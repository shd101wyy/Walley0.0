//
//  walley_core.h
//  Walley
//
//  Created by shd101wyy on 12-10-18.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

//
//  walley_core_final.h
//  Walley
//
//  Created by shd101wyy on 12-10-17.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

/*
 * File:   walley.h
 * Author: shd101wyy
 *
 * Created on August 17, 2012, 2:41 PM
 */


/*
 ################################################################################################################################
 ############################################ Attention #########################################################################
 ################################################################################################################################
 1.  The Token List here are all Token Without W_WHITESPACES 
 
 ################################################################################################################################
 ################################################################################################################################
 
*/


//#include "walley_function.h"
#include "walley_language.h"



/*
 *#################################################################################################################################
 */

void Walley_Initialize_Settings(struct VAR **settings){


    Var_addProperty(settings, "can_run_basic_input", "0", "int");

    //Var_addProperty(settings, "turn", "0", "int");

    Var_addProperty(settings, "fraction_mode", "1", "int");



}

void Walley_Initialize_Var(struct VAR **var){


    // now this function did nothing
    
    
}



void Walley_Initialize(){
    
    matho_init();

    
    Var_initVar(&VAR_var);
    Var_initVar(&VAR_settings);
    
    Str_initStringList(&TEMP_FILE);
    Str_initStringList(&FUNCTION);
    Str_initStringList(&WALLEY_EXPRESSION);
    AS_NAME="";
    //matho_init();
    
    //################ Initialize some necessary expression ##########################################################
    Str_addString(&WALLEY_EXPRESSION, "walley_show_var|show var");
    Str_addString(&WALLEY_EXPRESSION, "walley_decimal_mode|decimal mode");
    Str_addString(&WALLEY_EXPRESSION, "walley_fraction_mode|fraction mode");
    Str_addString(&WALLEY_EXPRESSION, "walley_is_fraction_mode|is fraction mode");
    
    //################################################################################################################
    
    
    
    Walley_Initialize_Var(&VAR_var);
    Walley_Initialize_Settings(&VAR_settings);
    Str_addString(&TEMP_FILE, "#Temp File In Order To Run goto");
    
    
    Str_initStringList(&STRING_IN_WHILE_LOOP);
    Str_initStringList(&STRING_IN_FOR_LOOP);
    
}

void Walley_Finalize(){
    free(VAR_var);
    free(VAR_settings);
    free(FUNCTION);
    free(TEMP_FILE);
    free(WALLEY_EXPRESSION);
// free(AS_NAME) is incorrect
}


