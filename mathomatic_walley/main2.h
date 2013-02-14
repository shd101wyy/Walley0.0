/*
 * This file contains main() and the startup code for Mathomatic,
 * which is a computer algebra system written in the C programming language.
 *
 * Copyright (C) 1987-2012 George Gesslein II.
 
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

The chief copyright holder can be contacted at gesslein@mathomatic.org, or
George Gesslein II, P.O. Box 224, Lansing, NY  14882-0224  USA.
 
 */

/*
 * Output to stderr is only done in this file.  The rest of the Mathomatic code
 * should not output to stderr; error messages should use error() or go to stdout.
 * One reason for this is so that Mathomatic stdout can be redirected or piped,
 * catching all output.
 *
 * This program only supports binary and unary operators.
 * Unary operators are implemented as a binary operation with a dummy operand.
 *
 * In the storage format, each level of parentheses is indicated
 * by a level number (origin 1).  The deeper the level, the
 * higher the level number.
 *
 * The storage format for expressions is a fixed size array of elements
 * "token_type", which may be a CONSTANT, VARIABLE, or OPERATOR.
 * The array always alternates between operand (CONSTANT or VARIABLE)
 * and OPERATOR.  There is a separate integer for each array which
 * contains the current length of the expression stored in the array.
 * This length is always odd and must never exceed "n_tokens".
 *
 * In the storage format,
 * any number of TIMES and DIVIDE operators may be on the same level of parentheses,
 * because they are similar and the most basic multiplicative class operators.
 * The same for the PLUS and MINUS operators, because they are similar (additive class).
 * All other operators are only allowed one single operator per level of parentheses,
 * and no same nor different operators may be with it on that level within the current grouping.
 *
 * Most of the expression manipulation and comparison routines are recursive,
 * calling themselves for each level of parentheses.
 *
 * Note that equation space numbers internally are 1 less than the equation
 * space numbers displayed.  That is because internal equation space numbers
 * are origin 0 array indexes, while displayed equation numbers are origin 1.
 *
 * See the file "am.h" to start understanding the Mathomatic code and
 * to adjust memory usage.
 *
 * C types "long long" and "long double" are not used at all in Mathomatic,
 * because many architectures and compilers do not support them.  These large C
 * types can be used in the Mathomatic Prime Number Tools though, producing
 * larger prime numbers and quickly on a 64-bit computer.  64 bits is the size
 * of a double, so Mathomatic runs optimally on a 64-bit system.
 */

#if	!LIBRARY	/* This comments out this whole file if compiling as the symbolic math library. */

#include "globals.h"
#if	!NO_GETOPT_H
#include <getopt.h>
#endif

#if	WIN32_CONSOLE_COLORS
#include <windows.h>
#include <wincon.h>

HANDLE	hOut;
#endif

/*
 * Display invocation usage info.
 */
void
usage(fp)
FILE	*fp;
{
	fprintf(fp, _("Mathomatic computer algebra system, version %s\n"), "1.0");
	fprintf(fp, _("Usage: %s [ options ] [ input_files or input ]\n\n"), prog_name);
	fprintf(fp, _("Options:\n"));
	fprintf(fp, _("  -a            Enable alternative color mode.\n"));
	fprintf(fp, _("  -b            Enable bold color mode.\n"));
	fprintf(fp, _("  -c            Toggle color mode.\n"));
	fprintf(fp, _("  -d            Set demo mode.\n"));
	fprintf(fp, _("  -e            Process expressions and commands on the command line.\n"));
	fprintf(fp, _("  -h            Display this help and exit.\n"));
	fprintf(fp, _("  -m number     Specify a memory size multiplier.\n"));
	fprintf(fp, _("  -q            Set quiet mode (don't display prompts).\n"));
	fprintf(fp, _("  -r            Disable readline.\n"));
	fprintf(fp, _("  -s level      Set enforced security level for session.\n"));
	fprintf(fp, _("  -t            Set test mode.\n"));
	fprintf(fp, _("  -u            Set unbuffered output with input echo.\n"));
	fprintf(fp, _("  -v            Display version number, then exit successfully.\n"));
	fprintf(fp, _("  -w            Wide output mode, sets unlimited width.\n"));
	fprintf(fp, _("  -x            Enable HTML/XHTML output mode.\n"));
	fprintf(fp, _("\nPlease refer to the man page for details (type \"man mathomatic\" in shell).\n"));
}

