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
char *Walley_Run_One_Function_And_Return_Value_From_Var_2(char *input_str,struct VAR **struct_var, char ***FUNCTION_functions);
char *Walley_Substitute_Var_And_Function_According_To_Token(struct TOKEN **token_list,struct VAR **struct_var, char ***FUNCTION_functions);
void Walley_Eval_And_Update_Var_And_Value_To_Var_According_To_Token(struct VAR **struct_var,char ***FUNCTION_functions,struct TOKEN *var_name_token_list,struct TOKEN *var_value_token_list);
void Walley_Judge_Run_Anotation_For_While_Def_Class_According_To_Token(struct VAR **struct_var,struct VAR **struct_settings,char ***FUNCTION_functions, struct TOKEN *token_list);
bool Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function_According_To_Token(struct TOKEN *token_list, struct VAR **struct_var, char ***FUNCTION_functions);

char *Walley_Print_For_Token_List(struct VAR **struct_var, char ***FUNCTION_functions, struct TOKEN *token_list){
    
    char *input_str=Walley_Substitute_Var_And_Function_According_To_Token(&token_list, struct_var, FUNCTION_functions);
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
    return output;
}


// x=Hi()
// x is instance_name
// Hi() is __class__
void Walley_Init_Class(struct VAR **struct_var, struct VAR **struct_settings, char *existing_file, char ***FUNCTION_functions,struct TOKEN *instance_name_token_list, char *__class__){
    
    int length_of_instance_name_token_list=TL_length(instance_name_token_list);
    int i=0;
    
    
    for (i=1; i<length_of_instance_name_token_list; i++) {
        // table or list
        if (strcmp((instance_name_token_list+i)->TOKEN_CLASS,"W_LIST_TABLE")==0) {
            char *inside=substr((instance_name_token_list+i)->TOKEN_STRING, 1, (int)strlen((instance_name_token_list+i)->TOKEN_STRING)-1);
            struct TOKEN *temp_token_list=Walley_Lexica_Analysis(inside);
            inside=Walley_Substitute_Var_And_Function_According_To_Token(&temp_token_list, struct_var, FUNCTION_functions);
            (instance_name_token_list+i)->TOKEN_STRING=append("[", append(inside, "]"));
        }
    }
    char *instance_name=TL_toString(instance_name_token_list);
    
    //instance_name = trim(instance_name);
    
    
        __class__ = trim(__class__);
        char *parameter=substr(__class__,find(__class__,"(")+1,find_not_in_string(__class__,")"));
        char *class_name=substr(__class__, 0, find(__class__,"("));
        
        
        char *after_change=formatStringInClassWithExtendFromVar(*struct_var,CLASS_LIST,class_name,instance_name);
        //printf("#### AFTER CHANGE\n|%s|\n####\n",after_change);
    
        char **after_change_string_list=changeStringToStringList(after_change);
    
        Walley_Parse_String_List(struct_var, struct_settings, existing_file, FUNCTION_functions, after_change_string_list);
    
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
            
            Walley_Run_One_Function_And_Return_Value_From_Var_2(init, struct_var, FUNCTION_functions);
        }
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
                
                Walley_Parse_Simple_String(struct_var, struct_settings, existing_file, FUNCTION_functions,input_str);
                
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
                
                Walley_Parse_Simple_String(struct_var, struct_settings, existing_file, FUNCTION_functions,input_str);
                
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
                
                Walley_Parse_Simple_String(struct_var, struct_settings, existing_file, FUNCTION_functions,input_str);
                
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
                
                Walley_Parse_Simple_String(struct_var, struct_settings, existing_file, FUNCTION_functions,input_str);
                
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
                
                Walley_Parse_Simple_String(struct_var, struct_settings, existing_file, FUNCTION_functions,input_str);
                
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
         Walley_Parse_Simple_String(struct_var, struct_settings, existing_file, FUNCTION_functions, RUN_EXPRESSION_TO_BE_COMPLETE);
     //Walley_Run_For_Appointed_Var(struct_var, struct_settings, save_to_file, existing_file, FUNCTION_functions, RUN_EXPRESSION_TO_BE_COMPLETE);
     RUN_EXPRESSION_TO_BE_COMPLETE="";
     }
     
     // not complete
     else{
     RUN_EXPRESSION_TO_BE_COMPLETE=append(RUN_EXPRESSION_TO_BE_COMPLETE, " ");
     RUN_EXPRESSION_TO_BE_COMPLETE=append(RUN_EXPRESSION_TO_BE_COMPLETE, trim_input_str);
     }
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
                            
                            struct TOKEN *to_judge_token_list=Walley_Lexica_Analysis(to_judge);
                            
                            //printf("==========\n");
                            //TL_PrintTOKEN(to_judge_token_list);
                            
                            bool can_run=Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function_According_To_Token(to_judge_token_list, struct_var, FUNCTION_functions);
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
                    
                    while (Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function_According_To_Token(Walley_Lexica_Analysis(temp_last_while_sentence), struct_var,FUNCTION_functions) == TRUE) {
                        
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
                    
                    CAN_RUN_BASIC_INPUT_IF_CONTINUE_OR_BREAK=TRUE;
                    
                    
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
                    }
                    else {
                        printf("#### For Sentence Only Support list Type At This Time\n");
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
                    
                    char* temp_output = Walley_Print_For_Token_List(struct_var,FUNCTION_functions, subtoken(token_list, 2, length_of_token_list));
                   
                        printf("%s", temp_output);
                    
                    
                }
                else if (strcmp(first_none_whitespace_token.TOKEN_STRING,"println")==0){
                    char* temp_output = Walley_Print_For_Token_List(struct_var,FUNCTION_functions, subtoken(token_list, 2, length_of_token_list));
                   
                        printf("%s\n", temp_output);
                    
                    
                }
                // add new symbolic math support
                else if(strcmp(first_none_whitespace_token.TOKEN_STRING,"syms")==0){
                    struct TOKEN *var_token_list=subtoken(token_list, 2, length_of_token_list);
                    var_token_list=TL_returnTokenListWithoutPunctuation(var_token_list);
                    //TL_PrintTOKEN(var_token_list);
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
                        Walley_Judge_Run_Anotation_For_While_Def_Class_According_To_Token(struct_var, struct_settings, FUNCTION_functions,token_list);
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
                        
                        
                        struct TOKEN_ARRAY var_name_token_array;
                        TA_init(&var_name_token_array);
                        var_name_token_array=TL_returnTokenArrayWithoutPunctuation(var_name_token_list);

                        struct TOKEN_ARRAY var_value_token_array;
                        TA_init(&var_value_token_array);
                        var_value_token_array=TL_returnTokenArrayWithoutPunctuation(var_value_token_list);
                        
                                             
                        if (TL_length(var_value_token_list)==1) {
                            Walley_Print_Error(input_str, "You need to assign value to var", token_list[index_of_assignment].TOKEN_END+1);
                        }
                        

                        int length_of_var_name_token_array=TA_length(var_name_token_array);
                        int length_of_var_value_token_array=TA_length(var_value_token_array);
                        
                        int i=0;
                        for (; i<length_of_var_name_token_array; i++) {
                            struct TOKEN *var_name=var_name_token_array.token_list[i];
                            struct TOKEN *var_value;
                            if (i>=length_of_var_value_token_array-1) {
                                var_value=var_value_token_array.token_list[length_of_var_value_token_array-1];
                            }
                            else{
                                var_value=var_value_token_array.token_list[i];
                            }
                            
                            //printf("var_name-------\n");
                            //TL_PrintTOKEN(var_name);
                            //printf("var_value------\n");
                            //TL_PrintTOKEN(var_value);
                            
                            // for check class
                            int index_of_bracket=find(var_value[1].TOKEN_STRING, "(");
                            if (TL_length(var_value)==2 && index_of_bracket!=-1) {
                                char *check_var_value=var_value[1].TOKEN_STRING;
                                // it is class
                                if (checkWhetherSameClassExistedFromVar(CLASS_LIST, substr(check_var_value,0,index_of_bracket))==TRUE) {
                                    Walley_Init_Class(struct_var, struct_settings, existing_file, FUNCTION_functions, var_name, check_var_value);
                                }
                                // it is not class
                                else{
                                    Walley_Eval_And_Update_Var_And_Value_To_Var_According_To_Token(struct_var, FUNCTION_functions, var_name, var_value);
                                }
                            }
                            else{
                                // it is not class
                                // char *temp=append(var_name, append("=", var_value));
                                // Walley_Eval_And_Update_Var_And_Value_To_Var(struct_var,FUNCTION_functions, temp);
                                Walley_Eval_And_Update_Var_And_Value_To_Var_According_To_Token(struct_var, FUNCTION_functions, var_name, var_value);
                            }
                        
                        }
                        //exit(0);
                        
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
                            /*
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
                             */
                            
                            Walley_Substitute_Var_And_Function_According_To_Token(&token_list, struct_var, FUNCTION_functions);
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

char *Walley_Run_One_Function_And_Return_Value_From_Var_2(char *input_str,struct VAR **struct_var, char ***FUNCTION_functions){
            
    char *function_in_def="[]";
    
    char* return_var_name="None";
    char* return_value = "";
        
    input_str=append(input_str, ":");
    
    //char *func_name=substr(input_str, find(input_str,"def")+3,find(input_str,"("));
    char *func_name=substr(input_str,0,find(input_str,"("));
    
    
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
    
    
    // get the row of function from behind
    int row_of_function=-1;
    int i=length_of_FUNCTION_functions-1;
    for (; i>=1; i--) {
        if (find((*FUNCTION_functions)[i],temp_temp)==0) {
            row_of_function=i;
            find_function=TRUE;
            break;
        }
    }
    
    // function does not exit
    if (row_of_function==-1) {
        Walley_Print_Error(input_str, "Function Does Not Exist", 0);
    }
    
    
    row=row_of_function+1;
    while (row<length_of_FUNCTION_functions) {
        char *arr=(*FUNCTION_functions)[row];
        arr=removeNFromBack(arr);
        if (stringIsEmpty(trim(arr))) {
            row++;
            continue;
        }
        
        if (find_function == TRUE && strcmp("return", substr(trim(arr), 0, 6)) == 0) {
            
            //find_return=TRUE;
            // printf("\n\n\n\n\n--------Find Return--------\n");
            // printf("|%s|\n",arr);
            char *temp_arr=removeNFromBack(arr);
            Walley_Parse_Simple_String(&TEMP_VAR_var, &TEMP_VAR_settings, "None", FUNCTION_functions, temp_arr);
            //Walley_Run_For_Appointed_Var(&TEMP_VAR_var, &TEMP_VAR_settings, &TEMP_TEMP_FILE, "FUNCTION", FUNCTION_functions,temp_arr);
            
            
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
        
        
        /*
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
        */
        
        
        if (find_function == TRUE && find(arr, "#~End") == 0) {
            finish = TRUE;
        }
        
        if (finish == TRUE) {
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
                Walley_Parse_Simple_String(&TEMP_VAR_var, &TEMP_VAR_settings, "None", FUNCTION_functions, arr);
            }
            else{                                
                // begin to define global var
                if (find(trim(arr),"global ")==0) {
                    char *rest=trim(substr(trim(arr),7,(int)strlen(trim(arr))));
                    int num_of_var=count_str(rest, ",")+1;
                    int x=0;
                    for (; x<num_of_var; x++) {
                        char *global_var_name=getParamAccordingToIndex(rest,x);
                        
                        Walley_Update_Var_And_Var_Value_To_Var(&TEMP_VAR_var, global_var_name, Var_getValueOfVar(*struct_var, global_var_name));
                        
                        global_var=list_append(global_var,global_var_name);
                    }
                    row++;
                    continue;
                }
                
                
                Walley_Parse_Simple_String(&TEMP_VAR_var,&TEMP_VAR_settings,"None",FUNCTION_functions,arr);
            }
            
        }
        
        if (begin == TRUE && finish_init_param == FALSE) {
           
            char *arr_arr;
            arr_arr=removeNFromBack(arr);
            arr_arr = removeBackSpace(arr_arr);
            
            if (find_not_in_string(removeAheadSpace(arr_arr), "##Finish Init Params")==0) {
                finish_init_param=TRUE;
                //// finish_init_param
                row++;
                continue;
            }
            
            
            
            if (stringIsEmpty(substr(arr_arr, find_not_in_string(arr_arr, "=")+1, (int)strlen(arr_arr)))==FALSE
                // &&checkWhetherSameVarNameExistsFromFile(file_var_temp_name, substr(arr_arr, 0, find_not_in_string(arr_arr, "=")))==FALSE) {
                &&Var_Existed(TEMP_VAR_var, substr(arr_arr, 0, find_not_in_string(arr_arr, "=")))==FALSE) {
                
                //printf("ENTER HERE1\n");
                
                Walley_Parse_Simple_String(&TEMP_VAR_var, &TEMP_VAR_settings,"FUNCTION",FUNCTION_functions,arr_arr);
            }
            
            if (strcmp(parameter_str, "None,") == 0) {
                //// printf("Params is None\n");
                //finish_init_param = TRUE;
                row++;
                continue;
            }
            
            
            char *var_value;
            if(find_from_index_not_in_str_list_dict(parameter_str, ",",from_index+1)==-1){
                row++;
                continue;
            }
            else{
                var_value = substr(parameter_str, from_index, find_from_index_not_in_str_list_dict(parameter_str, ",", from_index + 1));
            }
            // It is not expression
            if (find_not_in_string(var_value, "=")==-1) {
                // I add this row here on 11 15/ in order to solve initiation problem
                
                struct TOKEN *input_token_list=Walley_Lexica_Analysis(var_value);
                var_value=Walley_Substitute_Var_And_Function_According_To_Token(&input_token_list, struct_var, FUNCTION_functions);
                //var_value=Walley_Substitute_Var_And_Function_Return_Value_From_Var(var_value, struct_var,FUNCTION_functions);
                
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
            //printf("arr_arr -----> %s\n",arr_arr);
            
            
            
            strcat(output, arr_arr);
            strcat(output, substr(parameter_str, from_index, find_from_index_not_in_string(parameter_str, ",", from_index + 1)));
            strcat(output, "\n");
            
            
            if ((int) strlen(removeAheadSpace(removeBackSpace(arr_arr))) != 0){
                Walley_Parse_Simple_String(&TEMP_VAR_var, &TEMP_VAR_settings,"None",FUNCTION_functions,arr_arr);
                //Walley_Run_For_Appointed_Var(&TEMP_VAR_var, &TEMP_VAR_settings,&TEMP_TEMP_FILE,"FUNCTION",FUNCTION_functions,arr_arr);
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
    
    
    Walley_Parse_Simple_String(&TEMP_VAR_var, &TEMP_VAR_settings, "None", FUNCTION_functions, "#end function");
    //Walley_Run_For_Appointed_Var(&TEMP_VAR_var, &TEMP_VAR_settings, &TEMP_TEMP_FILE, "FUNCTION", FUNCTION_functions,"#end function");
    
    
    //printf("Now the functions in def is %s\n",function_in_def);
    int num_of_temp_func=valueNumOfList(function_in_def);
    int a=0;
    
    
    while (a<num_of_temp_func) {
        char *temp_func_name=toCString(valueOfListAtIndex(function_in_def, a));
        //printf("##temp_func_name is %s\n",temp_func_name);
        deleteOneFunctionFromBehind(FUNCTION_functions, temp_func_name);
        a++;
    }
    
    i=0;
    int length_of_global_var=valueNumOfList(global_var);
    for (; i<length_of_global_var; i++) {
        char *global_var_name=valueOfListAtIndex(global_var, i);
        Walley_Update_Var_And_Var_Value_To_Var(struct_var, global_var_name, Var_getValueOfVar(TEMP_VAR_var,global_var_name));
    }
    
    
    copyInstanceValueBackToVar(TEMP_VAR_var, struct_var,INSTANCE_NAMES_LIST);
    function_in_def="";
    
    return return_value;
}


/*
 I did not replace content in ()
 */
char *Walley_Substitute_Var_And_Function_According_To_Token(struct TOKEN **token_list,struct VAR **struct_var, char ***FUNCTION_functions){//, char *file_function_name){
    // printf("#### Walley_Substitute_Var_And_Function_Return_Value_From_File ####\n");
    //printf("$$$ input str is |%s| ####\n",input_str);
    
    int length_of_token_list=TL_length(*token_list);
    if (length_of_token_list==2) {
        if (strcmp((*token_list+1)->TOKEN_CLASS, "W_NUMBER")==0) {
            return (*token_list+1)->TOKEN_STRING;
        }
        else if (strcmp((*token_list+1)->TOKEN_CLASS, "W_STRING")==0) {
            return (*token_list+1)->TOKEN_STRING;
        }
    }
       
    
    int i=0;
       
    //###############################################################################################################
    //###############################################################################################################
    //###############################################################################################################
    //################################# New Expression code #########################################################
    //###############################################################################################################
    //###############################################################################################################
    
    for (i=1; i<length_of_token_list; i++) {
        // table or list
        if (strcmp((*token_list+i)->TOKEN_CLASS,"W_DICTIONARY")==0) {
            char *inside=substr((*token_list+i)->TOKEN_STRING, 1, (int)strlen((*token_list+i)->TOKEN_STRING)-1);
            char *best_match_sentence=bestMathSentenceForExpression(inside,WALLEY_EXPRESSION);
            char *with_str = Walley_Translate_To_Function_From_Var(inside, best_match_sentence,struct_var);
            struct TOKEN *temp_token_list=Walley_Lexica_Analysis(with_str);
            inside=Walley_Substitute_Var_And_Function_According_To_Token(&temp_token_list, struct_var, FUNCTION_functions);
            (*token_list+i)->TOKEN_STRING=inside;
            (*token_list+i)->TOKEN_CLASS=TOKEN_analyzeTokenClass(inside);
        }
    }

       
    for (i=1; i<length_of_token_list; i++) {
        // table or list
        if (strcmp((*token_list+i)->TOKEN_CLASS,"W_LIST_TABLE")==0) {
            char *inside=substr((*token_list+i)->TOKEN_STRING, 1, (int)strlen((*token_list+i)->TOKEN_STRING)-1);
            struct TOKEN *temp_token_list=Walley_Lexica_Analysis(inside);
            inside=Walley_Substitute_Var_And_Function_According_To_Token(&temp_token_list, struct_var, FUNCTION_functions);
            (*token_list+i)->TOKEN_STRING=append("[", append(inside, "]"));
        }
    }
    
 
    
    struct TOKEN *output_token;
    TL_initTokenList(&output_token);
    
    struct TOKEN temp_token;
    
    i=1;
    for (; i<length_of_token_list; i++) {
        
        char *token_class=(*token_list)[i].TOKEN_CLASS;
        char *token_string=(*token_list)[i].TOKEN_STRING;
        struct TOKEN next=TOKEN_nextToken(*token_list, i);
        
        if (strcmp(token_class, "W_ID")==0) {
            
            // it is slice
            // x[0]
            // x[0][0]
            if (strcmp(next.TOKEN_CLASS,"W_LIST_TABLE")==0||next.TOKEN_STRING[0]=='.') {
                
                SAVE_VAR_NAME_TO_CHECK_WHETHER_IT_IS_INSTANCE=token_string;
                
                char *var_value=Var_getValueOfVar(*struct_var, token_string);
                
                i=i+1;
                Walley_Next(*token_list, &i, &var_value, struct_var, *FUNCTION_functions);
                i=i-1;
                temp_token.TOKEN_STRING=var_value;
            }
            
            // it is just var
            else if (find((*token_list)[i].TOKEN_STRING,"(")==-1) {
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
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);                    char* temp_output = Walley_Println(struct_var,FUNCTION_functions, temp_value);
                    
                        printf("%s", temp_output);
                    
                    return_value="None";
                }//#####################  print  ###################
                else if (strcmp(func_name, "walley_print") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    char* temp_output = Walley_Print(struct_var,FUNCTION_functions, temp_value);
                   
                        printf("%s", temp_output);
                    
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
                        
                        Walley_Parse_Simple_String(&VAR_VAR_FOR_EMBED, &VAR_SETTINGS_FOR_EMBED, "None", &FUNCTION_FOR_EMBED, string_in_out_wy);
                        //Walley_Run_For_Appointed_Var(&VAR_VAR_FOR_EMBED, &VAR_SETTINGS_FOR_EMBED, &TEMP_FILE_FOR_EMBED, "None", &FUNCTION_FOR_EMBED, string_in_out_wy);
                    }
                    
                    
                    
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitute_Var_And_Function_Return_Value_From_Var(temp1, struct_var,FUNCTION_functions);
                    Walley_Parse_Simple_String(&VAR_VAR_FOR_EMBED, &VAR_SETTINGS_FOR_EMBED, "None", &FUNCTION_FOR_EMBED, toCString(temp_value));
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
                                        
                    return_value = Walley_Run_One_Function_And_Return_Value_From_Var_2(function,struct_var,FUNCTION_functions);
                }
                
                temp_token.TOKEN_STRING=return_value;
            }
        }
        
        
        else if (strcmp(token_class, "W_STRING")==0){
            if (strcmp(next.TOKEN_CLASS,"W_LIST_TABLE")==0||next.TOKEN_STRING[0]=='.') {
                char *var_value=token_string;
                i=i+1;
                Walley_Next(*token_list, &i, &var_value, struct_var, *FUNCTION_functions);
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
                Walley_Next(*token_list, &i, &var_value, struct_var, *FUNCTION_functions);
                i=i-1;
                temp_token.TOKEN_STRING=var_value;
            }
            else{
                temp_token.TOKEN_STRING=token_string;
            }
        }
        else if(strcmp(token_class, "W_TRUE_OR_FALSE")==0){
            if (strcmp(token_string, "TRUE")==0) {
                temp_token.TOKEN_STRING="1";
            }
            else{
                temp_token.TOKEN_STRING="0";
            }
        }
        else {
            temp_token.TOKEN_STRING=token_string;
        }
        
        
        
        temp_token.TOKEN_CLASS=TOKEN_analyzeTokenClass(temp_token.TOKEN_STRING);
        TL_addToken(&output_token, temp_token);
    }
    
    
    
    
    //TOKEN_PrintTOKEN(output_token);
    //char *output2=TL_toString(output_token);
    //printf("output2---> %s\n",output2);
    char *output=TL_toString(output_token);
    
    
    
    
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


void Walley_Eval_And_Update_Var_And_Value_To_Var_According_To_Token(struct VAR **struct_var,char ***FUNCTION_functions,struct TOKEN *var_name_token_list,struct TOKEN *var_value_token_list) {
    
    int length_of_var_name_token_list=TL_length(var_name_token_list);
    int length_of_var_value_token_list=TL_length(var_value_token_list);
    
    // new code here on Jan 12 to solve x[i][j]=x[i][j]+3, replace var_name x[i][j] problem
    int i=0;
    

    for (i=1; i<length_of_var_name_token_list; i++) {
        // table or list
        if (strcmp((var_name_token_list+i)->TOKEN_CLASS,"W_LIST_TABLE")==0) {
            char *inside=substr((var_name_token_list+i)->TOKEN_STRING, 1, (int)strlen((var_name_token_list+i)->TOKEN_STRING)-1);
            struct TOKEN *temp_token_list=Walley_Lexica_Analysis(inside);
            inside=Walley_Substitute_Var_And_Function_According_To_Token(&temp_token_list, struct_var, FUNCTION_functions);
            (var_name_token_list+i)->TOKEN_STRING=append("[", append(inside, "]"));
        }
    }

    
    // Unfinish Var Value
    if (strcmp(var_value_token_list[length_of_var_value_token_list-1].TOKEN_CLASS,"W_UNFINISHED_VAR")==0) {
        
        
        // new code here on Jan 6
        char *var_name=TL_toString(var_name_token_list);
        char *var_value=var_value_token_list[length_of_var_value_token_list-1].TOKEN_STRING;
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

    }
    
    
    
    
    
    
    
    if (VAR_VALUE_INCOMPLETE==FALSE) {
        
        
        char *var_name=TL_toString(var_name_token_list);
                        
        char *var_value=Walley_Substitute_Var_And_Function_According_To_Token(&var_value_token_list, struct_var, FUNCTION_functions);
        
        //printf("#### The Variable Name is :%s\n", var_name);
        //printf("#### The Variable Value is :%s\n", var_value);
        //printf("#### The Variable Value Type is :%s\n", var_value_type);
        //printf("The Variable Value after put known Variable in is :%s\n",putKnownVariableIntoExpression(var_value));
        
        /*
         // New code on Dec 16.
         // To solve x[0]="Hel" problem
         */
        //##########################################################################
        /*
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
         */
        //##########################################################################
        
        // ################### Basic Calculation ##################################
        //if(strcmp(var_value_type,"unknown type")!=0){//&&strcmp(var_value_type,"function")!=0){
        
        Walley_Update_Var_And_Var_Value_To_Var(struct_var,var_name,var_value);
    }
}



bool Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function_According_To_Token(struct TOKEN *token_list, struct VAR **struct_var, char ***FUNCTION_functions){
    // I did not consider the situation when and or or is in string
    
    //input_str=replace_not_in_string(input_str, " and ", "+++++");
    //input_str=replace_not_in_string(input_str, " or ", "----");
    
    int lenght_of_token_list=TL_length(token_list);
    int i=0;
    for (i=1; i<lenght_of_token_list; i++) {
        if (strcmp(token_list[i].TOKEN_STRING, "TRUE")==0) {
            token_list[i].TOKEN_STRING="1";
            token_list[i].TOKEN_CLASS="W_NUMBER";
        }
        if (strcmp(token_list[i].TOKEN_STRING, "FALSE")==0) {
            token_list[i].TOKEN_STRING="0";
            token_list[i].TOKEN_CLASS="W_NUMBER";
        }
    }
    
    
    /*
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
     */
    //######### if not 3>4: #########
    //############# Add Not #########
    
    //input_str=replace_not_in_string(input_str, "not ", "*****");
    
    //input_str=Walley_Substitute_Var_And_Function_Return_Value_From_Var(input_str,struct_var,FUNCTION_functions);
    
    //input_str=replace_not_in_string(input_str, "+++++", " and ");
    //input_str=replace_not_in_string(input_str, "----", " or ");
    //input_str=replace_not_in_string(input_str, "*****","not ");
    
    //input_str=replace_not_in_string(input_str, "TRUE==", "1==");
    //input_str=replace_not_in_string(input_str, "FALSE==", "0==");
    
    char *after_substitute=Walley_Substitute_Var_And_Function_According_To_Token(&token_list, struct_var,FUNCTION_functions);
    
    //printf("after_substitute---> %s\n",after_substitute);
    
    bool output=judgeWithAndAndOrWithParenthesis(after_substitute);
    return output;
}


void Walley_Judge_Run_Anotation_For_While_Def_Class_According_To_Token(struct VAR **struct_var,struct VAR **struct_settings,char ***FUNCTION_functions, struct TOKEN *token_list) {
    
    struct TOKEN first_none_whitespace_token=token_list[1];
    int length_of_token_list=TL_length(token_list);
    
    if (strcmp(first_none_whitespace_token.TOKEN_STRING,"class")==0){
        CLASS_NUM++;
        if (HAVE_INIT_CLASS_LIST==FALSE) {
            Str_initStringList(&INSTANCE_NAMES_LIST);
            CLASS_initCLASSList(&CLASS_LIST);
            HAVE_INIT_CLASS_LIST=TRUE;
        }
        NOW_WRITTING_CLASS=TRUE;
        SPACE_OF_FIRST_CLASS_SENTENCE=REQUIRED_SPACE;
        REQUIRED_SPACE=REQUIRED_SPACE+4;
        
        
        // class X:
        //  1    23
        // class x extends Y:
        //  1    2  3      45
        char *class_name=token_list[2].TOKEN_STRING;
        char *class_mother;
        if (length_of_token_list==6) {
            class_mother=token_list[4].TOKEN_STRING;
        }
        else{
            class_mother="None";
        }
        CLASS_addProperty(&CLASS_LIST, class_name, class_mother, "#Begin to define class...\n");
        //CLASS_PrintCLASS(CLASS_LIST);
    }
    // ##############  Function  ##############################
    else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "def") == 0) {
        // def add(num1,num2) :
        //  1   2             3
        SPACE_OF_FIRST_DEF_SENTENCE = REQUIRED_SPACE;
        REQUIRED_SPACE = REQUIRED_SPACE + 4;
        
        NOW_WRITTING_FUNCTION = TRUE;
        
        int index_of_left_bracket=find(token_list[2].TOKEN_STRING, "(");
        int index_of_right_bracket=find_from_behind(token_list[2].TOKEN_STRING,")");
        if (index_of_left_bracket==-1||index_of_right_bracket==-1) {
            Walley_Print_Error(CURRENT_INPUT_STR, "Define function wrong..\nFormat def add(num1,num2):\nNeed ()", token_list[2].TOKEN_START);
        }
        
        char *func_name = substr(token_list[2].TOKEN_STRING, 0, index_of_left_bracket);
        char *func_param_str = substr(token_list[2].TOKEN_STRING, index_of_left_bracket+1, index_of_right_bracket);
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
        

        // if x == 2 :
        //  1 2  3 4 5
        
        Str_initStringList(&IF_ELIF_ELSE.if_elif_else);
        
        //char *string_in_if=trim(substr(trim_input_str, find(trim_input_str,"if ")+3, find_from_behind(trim_input_str, ":")));
        char *string_in_if=TL_toString(subtoken(token_list, 2, length_of_token_list-1));
        
        Str_addString(&IF_ELIF_ELSE.if_elif_else,string_in_if);
        
        IF_ELIF_ELSE.content=(char***)malloc(sizeof(char**)*(INDEX_OF_IF_ELIF_ELSE+1));
        Str_initStringList(&IF_ELIF_ELSE.content[0]);
        
        
    }
    
    //#################### While Sentence ##################################
    else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "while") == 0) {
        
        // while x < 2 :
        //  1    2 3 4 5
        
        char *last_while_sentence =TL_toString(subtoken(token_list, 2, length_of_token_list-1));
        LAST_WHILE_SENTENCE=last_while_sentence;
        
        bool can_run_while = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(last_while_sentence, struct_var,FUNCTION_functions);
        if (can_run_while == FALSE) {
            //// printf("Can Not Run While");
            NOW_WRITTING_WHILE = FALSE;
        } else {
            NOW_WRITTING_WHILE = TRUE;
            SPACE_OF_FIRST_WHILE_SENTENCE=REQUIRED_SPACE;
            REQUIRED_SPACE = REQUIRED_SPACE + 4;
            
            
          
        }
        
        
        
    }        //#################### For Sentence #####################################
    else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "for") == 0) {// && removeBackSpace(input_str)[(int) strlen(removeBackSpace(input_str)) - 1] == ':') {
        //printf("#### Find For ####\n");
        
        // for i in range(5) :
        //  1  2  3  4       5
        
        if (length_of_token_list!=6) {
            Walley_Print_Error(CURRENT_INPUT_STR, "Error.  For statement wrong\nTry 'for i in range(5):' format\n", 0) ;
            printf("Error.  For statement wrong\n");
        }
        
        if (strcmp(token_list[3].TOKEN_STRING,"in")!=0) {
            Walley_Print_Error(CURRENT_INPUT_STR, "Error. 'in' is needed in for statement\n", token_list[3].TOKEN_START);
        }
        
        
        //char *temp_i = substr(input_str, find(input_str, "for ") + 4, find(input_str, " in"));
        //temp_i = removeAheadSpace(removeBackSpace(temp_i));
        char *temp_i=token_list[2].TOKEN_STRING;
        //char *in_what = substr(input_str, find(input_str, " in ") + 4, (int) strlen(removeBackSpace(input_str)) - 1);
        char *in_what=token_list[4].TOKEN_STRING;
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
        
        
       
        
        
        // Write temp_i_in_for_sentence to __temp_for__  eg
        // for i in [1,2,3,4]:     write [1,2,3,4] to __temp_for__
        
    }
    else if (strcmp(first_none_whitespace_token.TOKEN_STRING, "switch")==0){
        SPACE_OF_FIRST_SWITCH_SENTENCE = REQUIRED_SPACE;
        REQUIRED_SPACE = REQUIRED_SPACE + 4;
        
        NOW_WRITTING_SWITCH = TRUE;
        

        // switch x :
        //  1     2 3
        
        char *switch_object=token_list[2].TOKEN_STRING;
        SWITCH_OBJECT=trim(switch_object);
        
    }
    
    
}


