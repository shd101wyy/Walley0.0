/* 
 * File:   walley_agent.h
 * Author: shd101wyy
 *
 * Created on September 30, 2012, 4:53 PM
 */

#include "walley_core.h"
/*
void Walley_Agent_Respond(char **walley_language_file,char **walley_language_similarity_file, char **walley_language_verb_file,struct VAR struct_var[], struct VAR struct_settings[], char *temp_file[], char* existing_file, char* input_str) {
    //printf("######### Run Function Walley_Agent_Respond ######\n");
    
    // delete #.... after sentence
    char *temp_input_str2=trim(input_str);
    int index_of_jing=find_not_in_string(temp_input_str2, "#");
    
    bool now_in_annotation=0;
    
    if(index_of_jing!=-1 && index_of_jing !=0 && (index_of_jing>=1 && input_str[index_of_jing-1]!='~')){
        if (index_of_jing!=(int)strlen(input_str)-1 && input_str[index_of_jing+1]=='~') {
            now_in_annotation=1;
        }
        input_str=substr(input_str, 0, find_not_in_string(input_str, "#"));
        
    }
    input_str=removeBackSpace(input_str);
   // printf("Now input_str is %s\n",input_str);
    //

    
    char *translate_to=Walley_Translate(walley_language_file,walley_language_similarity_file,walley_language_verb_file,struct_var,input_str);
   // printf("TRANSLATE TO is %s\n",translate_to);
    
    translate_to=stringToLowerCase(translate_to);
    translate_to=removeSpaceForDictionaryListAndParenthesis(translate_to);
    if(find_not_in_string(translate_to," (")!=-1)
        translate_to=replace_not_in_string(translate_to," (","(");
    if(find_not_in_string(translate_to," :")!=-1)
        translate_to=replace_not_in_string(translate_to," :",":");
    if (find_not_in_string(translate_to, "true")!=-1)
        translate_to=replace_not_in_string(translate_to, "true","TRUE");
    if (find_not_in_string(translate_to, "false")!=-1)
        translate_to=replace_not_in_string(translate_to, "false","FALSE");
    //// printf("TRANSLATE TO is %s\n",translate_to);
    //Walley_Run_Fourth_Generation(file_var_name,setting_file,temp_file,existing_file,translate_to);
    Walley_Run_For_Appointed_Var(struct_var,struct_settings,temp_file,existing_file,translate_to);
    if (now_in_annotation==1) {
        Var_changeValueOfVar(struct_settings,"now_in_annotation", "1", "int");
    }
}
*/
void Walley_Agent_Respond(char **walley_language_file,char **walley_language_similarity_file, char **walley_language_verb_file,struct VAR struct_var[], struct VAR struct_settings[], char *temp_file[], char* existing_file, char* input_str) {
    //printf("######### Run Function Walley_Agent_Respond ######\n");
    //printf("input_str----->%s\n",input_str);
    // printf("ENTER HERE\n");
    
    //############################################################################################################################
    //############################################################################################################################
    //############################################################################################################################
    //############
    //############         I move this ahead
    //############
    //############################################################################################################################
    //############################################################################################################################
    //############################################################################################################################

    bool continue_run = FALSE;
    bool find_gang_gang = FALSE;
    bool str_is_empty=FALSE;
    
    char *temp_input_str=input_str;
        
    if (find_not_in_string(input_str, "\n") != -1) {
        //// printf("find \\n");
        continue_run = TRUE;
        input_str = substr(input_str, 0, find(input_str, "\n"));
        //Walley_Run_For_Appointed_Var(struct_var,setting_file,substr(temp_input_str,find(temp_input_str,"\n")+1,(int)strlen(temp_input_str)));
    }
    
    if (find_not_in_string(input_str, "\\n") != -1) {
        //printf("find \\n");
        //// printf("find \\\\n");
        continue_run = TRUE;
        find_gang_gang = TRUE;
        input_str = substr(input_str, 0, find(input_str, "\\n"));
        //Walley_Run_For_Appointed_Var(struct_var,setting_file,substr(temp_input_str,find(temp_input_str,"\n")+1,(int)strlen(temp_input_str)));
    }
    //############################################################################################################################
    //############################################################################################################################
    //############################################################################################################################

    
    
    // delete #.... after sentence
    char *temp_input_str2=trim(input_str);
    int index_of_jing=find_not_in_string(temp_input_str2, "#");
    
    bool now_in_annotation2=0;
    
    if(index_of_jing!=-1 && index_of_jing !=0 && (index_of_jing>=1 && input_str[index_of_jing-1]!='~')){
        if (index_of_jing!=(int)strlen(input_str)-1 && input_str[index_of_jing+1]=='~') {
            now_in_annotation2=1;
        }
        input_str=substr(input_str, 0, find_not_in_string(input_str, "#"));
        
    }
    input_str=removeBackSpace(input_str);
    
    char *translate_to=Walley_Translate(walley_language_file,walley_language_similarity_file,walley_language_verb_file,struct_var,input_str);
        
    translate_to=stringToLowerCase(translate_to);
    translate_to=removeSpaceForDictionaryListAndParenthesis(translate_to);
    if(find_not_in_string(translate_to," (")!=-1)
        translate_to=replace_not_in_string(translate_to," (","(");
    if(find_not_in_string(translate_to," :")!=-1)
        translate_to=replace_not_in_string(translate_to," :",":");
    if (find_not_in_string(translate_to, "true")!=-1)
        translate_to=replace_not_in_string(translate_to, "true","TRUE");
    if (find_not_in_string(translate_to, "false")!=-1)
        translate_to=replace_not_in_string(translate_to, "false","FALSE");
    //// printf("TRANSLATE TO is %s\n",translate_to);
    //Walley_Run_Fourth_Generation(file_var_name,setting_file,temp_file,existing_file,translate_to);
    //Walley_Run_For_Appointed_Var(struct_var,struct_settings,temp_file,existing_file,translate_to);
    //Walley_Agent_Respond(walley_language_file, walley_language_similarity_file, walley_language_verb_file, struct_var, struct_settings, temp_file, existing_file, input_str);
    if (now_in_annotation2==1) {
        Var_changeValueOfVar(struct_settings,"now_in_annotation", "1", "int");
    }
//############################################################################################################################
    //############################################################################################################################
    //############################################################################################################################
    //############################################################################################################################
    //#####This is nearly the same as Walley_Run_For_Appointed_Var but function Walley_Run_For_Appointed_Var is changed
    //#####to Walley_Agent_Respond....
    //############################################################################################################################
    //############################################################################################################################
    //############################################################################################################################
    //############################################################################################################################

    input_str=removeNFromBack(translate_to);
    
    //####################  Auto clean variables  #########################################
    int turn = atoi(Var_getValueOfVar(struct_settings , "turn"));
    turn=turn+1;
    Var_changeValueOfVar(struct_settings , "turn", numToCString(turn), "int");
    if (turn%10==0) {
        //printf("Begin cleaning variables\n");
        //printf("Before cleaning::\n");
        //Var_PrintVar(struct_var);
        Walley_Clean_Variables(existing_file, struct_var, turn);
        //printf("Finish cleaning variables\n");
        //printf("After cleaning::\n");
        //Var_PrintVar(struct_var);
    }
    //######################################################################################
    
    
    bool now_in_annotation = atoi(Var_getValueOfVar(struct_settings, "now_in_annotation"));
    char *judge_annotation_string=trim(input_str);
    int length_of_judge_annotation_string=(int)strlen(judge_annotation_string);
    if (judge_annotation_string[length_of_judge_annotation_string-1]=='#' && judge_annotation_string[length_of_judge_annotation_string-2]=='~'){
        //printf("Now End Long Annotation");
        now_in_annotation = 0;
        char temp4[100];
        sprintf(temp4, "%d", now_in_annotation);
        //Var_changeValueOfVar(struct_settings , "now_in_annotation", (char*) temp4, "int");
        Var_changeValueOfVar(struct_settings,"now_in_annotation", append("",temp4), "int");
    }
    else if (judge_annotation_string[0] == '#' && judge_annotation_string[1] == '~') {
        //// printf("Now Begin Long Annotation");
        now_in_annotation = 1;
        char temp4[100];
        sprintf(temp4, "%d", now_in_annotation);
        //Var_changeValueOfVar(struct_settings , "now_in_annotation", (char*) temp4, "int");
        Var_changeValueOfVar(struct_settings, "now_in_annotation",append("",temp4), "int");
    }
    
    if(now_in_annotation==0){
                //printf("TEMP IS %s\n",temp_input_str);
        //if(input_str[(int)strlen(input_str)-1]=='\n')
        //    input_str=substr(input_str,0,(int)strlen(input_str)-1);
        //printf("here 5\n");
        //printf("\n\n\n\n|%s|\n\n\n\n",input_str);
        //writeStringToFile(temp_file, input_str);
        //writeStringToFile(temp_file, "\n");
        Str_addString(temp_file, input_str);
        
        //###### Initialize Space ######
        //printf("here 6\n");
        //printf("\n\n\n\n|%s|\n\n\n\n",input_str);
        int space = atoi(Var_getValueOfVar(struct_settings , "space"));
        bool now_writting_function = atoi(Var_getValueOfVar(struct_settings , "now_writting_function"));
        bool now_writting_class = atoi(Var_getValueOfVar(struct_settings , "now_writting_class"));
        bool now_writting_while = atoi(Var_getValueOfVar(struct_settings , "now_writting_while"));
        bool now_writting_for = atoi(Var_getValueOfVar(struct_settings , "now_writting_for"));
        bool now_run_if = atoi(Var_getValueOfVar(struct_settings , "now_run_if"));
        char *last_if_sentence = Var_getValueOfVar(struct_settings , "last_if_sentence");
        char *last_while_sentence = Var_getValueOfVar(struct_settings , "last_while_sentence");
        char *string_in_while_loop = Var_getValueOfVar(struct_settings , "string_in_while_loop");
        char *string_in_for_loop = Var_getValueOfVar(struct_settings , "string_in_for_loop");
        char *temp_i = Var_getValueOfVar(struct_settings , "temp_i");
        char *temp_i_in_for_sentence = Var_getValueOfVar(struct_settings , "temp_i_in_for_sentence");
        int space_of_first_while_sentence = atoi(Var_getValueOfVar(struct_settings , "space_of_first_while_sentence"));
        int space_of_first_for_sentence = atoi(Var_getValueOfVar(struct_settings , "space_of_first_for_sentence"));
        int space_of_first_def_sentence = atoi(Var_getValueOfVar(struct_settings , "space_of_first_def_sentence"));
        int space_of_first_class_sentence = atoi(Var_getValueOfVar(struct_settings , "space_of_first_class_sentence"));
        
        //I add this value here in order to run now_run_if.
        bool can_run_basic_input = TRUE;
        bool run_goto = FALSE;
        
        
        int current_space = numOfSpaceAheadString(input_str);
        char temp2[100];
        sprintf(temp2, "%d", current_space);
        Var_changeValueOfVar(struct_settings , "current_space", append("",temp2), "int");
        
        
        //printf("\n\n\n\n|%s|\n\n\n\n",input_str);
        
        // delete #.... after sentence
        char *temp_input_str2=trim(input_str);
        int index_of_jing=find_not_in_string(temp_input_str2, "#");
        if(index_of_jing!=-1 && index_of_jing !=0){
            input_str=substr(input_str, 0, find_not_in_string(input_str, "#"));
        }
        //
        
        //printf("-------Now input is |%s|\n", input_str);
        //printf("-------Current Space is |%d|\n",current_space);
        //printf("temp2 is %s\n",temp2);
        //printf("-------Now Ahead Space is %d\n",current_space);
        // printf("-------Now writting in function is %d\n",now_writting_function);
        
        //################## Judge Whether this whether an if sentence ##########################
        //if(find(removeAheadSpace(input_str),"if ")==0)
        //    now_run_if=TRUE;
        // I move this judge below
        //#######################################################################################
        /*
         if (current_space == 0 && stringIsEmpty(input_str) == FALSE && removeAheadSpace(input_str)[0] != '#') {
         //printf("------Ahead Space is 0");
         if (now_writting_function == TRUE) {
         //printf("--------Finish defining function--------\n");
         Str_addString(FUNCTION, "#~End\n\n");
         //cleanFunctionFile("FUNCTION");
         }
         if (now_run_if == TRUE) {
         printf("Finish If");
         }
         now_writting_function = FALSE;
         now_writting_class = FALSE;
         now_run_if = FALSE;
         space = 0;
         }**/
        
        if ((int) strlen(input_str) == 0 || stringIsEmpty(input_str) == TRUE) {
            can_run_basic_input = FALSE;
            str_is_empty=TRUE;
            //// printf("Input Str is Empty\n");
            //// printf("now_writting_function is %d\n",now_writting_function);
            //// printf("now_writting_while is %d\n",now_writting_while);
        }
        if (current_space > space) {
            can_run_basic_input = FALSE;
        }
        //printf("-------Now Ahead Space is %d\n-------Now Required Space is %d\n",numOfSpaceAheadString(input_str),space);
        //printf("-------Now writting in function is %d\n",now_writting_function);
        
        
        //############### Now Writting While In Progress ########################
        if (now_writting_while == TRUE && str_is_empty==FALSE) {
            //// printf("Space %d, Current Space %d\n", space, current_space);
            if (current_space > space_of_first_while_sentence && current_space % 4 == 0) {
                // printf("################ Now Writting While ###################");
                can_run_basic_input = FALSE;
                input_str = removeAheadSpaceForNum(input_str, space_of_first_while_sentence + 4);
                //// printf("Input str is |%s|\n", input_str);
                char *temp_in_loop = malloc(sizeof (char) *((int) strlen(input_str)+(int) strlen(string_in_while_loop) + 2));
                strcat(temp_in_loop, substr(string_in_while_loop, 0, (int) strlen(string_in_while_loop) - 1));
                strcat(temp_in_loop, input_str);
                strcat(temp_in_loop, "\\n\"");
                string_in_while_loop = temp_in_loop;
                Var_changeValueOfVar(struct_settings , "string_in_while_loop", string_in_while_loop, "string");
            } else if (current_space <= space_of_first_while_sentence && current_space % 4 == 0) {
                // printf("Begin to Run While, input_str %s, current_space %d, space_of_first %d\n",input_str,current_space,space_of_first_while_sentence);
                can_run_basic_input = TRUE;
                now_writting_while = FALSE;
                
                char temp3[100];
                sprintf(temp3, "%d", now_writting_while);
                Var_changeValueOfVar(struct_settings , "now_writting_while", append("",temp3), "int");
                space=current_space;
                sprintf(temp3, "%d", space);
                Var_changeValueOfVar(struct_settings , "space", append("",temp3), "int");
                
                //get __temp_while__ to get last_while_sentence
                char *__temp_while__=Var_getValueOfVar(struct_var,"__temp_while__");
                //// printf("__temp_while__ is %s\n",__temp_while__);
                int length_of_list=valueNumOfList(__temp_while__);
                char *last_while_sentence2=valueOfListAtIndex(__temp_while__,length_of_list-1);
                //// printf("Last_While_Sentence is %s\n",last_while_sentence2);
                
                //get __temp_string_in_while_loop__
                char *__temp_string_in_while_loop__=Var_getValueOfVar(struct_var,"__temp_string_in_while_loop__");
                //// printf("BEFORE APPEND -->|%s|\n",__temp_string_in_while_loop__);
                //// printf("STRING IN WHILE LOOP-->|%s|\n",string_in_while_loop);
                __temp_string_in_while_loop__=listAppendOneElement(__temp_string_in_while_loop__,string_in_while_loop);
                
                //changeTheWholeVarValueFromItsInitialOneFromFileForList(struct_var,"__temp_string_in_while_loop__",__temp_string_in_while_loop__);
                changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, "__temp_string_in_while_loop__", __temp_string_in_while_loop__);
                
                //// printf("AFTER CHANGE %s\n",__temp_string_in_while_loop__);
                string_in_while_loop="\"#While\\n\"";
                Var_changeValueOfVar(struct_settings , "string_in_while_loop", string_in_while_loop, "string");
                char *string_in_while_loop2=valueOfListAtIndex(__temp_string_in_while_loop__,length_of_list-1);
                //// printf("String in while loop is %s\n",string_in_while_loop2);
                
                //while (Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function_Second_Generation(last_while_sentence, file_name) == TRUE) {
                while (Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(last_while_sentence2, struct_var) == TRUE) {
                    char *temp_to_run = substr(string_in_while_loop2, 1, (int) strlen(string_in_while_loop2) - 1);
                    //printf("Temp To Run is %s\n",temp_to_run);
                    
                    char *temp_to_run2=temp_to_run;
                    while (find_not_in_string(temp_to_run, "\\n")!=-1) {
                        int index_of_gang_n=find_from_index_not_in_string(temp_to_run, "\\n", 1);
                        //printf("index_of_gang_n is %d\n",index_of_gang_n);
                        temp_to_run2=substr(temp_to_run, 0, index_of_gang_n);
                        temp_to_run=substr(temp_to_run, index_of_gang_n+2, (int)strlen(temp_to_run));
                        //if(strcmp(trim(temp_to_run2),"pass")==0){
                        //    can_break=TRUE;
                        //    break;
                        //}
                        //if(strcmp(trim(temp_to_run2),"continue")==0){
                        //    can_continue=TRUE;
                        //    break;
                        //}
                        ////  printf("\ntemp to run |%s|\n",temp_to_run);
                        Walley_Agent_Respond(walley_language_file, walley_language_similarity_file, walley_language_verb_file, struct_var, struct_settings, temp_file, existing_file, temp_to_run);
                        //Walley_Run_For_Appointed_Var(struct_var,setting_file,temp_file,temp_to_run);
                    }
                    
                    bool can_break=FALSE;
                    bool can_continue=FALSE;
                    can_break=atoi(Var_getValueOfVar(struct_settings, "can_break"));
                    can_continue=atoi(Var_getValueOfVar(struct_settings, "can_continue"));
                    if (can_break) {
                        Var_changeValueOfVar(struct_settings, "can_break", "0", "int");
                        break;
                    }
                    if (can_continue) {
                        Var_changeValueOfVar(struct_settings, "can_continue", "0", "int");
                        continue;
                    }
                    
                }
                
                //Afte run while, remove the element at __temp_while__
                char final_index[100];
                sprintf(final_index,"%d",length_of_list-1);
                char *remove_at_index=malloc(sizeof(char)*((int)strlen("[]")+(int)strlen(final_index)));
                strcat(remove_at_index,"[");
                strcat(remove_at_index,final_index);
                strcat(remove_at_index,"]");
                //// printf("remove at index is %s\n",remove_at_index);
                __temp_while__=listRemoveOneElementAtOneIndex(__temp_while__,remove_at_index);
                //// printf("__temp_while__ %s\n\n",__temp_while__);
                //changeTheWholeVarValueFromItsInitialOneFromFileForList(struct_var,"__temp_while__",__temp_while__);
                changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, "__temp_while__", __temp_while__);
                
                __temp_string_in_while_loop__=listRemoveOneElementAtOneIndex(__temp_string_in_while_loop__,remove_at_index);
                //// printf("__temp_string_in_while_loop %s\n\n",__temp_string_in_while_loop__);
                //changeTheWholeVarValueFromItsInitialOneFromFileForList(struct_var,"__temp_string_in_while_loop__",__temp_string_in_while_loop__);
                changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, "__temp_string_in_while_loop__", __temp_string_in_while_loop__);
            }
        }//############### Now Writting Function In Progress #####################
        else if (now_writting_function == TRUE && str_is_empty==FALSE) {
            can_run_basic_input = FALSE;
            // printf("//############### Now Writting Function In Progress #####################\n");
            ////printf("--->%s\n",input_str);
            //// printf("Current Space is %d, Required Space is %d\n",current_space,space);
            if (current_space % 4 != 0) {
                printf("Space Mistake\nCurrent Space is %d\nRequired Space is %d\n", current_space, space);
                exit(0);
            } else if (current_space <= space_of_first_def_sentence) {
                // printf("Finish_define_FUNCTION\n");
                can_run_basic_input = TRUE;
                now_writting_function = FALSE;
                char temp2[100];
                space=current_space;
                sprintf(temp2, "%d", space);
                Var_changeValueOfVar(struct_settings , "space", append("",temp2), "int");
                sprintf(temp2, "%d", now_writting_function);
                Var_changeValueOfVar(struct_settings , "now_writting_function", append("",temp2), "int");
                
                //// printf("--------Finish defining function--------\n");
                Str_addString(FUNCTION, "#~End\n\n");
            } else {
                
                space = current_space;
                input_str = removeAheadSpaceForNum(input_str, space_of_first_def_sentence + 4);
                Str_addString(FUNCTION, input_str);
                Str_addString(FUNCTION, "\n");
            }
            
            if (find_from_index_to_index(removeAheadSpace(input_str), "def ", 0, (int)strlen(removeAheadSpace(input_str))) != -1) {
                //printf("Find another function while defining a function\n");
                space = space + 4;
                //printf("Now required space is %d\n",space);
            }
            //}
            ////printf("NEXT\n");
            
        }        //################### Now Writting Class ##############################
        else if (now_writting_class == TRUE && str_is_empty==FALSE) {
            can_run_basic_input = FALSE;
            // printf("#### Now_Writting_Class In Progress ####\n");
            
            if(current_space % 4 !=0){
                printf("Space Mistake occurred while defining a class\n");
            }
            else if (current_space<=space_of_first_class_sentence){
                //printf("%s\n",input_str);
                //printf("Finish defining class.\n");
                now_writting_class=FALSE;
                can_run_basic_input = TRUE;
                space=current_space;
                sprintf(temp2, "%d", space);
                Var_changeValueOfVar(struct_settings , "space", append("",temp2), "int");
                sprintf(temp2, "%d", now_writting_class);
                Var_changeValueOfVar(struct_settings , "now_writting_class", append("",temp2), "int");
            }
            else{
                //// printf("Now Writting Class To File\n");
                space=current_space;
                input_str = removeAheadSpaceForNum(input_str, space_of_first_def_sentence + 4);
                //printf("---->|%s|\n",input_str);
                
                char *__string_in_temp_class__=Var_getValueOfVar(struct_var,"__string_in_temp_class__");
                char *__class_now__=Var_getValueOfVar(struct_var,"__temp_class_name_now_writting__");
                //printf("class now ----->%s\n",__class_now__);
                //printf("88888888 %s\n",__string_in_temp_class__);
                char *string_in_class=valueAtKey(__string_in_temp_class__,__class_now__);
                //printf("88888888 %s\n",__string_in_temp_class__);
                //printf("00000000 %s\n",string_in_class);
                char *temp_in_class = malloc(sizeof (char) *((int) strlen(input_str)+(int) strlen(string_in_class) + 2));
                strcat(temp_in_class, substr(string_in_class, 0, (int) strlen(string_in_class) - 1));
                strcat(temp_in_class, input_str);
                strcat(temp_in_class, "\\n\"");
                string_in_class = temp_in_class;
                //printf("11111111 %s\n",string_in_class);
                
                char *dict_var_name=malloc(sizeof(char)*((int)strlen("__string_in_temp_class__{}")+(int)strlen(__class_now__)));
                strcat(dict_var_name,"__string_in_temp_class__{");
                strcat(dict_var_name,__class_now__);
                strcat(dict_var_name,"}");
                //changeTheOneVarValueFromItsInitialOneFromFileOrAddVarNameAndValueForDictionary(struct_var,dict_var_name,string_in_class);
                changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var, dict_var_name, string_in_class);
            }
            
        }        //################## Now Run If #######################################
        else if (now_run_if == TRUE && str_is_empty==FALSE) {
            // printf("Now Run If\n");
            if (current_space > space || current_space % 4 != 0) {
                //if (current_space != space) {
                printf("Space Mistake\nCurrent Space is %d\nRequired Space is %d\n", current_space, space);
                exit(0);
            }
            // I do not know whether it is right or not.......
            if (current_space <= space) {
                input_str = removeAheadSpace(input_str);
                // change space and rewrite it to file
                space=current_space;
                char temp2[100];
                sprintf(temp2, "%d", space);
                Var_changeValueOfVar(struct_settings , "space", append("",temp2), "int");
            }
            
        }        //################## Now Run For #######################################
        else if (now_writting_for == TRUE && str_is_empty==FALSE) {
            // printf("#### Now Writting For ####");
            if (current_space > space_of_first_for_sentence && current_space % 4 == 0) {
                //// printf("################ Now Writting For ###################");
                //printf("STRING IN FOR LOOP is |%s|\n", string_in_for_loop);
                can_run_basic_input = FALSE;
                input_str = removeAheadSpaceForNum(input_str, space_of_first_for_sentence + 4);
                //printf("Input str is |%s|\n", input_str);
                //char *temp_in_loop = malloc(sizeof (char) *((int) strlen(input_str)+(int) strlen(string_in_for_loop) + 2));
                //strcat(temp_in_loop, substr(string_in_for_loop, 0, (int) strlen(string_in_for_loop) - 1));
                //strcat(temp_in_loop, input_str);
                //strcat(temp_in_loop, "\\n\"");
                
                char *temp_in_loop=append(substr(string_in_for_loop, 0, (int) strlen(string_in_for_loop) - 1), input_str);
                temp_in_loop=append(temp_in_loop, "\\n\"");
                
                string_in_for_loop = temp_in_loop;
                //printf("STRING IN FOR LOOP is |%s|\n", string_in_for_loop);
                Var_changeValueOfVar(struct_settings , "string_in_for_loop", string_in_for_loop, "string");
                
            } else if (current_space <= space_of_first_for_sentence && current_space % 4 == 0) {
                //printf("\nBegin to Run For input_str %s, current_space %d, space_of_first %d\n",input_str,current_space,space_of_first_for_sentence);
                can_run_basic_input = TRUE;
                now_writting_for = FALSE;
                //printf("----String in loop is %s\n",string_in_for_loop);
                char temp3[100];
                sprintf(temp3, "%d", now_writting_for);
                Var_changeValueOfVar(struct_settings , "now_writting_for", append("",temp3), "int");
                space=current_space;
                sprintf(temp3, "%d", space);
                Var_changeValueOfVar(struct_settings , "space", append("",temp3), "int");
                
                if (strcmp(variableValueType(temp_i_in_for_sentence), "list") == 0) {
                    //printf("i is list type\ni value is |%s|\n", temp_i_in_for_sentence);
                    //printf("temp i is |%s|\n", temp_i);
                    int value_num = valueNumOfList(temp_i_in_for_sentence);
                    
                    //get __temp_for__ to get last_while_sentence
                    char *__temp_for__=Var_getValueOfVar(struct_var,"__temp_for__");
                    int length_of_list=valueNumOfList(__temp_for__);
                    char final_index0[100];
                    sprintf(final_index0,"%d",length_of_list-1);
                    char *temp_index=malloc(sizeof(char)*((int)strlen("[]")+(int)strlen(final_index0)));
                    strcat(temp_index,"[");
                    strcat(temp_index,final_index0);
                    strcat(temp_index,"]");
                    //char *temp_i_in_for_sentence2=valueOfListAtIndex(__temp_for__,length_of_list-1);
                    char *temp_i_in_for_sentence2=valueOfListAtIndexString(__temp_for__,temp_index);
                    
                    //printf("temp_i_in_for_sentence is %s\n",temp_i_in_for_sentence2);
                    
                    //get __temp_i__
                    char *__temp_i__=Var_getValueOfVar(struct_var,"__temp_i__");
                    char *temp_i2=valueOfListAtIndexString(__temp_i__,temp_index);
                    //printf("temp_i is %s\n",temp_i2);
                    
                    //get __temp_string_in_for_loop__
                    //printf("string in for loop %s\n",string_in_for_loop);
                    char *__temp_string_in_for_loop__=Var_getValueOfVar(struct_var,"__temp_string_in_for_loop__");
                    __temp_string_in_for_loop__=listAppendOneElement(__temp_string_in_for_loop__,string_in_for_loop);
                    //changeTheWholeVarValueFromItsInitialOneFromFileForList(struct_var,"__temp_string_in_for_loop__",__temp_string_in_for_loop__);
                    changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, "__temp_string_in_for_loop__", __temp_string_in_for_loop__);
                    
                    //printf("----String in loop is %s\n",string_in_for_loop);
                    //printf("__temp_string_in_for_loop__ is %s\n",__temp_string_in_for_loop__);
                    string_in_for_loop="\"#For\\n\"";
                    Var_changeValueOfVar(struct_settings , "string_in_for_loop", string_in_for_loop, "string");
                    //char *string_in_for_loop2=valueOfListAtIndex(__temp_string_in_for_loop__,length_of_list-1);
                    //// printf("__temp_string_in_for_loop__ %s\n",__temp_string_in_for_loop__);
                    char *string_in_for_loop2=valueOfListAtIndexString(__temp_string_in_for_loop__,temp_index);
                    //// printf("string_in_for_loop2 is %s\n",string_in_for_loop2);
                    //printf("String in for loop is %s\n",string_in_for_loop2);
                    
                    int x = 0;
                    /*
                     for (x = 0; x < value_num; x++) {
                     printf("X--->%d\n", x);
                     char temp_num[100];
                     sprintf(temp_num, "%d", x);
                     
                     char *index_temp = malloc(sizeof (char) *(2 + (int) strlen(temp_num)));
                     strcat(index_temp, "[");
                     strcat(index_temp, temp_num);
                     strcat(index_temp, "]");
                     
                     char *value_of_i_in_x = valueOfListAtIndexString(temp_i_in_for_sentence, index_temp);
                     //printf("value_of_i_in_x is |%s|\n",value_of_i_in_x);
                     //printf("Now Run %d Time\n",x);
                     printf("Get Here\n");
                     char *init_temp_i = malloc(sizeof (char) *((int) strlen(temp_i) + 1 + (int) strlen(value_of_i_in_x)));
                     strcat(init_temp_i, temp_i);
                     strcat(init_temp_i, "=");
                     strcat(init_temp_i, value_of_i_in_x);
                     //printf("init_temp_i is |%s|\n",init_temp_i);
                     printf("Get Here\n");
                     printf("STRING IN FOR LOOP %s\n", string_in_for_loop);
                     char *temp_to_run = substr(string_in_for_loop, 1, (int) strlen(string_in_for_loop) - 1);
                     printf("TEMP TO RUN %s\n", temp_to_run);
                     printf("Get Here\n");
                     
                     Walley_Run_For_Appointed_Var(struct_var, setting_file, temp_file, existing_file, init_temp_i);
                     Walley_Run_For_Appointed_Var(struct_var, setting_file, temp_file, existing_file, temp_to_run);
                     
                     }
                     string_in_for_loop = "\"#For\\n\"";
                     temp_i = "\"None\"";
                     temp_i_in_for_sentence = "\"None\"";
                     }
                     **/
                    //// printf("value num is %d\n",value_num);
                    for (x = 0; x < value_num; x++) {
                        //printf("X--->%d\n", x);
                        char temp_num[100];
                        sprintf(temp_num, "%d", x);
                        
                        char *index_temp = malloc(sizeof (char) *(2 + (int) strlen(temp_num)));
                        strcat(index_temp, "[");
                        strcat(index_temp, temp_num);
                        strcat(index_temp, "]");
                        
                        char *value_of_i_in_x = valueOfListAtIndexString(temp_i_in_for_sentence2, index_temp);
                        //// printf("value_of_i_in_x is |%s|\n",value_of_i_in_x);
                        //printf("Now Run %d Time\n",x);
                        //printf("Get Here\n");
                        
                        char *init_temp_i = malloc(sizeof (char) *((int) strlen(temp_i2) + 2 + (int) strlen(value_of_i_in_x)));
                        strcat(init_temp_i, temp_i2);
                        strcat(init_temp_i, "=");
                        strcat(init_temp_i, value_of_i_in_x);
                        init_temp_i[(int)strlen(init_temp_i)]=0;
                        //// printf("init_temp_i is %s\n",init_temp_i);
                        //// printf("init_temp_i is |%s|\n",init_temp_i);
                        //printf("Get Here\n");
                        //printf("STRING IN FOR LOOP %s\n", string_in_for_loop2);
                        char *temp_to_run = substr(string_in_for_loop2, 1, (int) strlen(string_in_for_loop2) - 1);
                        //printf("TEMP TO RUN %s\n", temp_to_run);
                        //printf("Get Here\n");
                        //if (strcmp(trim(temp_to_run), "pass") == 0) {
                        //    break;
                        //}
                        //if (strcmp(trim(temp_to_run), "continue") == 0) {
                        //    continue;
                        //}
                        //printf("%s\n",init_temp_i);
                        //Walley_Run_For_Appointed_Var(struct_var, struct_settings, temp_file, existing_file, init_temp_i);
                        //Walley_Run_For_Appointed_Var(struct_var, struct_settings, temp_file, existing_file, temp_to_run);
                        
                        Walley_Agent_Respond(walley_language_file, walley_language_similarity_file, walley_language_verb_file, struct_var, struct_settings, temp_file, existing_file, init_temp_i);
                        Walley_Agent_Respond(walley_language_file, walley_language_similarity_file, walley_language_verb_file, struct_var, struct_settings, temp_file, existing_file, temp_to_run);
                        
                        
                        bool can_break=FALSE;
                        bool can_continue=FALSE;
                        can_break=atoi(Var_getValueOfVar(struct_settings, "can_break"));
                        can_continue=atoi(Var_getValueOfVar(struct_settings, "can_continue"));
                        if (can_break) {
                            Var_changeValueOfVar(struct_settings, "can_break", "0", "int");
                            break;
                        }
                        if (can_continue) {
                            Var_changeValueOfVar(struct_settings, "can_continue", "0", "int");
                            continue;
                        }
                        
                    }
                    string_in_for_loop = "\"#For\\n\"";
                    temp_i = "\"None\"";
                    temp_i_in_for_sentence = "\"None\"";
                    
                    //Afte run while, remove the element at __temp_for__
                    char final_index[100];
                    sprintf(final_index,"%d",length_of_list-1);
                    char *remove_at_index=malloc(sizeof(char)*((int)strlen("[]")+(int)strlen(final_index)));
                    strcat(remove_at_index,"[");
                    strcat(remove_at_index,final_index);
                    strcat(remove_at_index,"]");
                    //printf("remove at index is %s\n",remove_at_index);
                    __temp_for__=listRemoveOneElementAtOneIndex(__temp_for__,remove_at_index);
                    //changeTheWholeVarValueFromItsInitialOneFromFileForList(struct_var,"__temp_for__",__temp_for__);
                    changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, "__temp_for__", __temp_for__);
                    __temp_string_in_for_loop__=listRemoveOneElementAtOneIndex(__temp_string_in_for_loop__,remove_at_index);
                    //changeTheWholeVarValueFromItsInitialOneFromFileForList(struct_var,"__temp_string_in_for_loop__",__temp_string_in_for_loop__);
                    changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, "__temp_string_in_for_loop__", __temp_string_in_for_loop__);
                    __temp_i__=listRemoveOneElementAtOneIndex(__temp_i__,remove_at_index);
                    //changeTheWholeVarValueFromItsInitialOneFromFileForList(struct_var,"__temp_i__",__temp_i__);
                    changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, "__temp_i__", __temp_i__);
                    
                }
                else {
                    printf("#### For Sentence Only Support list Type At This Time\n");
                }
                
            }
        }
        char temp5[10];
        sprintf(temp5, "%d", can_run_basic_input);
        Var_changeValueOfVar(struct_settings , "can_run_basic_input", append("",temp5), "int");
        //##########################################################################################################
        //##########################################################################################################
        //##########################################################################################################
        //##########################################################################################################
        //// printf("can run basic input %d numOfSpaceAheadString %d required space %d\n",can_run_basic_input,numOfSpaceAheadString(input_str),space);
        if (can_run_basic_input == TRUE && (numOfSpaceAheadString(input_str) == 0 || space==current_space)) {
            /*
             //#####################  Anotation  ###################
             if (removeAheadSpace(input_str)[0] == '#') {
             printf("This is one anatation %s\n", removeAheadSpace(input_str));
             }
             // ##############  Function  ##############################
             else if (find(removeAheadSpace(input_str), "def ") == 0) {
             printf("\n###### begin to define a function######\n");
             space_of_first_def_sentence=space;
             space = space + 4;
             //printf("Now Space is %d\n",space);
             now_writting_function = TRUE;
             //char *output=defineAFunction(input_str);
             //printf("100---------------\n%s---------------\n",getStringFromFile("__walley_settings__.wy"));
             char *func_name = functionName(input_str);
             char *func_param_str = functionParameterStr(input_str);
             bool has_same_function_name = checkWhetherSameFunctionNameExists(func_name);
             if (has_same_function_name) {
             //printf("Has Same Function Name\n");
             changeFunctionFromItsInitialOne(func_name, func_param_str);
             
             } else {
             //printf("Does Not Have Same Function Name\n");
             writeFunctionIntoFile(func_name, func_param_str);
             Str_addString(FUNCTION, "#~Begin\n");
             //Str_addString(FUNCTION,"Begin\n");
             
             if (strcmp(func_param_str, "None") == 0) {
             printf("This Function has no Parameter\n");
             } else {
             writeFunctionParameterOneByOneToFile(func_param_str);
             Str_addString(FUNCTION, "#~Finish Init Params\n");
             //Str_addString(FUNCTION,"#Finish initialize parameters\n");
             }
             }
             }            //################## Judge Whether this whether an if sentence ##########################
             else if (find(removeAheadSpace(input_str), "if ") == 0 || find(removeAheadSpace(input_str), "elif ") == 0 || find(removeAheadSpace(input_str), "else") == 0) {
             printf("now judge if sentence\n");
             char *sentence="";
             char *temp_for_sentence = removeAheadSpace(removeBackSpace(input_str));
             bool can_run;
             if (find(removeAheadSpace(input_str), "if ") == 0) {
             printf("Find If\n");
             sentence = substr(temp_for_sentence, find(temp_for_sentence, "if ") + 3, (int) strlen(temp_for_sentence) - 1);
             last_if_sentence = sentence;
             can_run = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function_Second_Generation(sentence, file_name);
             } else if (find(removeAheadSpace(input_str), "elif ") == 0) {
             printf("Find elif\n");
             sentence = substr(temp_for_sentence, find(temp_for_sentence, "elif ") + 5, (int) strlen(temp_for_sentence) - 1);
             int length_of_temp = (int) strlen("not ( ") + 1 + (int) strlen(" ) and (  )")+(int) strlen(last_if_sentence)+(int) strlen(sentence);
             char *temp_for_sentence2 = malloc(sizeof (char) *length_of_temp);
             strcat(temp_for_sentence2, "not ( ");
             strcat(temp_for_sentence2, last_if_sentence);
             strcat(temp_for_sentence2, " ) and ( ");
             strcat(temp_for_sentence2, sentence);
             strcat(temp_for_sentence2, " )");
             temp_for_sentence2[length_of_temp - 1] = 0;
             
             sentence = temp_for_sentence2;
             last_if_sentence = sentence;
             can_run = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function_Second_Generation(sentence, file_name);
             } else if (find(removeAheadSpace(input_str), "else") == 0) {
             printf("Find else\n");
             can_run = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function_Second_Generation(last_if_sentence, file_name);
             if (can_run == 1)
             can_run = 0;
             else
             can_run = 1;
             last_if_sentence = "None";
             }
             printf("Sentence is |%s|\nLength is %d\n", sentence, (int) strlen(sentence));
             //bool can_run = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(sentence, file_name);
             if (can_run) {
             now_run_if = TRUE;
             printf("Can Run\n");
             space = space + 4;
             //last_if_sentence=sentence;
             } else {
             now_run_if = FALSE;
             printf("Can not run\n");
             }
             }            //#################### While Sentence ##################################
             else if (find(removeAheadSpace(input_str), "while ") == 0) {
             //now_writting_while=TRUE;
             last_while_sentence = removeAheadSpace(input_str);
             last_while_sentence = substr(last_while_sentence, 6, find(last_while_sentence, ":"));
             last_while_sentence = removeBackSpace(last_while_sentence);
             
             bool can_run_while = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function_Second_Generation(last_while_sentence, file_name);
             if (can_run_while == FALSE) {
             printf("Can Not Run While");
             now_writting_while = FALSE;
             last_while_sentence = "None";
             } else {
             printf("Can Run While\n");
             now_writting_while = TRUE;
             space_of_first_while_sentence = space;
             space = space + 4;
             }
             }
             //#################### For Sentence #####################################
             else if (find(removeAheadSpace(input_str), "for") == 0 && removeBackSpace(input_str)[(int) strlen(removeBackSpace(input_str)) - 1] == ':') {
             printf("#### Find For ####\n");
             temp_i = substr(input_str, find(input_str, "for ") + 4, find(input_str, " in"));
             temp_i = removeAheadSpace(removeBackSpace(temp_i));
             char *in_what = substr(input_str, find(input_str, " in ") + 4, (int) strlen(removeBackSpace(input_str)) - 1);
             in_what = removeAheadSpace(removeBackSpace(in_what));
             in_what = Walley_Substitute_Var_And_Function_Return_Value_From_File_Second_Generation(in_what, file_name);
             printf("i is |%s|, in_what is |%s|\n", temp_i, in_what);
             now_writting_for = TRUE;
             //temp_i_in_for_sentence=Var_getValueOfVar(struct_var,in_what);
             temp_i_in_for_sentence = in_what;
             if (strcmp(variableValueType(temp_i_in_for_sentence), "string") == 0) {
             temp_i_in_for_sentence = changeStringToList(temp_i_in_for_sentence);
             }
             printf("i is |%s|\n", temp_i_in_for_sentence);
             
             space_of_first_for_sentence = space;
             space = space + 4;
             }
             
             **/
            char *input_temp = removeAheadSpace(input_str);
            if (strcmp(trim(input_str), "pass")==0) {
                Var_changeValueOfVar(struct_settings, "can_break", "1", "int");
            }
            else if (strcmp(trim(input_str), "continue")==0) {
                Var_changeValueOfVar(struct_settings, "can_continue", "1", "int");
            }
            else if (input_temp[0] == '#' ||
                     find(input_temp, "for ") == 0 ||
                     find(input_temp, "while ") == 0 ||
                     find(input_temp, "if ") == 0 || find(input_temp, "elif ") == 0 || find(input_temp, "else") == 0 ||
                     find(input_temp, "def ") == 0 ||
                     find(input_temp,"class ")==0) {
                Walley_Judge_Run_Anotation_For_While_Def_Class(struct_var, struct_settings, input_str);
                
            }// ##################################### CHECK RETURN IN FUNCTION, CHECK WHETHER IT CAN RUN OR NOT
            else if (strcmp(substr(trim(input_str),0, 6),"return")==0){
                printf("");
            }
            //#################### Basic Input To Run #############################
            else {
                //// printf("\n\n######### Basic Input To Run #########\n");
                input_str = trim(input_str);
                //#####################  Init class  #####################
                //if (find_not_in_string(input_str, " is ") != -1||
                if((find_not_in_string(input_str, "=")!=-1&&find_not_in_string(input_str,"(")!=-1&&checkWhetherSameClassExistedFromVar(struct_var,trim(substr(input_str,find_not_in_string(input_str, "=")+1,find_not_in_string(input_str,"("))))==TRUE)
                   ) {
                    // printf("#### Begin to initialize class ####\n");
                    // ## a is hello()
                    // ## a is instance_name
                    // ## hello() is __class__
                    // ## in hello("Hello"), "Hello" is parameter.
                    char *instance_name = substr(input_str, 0, find_not_in_string(input_str, "="));
                    char *__class__ = substr(input_str, find_not_in_string(input_str, "=") + 1, (int) strlen(input_str));
                    instance_name = trim(instance_name);
                    __class__ = trim(__class__);
                    //char *class_name=substr(__class__,0,find(__class__,"("));
                    char *parameter=substr(__class__,find(__class__,"(")+1,find_not_in_string(__class__,")"));
                    
                    /*
                     char *__string_in_temp_class__ = Var_getValueOfVar(struct_var, "__string_in_temp_class__");
                     char *__class_now__ = toString(class_name);
                     char *string_in_class = valueAtKey(__string_in_temp_class__, __class_now__);
                     printf("string in class \n|%s|\n",string_in_class);
                     **/
                    //char *after_change=formatStringInClass(instance_name,string_in_class);
                    
                    char *after_change=formatStringInClassWithExtendFromVar(struct_var,input_str);
                    //printf("#### AFTER CHANGE\n|%s|\n####\n",after_change);
                    
                    //Walley_Run_For_Appointed_Var(struct_var, struct_settings, temp_file, existing_file, after_change);
                    Walley_Agent_Respond(walley_language_file, walley_language_similarity_file, walley_language_verb_file, struct_var, struct_settings, temp_file, existing_file, after_change);

                    
                    //addInstanceNameToFile(instance_name,file_name);
                    addInstanceNameToVar(instance_name,struct_var);
                    
                    
                    
                    
                    // run init() function
                    // a.init()
                    char *init=malloc(sizeof(char)*((int)strlen(instance_name)+1+(int)strlen(".init()")+(int)strlen(parameter)));
                    strcat(init,instance_name);
                    strcat(init,".init(");
                    strcat(init,parameter);
                    strcat(init,")");
                    init[(int)strlen(init)]=0;
                    //  printf("BEGIN TO INITIALIZE %s\n",init);
                    //Walley_Run_For_Appointed_Var(struct_var, struct_settings, temp_file, existing_file, init);
                    Walley_Agent_Respond(walley_language_file, walley_language_similarity_file, walley_language_verb_file, struct_var, struct_settings, temp_file, existing_file, init);

                    
                }
                
                //#####################  println  ###################
                else if (find_not_in_string(input_str, "println(") == 0) {
                    char* output = Walley_Println(struct_var, strInBrackets(input_str));
                    printf("%s", output);
                }//#####################  print  ###################
                else if (find_not_in_string(input_str, "print(") == 0) {
                    char* output = Walley_Print(struct_var, strInBrackets(input_str));
                    ////printf("PRINT %s\n",output);
                    printf("%s", output);
                    ////puts(output);
                }                //#################### import ####################
                else if (find(removeAheadSpace(input_str), "import ") == 0) {
                    // Now only support import a   does not support import a,b,c ... at same row
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
                    
                    char *temp_file_to_run = malloc(sizeof (char) *((int) strlen(name_of_file_to_run) + 3));
                    strcat(temp_file_to_run, name_of_file_to_run);
                    strcat(temp_file_to_run, ".wy");
                    
                    //char *content_of_file = getStringFromFile(temp_file_to_run);
                    char *content_of_file = functionOrClassAddAheadName(temp_file_to_run,as_name);
                    
                    //printf("content of file is |%s|\n", content_of_file);
                    //Walley_Run_For_Appointed_Var(struct_var, struct_settings, temp_file, existing_file, content_of_file);
                    //Walley_Run_For_Appointed_Var(struct_var, struct_settings, temp_file, existing_file, "#End Importing");
                    
                    Walley_Agent_Respond(walley_language_file, walley_language_similarity_file, walley_language_verb_file, struct_var, struct_settings, temp_file, existing_file, content_of_file);
                    Walley_Agent_Respond(walley_language_file, walley_language_similarity_file, walley_language_verb_file, struct_var, struct_settings, temp_file, existing_file, "#End Importing");

                }
                //This is also import
                else if (find(removeAheadSpace(input_str),"from ")==0){
                    //printf("\nNow input_str is |%s|\n",input_str);
                    
                    input_str=trim(input_str);
                    if(find_not_in_string(input_str," import ")==-1){
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
                        //as_name=import_module;
                    }
                    import_file=trim(import_file);
                    import_module=trim(import_module);
                    as_name=trim(as_name);
                    
                    //char *temp_file_to_run = malloc(sizeof (char) *((int) strlen(import_file) + 3));
                    //strcat(temp_file_to_run, import_file);
                    
                    
                    int length_of_import_file=(int)strlen(import_file);
                    
                    char *temp_file_to_run;
                    char *type=substr(import_file, length_of_import_file-3,length_of_import_file);
                    //printf("type is %s\n",type);
                    if (strcmp(substr(import_file, length_of_import_file-3,length_of_import_file),".wy")!=0 &&
                        strcmp(substr(import_file, length_of_import_file-3,length_of_import_file),".wi")!=0) {
                        temp_file_to_run=append(import_file, ".wi");
                    }
                    else{
                        temp_file_to_run=append("", import_file);
                    }
                    
                    //strcat(temp_file_to_run, ".wi");
                    char *content_of_file="";
                    
                    // import all functions or classes from module
                    if(strcmp(import_module,"all")==0||strcmp(import_module,"*")==0){
                        if(strcmp(import_module,as_name)==0)
                            as_name="";
                        content_of_file = functionOrClassAddAheadName(temp_file_to_run,as_name);
                    }
                    else{
                        content_of_file = getOneFunctionFromFileAndFormatItgetOneFunctionFromFile(temp_file_to_run,import_module,as_name);
                    }
                    
                    
                    //char *content_of_file = getStringFromFile(temp_file_to_run);
                    //printf("content of file is |%s|\n", content_of_file);
                    //Walley_Run_For_Appointed_Var(struct_var, struct_settings, temp_file, existing_file, content_of_file);
                    //Walley_Run_For_Appointed_Var(struct_var, struct_settings, temp_file, existing_file, "#End Importing");
                    
                    Walley_Agent_Respond(walley_language_file, walley_language_similarity_file, walley_language_verb_file, struct_var, struct_settings, temp_file, existing_file, content_of_file);
                    Walley_Agent_Respond(walley_language_file, walley_language_similarity_file, walley_language_verb_file, struct_var, struct_settings, temp_file, existing_file, "#End Importing");

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
                 string_to_run = getStringFromFile(temp_file);
                 } else {
                 string_to_run = getStringFromFile(existing_file);
                 }
                 //// printf("String in File is |%s|\n", getStringFromFile(temp_file));
                 char *setmark = malloc(sizeof (char) *((int) strlen("setmark ")+(int) strlen(mark_name)));
                 strcat(setmark, "setmark ");
                 strcat(setmark, mark_name);
                 if (find(string_to_run, setmark) == -1) {
                 printf("Mistake Occurred while calling function Walley_To_Mark\nMark not found");
                 exit(1);
                 } else {
                 string_to_run = substr(string_to_run, find(string_to_run, "setmark "), (int) strlen(string_to_run));
                 FILE *fp = fopen(temp_file, "w");
                 fputs("", fp);
                 fclose(fp);
                 //// printf("$$$ \n|%s|\n", string_to_run);
                 //clearTextInFile(temp_file);
                 writeStringToFile(temp_file, string_to_run);
                 writeStringToFile(temp_file, "\n");
                 run_goto = TRUE;
                 //Walley_Run_Second_Generation(struct_var,setting_file,temp_file,string_to_run);
                 }
                 }*/
                //#####################  Eval  ###################
                else if (isExpression(input_str) == TRUE) {
                    Walley_Eval_And_Update_Var_And_Value_To_Var(struct_var, input_str);
                }                // ##############  Is Not Expression ######################
                
                //#####################  Delete Space  ###################
                //} else if(strcmp("",removeBackSpace(removeAheadSpace(input_str)))==0){
                //    printf("Empty Input");
                //space=space-4;
                
                //#####################  Mistake  ###################
                else {
                    // printf("Enter Here\n");
                    
                    /*
                     char *temp2 = Walley_Substitute_Var_And_Function_Return_Value_From_File(input_str, file_name);
                     //printf("temp2 is %s\n",temp2);
                     //printf("enter here\n");
                     if (strcmp(input_str, "None") != 0) {
                     Walley_Eval_With_Variable_From_File(struct_var, temp2);
                     printf("Mistake May occurred which calling function Walley_Run_Second_Generation;\nThis Language is under development");
                     }
                     **/
                    //printf("ENTER HERE\n");
                    bool can_just_eval = TRUE;
                    int index_of_dot = find_not_in_string(input_str, ".");
                    if (index_of_dot > 0) {
                        char temp_char = input_str[index_of_dot - 1];
                        if (isalpha(temp_char)||temp_char=='_')
                            can_just_eval = FALSE;
                    }
                    if (isFunctionFromVar(input_str) == TRUE) {
                        //// printf("Yes it is function\n");
                        can_just_eval = FALSE;
                    }
                    if (can_just_eval) {
                        int length_of_input_str=(int)strlen(input_str);
                        if(input_str[length_of_input_str-1]=='+'&&input_str[length_of_input_str-2]=='+') {
                            //printf("++\n");
                            char *temp_var_name=substr(input_str, 0, length_of_input_str-2);
                            temp_var_name=trim(temp_var_name);
                            //printf("temp_var_name %s\n",temp_var_name);
                            temp_var_name=append(temp_var_name, "=");
                            char *temp_to_run=append(temp_var_name, input_str);
                            Walley_Eval_And_Update_Var_And_Value_To_Var(struct_var,temp_to_run);
                        }
                        else if (input_str[length_of_input_str-1]=='-'&&input_str[length_of_input_str-2]=='-') {
                            //printf("++\n");
                            char *temp_var_name=substr(input_str, 0, length_of_input_str-2);
                            temp_var_name=trim(temp_var_name);
                            //printf("temp_var_name %s\n",temp_var_name);
                            temp_var_name=append(temp_var_name, "=");
                            char *temp_to_run=append(temp_var_name, input_str);
                            Walley_Eval_And_Update_Var_And_Value_To_Var(struct_var,temp_to_run);
                        }
                        else{
                            char *temp2 = malloc(sizeof (char) *((int) strlen(input_str)+(int) strlen("__temp__=")));
                            strcat(temp2, "__temp__=");
                            strcat(temp2, input_str);
                            //printf("TEMP2 is %s\n", temp2);
                            Walley_Eval_And_Update_Var_And_Value_To_Var(struct_var, temp2);
                            //// printf("Remove\n\n");
                            //Walley_Remove_Variable_And_Value_From_File(struct_var, "__temp__");
                            Var_removeVar(struct_var, "__temp__");
                            

                        }
                        
                    } else {
                        //printf("Enter Else\n");
                        input_str = Walley_Substitute_Var_And_Function_Return_Value_From_Var(input_str, struct_var);
                        // printf("EHE %s\n",input_str);
                        Walley_Eval_With_Variable_From_Var(struct_var, input_str);
                    }
                    // printf("End\n");
                    
                }
                //printf("\nRequired space num is %d\n",space);
                //// printf("#### Set Settings ####\n\n\n");
                char temp2[100];
                sprintf(temp2, "%d", space);
                Var_changeValueOfVar(struct_settings , "space", append("",temp2), "int");
                sprintf(temp2, "%d", now_writting_function);
                Var_changeValueOfVar(struct_settings , "now_writting_function", append("",temp2), "int");
                sprintf(temp2, "%d", now_writting_class);
                Var_changeValueOfVar(struct_settings , "now_writting_class", append("",temp2), "int");
                sprintf(temp2, "%d", now_writting_while);
                Var_changeValueOfVar(struct_settings , "now_writting_while", append("",temp2), "int");
                sprintf(temp2, "%d", now_writting_for);
                Var_changeValueOfVar(struct_settings , "now_writting_for", append("",temp2), "int");
                sprintf(temp2, "%d", now_run_if);
                Var_changeValueOfVar(struct_settings , "now_run_if", append("",temp2), "int");
                sprintf(temp2, "%d", space_of_first_while_sentence);
                Var_changeValueOfVar(struct_settings , "space_of_first_while_sentence", append("",temp2), "int");
                sprintf(temp2, "%d", space_of_first_for_sentence);
                Var_changeValueOfVar(struct_settings , "space_of_first_for_sentence", append("",temp2),"int");
                sprintf(temp2, "%d", space_of_first_def_sentence);
                Var_changeValueOfVar(struct_settings , "space_of_first_def_sentence", append("",temp2),"int");
                sprintf(temp2, "%d", space_of_first_class_sentence);
                Var_changeValueOfVar(struct_settings , "space_of_first_class_sentence", append("",temp2),"int");
                
                Var_changeValueOfVar(struct_settings , "last_if_sentence", last_if_sentence, "string");
                Var_changeValueOfVar(struct_settings , "last_while_sentence", last_while_sentence, "string");
                Var_changeValueOfVar(struct_settings , "string_in_while_loop", string_in_while_loop, "string");
                Var_changeValueOfVar(struct_settings , "string_in_for_loop", string_in_for_loop, "string");
                Var_changeValueOfVar(struct_settings , "temp_i", temp_i, "string");
                Var_changeValueOfVar(struct_settings , "temp_i_in_for_sentence", temp_i_in_for_sentence, "string");
            }
            
        }
        /**
         //#################### Set Settigns ################################
         printf("#### Set Settings ####\n\n\n");
         char temp2[100];
         sprintf(temp2, "%d", space);
         Var_changeValueOfVar(struct_settings , "space", append("",temp2), "int");
         sprintf(temp2, "%d", now_writting_function);
         Var_changeValueOfVar(struct_settings , "now_writting_function", append("",temp2), "int");
         sprintf(temp2, "%d", now_writting_class);
         Var_changeValueOfVar(struct_settings , "now_writting_class", append("",temp2), "int");
         sprintf(temp2, "%d", now_writting_while);
         Var_changeValueOfVar(struct_settings , "now_writting_while", append("",temp2), "int");
         sprintf(temp2, "%d", now_writting_for);
         Var_changeValueOfVar(struct_settings , "now_writting_for", append("",temp2), "int");
         sprintf(temp2, "%d", now_run_if);
         Var_changeValueOfVar(struct_settings , "now_run_if", append("",temp2), "int");
         sprintf(temp2, "%d", space_of_first_while_sentence);
         Var_changeValueOfVar(struct_settings , "space_of_first_while_sentence", append("",temp2), "int");
         sprintf(temp2, "%d", space_of_first_for_sentence);
         sprintf(temp2, "%d", space_of_first_def_sentence);
         Var_changeValueOfVar(struct_settings , "space_of_first_def_sentence", append("",temp2), "int");
         Var_changeValueOfVar(struct_settings , "space_of_first_for_sentence", append("",temp2), "int");
         Var_changeValueOfVar(struct_settings , "last_if_sentence", last_if_sentence, "string");
         Var_changeValueOfVar(struct_settings , "last_while_sentence", last_while_sentence, "string");
         Var_changeValueOfVar(struct_settings , "string_in_while_loop", string_in_while_loop, "string");
         Var_changeValueOfVar(struct_settings , "string_in_for_loop", string_in_for_loop, "string");
         Var_changeValueOfVar(struct_settings , "temp_i", temp_i, "string");
         Var_changeValueOfVar(struct_settings , "temp_i_in_for_sentence", temp_i_in_for_sentence, "string");*/
        //// printf("here\n");
        if (continue_run == TRUE && run_goto == FALSE) {
            //// printf("continue run\n");
            if (find_gang_gang == TRUE) {
                // int index_of_gang_gang_n=find(temp_input_str, "\\n");
                // printf("index of gang gang is %d\n",index_of_gang_gang_n);
                // printf("index of \\n %d",(int)strlen("\\n"));
                //Walley_Run_For_Appointed_Var(struct_var, struct_settings, temp_file, existing_file, substr(temp_input_str, find(temp_input_str, "\\n") + 2, (int) strlen(temp_input_str)));
                Walley_Agent_Respond(walley_language_file, walley_language_similarity_file, walley_language_verb_file, struct_var, struct_settings, temp_file, existing_file, substr(temp_input_str, find(temp_input_str, "\\n") + 2, (int) strlen(temp_input_str)));

                
            } else {
                //// printf("STRING LEFT is %s\n",substr(temp_input_str,find(temp_input_str,"\n")+1,(int)strlen(temp_input_str)));
               // Walley_Run_For_Appointed_Var(struct_var, struct_settings, temp_file, existing_file, substr(temp_input_str, find(temp_input_str, "\n") + 1, (int) strlen(temp_input_str)));
                Walley_Agent_Respond(walley_language_file, walley_language_similarity_file, walley_language_verb_file, struct_var, struct_settings, temp_file, existing_file, substr(temp_input_str, find(temp_input_str, "\n") + 1, (int) strlen(temp_input_str)));

            }
        }
        /* Disable setmark and goto.....
         if (run_goto == TRUE) {
         //// printf("@@@@ Run GOTO @@@@\n");
         Walley_Run_For_Appointed_Var(struct_var, struct_settings, temp_file, existing_file, getStringFromFile(temp_file));
         }*/
    }
}
