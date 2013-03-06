/* 
 * File:   walley.h
 * Author: shd101wyy
 *
 * Created on September 6, 2012, 12:01 AM
 */
#include "walley_parser.h"
/*void Walley_Run(char *input_str){
   //// printf("#### Walley Run ####\n");
    char *file_name = "__walley__.wy";
    char *setting_file = "__walley_settings__.wy";
    char *temp_file_name="__walley_file__.wy";
    char *existing_file="None";
    //Walley_Run_Four_Generation(file_name,setting_file,temp_file_name,existing_file,input_str);
    Walley_Run_For_Appointed_File(file_name,setting_file,temp_file_name,existing_file,input_str);
    
}*/
void Walley_Run(char *input_str){
    char *existing_file="None";
    Walley_Run_For_Appointed_Var(&VAR_var,&VAR_settings,&TEMP_FILE,existing_file,&FUNCTION,input_str);
}

void Walley_Parse(char *input_str){
    char *existing_file="None";
    Walley_Parse_Simple_String(&VAR_var,&VAR_settings,existing_file,&FUNCTION,input_str);
}

void Walley_Parse_String_List_Default(char **input_str_list){
    char *existing_file="None";
    Walley_Parse_String_List(&VAR_var,&VAR_settings,existing_file,&FUNCTION,input_str_list);
}
/*
void Walley_Agent_Run(char *input_str,char *existing_file){
   //// printf("#### Walley_Agent_Run ####\n");
    //char *brain_path="/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/";
    //char *brain_path=toCString(getValueFromValueName("__walley_path__.wy", "__walley_path__"));
    //char *walley_language_file=append(brain_path, "__walley_language__.wy");
    //char *walley_language_similarity_file=append(brain_path, "__walley_language_similarity__.wy");
    //char *walley_language_verb_file=append(brain_path, "__walley_language_verb__.wy");
    //char *existing_file="None";
    
    //Walley_Agent_Respond(walley_language_file,walley_language_similarity_file,walley_language_verb_file,VAR_var,VAR_settings,TEMP_FILE,existing_file,input_str);
    
    Walley_Agent_Respond(WALLEY_LANGUAGE_FILE,WALLEY_SIMILARITY_FILE,WALLEY_VERB_FILE,VAR_var,VAR_settings,TEMP_FILE,existing_file,input_str);

}*/
void Walley_Run_File(char *file_name){
   // printf("#### Walley_Run_File ####\n");
        
    file_name=removeBackSpace(file_name);
    
    if (strcmp(".wyc",substr(file_name,(int)strlen(file_name)-4,(int)strlen(file_name)))==0) {
        char *string_in_file=changeBinaryToText(getStringFromFile(file_name));
        FILE *temp_file=fopen("WALLEY_TEMP_TEMP_FILE.wy", "w");
        fputs(string_in_file, temp_file);
        fclose(temp_file);
        Walley_Run_File("WALLEY_TEMP_TEMP_FILE.wy");
        remove("WALLEY_TEMP_TEMP_FILE.wy");
    }
    // .wy format file
    else {
    
    if(strcmp("wy",substr(file_name,(int)strlen(file_name)-2,(int)strlen(file_name)))!=0){
        printf("File format wrong\n");
        exit(1);
    }
    /*
    char *str_in_wy = getStringFromFile(file_name);

    FILE *fp = fopen(file_name, "w");
    if(fp==NULL){
        printf("Failed to initialize");
        exit(1);
    }
    char input_message[1000] = "";
    strcat(input_message, "###### Done! ######\n");
    fputs(str_in_wy, fp);
    fputs(input_message, fp);
    fclose(fp);
    **/
    FILE *fp=fopen(file_name,"r");
   // printf("Here\n");
    if(fp==NULL){
        printf("Failed to initialize\n");
        printf("File not found\n");
        exit(1);
    } else {
        
        //Walley_Initialize();

        char arr[10000]="";
        //char output[1000]="";
        /**
        while ((fgets(arr, 1000, fp)) != NULL) {
            //char *temp=substr(arr,0,(int)strlen(arr)-1);
            char *temp=removeBackSpace(arr);
            //if (find(arr,"\n")!=-1){
            if (arr[(int)strlen(arr)-1]=='\n'){
                temp=substr(arr,0,(int)strlen(arr)-1);
                //printf("Find \\n\n");
            }
            //printf("## char is %c \n ##",arr[(int)strlen(arr)-1]);
            printf("## Arr is '%s' ##\n",temp);
            //printf("## Length of arr is %d\n ##",(int)strlen(temp));
            Walley_Run(temp);
        }*/
        while ((fgets(arr, 10000, fp)) != NULL) {
            
            if(stringIsEmpty(removeNFromBack(arr)) || strcmp("",trim(removeNFromBack(arr)))==0 ||(int)strlen(arr)==0)
                continue;
            else{
               // printf("arr----> |%s|\n");
                //strcat(output,arr);
                if((int)strlen(arr)==0)
                    continue;
                /*
                char *temp_str=malloc(sizeof(char)*((int)strlen(arr)+1));
                int a=0;
                for(a=0;a<(int)strlen(arr);a++){
                    temp_str[a]=arr[a];
                }
                temp_str[(int)strlen(temp_str)]=0;
                temp_str=removeBackSpace(temp_str);
                //printf("^^^^^^%c\n",(temp_str[(int)strlen(temp_str)-1]));
                if(temp_str[(int)strlen(temp_str)-1]=='\n')
                    temp_str=substr(temp_str,0,(int)strlen(temp_str)-1);
                        */
                char *temp_str=append("", arr);
                if(temp_str[(int)strlen(temp_str)-1]=='\n')
                    temp_str=substr(temp_str,0,(int)strlen(temp_str)-1);
                
                //Walley_Run(temp_str);
                //if(stringIsEmpty(temp_str)==FALSE)
               // printf("temp_str---->|%s|\n",temp_str);
                //Walley_Run_Third_Generation("__walley__.wy","__walley_settings__.wy","__walley_file__.wy",file_name,temp_str);
                
                
                // new code here on Dec 10
                if (strcmp(file_name, FIRST_RUNNING_FILE)==0) {
                    TURN++;
                }
                
                /*
                //##################################################################
                // for auto clean var
                int turn = atoi(Var_getValueOfVar(VAR_settings , "turn"));
                turn=turn+1;
                Var_changeValueOfVar(VAR_settings , "turn", numToCString(turn), "int");
                //###################################################################*/
                
                Walley_Run_For_Appointed_Var(&VAR_var,&VAR_settings,&TEMP_FILE,file_name,&FUNCTION,temp_str);
            }
        }
        //char *output_output=malloc(sizeof(char)*(int)strlen(output));
        //strcat(output_output,output);
        //printf("output_output is \n--------\n%s\n--------\n",output_output);
        //if(find(output_output,"\n\n")!=-1);
        //output_output=replace(output_output,"\n\n","\n");
        //Walley_Run(output_output);
        //Walley_Finalize();
        //fclose(fp);
        //fp = fopen(file_name, "w");
        //fputs(str_in_wy, fp);
        //fputs(input_message, fp);
        //Walley_Run_For_Appointed_File("__walley__.wy","__walley_settings__.wy","__walley_file__.wy",file_name,"#end");
        Walley_Run_For_Appointed_Var(&VAR_var,&VAR_settings,&TEMP_FILE,file_name,&FUNCTION,"#end");
        Var_changeValueOfVar(&VAR_settings , "turn", "0", "int");
        fclose(fp);
    }
    }
}


