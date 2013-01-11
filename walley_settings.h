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
char *VAR_VALUE_TO_BE_COMPLETE="";      // save incomplete var_value
char *VAR_NAME_TO_BE_COMPLETE="";       // save incomplete var_name
char *VAR_VALUE_TYPE_TO_BE_COMPLETE=""; // save incomplete var_value_type


bool EXPRESSION_INCOMPLETE=FALSE;       // expression is incomplete
char *EXPRESSION_TO_BE_COMPLETE="";

bool RUN_EXPRESSION_INCOMPLETE=FALSE;    // can not run expression that is incomplete
char *RUN_EXPRESSION_TO_BE_COMPLETE="";


// For switch sentence
int SPACE_OF_FIRST_SWITCH_SENTENCE=0;
bool NOW_WRITTING_SWITCH=FALSE;
char *SWITCH_OBJECT="";
char *SENTENCE_OF_SWITCH="";


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

