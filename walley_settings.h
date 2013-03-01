//
//  walley_settings.h
//  Walley
//
//  Created by shd101wyy on 12-11-8.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

#include "walley_data.h"


struct VAR *VAR_var;                    // Var Variables
struct VAR *VAR_settings;               // Var Settings
char **TEMP_FILE;                       // Save string to file
char **FUNCTION;                        // Save function strings
char **WALLEY_LANGUAGE_FILE;            // not in use now
char **WALLEY_SIMILARITY_FILE;          // not in use now
char **WALLEY_VERB_FILE;                // not in use now
char **WALLEY_EXPRESSION;               // for expression translate
char *HIGHTEST_FILE;                    // for import file.... eg:   a.wy->b.wy->c.wy run a.wy, then b.wy is the superior file, so as name is its name
char *AS_NAME;                          // for import file.
char **ARGV;                            // to get argv in main
int ARGC;                               // to get argc in main
char *FIRST_RUNNING_FILE="";            // the file you run
int TURN=0;                             // row in file
bool HAS_INIT_WALLEY_RUN_STR=FALSE;     // for embed function walley_run_str()
struct VAR *VAR_VAR_FOR_EMBED;          // Var Variables
struct VAR *VAR_SETTINGS_FOR_EMBED;     // Var Settings
char **TEMP_FILE_FOR_EMBED;             // Save string to file
char **FUNCTION_FOR_EMBED;              // Save function strings
char **WALLEY_EXPRESSION_FOR_EMBED;
char *CURRENT_DIRECTORY="./";           // File Directory


bool VAR_VALUE_INCOMPLETE=FALSE;        // eg:  x="12  incomplete  x="123" complete
char *VAR_VALUE_INCOMPLETE_TYPE="";     // save incomplete var value type
//struct TOKEN *VAR_VALUE_TO_BE_COMPLETE; // save incomplete var_value
char *VAR_VALUE_TO_BE_COMPLETE; // save incomplete var_value

char *VAR_NAME_TO_BE_COMPLETE="";       // save incomplete var_name
char *VAR_VALUE_TYPE_TO_BE_COMPLETE=""; // save incomplete var_value_type


bool EXPRESSION_INCOMPLETE=FALSE;       // expression is incomplete
char *EXPRESSION_TO_BE_COMPLETE="";

bool RUN_EXPRESSION_INCOMPLETE=FALSE;    // can not run expression that is incomplete
char *RUN_EXPRESSION_TO_BE_COMPLETE="";

bool WALLEY_SUBSTITUTION_CAN_JUST_EVAL_IN_THE_END=TRUE;

// For switch sentence
int SPACE_OF_FIRST_SWITCH_SENTENCE=0;
bool NOW_WRITTING_SWITCH=FALSE;
char *SWITCH_OBJECT="";
char *SENTENCE_OF_SWITCH="";


// Global Var
char *GLOBAL_VAR="[]";

// List Incomplete
int LIST_TOTAL_LEFT=0; // num of [
int LIST_TOTAL_RIGHT=0; // num of ]

// for loop
bool CAN_CONTINUE=FALSE;
bool CAN_BREAK=FALSE;
bool CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK=TRUE;  // if meet break, continue, then it is false;


// for while loop
char **STRING_IN_WHILE_LOOP;
char *LAST_WHILE_SENTENCE;  // while x<10:    x<10 is the LAST_WHILE_SENTENCE
int SPACE_OF_FIRST_WHILE_SENTENCE; // |while x<10|    0---->SPACE_OF_FIRST_WHILE_SENTENCE
bool NOW_WRITTING_WHILE;

// for for loop
char **STRING_IN_FOR_LOOP;
char *I_VALUE_AFTER_IN;    // for i in range(3)   range(3) is I_VALUE_AFTER_IN
char *I_IN_FOR_LOOP;       // for i in range(3)    i is I_IN_FOR_LOOP
int SPACE_OF_FIRST_FOR_SENTENCE;  // |for i in range(3)|   0--->SPACE_OF_FIRST_FOR_SENTENCE
bool NOW_WRITTING_FOR;


// for function
bool NOW_WRITTING_FUNCTION;
int SPACE_OF_FIRST_DEF_SENTENCE;  // |def Hi():|  0--->SPACE_OF_FIRST_DEF_SENTENCE
bool NOW_WRITTING_EXPRESSION=FALSE;