void Walley_Run_For_Appointed_Var(struct VAR **struct_var, struct VAR **struct_settings, char ***save_to_file, char* existing_file, char ***FUNCTION_functions, char* input_str) {
    
    
    if (VAR_VALUE_INCOMPLETE==TRUE) {
        if (strcmp(VAR_VALUE_INCOMPLETE_TYPE,"string\"")==0) {
            int length_of_input_str=(int)strlen(input_str);
            // Can become complete now
            if (input_str[length_of_input_str-1]=='"'&&input_str[length_of_input_str-2]!='\\') {
                VAR_VALUE_TO_BE_COMPLETE=append(VAR_VALUE_TO_BE_COMPLETE, input_str);
                input_str=append(VAR_NAME_TO_BE_COMPLETE, "=");
                input_str=append(input_str, VAR_VALUE_TO_BE_COMPLETE);
                
                
                VAR_VALUE_INCOMPLETE=FALSE;
                VAR_VALUE_INCOMPLETE_TYPE="";
                VAR_VALUE_TO_BE_COMPLETE="";
                VAR_NAME_TO_BE_COMPLETE="";
                VAR_VALUE_TYPE_TO_BE_COMPLETE="";
                
                Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions, input_str);
                
            }
            // Can not become complete now
            else{
                if (input_str[length_of_input_str-1]=='\\') {
                    input_str=append(input_str, "n");
                }
                VAR_VALUE_TO_BE_COMPLETE=append(VAR_VALUE_TO_BE_COMPLETE, input_str);
            }
            
        }
        
        else if (strcmp(VAR_VALUE_INCOMPLETE_TYPE, "string'")==0){
            int length_of_input_str=(int)strlen(input_str);
            // Can become complete now
            if (input_str[length_of_input_str-1]=='\''&&input_str[length_of_input_str-2]!='\\') {
                VAR_VALUE_TO_BE_COMPLETE=append(VAR_VALUE_TO_BE_COMPLETE, input_str);
                input_str=append(VAR_NAME_TO_BE_COMPLETE, "=");
                input_str=append(input_str, VAR_VALUE_TO_BE_COMPLETE);
                
                
                VAR_VALUE_INCOMPLETE=FALSE;
                VAR_VALUE_INCOMPLETE_TYPE="";
                VAR_VALUE_TO_BE_COMPLETE="";
                VAR_NAME_TO_BE_COMPLETE="";
                VAR_VALUE_TYPE_TO_BE_COMPLETE="";
                
                Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions, input_str);
                
            }
            // Can not become complete now
            else{
                if (input_str[length_of_input_str-1]=='\\') {
                    input_str=append(input_str, "n");
                }
                VAR_VALUE_TO_BE_COMPLETE=append(VAR_VALUE_TO_BE_COMPLETE, input_str);
            }
            
        }
        
        else if (strcmp(VAR_VALUE_INCOMPLETE_TYPE, "list")==0){
            int length_of_input_str=(int)strlen(input_str);
            LIST_TOTAL_LEFT+=count_str_not_in_string(input_str, "[");
            LIST_TOTAL_RIGHT+=count_str_not_in_string(input_str, "]");
            if (LIST_TOTAL_LEFT==LIST_TOTAL_RIGHT&&input_str[length_of_input_str-1]==']') {
                VAR_VALUE_TO_BE_COMPLETE=append(VAR_VALUE_TO_BE_COMPLETE, trim(input_str));
                input_str=append(VAR_NAME_TO_BE_COMPLETE, "=");
                input_str=append(input_str, VAR_VALUE_TO_BE_COMPLETE);
                
                
                VAR_VALUE_INCOMPLETE=FALSE;
                VAR_VALUE_INCOMPLETE_TYPE="";
                VAR_VALUE_TO_BE_COMPLETE="";
                VAR_NAME_TO_BE_COMPLETE="";
                VAR_VALUE_TYPE_TO_BE_COMPLETE="";
                
                LIST_TOTAL_LEFT=0;
                LIST_TOTAL_RIGHT=0;
                
                Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions, input_str);
                
            }
            // Can not become complete now
            else{
                VAR_VALUE_TO_BE_COMPLETE=append(VAR_VALUE_TO_BE_COMPLETE, trim(input_str));
            }
        }
        
        else if (strcmp(VAR_VALUE_INCOMPLETE_TYPE, "dictionary")==0){
            int length_of_input_str=(int)strlen(input_str);
            if (count_str_not_in_string(input_str, "{")+1==count_str_not_in_string(input_str, "}")&&input_str[length_of_input_str-1]=='}') {
                VAR_VALUE_TO_BE_COMPLETE=append(VAR_VALUE_TO_BE_COMPLETE, input_str);
                input_str=append(VAR_NAME_TO_BE_COMPLETE, "=");
                input_str=append(input_str, VAR_VALUE_TO_BE_COMPLETE);
                
                
                VAR_VALUE_INCOMPLETE=FALSE;
                VAR_VALUE_INCOMPLETE_TYPE="";
                VAR_VALUE_TO_BE_COMPLETE="";
                VAR_NAME_TO_BE_COMPLETE="";
                VAR_VALUE_TYPE_TO_BE_COMPLETE="";
                
                Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions, input_str);
                
            }
            // Can not become complete now
            else{
                VAR_VALUE_TO_BE_COMPLETE=append(VAR_VALUE_TO_BE_COMPLETE, input_str);
            }
        }
        
        else if (strcmp(VAR_VALUE_INCOMPLETE_TYPE, "expression")==0){
            int length_of_input_str=(int)strlen(input_str);
            if (input_str[length_of_input_str-1]=='>') {
                VAR_VALUE_TO_BE_COMPLETE=append(VAR_VALUE_TO_BE_COMPLETE, " ");
                VAR_VALUE_TO_BE_COMPLETE=append(VAR_VALUE_TO_BE_COMPLETE, trim(input_str));
                input_str=append(VAR_NAME_TO_BE_COMPLETE, "=");
                input_str=append(input_str, VAR_VALUE_TO_BE_COMPLETE);
                
                
                VAR_VALUE_INCOMPLETE=FALSE;
                VAR_VALUE_INCOMPLETE_TYPE="";
                VAR_VALUE_TO_BE_COMPLETE="";
                VAR_NAME_TO_BE_COMPLETE="";
                VAR_VALUE_TYPE_TO_BE_COMPLETE="";
                
                Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions, input_str);
                
            }
            // Can not become complete now
            else{
                VAR_VALUE_TO_BE_COMPLETE=append(VAR_VALUE_TO_BE_COMPLETE, " ");
                VAR_VALUE_TO_BE_COMPLETE=append(VAR_VALUE_TO_BE_COMPLETE, trim(input_str));
            }
            
        }
        
    }
    else if (EXPRESSION_INCOMPLETE==TRUE){
        char *trim_input_str=trim(input_str);
        // can become incomplete
        if (trim_input_str[(int)strlen(trim_input_str)-1]=='>') {
            EXPRESSION_TO_BE_COMPLETE=append(EXPRESSION_TO_BE_COMPLETE, " ");
            EXPRESSION_TO_BE_COMPLETE=append(EXPRESSION_TO_BE_COMPLETE, trim_input_str);
            Str_addString(&WALLEY_EXPRESSION, append(TEMP_FUNCTION_NAME,append("|",substr(EXPRESSION_TO_BE_COMPLETE,2,(int)strlen(EXPRESSION_TO_BE_COMPLETE)-1))));
            EXPRESSION_INCOMPLETE=FALSE;
            EXPRESSION_TO_BE_COMPLETE="";
        }
        
        // can not become complete
        else{
            EXPRESSION_TO_BE_COMPLETE=append(EXPRESSION_TO_BE_COMPLETE, " ");
            EXPRESSION_TO_BE_COMPLETE=append(EXPRESSION_TO_BE_COMPLETE, trim_input_str);
        }
    }
    else if (RUN_EXPRESSION_INCOMPLETE==TRUE){
        char *trim_input_str=trim(input_str);
        int length_of_trim_input_str=(int)strlen(trim_input_str);
        
        // complete
        if (trim_input_str[length_of_trim_input_str-1]=='>') {
            RUN_EXPRESSION_TO_BE_COMPLETE=append(RUN_EXPRESSION_TO_BE_COMPLETE, " ");
            RUN_EXPRESSION_TO_BE_COMPLETE=append(RUN_EXPRESSION_TO_BE_COMPLETE, trim_input_str);
            RUN_EXPRESSION_INCOMPLETE=FALSE;
            Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions, RUN_EXPRESSION_TO_BE_COMPLETE);
            RUN_EXPRESSION_TO_BE_COMPLETE="";
        }
        
        // not complete
        else{
            RUN_EXPRESSION_TO_BE_COMPLETE=append(RUN_EXPRESSION_TO_BE_COMPLETE, " ");
            RUN_EXPRESSION_TO_BE_COMPLETE=append(RUN_EXPRESSION_TO_BE_COMPLETE, trim_input_str);
        }
    }
    else{
        
        
        // printf("######### Run Function Walley_Run_For_Appointed_Var ######\n");
        // check whether in #~ ~# at first
        
        // I stop auto clean temporiaryly
        /*
         //####################  Auto clean variables  #########################################
         int turn = atoi(Var_getValueOfVar(struct_settings , "turn"));
         if (turn%10==0&&turn!=0) {
         
         Walley_Clean_Variables(existing_file, struct_var, turn);
         }
         
         //#####################################################################################
         */
        
        
        /*  These codes have problem
         // New code here on Dec 10.
         //####################  Auto clean variables  #########################################
         if (strcmp(existing_file, FIRST_RUNNING_FILE)==0) {
         
         
         int turn = TURN;
         if (turn%10==0&&turn!=0) {
         Walley_Clean_Variables(existing_file, struct_var, turn);
         }
         }
         
         //#####################################################################################
         */
        
        
        
        
        bool continue_run = FALSE;
        bool find_gang_gang = FALSE;
        bool str_is_empty=FALSE;
        bool run_goto = FALSE;
        
        char *temp_input_str=input_str;
        
        
        
        
        if (find_not_in_string(input_str, "\n") != -1) {
            continue_run = TRUE;
            input_str = substr(input_str, 0, find_not_in_string(input_str, "\n"));
        }
        
        if (find_not_in_string(input_str, "\\n") != -1) {
            continue_run = TRUE;
            find_gang_gang = TRUE;
            input_str = substr(input_str, 0, find_not_in_string(input_str, "\\n"));
        }
        input_str=removeNFromBack(input_str);
        
        
        
        char *judge_annotation_string=trim(input_str);
        int length_of_judge_annotation_string=(int)strlen(judge_annotation_string);
        if (judge_annotation_string[length_of_judge_annotation_string-1]=='#' && judge_annotation_string[length_of_judge_annotation_string-2]=='~'){
            // printf("Now End Long Annotation");
            NOW_IN_ANNOTATION = 0;
            
        }
        else if (judge_annotation_string[0] == '#' && judge_annotation_string[1] == '~') {
            //// printf("Now Begin Long Annotation");
            NOW_IN_ANNOTATION = 1;
        }
        if(NOW_IN_ANNOTATION==0 && stringIsEmpty(trim(input_str))==FALSE){
            
            Str_addString(save_to_file, input_str);
            
            
            //I add this value here in order to run now_run_if.
            bool can_run_basic_input = TRUE;
            
            
            CURRENT_SPACE = numOfSpaceAheadString(input_str);
            
            //printf("\n\n\n\n|%s|\n\n\n\n",input_str);
            
            // delete #.... after sentence
            char *temp_input_str2=trim(input_str);
            int index_of_jing=find_not_in_string(temp_input_str2, "#");
            if(index_of_jing!=-1 && index_of_jing !=0){
                input_str=substr(input_str, 0, find_not_in_string(input_str, "#"));
            }
            
            input_str=cleanUpSentence(input_str);
            
            if (CURRENT_SPACE%4!=0) {
                printf("Error.. Current Space is incorrect\n");
                exit(0);
            }
            
            if (CURRENT_SPACE > REQUIRED_SPACE) {
                can_run_basic_input = FALSE;
            }
            
            
            if (input_str[(int)strlen(input_str)-1]==';') {
                printf("%s\n",input_str);
                char *temp_str="";
                temp_str=Str_appendSpaceAhead(temp_str, (int)strlen(input_str)-1);
                printf("%s^\n",temp_str);
                printf("Error. Walley does not need ; in sentence\n");
                exit(0);        }
            
            
            if(CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==FALSE){
                can_run_basic_input=FALSE;
            }
            
            CURRENT_INPUT_STR=input_str;
            
            
            
            struct TOKEN *token=Walley_Lexica_Analysis(input_str);
            TOKEN_checkError(token, input_str);
            //int length_of_token=TOKEN_length(token);
            int index_of_first_none_whitespace=TL_indexOfFirstNoneWhiteSpaceToken(token);
            struct TOKEN first_none_whitespace_token=token[index_of_first_none_whitespace];
            
            
            //printf("-------Now input is |%s| required space %d current space %d\n", input_str,space,current_space);
            
            //printf("input_str --------------> |%s|, %d\n",input_str,REQUIRED_SPACE);
            
            /*
             //################## Now Run If #######################################
             if (now_run_if == TRUE && str_is_empty==FALSE&& CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==TRUE) {
             if (CURRENT_SPACE > REQUIRED_SPACE || CURRENT_SPACE % 4 != 0) {
             printf("@@ |%s|\n",CURRENT_INPUT_STR);
             printf("Space Mistake\nCurrent Space is %d\nRequired Space is %d\n", CURRENT_SPACE, REQUIRED_SPACE);
             exit(0);
             }
             // I do not know whether it is right or not.......
             if (CURRENT_SPACE < REQUIRED_SPACE) {
             // change space and rewrite it to file
             REQUIRED_SPACE=CURRENT_SPACE;
             now_run_if=FALSE;
             
             }
             
             }
             */
            
            //################## Now Run If #######################################
            if (NOW_WRITTING_IF == TRUE && str_is_empty==FALSE && CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==TRUE) {
                can_run_basic_input=FALSE;
                // elif else or finish
                if (CURRENT_SPACE==SPACE_OF_FIRST_IF_SENTENCE) {
                    //ELIF
                    if (strcmp(first_none_whitespace_token.TOKEN_STRING, "elif")==0) {
                        Str_addString(&(IF_ELIF_ELSE.content[INDEX_OF_IF_ELIF_ELSE])
                                      , "#end");
                        INDEX_OF_IF_ELIF_ELSE++;
                        char *trim_input_str=trim(input_str);
                        char *string_in_elif=substr(trim_input_str, find(trim_input_str,"elif ")+5, find_from_behind(trim_input_str, ":"));
                        Str_addString(&IF_ELIF_ELSE.if_elif_else, string_in_elif);
                        IF_ELIF_ELSE.content=(char***)realloc(IF_ELIF_ELSE.content,sizeof(char**)*(INDEX_OF_IF_ELIF_ELSE+1));
                        
                        Str_initStringList(&IF_ELIF_ELSE.content[INDEX_OF_IF_ELIF_ELSE]);
                    }
                    //ELSE
                    else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "else")==0){
                        Str_addString(&(IF_ELIF_ELSE.content[INDEX_OF_IF_ELIF_ELSE])
                                      , "#end");
                        INDEX_OF_IF_ELIF_ELSE++;
                        Str_addString(&IF_ELIF_ELSE.if_elif_else, "#~ELSE~#");
                        IF_ELIF_ELSE.content=(char***)realloc(IF_ELIF_ELSE.content,sizeof(char**)*(INDEX_OF_IF_ELIF_ELSE+1));
                        Str_initStringList(&IF_ELIF_ELSE.content[INDEX_OF_IF_ELIF_ELSE]);
                        
                    }
                    //FINISH IF
                    else{
                        struct IF If_copy=IF_ELIF_ELSE;
                        int index_of_if_copy=INDEX_OF_IF_ELIF_ELSE;
                        
                        //printf("Begin to run if.. exit here temp..\n");
                        //IF_PrintIf(IF_ELIF_ELSE, INDEX_OF_IF_ELIF_ELSE+1);
                        Str_addString(&(IF_ELIF_ELSE.content[INDEX_OF_IF_ELIF_ELSE])
                                      , "#end");
                        NOW_WRITTING_IF=FALSE;
                        SPACE_OF_FIRST_IF_SENTENCE=0;
                        REQUIRED_SPACE=CURRENT_SPACE;
                        INDEX_OF_IF_ELIF_ELSE=0;
                        memset(&IF_ELIF_ELSE, 0, sizeof(IF_ELIF_ELSE));
                        
                        CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK=TRUE;
                        can_run_basic_input=TRUE;
                        
                        // Begin to Run Code
                        int i=0;
                        for (; i<=index_of_if_copy; i++) {
                            char *to_judge=If_copy.if_elif_else[i+1];
                            
                            
                            if (strcmp(to_judge, "#~ELSE~#")==0) {
                                //printf("run else\n");
                                Walley_Run_For_Appointed_Var_String_List(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions, If_copy.content[i]);
                                break;
                            }
                            bool can_run=Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(to_judge, struct_var, FUNCTION_functions);
                            if (can_run) {
                                //printf("run if elif \n");
                                Walley_Run_For_Appointed_Var_String_List(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions, If_copy.content[i]);
                                break;
                            }
                        }
                        //printf("FINISH Running If\n");
                        
                        
                        //exit(1);
                    }
                }
                
                // add string.
                else{
                    input_str = removeAheadSpaceForNum(input_str, SPACE_OF_FIRST_IF_SENTENCE + 4);
                    Str_addString(&(IF_ELIF_ELSE.content[INDEX_OF_IF_ELIF_ELSE])
                                  , input_str);
                    
                }
            }
            
            //############### Now Writting While In Progress ########################
            else if (NOW_WRITTING_WHILE == TRUE && str_is_empty==FALSE && CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==TRUE) {
                int space_of_first_while_sentence=SPACE_OF_FIRST_WHILE_SENTENCE;
                if (CURRENT_SPACE > space_of_first_while_sentence && CURRENT_SPACE % 4 == 0) {
                    can_run_basic_input = FALSE;
                    input_str = removeAheadSpaceForNum(input_str, space_of_first_while_sentence + 4);
                    
                    if (stringIsEmpty(input_str)==FALSE) {
                        Str_addString(&STRING_IN_WHILE_LOOP, input_str);
                        
                    }
                    
                }
                else if (CURRENT_SPACE <= space_of_first_while_sentence && CURRENT_SPACE % 4 == 0) {
                    //printf("Begin to Run While, input_str %s, current_space %d, space_of_first %d\n",input_str,current_space,space_of_first_while_sentence);
                    can_run_basic_input = TRUE;
                    NOW_WRITTING_WHILE = FALSE;
                    
                    
                    REQUIRED_SPACE=CURRENT_SPACE;
                    
                    
                    char *temp_last_while_sentence=LAST_WHILE_SENTENCE;
                    
                    Str_addString(&STRING_IN_WHILE_LOOP, "#end");
                    char **temp_string_list_in_while_loop=STRING_IN_WHILE_LOOP;
                    Str_initStringList(&STRING_IN_WHILE_LOOP);
                    
                    // while (Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(last_while_sentence2, struct_var,FUNCTION_functions) == TRUE) {
                    while (Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(temp_last_while_sentence, struct_var,FUNCTION_functions) == TRUE) {
                        
                        CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK=TRUE;
                        
                        Walley_Run_For_Appointed_Var_String_List(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions, temp_string_list_in_while_loop);
                        
                        if (CAN_BREAK) {
                            CAN_BREAK=FALSE;
                            break;
                        }
                        if (CAN_CONTINUE) {
                            CAN_CONTINUE=FALSE;
                            continue;
                        }
                        
                    }
                    
                    LOOP_TURN--;
                    CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK=TRUE;
                    
                    
                    if (LOOP_TURN==0) {
                        LOOP_TURN=0;
                        
                        // Finish Main Loop
                        // Stop Collecting String
                        PRINT_IN_WHILE_OR_FOR_LOOP=FALSE;
                        printf("%s",PRINT_STRING_AFTER_LOOP);
                        PRINT_STRING_AFTER_LOOP="";
                        
                    }
                    
                    
                }
            }//############### Now Writting Function In Progress #####################
            else if (NOW_WRITTING_FUNCTION == TRUE && str_is_empty==FALSE&& CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==TRUE) {
                can_run_basic_input = FALSE;
                //printf("//############### Now Writting Function In Progress #####################\n");
                //printf("--->%s\n",input_str);
                if (CURRENT_SPACE % 4 != 0) {
                    printf("@@ |%s|\n",CURRENT_INPUT_STR);
                    
                    printf("Space Mistake\nCurrent Space is %d\nRequired Space is %d\n", CURRENT_SPACE, REQUIRED_SPACE);
                    exit(0);
                } else if (CURRENT_SPACE <= SPACE_OF_FIRST_DEF_SENTENCE) {
                    // printf("Finish_define_FUNCTION\n");
                    can_run_basic_input = TRUE;
                    NOW_WRITTING_FUNCTION = FALSE;
                    REQUIRED_SPACE=CURRENT_SPACE;
                    Str_addString(FUNCTION_functions, "#~End");
                    
                }
                else {
                    
                    
                    input_str = removeAheadSpaceForNum(input_str, SPACE_OF_FIRST_DEF_SENTENCE + 4);
                    
                    
                    if ((strcmp(first_none_whitespace_token.TOKEN_STRING, "exp")==0&&input_str[(int)strlen(input_str)-1]==':'&&CURRENT_SPACE==SPACE_OF_FIRST_DEF_SENTENCE+4)|| NOW_WRITTING_EXPRESSION==TRUE) {
                        if (NOW_WRITTING_EXPRESSION==FALSE) {
                            NOW_WRITTING_EXPRESSION=TRUE;
                            REQUIRED_SPACE+=4;
                        }
                        else if (CURRENT_SPACE<REQUIRED_SPACE) {
                            Str_addString(FUNCTION_functions, input_str);
                            NOW_WRITTING_EXPRESSION=FALSE;
                            REQUIRED_SPACE=CURRENT_SPACE;
                        }
                        else{
                            //printf("EXPRESSION----> %s\n",input_str);
                            //char *sentence_after_analysize=Walley_Analyze_Sentence_By_Known_Variable(input_str,TEMP_FUNCTION_PARAMETER);
                            //printf("sentence_after_analysize %s\n",sentence_after_analysize);
                            
                            //printf("TEMP FUNCTION NAME %s\n",TEMP_FUNCTION_NAME);
                            
                            
                            // new code here on Jan 6
                            
                            
                            if (EXPRESSION_INCOMPLETE==FALSE) {
                                
                                
                                char *trim_input_str=trim(input_str);
                                //printf("-->|%s|\n",trim_input_str);
                                
                                
                                // basic expression without boundary
                                // like
                                /*
                                 def add(num1,num2):
                                 exp:
                                 add num1 num2  # just add "add num1 num2" as expression
                                 */
                                
                                if ( trim_input_str[0]!='<'&&trim_input_str[1]!='@') {
                                    // add exression...                                                   //problem here, I add trim. No problem before.
                                    Str_addString(&WALLEY_EXPRESSION, append(TEMP_FUNCTION_NAME,append("|",trim(input_str))));
                                }
                                
                                
                                // basic expression with boundary but only in one row
                                // like
                                /*
                                 def add(num1,num2):
                                 exp:
                                 <@add num1 num2>  # just add "add num1 num2" as expression
                                 */
                                
                                else if (trim_input_str[0]=='<'&&trim_input_str[1]=='@'&&trim_input_str[(int)strlen(trim_input_str)-1]=='>'){
                                    Str_addString(&WALLEY_EXPRESSION, append(TEMP_FUNCTION_NAME,append("|",substr(trim_input_str, 2, (int)strlen(trim_input_str)-1))));
                                }
                                
                                
                                // basic expression with boundary and not only in one row
                                // like
                                /*
                                 def add(num1,num2):
                                 exp:
                                 <@add
                                 num1
                                 num2
                                 >
                                 
                                 */
                                else{
                                    EXPRESSION_INCOMPLETE=TRUE;
                                    EXPRESSION_TO_BE_COMPLETE=trim_input_str;
                                    //printf("--->|%s|\n",EXPRESSION_TO_BE_COMPLETE);
                                }
                            }
                            
                        }
                        
                        
                        
                    }
                    
                    else{
                        
                        Str_addString(FUNCTION_functions, input_str);
                        if (CURRENT_SPACE<REQUIRED_SPACE) {
                            REQUIRED_SPACE=CURRENT_SPACE;
                        }
                        
                        // find another function
                        //if (find_from_index_to_index(removeAheadSpace(input_str), "def ", 0, (int)strlen(removeAheadSpace(input_str))) != -1) {
                        if (strcmp(first_none_whitespace_token.TOKEN_STRING, "def")==0) {
                            REQUIRED_SPACE = REQUIRED_SPACE + 4;
                        }
                        
                        
                    }
                    //REQUIRED_SPACE = current_space;
                    
                }
                
                
            }        //################### Now Writting Class ##############################
            else if (NOW_WRITTING_CLASS == TRUE && str_is_empty==FALSE&& CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==TRUE) {
                can_run_basic_input = FALSE;
                // printf("#### Now_Writting_Class In Progress ####\n");
                
                if(CURRENT_SPACE % 4 !=0){
                    printf("Space Mistake occurred while defining a class\n");
                }
                else if (CURRENT_SPACE<=SPACE_OF_FIRST_CLASS_SENTENCE){
                    NOW_WRITTING_CLASS=FALSE;
                    can_run_basic_input = TRUE;
                    REQUIRED_SPACE=CURRENT_SPACE;
                }
                else{
                    
                    
                    
                    input_str = removeAheadSpaceForNum(input_str, SPACE_OF_FIRST_CLASS_SENTENCE + 4);
                    
                    CLASS_LIST[CLASS_NUM].string_in_class=append(CLASS_LIST[CLASS_NUM].string_in_class, append(input_str,"\\n"));
                    
                    REQUIRED_SPACE=CURRENT_SPACE;
                    
                }
                
            }
            //################## Now Run For #######################################
            else if (NOW_WRITTING_FOR == TRUE && str_is_empty==FALSE && CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==TRUE) {
                int space_of_first_for_sentence=SPACE_OF_FIRST_FOR_SENTENCE;
                if (CURRENT_SPACE > space_of_first_for_sentence && CURRENT_SPACE % 4 == 0) {
                    //printf("################ Now Writting For ###################");
                    //printf("STRING IN FOR LOOP is |%s|\n", string_in_for_loop);
                    can_run_basic_input = FALSE;
                    
                    input_str = removeAheadSpaceForNum(input_str, space_of_first_for_sentence + 4);
                    
                    
                    if (stringIsEmpty(input_str)==FALSE) {
                        Str_addString(&STRING_IN_FOR_LOOP, input_str);
                        
                    }
                }
                else if (CURRENT_SPACE <= space_of_first_for_sentence && CURRENT_SPACE % 4 == 0) {
                    can_run_basic_input = TRUE;
                    NOW_WRITTING_FOR = FALSE;
                    REQUIRED_SPACE=CURRENT_SPACE;
                    
                    char *i_value_after_in=I_VALUE_AFTER_IN;
                    char *i_in_for_loop = I_IN_FOR_LOOP;
                    
                    
                    
                    if (strcmp(variableValueType(i_value_after_in), "list") == 0) {
                        
                        int value_num = valueNumOfList(i_value_after_in);
                        
                        int x = 0;
                        
                        // Idk Why I must add #end here.. But if I
                        // do not add, it will have problems
                        Str_addString(&STRING_IN_FOR_LOOP, "#end");
                        
                        char **temp_string_list_in_foor_loop=STRING_IN_FOR_LOOP;
                        Str_initStringList(&STRING_IN_FOR_LOOP);
                        
                        
                        for (x = 0; x < value_num; x++) {
                            CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK=TRUE;
                            
                            char *value_of_i_in_x=valueOfListAtIndex(i_value_after_in, x);
                            
                            
                            char *init_temp_i = (char*)malloc(sizeof (char) *((int) strlen(i_in_for_loop) + 2 + (int) strlen(value_of_i_in_x)));
                            strcpy(init_temp_i, i_in_for_loop);
                            strcat(init_temp_i, "=");
                            strcat(init_temp_i, value_of_i_in_x);
                            init_temp_i[(int) strlen(i_in_for_loop) + 1 + (int) strlen(value_of_i_in_x)]=0;
                            
                            
                            Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions,init_temp_i);
                            
                            
                            
                            
                            Walley_Run_For_Appointed_Var_String_List(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions, temp_string_list_in_foor_loop);
                            
                            
                            if (CAN_BREAK) {
                                CAN_BREAK=FALSE;
                                break;
                            }
                            if (CAN_CONTINUE) {
                                CAN_CONTINUE=FALSE;
                                continue;
                            }
                            
                            
                        }
                        CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK=TRUE;
                        
                        LOOP_TURN--;
                        
                    }
                    else {
                        printf("#### For Sentence Only Support list Type At This Time\n");
                    }
                    
                    if (LOOP_TURN==0) {
                        LOOP_TURN=0;
                        
                        // Finish Main Loop
                        // Stop Collecting String
                        PRINT_IN_WHILE_OR_FOR_LOOP=FALSE;
                        printf("%s",PRINT_STRING_AFTER_LOOP);
                        PRINT_STRING_AFTER_LOOP="";
                        
                    }
                    
                    
                }
            }
            
            if(CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==FALSE){
                can_run_basic_input=FALSE;
            }
            
            //############### New code here on Jan 10 #############################################
            //############### To support switch sentence ##########################################
            if(NOW_WRITTING_SWITCH == TRUE && str_is_empty==FALSE && CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==TRUE){
                
                can_run_basic_input = FALSE;
                if(CURRENT_SPACE % 4 !=0){
                    printf("Space Mistake occurred while defining a switch\n");
                }
                else if (CURRENT_SPACE<=SPACE_OF_FIRST_SWITCH_SENTENCE){
                    can_run_basic_input = TRUE;
                    
                    char *copy_SENTENCE_OF_SWITCH=SENTENCE_OF_SWITCH;
                    copy_SENTENCE_OF_SWITCH=append(copy_SENTENCE_OF_SWITCH, "#end");
                    
                    //char temp2[100];
                    //sprintf(temp2, "%d", SPACE_OF_FIRST_SWITCH_SENTENCE);
                    //Var_changeValueOfVar(*struct_settings , "space", append("",temp2), "int");
                    REQUIRED_SPACE=SPACE_OF_FIRST_SWITCH_SENTENCE;
                    
                    NOW_WRITTING_SWITCH=FALSE;
                    SENTENCE_OF_SWITCH="";
                    SWITCH_OBJECT="";
                    SPACE_OF_FIRST_SWITCH_SENTENCE=0;
                    
                    //printf("TO RUN :|\n%s|\nspace is %d\n",copy_SENTENCE_OF_SWITCH,SPACE_OF_FIRST_SWITCH_SENTENCE);
                    Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions, copy_SENTENCE_OF_SWITCH);
                    
                    REQUIRED_SPACE=CURRENT_SPACE;
                    
                }
                else{
                    
                    // case sentence
                    if (strcmp(first_none_whitespace_token.TOKEN_STRING,"case")==0&& CURRENT_SPACE==SPACE_OF_FIRST_SWITCH_SENTENCE+4) {
                        if (CURRENT_SPACE%4!=0 && CURRENT_SPACE<SPACE_OF_FIRST_SWITCH_SENTENCE+4) {
                            printf("@@ |%s|\n",CURRENT_INPUT_STR);
                            printf("Space mistake occurred while running |%s|\n",input_str);
                            exit(0);
                        }
                        else{
                            char *temp_str="";
                            char *trim_input_str=trim(input_str);
                            
                            // case "Hello":    str_after_case = "Hello"
                            char *str_after_case=substr(trim_input_str, 5, find_from_behind(trim_input_str, ":"));
                            
                            
                            // str_after_case -> 1 or 2
                            // change to  -----> 1 or x==2
                            str_after_case=replace_not_in_string(str_after_case, " or ", append(" or ", append(SWITCH_OBJECT, "==")));
                            str_after_case=replace_not_in_string(str_after_case, " and ", append(" and ", append(SWITCH_OBJECT, "==")));
                            
                            
                            str_after_case=trim(str_after_case);
                            int a=0;
                            for (; a<SPACE_OF_FIRST_SWITCH_SENTENCE; a++) {
                                temp_str=append(" ", temp_str);
                            }
                            // has defined if sentence
                            if (find(trim(SENTENCE_OF_SWITCH),"if")==0) {
                                
                                // else
                                if (strcmp(str_after_case, "default")==0) {
                                    temp_str=append(temp_str, "else:");
                                }
                                
                                // elif
                                else{
                                    temp_str=append(temp_str,"elif ");
                                    temp_str=append(temp_str, append(SWITCH_OBJECT, append("==", str_after_case)));
                                    temp_str=append(temp_str, ":");
                                    
                                }
                                
                            }
                            // have not defined if sentence
                            else{
                                temp_str=append(temp_str, "if ");
                                temp_str=append(temp_str, append(SWITCH_OBJECT, append("==", str_after_case)));
                                temp_str=append(temp_str, ":");
                            }
                            
                            
                            SENTENCE_OF_SWITCH=append(SENTENCE_OF_SWITCH,append(temp_str, "\n"));
                            REQUIRED_SPACE=CURRENT_SPACE+4;
                        }
                    }
                    // string in case sentence
                    else{
                        
                        char *temp_str=trim(input_str);
                        int a=0;
                        for (; a<CURRENT_SPACE-4; a++) {
                            temp_str=append(" ", temp_str);
                        }
                        SENTENCE_OF_SWITCH=append(SENTENCE_OF_SWITCH, temp_str);
                        SENTENCE_OF_SWITCH=append(SENTENCE_OF_SWITCH, "\n");
                    }
                    //
                }
            }
            //#####################################################################################
            char temp5[10];
            sprintf(temp5, "%d", can_run_basic_input);
            Var_changeValueOfVar(struct_settings , "can_run_basic_input", append("",temp5), "int");
            //##########################################################################################################
            //##########################################################################################################
            //##########################################################################################################
            //##########################################################################################################
            //// printf("can run basic input %d numOfSpaceAheadString %d required space %d\n",can_run_basic_input,numOfSpaceAheadString(input_str),space);
            if (can_run_basic_input == TRUE && (numOfSpaceAheadString(input_str) == 0 || REQUIRED_SPACE==CURRENT_SPACE)) {
                // printf("CAN RUN BASIC INPUT\n");
                char *input_temp = removeAheadSpace(input_str);
                if (strcmp(first_none_whitespace_token.TOKEN_STRING, "pass")==0) {
                    CAN_BREAK=TRUE;
                    CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK=FALSE;
                }
                else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "break")==0) {
                    CAN_BREAK=TRUE;
                    CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK=FALSE;
                }
                else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "continue")==0) {
                    CAN_CONTINUE=TRUE;
                    CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK=FALSE;
                    
                    //Var_changeValueOfVar(*struct_settings, "can_continue", "1", "int");
                }
                else if (strcmp(first_none_whitespace_token.TOKEN_STRING,"print")==0){
                    char* temp_output = Walley_Print(struct_var,FUNCTION_functions, substr(trim(input_str), 6, (int)strlen(trim(input_str))));
                    if (PRINT_IN_WHILE_OR_FOR_LOOP==TRUE) {
                        PRINT_STRING_AFTER_LOOP=append(PRINT_STRING_AFTER_LOOP, temp_output);
                    }
                    else{
                        printf("%s", temp_output);
                    }
                    
                    
                }
                else if (strcmp(first_none_whitespace_token.TOKEN_STRING,"println")==0){
                    char* temp_output = Walley_Println(struct_var,FUNCTION_functions, substr(trim(input_str), 8, (int)strlen(trim(input_str))));
                    if (PRINT_IN_WHILE_OR_FOR_LOOP==TRUE) {
                        PRINT_STRING_AFTER_LOOP=append(PRINT_STRING_AFTER_LOOP, temp_output);
                    }
                    else{
                        printf("%s", temp_output);
                    }
                    
                }
                // add new symbolic math support
                else if(strcmp(first_none_whitespace_token.TOKEN_STRING,"syms")==0){
                    char *sym_vars=substr(trim(input_str), 5, (int)strlen(trim(input_str)));
                    int num_of_vars=count_str(sym_vars, ",")+1;
                    int i=0;
                    for (; i<num_of_vars; i++) {
                        char *var_name=getParamAccordingToIndex(sym_vars,i);
                        if (Var_Existed(*struct_var, var_name)) {
                            Var_changeValueOfVar(struct_var, var_name, var_name, "sym");
                        }
                        else{
                            Var_addProperty(struct_var, var_name, var_name, "sym");
                        }
                    }
                }
                else if (input_temp[0] == '#' ||
                         strcmp(first_none_whitespace_token.TOKEN_STRING, "for") == 0 ||
                         strcmp(first_none_whitespace_token.TOKEN_STRING, "while") == 0 ||
                         strcmp(first_none_whitespace_token.TOKEN_STRING, "if") == 0 || strcmp(first_none_whitespace_token.TOKEN_STRING, "elif") == 0 || strcmp(first_none_whitespace_token.TOKEN_STRING, "else") == 0 ||
                         strcmp(first_none_whitespace_token.TOKEN_STRING, "def") == 0 ||
                         strcmp(first_none_whitespace_token.TOKEN_STRING,"class")==0
                         // new code here to support switch
                         || strcmp(first_none_whitespace_token.TOKEN_STRING,"switch")==0) {
                    
                    if (first_none_whitespace_token.TOKEN_STRING[0]=='#') {
                        printf("");
                    }
                    else{
                        Walley_Judge_Run_Anotation_For_While_Def_Class(struct_var, struct_settings, FUNCTION_functions,input_str,token);
                    }
                    
                }// ##################################### CHECK RETURN IN FUNCTION, CHECK WHETHER IT CAN RUN OR NOT
                else if (strcmp(first_none_whitespace_token.TOKEN_STRING,"return")==0){
                    printf("");
                }
                //#################### Basic Input To Run #############################
                else {
                    input_str = trim(input_str);
                    //#####################  Init class  #####################
                    if((find_not_in_string(input_str, "=")!=-1&&find_not_in_string(input_str,"(")!=-1&& (find_not_in_string(input_str, "=")<find_not_in_string(input_str,"(")) &&checkWhetherSameClassExistedFromVar(CLASS_LIST,trim(substr(input_str,find_not_in_string(input_str, "=")+1,find_not_in_string(input_str,"("))))==TRUE)
                       ) {
                        
                        //printf("#### Begin to initialize class ####\n");
                        // ## a is hello()
                        // ## a is instance_name
                        // ## hello() is __class__
                        // ## in hello("Hello"), "Hello" is parameter.
                        char *instance_name = substr(input_str, 0, find_not_in_string(input_str, "="));
                        char *__class__ = substr(input_str, find_not_in_string(input_str, "=") + 1, (int) strlen(input_str));
                        instance_name = trim(instance_name);
                        __class__ = trim(__class__);
                        char *parameter=substr(__class__,find(__class__,"(")+1,find_not_in_string(__class__,")"));
                        char *class_name=substr(__class__, 0, find(__class__,"("));
                        
                        
                        char *after_change=formatStringInClassWithExtendFromVar(*struct_var,CLASS_LIST,class_name,instance_name);
                        //printf("#### AFTER CHANGE\n|%s|\n####\n",after_change);
                        
                        Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file,FUNCTION_functions, after_change);
                        addInstanceNameToVar(&INSTANCE_NAMES_LIST,instance_name);
                        
                        
                        // For list instance like x[0]=a()
                        if (find(instance_name,"[")!=-1) {
                            int right=(int)strlen(instance_name)-1;
                            if (instance_name[right]==']') {
                                Walley_Update_Var_And_Var_Value_To_Var(struct_var, instance_name, toString(__class__));
                                //changeTheOneVarValueFromItsInitialOneFromVarForList(struct_var, substr(instance_name,0,right+1), toString(__class__));
                            }
                        }
                        
                        
                        //For dictionary like x{"A"}=a()
                        else if (find(instance_name,"{")!=-1) {
                            int right=(int)strlen(instance_name)-1;
                            if (instance_name[right]=='}') {
                                changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var, instance_name, toString(__class__));
                            }
                        }
                        
                        else{
                            Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file,FUNCTION_functions, append("syms ", instance_name));
                        }
                        // run init() function
                        // a.init()
                        if (find(after_change,".init(")!=-1) {
                            char *init=(char*)malloc(sizeof(char)*((int)strlen(instance_name)+1+(int)strlen(".init()")+(int)strlen(parameter)));
                            strcpy(init,instance_name);
                            strcat(init,".init(");
                            strcat(init,parameter);
                            strcat(init,")");
                            init[sizeof(char)*((int)strlen(instance_name)+(int)strlen(".init()")+(int)strlen(parameter))]=0;
                            
                            Walley_Run_One_Function_And_Return_Value_From_Var(init, struct_var, FUNCTION_functions);
                            //Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions,init);
                        }
                        //printf("After Initializing\n");
                        
                    }
                    //#################### import ####################
                    // Only Import File Module, Can not import the specific function from Module.
                    else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "import") == 0) {
                        // Now only support import a   does not support import a,b,c ... at same row
                        //printf("ENTER HERE1\n");
                        
                        
                        char *name_of_file_to_run = substr(input_str, find(input_str, "import ") + 7, (int) strlen(input_str));
                        name_of_file_to_run = removeAheadSpace(removeBackSpace(name_of_file_to_run));
                        
                        char *as_name="";
                        if(find_not_in_string(name_of_file_to_run," as ")!=-1){
                            as_name=substr(name_of_file_to_run,find_not_in_string(name_of_file_to_run," as ")+4,(int)strlen(name_of_file_to_run));
                            name_of_file_to_run=substr(name_of_file_to_run,0,find_not_in_string(name_of_file_to_run," as "));
                        } else {
                            as_name=name_of_file_to_run;
                        }
                        
                        name_of_file_to_run=trim(name_of_file_to_run);
                        as_name=trim(as_name);
                        
                        //printf("Name of file to run %s\n",name_of_file_to_run);
                        
                        /*
                         // I changed the code below on Dec 17
                         char *module_path=getModulePathFromDirectory(name_of_file_to_run,"./");
                         */
                        char *module_path=getModulePathFromDirectory(name_of_file_to_run,CURRENT_DIRECTORY);
                        
                        
                        if (module_path[(int)strlen(module_path)-1]=='p') {
                            printf("@@ |%s|\n",CURRENT_INPUT_STR);
                            printf("Can not import folder\nPlease try to import the file in that folder");
                            exit(0);
                        }
                        //printf("MODULE_PATH is %s\n",module_path);
                        
                        
                        // CHECK WHETHER IMPORTING CORRECTLY OR NOT
                        int length_of_module_path=(int)strlen(module_path);
                        int a=length_of_module_path-1;
                        for (; a>=0; a--) {
                            if (module_path[a]=='/') {
                                break;
                            }
                        }
                        char *final_module=substr(module_path, a+1, length_of_module_path);
                        final_module=substr(final_module, 0, find(final_module,"."));
                        
                        int length_of_name_of_file_to_run=(int)strlen(name_of_file_to_run);
                        a=length_of_name_of_file_to_run-1;
                        
                        //printf("FINAL MODULE IS %s\n",final_module);
                        for (; a>=0; a--) {
                            if (name_of_file_to_run[a]=='.') {
                                break;
                            }
                        }
                        char *final_module2=substr(name_of_file_to_run, a+1, length_of_name_of_file_to_run);
                        //printf("FINAL MODULE2 IS %s\n",final_module2);
                        if (strcmp(final_module2, final_module)!=0) {
                            printf("@@ |%s|\n",CURRENT_INPUT_STR);
                            printf("No File called %s found\nYou can only import .wy file\n",append(final_module2, ".wy"));
                            exit(0);
                        }
                        
                        
                        // Assign Value to AS_NAME
                        AS_NAME=append(AS_NAME, append(".", as_name));  // AS_NAME= ".a"  AS_NAME= ".a.b"
                        
                        
                        
                        /*
                         * I modified the code below on Dec 5
                         *
                         char *temp_file_to_run;
                         int length_of_name_of_file_to_run=(int)strlen(name_of_file_to_run);
                         if (name_of_file_to_run[length_of_name_of_file_to_run-1]=='y'&&name_of_file_to_run[length_of_name_of_file_to_run-2]=='w'&&name_of_file_to_run[length_of_name_of_file_to_run-3]=='.') {
                         temp_file_to_run=name_of_file_to_run;
                         } else {
                         temp_file_to_run=append(name_of_file_to_run, ".wy");
                         }*/
                        
                        
                        char *temp_file_to_run=module_path;
                        /*
                         // I changed the code below to fix the import problem on Dec 4 and also changed the function
                         // functionOrClassAddAheadName in order to fix a.y ('a' is as name) like problem
                         //char *content_of_file = functionOrClassAddAheadName(temp_file_to_run,as_name);
                         */
                        
                        /* I add new codes here on Dec 5 to solve importing problem
                         // This code below refresh the struct_var and FUNCTION_functions while can not update the class
                         // Update:::: IMPORTANT !!!!!!!
                         // It now can support class update*/
                        Walley_Update_Functions_And_Vars_While_Importing(temp_file_to_run, struct_var, FUNCTION_functions);
                        
                        
                        
                        //printf("Finish loading file %s\n",temp_file_to_run);
                        
                        // Remove the last value of AS_NAME
                        a=(int)strlen(AS_NAME)-1;
                        for (; a>=0; a--) {
                            if (AS_NAME[a]=='.') {
                                break;
                            }
                        }
                        if (a==0) {
                            AS_NAME="";
                        }else{
                            AS_NAME=substr(AS_NAME, 0, a);
                        }
                        //printf("AS_NAME IS %s\n",AS_NAME);
                        
                        
                    }
                    //This is also import
                    else if (strcmp(first_none_whitespace_token.TOKEN_STRING,"from")==0){
                        //printf("ENTER HERE2\n");
                        
                        //printf("\nNow input_str is |%s|\n",input_str);
                        input_str=replace_not_in_string(input_str, "*as", "* as");
                        
                        input_str=trim(input_str);
                        if(find_not_in_string(input_str," import ")==-1){
                            printf("@@ |%s|\n",CURRENT_INPUT_STR);
                            printf("Mistake occurred while importing\n no ' import ' found");
                            exit(0);
                        }
                        char *import_file=substr(input_str,5,find_not_in_string(input_str," import "));
                        char *import_module="";
                        char *as_name="";
                        
                        if(find_not_in_string(input_str," as ")!=-1){
                            import_module=substr(input_str,find_not_in_string(input_str," import ")+8,find_not_in_string(input_str," as "));
                            as_name=substr(input_str,find_not_in_string(input_str," as ")+4,(int)strlen(input_str));
                        } else {
                            import_module=substr(input_str,find_not_in_string(input_str," import ")+8,(int)strlen(input_str));
                            as_name=import_module;
                        }
                        import_file=trim(import_file);
                        import_module=trim(import_module);
                        as_name=trim(as_name);
                        
                        //printf("import_file %s\nimport_module %s\nas_name %s\n",import_file,import_module,as_name);
                        
                        /*
                         // I changed the code below on Dec 17
                         char *module_path=getModulePathFromDirectory(import_file,"./");*/
                        char *module_path=getModulePathFromDirectory(import_file,CURRENT_DIRECTORY);
                        CURRENT_DIRECTORY=substr(module_path, 0, find_from_behind(module_path, "/")+1);
                        
                        //printf("module_path --> %s\n",module_path);
                        
                        // Assign Value to AS_NAME
                        AS_NAME=append(AS_NAME, append(".", as_name));  // AS_NAME= ".a"  AS_NAME= ".a.b"
                        
                        
                        /*
                         * I modified the code below on Dec 5
                         *
                         int length_of_import_file=(int)strlen(import_file);
                         char *temp_file_to_run;
                         char *type=substr(import_file, length_of_import_file-3,length_of_import_file);
                         //printf("type is %s\n",type);
                         if (strcmp(type,".wy")!=0) {
                         temp_file_to_run=append(import_file, ".wy");
                         }
                         else{
                         temp_file_to_run=import_file;
                         }*/
                        
                        char *temp_file_to_run=module_path;
                        if (temp_file_to_run[(int)strlen(temp_file_to_run)-1]!='y') {
                            module_path=getModulePathFromDirectory(import_module, append(temp_file_to_run,"/"));
                            //printf("MODULE PATH %s\n",module_path);
                            temp_file_to_run=module_path;
                            
                            int a=(int)strlen(temp_file_to_run);
                            for (; a>=0; a--) {
                                if (temp_file_to_run[a]=='/') {
                                    break;
                                }
                            }
                            char *temp_file=substr(temp_file_to_run, a+1, (int)strlen(temp_file_to_run)-2);
                            //printf("temp_file is %s\n",temp_file);
                            
                            import_module=substr(import_module, find(import_module,temp_file)+(int)strlen(temp_file),(int)strlen(import_module));
                            
                            //printf("import_module is %s\n",import_module);
                        }
                        
                        
                        char *content_of_file="";
                        if (strcmp(import_module, "")==0) {
                            import_module="all";
                            as_name=import_module;
                            //printf("MODULE PATH %s\n",temp_file_to_run);
                            content_of_file = functionOrClassAddAheadName(temp_file_to_run,substr(AS_NAME, 1, (int)strlen(AS_NAME)));
                        }
                        // import all functions or classes from module
                        else if(strcmp(import_module,"all")==0||strcmp(import_module,"*")==0){
                            if(strcmp(import_module,as_name)==0){
                                // THIS PART IS CORRECT
                                as_name="";
                                content_of_file = getStringFromFile(temp_file_to_run);
                                
                                //printf("content_of_file:\n##########################################\n%s\n################################################\n",content_of_file);
                                
                            } else {
                                printf("@@ |%s|\n",CURRENT_INPUT_STR);
                                printf("Can not run\n from A import all/* as B\n");
                                exit(0);
                                //content_of_file = functionOrClassAddAheadName(temp_file_to_run,substr(AS_NAME, 1, (int)strlen(AS_NAME)));
                            }
                        }
                        else{
                            //content_of_file = getOneFunctionFromFileAndFormatItgetOneFunctionFromFile(temp_file_to_run,import_module,as_name);
                            //printf("Import module %s, as name %s\n",import_module,as_name);
                            content_of_file = getOneFunctionFromFileAndFormatItgetOneFunctionFromFile(temp_file_to_run,import_module,substr(AS_NAME, 1, (int)strlen(AS_NAME)));
                        }
                        
                        
                        //printf("content of file is |%s|\n", content_of_file);
                        Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file,FUNCTION_functions, content_of_file);
                        Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions,"#End Importing");
                        
                        // Remove the last value of AS_NAME
                        int a=(int)strlen(AS_NAME)-1;
                        for (; a>=0; a--) {
                            if (AS_NAME[a]=='.') {
                                break;
                            }
                        }
                        if (a==0) {
                            AS_NAME="";
                        }else{
                            AS_NAME=substr(AS_NAME, 0, a);
                        }
                    }
                    
                    // Disable Setmark and Goto
                    /*
                     //##################### setmark ##################
                     else if (find(removeAheadSpace(input_str), "setmark ") == 0) {
                     //// printf("#### Find setmark ####");
                     }//#################### goto ######################
                     else if (find(removeAheadSpace(input_str), "goto ") == 0) {
                     char *mark_name = substr(input_str, find(input_str, "goto ") + 5, (int) strlen(input_str));
                     //// printf("Mark Name :%s\n", mark_name);
                     mark_name = removeBackSpace(removeAheadSpace(mark_name));
                     //// printf("#### Find goto ####");
                     char *string_to_run;
                     if (strcmp("None", existing_file) == 0) {
                     string_to_run = getStringFromFile(temp_file_name);
                     } else {
                     string_to_run = getStringFromFile(existing_file);
                     }
                     //// printf("String in File is |%s|\n", getStringFromFile(temp_file_name));
                     char *setmark = malloc(sizeof (char) *((int) strlen("setmark ")+(int) strlen(mark_name)));
                     strcat(setmark, "setmark ");
                     strcat(setmark, mark_name);
                     if (find(string_to_run, setmark) == -1) {
                     printf("Mistake Occurred while calling function Walley_To_Mark\nMark not found");
                     exit(1);
                     } else {
                     string_to_run = substr(string_to_run, find(string_to_run, "setmark "), (int) strlen(string_to_run));
                     FILE *fp = fopen(temp_file_name, "w");
                     fputs("", fp);
                     fclose(fp);
                     //// printf("$$$ \n|%s|\n", string_to_run);
                     //clearTextInFile(temp_file_name);
                     writeStringToFile(temp_file_name, string_to_run);
                     writeStringToFile(temp_file_name, "\n");
                     run_goto = TRUE;
                     //Walley_Run_Second_Generation(struct_var,setting_file,temp_file_name,string_to_run);
                     }
                     }*/
                    //#####################  Eval  ###################
                    else if (TL_numOfTOKEN_CLASS(token, "W_ASSIGNMENT_OPERATOR")==1){
                        // else if (isExpression(input_str) == TRUE) {
                        // x=12
                        // or x,y=12,13
                        char *var_name=variableName(input_str);
                        // x,y=12,13 more than one var
                        if (find(var_name,",")!=-1) {
                            int num_of_space_ahead=numOfSpaceAheadString(input_str);
                            char *var_value=variableValue(input_str);
                            var_name=append(var_name, ",");
                            char *last_var_value=substr(var_value, find_from_behind(var_value, ",")+1, (int)strlen(var_value));
                            var_value=append(var_value, ",");
                            int num_of_comma=count_str(var_name, ",");
                            int a=0;
                            for (; a<num_of_comma; a++) {
                                int index_of_comma=find(var_name,",");
                                char *temp_var_name=substr(var_name, 0, index_of_comma);
                                var_name=substr(var_name, index_of_comma+1, (int)strlen(var_name));
                                
                                int index_of_comma2=find(var_value,",");
                                char *temp_var_value;
                                if (index_of_comma2==-1) {
                                    temp_var_value=last_var_value;
                                }
                                else{
                                    temp_var_value=substr(var_value, 0, index_of_comma2);
                                    var_value=substr(var_value, index_of_comma2+1, (int)strlen(var_value));
                                }
                                
                                
                                char *temp_temp="";
                                temp_var_name=trim(temp_var_name);
                                temp_var_value=trim(temp_var_value);
                                int b=0;
                                for (; b<num_of_space_ahead; b++) {
                                    temp_temp=append(temp_temp, " ");
                                }
                                temp_temp=append(temp_temp, temp_var_name);
                                temp_temp=append(temp_temp, "=");
                                temp_temp=append(temp_temp, temp_var_value);
                                Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions, temp_temp);
                            }
                        }
                        // x=13      only one var
                        else{
                            Walley_Eval_And_Update_Var_And_Value_To_Var(struct_var,FUNCTION_functions, input_str);
                        }
                    }                // ##############  Is Not Expression ######################
                    
                    
                    
                    //#####################  Mistake  ###################
                    else {
                        
                        // new code on Jan 6 to run
                        // <@Hello
                        // World>
                        // kind code
                        char *trim_input_str=trim(input_str);
                        
                        if (trim_input_str[0]=='<'&&trim_input_str[1]=='@'&&trim_input_str[(int)strlen(trim_input_str)-1]!='>') {
                            RUN_EXPRESSION_INCOMPLETE=TRUE;
                            RUN_EXPRESSION_TO_BE_COMPLETE=input_str;
                        }
                        else{
                            
                            // make print 'hello'----><print 'hello'>
                            int sentence_num=numOfSmallSentences(input_str);
                            if (sentence_num>1) {
                                if (input_str[0]!='<') {
                                    input_str=append("<@", input_str);
                                    input_str=append(input_str, ">");
                                }
                            }
                            
                            bool can_just_eval = TRUE;
                            int index_of_dot = find_not_in_string(input_str, ".");
                            if (index_of_dot > 0) {
                                char temp_char = input_str[index_of_dot - 1];
                                if (isalpha(temp_char)||temp_char=='_')
                                    can_just_eval = FALSE;
                            }
                            if (isFunctionFromVar(*FUNCTION_functions,input_str) == TRUE) {
                                //// printf("Yes it is function\n");
                                can_just_eval = FALSE;
                            }
                            if (can_just_eval) {
                                int length_of_input_str=(int)strlen(input_str);
                                if(input_str[length_of_input_str-1]=='+'&&input_str[length_of_input_str-2]=='+') {
                                    //printf("++\n");
                                    char *temp_var_name=substr(input_str, 0, length_of_input_str-2);
                                    temp_var_name=trim(temp_var_name);
                                    temp_var_name=append(temp_var_name, "=");
                                    char *temp_to_run=append(temp_var_name, input_str);
                                    Walley_Eval_And_Update_Var_And_Value_To_Var(struct_var,FUNCTION_functions,temp_to_run);
                                }
                                else if (input_str[length_of_input_str-1]=='-'&&input_str[length_of_input_str-2]=='-') {
                                    char *temp_var_name=substr(input_str, 0, length_of_input_str-2);
                                    temp_var_name=trim(temp_var_name);
                                    temp_var_name=append(temp_var_name, "=");
                                    char *temp_to_run=append(temp_var_name, input_str);
                                    Walley_Eval_And_Update_Var_And_Value_To_Var(struct_var,FUNCTION_functions,temp_to_run);
                                }
                                else{
                                    char *temp2=append("__temp__=",input_str);
                                    Walley_Eval_And_Update_Var_And_Value_To_Var(struct_var,FUNCTION_functions, temp2);
                                    Var_removeVar(struct_var, "__temp__");
                                }
                            }
                            else {
                                input_str = Walley_Substitute_Var_And_Function_Return_Value_From_Var(input_str, struct_var,FUNCTION_functions);
                                Walley_Eval_With_Variable_From_Var(*struct_var, input_str);
                            }
                            // printf("End\n");
                            
                        }
                    }
                }
                
            }
            if (continue_run == TRUE && run_goto == FALSE) {
                if (find_gang_gang == TRUE) {
                    Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file,FUNCTION_functions, substr(temp_input_str, find_not_in_string(temp_input_str, "\\n") + 2, (int) strlen(temp_input_str)));
                    
                } else {
                    Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file,FUNCTION_functions, substr(temp_input_str, find_not_in_string(temp_input_str, "\n") + 1, (int) strlen(temp_input_str)));
                }
            }
            /* Disable setmark and goto.....
             if (run_goto == TRUE) {
             //// printf("@@@@ Run GOTO @@@@\n");
             Walley_Run_For_Appointed_Var(struct_var, struct_settings, temp_file, existing_file, getStringFromFile(temp_file_name));
             }*/
        }
        
        
        // I add new Codes Here to solve Annotation Problem...... on Dec 6
        else if (continue_run == TRUE && run_goto == FALSE) {
            //// printf("continue run\n");
            if (find_gang_gang == TRUE) {
                Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file,FUNCTION_functions, substr(temp_input_str, find_not_in_string(temp_input_str, "\\n") + 2, (int) strlen(temp_input_str)));
                
            } else {
                //// printf("STRING LEFT is %s\n",substr(temp_input_str,find(temp_input_str,"\n")+1,(int)strlen(temp_input_str)));
                Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file,FUNCTION_functions, substr(temp_input_str, find_not_in_string(temp_input_str, "\n") + 1, (int) strlen(temp_input_str)));
            }
        }
    }
    
}


