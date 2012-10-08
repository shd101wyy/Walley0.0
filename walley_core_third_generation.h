/* 
 * File:   walley_core_third_generation.h
 * Author: shd101wyy
 *
 * Created on September 12, 2012, 10:01 PM
 */

#include "walley_core_second_generation.h"

void Walley_Run_Third_Generation(char* file_name, char *setting_file, char *temp_file_name, char* existing_file, char* input_str) {
    printf("######### Run Function Walley_Run_Third_Generation ######\n");
    
        // check whether in #~ ~# at first

    bool now_in_annotation = atoi(getValueFromValueName(setting_file, "now_in_annotation"));
    char *judge_annotation_string=trim(input_str);
    int length_of_judge_annotation_string=(int)strlen(judge_annotation_string);
    if (judge_annotation_string[length_of_judge_annotation_string-1]=='#' && judge_annotation_string[length_of_judge_annotation_string-2]=='~'){
        printf("Now End Long Annotation");
        now_in_annotation = 0;
        char temp4[100];
        sprintf(temp4, "%d", now_in_annotation);
        changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_in_annotation", (char*) temp4, "int");
    }
    else if (judge_annotation_string[0] == '#' && judge_annotation_string[1] == '~') {
        printf("Now Begin Long Annotation");
        now_in_annotation = 1;
        char temp4[100];
        sprintf(temp4, "%d", now_in_annotation);
        changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_in_annotation", (char*) temp4, "int");
    }
    if(now_in_annotation==0){
    bool continue_run = FALSE;
    bool find_gang_gang = FALSE;
    bool str_is_empty=FALSE;
    
    char *temp_input_str=input_str;
    
    //char *temp_input_str = malloc(sizeof(char) *((int) strlen(input_str) + 1));
    //strcat(temp_input_str,input_str);
    //temp_input_str[(int) strlen(temp_input_str)] = 0;
    
    if (find(input_str, "\n") != -1) {
        continue_run = TRUE;
        input_str = substr(input_str, 0, find(input_str, "\n"));
        //Walley_Run_For_Appointed_File(file_name,setting_file,substr(temp_input_str,find(temp_input_str,"\n")+1,(int)strlen(temp_input_str)));
    }
    
    if (find(input_str, "\\n") != -1) {
        //printf("find \\n");
        continue_run = TRUE;
        find_gang_gang = TRUE;
        input_str = substr(input_str, 0, find(input_str, "\\n"));
        //Walley_Run_For_Appointed_File(file_name,setting_file,substr(temp_input_str,find(temp_input_str,"\n")+1,(int)strlen(temp_input_str)));
    }
    //printf("TEMP IS %s\n",temp_input_str);
    //if(input_str[(int)strlen(input_str)-1]=='\n')
    //    input_str=substr(input_str,0,(int)strlen(input_str)-1);
    //printf("here 5\n");
    //printf("\n\n\n\n|%s|\n\n\n\n",input_str);
    writeStringToFile(temp_file_name, input_str);
    writeStringToFile(temp_file_name, "\n");
    //###### Initialize Space ######
    //printf("here 6\n");
    //printf("\n\n\n\n|%s|\n\n\n\n",input_str);
    int space = atoi(getValueFromValueName(setting_file, "space"));
    bool now_writting_function = atoi(getValueFromValueName(setting_file, "now_writting_function"));
    bool now_writting_class = atoi(getValueFromValueName(setting_file, "now_writting_class"));
    bool now_writting_while = atoi(getValueFromValueName(setting_file, "now_writting_while"));
    bool now_writting_for = atoi(getValueFromValueName(setting_file, "now_writting_for"));
    bool now_run_if = atoi(getValueFromValueName(setting_file, "now_run_if"));
    char *last_if_sentence = getValueFromValueName(setting_file, "last_if_sentence");
    char *last_while_sentence = getValueFromValueName(setting_file, "last_while_sentence");
    char *string_in_while_loop = getValueFromValueName(setting_file, "string_in_while_loop");
    char *string_in_for_loop = getValueFromValueName(setting_file, "string_in_for_loop");
    char *temp_i = getValueFromValueName(setting_file, "temp_i");
    char *temp_i_in_for_sentence = getValueFromValueName(setting_file, "temp_i_in_for_sentence");
    int space_of_first_while_sentence = atoi(getValueFromValueName(setting_file, "space_of_first_while_sentence"));
    int space_of_first_for_sentence = atoi(getValueFromValueName(setting_file, "space_of_first_for_sentence"));
    int space_of_first_def_sentence = atoi(getValueFromValueName(setting_file, "space_of_first_def_sentence"));
    int space_of_first_class_sentence = atoi(getValueFromValueName(setting_file,"space_of_first_def_sentence"));
    
    //I add this value here in order to run now_run_if.
    bool can_run_basic_input = TRUE;
    bool run_goto = FALSE;


    int current_space = numOfSpaceAheadString(input_str);
    char temp2[100];
    sprintf(temp2, "%d", current_space);
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "current_space", (char*) temp2, "int");
    
    //printf("\n\n\n\n|%s|\n\n\n\n",input_str);
        // delete #.... after sentence
        char *temp_input_str2=trim(input_str);
        int index_of_jing=find_not_in_string(temp_input_str2, "#");
        if(index_of_jing!=-1 && index_of_jing !=0){
            input_str=substr(input_str, 0, find_not_in_string(input_str, "#"));
        }
        //
    printf("\n\n\n\n-------Now input is |%s|\n", input_str);
    //printf("-------Current Space is |%d|\n",current_space);
    //printf("temp2 is %s\n",temp2);
    //printf("-------Now Ahead Space is %d\n",current_space);
    //printf("-------Now writting in function is %d\n",now_writting_function);

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
            writeStringToFile("__walley_function__.wy", "#~End\n\n");
            //cleanFunctionFile("__walley_function__.wy");
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
        printf("Input Str is Empty\n");
        printf("now_writting_function is %d\n",now_writting_function);
        printf("now_writting_while is %d\n",now_writting_while);
    }
    if (current_space > space) {
        can_run_basic_input = FALSE;
    }
    //printf("-------Now Ahead Space is %d\n-------Now Required Space is %d\n",numOfSpaceAheadString(input_str),space);
    //printf("-------Now writting in function is %d\n",now_writting_function);

    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("Fail to initialize. No %s file found\n",file_name);
        exit(1);
    } else {
        fclose(fp);
    }
    
    //############### Now Writting While In Progress ########################
    if (now_writting_while == TRUE && str_is_empty==FALSE) {
        printf("Space %d, Current Space %d\n", space, current_space);
        if (current_space > space_of_first_while_sentence && current_space % 4 == 0) {
            printf("################ Now Writting While ###################");
            can_run_basic_input = FALSE;
            input_str = removeAheadSpaceForNum(input_str, space_of_first_while_sentence + 4);
            printf("Input str is |%s|\n", input_str);
            char *temp_in_loop = malloc(sizeof (char) *((int) strlen(input_str)+(int) strlen(string_in_while_loop) + 2));
            strcat(temp_in_loop, substr(string_in_while_loop, 0, (int) strlen(string_in_while_loop) - 1));
            strcat(temp_in_loop, input_str);
            strcat(temp_in_loop, "\\n\"");
            string_in_while_loop = temp_in_loop;
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "string_in_while_loop", string_in_while_loop, "string");
        } else if (current_space <= space_of_first_while_sentence && current_space % 4 == 0) {
            printf("Begin to Run While\n");
            can_run_basic_input = TRUE;
            now_writting_while = FALSE;

            char temp3[100];
            sprintf(temp3, "%d", now_writting_while);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_writting_while", (char*) temp3, "int");
            space=current_space;
            sprintf(temp3, "%d", space);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "space", (char*) temp3, "int");
            
            //get __temp_while__ to get last_while_sentence
            char *__temp_while__=getValueFromValueName(file_name,"__temp_while__");
            int length_of_list=valueNumOfList(__temp_while__);
            char *last_while_sentence2=valueOfListAtIndex(__temp_while__,length_of_list-1);
            printf("Last_While_Sentence is %s\n",last_while_sentence2);
            
            //get __temp_string_in_while_loop__
            char *__temp_string_in_while_loop__=getValueFromValueName(file_name,"__temp_string_in_while_loop__");
            __temp_string_in_while_loop__=listAppendOneElement(__temp_string_in_while_loop__,string_in_while_loop);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_name,"__temp_string_in_while_loop__",__temp_string_in_while_loop__);
            string_in_while_loop="\"#While\\n\"";
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "string_in_while_loop", string_in_while_loop, "string");
            char *string_in_while_loop2=valueOfListAtIndex(__temp_string_in_while_loop__,length_of_list-1);
                printf("String in while loop is %s\n", string_in_while_loop2);

                //while (Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function_Second_Generation(last_while_sentence, file_name) == TRUE) {
                while (Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function_Second_Generation(last_while_sentence2, file_name) == TRUE) {
                    char *temp_to_run = substr(string_in_while_loop2, 1, (int) strlen(string_in_while_loop2) - 1);
                    printf("Temp To Run is %s\n", temp_to_run);
                    if (strcmp(trim(temp_to_run), "pass") == 0) {
                        break;
                    }
                    if (strcmp(trim(temp_to_run), "continue") == 0) {
                        continue;
                    }
                    Walley_Run_Third_Generation(file_name, setting_file, temp_file_name, existing_file, temp_to_run);
                    //Walley_Run_For_Appointed_File(file_name,setting_file,temp_file_name,temp_to_run);
                }

                //Afte run while, remove the element at __temp_while__
            char final_index[100];
            sprintf(final_index,"%d",length_of_list-1);
            char *remove_at_index=malloc(sizeof(char)*((int)strlen("[]")+(int)strlen(final_index)));
            strcat(remove_at_index,"[");
            strcat(remove_at_index,final_index);
            strcat(remove_at_index,"]");
            printf("remove at index is %s\n",remove_at_index);
            __temp_while__=listRemoveOneElementAtOneIndex(__temp_while__,remove_at_index);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_name,"__temp_while__",__temp_while__);
            __temp_string_in_while_loop__=listRemoveOneElementAtOneIndex(__temp_string_in_while_loop__,remove_at_index);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_name,"__temp_string_in_while_loop__",__temp_string_in_while_loop__);
        }
    }//############### Now Writting Function In Progress #####################
    else if (now_writting_function == TRUE && str_is_empty==FALSE) {
        can_run_basic_input = FALSE;
        printf("//############### Now Writting Function In Progress #####################\n");
        printf("Current Space is %d, Required Space is %d\n",current_space,space);
        if (current_space % 4 != 0) {
            printf("Space Mistake\nCurrent Space is %d\nRequired Space is %d\n", current_space, space);
            exit(0);
        } else if (current_space <= space_of_first_def_sentence) {
            printf("Finish_define_FUNCTION\n");
            can_run_basic_input = TRUE;
            now_writting_function = FALSE;
            char temp2[100];
            space=current_space;
            sprintf(temp2, "%d", space);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "space", (char*) temp2, "int");
            sprintf(temp2, "%d", now_writting_function);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_writting_function", (char*) temp2, "int");
            
            printf("--------Finish defining function--------\n");
            writeStringToFile("__walley_function__.wy", "#~End\n\n");
        } else {

            space = current_space;
            input_str = removeAheadSpaceForNum(input_str, space_of_first_def_sentence + 4);
            writeStringToFile("__walley_function__.wy", input_str);
            writeStringToFile("__walley_function__.wy", "\n");
        }

        if (find_from_index_to_index(removeAheadSpace(input_str), "def ", 0, 5) != -1) {
            //printf("Find another function while defining a function\n");
            space = space + 4;
            //printf("Now required space is %d\n",space);
        }
        //}

    }        //################### Now Writting Class ##############################
    else if (now_writting_class == TRUE && str_is_empty==FALSE) {
        can_run_basic_input = FALSE;
        printf("#### Now_Writting_Class In Progress ####\n");
       
        if(current_space % 4 !=0){
            printf("Space Mistake occurred while defining a class\n");
        }
        else if (current_space<=space_of_first_class_sentence){
            printf("Finish defining class.\n");
            now_writting_class=FALSE;
            can_run_basic_input = TRUE;
            space=current_space;
            sprintf(temp2, "%d", space);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "space", (char*) temp2, "int");
            sprintf(temp2, "%d", now_writting_class);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_writting_class", (char*) temp2, "int");
        }
        else{
            printf("Now Writting Class To File\n");
            space=current_space;
            input_str = removeAheadSpaceForNum(input_str, space_of_first_def_sentence + 4);
            //printf("---->|%s|\n",input_str);
            
            char *__string_in_temp_class__=getValueFromValueName(file_name,"__string_in_temp_class__");
            char *__class_now__=getValueFromValueName(file_name,"__temp_class_name_now_writting__");
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
            changeTheOneVarValueFromItsInitialOneFromFileOrAddVarNameAndValueForDictionary(file_name,dict_var_name,string_in_class);
        }

    }        //################## Now Run If #######################################
    else if (now_run_if == TRUE && str_is_empty==FALSE) {
        printf("Now Run If\n");
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
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "space", (char*) temp2, "int");
        }

    }        //################## Now Run For #######################################
    else if (now_writting_for == TRUE && str_is_empty==FALSE) {
        //printf("#### Now Writting For ####");
        if (current_space > space_of_first_for_sentence && current_space % 4 == 0) {
            printf("################ Now Writting For ###################");
            //printf("STRING IN FOR LOOP is |%s|\n", string_in_for_loop);
            can_run_basic_input = FALSE;
            input_str = removeAheadSpaceForNum(input_str, space_of_first_for_sentence + 4);
            //printf("Input str is |%s|\n", input_str);
            char *temp_in_loop = malloc(sizeof (char) *((int) strlen(input_str)+(int) strlen(string_in_for_loop) + 2));
            strcat(temp_in_loop, substr(string_in_for_loop, 0, (int) strlen(string_in_for_loop) - 1));
            strcat(temp_in_loop, input_str);
            strcat(temp_in_loop, "\\n\"");
            string_in_for_loop = temp_in_loop;
            //printf("STRING IN FOR LOOP is |%s|\n", string_in_for_loop);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "string_in_for_loop", string_in_for_loop, "string");
        } else if (current_space <= space_of_first_for_sentence && current_space % 4 == 0) {
            printf("Begin to Run For\n");
            can_run_basic_input = TRUE;
            now_writting_for = FALSE;
            //printf("----String in loop is %s\n",string_in_for_loop);
            char temp3[100];
            sprintf(temp3, "%d", now_writting_for);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_writting_for", (char*) temp3, "int");

            if (strcmp(variableValueType(temp_i_in_for_sentence), "list") == 0) {
                //printf("i is list type\ni value is |%s|\n", temp_i_in_for_sentence);
                //printf("temp i is |%s|\n", temp_i);
                int value_num = valueNumOfList(temp_i_in_for_sentence);
            
            //get __temp_for__ to get last_while_sentence
            char *__temp_for__=getValueFromValueName(file_name,"__temp_for__");
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
            char *__temp_i__=getValueFromValueName(file_name,"__temp_i__");
            char *temp_i2=valueOfListAtIndexString(__temp_i__,temp_index);
            //printf("temp_i is %s\n",temp_i2);
            
            //get __temp_string_in_for_loop__
            char *__temp_string_in_for_loop__=getValueFromValueName(file_name,"__temp_string_in_for_loop__");
            __temp_string_in_for_loop__=listAppendOneElement(__temp_string_in_for_loop__,string_in_for_loop);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_name,"__temp_string_in_for_loop__",__temp_string_in_for_loop__);
            //printf("----String in loop is %s\n",string_in_for_loop);
            //printf("__temp_string_in_for_loop__ is %s\n",__temp_string_in_for_loop__);
            string_in_for_loop="\"#For\\n\"";
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "string_in_for_loop", string_in_for_loop, "string");
            //char *string_in_for_loop2=valueOfListAtIndex(__temp_string_in_for_loop__,length_of_list-1);
            char *string_in_for_loop2=valueOfListAtIndexString(__temp_string_in_for_loop__,temp_index);
            
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

                    Walley_Run_Third_Generation(file_name, setting_file, temp_file_name, existing_file, init_temp_i);
                    Walley_Run_Third_Generation(file_name, setting_file, temp_file_name, existing_file, temp_to_run);

                }
                string_in_for_loop = "\"#For\\n\"";
                temp_i = "\"None\"";
                temp_i_in_for_sentence = "\"None\"";
            }
            **/
                for (x = 0; x < value_num; x++) {
                    //printf("X--->%d\n", x);
                    char temp_num[100];
                    sprintf(temp_num, "%d", x);

                    char *index_temp = malloc(sizeof (char) *(2 + (int) strlen(temp_num)));
                    strcat(index_temp, "[");
                    strcat(index_temp, temp_num);
                    strcat(index_temp, "]");

                    char *value_of_i_in_x = valueOfListAtIndexString(temp_i_in_for_sentence2, index_temp);
                    //printf("value_of_i_in_x is |%s|\n",value_of_i_in_x);
                    //printf("Now Run %d Time\n",x);
                    //printf("Get Here\n");
                    char *init_temp_i = malloc(sizeof (char) *((int) strlen(temp_i2) + 2 + (int) strlen(value_of_i_in_x)));
                    strcat(init_temp_i, temp_i2);
                    strcat(init_temp_i, "=");
                    strcat(init_temp_i, value_of_i_in_x);
                    init_temp_i[(int)strlen(init_temp_i)]=0;
                    //printf("init_temp_i is |%s|\n",init_temp_i);
                    //printf("Get Here\n");
                    //printf("STRING IN FOR LOOP %s\n", string_in_for_loop2);
                    char *temp_to_run = substr(string_in_for_loop2, 1, (int) strlen(string_in_for_loop2) - 1);
                    //printf("TEMP TO RUN %s\n", temp_to_run);
                    //printf("Get Here\n");
                        if(strcmp(trim(temp_to_run),"pass")==0){
                         break;
                        }
                         if(strcmp(trim(temp_to_run),"continue")==0){
                      continue;
                  }
                    Walley_Run_Third_Generation(file_name, setting_file, temp_file_name, existing_file, init_temp_i);
                    Walley_Run_Third_Generation(file_name, setting_file, temp_file_name, existing_file, temp_to_run);

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
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_name,"__temp_for__",__temp_for__);
            __temp_string_in_for_loop__=listRemoveOneElementAtOneIndex(__temp_string_in_for_loop__,remove_at_index);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_name,"__temp_string_in_for_loop__",__temp_string_in_for_loop__);
            __temp_i__=listRemoveOneElementAtOneIndex(__temp_i__,remove_at_index);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_name,"__temp_i__",__temp_i__);
            }
            else {
                printf("#### For Sentence Only Support list Type At This Time\n");
            }

        }
    }

    //##########################################################################################################
    //##########################################################################################################
    //##########################################################################################################
    //##########################################################################################################
    printf("can run basic input %d numOfSpaceAheadString %d required space %d\n",can_run_basic_input,numOfSpaceAheadString(input_str),space);
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
                        writeStringToFile("__walley_function__.wy", "#~Begin\n");
                        //writeStringToFIle("__walley_function__.wy","Begin\n");

                        if (strcmp(func_param_str, "None") == 0) {
                            printf("This Function has no Parameter\n");
                        } else {
                            writeFunctionParameterOneByOneToFile(func_param_str);
                            writeStringToFile("__walley_function__.wy", "#~Finish Init Params\n");
                            //writeStringToFile("__walley_function__.wy","#Finish initialize parameters\n");
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
                    in_what = Walley_Substitue_Var_And_Function_Return_Value_From_File_Second_Generation(in_what, file_name);
                    printf("i is |%s|, in_what is |%s|\n", temp_i, in_what);
                    now_writting_for = TRUE;
                    //temp_i_in_for_sentence=getValueFromValueName(file_name,in_what);
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
        if (input_temp[0] == '#' ||
                find(input_temp, "for ") == 0 ||
                find(input_temp, "while ") == 0 ||
                find(input_temp, "if ") == 0 || find(input_temp, "elif ") == 0 || find(input_temp, "else") == 0 ||
                find(input_temp, "def ") == 0 ||
                find(input_temp,"class ")==0) {

            Walley_Judge_Run_Anotation_For_While_Def_Class(file_name, setting_file, input_str);
            
        }            //#################### Basic Input To Run #############################
        else {
            printf("\n\n######### Basic Input To Run #########\n");
            input_str = trim(input_str);
            //#####################  Init class  #####################
            if (find_not_in_string(input_str, " is ") != -1||
                                (find_not_in_string(input_str, "=")!=-1&&find_not_in_string(input_str,"(")!=-1&&checkWhetherSameClassExisted(file_name,trim(substr(input_str,find_not_in_string(input_str, "=")+1,find_not_in_string(input_str,"("))))==TRUE)
                    ) {
                printf("#### Begin to initialize class ####\n");
                // ## a is hello()
                // ## a is instance_name
                // ## hello() is __class__ 
                // ## in hello("Hello"), "Hello" is parameter.
                char *instance_name = substr(input_str, 0, find_not_in_string(input_str, " is "));
                char *__class__ = substr(input_str, find_not_in_string(input_str, " is ") + 4, (int) strlen(input_str));
                instance_name = trim(instance_name);
                __class__ = trim(__class__);
                char *class_name=substr(__class__,0,find(__class__,"("));
                char *parameter=substr(__class__,find(__class__,"(")+1,find_not_in_string(__class__,")"));
                /*
                char *__string_in_temp_class__ = getValueFromValueName(file_name, "__string_in_temp_class__");
                char *__class_now__ = toString(class_name);
                char *string_in_class = valueAtKey(__string_in_temp_class__, __class_now__);
                printf("string in class \n|%s|\n",string_in_class);
                **/
                //char *after_change=formatStringInClass(instance_name,string_in_class);
                char *after_change=formatStringInClassWithExtendFromFile(file_name,input_str);
                printf("#### AFTER CHANGE\n|%s|\n####\n",after_change);
                
                Walley_Run_Third_Generation(file_name, setting_file, temp_file_name, existing_file, after_change);
                addInstanceNameToFile(instance_name,file_name);
                
                
                
                // run init() function
                // a.init()
                char *init=malloc(sizeof(char)*((int)strlen(instance_name)+1+(int)strlen(".init()")+(int)strlen(parameter)));
                strcat(init,instance_name);
                strcat(init,".init(");
                strcat(init,parameter);
                strcat(init,")");
                init[(int)strlen(init)]=0;
                printf("BEGIN TO INITIALIZE");
                Walley_Run_Third_Generation(file_name, setting_file, temp_file_name, existing_file, init);
                
            }
            
            //#####################  println  ###################
            else if (find_not_in_string(input_str, "println") == 0) {
                char* output = Walley_Println_Second_Generation(file_name, strInBrackets(input_str));
                printf("%s", output);
            }//#####################  print  ###################
            else if (find_not_in_string(input_str, "print") == 0) {
                char* output = Walley_Print_Second_Generation(file_name, strInBrackets(input_str));
                printf("%s", output);
            }                //#################### import ####################
                            //#################### import ####################
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
                Walley_Run_Third_Generation(file_name, setting_file, temp_file_name, existing_file, content_of_file);
                Walley_Run_Third_Generation(file_name, setting_file, temp_file_name, existing_file, "#End Importing");
            }
            //This is also import
            else if (find(removeAheadSpace(input_str),"from ")==0){
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
                
                char *temp_file_to_run = malloc(sizeof (char) *((int) strlen(import_file) + 3));
                strcat(temp_file_to_run, import_file);
                strcat(temp_file_to_run, ".wy");
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
                Walley_Run_Third_Generation(file_name, setting_file, temp_file_name, existing_file, content_of_file);
                Walley_Run_Third_Generation(file_name, setting_file, temp_file_name, existing_file, "#End Importing");
            }            //##################### setmark ##################
            else if (find(removeAheadSpace(input_str), "setmark ") == 0) {
                printf("#### Find setmark ####");
            }//#################### goto ######################
            else if (find(removeAheadSpace(input_str), "goto ") == 0) {
                char *mark_name = substr(input_str, find(input_str, "goto ") + 5, (int) strlen(input_str));
                printf("Mark Name :%s\n", mark_name);
                mark_name = removeBackSpace(removeAheadSpace(mark_name));
                printf("#### Find goto ####");
                char *string_to_run;
                if (strcmp("None", existing_file) == 0) {
                    string_to_run = getStringFromFile(temp_file_name);
                } else {
                    string_to_run = getStringFromFile(existing_file);
                }
                printf("String in File is |%s|\n", getStringFromFile(temp_file_name));
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
                    printf("$$$ \n|%s|\n", string_to_run);
                    //clearTextInFile(temp_file_name);
                    writeStringToFile(temp_file_name, string_to_run);
                    writeStringToFile(temp_file_name, "\n");
                    run_goto = TRUE;
                    //Walley_Run_Second_Generation(file_name,setting_file,temp_file_name,string_to_run);
                }
            }                //#####################  Eval  ###################
            else if (isExpression(input_str) == TRUE) {
                Walley_Eval_And_Update_Var_And_Value_To_File_Second_Generation(file_name, input_str);
            }                // ##############  Is Not Expression ######################

                //#####################  Delete Space  ###################
                //} else if(strcmp("",removeBackSpace(removeAheadSpace(input_str)))==0){
                //    printf("Empty Input");
                //space=space-4;

                //#####################  Mistake  ###################
            else {

                /*
                 char *temp2 = Walley_Substitue_Var_And_Function_Return_Value_From_File(input_str, file_name);
                 //printf("temp2 is %s\n",temp2);
                 //printf("enter here\n");
                 if (strcmp(input_str, "None") != 0) {
                     Walley_Eval_With_Variable_From_File(file_name, temp2);
                     printf("Mistake May occurred which calling function Walley_Run_Second_Generation;\nThis Language is under development");
                 }
                 **/
                bool can_just_eval = TRUE;
                int index_of_dot = find_not_in_string(input_str, ".");
                if (index_of_dot > 0) {
                    char temp_char = input_str[index_of_dot - 1];
                    if (isalpha(temp_char)||temp_char=='_')
                        can_just_eval = FALSE;
                }
                if (isFunction(input_str) == TRUE) {
                    printf("Yes it is function\n");
                    can_just_eval = FALSE;
                }
                if (can_just_eval) {
                    char *temp2 = malloc(sizeof (char) *((int) strlen(input_str)+(int) strlen("__temp__=")));
                    strcat(temp2, "__temp__=");
                    strcat(temp2, input_str);
                    printf("TEMP2 is %s\n", temp2);
                    Walley_Eval_And_Update_Var_And_Value_To_File_Second_Generation(file_name, temp2);
                    Walley_Remove_Variable_And_Value_From_File(file_name, "__temp__");
                } else {
                    printf("Enter Else\n");
                    input_str = Walley_Substitue_Var_And_Function_Return_Value_From_File_Second_Generation(input_str, file_name);
                    Walley_Eval_With_Variable_From_File(file_name, input_str);
                }

            }
            //printf("\nRequired space num is %d\n",space);
            printf("#### Set Settings ####\n\n\n");
            char temp2[100];
            sprintf(temp2, "%d", space);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "space", (char*) temp2, "int");
            sprintf(temp2, "%d", now_writting_function);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_writting_function", (char*) temp2, "int");
            sprintf(temp2, "%d", now_writting_class);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_writting_class", (char*) temp2, "int");
            sprintf(temp2, "%d", now_writting_while);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_writting_while", (char*) temp2, "int");
            sprintf(temp2, "%d", now_writting_for);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_writting_for", (char*) temp2, "int");
            sprintf(temp2, "%d", now_run_if);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_run_if", (char*) temp2, "int");
            sprintf(temp2, "%d", space_of_first_while_sentence);
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "space_of_first_while_sentence", (char*) temp2, "int");
            sprintf(temp2, "%d", space_of_first_for_sentence);
            changeTheVarValueFromItsInitialOneFromFile(setting_file,"space_of_first_for_sentence", (char*)temp2,"int");
            sprintf(temp2, "%d", space_of_first_def_sentence);
            changeTheVarValueFromItsInitialOneFromFile(setting_file,"space_of_first_def_sentence", (char*)temp2,"int");
            sprintf(temp2, "%d", space_of_first_class_sentence);
            changeTheVarValueFromItsInitialOneFromFile(setting_file,"space_of_first_class_sentence", (char*)temp2,"int");

            changeTheVarValueFromItsInitialOneFromFile(setting_file, "last_if_sentence", last_if_sentence, "string");
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "last_while_sentence", last_while_sentence, "string");
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "string_in_while_loop", string_in_while_loop, "string");
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "string_in_for_loop", string_in_for_loop, "string");
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "temp_i", temp_i, "string");
            changeTheVarValueFromItsInitialOneFromFile(setting_file, "temp_i_in_for_sentence", temp_i_in_for_sentence, "string");
        }

    }
    /**
    //#################### Set Settigns ################################
    printf("#### Set Settings ####\n\n\n");
    char temp2[100];
    sprintf(temp2, "%d", space);
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "space", (char*) temp2, "int");
    sprintf(temp2, "%d", now_writting_function);
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_writting_function", (char*) temp2, "int");
    sprintf(temp2, "%d", now_writting_class);
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_writting_class", (char*) temp2, "int");
    sprintf(temp2, "%d", now_writting_while);
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_writting_while", (char*) temp2, "int");
    sprintf(temp2, "%d", now_writting_for);
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_writting_for", (char*) temp2, "int");
    sprintf(temp2, "%d", now_run_if);
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_run_if", (char*) temp2, "int");
    sprintf(temp2, "%d", space_of_first_while_sentence);
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "space_of_first_while_sentence", (char*) temp2, "int");
    sprintf(temp2, "%d", space_of_first_for_sentence);
    sprintf(temp2, "%d", space_of_first_def_sentence);
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "space_of_first_def_sentence", (char*) temp2, "int");
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "space_of_first_for_sentence", (char*) temp2, "int");
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "last_if_sentence", last_if_sentence, "string");
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "last_while_sentence", last_while_sentence, "string");
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "string_in_while_loop", string_in_while_loop, "string");
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "string_in_for_loop", string_in_for_loop, "string");
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "temp_i", temp_i, "string");
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "temp_i_in_for_sentence", temp_i_in_for_sentence, "string");*/
    printf("here\n");
    if (continue_run == TRUE && run_goto == FALSE) {
        printf("continue run\n");
        if (find_gang_gang == TRUE) {
            Walley_Run_Third_Generation(file_name, setting_file, temp_file_name, existing_file, substr(temp_input_str, find(temp_input_str, "\\n") + 2, (int) strlen(temp_input_str)));

        } else {
            printf("STRING LEFT is %s\n",substr(temp_input_str,find(temp_input_str,"\n")+1,(int)strlen(temp_input_str)));
            Walley_Run_Third_Generation(file_name, setting_file, temp_file_name, existing_file, substr(temp_input_str, find(temp_input_str, "\n") + 1, (int) strlen(temp_input_str)));
        }
    }
    if (run_goto == TRUE) {
        printf("@@@@ Run GOTO @@@@\n");
        Walley_Run_Third_Generation(file_name, setting_file, temp_file_name, existing_file, getStringFromFile(temp_file_name));
    }
    }
}