void Walley_Parse_File(char *file_name){
    // printf("#### Walley_Run_File ####\n");
    
    file_name=removeBackSpace(file_name);
    
    if (strcmp(".wyc",substr(file_name,(int)strlen(file_name)-4,(int)strlen(file_name)))==0) {
        char *string_in_file=changeBinaryToText(getStringFromFile(file_name));
        FILE *temp_file=fopen("WALLEY_TEMP_TEMP_FILE.wy", "w");
        fputs(string_in_file, temp_file);
        fclose(temp_file);
        Walley_Run_File("WALLEY_TEMP_TEMP_FILE.wy");
        remove("WALLEY_TEMP_TEMP_FILE.wy");
    }
    // .wy format file
    else {
        
        if(strcmp("wy",substr(file_name,(int)strlen(file_name)-2,(int)strlen(file_name)))!=0){
            printf("File format wrong\n");
            exit(1);
        }
        FILE *fp=fopen(file_name,"r");
        if(fp==NULL){
            printf("Failed to initialize\n");
            printf("File not found\n");
            exit(1);
        } else {
            
            //Walley_Initialize();
            
            char arr[10000]="";
            while ((fgets(arr, 10000, fp)) != NULL) {
                
                if(stringIsEmpty(removeNFromBack(arr)) || strcmp("",trim(removeNFromBack(arr)))==0 ||(int)strlen(arr)==0)
                    continue;
                else{
                    // printf("arr----> |%s|\n");
                    //strcat(output,arr);
                    if((int)strlen(arr)==0)
                        continue;
                    char *temp_str=append("", arr);
                    if(temp_str[(int)strlen(temp_str)-1]=='\n')
                        temp_str=substr(temp_str,0,(int)strlen(temp_str)-1);
                    
                    if (strcmp(file_name, FIRST_RUNNING_FILE)==0) {
                        TURN++;
                    }
                    
                
                    Walley_Parse_Simple_String(&VAR_var, &VAR_settings, file_name, &FUNCTION, temp_str);
                    //Walley_Run_For_Appointed_Var(&VAR_var,&VAR_settings,&TEMP_FILE,file_name,&FUNCTION,temp_str);
                }
            }
            
            Walley_Parse_Simple_String(&VAR_var, &VAR_settings, file_name, &FUNCTION, "#end");
            //Var_changeValueOfVar(&VAR_settings , "turn", "0", "int");
            fclose(fp);
        }
    }
}