// new function here on Feb 3
void Walley_Run_For_Appointed_Var_String_List(struct VAR **struct_var, struct VAR **struct_settings, char ***save_to_file, char *existing_file, char ***FUNCTION_functions, char **input_str){
    int length=atoi(input_str[0]);
    int i=1;
    for (i=1; i<length; i++) {
        Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions, removeNFromBack(input_str[i]));
    }
}


//############################### Update Var and Var_Value to File#############################
// If var existed, then replace
// else create new one.

// Not modify
void Walley_Update_Var_And_Var_Value_To_Var(struct VAR **struct_var, char *var_name, char *var_value){
    // printf("#### Walley_Update_Var_And_Var_Value_To_File ####\n");
    // printf("var_name %s var_value %s\n",var_name,var_value);
    char *var_value_type = variableValueType(var_value);
    bool has_same_var_name = Var_Existed(*struct_var, var_name);
    
    if (has_same_var_name == TRUE) {

        char *previous_var_value=Var_getValueOfVar(*struct_var,var_name);
        char *previous_var_value_type=variableValueType(previous_var_value);
        
        if (strcmp(var_value_type, "list") == 0 && find(var_name, "[") == -1) {
            
            if (find_not_in_string(var_name, "{")!=-1) {
                changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var, var_name, var_value);
            }
            //printf("Value type List, change the whole value of list to file\n");
            else  if(strcmp(previous_var_value_type,"list")==0)
                //changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name, var_name, var_value);
            changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, var_name, var_value);
            else{
                //Walley_Remove_Variable_And_Value_From_File(file_var_name,var_name);
                Var_removeVar(struct_var, var_name);
                //writeVarNameAndVarValueIntoAppointedFileForList(file_var_name, var_name, var_value);
                writeVarNameAndVarValueIntoAppointedVarForList(struct_var, var_name, var_value);
            }
        }
        // x={a:1,b:2}, now the input is x={a:12}, so need to rewrite x.
        else if (strcmp(var_value_type, "dictionary") == 0 && find(var_name, "{") == -1) {
            if(strcmp(previous_var_value_type,"dictionary")==0){
                //changeTheWholeVarValueFromItsInitialOneFromFileForDictionary(file_var_name, var_name, var_value);
                changeTheWholeVarValueFromItsInitialOneFromVarForDictionary(struct_var, var_name, var_value);
            }
            else{
               // Walley_Remove_Variable_And_Value_From_File(file_var_name,var_name);
                Var_removeVar(struct_var, var_name);
                //writeVarNameAndVarValueIntoAppointedFileForDictionary(file_var_name, var_name, var_value);
                writeVarNameAndVarValueIntoAppointedVarForDictionary(struct_var, var_name, var_value);
            }
        }
                
        else {
            // Eg a[0] is one element of list a
            if (isListElementForVar(*struct_var, var_name)) {
                //changeTheOneVarValueFromItsInitialOneFromFileForList(file_var_name, var_name, var_value);
                changeTheOneVarValueFromItsInitialOneFromVarForList(struct_var, var_name, var_value);
            }
            // Eg a{"Hello"} is one element of dictionary
            else if (find_not_in_string(var_name, "{") != -1 && find_not_in_string(var_name, "}") != -1 && find_not_in_str_list_dict_parenthesis(var_name, ".")==-1) {
                //// printf("&&&&&&& Enter Here 1 \n");
                //changeTheOneVarValueFromItsInitialOneFromFileOrAddVarNameAndValueForDictionary(file_var_name, var_name, var_value);
               // printf("!!!!!!!!!!11111\n");
                changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var,var_name,var_value);
            }
            
            // x[0]=12, x is table
            // but x[0].a should not run code below
            else if (find_not_in_string(var_name,"[")!=-1&&find(var_name, ".")==-1){
                char *ahead=substr(var_name, 0, find_not_in_string(var_name, "["));
                char *string_index=substr(var_name, find_not_in_string(var_name, "["), (int)strlen(var_name));
                char *temp_var_value=Var_getValueOfVar(*struct_var, ahead);
                if (strcmp(variableValueType(temp_var_value), "table")==0) {
                    var_value=Table_addValueOrChangeValue(temp_var_value, string_index, var_value);
                    Var_changeValueOfVar(struct_var, ahead, var_value, "table");
                }
            }
            else {
                
                if(strcmp(previous_var_value_type,"dictionary")==0||strcmp(previous_var_value_type,"list")==0){
                    //Walley_Remove_Variable_And_Value_From_File(file_var_name,var_name);
                    Var_removeVar(struct_var, var_name);
                    //writeVarNameAndVarValueIntoAppointedFile(file_var_name, var_name, var_value, var_value_type);
                    Var_addProperty(struct_var, var_name, var_value, var_value_type);
                }
                //printf("&&&&&&& Enter Here 2 \n");
                //var_value = Walley_Substitute_Var_And_Function_Return_Value_From_File(var_value, file_var_name);
                //var_value = Walley_Eval_With_Variable_From_File(file_var_name, var_value);
                //var_value_type = variableValueType(var_value);
                else if(strcmp(var_value_type, "table")==0){
                    
                    Table_updateTableToStructVar(struct_var, var_name, var_value);
                }
                else{
                    Var_changeValueOfVar(struct_var, var_name, var_value, var_value_type);
                    
                }
            }
        }
    }
    
    
    // Does not have the same var name
    else {
        // Initialize List
        if (strcmp(var_value_type, "list") == 0) {
            
            if (find_not_in_string(var_name, "{")!=-1) {
                changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var, var_name, var_value);
            }
            else{
            
            //printf("Value type List, write the list and its value to file\n");
            //writeVarNameAndVarValueIntoAppointedFileForList(file_var_name, var_name, var_value);
            writeVarNameAndVarValueIntoAppointedVarForList(struct_var, var_name, var_value);
            }
        }
        // Initialize Dictionary
        else if (strcmp(var_value_type, "dictionary") == 0) {
            //// printf("Find Dictionary Type Value");
            //writeVarNameAndVarValueIntoAppointedFileForDictionary(file_var_name, var_name, var_value);
            
            if (find_not_in_string(var_name, "{")==-1) {
               // printf("ENTER HERE EHE\n");
                writeVarNameAndVarValueIntoAppointedVarForDictionary(struct_var, var_name, var_value);
            } else {
               // printf("ENTER HERE 2\n");
                changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var, var_name, var_value);
            }
            
            //printf("ENTER HERE EHE\n");
            //writeVarNameAndVarValueIntoAppointedVarForDictionary(struct_var, var_name, var_value);
        }            // Eg a{"Hello"} is one element of dictionary
        
        else if (strcmp(var_value_type, "table")==0){
            Table_updateTableToStructVar(struct_var, var_name, var_value);
        }
                                                                                                        // add new code here to fix x{'a'}.age=12 like problem
        else if (find_not_in_string(var_name, "{") != -1 && find_not_in_string(var_name, "}") != -1 && find_not_in_str_list_dict_parenthesis(var_name, ".")==-1) {
            //// printf("&&&&&&& Enter Here 1 \n");
            //changeTheOneVarValueFromItsInitialOneFromFileOrAddVarNameAndValueForDictionary(file_var_name, var_name, var_value);
            char *temp_var_name=substr(var_name, 0, find_not_in_string(var_name, "{"));
            if (Var_Existed(*struct_var, temp_var_name)==FALSE) {
                writeVarNameAndVarValueIntoAppointedVarForDictionary(struct_var, temp_var_name, "{}");
            }
            changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var,var_name,var_value);
        }
        
        // x[0]=12, x is table
        // x[0].a=12 x[0] is instance, so do not run code below
        else if (find_not_in_string(var_name,"[")!=-1 && find(var_name, ".")==-1){
            char *ahead=substr(var_name, 0, find_not_in_string(var_name, "["));
            char *string_index=substr(var_name, find_not_in_string(var_name, "["), (int)strlen(var_name));
            char *temp_var_value=Var_getValueOfVar(*struct_var, ahead);
            if (strcmp(variableValueType(temp_var_value), "table")==0) {
                var_value=Table_addValueOrChangeValue(temp_var_value, string_index, var_value);
                Var_changeValueOfVar(struct_var, ahead, var_value, "table");
            }
            else if(strcmp(variableValueType(temp_var_value), "list")==0){
                var_value=Table_addValueOrChangeValue(temp_var_value, string_index, var_value);
                Var_removeVar(struct_var, ahead);

                Var_addProperty(struct_var, ahead, var_value, "table");

            }
            
        }
        
        // Initialize simple value
        else {
            
            Var_addProperty(struct_var, var_name, var_value, var_value_type);
        }
    }
}