/*
 * Repeatedly read a line of text from standard input and process the expression or command.
 */
void
main_io_loop(void)
{
	char	*cp = NULL;

	for (;;) {
		error_str = NULL;
		warning_str = NULL;
		default_color(false);
		snprintf(prompt_str, sizeof(prompt_str), "%d%s", cur_equation + 1, html_flag ? HTML_PROMPT_STR : PROMPT_STR);
		if ((cp = get_string((char *) tlhs, n_tokens * sizeof(token_type))) == NULL)
			break;
		process(cp);
	}
}

/*
 * All signal(2) initialization goes here.
 * Attach all necessary C signals to their handler functions.
 *
 * Return zero on success, or a non-zero unsettable signal number on error.
 */
int
set_signals(void)
{
	int	rv = 0;

	if (signal(SIGFPE, fphandler) == SIG_ERR)
		rv = SIGFPE;
	if (signal(SIGINT, inthandler) == SIG_ERR)
		rv = SIGINT;
	if (signal(SIGTERM, exithandler) == SIG_ERR)
		rv = SIGTERM;
#if	!MINGW
	if (signal(SIGHUP, exithandler) == SIG_ERR)
		rv = SIGHUP;
#endif
#if	UNIX || CYGWIN
	if (signal(SIGWINCH, resizehandler) == SIG_ERR)
		rv = SIGWINCH;
#endif
#if	TIMEOUT_SECONDS
	if (signal(SIGALRM, alarmhandler) == SIG_ERR)
		rv = SIGALRM;
	alarm(TIMEOUT_SECONDS);
#endif
	return rv;
}

/*
 * Floating point exception handler.
 * Floating point exceptions are currently ignored.
 */
void
fphandler(sig)
int	sig;
{
#if	DEBUG
	warning("Floating point exception.");
#endif
}

/*
 * Fancy Control-C (interrupt) signal handler.
 * Interrupts processing and returns to main prompt through a polling mechanism.
 * If it can't, repeated calls terminate this program.
 */
void
inthandler(sig)
int	sig;
{
	abort_flag++;
	switch (abort_flag) {
	case 0:
	case 1:
		/* wait for graceful abort */
		printf(_("\nUser interrupt signal received; three times in a row quits Mathomatic.\n"));
		return;
	case 2:
		printf(_("\nPress Control-C once more to quit program.\n"));
		return;
	default:
		/* abruptly quit this program */
		printf(_("\nRepeatedly interrupted; returning to operating system...\n"));
		exit_program(1);
	}
}

/*
 * Alarm signal handler.
 */
void
alarmhandler(sig)
int	sig;
{
	printf(_("\nTimeout, quitting...\n"));
	exit_program(1);
}

/*
 * Signal handler for proper exiting to the operating system.
 */
void
exithandler(sig)
int	sig;
{
	exit_program(1);
}

#if	UNIX || CYGWIN
/*
 * Window resize signal handler.
 */
void
resizehandler(sig)
int	sig;
{
	if (screen_columns)
		get_screen_size();
}
#endif

/*
 * Properly exit this program and return to the operating system.
 */
void
exit_program(exit_value)
int	exit_value;	/* zero if OK, non-zero indicates error return */
{
	reset_attr();
	if (html_flag) {
		printf("</pre>\n");
	}
#if	READLINE && !SECURE
	if (readline_enabled && security_level <= 3) {
		write_history(history_filename);	/* save readline history */
	}
#endif
	if (exit_value == 0 && !quiet_mode && !eoption && !html_flag) {
		printf(_("ByeBye!! from Mathomatic.\n"));
	}
#if	VALGRIND
	printf("Deallocating all Mathomatic allocated memory for valgrind memory leak checking...\n");
	printf("If you are not using valgrind, please compile without -DVALGRIND.\n");
        free_mem();     /* Free all known memory buffers to check for memory leaks with something like valgrind(1). */
#endif
	exit(exit_value);
}
#endif