/*
void Walley_Agent_Run_File(char *file_name) {

    file_name = removeBackSpace(file_name);
    if (strcmp("wy", substr(file_name, (int) strlen(file_name) - 2, (int) strlen(file_name))) == 0) {
       //// printf("#### Walley_Run_File ####\n");
        Walley_Run_File(file_name);
    }
    else if (strcmp("wi", substr(file_name, (int) strlen(file_name) - 2, (int) strlen(file_name))) != 0) {
        printf("File format wrong\n");
        exit(1);
    } else {
       //// printf("#### Walley_Agent_Run_File ####\n");
        FILE *fp = fopen(file_name, "r");
        if (fp == NULL) {
            printf("Failed to initialize\n");
            printf("File %s not found\n", file_name);
            exit(1);
        } else {
            //Walley_Initialize();
            //char ch;
            char arr[1001] = "";
            char output[1000] = "";*/
            /**
            while ((fgets(arr, 1000, fp)) != NULL) {
                //char *temp=substr(arr,0,(int)strlen(arr)-1);
                char *temp=removeBackSpace(arr);
                //if (find(arr,"\n")!=-1){
                if (arr[(int)strlen(arr)-1]=='\n'){
                    temp=substr(arr,0,(int)strlen(arr)-1);
                    //printf("Find \\n\n");
                }
                //printf("## char is %c \n ##",arr[(int)strlen(arr)-1]);
                printf("## Arr is '%s' ##\n",temp);
                //printf("## Length of arr is %d\n ##",(int)strlen(temp));
                Walley_Run(temp);
            }*//*
            while ((fgets(arr, 1000, fp)) != NULL) {
                if (stringIsEmpty(arr) || strcmp("", removeAheadSpace(removeBackSpace(arr))) == 0 || (int) strlen(arr) == 0)
                    continue;
                else {
                    strcat(output, arr);
                    if ((int) strlen(arr) == 0)
                        continue;
                    //char *temp_str = malloc(sizeof (char) *(int) strlen(arr));
                    //int a = 0;
                    //for (a = 0; a < (int) strlen(arr); a++) {
                    //    temp_str[a] = arr[a];
                    //}
                    //temp_str = removeBackSpace(temp_str);
                    
                    char *temp_str=append("", arr);
                    temp_str=removeBackSpace(temp_str);
                    temp_str=removeNFromBack(temp_str);
                    //printf("^^^^^^%c\n",(temp_str[(int)strlen(temp_str)-1]));
                    //if (temp_str[(int) strlen(temp_str) - 1] == '\n')
                    //    temp_str = substr(temp_str, 0, (int) strlen(temp_str) - 1);


                    //Walley_Run(temp_str);
                    //if(stringIsEmpty(temp_str)==FALSE)
                   // printf("---->|%s|\n",temp_str);
                    //Walley_Run_Third_Generation("__walley__.wy","__walley_settings__.wy","__walley_file__.wy",file_name,temp_str);
                    //Walley_Run_For_Appointed_File("__walley__.wy","__walley_settings__.wy","__walley_file__.wy",file_name,temp_str);
                    Walley_Agent_Run(temp_str,file_name);
                }
            }
            //char *output_output=malloc(sizeof(char)*(int)strlen(output));
            //strcat(output_output,output);
            //printf("output_output is \n--------\n%s\n--------\n",output_output);
            //if(find(output_output,"\n\n")!=-1);
            //output_output=replace(output_output,"\n\n","\n");
            //Walley_Run(output_output);
            //Walley_Finalize();
            //fclose(fp);
            //fp = fopen(file_name, "w");
            //fputs(str_in_wy, fp);
            //fputs(input_message, fp);
            Walley_Run_For_Appointed_Var(VAR_var, VAR_settings, TEMP_FILE, file_name, FUNCTION,"#end");
            fclose(fp);
        }
    }
}
*/
/*
void Walley_Agent_Recall(char *file_name) {
   //// printf("#### Walley_Agent_Recall ####\n");
    //char *brain_path="/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/";
    //char *brain_path=toCString(getValueFromValueName("__walley_path__.wy", "__walley_path__"));
    //char *walley_language_file=append(brain_path, "__walley_language__.wy");
    //char *walley_language_similarity_file=append(brain_path, "__walley_language_similarity__.wy");
    //char *walley_language_verb_file=append(brain_path, "__walley_language_verb__.wy");

    file_name = removeBackSpace(file_name);
    if (strcmp("wy", substr(file_name, (int) strlen(file_name) - 2, (int) strlen(file_name))) == 0 || strcmp("wi", substr(file_name, (int) strlen(file_name) - 2, (int) strlen(file_name))) == 0) {
       //// printf("#### Walley_Agent_Run_File ####\n");
        FILE *fp = fopen(file_name, "r");
        if (fp == NULL) {
            printf("Failed to initialize\n");
            printf("File %s not found\n", file_name);
            exit(1);
        } else {

            //Walley_Initialize();
            char arr[1001] = "";
            char output[1000] = "";

            int count = 1;
            while ((fgets(arr, 1000, fp)) != NULL) {
                if (stringIsEmpty(arr) || strcmp("", removeAheadSpace(removeBackSpace(arr))) == 0 || (int) strlen(arr) == 0)
                    continue;
                else {
                    strcat(output, arr);
                    if ((int) strlen(arr) == 0)
                        continue;
                    char *temp_str = malloc(sizeof (char) *(int) strlen(arr));
                    int a = 0;
                    for (a = 0; a < (int) strlen(arr); a++) {
                        temp_str[a] = arr[a];
                    }
                    temp_str = removeBackSpace(temp_str);
                    //printf("^^^^^^%c\n",(temp_str[(int)strlen(temp_str)-1]));
                    if (temp_str[(int) strlen(temp_str) - 1] == '\n')
                        temp_str = substr(temp_str, 0, (int) strlen(temp_str) - 1);

                    printf("\n# %d ############################\n", count);
                    printf("Now input is       ----> |%s|\n", temp_str);
                    char *format_string = Walley_Analyze_Sentence_Automatically(VAR_var,WALLEY_SIMILARITY_FILE,WALLEY_VERB_FILE, temp_str);
                    printf("Format String is   ----> |%s|\n", format_string);
                    printf("Translate to string----> |%s|\n", Walley_Translate(WALLEY_LANGUAGE_FILE, WALLEY_SIMILARITY_FILE,WALLEY_VERB_FILE,VAR_var,temp_str));
                    printf("Think---------------------|\n");
                    printf("Output--------------------|\n");
                    Walley_Agent_Run(temp_str,file_name);
                    printf("Finish Thinking---------------------|\n");
                    printf("###################################################\n");
                    printf("###################################################\n\n\n");

                    count += 1;
                }
            }
            Walley_Run_For_Appointed_Var(VAR_var, VAR_settings, TEMP_FILE, file_name,FUNCTION, "#end");
            fclose(fp);
            while (TRUE) {
                printf("Which Sentence do you think that has a problem?\n");
                printf("Enter sentence number.. enter 0 to exit\n");
                printf("Enter sentence number------>");
                int sentence_number = 0;
                scanf("%d", &sentence_number);
                if (sentence_number == 0) {
                    printf("\n\n#################################################\n\n");
                    printf("Exit\n");
                    exit(1);
                } else {
                    printf("\nSentence # %d made mistake!\n", sentence_number);
                    count = 1;
                    char *input_to_run = "";
                    char *format_string = "";
                    char *translate_to = "";
                    fp = fopen(file_name, "r");
                    char arr2[1001] = "";
                    while ((fgets(arr2, 1000, fp)) != NULL) {
                        if (stringIsEmpty(arr2) || strcmp("", removeAheadSpace(removeBackSpace(arr2))) == 0 || (int) strlen(arr2) == 0)
                            continue;
                        else {
                            if (count == sentence_number) {
                                strcat(output, arr2);
                                if ((int) strlen(arr2) == 0)
                                    continue;
                                char *temp_str = malloc(sizeof (char) *(int) strlen(arr2));
                                int a = 0;
                                for (a = 0; a < (int) strlen(arr2); a++) {
                                    temp_str[a] = arr2[a];
                                }
                                temp_str = removeBackSpace(temp_str);
                                //printf("^^^^^^%c\n",(temp_str[(int)strlen(temp_str)-1]));
                                if (temp_str[(int) strlen(temp_str) - 1] == '\n')
                                    temp_str = substr(temp_str, 0, (int) strlen(temp_str) - 1);
                                input_to_run = temp_str;
                                format_string = Walley_Analyze_Sentence_Automatically(VAR_var, WALLEY_SIMILARITY_FILE,WALLEY_VERB_FILE,input_to_run);
                                translate_to = Walley_Translate(WALLEY_LANGUAGE_FILE,WALLEY_SIMILARITY_FILE,WALLEY_VERB_FILE, VAR_var,input_to_run);
                                
                                printf("###################################################\n");
                                printf("###################################################\n");
                                printf("Now input is        ----> |%s|\n", input_to_run);
                                printf("Format String is    ----> |%s|\n", format_string);
                                printf("Translate to string ----> |%s|\n", translate_to);
                                printf("Think---------------------|\n");
                                printf("Output--------------------|\n");
                                Walley_Agent_Run(input_to_run,file_name);
                                printf("Finish Thinking---------------------|\n");
                                printf("###################################################\n");
                                printf("###################################################\n\n\n");

                                
                                break;
                            } else {
                                strcat(output, arr);
                                if ((int) strlen(arr) == 0)
                                    continue;
                                char *temp_str = malloc(sizeof (char) *(int) strlen(arr));
                                int a = 0;
                                for (a = 0; a < (int) strlen(arr); a++) {
                                    temp_str[a] = arr[a];
                                }
                                temp_str = removeBackSpace(temp_str);
                                //printf("^^^^^^%c\n",(temp_str[(int)strlen(temp_str)-1]));
                                if (temp_str[(int) strlen(temp_str) - 1] == '\n')
                                    temp_str = substr(temp_str, 0, (int) strlen(temp_str) - 1);


                                //Walley_Run(temp_str);
                                //if(stringIsEmpty(temp_str)==FALSE)
                                //printf("---->|%s|\n",temp_str);
                                //Walley_Run_Third_Generation("__walley__.wy","__walley_settings__.wy","__walley_file__.wy",file_name,temp_str);
                                //Walley_Run_For_Appointed_File("__walley__.wy","__walley_settings__.wy","__walley_file__.wy",file_name,temp_str);
                                Walley_Agent_Run(temp_str,file_name);
                            }
                            count += 1;
                        }
                    }
                    fclose(fp);
                    while (TRUE) {
                        printf("Which part do you think is wrong??\n");
                        printf("# 0 exit this part\n");
                        printf("# 1 input\n");
                        printf("# 2 format_string\n");
                        printf("# 3 translated string\n");
                        //printf("# 4 output after run\n");
                        int mistake = 0;
                        printf("------>");
                        scanf("%d", &mistake);
                        if (mistake == 0) {
                            break;
                        }
                        if (mistake == 1) {
                            printf("You should check your file and change what you wrote\n");
                            exit(0);
                        }
                        else if (mistake == 2) {
                            printf("It seems that I format string wrongly\n");
                            printf("You could now format string on your own\n");
                            printf("Now I will make a format for your input string\nplease follow the order\n");
                            char *true_format = Walley_Analyze_Sentence_Manually(input_to_run);
                            int num_of_true_format = numOfSmallSentences(true_format);
                            num_of_true_format -= count_str_not_in_string(true_format, "VAR");

                            char temp_str[1000] = "";
                            sprintf(temp_str, "%d", num_of_true_format);

                            char *temp_to_add=append(true_format, "|");
                            temp_to_add=append(temp_to_add, temp_str);
                            temp_to_add=append(temp_to_add, "|");
                            Str_addString(WALLEY_SIMILARITY_FILE, temp_to_add);
                            
                            char *temp_walley_similarity_file_path=append(BRAIN_PATH, "__walley_language_similarity__.wy");
                            writeStringToFile(temp_walley_similarity_file_path,true_format);
                            writeStringToFile(temp_walley_similarity_file_path,"|");
                            writeStringToFile(temp_walley_similarity_file_path,temp_str);
                            writeStringToFile(temp_walley_similarity_file_path,"|\n");
                            cleanWalleyLanguageFile(temp_walley_similarity_file_path);
                            
                            printf("\n\nOkay, I finished modifying the format string\n");
                            printf("to enter 0 to exit modification\n");
                        }
                        else if (mistake == 3){
                            printf("\n\nIs the format_string right? the translated string comes from format_string\n");
                            printf("You could try to change the format_string\n\n");
                            continue;
                        }
                        else {
                            continue;
                        }

                    }
                }
            }
            printf("\n\n#####################################################################################\n");
            printf("Alright! I have recalled all of the things, and now do you want me to run again? Y/N \n");
            char *answer=malloc(sizeof(char)*10);
            gets(answer);
            answer=stringToUpperCase(answer);
            if (strcmp(answer, "Y") == 0 || strcmp(answer, "YES") == 0) {
                printf("Okay begin to run again!");
                Walley_Agent_Run_File(file_name);
                printf("\n\n################## FINISH RUNNING #################################################\n");
                printf("###################################################################################\n");
                printf("Are there still some mistakes?");
                char *answer2=malloc(sizeof(char)*10);
                gets(answer2);
                answer2=stringToUpperCase(answer2);
                if (strcmp(answer2, "Y") == 0 || strcmp(answer2, "YES") == 0) {
                    Walley_Agent_Recall(file_name);
                }
                else{
                    printf("\nGlad to help you!!\nSee you!!\n");
                    exit(0);
                }
            }
            else{
                 printf("\nGlad to help you!!\nSee you!!\n");
                 exit(0);
            }
        }
    }
    else {
        printf("File format wrong\nFile name : %s\n",file_name);
        exit(1);
    }
}*/