/*
 *This function is mainly about  Walley_Run_One_Function_And_Return_Value. get_var_from_file_name is you get parameter
 * value from the file that you appointed.
 */
//char *Walley_Run_One_Function_And_Return_Value(char *input_str){

// Not Modify....
char *Walley_Run_One_Function_And_Return_Value_From_Var(char *input_str,struct VAR **struct_var, char ***FUNCTION_functions){
    char *global_var_back_up=GLOBAL_VAR;

    char *function_in_def="[]";
    
    char* return_var_name="None";
    char* return_value = "";
    //// printf("Function is |%s|\n",input_str);
    
    input_str=removeBackSpace(input_str);
    input_str=removeAheadSpace(input_str);
    
    
    input_str=append(input_str, ":");
    
    //char *func_name=substr(input_str, find(input_str,"def")+3,find(input_str,"("));
    char *func_name=substr(input_str,0,find(input_str,"("));
    func_name=removeAheadSpace(func_name);
    func_name=removeBackSpace(func_name);
    
    
    //// printf("here1\n");
    
    // I changed the code below
    //char *parameter_str=substr(input_str, find(input_str,"(")+1,find(input_str,")"));
    //printf("input_str now is %s\n",input_str);
    char *parameter_str=substr(input_str, find(input_str,"(")+1,(int)strlen(input_str)-2);
    parameter_str=trim(parameter_str);
    int para_num;
    
    if(stringIsEmpty(parameter_str)){
        para_num=0;
        parameter_str="None";
    } else {
        para_num=count_str(parameter_str,",")+1;
    }
    
    char *func_name_temp;
    if(find_not_in_string(func_name,".")!=-1)
        func_name_temp=replace_not_in_string(func_name,".","_");
    else
        func_name_temp=func_name;
    
    
    
    struct VAR *TEMP_VAR_var;
    struct VAR *TEMP_VAR_settings;
    Var_initVar(&TEMP_VAR_var);
    Var_initVar(&TEMP_VAR_settings);

    
    Walley_Initialize_Var(&TEMP_VAR_var);
    Walley_Initialize_Settings(&TEMP_VAR_settings);
    
    
    /* for instance var//
    // copy instance var to TEMP_VAR_var
    // and then copy it back
     */
    copyInstanceValueToStructVar(*struct_var,&TEMP_VAR_var,INSTANCE_NAMES_LIST);

    
    char **TEMP_TEMP_FILE;Str_initStringList(&TEMP_TEMP_FILE);
    
    bool find_function = FALSE;
    bool begin = FALSE;
    bool finish = FALSE;
    bool finish_init_param = FALSE;
    
    char *temp_temp=append(func_name, ":");
    
    char *temp2=append(parameter_str, ",");
    
    
    parameter_str = temp2;
    
    int from_index = 0;
    char output[10000] = "";
    
    int row=0;
    int length_of_FUNCTION_functions=atoi((*FUNCTION_functions)[0]);
    
    char *global_var="[]";
    
    
    while (row<length_of_FUNCTION_functions) {
        char *arr=(*FUNCTION_functions)[row];
        //char one_line[1000];
        arr=removeNFromBack(arr);
        if (stringIsEmpty(trim(arr))) {
            row++;
            continue;
        }
       // printf("----arr----|%s|\n", arr);
       // printf("Finish init param %d\n", finish_init_param);
       // printf("temp_temp is %s\n",temp_temp);
        if (find_function == TRUE && strcmp("return", substr(trim(arr), 0, 6)) == 0) {
            
            //find_return=TRUE;
            // printf("\n\n\n\n\n--------Find Return--------\n");
            // printf("|%s|\n",arr);
            char *temp_arr=removeNFromBack(arr);
            Walley_Run_For_Appointed_Var(&TEMP_VAR_var, &TEMP_VAR_settings, &TEMP_TEMP_FILE, "FUNCTION", FUNCTION_functions,temp_arr);

                        
            bool can_get_return=atoi(Var_getValueOfVar(TEMP_VAR_settings, "can_run_basic_input"));
            

            if (can_get_return==FALSE) {
                row++;
                continue;
            }
            
            finish = TRUE;
            return_var_name = substr(arr, find(arr, "return") + 7, (int) strlen(arr));
            return_var_name =trim(return_var_name);
            if (return_var_name[(int) strlen(return_var_name) - 1] == '\n') {
                return_var_name = substr(return_var_name, 0, (int) strlen(return_var_name) - 1);
            }
            //printf("Return Var Name is :|%s|\n",return_var_name);
            break;
        }
        
        if (find(arr, temp_temp) != -1) {
            // printf("Find Function\n");
            //printf("arr is |%s|, temp_temp is |%s|\n",arr,temp_temp);
            int index_of_temp_temp=find(arr,temp_temp);
            if ((index_of_temp_temp>=1&&arr[index_of_temp_temp-1]!=' ') && index_of_temp_temp!=0) {
                
            }
            else{
            int row2=row;
            while (TRUE) {
                row=row2;
                row2=row2+1;
                bool find_another_function=FALSE;
                while (row2<length_of_FUNCTION_functions) {
                    if (find((*FUNCTION_functions)[row2],temp_temp)!=-1) {
                        
                        index_of_temp_temp=find((*FUNCTION_functions)[row2],temp_temp);
                        if ((index_of_temp_temp>=1&&(*FUNCTION_functions)[row2][index_of_temp_temp-1]!=' ') && index_of_temp_temp!=0) {
                            row2++;
                            continue;
                        }
                        
                        
                        row=row2;
                        find_another_function=TRUE;
                        break;
                    }
                    row2++;
                }
                if (find_another_function==FALSE) {
                    break;
                }
            }
                        
            find_function = TRUE;
            }
            
            
        }
        if (find_function == TRUE && find(arr, "#~End") == 0) {
            //// printf("Find End\n");
            finish = TRUE;
        }
        
        if (finish == TRUE) {
            //printf("Finish\n\n");
            break;
            
        }
        
        if(finish_init_param==TRUE && finish==FALSE){
            strcat(output,arr);
                
            char *temp=trim(arr);
            
            // For def function in a function
            // so this function is private function
            int current_space=numOfSpaceAheadString(arr);
            if (current_space==0 && find(arr,"def ")==0) {
                char *temp_func_name=substr(arr, find(arr,"def ")+4, find(arr, "("));
                function_in_def=listAppendOneElement(function_in_def, temp_func_name);
                
            }
            
            
            //printf("----After remove space---> %s ---\n",temp);
            if(isFunctionFromVar(*FUNCTION_functions,temp)){
                
                /*
                 // #### I delete the code below on Dec 6...
                 // #### This code has big problems
                printf("Is Function1111----> %s\n",arr);
                Walley_Run_One_Function_And_Return_Value_From_Var(temp,TEMP_VAR_var,FUNCTION_functions);
                printf("");
                 */
                
                                
                Walley_Run_For_Appointed_Var(&TEMP_VAR_var, &TEMP_VAR_settings, &TEMP_TEMP_FILE, "FUNCTION", FUNCTION_functions, arr);
            }
            else{
                //printf("*************** GO THERE *************** %s\n",arr);
                // if is_instance_value is true, save like Rohit.age to VAR_var
                //bool is_instance_value=FALSE;
                bool is_global_var=FALSE;
                //bool is_expresssion=FALSE;
                //char *user;
                /*
                if(isExpression(arr)){
                    is_expresssion=TRUE;
                    //printf("********* %s IT IS EXPRESSION ********\n",arr);
                    char *var_name2=variableName(arr);
                    char *user;
                    if(find_not_in_string(var_name2,".")!=-1){
                        user=substr(var_name2,0,find_not_in_string(var_name2,"."));
                        bool is_instance=checkWhetherSameInstanceExistedFromVar(INSTANCE_NAMES_LIST,user);
                        if(is_instance)
                            is_instance_value=TRUE;
                        else
                            is_instance_value=FALSE;
                    }
                    
                    
                    int x=0;
                    int num_of_element_in_global_var=valueNumOfList(GLOBAL_VAR);
                    for (; x<num_of_element_in_global_var; x++) {
                        char *element=valueOfListAtIndex(GLOBAL_VAR, x);
                        if (strcmp(element, var_name2)==0) {
                            is_global_var=TRUE;
                            break;
                        }
                    }
                    
                }
                
                // check like x.stack.push(4)
                else{
                    if (find(arr,".")==-1) {
                        is_instance_value=FALSE;
                    }
                    else{
                        user=substr(arr, 0, find(arr, "."));
                        user=trim(user);
                        if (checkWhetherSameInstanceExistedFromVar(INSTANCE_NAMES_LIST, user)==TRUE) {
                            is_instance_value=TRUE;
                        }
                        else{
                            is_instance_value=FALSE;
                        }
                    }
                }
                */
                //if(is_instance_value==FALSE){
                   
                    // begin to define global var
                    if (find(trim(arr),"global ")==0) {
                        char *rest=trim(substr(trim(arr),7,(int)strlen(trim(arr))));
                        int num_of_var=count_str(rest, ",")+1;
                        int x=0;
                        for (; x<num_of_var; x++) {
                            global_var=list_append(global_var, getParamAccordingToIndex(rest,x));
                        }
                        GLOBAL_VAR=global_var;
                    }
                    
                    // is global var
                    else if (is_global_var==TRUE){
                        Walley_Run_For_Appointed_Var(&TEMP_VAR_var, &TEMP_VAR_settings, &TEMP_TEMP_FILE, "FUNCTION",FUNCTION_functions,arr);
                        char *var_name3 = variableName(arr);
                        char *var_value3 = Var_getValueOfVar(TEMP_VAR_var, var_name3);
                        
                        Walley_Update_Var_And_Var_Value_To_Var(&VAR_var, var_name3, var_value3);
                    }
                    else{
                        // printf("ELSE--->|%s|\n",(*FUNCTION_functions)[row]);
                        Walley_Run_For_Appointed_Var(&TEMP_VAR_var,&TEMP_VAR_settings,&TEMP_TEMP_FILE,"FUNCTION",FUNCTION_functions,arr);
                    }
                    
                //}
                /*
                else{
                    // printf("************ IT IS INSTANCE VALUE ************");
                    // printf("************ %s **********\n",arr);
                    if (is_expresssion==TRUE) {
                        Walley_Run_For_Appointed_Var(&TEMP_VAR_var, &TEMP_VAR_settings, &TEMP_TEMP_FILE, "FUNCTION",FUNCTION_functions,arr);
                        char *var_name3 = variableName(arr);
                        char *var_value3 = Var_getValueOfVar(TEMP_VAR_var, var_name3);
                        
                        // printf("VAR_NAME %s VAR_VALUE %s\n",var_name3,var_value3);
                        Walley_Update_Var_And_Var_Value_To_Var(&VAR_var, var_name3, var_value3);
                        
                        //Var_PrintVar(VAR_var);
                    }
                    
                    
                    
                    // x.stack.push()
                    else{
                        Walley_Run_For_Appointed_Var(&TEMP_VAR_var, &TEMP_VAR_settings, &TEMP_TEMP_FILE, "FUNCTION", FUNCTION_functions, arr);
                    }
                    
                    
                    
                    
                }
                 */
            }
            
        }
        
        if (begin == TRUE && finish_init_param == FALSE) {
            //printf("Initialize parameters\n");
            //printf("param str is %s\n",parameter_str);
            //printf("PARAMETER is %s\n", parameter_str);
            //printf("arr %s\n",arr);
            // 12,13,12,
            //printf("Enter Here\n");
            char *arr_arr;
            arr_arr=removeNFromBack(arr);
            arr_arr = removeBackSpace(arr_arr);
            
            if (find_not_in_string(removeAheadSpace(arr_arr), "##Finish Init Params")==0) {
                finish_init_param=TRUE;
                //// printf("finish_init_param\n")
                row++;
                continue;
            }
            
            
            
            if (stringIsEmpty(substr(arr_arr, find_not_in_string(arr_arr, "=")+1, (int)strlen(arr_arr)))==FALSE
               // &&checkWhetherSameVarNameExistsFromFile(file_var_temp_name, substr(arr_arr, 0, find_not_in_string(arr_arr, "=")))==FALSE) {
                 &&Var_Existed(TEMP_VAR_var, substr(arr_arr, 0, find_not_in_string(arr_arr, "=")))==FALSE) {
                
                //printf("ENTER HERE1\n");
                
                Walley_Run_For_Appointed_Var(&TEMP_VAR_var, &TEMP_VAR_settings,&TEMP_TEMP_FILE,"FUNCTION",FUNCTION_functions,arr_arr);
            }
            
            if (strcmp(parameter_str, "None,") == 0) {
                //// printf("Params is None\n");
                //finish_init_param = TRUE;
                row++;
                continue;
            }
            
            
            char *var_value;
            //if(find_from_index_not_in_string(parameter_str, ",",from_index+1)==-1)
            if(find_from_index_not_in_str_list_dict(parameter_str, ",",from_index+1)==-1){
                // printf("==-1\n");
                //// printf("parameter_str |%s|,from_index %d\n",parameter_str,from_index);
                row++;
                continue;
            }
            else{
                var_value = substr(parameter_str, from_index, find_from_index_not_in_str_list_dict(parameter_str, ",", from_index + 1));
            }
            // It is not expression
            if (find_not_in_string(var_value, "=")==-1) {
                // I add this row here on 11 15/ in order to solve initiation problem
                var_value=Walley_Substitute_Var_And_Function_Return_Value_From_Var(var_value, struct_var,FUNCTION_functions);
                //
                
                var_value=Walley_Eval_With_Variable_From_Var(*struct_var, var_value);
                arr_arr = substr(arr_arr, 0, find_not_in_string(arr_arr, "=")+1);
                if (stringIsDigit(var_value) == FALSE &&stringIsFraction(var_value)==FALSE && strcmp(variableValueType(var_value), "string") != 0
                    &&strcmp(variableValueType(var_value), "list") != 0
                    &&strcmp(variableValueType(var_value), "dictionary") != 0) {
                    var_value = Var_getValueOfVar(*struct_var, var_value);
                }
                //strcat(arr_arr, var_value);
                arr_arr=append(arr_arr, var_value);
            }
            // It is expression
            else{
                arr_arr=var_value;
            }
            //printf("var value2 is %s\n",var_value);
            //printf("arr_arr -----> %s\n",arr_arr);
            
            
            
            strcat(output, arr_arr);
            strcat(output, substr(parameter_str, from_index, find_from_index_not_in_string(parameter_str, ",", from_index + 1)));
            strcat(output, "\n");
            
            
            //Walley_Run(arr_arr);
            //Walley_Run_For_Appointed_Var("__walley_temp__.wy","__walley_settings_temp__.wy",arr_arr);
            if ((int) strlen(removeAheadSpace(removeBackSpace(arr_arr))) != 0){
                Walley_Run_For_Appointed_Var(&TEMP_VAR_var, &TEMP_VAR_settings,&TEMP_TEMP_FILE,"FUNCTION",FUNCTION_functions,arr_arr);
            }
            
            from_index = find_from_index_not_in_str_list_dict(parameter_str, ",", from_index + 1) + 1;
            
            /*
             if ((from_index + 1) >= (int) strlen(parameter_str)) {
             finish_init_param = TRUE;
             //printf("finish init param\n");
             }*/
        }
        
        if (find_function == TRUE && find(arr, "#~Begin") == 0) {
            //printf("Begin to initialzie parameters\n");
            begin = TRUE;
        }
        row++;
    }
    
    

    
    if(strcmp(return_var_name,"None")==0){
        //// printf("------Return None------\n");
        return_value="None";
    } else {
        //printf("Enter Else\n");
        return_var_name=Walley_Substitute_Var_And_Function_Return_Value_From_Var(return_var_name,&TEMP_VAR_var,FUNCTION_functions);
        
        // I fixed the code below on Dec 6
        return_value=Walley_Eval_With_Variable_From_Var(*struct_var, return_var_name);
        //return_value="Hi";
    }
    
    if (find_function==FALSE) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Mistake occurred whiling call function Walley_Run_One_Function_And_Return_Value\n");
        printf("Function |%s| is not found\n Exit....\n",input_str);
        exit(0);
    }
    
    
    
    Walley_Run_For_Appointed_Var(&TEMP_VAR_var, &TEMP_VAR_settings, &TEMP_TEMP_FILE, "FUNCTION", FUNCTION_functions,"#end function");
    
    
    //printf("Now the functions in def is %s\n",function_in_def);
    int num_of_temp_func=valueNumOfList(function_in_def);
    int a=0;
    
   
    while (a<num_of_temp_func) {
        char *temp_func_name=toCString(valueOfListAtIndex(function_in_def, a));
        //printf("##temp_func_name is %s\n",temp_func_name);
        deleteOneFunctionFromBehind(FUNCTION_functions, temp_func_name);
        a++;
    }
    
    copyInstanceValueBackToVar(TEMP_VAR_var, struct_var,INSTANCE_NAMES_LIST);
    function_in_def="";
    GLOBAL_VAR=global_var_back_up;
    
    return return_value;
}

/*
 * ("add 1 2","add(num1,num2)|add num1 num2")
 */
char *Walley_Translate_To_Function_From_Var(char *input_str, char *best_match_sentence, struct VAR **struct_var){
    //printf("#### Walley_Translate_To_Function_From_Var ####\n");
    //printf("best match sentence |%s|, input_str |%s|\n",best_match_sentence,input_str);
    int index_of_gang=find(best_match_sentence, "|");
    if (index_of_gang==-1) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Mistake occurred while calling function Walley_Translate_To_Function\n input_str |%s|, best_match sentence error, |%s|\n",input_str,best_match_sentence);
        printf("it should be in format function|expression \n");
        exit(0);
    }
    char *function=substr(best_match_sentence, 0, index_of_gang);
    
    //if (stringIsEmpty(substr(function, find_not_in_str_list_dict(function, "(")+1, find_not_in_str_list_dict(function, ")")))==TRUE) {
    //    return function;
    //}
    
    char *expression=substr(best_match_sentence, index_of_gang+1, (int)strlen(best_match_sentence));
    expression=trim(expression);
    int num_of_small_sentence=numOfSmallSentences(input_str);
    int i=0;
    char *output=append(function, "(");
    
    
    for (i=0; i<num_of_small_sentence; i++) {
        char *sentence_at_input_str=sentenceAtIndexOfString(input_str, i);
        char *sentence_at_expression=sentenceAtIndexOfString(expression, i);
        
        
        // printf("@@ %s @@ %s\n",sentence_at_input_str,sentence_at_expression);
                                                                    // New code here on Dec 6
        if (strcmp(sentence_at_expression, sentence_at_input_str)!=0||Var_Existed(*struct_var, sentence_at_input_str)) {
            output=append(output, sentence_at_expression);
            output=append(output, "=");
            
            // New code here
           // if (Var_Existed(struct_var, sentence_at_input_str)) {
                
                sentence_at_input_str=Var_getValueOfVar(*struct_var, sentence_at_input_str);
           // }
            
            output=append(output, sentence_at_input_str);
            if (i!=num_of_small_sentence-1) {
                output=append(output, ",");
            }
            // printf("@@@ %s @@@ %s\n",sentence_at_input_str,sentence_at_expression);
        }
    }
    output=append(output, ")");
    
    //// printf("WALLEY TRANSLATION |%s| |%s| |%s|\n",input_str,best_match_sentence,output);
    return output;
}

// var_value is "shd101wyy123/shd101wyy", slice is [x.find("/"):]
char *Walley_Slice(char *var_value, char *slice,struct VAR **struct_var, char ***FUNCTION_functions){
    slice = trim(slice);
    
    if (strcmp(variableValueType(var_value), "table")==0) {
        return Table_valueOfTableAtStringIndex(var_value, slice);
    }
    
    int count=count_str(slice, "][");
    int a=0;
    for (; a<count; a++) {
        int index=find(slice, "][");
        char *temp_slice=substr(slice, 0, index+1);
        slice=substr(slice, index+1, (int)strlen(slice));
        var_value=Walley_Slice(var_value, temp_slice, struct_var, FUNCTION_functions);
    }
    
    
    
    char *inside = substr(slice, 0 + 1, (int) strlen(slice) - 1);
    inside=trim(inside);
    //x[1:2]
    if (find_not_in_string(inside, ":") != -1) {
        int num1;
        int num2;
        if(inside[0]==':'&&inside[(int)strlen(inside)-1]==':'){
            return "None";
        }
        else if (inside[0]==':'&&inside[(int)strlen(inside)-1]!=':'){
            num1=0;
            //num2=atoi();
            //num1=Walley_Eval(num1);
            num2=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(substr(slice, find_not_in_string(slice, ":") + 1, (int)strlen(slice)-1), struct_var, FUNCTION_functions));
            return sliceOnlyIncludeLeftSide(var_value,num1,num2);
        }
        else if (inside[0]!=':'&&inside[(int)strlen(inside)-1]==':'){
            //char *type=variableValueType(input_str);
            //num1=atoi(substr(slice, 1, find_not_in_string(slice, ":")));
            num1=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(substr(slice, 1, find_not_in_string(slice, ":")),struct_var,FUNCTION_functions));
            //num2=Walley_Eval(num2);
            if(strcmp(variableValueType(var_value),"list")==0){
                num2=valueNumOfList(var_value);
            }
            else if (strcmp(variableValueType(var_value),"string")==0){
                num2=(int)strlen(toCString(var_value));
            }
            return sliceOnlyIncludeLeftSide(var_value, num1, num2);
        }
        else {
            //num1 = atoi(substr(slice, 1, find(slice, ":")));
            //num2 = atoi(substr(slice, find(slice, ":") + 1, right));
            num1=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(substr(slice, 1, find_not_in_string(slice, ":")),struct_var,FUNCTION_functions));
            num2=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(substr(slice, find_not_in_string(slice, ":") + 1, (int)strlen(slice)-1),struct_var,FUNCTION_functions));
            return sliceOnlyIncludeLeftSide(var_value, num1, num2);
        }
        
        
    }
    
    // I stop using this kind of slice on Jan 3 2013
    // x[1,2]
    /*
    else if (find_not_in_string(inside, ",") != -1) {
        int num1;
        int num2;
        if(inside[0]==','&&inside[(int)strlen(inside)-1]==','){
            return "None";
        }
        else if (inside[0]==','&&inside[(int)strlen(inside)-1]!=','){
            num1=0;
            //num2=atoi(substr(slice, find(slice, ",") + 1, right));
            //num1=Walley_Eval(num1);
            num2=atoi(Walley_Eval(substr(slice, find_not_in_string(slice, ",") + 1, (int)strlen(slice)-1)));
            return sliceOnlyIncludeLeftSide(input_str,num1,num2);
        }
        else if (inside[0]!=','&&inside[(int)strlen(inside)-1]==','){
            char *type=variableValueType(input_str);
            //num1=atoi(substr(slice, 1, find(slice, ",")));
            if(strcmp(type,"list")==0){
                num2=valueNumOfList(input_str);
            }
            else if (strcmp(input_str,"string")==0){
                num2=(int)strlen(toCString(input_str));
            }
            num1=atoi(Walley_Eval(substr(slice, 1, find_not_in_string(slice, ","))));
            //num2=Walley_Eval(num2);
            return sliceOnlyIncludeLeftSide(input_str, num1, num2);
        }
        else {
            //num1 = atoi(substr(slice, 1, find(slice, ",")));
            //num2 = atoi(substr(slice, find(slice, ",") + 1, right));
            num1=atoi(Walley_Eval(substr(slice, 1, find_not_in_string(slice, ","))));
            num2=atoi(Walley_Eval(substr(slice, find_not_in_string(slice, ",") + 1, (int)strlen(slice)-1)));
            return sliceOnlyIncludeLeftSide(input_str, num1, num2);
        }
        
        
    }
    */
    //x[0]
    else {
        //printf("here\n");
        char *num_str = substr(slice, 1, (int)strlen(slice)-1);
        //printf("num_str %s\n",num_str);
        int num=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(num_str,struct_var,FUNCTION_functions));
        
        if (strcmp("string", variableValueType(var_value)) == 0) {
            //// printf("it is string\n");
            //// printf("num is %d\n",num);
            var_value = toCString(var_value);
            char *output = substr(var_value, num, num + 1);
            //// printf("return is %s\n",toString(output));
            return toString(output);
        } else if (strcmp("list", variableValueType(var_value)) == 0) {
            //// printf("it is list\n");
            char *output = (char*)malloc(sizeof(char)*1000);
            
            char *value_at_index = valueOfListAtIndexString(var_value, slice);
            strcpy(output, value_at_index);
            
            
            //strcat(output, "]");
            int i = 0;
            char *output2 = (char*)malloc(sizeof (char) *((int) strlen(output) + 1));
            for (i = 0; i < (int) strlen(output); i++) {
                output2[i] = output[i];
            }
            output2[(int) strlen(output)] = 0;
            return output2;
            
        }
        else{
            printf("@@ |%s|\n",CURRENT_INPUT_STR);

            printf("Mistake occurred while calling function slice\nIt is not a slice or value type wrong\n");
            printf("If you want use dictionary, please try x{'a'} like expression\n");
            exit(0);
        }
    }    
    
}