// for class
bool NOW_WRITTING_CLASS;
int SPACE_OF_FIRST_CLASS_SENTENCE;  // |class a:|  0--->SPACE_OF_FIRST_CLASS_SENTENCE
bool HAVE_INIT_CLASS_LIST=FALSE;
struct CLASS *CLASS_LIST;
int CLASS_NUM=0; // class num
char **INSTANCE_NAMES_LIST;


// collect the string that will be displayed
// after finished the loop
// print them together
bool PRINT_IN_WHILE_OR_FOR_LOOP=FALSE;
char *PRINT_STRING_AFTER_LOOP="";
int LOOP_TURN=0; // Count the loop num when meets for and while
                // LOOP_TURN -- after one loop.


bool NOW_IN_ANNOTATION=FALSE;

int REQUIRED_SPACE=0;
int CURRENT_SPACE=0;


// for if
bool NOW_WRITTING_IF;
int SPACE_OF_FIRST_IF_SENTENCE;
struct IF IF_ELIF_ELSE;
int INDEX_OF_IF_ELIF_ELSE=0; // if elif , then INDEX_OF... ++, if else, then ++. if finish if, then -> 0

char *SAVE_VAR_NAME_TO_CHECK_WHETHER_IT_IS_INSTANCE="";


char *USER_NAME=""; // for x.append(3) where x=[1,2,3].. then upload [1,2,3,3] to x.. Save x to USER_NAME

// For if elif sentence
/*
int SPACE_OF_FIRST_IF_ELIF_ELSE_SENTENCE=0;
bool NOW_WRITTING_IF=FALSE;
char *SENTENCE_OF_IF="";
*/

//char *STR_TO_BE_INCLUED_WHILE_MAKING_EXEC_FILE; // string that need to be included whiling making exec file.. replace "walley.h"




//char *FUNCTIONS_IN_DEF="[]";  // private functions in functions
//bool NOW_IN_DEF=FALSE;        // now running a function
//char *LAST_FUNC_NAME="";
//char *CURRENT_INSTANCE_NAME;  // to save the current instance name. for fixing the expression error in class function



/* I FINALLY STOP USING THESE VARIABLES......
//####################### struct_settings ##################################
//    fputs("space:0:int:\n",fp);
int SPACE=0;
int CURRENT_SPACE=0;
int NOW_WRITTING_FUNCTION=0;
int NOW_WRITTING_CLASS=0;
int NOW_WRITTING_WHILE=0;
int NOW_WRITTING_FOR=0;
int NOW_RUN_IF=0;
char *LAST_IF_SENTENCE;
char *LAST_WHILE_SENTENCE;
char *TEMP_I;
char *TEMP_I_IN_FOR_SENTENCE;
char *STRING_IN_WHILE_LOOP;
char *STRING_IN_FOR_LOOP;
int WHILE_FINISH=1;
int SPACE_OF_FIRST_IF_SENTENCE=0;
int SPACE_OF_FIRST_WHILE_SENTENCE=0;
int SPACE_OF_FIRST_FOR_SENTENCE=0;
int SPACE_OF_FIRST_DEF_SENTENCE=0;
int SPACE_OF_FIRST_CLASS_SENTENCE=0;
int NOW_IN_ANNOTATION=0;
int CAN_RUN_BASIC_INPUT=0;
int CAN_BREAK=0;
int CAN_CONTINUE=0;
int TURN=0;

//######################## struct var settings ############################
char *__TEMP_WHILE__="[]";
char *__TEMP_WHILE_SPACE__="[]";
char *__TEMP_STRING_IN_WHILE_LOOP__="[]";
char *__TEMP_IF__="[]";
char *__TEMP_IF_SPACE__="[]";
char *__HAS_RUN_IF__="[]";
char *__TEMP_FOR__="[]";
char *__TEMP_I__="[]";
char *__TEMP_STRING_IN_FOR_LOOP__="[]";
char *__TEMP_CLASS__="{}";
char *__TEMP_CLASS_NAME_NOW_WRITTING__="'None'";
char *__STRING_IN_TEMP_CLASS__="{}";
char *__INSTANCE_NAME__="[]";
char *__INSTANCE_VAR__="[]";
 */

