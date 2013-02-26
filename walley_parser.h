//
//  walley_parser.h
//  Walley
//
//  Created by shd101wyy on 13-2-25.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_core.h"
/*
 Attention
  CHANGE input_str to token_list
 1. The Token List here is the token list without whitespaces
 2. The Token List here is the token list before # (W_SHORT_ANNOTATION)
 3. #~ must be the first token of Token List
 4. CURRENT_SPACE should be got before running Walley_Parse_Token_List
*/

void Walley_Parse_Simple_String(struct VAR **struct_var, struct VAR **struct_settings, char* existing_file, char ***FUNCTION_functions, char *input_str);
void Walley_Parse_String_List(struct VAR **struct_var, struct VAR **struct_settings, char *existing_file, char ***FUNCTION_functions, char **input_str);


// x=Hi()
// x is instance_name
// Hi() is __class__
void Walley_Init_Class(struct VAR **struct_var, struct VAR **struct_settings, char *existing_file, char ***FUNCTION_functions,char *instance_name, char *__class__){
        instance_name = trim(instance_name);
        __class__ = trim(__class__);
        char *parameter=substr(__class__,find(__class__,"(")+1,find_not_in_string(__class__,")"));
        char *class_name=substr(__class__, 0, find(__class__,"("));
        
        
        char *after_change=formatStringInClassWithExtendFromVar(*struct_var,CLASS_LIST,class_name,instance_name);
        //printf("#### AFTER CHANGE\n|%s|\n####\n",after_change);
        
        Walley_Parse_Simple_String(struct_var, struct_settings, existing_file,FUNCTION_functions, after_change);
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
            Walley_Parse_Simple_String(struct_var, struct_settings, existing_file,FUNCTION_functions, append("syms ", instance_name));
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

void Walley_Parse_Simple_String(struct VAR **struct_var, struct VAR **struct_settings, char* existing_file, char ***FUNCTION_functions, char *input_str){ //struct TOKEN *token_list) {
    //printf("-----> %s\n",input_str);
    struct TOKEN *token_list=Walley_Lexica_Analysis(input_str);
    token_list=TL_returnTokenListWithoutWhitespaces(token_list);
    
   
    // get token before #
    // eg x=12 #123
    // get x=12 only
    int num_of_short_annotation=TL_numOfTOKEN_CLASS(token_list, "W_SHORT_ANNOTATION");
    if (num_of_short_annotation>1) {
        token_list=subtoken(token_list, 1, TL_indexOfTokenAccordingTokenClassAndNum(token_list, "W_SHORT_ANNOTATION", 0));
    }
    
    // printf("====================\n");
    // TL_PrintTOKEN(token_list);
    // printf("====================\n");
 
    
    
    
    int length_of_token_list=TL_length(token_list);
    /*
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
     // can become complete
     if (trim_input_str[(int)strlen(trim_input_str)-1]=='}') {
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
     if (trim_input_str[length_of_trim_input_str-1]=='}') {
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

     */
    if(1==0){
        
    }
    else{
        
        
        
        
        if (strcmp(token_list[length_of_token_list-1].TOKEN_STRING,"~#")==0){
            // printf("Now End Long Annotation");
            NOW_IN_ANNOTATION = 0;
            
        }
        else if (strcmp(token_list[1].TOKEN_STRING, "#~")==0) {
            //// printf("Now Begin Long Annotation");
            NOW_IN_ANNOTATION = 1;
        }
        if(NOW_IN_ANNOTATION==0 && length_of_token_list!=1){
                        
            
            //I add this value here in order to run now_run_if.
            bool can_run_basic_input = TRUE;
            
            
            CURRENT_SPACE = numOfSpaceAheadString(input_str);
            
            // $2 Got Current Space before running this function
            CURRENT_INPUT_STR=input_str;

            
            if (CURRENT_SPACE%4!=0) {
                printf("Error.. Current Space is incorrect\n");
                exit(0);
            }
            
            if (CURRENT_SPACE > REQUIRED_SPACE) {
                can_run_basic_input = FALSE;
            }
            
            
            if (strcmp(token_list[length_of_token_list-1].TOKEN_STRING, ";")==0) {
                printf("%s\n",CURRENT_INPUT_STR);
                char *temp_str="";
                temp_str=Str_appendSpaceAhead(temp_str, (int)strlen(CURRENT_INPUT_STR)-1);
                printf("%s^\n",temp_str);
                printf("Error. Walley does not need ; in sentence\n");
                exit(0);        }
            
            
            if(CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==FALSE){
                can_run_basic_input=FALSE;
            }
            
            
            
            struct TOKEN first_none_whitespace_token=token_list[1];
            
            
                       
            //################## Now Run If #######################################
            if (NOW_WRITTING_IF == TRUE  && CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==TRUE) {
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
                                Walley_Parse_String_List(struct_var, struct_settings,existing_file, FUNCTION_functions, If_copy.content[i]);
                                break;
                            }
                            bool can_run=Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(to_judge, struct_var, FUNCTION_functions);
                            if (can_run) {
                                //printf("run if elif \n");
                                Walley_Parse_String_List(struct_var, struct_settings,existing_file, FUNCTION_functions, If_copy.content[i]);
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
            else if (NOW_WRITTING_WHILE == TRUE  && CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==TRUE) {
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
                        
                        Walley_Parse_String_List(struct_var, struct_settings,existing_file, FUNCTION_functions, temp_string_list_in_while_loop);

                        
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
            else if (NOW_WRITTING_FUNCTION == TRUE && CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==TRUE) {
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
                                
                                if ( trim_input_str[0]!='{') {
                                    // add exression...                                                   //problem here, I add trim. No problem before.
                                    Str_addString(&WALLEY_EXPRESSION, append(TEMP_FUNCTION_NAME,append("|",trim(input_str))));
                                }
                                
                                
                                // basic expression with boundary but only in one row
                                // like
                                /*
                                 def add(num1,num2):
                                 exp:
                                 {add num1 num2}  # just add "add num1 num2" as expression
                                 */
                                
                                else if (trim_input_str[0]=='{'&&trim_input_str[(int)strlen(trim_input_str)-1]=='}'){
                                    Str_addString(&WALLEY_EXPRESSION, append(TEMP_FUNCTION_NAME,append("|",substr(trim_input_str, 2, (int)strlen(trim_input_str)-1))));
                                }
                                
                                
                                // basic expression with boundary and not only in one row
                                // like
                                /*
                                 def add(num1,num2):
                                 exp:
                                 {add
                                 num1
                                 num2
                                 }
                                 
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
            else if (NOW_WRITTING_CLASS == TRUE && CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==TRUE) {
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
            else if (NOW_WRITTING_FOR == TRUE && CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==TRUE) {
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
                            
                            
                            Walley_Parse_Simple_String(struct_var, struct_settings, existing_file, FUNCTION_functions,init_temp_i);
                            
                            
                            Walley_Parse_String_List(struct_var, struct_settings, existing_file, FUNCTION_functions, temp_string_list_in_foor_loop);
                            
                            
                            
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
            if(NOW_WRITTING_SWITCH == TRUE && CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK==TRUE){
                
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
                    Walley_Parse_Simple_String(struct_var, struct_settings, existing_file, FUNCTION_functions, copy_SENTENCE_OF_SWITCH);
                    
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
                    char* temp_output = Walley_Print(struct_var,FUNCTION_functions, token_list[2].TOKEN_STRING);
                    if (PRINT_IN_WHILE_OR_FOR_LOOP==TRUE) {
                        PRINT_STRING_AFTER_LOOP=append(PRINT_STRING_AFTER_LOOP, temp_output);
                    }
                    else{
                        printf("%s", temp_output);
                    }
                    
                    
                }
                else if (strcmp(first_none_whitespace_token.TOKEN_STRING,"println")==0){
                    char* temp_output = Walley_Println(struct_var,FUNCTION_functions, token_list[2].TOKEN_STRING);
                    if (PRINT_IN_WHILE_OR_FOR_LOOP==TRUE) {
                        PRINT_STRING_AFTER_LOOP=append(PRINT_STRING_AFTER_LOOP, temp_output);
                    }
                    else{
                        printf("%s", temp_output);
                    }
                    
                }
                // add new symbolic math support
                else if(strcmp(first_none_whitespace_token.TOKEN_STRING,"syms")==0){
                    struct TOKEN *var_token_list=subtoken(token_list, 2, length_of_token_list);
                    var_token_list=TL_returnTokenListWithoutPunctuation(var_token_list);
                    TL_PrintTOKEN(var_token_list);
                    int length_of_var_token_list=TL_length(var_token_list);
                    
                    int i=1;
                    for (; i<length_of_var_token_list; i++) {
                        char *var_name=var_token_list[i].TOKEN_STRING;
                        if (strcmp(var_token_list[i].TOKEN_CLASS, "W_ID")!=0) {
                            printf("Error.. syms var. var must be valid var_name\n");
                            printf("%s\n",input_str);
                            int start=var_token_list[i].TOKEN_START;
                            printf("%s^\n",Str_appendSpaceAhead("", start));
                            exit(0);
                        }
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
                        Walley_Judge_Run_Anotation_For_While_Def_Class(struct_var, struct_settings, FUNCTION_functions,input_str,token_list);
                    }
                    
                }// ##################################### CHECK RETURN IN FUNCTION, CHECK WHETHER IT CAN RUN OR NOT
                else if (strcmp(first_none_whitespace_token.TOKEN_STRING,"return")==0){
                    printf("");
                }
                //#################### Basic Input To Run #############################
                else {
                    input_str = trim(input_str);
                    //#################### import ####################
                    // Only Import File Module, Can not import the specific function from Module.
                    if (strcmp(first_none_whitespace_token.TOKEN_STRING, "import") == 0) {
                        // Now only support import a   does not support import a,b,c ... at same row
                        //printf("ENTER HERE1\n");
                        
                        
                        //char *name_of_file_to_run = substr(input_str, find(input_str, "import ") + 7, (int) strlen(input_str));
                        char *name_of_file_to_run = token_list[2].TOKEN_STRING;
                        
                        char *as_name="";
                        if(find_not_in_string(name_of_file_to_run," as ")!=-1){
                            as_name=token_list[4].TOKEN_STRING;
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
                        
                        input_str=replace_not_in_string(input_str, "*as", "* as");
                        
                        input_str=trim(input_str);
                        
                        // from a import b as c
                        //  1   2    3   4 5  6
                        if(strcmp(token_list[3].TOKEN_STRING, "import")!=0){
                            Walley_Print_Error(input_str, "from a import b as c... Need keyword 'import'", token_list[3].TOKEN_START);
                        }
                        char *import_file=token_list[2].TOKEN_STRING;
                        char *import_module="";
                        char *as_name="";
                        
                        if(find_not_in_string(input_str," as ")!=-1){
                            import_module=token_list[4].TOKEN_STRING;
                            as_name=token_list[6].TOKEN_STRING;
                        } else {
                            import_module=token_list[4].TOKEN_STRING;
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
                        Walley_Parse_Simple_String(struct_var, struct_settings, existing_file,FUNCTION_functions, content_of_file);
                        Walley_Parse_Simple_String(struct_var, struct_settings, existing_file, FUNCTION_functions,"#End Importing");
                        
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
                    
                    // x=12
                    // or x,y=12,13
                    else if (TL_numOfTOKEN_CLASS(token_list, "W_ASSIGNMENT_OPERATOR")==1){
                        
                        
                        struct TOKEN *var_name_token_list;
                        TL_initTokenList(&var_name_token_list);
                        
                        struct TOKEN *var_value_token_list;
                        TL_initTokenList(&var_value_token_list);
                        
                        int index_of_assignment=TL_indexOfTokenAccordingTokenClassAndNum(token_list, "W_ASSIGNMENT_OPERATOR", 0);
                        
                        var_name_token_list=subtoken(token_list, 1, index_of_assignment);
                        var_value_token_list=subtoken(token_list, index_of_assignment+1, length_of_token_list);
                        
                        var_name_token_list=TL_returnTokenListWithoutPunctuation(var_name_token_list);
                        var_value_token_list=TL_returnTokenListWithoutPunctuation(var_value_token_list);
                        
                        
                        if (TL_length(var_value_token_list)==1) {
                            Walley_Print_Error(input_str, "You need to assign value to var", token_list[index_of_assignment].TOKEN_END+1);
                        }
                        

                        int length_of_var_name_token_list=TL_length(var_name_token_list);
                        int length_of_var_value_token_list=TL_length(var_value_token_list);
                        
                        int i=1;
                        for (; i<length_of_var_name_token_list; i++) {
                            char *var_name=var_name_token_list[i].TOKEN_STRING;
                            char *var_value;
                            if (i>=length_of_var_value_token_list-1) {
                                var_value=var_value_token_list[length_of_var_value_token_list-1].TOKEN_STRING;
                            }
                            else{
                                var_value=var_value_token_list[i].TOKEN_STRING;
                            }
                            
                            // it is class
                            if (checkWhetherSameClassExistedFromVar(CLASS_LIST, var_value)==TRUE) {
                                Walley_Init_Class(struct_var, struct_settings, existing_file, FUNCTION_functions, var_name, var_value);
                            }
                            
                            // it is not class
                            else{
                                char *temp=append(var_name, append("=", var_value));
                                Walley_Eval_And_Update_Var_And_Value_To_Var(struct_var,FUNCTION_functions, temp);
                            }
                        }
                        
                    }
                    // ##############  Is Not Expression ######################
                    
                    
                    
                    //#####################  Mistake  ###################
                    else {
                        
                        // new code on Jan 6 to run
                        // {Hello
                        // World}
                        // kind code
                        char *trim_input_str=trim(input_str);
                        
                        if (trim_input_str[0]=='{'&&trim_input_str[(int)strlen(trim_input_str)-1]!='}') {
                            RUN_EXPRESSION_INCOMPLETE=TRUE;
                            RUN_EXPRESSION_TO_BE_COMPLETE=input_str;
                        }
                        else{
                            
                            // make print 'hello'----><print 'hello'>
                            int sentence_num=numOfSmallSentences(input_str);
                            if (sentence_num>1) {
                                if (input_str[0]!='{') {
                                    input_str=append("{", input_str);
                                    input_str=append(input_str, "}");
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
                        }
                    }
                }
                
            }
        }
        
    }
    
}

void Walley_Parse_String_List(struct VAR **struct_var, struct VAR **struct_settings, char *existing_file, char ***FUNCTION_functions, char **input_str){
    int length=atoi(input_str[0]);
    int i=1;
    for (i=1; i<length; i++) {
        Walley_Parse_Simple_String(struct_var, struct_settings, existing_file, FUNCTION_functions, removeNFromBack(input_str[i]));
    }
}