// Not Modify....
char *Walley_Substitute_Var_And_Function_Return_Value_From_Var(char* input_str,struct VAR **struct_var, char ***FUNCTION_functions){//, char *file_function_name){
    // printf("#### Walley_Substitute_Var_And_Function_Return_Value_From_File ####\n");
    //printf("$$$ input str is |%s| ####\n",input_str);
    
        
    if(stringIsAlphaAndSlash(input_str)){
        return Var_getValueOfVar(*struct_var, input_str);
    }
    else if (stringIsDigit(input_str)){
        return input_str;
    }
    
    
    int i=0;
    int begin=0;  //begin of { and [
    int end = 0; // end of } and ]
    
    //###############################################################################################################
    //###############################################################################################################
    //###############################################################################################################
    //################################# New Expression code #########################################################
    //###############################################################################################################
    //###############################################################################################################
    
    
    while (count_str_not_in_string(input_str, "<@")!=0) {
        
        begin = find_from_behind_not_in_string(input_str, "<@");
        end = find_from_index_not_in_string(input_str, ">", begin + 1);
        
        char *replace_str = substr(input_str, begin + 2, end); //<@hello> get hello
        if (stringIsEmpty(replace_str) == FALSE) {
            
            char *with_str = Walley_Translate_To_Function_From_Var(replace_str, bestMathSentenceForExpression(replace_str,WALLEY_EXPRESSION),struct_var);
            
            
            
            input_str = replace_from_index_to_index(input_str, substr(input_str, begin, end+1), with_str, begin, end+1);
            
            
        } else {
            char *with_str="";
            input_str = replace_from_index_to_index(input_str, substr(input_str, begin, end+1), with_str, begin, end+1);
        }
    }
    
    //printf("@@@@@@AFTER TRANSLATION, |%s|\n",input_str);
    //###############################################################################################################
    //###############################################################################################################
    //###############################################################################################################
    //###############################################################################################################

    
    
    for (i = 0; i < (int) strlen(input_str); i++) {
        
        
        if (charIsInString(input_str, i) == FALSE && input_str[i] == '{') {
            //printf("______------______FIND {}\n");
            begin = i;
            end = find_from_index_not_in_string(input_str, "}", begin + 1);
            //if (end != -1) {
            char *check = substr(input_str, begin, end + 1);
            while (count_str_not_in_string(check, "{") != count_str_not_in_string(check, "}")) {
                end = find_from_index_not_in_string(input_str, "}", end + 1);
                check = substr(input_str, begin, end + 1);
            }
            char *replace_str = substr(input_str, begin + 1, end); //from x{i} get i
            if (stringIsEmpty(replace_str) == FALSE) {
                if (finishFindingVarAndFunction(replace_str) == FALSE) {
                    char *with_str = Walley_Substitute_Var_And_Function_Return_Value_From_Var(replace_str, struct_var,FUNCTION_functions);
                    input_str = replace_from_index_to_index(input_str, replace_str, with_str, begin + 1, end);
                }
            }
            //} //printf("Replace %s with %s, the input_str is %s\n",replace_str,with_str,input_str);
        }
        
        if (charIsInString(input_str, i) == FALSE && input_str[i] == '[') {
            
            begin = i;
            end = find_from_index_not_in_string(input_str, "]", begin + 1);
            //if (end != -1) {
            char *check = substr(input_str, begin, end + 1);
            //if(end!=-1){
            while (count_str_not_in_string(check, "[") != count_str_not_in_string(check, "]")) {
                end = find_from_index_not_in_string(input_str, "]", end + 1);
                check = substr(input_str, begin, end + 1);
            }
            //}
            char *replace_str = substr(input_str, begin + 1, end);
            if (stringIsEmpty(replace_str) == FALSE) {
                if (finishFindingVarAndFunction(replace_str) == FALSE && find_not_in_string(replace_str, ":")==-1) {//from x{i} get i
                    char *with_str = Walley_Substitute_Var_And_Function_Return_Value_From_Var(replace_str, struct_var,FUNCTION_functions);
                    input_str = replace_from_index_to_index(input_str, replace_str, with_str, begin + 1, end);
                }
            }
            //}
        }
        if (charIsInString(input_str, i) == FALSE && input_str[i] == '(') {
            begin = i;
            end = find_from_index_not_in_string(input_str, ")", begin + 1);
            //if (end != -1) {
            char *check = substr(input_str, begin, end + 1);
            while (count_str_not_in_string(check, "(") != count_str_not_in_string(check, ")")) {
                end = find_from_index_not_in_string(input_str, ")", end + 1);
                check = substr(input_str, begin, end + 1);
            }
            char *replace_str = substr(input_str, begin + 1, end);
            if (stringIsEmpty(replace_str) == FALSE) {
                if (finishFindingVarAndFunction(replace_str) == FALSE) {//from x{i} get i
                    char *with_str = Walley_Substitute_Var_And_Function_Return_Value_From_Var(replace_str, struct_var,FUNCTION_functions);
                    if (strcmp(with_str, replace_str)==0) {
                        continue;
                    }
                    
                   // with_str=Walley_Eval_All_From_Var(struct_var, with_str);
                    input_str = replace_from_index_to_index(input_str, replace_str, with_str, begin + 1, end);
                   // printf("here\n");
                }
            }
            
        }

    }
    
    
    
    
    struct TOKEN *token=Walley_Lexica_Analysis(input_str);
    token=TL_returnTokenListWithoutWhitespaces(token);
    int length_of_token=TL_length(token);
    //TOKEN_PrintTOKEN(token);
    
    if (length_of_token==2) {
        // string
        if (strcmp("W_STRING", token[1].TOKEN_CLASS)==0)
            return input_str;
        // number
        else if(strcmp("W_NUMBER", token[1].TOKEN_CLASS)==0)
            return input_str;
        
    }

    
    
    // printf("AFTER REPLACE THE THING IN [] AND {}\nTHE INPUT IS |%s|\n",input_str);
    
    // I add new code here to solve print(input_str='1') problem
    // input_str='1' should not be run
    if (isExpression(input_str)) {
        // printf("%s IT IS EXPRESSION\n",input_str);
        char *var_name=variableName(input_str);
        char *var_value=variableValue(input_str);

        var_value=Walley_Substitute_Var_And_Function_Return_Value_From_Var(var_value, struct_var,FUNCTION_functions);
        char *output=append(var_name, "=");
        output=append(output, var_value);
        return output;
    }
    
    //// printf("input str is :%s\nlength is %d\n",input_str,(int)strlen(input_str));
    //printf("Required File is %s\n",file_var_name);
    
    
    //bool find_alpha=FALSE;
    //bool finish_find_var=FALSE;
    //bool find_function=FALSE;
    
    begin=0;
    end=(int)strlen(input_str);
    i=0;
    
    
    char *output=(char*)malloc(sizeof(char)*((int)strlen(input_str)+1));
    //char output[1000]="";
    for(i=0;i<(int)strlen(input_str);i++){
        output[i]=input_str[i];
    }
    output[(int)strlen(input_str)]=0;
    
    
    
    
    //bool has_var=FALSE;
    
    struct TOKEN *output_token;
    TL_initTokenList(&output_token);
    
    struct TOKEN temp_token;
    
    i=1;
    for (; i<length_of_token; i++) {
        
        char *token_class=token[i].TOKEN_CLASS;
        char *token_string=token[i].TOKEN_STRING;
        struct TOKEN next=TOKEN_nextToken(token, i);
        
        
        if (strcmp(token_class, "W_ID")==0) {
            
            // it is slice
            // x[0]
            // x[0][0]
            if (strcmp(next.TOKEN_CLASS,"W_LIST_TABLE")==0||next.TOKEN_STRING[0]=='.') {
                
                SAVE_VAR_NAME_TO_CHECK_WHETHER_IT_IS_INSTANCE=token_string;
                
                char *var_value=Var_getValueOfVar(*struct_var, token_string);
                i=i+1;
                Walley_Next(token, &i, &var_value, struct_var, *FUNCTION_functions);
                i=i-1;
                temp_token.TOKEN_STRING=var_value;
            }
            
            // it is just var
            else if (find(token[i].TOKEN_STRING,"(")==-1) {
                temp_token.TOKEN_STRING=Var_getValueOfVar(*struct_var, token_string);
            }
            
            // it is function
            else{
                
                char *function = token_string;
                
                char *return_value;
                
                char *func_name=substr(function, 0, find(function,"("));
                
                //int index_of_dot=find_from_behind_not_in_str_list_dict_parenthesis(function, ".");
                /*
                if (find(substr(function, 0, find(function, "(")), ".") != -1 && charIsInString(function, index_of_dot) == FALSE) {
                    //// printf("It is instance function\n");
                    char *user = substr(function, 0, index_of_dot);
                    //printf("user---> %s  func---> %s\n",user,function);
                    bool instance_existed = checkWhetherSameInstanceExistedFromVar(INSTANCE_NAMES_LIST, user);
                    bool var_existed = Var_Existed(*struct_var,user);
                    
                    bool only_var_existed = var_existed;
                    
                    char *user_value=Walley_Substitute_Var_And_Function_Return_Value_From_Var(user, struct_var,FUNCTION_functions);
                    char *function_temp=replace_not_in_string(function, user, user_value);
                    
                    
                    if (strcmp(variableValueType(user_value), "string")==0||strcmp(variableValueType(user_value), "list")==0) {
                        var_existed=TRUE;
                    }
                    
                    if (instance_existed == FALSE && var_existed==TRUE){
                        if (only_var_existed==TRUE) {
                            return_value=Walley_Run_Special_Function_From_Var(function, struct_var);
                        } else {
                            return_value = Walley_Run_Special_Function_From_Var(function_temp, struct_var);
                        }
                    }
                    else {
                        return_value = Walley_Run_One_Function_And_Return_Value_From_Var(function, &VAR_var,FUNCTION_functions);
                        
                    }
                    
                }
                */
                //################### Embeded Function ###############################################################
                if (strcmp(func_name, "int") ==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = to_int(temp_value);
                } else if (strcmp(func_name, "double") ==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = to_double(temp_value);
                } else if (strcmp(func_name, "d") ==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = to_decimal(temp_value);
                } else if (strcmp(func_name, "f") ==0) {
                    WALLEY_SUBSTITUTION_CAN_JUST_EVAL_IN_THE_END=FALSE;
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = eval_for_fraction_with_alpha(temp_value);
                    return_value = to_fraction(temp_value);
                    WALLEY_SUBSTITUTION_CAN_JUST_EVAL_IN_THE_END=TRUE;
                } else if (strcmp(func_name, "nstr") ==0) {
                    //// printf("Find nstr(");
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = to_nstr(temp_value);
                } else if (strcmp(func_name, "str")==0) {
                    
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = to_string(temp_value);
                    
                    //printf("HERE return_value %s\n",return_value);
                }
                //#####################  println  ###################
                else if (strcmp(func_name, "walley_println") == 0) {
                    //printf("find println\ninput_str is |%s|\nstr in bracket is |%s|",input_str,strInBrackets(input_str));
                    char* temp_output = Walley_Println(struct_var,FUNCTION_functions, strInBrackets(input_str));
                    if (PRINT_IN_WHILE_OR_FOR_LOOP==TRUE) {
                        PRINT_STRING_AFTER_LOOP=append(PRINT_STRING_AFTER_LOOP, temp_output);
                    }
                    else{
                        printf("%s", temp_output);
                    }
                    return_value="None";
                }//#####################  print  ###################
                else if (strcmp(func_name, "walley_print") == 0) {
                    char* temp_output = Walley_Print(struct_var,FUNCTION_functions, strInBrackets(input_str));
                    if (PRINT_IN_WHILE_OR_FOR_LOOP==TRUE) {
                        PRINT_STRING_AFTER_LOOP=append(PRINT_STRING_AFTER_LOOP, temp_output);
                    }
                    else{
                        printf("%s", temp_output);
                    }
                    return_value="None";
                }
                else if(strcmp(func_name,"walley_run_str")==0 || strcmp(func_name,"walley_eval(")==0){
                    if (HAS_INIT_WALLEY_RUN_STR==FALSE) {
                        HAS_INIT_WALLEY_RUN_STR=TRUE;
                        
                        Var_initVar(&VAR_VAR_FOR_EMBED);
                        Var_initVar(&VAR_SETTINGS_FOR_EMBED);
                        
                        Str_initStringList(&TEMP_FILE_FOR_EMBED);
                        Str_initStringList(&FUNCTION_FOR_EMBED);
                        Str_initStringList(&WALLEY_EXPRESSION_FOR_EMBED);
                        //AS_NAME="";
                        //matho_init();
                        
                        //################ Initialize some necessary expression ##########################################################
                        Str_addString(&WALLEY_EXPRESSION_FOR_EMBED, "walley_show_var|show var");
                        Str_addString(&WALLEY_EXPRESSION_FOR_EMBED, "walley_decimal_mode|decimal mode");
                        Str_addString(&WALLEY_EXPRESSION_FOR_EMBED, "walley_fraction_mode|fraction mode");
                        Str_addString(&WALLEY_EXPRESSION_FOR_EMBED, "walley_is_fraction_mode|is fraction mode");                        //################################################################################################################
                        
                        
                        
                        Walley_Initialize_Var(&VAR_VAR_FOR_EMBED);
                        Walley_Initialize_Settings(&VAR_SETTINGS_FOR_EMBED);
                        Str_addString(&TEMP_FILE_FOR_EMBED, "#Temp File In Order To Run goto");
                        
                        char *string_in_out_wy="def print(input_str):\n\
                        exp:\n\
                        print input_str\n\
                        walley_print(input_str)\n\
                        \n\
                        def println(input_str):\n\
                        exp:\n\
                        println input_str\n\
                        walley_println(input_str)\n\
                        \n\
                        def random(num1=0,num2=1):\n\
                        exp:\n\
                        random from num1 to num2\n\
                        decimal mode\n\
                        output=walley_random()*(num2-num1)+num1\n\
                        return output";
                        
                        Walley_Run_For_Appointed_Var(&VAR_VAR_FOR_EMBED, &VAR_SETTINGS_FOR_EMBED, &TEMP_FILE_FOR_EMBED, "None", &FUNCTION_FOR_EMBED, string_in_out_wy);
                    }
                    
                    
                    
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    Walley_Run_For_Appointed_Var(&VAR_VAR_FOR_EMBED, &VAR_SETTINGS_FOR_EMBED, &TEMP_FILE_FOR_EMBED, "None", &FUNCTION_FOR_EMBED, toCString(temp_value));
                    return_value="None";
                }
                else if(strcmp(func_name,"walley_show_var")==0){
                    walley_show_var(*struct_var);
                    return_value="None";
                }
                else if(strcmp(func_name,"walley_quit_program")==0){
                    walley_quit_program();
                }
                else if(strcmp(func_name,"walley_get_current_terminal_commands")==0){
                    return_value=walley_get_current_terminal_commands();;
                }
                else if(strcmp(func_name,"walley_exit")==0){
                    exit(0);
                }
                
                // Under fraction mode, sin cos tan will not be calculated......
                //########################### Basic Math Function #######################################
                else if (strcmp(func_name, "sin")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {
                        char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                        char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                        temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                        return_value = math_sin(temp_value);
                    }
                    
                    
                } else if (strcmp(func_name, "cos")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {
                        
                        char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                        char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                        temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                        return_value = math_cos(temp_value);
                    }
                } else if (strcmp(func_name, "tan")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {
                        
                        char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                        char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                        temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                        return_value = math_tan(temp_value);
                    }
                } else if (strcmp(func_name, "cot")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {
                        
                        char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                        char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                        temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                        return_value = math_cot(temp_value);
                    }
                } else if (strcmp(func_name, "tan")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {
                        
                        char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                        char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                        temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                        return_value = math_tan(temp_value);
                    }
                } else if (strcmp(func_name, "sec")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {
                        
                        char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                        char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                        temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                        return_value = math_sec(temp_value);
                    }
                } else if (strcmp(func_name, "csc")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {
                        
                        char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                        char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                        temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                        return_value = math_csc(temp_value);
                    }
                }  else if (strcmp(func_name, "exp")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {
                        
                        char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                        char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                        temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                        return_value = math_exp(temp_value);
                    }
                }else if (strcmp(func_name, "log10")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {
                        
                        char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                        char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                        temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                        return_value = math_log10(temp_value);
                    }
                }
                
                
                else if (strcmp(func_name,"range")==0){
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    return_value = math_range(temp_value);
                }
                
                //########################### End Basic Math Function #######################################
                
                
                else if (strcmp(func_name, "type")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = var_value_type(temp_value);
                    //// printf("Find type() and return value is %s\n", return_value);
                } else if (strcmp(func_name, "num")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = to_num(temp_value);
                } else if (strcmp(func_name, "time")==0) {
                    //char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    //char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    //temp_value = Walley_Eval_With_Variable_From_Var(struct_var, temp_value);
                    //return_value = simple_time(temp_value);
                    return_value = simple_time();
                } else if (strcmp(func_name, "file_readlines")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = file_readlines(temp_value);
                } else if (strcmp(func_name, "file_addstrtofile")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = file_addstrtofile(temp_value);
                }
                else if (strcmp(func_name, "file_writelines") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    char *file_name = substr(temp_value, 0, find_not_in_string(temp_value, ","));
                    char *lines = substr(temp_value, find_not_in_string(temp_value, ",") + 1, (int) strlen(temp_value));
                    file_name = toCString(file_name);
                    lines=toCString(lines);
                    return_value = file_writelines(file_name,lines);
                } else if (strcmp(func_name, "remove_file") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = file_removefile(temp_value);
                } else if (strcmp(func_name, "files_indir") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = file_readFileNameInDirectory(temp_value);
                } else if (strcmp(func_name, "create_file") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = file_createfile(temp_value);
                } else if (strcmp(func_name, "walley_system") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = walley_system(temp_value);
                } else if (strcmp(func_name, "walley_system_return_str") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = walley_system_return_str(temp_value);
                } else if (strcmp(func_name, "input") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = var_input(temp_value);
                } else if(strcmp(func_name,"walley_fraction_mode")==0){
                    Var_changeValueOfVar(&VAR_settings, "fraction_mode","1", "int");
                    
                    //char *ocp;
                    //matho_parse("set fraction 1", &ocp);
                    //matho_process("set fraction 1", &ocp);
                    
                    
                    return_value="None";
                } else if(strcmp(func_name,"walley_decimal_mode")==0){
                    Var_changeValueOfVar(&VAR_settings, "fraction_mode","0", "int");
                    
                    //char *ocp;
                    //matho_parse("set fraction 0", &ocp);
                    //matho_process("set fraction 0", &ocp);
                    
                    return_value="None";
                    
                } else if(strcmp(func_name,"walley_is_fraction_mode")==0){
                    return_value=walley_is_fraction_mode();
                }
                else if(strcmp(func_name,"walley_random")==0){
                    //char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    //char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var);
                    //temp_value = Walley_Eval_With_Variable_From_Var(struct_var, temp_value);
                    return_value=walley_random();
                }
                
                
                
                
                
                //#################################################################
                else {
                    
                    //// printf("HERE++++!!!!!\n");
                    
                    return_value = Walley_Run_One_Function_And_Return_Value_From_Var(function, &VAR_var,FUNCTION_functions);
                }

                temp_token.TOKEN_STRING=return_value;
            }
        }
        
        
        else if (strcmp(token_class, "W_STRING")==0){
            if (strcmp(next.TOKEN_CLASS,"W_LIST_TABLE")==0||next.TOKEN_STRING[0]=='.') {
                char *var_value=token_string;
                i=i+1;
                Walley_Next(token, &i, &var_value, struct_var, *FUNCTION_functions);
                i=i-1;
                temp_token.TOKEN_STRING=var_value;
            }
            else{
                temp_token.TOKEN_STRING=token_string;
            }
            // "Hello".length()
            //else if()
        }
        
        
        else if (strcmp(token_class, "W_NUMBER")==0){
            //printf("2------> %s\n",token_string);
            temp_token.TOKEN_STRING=token_string;

        }
        
        else if (strcmp(token_class, "W_DICTIONARY")==0){
            //printf("3------> %s\n",token_string);

            temp_token.TOKEN_STRING=token_string;
            exit(0);

        }
        
        else if (strcmp(token_class, "W_LIST_TABLE")==0){
            if (strcmp(next.TOKEN_CLASS,"W_LIST_TABLE")==0||next.TOKEN_STRING[0]=='.') {
                char *var_value=Var_getValueOfVar(*struct_var, token_string);
                i=i+1;
                Walley_Next(token, &i, &var_value, struct_var, *FUNCTION_functions);
                i=i-1;
                temp_token.TOKEN_STRING=var_value;
            }
            else{
                temp_token.TOKEN_STRING=token_string;
            }
        }
        else {
            temp_token.TOKEN_STRING=token_string;
        }
        
        
        
        temp_token.TOKEN_CLASS=TOKEN_analyzeTokenClass(temp_token.TOKEN_STRING);
        TL_addToken(&output_token, temp_token);
    }
    
    
    /*
    for(i=0;i<(int)strlen(input_str);i++){
  
        // printf("output %s--->%c %d\n",output,input_str[i],i);
        
        if(find_alpha==FALSE && (isalpha(input_str[i])||input_str[i]=='_'||input_str[i]=='"'||input_str[i]=='\''||input_str[i]=='[' )&& charIsInString(input_str,i)==FALSE){
            //// printf("Find alpha\n");
            //printf("--End this loop, output is %s\n",output);
            find_alpha=TRUE;
            begin=i;
            if (i!=(int)strlen(input_str)-1) {
                continue;
            }
            //printf("begin %d\n",begin);
        }
        
        
        //if(find_alpha==TRUE && (input_str[i]=='(' ||input_str[i]=='[') && charIsInString(input_str,i)==FALSE){
        if(find_alpha==TRUE && (input_str[i]=='(' ||input_str[i]=='[')
           && charIsInString(input_str,i)==FALSE
           && charIsInDictionary(input_str, i)==FALSE){
            //// printf("ENTER HERE\n");
            if (input_str[i]=='[') {
                // printf("It is [\n");
                
                // I forget the code here
                if (count_str_not_in_string(substr(input_str, 0, i), "[")==count_str_not_in_string(substr(input_str, 0, i), "]")) {
                    find_function=TRUE;
                    //// printf("FIND FUNCTION\n");
                } else {
                    find_function=FALSE;
                }
                // printf("FIND_FUNCTION %d\n",find_function);
            }
            else{
                find_function=TRUE;
            }
            //printf("Find Function\n");
        }
        
        //I make slice also a kind of function
        
        if (find_function) {
            find_function = FALSE;
            //printf("@@@@@ Enter Find Function @@@@@\n");

            char *func_name = substr(input_str, begin, i);
            //printf("Func_Name is %s\n",func_name);

            
            bool it_is_slice=FALSE;// = Var_Existed(struct_var, func_name);
            if (Var_Existed(*struct_var, func_name)==TRUE||
                strcmp(variableValueType(func_name),"string")==0|| // New code below on Dec 7
                strcmp(variableValueType(func_name), "list")==0) {
                it_is_slice=TRUE;
            }
            //printf("it_is_slice is %d\n",it_is_slice);
                       
            // New code here
            // to deal with list instance like x[0]=a() while a is class
            if (input_str[i]=='[' && it_is_slice==FALSE) {
                int index_of_right=indexOfMostOutterRectBracket(input_str,i);
                while (input_str[index_of_right+1]=='[') {
                    index_of_right=indexOfMostOutterRectBracket(input_str,index_of_right+1);
                }
                if (index_of_right!=-1) {
                    if (checkWhetherSameInstanceExistedFromVar(VAR_var, substr(input_str, begin, index_of_right+1))==TRUE) {
                        continue;
                    }
                }
            }
            
            
            
                        
            //printf("it is function %d\n",it_is_slice);
            if (it_is_slice==FALSE) {
                //char *temp = substr(input_str, i, (int) strlen(input_str));
                int index_of_youkuohao = find_from_index(input_str, ")", i);
                
                int num_of_zuo = count_str(substr(input_str, i, index_of_youkuohao + 1), "(");
                int num_of_you = count_str(substr(input_str, i, index_of_youkuohao + 1), ")");
                //printf("zuo %d, you %d\n",num_of_zuo,num_of_you);
                while (num_of_zuo != num_of_you) {
                    //printf("Bu Deng");
                    index_of_youkuohao = find_from_index(input_str, ")", index_of_youkuohao + 1);
                    num_of_zuo = count_str(substr(input_str, i, index_of_youkuohao + 1), "(");
                    num_of_you = count_str(substr(input_str, i, index_of_youkuohao + 1), ")");
                }
                
                //printf("------\n%s\n-------\n",substr(input_str,begin,index_of_youkuohao+1));
                
                char *function = substr(input_str, begin, index_of_youkuohao + 1);
                //printf("Function is %s\n",function);
                //################################################################
                //######## Check Embed Function ##################################
                char *return_value;
                
                //################### Special Function #########################################################
                //
                //eg x="Hello"-----> x.find("He")----->0
                //
                //// printf("#### Third Generation FUNCTION is |%s| ####\n", function);
                //// printf("I DO Not Know What Happened\n");
                
                //bool same_function_existed_in_walley_function=checkWhetherSameFunctionNameExists(func_name);
                
                int index_of_dot=find_from_behind_not_in_str_list_dict_parenthesis(function, ".");
                if (find(substr(function, 0, find(function, "(")), ".") != -1 && charIsInString(function, index_of_dot) == FALSE) {
                    //// printf("It is instance function\n");
                    char *user = substr(function, 0, index_of_dot);
                    //printf("user---> %s  func---> %s\n",user,function);
                    bool instance_existed = checkWhetherSameInstanceExistedFromVar(*struct_var, user);
                    bool var_existed = Var_Existed(*struct_var,user);
                    
                    bool only_var_existed = var_existed;
                    
                    char *user_value=Walley_Substitute_Var_And_Function_Return_Value_From_Var(user, struct_var,FUNCTION_functions);
                    char *function_temp=replace_not_in_string(function, user, user_value);
                    
                    
                    if (strcmp(variableValueType(user_value), "string")==0||strcmp(variableValueType(user_value), "list")==0) {
                        var_existed=TRUE;
                    }
                    
                    if (instance_existed == FALSE && var_existed==TRUE){
                        if (only_var_existed==TRUE) {
                            return_value=Walley_Run_Special_Function_From_Var(function, struct_var);
                        } else {
                            return_value = Walley_Run_Special_Function_From_Var(function_temp, struct_var);
                        }
                    }
                    else {
                        return_value = Walley_Run_One_Function_And_Return_Value_From_Var(function, &VAR_var,FUNCTION_functions);
                        
                    }
                    
                }
                
                //################### Embeded Function ###############################################################
                else if (find(function, "int(") ==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = to_int(temp_value);
                } else if (find(function, "double(") ==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = to_double(temp_value);
                } else if (find(function, "d(") ==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = to_decimal(temp_value);
                } else if (find(function, "f(") ==0) {
                    WALLEY_SUBSTITUTION_CAN_JUST_EVAL_IN_THE_END=FALSE;
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = eval_for_fraction_with_alpha(temp_value);
                    return_value = to_fraction(temp_value);
                    WALLEY_SUBSTITUTION_CAN_JUST_EVAL_IN_THE_END=TRUE;
                } else if (find(function, "nstr(") ==0) {
                    //// printf("Find nstr(");
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = to_nstr(temp_value);
                } else if (find(function, "str(")==0) {
                    
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = to_string(temp_value);
                    
                    //printf("HERE return_value %s\n",return_value);
                }
                //#####################  println  ###################
                else if (find(input_str, "walley_println(") == 0) {
                    //printf("find println\ninput_str is |%s|\nstr in bracket is |%s|",input_str,strInBrackets(input_str));
                    char* temp_output = Walley_Println(struct_var,FUNCTION_functions, strInBrackets(input_str));
                    if (PRINT_IN_WHILE_OR_FOR_LOOP==TRUE) {
                        PRINT_STRING_AFTER_LOOP=append(PRINT_STRING_AFTER_LOOP, temp_output);
                    }
                    else{
                        printf("%s", temp_output);
                    }
                    return_value="None";
                }//#####################  print  ###################
                else if (find(input_str, "walley_print(") == 0) {
                    char* temp_output = Walley_Print(struct_var,FUNCTION_functions, strInBrackets(input_str));
                    if (PRINT_IN_WHILE_OR_FOR_LOOP==TRUE) {
                        PRINT_STRING_AFTER_LOOP=append(PRINT_STRING_AFTER_LOOP, temp_output);
                    }
                    else{
                        printf("%s", temp_output);
                    }
                    return_value="None";
                }
                else if(find(input_str,"walley_run_str(")==0 || find(input_str,"walley_eval(")==0){
                    if (HAS_INIT_WALLEY_RUN_STR==FALSE) {
                        HAS_INIT_WALLEY_RUN_STR=TRUE;
                        
                        Var_initVar(&VAR_VAR_FOR_EMBED);
                        Var_initVar(&VAR_SETTINGS_FOR_EMBED);
                        
                        Str_initStringList(&TEMP_FILE_FOR_EMBED);
                        Str_initStringList(&FUNCTION_FOR_EMBED);
                        Str_initStringList(&WALLEY_EXPRESSION_FOR_EMBED);
                        //AS_NAME="";
                        //matho_init();
                        
                        //################ Initialize some necessary expression ##########################################################
                        Str_addString(&WALLEY_EXPRESSION_FOR_EMBED, "walley_show_var|show var");
                        Str_addString(&WALLEY_EXPRESSION_FOR_EMBED, "walley_decimal_mode|decimal mode");
                        Str_addString(&WALLEY_EXPRESSION_FOR_EMBED, "walley_fraction_mode|fraction mode");
                        Str_addString(&WALLEY_EXPRESSION_FOR_EMBED, "walley_is_fraction_mode|is fraction mode");                        //################################################################################################################
                        
                        
                        
                        Walley_Initialize_Var(&VAR_VAR_FOR_EMBED);
                        Walley_Initialize_Settings(&VAR_SETTINGS_FOR_EMBED);
                        Str_addString(&TEMP_FILE_FOR_EMBED, "#Temp File In Order To Run goto");
                        
char *string_in_out_wy="def print(input_str):\n\
    exp:\n\
        print input_str\n\
    walley_print(input_str)\n\
    \n\
def println(input_str):\n\
    exp:\n\
        println input_str\n\
    walley_println(input_str)\n\
    \n\
def random(num1=0,num2=1):\n\
    exp:\n\
        random from num1 to num2\n\
    decimal mode\n\
    output=walley_random()*(num2-num1)+num1\n\
    return output";
                        
                        Walley_Run_For_Appointed_Var(&VAR_VAR_FOR_EMBED, &VAR_SETTINGS_FOR_EMBED, &TEMP_FILE_FOR_EMBED, "None", &FUNCTION_FOR_EMBED, string_in_out_wy);
                    }
                    
                    
                    
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    Walley_Run_For_Appointed_Var(&VAR_VAR_FOR_EMBED, &VAR_SETTINGS_FOR_EMBED, &TEMP_FILE_FOR_EMBED, "None", &FUNCTION_FOR_EMBED, toCString(temp_value));
                    return_value="None";
                }
                else if(find(input_str,"walley_show_var(")==0){
                    walley_show_var(*struct_var);
                    return_value="None";
                }
                else if(find(input_str,"walley_quit_program(")==0){
                    walley_quit_program();
                }
                else if(find(input_str,"walley_get_current_terminal_commands(")==0){
                    return_value=walley_get_current_terminal_commands();;
                }
                else if(find(input_str,"walley_exit(")==0){
                    exit(0);
                }
                
                // Under fraction mode, sin cos tan will not be calculated......
                //########################### Basic Math Function #######################################
                else if (find(function, "sin(")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = math_sin(temp_value);
                    }
                    
                    
                } else if (find(function, "cos(")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {

                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = math_cos(temp_value);
                    }
                } else if (find(function, "tan(")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {

                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = math_tan(temp_value);
                    }
                } else if (find(function, "cot(")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {
                        
                        char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                        char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                        temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                        return_value = math_cot(temp_value);
                    }
                } else if (find(function, "tan(")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {
                        
                        char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                        char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                        temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                        return_value = math_tan(temp_value);
                    }
                } else if (find(function, "sec(")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {

                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = math_sec(temp_value);
                    }
                } else if (find(function, "csc(")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {
                        
                        char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                        char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                        temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                        return_value = math_csc(temp_value);
                    }
                }  else if (find(function, "exp(")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {
                        
                        char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                        char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                        temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                        return_value = math_exp(temp_value);
                    }
                }else if (find(function, "log10(")==0) {
                    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
                    if (fraction_mode==TRUE) {
                        return_value=function;
                    } else {

                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = math_log10(temp_value);
                    }
                }
                
                
                else if (find(function,"range(")==0){
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    return_value = math_range(temp_value);
                }
                
                //########################### End Basic Math Function #######################################

                
                else if (find(function, "type(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = var_value_type(temp_value);
                    //// printf("Find type() and return value is %s\n", return_value);
                } else if (find(function, "num(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = to_num(temp_value);
                } else if (find(function, "time(")==0) {
                    //char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    //char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    //temp_value = Walley_Eval_With_Variable_From_Var(struct_var, temp_value);
                    //return_value = simple_time(temp_value);
                    return_value = simple_time();
                } else if (find(function, "file_readlines(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = file_readlines(temp_value);
                } else if (find(function, "file_addstrtofile(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = file_addstrtofile(temp_value);
                }
                else if (find(function, "file_writelines(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    char *file_name = substr(temp_value, 0, find_not_in_string(temp_value, ","));
                    char *lines = substr(temp_value, find_not_in_string(temp_value, ",") + 1, (int) strlen(temp_value));
                    file_name = toCString(file_name);
                    lines=toCString(lines);
                    return_value = file_writelines(file_name,lines);
                } else if (find(function, "remove_file(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = file_removefile(temp_value);
                } else if (find(function, "files_indir(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = file_readFileNameInDirectory(temp_value);
                } else if (find(function, "create_file(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = file_createfile(temp_value);
                } else if (find(function, "walley_system(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = walley_system(temp_value);
                } else if (find(function, "walley_system_return_str(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = walley_system_return_str(temp_value);
                } else if (find(function, "input(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    temp_value = Walley_Eval_With_Variable_From_Var(*struct_var, temp_value);
                    return_value = var_input(temp_value);
                } else if(find(function,"walley_fraction_mode(")==0){
                    Var_changeValueOfVar(VAR_settings, "fraction_mode","1", "int");
                    
                    //char *ocp;
                    //matho_parse("set fraction 1", &ocp);
                    //matho_process("set fraction 1", &ocp);
                    
                    
                    return_value="None";
                } else if(find(function,"walley_decimal_mode(")==0){
                    Var_changeValueOfVar(VAR_settings, "fraction_mode","0", "int");
                    
                    //char *ocp;
                    //matho_parse("set fraction 0", &ocp);
                    //matho_process("set fraction 0", &ocp);

                    return_value="None";
                    
                } else if(find(function,"walley_is_fraction_mode(")==0){
                    return_value=walley_is_fraction_mode();
                }
                else if(find(function,"walley_random(")==0){
                    //char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    //char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var);
                    //temp_value = Walley_Eval_With_Variable_From_Var(struct_var, temp_value);
                    return_value=walley_random();
                }
                


                
                
                //#################################################################
                else {
                    
                    //// printf("HERE++++!!!!!\n");
                    
                    return_value = Walley_Run_One_Function_And_Return_Value_From_Var(function, &VAR_var,FUNCTION_functions);
                }
                              
                end=index_of_youkuohao+1;
                int begin_temp = begin + (int) strlen(output)-(int) strlen(input_str);
                int end_temp = end + (int) strlen(output)-(int) strlen(input_str);
                
                output = replace_from_index_to_index(output, function, return_value, begin_temp, end_temp);
                
                i = index_of_youkuohao;
                find_alpha = FALSE;
                has_var = TRUE;
                finish_find_var = FALSE;
                continue;
            }
            // IT is slice
            else {
                // printf("It is slice\n");
                int index_of_rect = find_from_index_not_in_str_list_dict_parenthesis(input_str, "]", i + 1);
                if (index_of_rect!=(int)strlen(input_str)-1) {
                    while (input_str[index_of_rect+1]=='[') {
                        index_of_rect= find_from_index_not_in_str_list_dict_parenthesis(input_str, "]", index_of_rect+ 1);
                    }
                }

                
                // case like x[0:1].toupper()
                if (index_of_rect!=(int)strlen(input_str)-1) {
                if (input_str[index_of_rect+1]=='.') {
                    //// printf("Find . after ]");
                    find_alpha=TRUE;
                    find_function=FALSE;
                    continue;
                }
                }
                
                char *slice_str = substr(input_str, i, index_of_rect + 1);
                char *value_of_var; //= Var_getValueOfVar(file_var_name, func_name);
                
                if (Var_Existed(*struct_var, func_name)==TRUE) {
                    value_of_var=Var_getValueOfVar(*struct_var, func_name);
                }
                else if (strcmp(variableValueType(func_name), "string")==0){
                    value_of_var=func_name;
                }
                else if (strcmp(variableValueType(func_name), "list")==0){
                    value_of_var=func_name;
                }
                else{
                    printf("@@ |%s|\n",CURRENT_INPUT_STR);

                    printf("Mistake occurred while calling function Walley_Substitute_Third....\n%s is wrong whiling judging it is slice\n",func_name);
                    exit(0);
                }
                
                char *replace_str = substr(input_str, begin, index_of_rect + 1);
                
                
                // I modified the code below on Jau 3 2013 and introduce new function Walley_Slice
                //char *with_str = old_slice(value_of_var, slice_str);
                char *with_str = Walley_Slice(value_of_var, slice_str, struct_var, FUNCTION_functions);

                
                int begin_temp = begin + (int) strlen(output)-(int) strlen(input_str);
                end=index_of_rect+1;
                int end_temp = end + (int) strlen(output)-(int) strlen(input_str);
                
                //printf("Begin %d, End %d\n",begin_temp,end_temp);
                //printf("Before change, output is %s\n",output);
                output = replace_from_index_to_index(output, replace_str, with_str, begin_temp, end_temp);
                
                i = index_of_rect;
                find_alpha = FALSE;
                has_var = TRUE;
                finish_find_var = FALSE;
                
                continue;
            }
        }
        
        if (find_alpha == TRUE && isSign(input_str[i]) && charIsInString(input_str, i) == FALSE) {
            find_alpha = FALSE;
            end = i;
            //printf("@@@@@@ end %d\n",end);
            finish_find_var = TRUE;
            
        }
        if (find_alpha == TRUE && ((isJudgeSign(input_str[i])) || input_str[i] == ')'|| input_str[i]==',' || input_str[i]==' ') && charIsInString(input_str, i) == FALSE && charIsInList(input_str, i)==FALSE && charIsInDictionary(input_str, i)==FALSE) {
            //printf("%d\n%d\n%d\n",find_alpha,(isJudgeSign(input_str[i])),input_str[i]==')');
            find_alpha = FALSE;
            end = i;
            //printf("------end %d\n",end);
            finish_find_var = TRUE;
            
        }
        if (find_alpha == TRUE && i == (int) strlen(input_str) - 1) {
            find_alpha = FALSE;
            end = i + 1;
            // printf("end %d\n",end);
            
            finish_find_var = TRUE;
        }
        //printf("--End this loop, output is %s\n",output);
        if (finish_find_var) {
            //printf("@@@@ Enter finish_find_var @@@@\n");
            //printf("------\n%s\n------\n",substr(input_str,begin,end));
            
            //printf("Begin %d, End %d\n",begin,end);
            char *var_name = substr(input_str, begin, end);
            char *var_value;
            //if var_name is a instance var like x.age, then try to get value from VAR_var
            if (find_not_in_string(var_name, ".") != -1) {
                char *user = substr(var_name, 0, find_not_in_string(var_name, "."));
                if (checkWhetherSameInstanceExistedFromVar(VAR_var, user) == TRUE) {
                    
                    var_value=Var_getValueOfVar(VAR_var, var_name);
                }
                else {
                    var_value=Var_getValueOfVar(*struct_var,var_name);
                }
                
            }
            else {
                
                // check whether is global var
                int num_of_element_in_global_var=valueNumOfList(GLOBAL_VAR);
                int x=0;
                bool is_global_var=FALSE;
                for (; x<num_of_element_in_global_var; x++) {
                    char *element=valueOfListAtIndex(GLOBAL_VAR, x);
                    if (strcmp(element, var_name)==0) {
                        is_global_var=TRUE;
                        break;
                    }
                }
                
                // is global var
                if (is_global_var==TRUE) {
                    var_value=Var_getValueOfVar(VAR_var, var_name);
                }
                
                // is not global var
                else{
                
                    if(Var_Existed(*struct_var,var_name)==TRUE){
                        var_value=Var_getValueOfVar(*struct_var,var_name);
                        //// printf("FIND!! %s   %s\n",file_var_name,var_name);
                    } else {
                        var_value=var_name;
                    }
                }
            }
            // printf("Var Name %s\nVar Value %s\n",var_name,var_value);
            int begin_temp=begin+(int)strlen(output)-(int)strlen(input_str);
            int end_temp=end+(int)strlen(output)-(int)strlen(input_str);
            
            //printf("Begin %d, End %d\n",begin_temp,end_temp);
            //printf("Before change, output is %s\n",output);
            output=replace_from_index_to_index(output,var_name,var_value,begin_temp,end_temp);
            // printf("Output is %s\n",output);
            has_var=TRUE;
            finish_find_var=FALSE;
            find_alpha=FALSE;
            
        }
        // printf("--End this loop, output is %s\n",output);
        
    }
*/
    
    
    //TOKEN_PrintTOKEN(output_token);
    //char *output2=TL_toString(output_token);
    //printf("output2---> %s\n",output2);
    output=TL_toString(output_token);
    
    
    
    
    if (WALLEY_SUBSTITUTION_CAN_JUST_EVAL_IN_THE_END==TRUE) {
        if (stringIsAlpha(output)==FALSE) {
            output=Walley_Eval_All_From_Var(*struct_var, output);
        }else {
            output=Walley_Eval_With_Variable_From_Var(*struct_var, output);
        }

    }
    

    //printf("Walley_Substitute_Var_And_Function_Return_Value_From_File !!!!!!input %s  output is %s\n",input_str,output);
    return output;
}