/*
 *This function is mainly about  Walley_Run_One_Function_And_Return_Value. get_var_from_file_name is you get parameter
 * value from the file that you appointed.
 */
//char *Walley_Run_One_Function_And_Return_Value(char *input_str){
char *Walley_Run_One_Function_And_Return_Value_Third_Generation(char *input_str,char *get_var_from_file_name){
    printf("\n#### Walley_Run_One_Function_And_Return_Value_Third_Generation ####\n");
    char* return_var_name="None";
    char* return_value;
    printf("Function is |%s|\n",input_str);
    
    //printf("here");
    input_str=removeBackSpace(input_str);
    input_str=removeAheadSpace(input_str);
    /*
    char *temp=malloc(sizeof(char)*(int)strlen(input_str)+sizeof(char)*1);
    temp=substr(input_str, 0, find(input_str,")"));
    strcat(temp,"  ):");
    input_str=temp;**/
    
    char temp22[1000]="";
    strcat(temp22,substr(input_str, 0,find(input_str,")")));
    strcat(temp22," ):"); 
    char *temp=malloc(sizeof(char)*((int)strlen(temp22)+1));
    int aa=0;
    for(aa=0;aa<(int)strlen(temp22);aa++){
        temp[aa]=temp22[aa];
    }
    temp[(int)strlen(temp)]=0;
    input_str=temp;
    
    //char *func_name=substr(input_str, find(input_str,"def")+3,find(input_str,"("));
    char *func_name=substr(input_str,0,find(input_str,"("));
    func_name=removeAheadSpace(func_name);
    func_name=removeBackSpace(func_name);    

    
    printf("here1\n");
    char *parameter_str=substr(input_str, find(input_str,"(")+1,find(input_str,")"));
    //printf("#### parameter_str is %s ####\n",parameter_str);
    printf("here2\n");
    parameter_str=removeAheadSpace(parameter_str);
    //printf("#### parameter_str is %s ####\n",parameter_str);
    parameter_str=removeBackSpace(parameter_str);
    //printf("###### Parameter is : %s ######\n",parameter_str);
    
    printf("here3\n");
    printf("Params is %s\n",parameter_str);
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
    
    FILE *fp;
    char *file_var_temp_name=malloc(sizeof(char)*((int)strlen("__walley_temp___.wy")+(int)strlen(func_name)+1));
    strcat(file_var_temp_name,"__walley_temp_");
    strcat(file_var_temp_name,func_name_temp);
    strcat(file_var_temp_name,"__.wy");
    //fp=fopen("__walley_temp__.wy","w");
    file_var_temp_name[(int)strlen(file_var_temp_name)]=0;
    Walley_Initialize_Var_File(file_var_temp_name);
    printf("==== file_var_temp_name %s\n",file_var_temp_name);
    
    char *file_settings_temp_name=malloc(sizeof(char)*((int)strlen("__walley_settings_temp___.wy")+(int)strlen(func_name)+1));
    strcat(file_settings_temp_name,"__walley_settings_temp_");
    strcat(file_settings_temp_name,func_name_temp);
    strcat(file_settings_temp_name,"__.wy");
    file_settings_temp_name[(int)strlen(file_settings_temp_name)]=0;
    //fp=fopen("__walley_settings_temp__.wy","w");
    /*
    fp=fopen(file_settings_temp_name,"w");
    
    if(fp==NULL){
        printf("Failed to initialize temp settings");
    } else {
        fputs("#~\n",fp);
        fputs("space:0:int\n",fp);
        fputs("now_writting_function:0:int\n",fp);
        fputs("now_writting_class:0:int\n",fp);
        fputs("now_run_if:0:int\n",fp);
        fputs("last_if_sentence:\"None\":string\n",fp);
        fclose(fp);
    }**/
    Walley_Initialize_Settings_File(file_settings_temp_name);
    printf("==== file_settings_temp_name %s\n", file_settings_temp_name);

    char *file_file_temp_name = malloc(sizeof (char) *((int) strlen(func_name)+(int) strlen("__walley_file_temp___.wy") + 1));
    strcat(file_file_temp_name, "__walley_file_temp_");
    strcat(file_file_temp_name, func_name_temp);
    strcat(file_file_temp_name, "__.wy");
    file_file_temp_name[(int) strlen(file_file_temp_name)] = 0;
    //fp=fopen("__walley_settings_temp__.wy","w");
    fp = fopen(file_file_temp_name, "w");
    if (fp == NULL) {
        printf("Failed to initialize file");
    } else {
        fputs("#Temp File In Order To Run goto\n", fp);
        fclose(fp);
    }
    printf("file_file_temp_name %s\n", file_file_temp_name);

    bool find_function = FALSE;
    bool begin = FALSE;
    bool finish = FALSE;
    bool finish_init_param = FALSE;
    bool find_return = FALSE;

    char *temp_temp = malloc(sizeof (char) *((int) strlen(func_name) + 1));
    strcat(temp_temp, func_name);
    strcat(temp_temp, ":");


    char *temp2 = malloc(sizeof (char) *(int) strlen(parameter_str) + 2);
    strcat(temp2, parameter_str);
    strcat(temp2, ",");
    temp2[(int)strlen(temp2)]=0;
    parameter_str = temp2;

    int from_index = 0;
    int count = 0;
    char output[10000] = "";

    char arr[1000] = "";
    fp = fopen("__walley_function__.wy", "r");
    while ((fgets(arr, 1000, fp)) != NULL) {
        //char one_line[1000];
        printf("----arr----%s\n", arr);
        printf("Finish init param %d\n", finish_init_param);
        if (find_function == TRUE && strcmp("return", substr(removeBackSpace(removeAheadSpace(arr)), 0, 6)) == 0) {

            //find_return=TRUE;
            printf("--------Find Return--------");
            Walley_Run_Third_Generation(file_var_temp_name, file_settings_temp_name, file_file_temp_name, "__walley_function__.wy", "#FIND RETURN");
            finish = TRUE;
            return_var_name = substr(arr, find(arr, "return") + 7, (int) strlen(arr));
            return_var_name = removeAheadSpace(return_var_name);
            return_var_name = removeBackSpace(return_var_name);
            if (return_var_name[(int) strlen(return_var_name) - 1] == '\n') {
                return_var_name = substr(return_var_name, 0, (int) strlen(return_var_name) - 1);
            }
            //printf("Return Var Name is :%s\n",return_var_name);
            break;
        }

        if (find(arr, temp_temp) != -1) {
            printf("Find Function\n");
            //printf("arr is %s, temp_temp is %s\n",arr,temp_temp);
            find_function = TRUE;
        }
        if (find_function == TRUE && find(arr, "#~End\n") != -1) {
            printf("Find End\n");
            finish = TRUE;
        }

        if (finish == TRUE) {
            //printf("Finish\n\n");
            break;

        }

        if(finish_init_param==TRUE && finish==FALSE){
            strcat(output,arr);
            printf("------->%s\n",arr);
            //Walley_Run(arr);
            //Walley_Run_For_Appointed_File("__walley_temp__.wy","__walley_settings_temp__.wy",arr);
            char *temp=removeAheadSpace(removeBackSpace(arr));
            //printf("----After remove space---> %s ---\n",temp);
            if(isFunction(temp)){
                    printf("Is Function1111\n");
                    printf("%s\n",Walley_Run_One_Function_And_Return_Value_Third_Generation(temp,file_var_temp_name));
                } 
            else{
                printf("*************** GO THERE ***************");
                // if is_instance_value is true, save like Rohit.age to __walley__.wy 
                bool is_instance_value=FALSE;
                if(isExpression(arr)){
                    printf("********* %s IT IS EXPRESSION ********\n",arr);
                    char *var_name2=variableName(arr);
                    char *user;
                    if(find_not_in_string(var_name2,".")!=-1){
                        user=substr(var_name2,0,find_not_in_string(var_name2,"."));
                        bool is_instance=checkWhetherSameInstanceExisted("__walley__.wy",user);
                        if(is_instance)
                            is_instance_value=TRUE;
                        else
                            is_instance_value=FALSE;
                    }
                    
                }
                if(is_instance_value==FALSE){
                    printf("********** Not INSTANCE VALUE *********\n");
                        Walley_Run_Third_Generation(file_var_temp_name,file_settings_temp_name,file_file_temp_name,"__walley_function__.wy",arr);
                }
                else{
                    printf("************ IT IS INSTANCE VALUE ************");
                    printf("************ %s **********\n",arr);
                    Walley_Run_Third_Generation(file_var_temp_name, file_settings_temp_name, file_file_temp_name, "__walley_function__.wy", arr);
                    char *var_name3 = variableName(arr);
                    char *var_value3 = getValueFromValueName(file_var_temp_name, var_name3);
                    Walley_Update_Var_And_Var_Value_To_File("__walley__.wy", var_name3, var_value3);
                }
            }
        }

        if (begin == TRUE && finish_init_param == FALSE) {
            //printf("Initialize parameters\n");
            //printf("param str is %s\n",parameter_str);
            //if(strcmp(parameter_str,"None")==0){
            printf("PARAMETER is %s\n", parameter_str);

            // 12,13,12,
            //printf("Enter Here\n");
            char *arr_arr;
            if (arr[(int) strlen(arr) - 1] == '\n') {
                //if(find(arr,"\n")!=-1)
                //arr_arr = malloc(sizeof (char) *((int) strlen(arr) - 1));
                arr_arr = substr(arr, 0, (int) strlen(arr) - 1);
            } else {
                //arr_arr = malloc(sizeof (char) *((int) strlen(arr)));
                //strcat(arr_arr, arr);
                arr_arr=append("", arr);
            }
            arr_arr = removeBackSpace(arr_arr);
            
            if (find_not_in_string(removeAheadSpace(arr_arr), "##Finish Init Params")==0) {
                finish_init_param=TRUE;
                printf("finish_init_param\n");
                continue;
            }
            
            
            
            if (stringIsEmpty(substr(arr_arr, find_not_in_string(arr_arr, "=")+1, (int)strlen(arr_arr)))==FALSE
                &&checkWhetherSameVarNameExistsFromFile(file_var_temp_name, substr(arr_arr, 0, find_not_in_string(arr_arr, "=")))==FALSE) {
                 Walley_Run_Third_Generation(file_var_temp_name, file_settings_temp_name,file_file_temp_name,"__walley_function__.wy",arr_arr);
            }
            
            if (strcmp(parameter_str, "None,") == 0) {
                printf("Params is None\n");
                //finish_init_param = TRUE;
                continue;
            }

            
            char *var_value;
            //if(find_from_index_not_in_string(parameter_str, ",",from_index+1)==-1)
            if(find_from_index_not_in_str_list_dict(parameter_str, ",",from_index+1)==-1){
                printf("==-1\n");
                printf("parameter_str |%s|,from_index %d\n",parameter_str,from_index);
                continue;
            }
            else{
                var_value = substr(parameter_str, from_index, find_from_index_not_in_str_list_dict(parameter_str, ",", from_index + 1));
            }
            // It is not expression
            if (find_not_in_string(var_value, "=")==-1) {
                arr_arr = substr(arr_arr, 0, find_not_in_string(arr_arr, "=")+1);
                if (stringIsDigit(var_value) == FALSE && strcmp(variableValueType(var_value), "string") != 0
                    &&strcmp(variableValueType(var_value), "list") != 0
                    &&strcmp(variableValueType(var_value), "dictionary") != 0) {
                    var_value = getValueFromValueName(get_var_from_file_name, var_value);
                }
                //strcat(arr_arr, var_value);
                arr_arr=append(arr_arr, var_value);
            }
            // It is expression
            else{
                arr_arr=var_value;
            }
            printf("var value is %s\n",var_value);

            
            
            
            strcat(output, arr_arr);
            strcat(output, substr(parameter_str, from_index, find_from_index_not_in_string(parameter_str, ",", from_index + 1)));
            strcat(output, "\n");
            
            printf("------->%s\n",arr_arr);
            
            //Walley_Run(arr_arr);
            //Walley_Run_For_Appointed_File("__walley_temp__.wy","__walley_settings_temp__.wy",arr_arr);
            if ((int) strlen(removeAheadSpace(removeBackSpace(arr_arr))) != 0){
                Walley_Run_Third_Generation(file_var_temp_name, file_settings_temp_name,file_file_temp_name,"__walley_function__.wy",arr_arr);
            }
            
            from_index = find_from_index_not_in_str_list_dict(parameter_str, ",", from_index + 1) + 1;
            
            /*
            if ((from_index + 1) >= (int) strlen(parameter_str)) {
                finish_init_param = TRUE;
                //printf("finish init param\n");
            }*/
        }

        if (find_function == TRUE && find(arr, "#~Begin\n") != -1) {
            //printf("Begin to initialzie parameters\n");
            begin = TRUE;
        }
    }
    
    if(strcmp(return_var_name,"None")==0){
        printf("------Return None------\n");
        return_value="None";
    } else {
        //printf("Enter Else\n");
        //return_var_name=substitueExistedVarValueFromFile(return_var_name,"__walley_temp__.wy");
        return_var_name=Walley_Substitue_Var_And_Function_Return_Value_From_File_Second_Generation(return_var_name,file_var_temp_name);
        printf("After substitueExistedVarValueFromFile, return var name is :%s\n",return_var_name);
        return_value=Walley_Eval(return_var_name);
        //return_value="Hi";
    }
    
    
    
    //remove("__walley_temp__.wy");
    //remove("__walley_settings_temp__.wy");
    remove(file_var_temp_name);
    remove(file_settings_temp_name);
    remove(file_file_temp_name);
    
    //printf("The output is \n####################\n%s####################\n",output);
    return return_value;
}