char *Walley_Print(struct VAR **struct_var, char ***FUNCTION_functions,char *input_str){
    //printf("#### Walley_Print ####    %s\n",input_str);
    input_str=Walley_Substitute_Var_And_Function_Return_Value_From_Var(input_str,struct_var,FUNCTION_functions);
    char *after_eval=input_str;
    if (stringIsAlpha(input_str)==FALSE) {
        Walley_Eval_With_Variable_From_Var(*struct_var,input_str);
    }

    char *output=toCString(after_eval);
   // printf("%s\n",output);
    //printf("output--->%s\n",output);

    if (find(output, "\\n")!=-1) {
        output=replace(output, "\\n", "\n");
    }
   // printf("output--->%s\n",output);

    if(find(output,"\\\"")!=-1){
        output=replace(output, "\\\"", "\"");
    }
    
    //if(find(output,"\\'")!=-1){
    //    output=replace(output, "\\'", "\'");
    //}
    //printf("print output--->%s\n",output);
    return output;
}
char *Walley_Println(struct VAR **struct_var,char ***FUNCTION_functions, char *input_str){
    //// printf("#### Walley_Println ####\n");

    return append(Walley_Print(struct_var,FUNCTION_functions,input_str), "\n");
}

bool Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(char *input_str, struct VAR **struct_var, char ***FUNCTION_functions){
    //printf("#### Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function ####\n");
    //printf("%s\n",input_str);
    // I did not consider the situation when and or or is in string
    //printf("%d\n",find(input_str," and "));
    input_str=cleanJudgeSentence(input_str);
    input_str=trim(input_str);
    
    
    
    input_str=replace_not_in_string(input_str, " and ", "+++++");
    input_str=replace_not_in_string(input_str, " or ", "----");
    /*
    if(find(input_str," and ")!=-1){
        //printf("Find And\n");
        input_str=replace(input_str," and ","+++++");
    }
    if(find(input_str," or ")!=-1){
        //printf("Find Or\n");
        input_str=replace(input_str," or ","----");
    }
    */
    if(find(input_str,"TRUE")!=-1){
        //printf("Find And\n");
        
        if (strcmp(input_str, "TRUE")==0) {
            input_str="1==1";
        }
        
        else if(find_from_index(input_str,"==TRUE",find(input_str,"TRUE")-2)!=1){
            input_str=replace(input_str,"TRUE","1==1");
        } else {
            input_str=replace(input_str,"TRUE","1");
        }
    }

    if(find(input_str,"FALSE")!=-1 ){
        //printf("Find Or\n");
        
        if (strcmp(input_str, "FALSE")==0) {
            input_str="0==1";
        }
        else if(find_from_index(input_str,"==FALSE",find(input_str,"FALSE")-2)!=1){
            //printf("%d\n",find_from_index(input_str,"==FALSE",find(input_str,"FALSE")-2));
            input_str=replace(input_str,"FALSE","0==1");
            //printf("@%s\n",input_str);
        } else {
            input_str=replace(input_str,"FALSE","0");
        }
    }
    //######### if not 3>4: #########
    //############# Add Not #########
    
    input_str=replace_not_in_string(input_str, "not ", "*****");
    /*
    if(find(input_str,"not ")!=-1){
        input_str=replace(input_str,"not ","*****");
    }
     */
    input_str=Walley_Substitute_Var_And_Function_Return_Value_From_Var(input_str,struct_var,FUNCTION_functions);
    
    /*
    if(find(input_str,"+++++")!=-1){
        input_str=replace(input_str,"+++++"," and ");
    }
    
    if(find(input_str,"----")!=-1){
        input_str=replace(input_str,"----"," or ");
    }
    
    if(find(input_str,"*****")!=-1){
        input_str=replace(input_str,"*****","not ");
    }*/
    input_str=replace_not_in_string(input_str, "+++++", " and ");
    input_str=replace_not_in_string(input_str, "----", " or ");
    input_str=replace_not_in_string(input_str, "*****","not ");
    
    input_str=replace_not_in_string(input_str, "TRUE==", "1==");
    input_str=replace_not_in_string(input_str, "FALSE==", "0==");
    //printf("####----->%s\n",input_str);
    //printf("Here\n");
    bool output=judgeWithAndAndOrWithParenthesis(input_str);
    //// printf("#### Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function #### output is %d\n",output);
    return output;
}