char *Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(char* input_str,char *file_var_name){//, char *file_function_name){
    printf("#### Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation ####\n");
    printf("#### input str is |%s| ####\n",input_str);
    
    //######### replace the thing inside the {} and []
    //substitueValueInDictionaryAndList(input_str,file_var_name);
    int i=0;
    int begin=0;  //begin of { and [
    int end = 0; // end of } and ]
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
                        char *with_str = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(replace_str, file_var_name);
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
                    if (finishFindingVarAndFunction(replace_str) == FALSE) {//from x{i} get i
                        char *with_str = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(replace_str, file_var_name);
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
                        char *with_str = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(replace_str, file_var_name);
                        input_str = replace_from_index_to_index(input_str, replace_str, with_str, begin + 1, end);
                    }
                }
            //}
        }
    }
    printf("AFTER REPLACE THE THING IN [] AND {}\nTHE INPUT IS |%s|\n",input_str);
    printf("input str is :%s\nlength is %d\n",input_str,(int)strlen(input_str));
    //printf("Required File is %s\n",file_var_name);
    bool find_alpha=FALSE;
    bool finish_find_var=FALSE;
    bool find_function=FALSE;
    //int begin=0;
    //int end=(int)strlen(input_str);
    //int i=0;
    begin=0;
    end=(int)strlen(input_str);
    i=0;
    
    
    char *output=malloc(sizeof(char)*((int)strlen(input_str)+1));
    //char output[1000]="";
    for(i=0;i<(int)strlen(input_str);i++){
        output[i]=input_str[i];
    }
    output[(int)strlen(input_str)]=0;
    //printf("Output now is %s\n",output);
    
    //char *output=malloc(sizeof(char)*1000);
    //strcat(output,input_str);
    
    bool has_var=FALSE;
    for(i=0;i<(int)strlen(input_str);i++){
        //printf("*********** %c End is %d --->%s\n",input_str[i],end,output);
        //printf("#### Enter Loop Output is %s\n####",output);
        //printf("#### Output Length is %d\n",(int)strlen(output));
        int temp_length=(int)strlen(output);
        printf("--->%c find_var %d\n",input_str[i],find_alpha);
        /*
        if(finishFindingVarAndFunction(output)==TRUE){
            printf("Finish Finding Var And Function, output is |%s|\n",output);
            output=substr(output,0,temp_length);
            break;
        }*/
        
        //printf("\n%d %c\n",i,input_str[i]);
        //printf("#### Output is %s\n####",output);
        //printf("--End this loop, output is %s\n",output);
        //charIsInString(input_str,i);
        //printf("++End this loop, output is %s\n",output);
        //if(find_alpha==FALSE && isalpha(input_str[i]) && charIsInString(input_str,i)==FALSE){
         /*
          * add input_str[i]=='_' in order for __temp_while__.append()......
          */   
       // if(find_alpha==FALSE && (isalpha(input_str[i])||input_str[i]=='_' )&& charIsInString(input_str,i)==FALSE){
        if(find_alpha==FALSE && (isalpha(input_str[i])||input_str[i]=='_'||input_str[i]=='"'||input_str[i]=='\''||input_str[i]=='[' )&& charIsInString(input_str,i)==FALSE){
            printf("Find alpha\n");
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
            printf("ENTER HERE\n");
            if (input_str[i]=='[') {
                printf("It is [\n");
                if (count_str_not_in_string(substr(input_str, 0, i), "[")==count_str_not_in_string(substr(input_str, 0, i), "]")) {
                    find_function=TRUE;
                    printf("FIND FUNCTION\n");
                } else {
                    find_function=FALSE;
                }
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
            printf("Func_Name is %s\n",func_name);
            bool it_is_slice=FALSE;// = checkWhetherSameVarNameExistsFromFile(file_var_name, func_name);
            if (checkWhetherSameVarNameExistsFromFile(file_var_name, func_name)==TRUE||
                strcmp(variableValueType(func_name),"string")==0||
                strcmp(variableValueType(func_name), "list")==0) {
                it_is_slice=TRUE;
            }
            printf("it is function %d\n",it_is_slice);
            if (it_is_slice==FALSE) {
                char *temp = substr(input_str, i, (int) strlen(input_str));
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
                //################################################################
                //######## Check Embed Function ##################################
                char *return_value;

                //################### Special Function #########################################################
                /*
                 * eg x="Hello"-----> x.find("He")----->0
                 */
                printf("#### Third Generation FUNCTION is |%s| ####\n", function);
                printf("I DO Not Know What Happened\n");
                
                //bool same_function_existed_in_walley_function=checkWhetherSameFunctionNameExists(func_name);
                
                if (find(substr(function, 0, find(function, "(")), ".") != -1 && charIsInString(function, find(function, ".")) == FALSE) {
                    printf("It is instance function\n");
                    char *user = substr(function, 0, find(function, "."));
                    bool instance_existed = checkWhetherSameInstanceExisted(file_var_name, user);
                    bool var_existed = checkWhetherSameVarNameExistsFromFile(file_var_name,user);
                    
                    char *user_value=Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(user, file_var_name);
                    char *function_temp=replace_not_in_string(function, user, user_value);
                    
                    
                    if (strcmp(variableValueType(user_value), "string")==0||strcmp(variableValueType(user_value), "list")==0) {
                        var_existed=TRUE;
                    }             
                    
                    if (instance_existed == FALSE && var_existed==TRUE){
                        return_value = Walley_Run_Special_Function(function_temp, file_var_name);
                        //printf("RETURN VALUE is %s\n",return_value);
                    }
                    else {
                        printf("FIND INSTANCE, THIS IS A CLASS FUNCTION\n");
                        return_value = Walley_Run_One_Function_And_Return_Value_Third_Generation(function, "__walley__.wy");
                    }

                }


                    //################### Embeded Function ###############################################################
                else if (find(function, "int(") ==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = to_int(temp_value);
                } else if (find(function, "double(") ==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = to_double(temp_value);
                } else if (find(function, "nstr(") ==0) {
                    printf("Find nstr(");
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = to_nstr(temp_value);
                } else if (find(function, "str(")==0) {
                    
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = to_string(temp_value);
                } else if (find(function, "sin(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = math_sin(temp_value);
                } else if (find(function, "cos(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = math_cos(temp_value);
                } else if (find(function, "tan(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = math_tan(temp_value);
                } else if (find(function, "exp(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = math_exp(temp_value);
                } else if (find(function, "log10(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = math_log10(temp_value);
                } else if (find(function, "type(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = var_value_type(temp_value);
                    printf("Find type() and return value is %s\n", return_value);
                } else if (find(function, "num(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = to_num(temp_value);
                } else if (find(function, "time(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = simple_time(temp_value);
                } else if (find(function, "file_readlines(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = file_readlines(temp_value);
                }
                else if (find(function, "file_writelines(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    temp_value=toCString(temp_value);
                    char *file_name = substr(temp_value, 0, find_not_in_string(temp_value, ","));
                    char *lines = substr(temp_value, find_not_in_string(temp_value, ",") + 1, (int) strlen(temp_value));
                    file_name = toCString(file_name);
                    lines=toCString(lines);
                    return_value = file_writelines(file_name,lines);
                } else if (find(function, "remove_file(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = file_removefile(temp_value);
                } else if (find(function, "create_file(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = file_createfile(temp_value);
                } else if (find(function, "system(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = walley_system(temp_value);
                } else if (find(function, "input(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = var_input(temp_value);
                }
                    

                    //#################################################################
                else {

                    printf("HERE++++!!!!!\n");

                    return_value = Walley_Run_One_Function_And_Return_Value_Third_Generation(function, "__walley__.wy");
                }
                end=index_of_youkuohao+1;
                int begin_temp = begin + (int) strlen(output)-(int) strlen(input_str);
                int end_temp = end + (int) strlen(output)-(int) strlen(input_str);

                //printf("Begin %d, End %d\n",begin_temp,end_temp);
                //printf("Before change, output is %s\n",output);
                //printf("For input_str Begin %d, End %d\n",begin,end);
                //printf("Begin %d, End %d\n",begin_temp,end_temp);
                //printf("Before change,input_str is %s output is %s\n",input_str,output);
                output = replace_from_index_to_index(output, function, return_value, begin_temp, end_temp);

                i = index_of_youkuohao;
                find_alpha = FALSE;
                has_var = TRUE;
                finish_find_var = FALSE;
                continue;
            }
                // IT is slice
            else {
                printf("It is slice\n");
                int index_of_rect = find_from_index_not_in_string(input_str, "]", i + 1);
                
                // case like x[0:1].toupper()
                if (input_str[index_of_rect+1]=='.') {
                    printf("Find . after ]");
                    find_alpha=TRUE;
                    find_function=FALSE;
                    continue;
                }
                
                char *slice_str = substr(input_str, i, index_of_rect + 1);
                char *value_of_var; //= getValueFromValueName(file_var_name, func_name);
                
                if (checkWhetherSameVarNameExistsFromFile(file_var_name, func_name)==TRUE) {
                    value_of_var=getValueFromValueName(file_var_name, func_name);
                }
                else if (strcmp(variableValueType(func_name), "string")==0){
                    value_of_var=func_name;
                }
                else if (strcmp(variableValueType(func_name), "list")==0){
                    value_of_var=func_name;
                }
                else{
                    printf("Mistake occurred while calling function Walley_Substitute_Third....\n%s is wrong whiling judging it is slice\n",func_name);
                    exit(0);
                }
                
                char *replace_str = substr(input_str, begin, index_of_rect + 1);
                char *with_str = old_slice(value_of_var, slice_str);
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
                //func_name
                /*
                int index_of_circle = find_from_index_not_in_string(input_str, ")",i+1);
                int index_of_rect = find_from_index_not_in_string(input_str, "]",i+1);
                printf("( %d [ %d\n\n",index_of_circle,index_of_rect);
                if (index_of_circle == -1 && index_of_rect == -1) {
                    printf("Mistake occurred while calling function Walley_Run_One_Function_And_Return_Value3rd\nIt is not a slice");
                    exit(0);
                }                    // you bian shi )
                else if ((index_of_circle!=-1&&index_of_circle < index_of_rect) || (index_of_rect == -1 && index_of_circle != -1)) {
                    char *slice_str = substr(input_str, i, index_of_circle + 1);
                    char *value_of_var = getValueFromValueName(file_var_name, func_name);
                    char *replace_str = substr(input_str, begin, index_of_circle + 1);
                    char *with_str = slice(value_of_var, slice_str);
                    
                    
                    
                    int begin_temp = begin + (int) strlen(output)-(int) strlen(input_str);
                    int end_temp = end + (int) strlen(output)-(int) strlen(input_str);

                    //printf("Begin %d, End %d\n",begin_temp,end_temp);
                    //printf("Before change, output is %s\n",output);
                    output = replace_from_index_to_index(output, replace_str, with_str, begin_temp, end_temp);

                    i = index_of_circle;
                    find_alpha = FALSE;
                    has_var = TRUE;
                    finish_find_var = FALSE;
                    continue;
                }// you bian shi ]
                else if ((index_of_rect!=-1&&index_of_rect < index_of_circle) || (index_of_circle == -1 && index_of_rect != -1)) {
                    printf("it is ]\n");
                    char *slice_str = substr(input_str, i, index_of_rect + 1);
                    
                    char *value_of_var = getValueFromValueName(file_var_name, func_name);
                    
                    char *replace_str = substr(input_str, begin, index_of_rect + 1);
                    
                    char *with_str = slice(value_of_var, slice_str);
                    printf("here\n");
                    int begin_temp = begin + (int) strlen(output)-(int) strlen(input_str);
                    int end_temp = end + (int) strlen(output)-(int) strlen(input_str);

                    //printf("Begin %d, End %d\n",begin_temp,end_temp);
                    //printf("Before change, output is %s\n",output);
                    output = replace_from_index_to_index(output, replace_str, with_str, begin_temp, end_temp);

                    i = index_of_rect;
                    find_alpha = FALSE;
                    has_var = TRUE;
                    finish_find_var = FALSE;
                    continue;
                }*/
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
            //printf("end %d\n",end);     
            finish_find_var = TRUE;
        }
        //printf("--End this loop, output is %s\n",output);
        if (finish_find_var) {
            //printf("@@@@ Enter finish_find_var @@@@\n");
            //printf("------\n%s\n------\n",substr(input_str,begin,end));
            //printf("Begin %d, End %d\n",begin,end);
            char *var_name = substr(input_str, begin, end);
            char *var_value;
            //if var_name is a instance var like x.age, then try to get value from __walley__.wy
            if (find_not_in_string(var_name, ".") != -1) {
                char *user = substr(var_name, 0, find_not_in_string(var_name, "."));
                if (checkWhetherSameInstanceExisted("__walley__.wy", user) == TRUE) {
                    var_value=getValueFromValueName("__walley__.wy", var_name);
                } 
                else {
                    var_value=getValueFromValueName(file_var_name,var_name);
                }
                
            } 
            else {
                if(checkWhetherSameVarNameExistsFromFile(file_var_name,var_name)==TRUE){
                        var_value=getValueFromValueName(file_var_name,var_name);
                } else {
                    var_value=var_name;
                }
            }
            //printf("Var Name %s\nVar Value %s\n",var_name,var_value);
            int begin_temp=begin+(int)strlen(output)-(int)strlen(input_str);
            int end_temp=end+(int)strlen(output)-(int)strlen(input_str);
            
            //printf("Begin %d, End %d\n",begin_temp,end_temp);
            //printf("Before change, output is %s\n",output);
            output=replace_from_index_to_index(output,var_name,var_value,begin_temp,end_temp);
            //printf("Output is %s\n",output);
            has_var=TRUE;
            finish_find_var=FALSE;
            find_alpha=FALSE;
            //free(var_name);
            //free(var_value);
        }
        //printf("--End this loop, output is %s\n",output);
        
    }
    
    //if(has_var==FALSE){
    //    return input_str;
    //}
    
    output=Walley_Eval_All_From_File(file_var_name, output);
    printf("Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation !!!!!!output is %s\n",output);
    return output;
}

bool Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function_Third_Generation(char *input_str, char *var_in_file_name){
    printf("#### Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function_Third_Generation ####\n");
    // I did not consider the situation when and or or is in string
    //printf("%d\n",find(input_str," and "));
    input_str=cleanJudgeSentence(input_str);
    if(find(input_str," and ")!=-1){
        //printf("Find And\n");
        input_str=replace(input_str," and ","+++++");
    }
    if(find(input_str," or ")!=-1){
        //printf("Find Or\n");
        input_str=replace(input_str," or ","----");
    }
    if(find(input_str,"TRUE")!=-1){
        //printf("Find And\n");
        if(find_from_index(input_str,"==TRUE",find(input_str,"TRUE")-2)!=1){
        //printf("%d\n",find_from_index(input_str,"==TRUE",find(input_str,"TRUE")-2));
        input_str=replace(input_str,"TRUE","1==1");
        //printf("@%s\n",input_str);
        } else {
            input_str=replace(input_str,"TRUE","1");
        }
    }
    if(find(input_str,"FALSE")!=-1 ){
        //printf("Find Or\n");
        if(find_from_index(input_str,"==FALSE",find(input_str,"FALSE")-2)!=1){
        //printf("%d\n",find_from_index(input_str,"==FALSE",find(input_str,"FALSE")-2));
        input_str=replace(input_str,"FALSE","0==1");
        //printf("@%s\n",input_str);
        } else {
            input_str=replace(input_str,"FALSE","0");
        }
    }
    //######### if not 3>4: #########
    //############# Add Not #########
    if(find(input_str,"not ")!=-1){
        input_str=replace(input_str,"not ","*****");
    }
    
    
    //printf("%s\n",input_str);
    input_str=Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(input_str,var_in_file_name);
    //printf("%s\n",input_str);
    if(find(input_str,"+++++")!=-1){
        input_str=replace(input_str,"+++++"," and ");
    }
    
    if(find(input_str,"----")!=-1){
        input_str=replace(input_str,"----"," or ");
    }
    
    if(find(input_str,"*****")!=-1){
        input_str=replace(input_str,"*****","not ");
    }
    //printf("####----->%s\n",input_str);
    //printf("Here\n");
    bool output=judgeWithAndAndOrWithParenthesis(input_str);
    
    return output;
}

//############################### If is expression, DO THAT ###################################

void Walley_Eval_And_Update_Var_And_Value_To_File_Third_Generation(char* file_var_name,char* input_str) {
    //else if (isExpression(input_str)==TRUE){
    printf("#### Walley_Eval_And_Update_Var_And_Value_To_File_Third_Generation ####\n");
    char *var_name = variableName(input_str);
    char *var_value = variableValue(input_str);
    char *var_value_type = variableValueType(var_value);
    printf("#### The Variable Value is :%s\n", var_value);
    printf("#### The Variable Value Type is :%s\n", var_value_type);
        
    //Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation AND Walley_Eval_With_Variable_From_File
    //Do not support operation of list and dictionary now
    if(strcmp("list",var_value_type)!=0 && strcmp("dictionary",var_value_type)!=0){
        printf("var value type is not list or dictionary\n");
        var_value = Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(var_value, file_var_name);
    }
    var_value = Walley_Eval_With_Variable_From_File(file_var_name, var_value);
    var_value_type = variableValueType(var_value);
    
    printf("#### The Variable Name is :%s\n", var_name);
    printf("#### The Variable Value is :%s\n", var_value);
    printf("#### The Variable Value Type is :%s\n", var_value_type);
    //printf("The Variable Value after put known Variable in is :%s\n",putKnownVariableIntoExpression(var_value));


    // ################### Basic Calculation ##################################
    //if(strcmp(var_value_type,"unknown type")!=0){//&&strcmp(var_value_type,"function")!=0){
    //printf("Enter Here\n");
    Walley_Update_Var_And_Var_Value_To_File(file_var_name,var_name,var_value);
    
        //write instance x.age to __walley__.wy
    /*
    if(find_not_in_string(var_name,".")!=-1){
        char *user=substr(var_name,0,find_not_in_string(var_name,"."));
        if(checkWhetherSameInstanceExisted("__walley__.wy",user)==TRUE){
            Walley_Eval_And_Update_Var_And_Value_To_File_Third_Generation("__walley__.wy",input_str);
        }
    }**/
}


char *Walley_Print_Third_Generation(char *var_in_file_name, char *input_str){
    printf("#### Walley_Print_Third_Generation ####\n");
    input_str=Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(input_str,var_in_file_name);
    //printf("%s\n",input_str);
    return Walley_Eval_With_Variable_From_File(var_in_file_name,input_str);
}
char *Walley_Println_Third_Generation(char *var_in_file_name, char *input_str){
    printf("#### Walley_Println_Third_Generation ####\n");
    input_str=Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation(input_str,var_in_file_name);
    char *input= Walley_Eval_With_Variable_From_File(var_in_file_name,input_str);
    char *output=malloc(sizeof(char)*(int)strlen(input));
    strcat(output,input);
    strcat(output,"\n");
    return output;
}