//############################### Update Var and Var_Value to File#############################
// If var existed, then replace
// else create new one.
/*
 void Walley_Update_Var_And_Var_Value_To_File(char *file_var_name, char *var_name, char *var_value){
 printf("#### Walley_Update_Var_And_Var_Value_To_File ####\n");
 char *var_value_type = variableValueType(var_value);
 bool has_same_var_name = Var_Existed(struct_var, var_name);
 
 if (has_same_var_name == TRUE) {
 char *previous_var_value=Var_getValueOfVar(file_var_name,var_name);
 char *previous_var_value_type=variableValueType(previous_var_value);
 
 if (strcmp(var_value_type, "list") == 0 && find(var_name, "[") == -1) {
 //printf("Value type List, change the whole value of list to file\n");
 if(strcmp(previous_var_value_type,"list")==0)
 changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name, var_name, var_value);
 else{
 Walley_Remove_Variable_And_Value_From_File(file_var_name,var_name);
 writeVarNameAndVarValueIntoAppointedFileForList(file_var_name, var_name, var_value);
 }
 }
 // x={a:1,b:2}, now the input is x={a:12}, so need to rewrite x.
 else if (strcmp(var_value_type, "dictionary") == 0 && find(var_name, "{") == -1) {
 if(strcmp(previous_var_value_type,"dictionary")==0)
 changeTheWholeVarValueFromItsInitialOneFromFileForDictionary(file_var_name, var_name, var_value);
 else{
 Walley_Remove_Variable_And_Value_From_File(file_var_name,var_name);
 writeVarNameAndVarValueIntoAppointedFileForDictionary(file_var_name, var_name, var_value);
 }
 }
 else {
 
 // Eg a[0] is one element of list a
 if (isListElement(file_var_name, var_name)) {
 changeTheOneVarValueFromItsInitialOneFromFileForList(file_var_name, var_name, var_value);
 }
 // Eg a{"Hello"} is one element of dictionary
 else if (find_not_in_string(var_name, "{") != -1 && find_not_in_string(var_name, "}") != -1) {
 printf("&&&&&&& Enter Here 1 \n");
 changeTheOneVarValueFromItsInitialOneFromFileOrAddVarNameAndValueForDictionary(file_var_name, var_name, var_value);
 
 } else {
 
 if(strcmp(previous_var_value_type,"dictionary")==0||strcmp(previous_var_value_type,"list")==0){
 Walley_Remove_Variable_And_Value_From_File(file_var_name,var_name);
 writeVarNameAndVarValueIntoAppointedFile(file_var_name, var_name, var_value, var_value_type);
 }
 //printf("&&&&&&& Enter Here 2 \n");
 //var_value = Walley_Substitute_Var_And_Function_Return_Value_From_File(var_value, file_var_name);
 //var_value = Walley_Eval_With_Variable_From_File(file_var_name, var_value);
 //var_value_type = variableValueType(var_value);
 else{
 //printf("here2\n");
 Var_changeValueOfVar(file_var_name, var_name, var_value, var_value_type);
 //printf("here3\n");
 }
 }
 }
 }
 // Does not have the same var name
 else {
 // Initialize List
 if (strcmp(var_value_type, "list") == 0) {
 //printf("Value type List, write the list and its value to file\n");
 writeVarNameAndVarValueIntoAppointedFileForList(file_var_name, var_name, var_value);
 }
 // Initialize Dictionary
 else if (strcmp(var_value_type, "dictionary") == 0) {
 printf("Find Dictionary Type Value");
 writeVarNameAndVarValueIntoAppointedFileForDictionary(file_var_name, var_name, var_value);
 
 }            // Eg a{"Hello"} is one element of dictionary
 else if (find_not_in_string(var_name, "{") != -1 && find_not_in_string(var_name, "}") != -1) {
 printf("&&&&&&& Enter Here 1 \n");
 changeTheOneVarValueFromItsInitialOneFromFileOrAddVarNameAndValueForDictionary(file_var_name, var_name, var_value);
 
 }            // Initialize simple value
 else {
 //printf("++++++++++++enter here\n");
 //var_value=countFromExpression(var_value);
 //var_value = Walley_Substitute_Var_And_Function_Return_Value_From_File(var_value, file_var_name);
 //var_value = Walley_Eval_With_Variable_From_File(file_var_name, var_value);
 //var_value_type = variableValueType(var_value);
 writeVarNameAndVarValueIntoAppointedFile(file_var_name, var_name, var_value, var_value_type);
 }
 }
 }**/


//############################### If is expression, DO THAT ###################################

void Walley_Eval_And_Update_Var_And_Value_To_Var(struct VAR **struct_var,char ***FUNCTION_functions,char* input_str) {
    //else if (isExpression(input_str)==TRUE){
    //printf("#### Walley_Eval_And_Update_Var_And_Value_To_File ####  %s\n",input_str);
    char *var_name = variableName(input_str);
    char *var_value = variableValue(input_str);
    char *var_value_type = variableValueType(var_value);
    
    //printf("#### The Variable Name is :%s\n",var_name);
    //printf("#### The Variable Value is :%s\n", var_value);
    //printf("#### The Variable Value Type is :%s\n", var_value_type);
    
    // new code here on Jan 12 to solve x[i][j]=x[i][j]+3, replace var_name x[i][j] problem
    int i=0;
    int begin=0;
    int end=0;
    for (i = 0; i < (int) strlen(var_name); i++) {
        
        
        if (charIsInString(var_name, i) == FALSE && var_name[i] == '{') {
            //printf("______------______FIND {}\n");
            begin = i;
            end = find_from_index_not_in_string(var_name, "}", begin + 1);
            //if (end != -1) {
            char *check = substr(var_name, begin, end + 1);
            while (count_str_not_in_string(check, "{") != count_str_not_in_string(check, "}")) {
                end = find_from_index_not_in_string(var_name, "}", end + 1);
                check = substr(var_name, begin, end + 1);
            }
            char *replace_str = substr(var_name, begin + 1, end); //from x{i} get i
            if (stringIsEmpty(replace_str) == FALSE) {
                if (finishFindingVarAndFunction(replace_str) == FALSE) {
                    char *with_str = Walley_Substitute_Var_And_Function_Return_Value_From_Var(replace_str, struct_var,FUNCTION_functions);
                    var_name = replace_from_index_to_index(var_name, replace_str, with_str, begin + 1, end);
                }
            }
            //} //printf("Replace %s with %s, the input_str is %s\n",replace_str,with_str,input_str);
        }
        
        if (charIsInString(var_name, i) == FALSE && var_name[i] == '[') {
            
            begin = i;
            end = find_from_index_not_in_string(var_name, "]", begin + 1);
            //if (end != -1) {
            char *check = substr(var_name, begin, end + 1);
            //if(end!=-1){
            while (count_str_not_in_string(check, "[") != count_str_not_in_string(check, "]")) {
                end = find_from_index_not_in_string(var_name, "]", end + 1);
                check = substr(var_name, begin, end + 1);
            }
            //}
            char *replace_str = substr(var_name, begin + 1, end);
            if (stringIsEmpty(replace_str) == FALSE) {
                if (finishFindingVarAndFunction(replace_str) == FALSE && find_not_in_string(replace_str, ":")==-1) {//from x{i} get i
                    char *with_str = Walley_Substitute_Var_And_Function_Return_Value_From_Var(replace_str, struct_var,FUNCTION_functions);
                    var_name = replace_from_index_to_index(var_name, replace_str, with_str, begin + 1, end);
                }
            }
            //}
        }
        if (charIsInString(var_name, i) == FALSE && var_name[i] == '(') {
            begin = i;
            end = find_from_index_not_in_string(var_name, ")", begin + 1);
            //if (end != -1) {
            char *check = substr(var_name, begin, end + 1);
            while (count_str_not_in_string(check, "(") != count_str_not_in_string(check, ")")) {
                end = find_from_index_not_in_string(var_name, ")", end + 1);
                check = substr(var_name, begin, end + 1);
            }
            char *replace_str = substr(var_name, begin + 1, end);
            if (stringIsEmpty(replace_str) == FALSE) {
                
                if (finishFindingVarAndFunction(replace_str) == FALSE) {//from x{i} get i
                    char *with_str = Walley_Substitute_Var_And_Function_Return_Value_From_Var(replace_str, struct_var,FUNCTION_functions);
                    if (strcmp(with_str, replace_str)==0) {
                        continue;
                    }
                    
                    // with_str=Walley_Eval_All_From_Var(struct_var, with_str);
                    var_name = replace_from_index_to_index(var_name, replace_str, with_str, begin + 1, end);
                    // printf("here\n");
                }
            }
            //}
        }
        
    }

    
    
    
    // new code here on Jan 6
    
    var_value=removeBackSpace(var_value);
    // incomplete string
    if (var_value[0]=='"'&&(var_value[(int)strlen(var_value)-1]!='"' ||(int)strlen(trim(var_value))==1||(var_value[(int)strlen(var_value)-1]=='"'&&var_value[(int)strlen(var_value)-2]=='\\'))&&count_str_not_in_string(var_value, "\"")%2!=0) {
        VAR_VALUE_INCOMPLETE=TRUE;
        VAR_VALUE_INCOMPLETE_TYPE="string\"";
        VAR_VALUE_TO_BE_COMPLETE=var_value;
        VAR_NAME_TO_BE_COMPLETE=var_name;
        VAR_VALUE_TYPE_TO_BE_COMPLETE="string";
        
        if (var_value[(int)strlen(var_value)-1]=='\\') {
            VAR_VALUE_TO_BE_COMPLETE=append(VAR_VALUE_TO_BE_COMPLETE, "n");
        }
    }
    
    // incomplete string
    else if (var_value[0]=='\''&&(var_value[(int)strlen(var_value)-1]!='\'' ||(int)strlen(trim(var_value))==1||(var_value[(int)strlen(var_value)-1]=='\''&&var_value[(int)strlen(var_value)-2]=='\\'))) {
        VAR_VALUE_INCOMPLETE=TRUE;
        VAR_VALUE_INCOMPLETE_TYPE="string'";
        VAR_VALUE_TO_BE_COMPLETE=var_value;
        VAR_NAME_TO_BE_COMPLETE=var_name;
        VAR_VALUE_TYPE_TO_BE_COMPLETE="string";
        if (var_value[(int)strlen(var_value)-1]=='\\') {
            VAR_VALUE_TO_BE_COMPLETE=append(VAR_VALUE_TO_BE_COMPLETE, "n");
        }

    }
    
    // incomplete list
    // and table
    else if (var_value[0]=='['&&count_str_not_in_string(var_value, "[")!=count_str_not_in_string(var_value, "]")){
        VAR_VALUE_INCOMPLETE=TRUE;
        VAR_VALUE_INCOMPLETE_TYPE="list";
        VAR_VALUE_TO_BE_COMPLETE=removeNFromBack(var_value);
        VAR_NAME_TO_BE_COMPLETE=var_name;
        VAR_VALUE_TYPE_TO_BE_COMPLETE="list";
        LIST_TOTAL_LEFT=count_str_not_in_string(var_value, "[");
        LIST_TOTAL_RIGHT=count_str_not_in_string(var_value, "]");

    }
    
    // incomplete dictionary
    else if (var_value[0]=='{'&&count_str_not_in_string(var_value, "{")==count_str_not_in_string(var_value, "}")+1){
        VAR_VALUE_INCOMPLETE=TRUE;
        VAR_VALUE_INCOMPLETE_TYPE="dictionary";
        VAR_VALUE_TO_BE_COMPLETE=var_value;
        VAR_NAME_TO_BE_COMPLETE=var_name;
        VAR_VALUE_TYPE_TO_BE_COMPLETE="dictionary";
    }
    
    // incomplete expression
    else if (var_value[0]=='<'&&var_value[1]=='@'&&var_value[(int)strlen(var_value)-1]!='>'){
        VAR_VALUE_INCOMPLETE=TRUE;
        VAR_VALUE_INCOMPLETE_TYPE="expression";
        VAR_VALUE_TO_BE_COMPLETE=var_value;
        VAR_NAME_TO_BE_COMPLETE=var_name;
        VAR_VALUE_TYPE_TO_BE_COMPLETE="expression";
    }

    
    
    
    
    if (VAR_VALUE_INCOMPLETE==FALSE) {
    
        
            
    var_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(var_value, struct_var,FUNCTION_functions);
            
        
    // I delete the sentence below on October 22.
    //var_value = Walley_Eval_With_Variable_From_Var(struct_var, var_value);
    var_value_type = variableValueType(var_value);
    
    //printf("#### The Variable Name is :%s\n", var_name);
    //printf("#### The Variable Value is :%s\n", var_value);
    //printf("#### The Variable Value Type is :%s\n", var_value_type);
    //printf("The Variable Value after put known Variable in is :%s\n",putKnownVariableIntoExpression(var_value));
        
    /*
    // New code on Dec 16.
    // To solve x[0]="Hel" problem
     */
    //##########################################################################
    if (find(var_name, "[")!=-1) {
        char *temp_var_name=substr(var_name, 0, find(var_name, "["));
        if (Var_Existed(*struct_var, temp_var_name)) {
            char *temp_var_value=Var_getValueOfVar(*struct_var, temp_var_name);
            if (strcmp("string",variableValueType(temp_var_value))==0 ) {
                temp_var_value=toCString(temp_var_value);
                //printf("find string slice like x[0]='Hello'\n");
                //printf("temp_var_value is %s\n",temp_var_value);
                // then
                char *slice=substr(var_name, find(var_name, "["), (int)strlen(var_name));
                //printf("slice is %s\n",slice);
                // x[1:3]="Helllo"
                if (find(slice, ":")!=-1) {
                    int index_of_colon=find(slice, ":");
                    int left=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(substr(slice, 1, index_of_colon), struct_var, FUNCTION_functions));
                    int right=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(substr(slice, index_of_colon+1, (int)strlen(slice)-1), struct_var, FUNCTION_functions));
                    var_value=replace_from_index_to_index(temp_var_value, substr(temp_var_value, left, right), toCString(var_value), left, right);
                    var_value=toString(var_value);
                }
                // x[2,3]="Hello"
                else if (find(slice, ",")!=-1){
                    int index_of_colon=find(slice, ",");
                    int left=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(substr(slice, 1, index_of_colon), struct_var, FUNCTION_functions));
                    int right=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(substr(slice, index_of_colon+1, (int)strlen(slice)-1), struct_var, FUNCTION_functions));
                    var_value=replace_from_index_to_index(temp_var_value, substr(temp_var_value, left, right), toCString(var_value), left, right);
                    var_value=toString(var_value);
                    
                }
                // x[2]="Hi"
                else{
                    int index=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(substr(slice, 1, (int)strlen(slice)-1), struct_var, FUNCTION_functions));
                    var_value=replace_from_index_to_index(temp_var_value, substr(temp_var_value, index, index+1), toCString(var_value), index, index+1);
                    var_value=toString(var_value);
                    //printf("VAR VALUE NOW IS %s\n",var_value);
                }
                var_name=temp_var_name;

            }
        }
    }
    //##########################################################################
    
    // ################### Basic Calculation ##################################
    //if(strcmp(var_value_type,"unknown type")!=0){//&&strcmp(var_value_type,"function")!=0){
        
    Walley_Update_Var_And_Var_Value_To_Var(struct_var,var_name,var_value);
}
}


void Walley_Judge_Run_Anotation_For_While_Def_Class(struct VAR **struct_var,struct VAR **struct_settings,char ***FUNCTION_functions,char *input_str, struct TOKEN *token) {
   // printf("Walley_Judge_Run_Anotation_For_While_Def_Class |%s|",input_str);
   // printf("#### Walley_Judge_Run_Anotation_For_While_Def_Class ####\n");
   // printf("############################\n");
   // Var_PrintVar(struct_settings);
   // printf("############################\n");
    
    int current_space=numOfSpaceAheadString(input_str);
    input_str = removeAheadSpace(input_str);
    
    //I add this value here in order to run now_run_if.
    //bool can_run_basic_input = TRUE;
    //bool run_goto = FALSE;
    
    //int current_space=atoi(Var_getValueOfVar(*struct_settings , "current_space"));
    //printf("##current_space is %d\n",current_space);
    
    
    int index_of_first_none_whitespace=TL_indexOfFirstNoneWhiteSpaceToken(token);
    int length_of_token=TL_length(token);
    struct TOKEN first_none_whitespace_token=token[index_of_first_none_whitespace];
    
    //#####################  Anotation  ###################
    if (input_str[0] == '#') {
        //printf("This is one anatation %s\n", removeAheadSpace(input_str));
        printf("");
    }
    else if (strcmp(first_none_whitespace_token.TOKEN_STRING,"class")==0){
        CLASS_NUM++;
        if (HAVE_INIT_CLASS_LIST==FALSE) {
            Str_initStringList(&INSTANCE_NAMES_LIST);
            CLASS_initCLASSList(&CLASS_LIST);
            HAVE_INIT_CLASS_LIST=TRUE;
        }
        NOW_WRITTING_CLASS=TRUE;
        SPACE_OF_FIRST_CLASS_SENTENCE=REQUIRED_SPACE;
        REQUIRED_SPACE=REQUIRED_SPACE+4;
        
        char *class_name=className(input_str);
        char *class_mother=classMother(input_str);
        
        CLASS_addProperty(&CLASS_LIST, class_name, class_mother, "#Begin to define class...\n");
        //CLASS_PrintCLASS(CLASS_LIST);
    }
    // ##############  Function  ##############################
    else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "def") == 0) {
        SPACE_OF_FIRST_DEF_SENTENCE = REQUIRED_SPACE;
        REQUIRED_SPACE = REQUIRED_SPACE + 4;
        
        NOW_WRITTING_FUNCTION = TRUE;
       
        char *func_name = functionName(input_str);
        char *func_param_str = functionParameterStr(input_str);
       // bool has_same_function_name = checkWhetherSameFunctionNameExistsFromVar(func_name);
        
        TEMP_FUNCTION_NAME=func_name;
        TEMP_FUNCTION_PARAMETER=func_param_str;
          
        
            writeFunctionIntoVar(func_name, func_param_str,FUNCTION_functions);
            Str_addString(FUNCTION_functions, "#~Begin");

        
            if (strcmp(func_param_str, "None") == 0) {
                Str_addString(FUNCTION_functions, "##Finish Init Params");
            } else {
                writeFunctionParameterOneByOneToVar(func_param_str,FUNCTION_functions);
                Str_addString(FUNCTION_functions, "##Finish Init Params");
            }
    }//################## Judge Whether this whether an if sentence ##########################
    //======= New Version of if sentence ===========
    else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "if") == 0 ){
        NOW_WRITTING_IF=TRUE;
        SPACE_OF_FIRST_IF_SENTENCE=CURRENT_SPACE;
        REQUIRED_SPACE=SPACE_OF_FIRST_IF_SENTENCE+4;
        
        
        char *trim_input_str=trim(input_str);
        
        Str_initStringList(&IF_ELIF_ELSE.if_elif_else);
        char *string_in_if=trim(substr(trim_input_str, find(trim_input_str,"if ")+3, find_from_behind(trim_input_str, ":")));
        Str_addString(&IF_ELIF_ELSE.if_elif_else,string_in_if);
        
        IF_ELIF_ELSE.content=(char***)malloc(sizeof(char**)*(INDEX_OF_IF_ELIF_ELSE+1));
        Str_initStringList(&IF_ELIF_ELSE.content[0]);
        
        
    }
    /*
    else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "if") == 0 || strcmp(first_none_whitespace_token.TOKEN_STRING, "elif") == 0 || strcmp(first_none_whitespace_token.TOKEN_STRING, "else") == 0) {
        // printf("now judge if sentence\n");
        char *sentence = "";
        char *temp_for_sentence = removeAheadSpace(removeBackSpace(input_str));
        bool can_run=TRUE;
        REQUIRED_SPACE=current_space;
        
        
        if (strcmp(first_none_whitespace_token.TOKEN_STRING, "if") == 0) {
            
            //// printf("Find If\n");
            sentence = substr(temp_for_sentence, find(temp_for_sentence, "if ") + 3, (int) strlen(temp_for_sentence) - 1);
            last_if_sentence = sentence;
            can_run = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(sentence, struct_var,FUNCTION_functions);
            //printf("++++++can run is %d\n",can_run);
            
            // if can run.
            // Write last_if_sentence to __temp_if__
            char *__temp_if__=Var_getValueOfVar(*struct_var,"__temp_if__");
            __temp_if__=listAppendOneElement(__temp_if__,last_if_sentence);
            changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, "__temp_if__", __temp_if__);
            //}
            char *__temp_if_space__=Var_getValueOfVar(*struct_var,"__temp_if_space__");
            char temp_num[100];
            //sprintf(temp_num,"%d",space);
            sprintf(temp_num,"%d",REQUIRED_SPACE);

            __temp_if_space__=listAppendOneElement(__temp_if_space__,temp_num);
            
            char *__has_run_if__=Var_getValueOfVar(*struct_var,"__has_run_if__");
            sprintf(temp_num,"%d",can_run);
            __has_run_if__=listAppendOneElement(__has_run_if__,temp_num);
            
            
            // Delete the same // eg delete one 4 from [0,4,4]
            int num_of_temp_if_space=valueNumOfList(__temp_if_space__);
            if (num_of_temp_if_space > 1) {
                char *previous = valueOfListAtIndex(__temp_if_space__, num_of_temp_if_space - 2);
                char *now = valueOfListAtIndex(__temp_if_space__, num_of_temp_if_space - 1);
                if (atoi(previous) == atoi(now)) {
                    //// printf("--------Find Another If--------\n");
                    char temp_length[100];
                    int index = num_of_temp_if_space - 2;
                    sprintf(temp_length, "%d", index);
                    char *index_str = (char*)malloc(sizeof (char) *((int) strlen(temp_length) + 3));
                    strcpy(index_str, "[");
                    strcat(index_str, temp_length);
                    strcat(index_str, "]");
                    index_str[(int) strlen(temp_length) + 2]=0;
                    __temp_if_space__ = listRemoveOneElementAtOneIndex(__temp_if_space__, index_str);
                    __temp_if__=listRemoveOneElementAtOneIndex(__temp_if__,index_str);
                    __has_run_if__=listRemoveOneElementAtOneIndex(__has_run_if__,index_str);
                    //changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__temp_if__",__temp_if__);
                    changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, "__temp_if__", __temp_if__);

                    
                }
                
                
            }
            //changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__has_run_if__",__has_run_if__);
            //changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__temp_if_space__",__temp_if_space__);
            changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, "__has_run_if__", __has_run_if__);
            changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, "__temp_if_space__", __temp_if_space__);

            
        } else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "elif") == 0) {
            
            
            char *__temp_if__=Var_getValueOfVar(*struct_var,"__temp_if__");
            int length=valueNumOfList(__temp_if__);
            char temp_length[100];
            
            char *__has_run_if__=Var_getValueOfVar(*struct_var,"__has_run_if__");
            
            int i=0;
            int index;
            char *__temp_if_space__=Var_getValueOfVar(*struct_var,"__temp_if_space__");
            for(i=0;i<length;i++){
                int number=atoi(valueOfListAtIndex(__temp_if_space__,i));
                //// printf("number is %d\n",number);
                if(number==current_space){
                    index=i;
                    break;
                }
            }
            
            //sprintf(temp_length,"%d",length-1);
            sprintf(temp_length,"%d",index);
            char *index_str=(char*)malloc(sizeof(char)*((int)strlen(temp_length)+3));
            strcpy(index_str,"[");
            strcat(index_str,temp_length);
            strcat(index_str,"]");
            index_str[(int)strlen(temp_length)+2]=0;
            last_if_sentence=valueOfListAtIndexString(__temp_if__,index_str);
            bool has_run_if=atoi(valueOfListAtIndexString(__has_run_if__,index_str));
            
            
            
            sentence = substr(temp_for_sentence, find(temp_for_sentence, "elif ") + 5, (int) strlen(temp_for_sentence) - 1);
            
            last_if_sentence = sentence;
            // if can run.
            // Write last_if_sentence to __temp_if__
            //if(can_run==TRUE){
            __temp_if__ = Var_getValueOfVar(*struct_var, "__temp_if__");
            length = valueNumOfList(__temp_if__);
            //char temp_length[100];
            sprintf(temp_length, "%d", length - 1);
            char *var_name_str =(char*) malloc(sizeof (char) *((int) strlen(temp_length) + 3 + (int) strlen("__temp_if__")));
            strcpy(var_name_str, "__temp_if__[");
            strcat(var_name_str, temp_length);
            strcat(var_name_str, "]");
            var_name_str[(int) strlen(temp_length) + 2 + (int) strlen("__temp_if__")]=0;

            changeTheOneVarValueFromItsInitialOneFromVarForList(struct_var, var_name_str, sentence);
            //}
            if(has_run_if==TRUE){
                //// printf("********* HAS RUN IF **********");
                can_run=FALSE;
            }else{
                can_run = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(sentence, struct_var,FUNCTION_functions);

                 if (can_run==TRUE){
                    int length_of_has_run_if__=valueNumOfList(__has_run_if__);
                    char temp4[100];
                    sprintf(temp4,"%d",length_of_has_run_if__-1);
                    char *var_name_str2=(char*)malloc(sizeof(char)*((int)strlen("__has_run_if__")+3+(int)strlen(temp4)));
                    strcpy(var_name_str2,"__has_run_if__[");
                    strcat(var_name_str2,temp4);
                    strcat(var_name_str2,"]");
                    var_name_str2[(int)strlen("__has_run_if__")+2+(int)strlen(temp4)]=0;
                    //changeTheOneVarValueFromItsInitialOneFromFileForList(struct_var,var_name_str2,"1");
                    changeTheOneVarValueFromItsInitialOneFromVarForList(struct_var, var_name_str2, "1");
                }
            }
            
        }
        
        
        
        else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "else") == 0) {
            
            char *__temp_if__=Var_getValueOfVar(*struct_var,"__temp_if__");
            int length=valueNumOfList(__temp_if__);
            char temp_length[100];
            
            char *__has_run_if__=Var_getValueOfVar(*struct_var,"__has_run_if__");
            
            int i=0;
            int index;
            char *__temp_if_space__=Var_getValueOfVar(*struct_var,"__temp_if_space__");
            for(i=0;i<length;i++){
                int number=atoi(valueOfListAtIndex(__temp_if_space__,i));
                //// printf("number is %d\n",number);
                //// printf("current space is %d\n",current_space);
                if(number==current_space){
                    index=i;
                    break;
                }
            }
                        
            //sprintf(temp_length,"%d",length-1);
            sprintf(temp_length,"%d",index);
            char *index_str=(char*)malloc(sizeof(char)*((int)strlen(temp_length)+3));
            strcpy(index_str,"[");
            strcat(index_str,temp_length);
            strcat(index_str,"]");
            index_str[(int)strlen(temp_length)+2]=0;
            last_if_sentence=valueOfListAtIndexString(__temp_if__,index_str);
            bool has_run_if=atoi(valueOfListAtIndexString(__has_run_if__,index_str));
            
           
            last_if_sentence = "\"None\"";
            
            //Delete the final __temp_if__ in file
            //// printf("index str is %s\n",index_str);
            __temp_if__=listRemoveOneElementAtOneIndex(__temp_if__,index_str);
            //changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__temp_if__",__temp_if__);
            changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, "__temp_if__", __temp_if__);
            
            __temp_if_space__=listRemoveOneElementAtOneIndex(__temp_if_space__,index_str);
            //changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__temp_if_space__",__temp_if_space__);
            changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, "__temp_if_space__", __temp_if_space__);

            __has_run_if__=listRemoveOneElementAtOneIndex(__has_run_if__,index_str);
            //changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__has_run_if__",__has_run_if__);
            changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, "__has_run_if__", __has_run_if__);

            if(has_run_if==TRUE){
                can_run=FALSE;
            }
            else{
                can_run=TRUE;
            }
            
            
        }
        //// printf("Enter here\n");
        //// printf("Sentence is |%s|\nLength is %d\n", sentence, (int) strlen(sentence));
        //bool can_run = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(sentence, file_name);
        if (can_run) {
            //SPACE_OF_FIRST_IF_ELIF_ELSE_SENTENCE=current_space;
            //printf("space of first if sentence %d\n",current_space);
            now_run_if = TRUE;
            REQUIRED_SPACE = REQUIRED_SPACE + 4;
        } else {
            now_run_if = FALSE;
        }
    }*/
     
     //#################### While Sentence ##################################
    else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "while") == 0) {
        char *last_while_sentence = removeAheadSpace(input_str);
        last_while_sentence = substr(last_while_sentence, 6, find(last_while_sentence, ":"));
        last_while_sentence = removeBackSpace(last_while_sentence);
        
        LAST_WHILE_SENTENCE=last_while_sentence;
        
        bool can_run_while = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(last_while_sentence, struct_var,FUNCTION_functions);
        if (can_run_while == FALSE) {
            //// printf("Can Not Run While");
            NOW_WRITTING_WHILE = FALSE;
        } else {
            NOW_WRITTING_WHILE = TRUE;
            SPACE_OF_FIRST_WHILE_SENTENCE=REQUIRED_SPACE;
            REQUIRED_SPACE = REQUIRED_SPACE + 4;

            LOOP_TURN++;
            
            
            // Begin the while loop
            // Begin to collect String
            PRINT_IN_WHILE_OR_FOR_LOOP=TRUE;
        }
                
        
        
    }        //#################### For Sentence #####################################
    else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "for") == 0) {// && removeBackSpace(input_str)[(int) strlen(removeBackSpace(input_str)) - 1] == ':') {
        //printf("#### Find For ####\n");
        int non_white_space_token_num=TL_numOfNoneWhitespaces(token);
        if (non_white_space_token_num!=5) {
            printf("%s\n",input_str);
            printf("Error.  For statement wrong\n");
            printf("Try 'for i in range(5):' format\n");
            exit(0);
        }
                
        if (strcmp(token[index_of_first_none_whitespace+4].TOKEN_STRING,"in")!=0) {
            int start=token[index_of_first_none_whitespace+4].TOKEN_START;
            printf("%s\n",input_str);
            char *temp_str="";
            temp_str=Str_appendSpaceAhead(temp_str, start);
            printf("%s^\n",temp_str);
            printf("Error. 'in' is needed in for statement\n");
            exit(0);
        }
        
        
        //char *temp_i = substr(input_str, find(input_str, "for ") + 4, find(input_str, " in"));
        //temp_i = removeAheadSpace(removeBackSpace(temp_i));
        char *temp_i=token[index_of_first_none_whitespace+2].TOKEN_STRING;
        //char *in_what = substr(input_str, find(input_str, " in ") + 4, (int) strlen(removeBackSpace(input_str)) - 1);
        char *in_what=token[index_of_first_none_whitespace+6].TOKEN_STRING;
        in_what = Walley_Substitute_Var_And_Function_Return_Value_From_Var(in_what, struct_var,FUNCTION_functions);
        I_VALUE_AFTER_IN=in_what;
        I_IN_FOR_LOOP=temp_i;
        //printf("i is |%s|, in_what is |%s|\n", temp_i, in_what);
        NOW_WRITTING_FOR = TRUE;
        
        if (strcmp(variableValueType(I_VALUE_AFTER_IN), "string") == 0) {
            I_VALUE_AFTER_IN = changeStringToList(I_VALUE_AFTER_IN);
        }

        
        SPACE_OF_FIRST_FOR_SENTENCE=REQUIRED_SPACE;
        REQUIRED_SPACE = REQUIRED_SPACE + 4;
        
        LOOP_TURN++;
        
        
        // Begin the for loop
        // Begin to collect String
        PRINT_IN_WHILE_OR_FOR_LOOP=TRUE;
        
        
        // Write temp_i_in_for_sentence to __temp_for__  eg
        // for i in [1,2,3,4]:     write [1,2,3,4] to __temp_for__
        
    }
    else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "switch")==0){
        SPACE_OF_FIRST_SWITCH_SENTENCE = current_space;
        REQUIRED_SPACE = current_space + 4;
        
        NOW_WRITTING_SWITCH = TRUE;
        
        //char *switch_object=substr(input_str, 7, find_from_behind(input_str, ":"));
        char *switch_object=token[index_of_first_none_whitespace+2].TOKEN_STRING;
        SWITCH_OBJECT=trim(switch_object);
        
    }
    
   
}



void Walley_Update_Functions_And_Vars_While_Importing(char *temp_file_to_run, struct VAR **struct_var, char ***FUNCTION_functions){
    
    char *string_in_out_wy_temp="def print(input_str):\n\
    exp:\n\
        print input_str\n\
    walley_print(input_str)\n\
    \n\
def println(input_str):\n\
    exp:\n\
        println input_str\n\
    walley_println(input_str)\n\
    \n\
def random(num1=0,num2=1):\n\
    exp:\n\
        random from num1 to num2\n\
    decimal mode\n\
    output=walley_random()*(num2-num1)+num1\n\
    return output";
    // New code here to import
    struct VAR *temp_struct_var;
    Var_initVar(&temp_struct_var);
    struct VAR *temp_struct_settings;
    Var_initVar(&temp_struct_settings);

    char **temp_TEMP_FILE;Str_initStringList(&temp_TEMP_FILE);
    char **temp_FUNCTION_functions;Str_initStringList(&temp_FUNCTION_functions);
    
    
    Walley_Initialize_Var(&temp_struct_var);
    Walley_Initialize_Settings(&temp_struct_settings);
    Walley_Run_For_Appointed_Var(&temp_struct_var, &temp_struct_settings, &temp_TEMP_FILE, temp_file_to_run, &temp_FUNCTION_functions, string_in_out_wy_temp);
    
    
    
    //Walley_Run_For_Appointed_Var(&temp_struct_var, &temp_struct_settings,&temp_TEMP_FILE,temp_file_to_run,&temp_FUNCTION_functions, getStringFromFile(temp_file_to_run));
    Walley_Run_For_Appointed_Var_String_List(&temp_struct_var, &temp_struct_settings, &temp_TEMP_FILE, temp_file_to_run, &temp_FUNCTION_functions, getStringFromFileAndReturnStringList(temp_file_to_run));

    
    //printf("####################\n");
    //Var_PrintVar(temp_struct_var);
    //printf("####################\n");
    int i=0;
    int length_of_temp_struct_var=0;
    if (strcmp((temp_struct_var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Can not find __size_of_array__");
        exit(0);
    }
    else{
        length_of_temp_struct_var=atoi((temp_struct_var)->var_value);
    }

    
    while (i<length_of_temp_struct_var) {
        char *var_name=temp_struct_var[i].var_name;
        // prevent from deleting those important variables.
        if (
            find(var_name, "__size_of_array__")==0
            ) {
        }
        else{
            //printf("Begin To Add Var\n");
            Var_addProperty(struct_var, append(append(substr(AS_NAME, 1, (int)strlen(AS_NAME)), "."), var_name), temp_struct_var[i].var_value, variableValueType(temp_struct_var[i].var_value));
        }
        
        i=i+1;
    }
        
    
    /*
    char *__temp_class__=Var_getValueOfVar(temp_struct_var, "__temp_class__");
    char *__string_in_temp_class__=Var_getValueOfVar(temp_struct_var, "__string_in_temp_class__");
    char *class_list=keyOfDictionaryAsList(__temp_class__);
    //printf("class_list is %s\n",class_list);
    int num_of_key_of_dictionary=valueNumOfList(class_list);
    i=0;
    for (; i<num_of_key_of_dictionary; i++) {
        char *key=valueOfListAtIndex(class_list, i);
        char *string_in_class=valueAtKey(__string_in_temp_class__, key);
        //printf(" class name --->%s\n|%s|\n",valueOfListAtIndex(class_list, i),string_in_class);
        char *new_class_name=append(append(substr(AS_NAME, 1, (int)strlen(AS_NAME)), "."), toCString(valueOfListAtIndex(class_list, i)));
        char *change_dictionary=append("__string_in_temp_class__", append("{", append( toString(new_class_name), "}")));
        //printf("@@change_dictionary is %s\n",change_dictionary);
        changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var, change_dictionary, string_in_class);
        
        char *mother=valueAtKey(__temp_class__, key);
        char *change_dictionary2=append("__temp_class__", append("{", append( toString(new_class_name), "}")));
        changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var, change_dictionary2, mother);

    }*/
    
   
    char *function_list=getFunctionNameAndReturnList(temp_FUNCTION_functions);
    int num_of_function_in_list=valueNumOfList(function_list);
    i=0;
    for (i=0; i<num_of_function_in_list; i++) {
        int j=0;
        int length_of_temp_FUNCTION_functions=atoi(temp_FUNCTION_functions[0]);
        while (j<length_of_temp_FUNCTION_functions) {
            char *func_now=valueOfListAtIndex(function_list, i);
            //printf("------> |%s|\n",temp_FUNCTION_functions[j]);
            //printf("#%s\n",append(func_now, ":"));
            if (find(temp_FUNCTION_functions[j],append(func_now, ":"))==0) {
                //  printf("FIND %s from %s\n",append(func_now, ":"),temp_FUNCTION_functions[j]);
                temp_FUNCTION_functions[j]=append(append(substr(AS_NAME, 1, (int)strlen(AS_NAME)), "."), temp_FUNCTION_functions[j]);
                j++;
                continue;
            } else {
                func_now=append(func_now, "(");
                int begin=0;
                int index_of_func=0;
                while (TRUE) {
                    //x=a()*a()+b()
                    index_of_func=find_from_index(temp_FUNCTION_functions[j], func_now, begin);
                    if (index_of_func==-1) {
                        break;
                    }
                    // printf("index_of_func is %d\n",index_of_func);
                    int left=find_from_index(temp_FUNCTION_functions[j], "(", index_of_func);
                    // printf("left is %d\n",left);
                    int right=indexOfMostOutterBracket(temp_FUNCTION_functions[j], left);
                    // printf("right is %d\n",right);
                    char *replace_str=substr(temp_FUNCTION_functions[j], index_of_func, right+1);
                    // printf("replace str is %s\n",replace_str);
                    if (index_of_func==-1) {
                        break;
                    }
                    else if(index_of_func==0){
                        char *with_str=append(append(substr(AS_NAME, 1, (int)strlen(AS_NAME)), "."), replace_str);
                        temp_FUNCTION_functions[j]=replace_from_index_to_index(temp_FUNCTION_functions[j], replace_str, with_str, index_of_func, right+1);
                        begin=right+1+(int)strlen(with_str)-(int)strlen(replace_str);
                        continue;
                        
                    }else{
                        if (isalpha(temp_FUNCTION_functions[j][index_of_func-1])||isdigit(temp_FUNCTION_functions[j][index_of_func-1])||temp_FUNCTION_functions[j][index_of_func-1]=='_') {
                            begin=right+1;
                            continue;
                        }
                        else{
                            char *with_str=append(append(substr(AS_NAME, 1, (int)strlen(AS_NAME)), "."), replace_str);
                            temp_FUNCTION_functions[j]=replace_from_index_to_index(temp_FUNCTION_functions[j], replace_str, with_str, index_of_func, right+1);
                            begin=right+1+(int)strlen(with_str)-(int)strlen(replace_str);
                            continue;
                        }
                    }
                    
                }
                
                j++;
            }
        }
    }
   
    
    i=0;
    int length_of_temp_FUNCTION_functions=atoi(temp_FUNCTION_functions[0]);
    while (i<length_of_temp_FUNCTION_functions) {
        Str_addString(FUNCTION_functions, temp_FUNCTION_functions[i]);
        i++;
    }
   }


/*
    eg   "Hello"[0:2][0]
            0     1   2  3
         "Hello" is the current_value
          [0:2] --> 1 is the current_index
          
          this function will return the final index
          it will return 3 which is now the current_index
 
 
 */
void Walley_Next(struct TOKEN *token, int *current_index, char **current_value, struct VAR **struct_var, char **FUNCTION_functions)
{

    //printf("current_value %s\n",*current_value);
    char *token_class=TOKEN_analyzeTokenClass(*current_value);
    if (*current_index==TL_length(token)) {
        return;
    }
    if (strcmp(token_class, "W_STRING")==0) {
        // "Hello"[0,2]
        if (strcmp(token[*current_index].TOKEN_CLASS, "W_LIST_TABLE")==0) {            
            char *var_value=Walley_Slice(*current_value, token[*current_index].TOKEN_STRING, struct_var, &FUNCTION_functions);
            *current_value=var_value;
            *current_index=*current_index+1;
            Walley_Next(token, current_index, current_value, struct_var, FUNCTION_functions);
            
        }
        // "Hello".length()
        else if (token[*current_index].TOKEN_STRING[0]=='.'){
            if (checkWhetherSameInstanceExistedFromVar(INSTANCE_NAMES_LIST, SAVE_VAR_NAME_TO_CHECK_WHETHER_IT_IS_INSTANCE)) {
                //printf("It is instance\n");
                if (find(token[*current_index+1].TOKEN_STRING, "(")==-1) {
                    char *output=Var_getValueOfVar(*struct_var, append(SAVE_VAR_NAME_TO_CHECK_WHETHER_IT_IS_INSTANCE, append(".",token[*current_index+1].TOKEN_STRING)));
                    if (strcmp(output, "None")==0) {
                        *current_index=*current_index+2;
                        return;
                    }
                    else{
                        *current_value=output;
                        *current_index=*current_index+2;
                        Walley_Next(token, current_index, current_value, struct_var, FUNCTION_functions);
                        
                    }

                }
                else{
                    char *output=Walley_Run_One_Function_And_Return_Value_From_Var(append(append(SAVE_VAR_NAME_TO_CHECK_WHETHER_IT_IS_INSTANCE,"."), token[*current_index+1].TOKEN_STRING), struct_var, &FUNCTION_functions);
                    //printf("OUTPUT----> %s\n",output);
                    if (strcmp(output, "None")==0) {
                        *current_index=*current_index+2;
                        return;
                    }
                    else{
                        *current_value=output;
                        *current_index=*current_index+2;
                        Walley_Next(token, current_index, current_value, struct_var, FUNCTION_functions);

                    }
                }
            }
            else{
                *current_value=Walley_Run_Special_Function_From_Var(append(append(*current_value,"."),token[*current_index+1].TOKEN_STRING ), struct_var);
                *current_index=*current_index+2;
                Walley_Next(token, current_index, current_value, struct_var, FUNCTION_functions);
            }

        }
        else{
            return ;
        }
    }
    
    else if (strcmp(token_class, "W_LIST_TABLE")==0) {
        // [1,2,3,4][0]
        if (strcmp(token[*current_index].TOKEN_CLASS, "W_LIST_TABLE")==0) {
            SAVE_VAR_NAME_TO_CHECK_WHETHER_IT_IS_INSTANCE=append(SAVE_VAR_NAME_TO_CHECK_WHETHER_IT_IS_INSTANCE, token[*current_index].TOKEN_STRING);

            char *var_value=Walley_Slice(*current_value, token[*current_index].TOKEN_STRING, struct_var, &FUNCTION_functions);
            *current_value=var_value;
            *current_index=*current_index+1;
            Walley_Next(token, current_index, current_value, struct_var, FUNCTION_functions);
        }
        // [1,2,3,4].length()
        else if (token[*current_index].TOKEN_STRING[0]=='.'){
            *current_value=Walley_Run_Special_Function_From_Var(append(append(*current_value,"."),token[*current_index+1].TOKEN_STRING ), struct_var);
            *current_index=*current_index+2;
            Walley_Next(token, current_index, current_value, struct_var, FUNCTION_functions);
        }
        else{
            return ;
        }
    }

    else{
        
    }
}