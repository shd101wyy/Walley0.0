/* 
 * File:   walley.h
 * Author: shd101wyy
 *
 * Created on August 17, 2012, 2:41 PM
 */
//#include "walley_function.h"
#include "walley_class.h"



void Walley_Initialize_Settings_File(char *settings_file_name){
    FILE *fp=fopen(settings_file_name,"w");
    if(fp==NULL){
        printf("Failed to initialize settings");
    } else {
        fputs("#~\n",fp);
        fputs("space:0:int:\n",fp);
        fputs("current_space:0:int:\n",fp);
        fputs("now_writting_function:0:int:\n",fp);
        fputs("now_writting_class:0:int:\n",fp);
        fputs("now_writting_while:0:int:\n",fp);
        fputs("now_writting_for:0:int:\n",fp);
        fputs("now_run_if:0:int:\n",fp);
        fputs("last_if_sentence:\"None\":string:\n",fp);
        fputs("last_while_sentence:\"None\":string:\n",fp);
        fputs("temp_i:\"None\":string:\n",fp); // for i in x------>i
        fputs("temp_i_in_for_sentence:\"None\":string:\n",fp); // for i in x-------> value of x
        fputs("string_in_while_loop:\"#While\\n\":string:\n",fp);
        fputs("string_in_for_loop:\"#For\\n\":string:\n",fp);
        fputs("while_finish:1:int:\n",fp);
        fputs("space_of_first_if_sentence:0:int:\n",fp);
        fputs("space_of_first_while_sentence:0:int:\n",fp);
        fputs("space_of_first_for_sentence:0:int:\n",fp);
        fputs("space_of_first_def_sentence:0:int:\n",fp);
        fputs("space_of_first_class_sentence:0:int:\n",fp);
        fputs("now_in_annotation:0:int:\n",fp);
        
        //fputs("now_brain_path:\"\":string:\n",fp);
        
        fputs("~#\n",fp);
        fclose(fp);
    }
}

void Walley_Initialize_Var_File(char *file_var_name){
    FILE *fp=fopen(file_var_name,"w");
    if(fp==NULL){
        printf("Failed to initialize var");
    } else {
        fputs("#~\n",fp);
        
        // While Sentence //
        fputs("__temp_while__:[]:list:\n",fp);
        fputs("#~Begin:__temp_while__:\n",fp);
        fputs("__temp_while__[0]:None:expression:\n",fp);
        fputs("#~End:__temp_while__:\n",fp);
        fputs("\n",fp);
        
        //Space before While Sentence //
        fputs("__temp_while_space__:[]:list:\n",fp);
        fputs("#~Begin:__temp_while_space__:\n",fp);
        fputs("__temp_while_space__[0]:None:expression:\n",fp);
        fputs("#~End:__temp_while_space__:\n",fp);
        fputs("\n",fp);
        
        // String in While Loop //
        fputs("__temp_string_in_while_loop__:[]:list:\n",fp);
        fputs("#~Begin:__temp_string_in_while_loop__:\n",fp);
        fputs("__temp_string_in_while_loop__[0]:None:expression:\n",fp);
        fputs("#~End:__temp_string_in_while_loop__:\n",fp);
        fputs("\n",fp);
        
        // If Sentence //
        fputs("__temp_if__:[]:list:\n",fp);
        fputs("#~Begin:__temp_if__:\n",fp);
        fputs("__temp_if__[0]:None:expression:\n",fp);
        fputs("#~End:__temp_if__:\n",fp);
        fputs("\n",fp);
        
        //space before is sentence//
        fputs("__temp_if_space__:[]:list:\n",fp);
        fputs("#~Begin:__temp_if_space__:\n",fp);
        fputs("__temp_if_space__[0]:None:expression:\n",fp);
        fputs("#~End:__temp_if_space__:\n",fp);
        fputs("\n",fp);      
        
        // has run if ....
        // if __has_run_if__ in if sentence is true, then elif and else will not run
        // if __has_run_if__ in elif sentence is true, then elif and else behind will not run
        fputs("__has_run_if__:[]:list:\n",fp);
        fputs("#~Begin:__has_run_if__:\n",fp);
        fputs("__has_run_if__[0]:None:expression:\n",fp);
        fputs("#~End:__has_run_if__:\n",fp);
        fputs("\n",fp); 
 
        // For Sentence //                         
        /*
         * for i in x:
         * x is the for sentence
         * x is __temp_for__
         */
        fputs("__temp_for__:[]:list:\n",fp);
        fputs("#~Begin:__temp_for__:\n",fp);
        fputs("__temp_for__[0]:None:expression:\n",fp);
        fputs("#~End:__temp_for__:\n",fp);
        fputs("\n",fp);
        
        // For I ??
        /*
         * for i in x:
         * i is the For I
         * i is __temp_i__
         */
        fputs("__temp_i__:[]:list:\n",fp);
        fputs("#~Begin:__temp_i__:\n",fp);
        fputs("__temp_i__[0]:None:expression:\n",fp);
        fputs("#~End:__temp_i__:\n",fp);
        fputs("\n",fp);
        
        // String in For Loop //
        fputs("__temp_string_in_for_loop__:[]:list:\n",fp);
        fputs("#~Begin:__temp_string_in_for_loop__:\n",fp);
        fputs("__temp_string_in_for_loop__[0]:None:expression:\n",fp);
        fputs("#~End:__temp_string_in_for_loop__:\n",fp);
        fputs("\n",fp);
        
        
        fputs("__temp_class__:{}:dictionary:\n",fp);
        fputs("#~Begin:__temp_class__:\n",fp);
        fputs("#~End:__temp_class__:\n",fp);
        fputs("\n",fp);
        
        fputs("__temp_class_name_now_writting__:'None':string:\n",fp);
        fputs("\n",fp);
        
        fputs("__string_in_temp_class__:{}:dictionary:\n",fp);
        fputs("#~Begin:__string_in_temp_class__:\n",fp);
        fputs("#~End:__string_in_temp_class__:\n",fp);
        fputs("\n",fp);
        
        fputs("__instance_name__:[]:list:\n",fp);
        fputs("#~Begin:__instance_name__:\n",fp);
        fputs("__instance_name__[0]:None:expression:\n",fp);
        fputs("#~End:__instance_name__:\n",fp);
        fputs("\n",fp);
        
        //eg x.age=16, save x.age=16 to __walley__.wy
        fputs("__instance_var__:[]:list:\n",fp);
        fputs("#~Begin:__instance_var__:\n",fp);
        fputs("__instance_var__[0]:None:expression:\n",fp);
        fputs("#~End:__instance_var__:\n",fp);
        fputs("\n",fp);
        
        fclose(fp);
    }   
}

void Walley_Run_For_Appointed_File(char* file_name,char *setting_file,char* temp_file_name,char* input_str) {
    
   //// printf("############ Run Function Walley_Run_For_Appointed_File ##############\n");
    
        bool now_in_annotation = atoi(getValueFromValueName(setting_file, "now_in_annotation"));
    char *judge_annotation_string=trim(input_str);
    int length_of_judge_annotation_string=(int)strlen(judge_annotation_string);
    if (judge_annotation_string[length_of_judge_annotation_string-1]=='#' && judge_annotation_string[length_of_judge_annotation_string-2]=='~'){
       //// printf("Now End Long Annotation");
        now_in_annotation = 0;
        char temp4[100];
        sprintf(temp4, "%d", now_in_annotation);
        changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_in_annotation", (char*) temp4, "int");
    }
    else if (judge_annotation_string[0] == '#' && judge_annotation_string[1] == '~') {
       //// printf("Now Begin Long Annotation");
        now_in_annotation = 1;
        char temp4[100];
        sprintf(temp4, "%d", now_in_annotation);
        changeTheVarValueFromItsInitialOneFromFile(setting_file, "now_in_annotation", (char*) temp4, "int");
    }
    
    if(now_in_annotation==0){
    bool do_not_run=FALSE;
    if((int)strlen(removeAheadSpace(removeBackSpace(input_str)))==0)
        do_not_run=TRUE;
    if(do_not_run==FALSE){
        
    bool continue_run=FALSE;
    char *temp_input_str=input_str;
    bool find_gang_gang=FALSE;
    if(find(input_str,"\n")!=-1){
        continue_run=TRUE;
        input_str=substr(input_str,0,find(input_str,"\n"));
        //Walley_Run_For_Appointed_File(file_name,setting_file,substr(temp_input_str,find(temp_input_str,"\n")+1,(int)strlen(temp_input_str)));
    }
    if (find(input_str, "\\n") != -1) {
        continue_run = TRUE;
        find_gang_gang=TRUE;
        input_str = substr(input_str, 0, find(input_str, "\\n"));
        //Walley_Run_For_Appointed_File(file_name,setting_file,substr(temp_input_str,find(temp_input_str,"\n")+1,(int)strlen(temp_input_str)));
    }
    //if(input_str[(int)strlen(input_str)-1]=='\n')
    //    input_str=substr(input_str,0,(int)strlen(input_str)-1);
    
    writeStringToFile("__walley_file__.wy",input_str);
    writeStringToFile("__walley_file__.wy","\n");
    
    //###### Initialize Space ######

    int space=atoi(getValueFromValueName(setting_file,"space"));
    bool now_writting_function=atoi(getValueFromValueName(setting_file,"now_writting_function"));
    bool now_writting_class=atoi(getValueFromValueName(setting_file,"now_writting_class"));
    bool now_run_if=atoi(getValueFromValueName(setting_file,"now_run_if"));
    char *last_if_sentence=getValueFromValueName(setting_file,"last_if_sentence");
    
    int current_space=numOfSpaceAheadString(input_str);
   //// printf("-------Now input is |%s|\n",input_str);
    //printf("-------Now input length is %d\n",(int)strlen(input_str));
    //printf("-------Now Ahead Space is %d\n",current_space);
    //printf("-------Now writting in function is %d\n",now_writting_function);
    
    if(current_space==0){
        //printf("------Ahead Space is 0");
        if(now_writting_function==TRUE){
            writeStringToFile("__walley_function__.wy","#~End\n\n");
            cleanFunctionFile("__walley_function__.wy");
        }
        now_writting_function=FALSE;
        now_writting_class=FALSE;
        space=0;
    }
    //printf("-------Now Ahead Space is %d\n",numOfSpaceAheadString(input_str));
    //printf("-------Now writting in function is %d\n",now_writting_function);
    
    FILE *fp=fopen(file_name,"r");
    if(fp==NULL){
        printf("Fail to initialize");
        exit(1);
    } else {
        fclose(fp);
    }

    //############### Now Writting Function In Progress #####################
    if (now_writting_function == TRUE) {
       //// printf("//############### Now Writting Function In Progress #####################\n");
        //printf("//############### %s #############\n",input_str);
        //printf("Input_Str is :%s\n",input_str);
        //printf("3---------------\n%s---------------\n",getStringFromFile("__walley_function__.wy"));
        //int current_space=numOfSpaceAheadString(input_str);

        //if(strcmp("",removeBackSpace(removeAheadSpace(input_str)))==0){
        //        space=space-4;
        //        if(space==0){
        //            now_writting_function=FALSE;
        //            writeStringToFile("__walley_function__.wy","#~End\n\n");
        //        }
        //} else {
        if(current_space>space && current_space%4!=0){
        //if (current_space != space) {
            printf("Space Mistake\nCurrent Space is %d\nRequired Space is %d\n", current_space, space);
            exit(0);
        } else {
            space=current_space;
            input_str=removeAheadSpace(input_str);
            char *temp = malloc(sizeof (char) *(int) strlen(input_str) + sizeof (char) *(1+space-4));
            int a=0;
            if(space-4!=0){
            for(a=0;a<(space-4);a++){
                strcat(temp, " ");
                //printf("Enter Xun huan\n");
            }
            }
            strcat(temp, input_str);
            strcat(temp, "\n");
            //temp = removeAheadSpace(temp);
            //printf("//############### Space-4 is %d Temp is :%s\n",space-4,temp);
            //printf("The string write file is :%s\n", temp);
            writeStringToFile("__walley_function__.wy", temp);
            //free(temp);
        }
        
        if (find_from_index_to_index(removeAheadSpace(input_str), "def ", 0, 5) != -1) {
            //printf("Find another function while defining a function\n");
            space = space + 4;
        }
        //}
        


    }
    //################### Now Writting Class ##############################
    else if (now_writting_class==TRUE){
        printf("now_writting_class \n");
        
    }
            
    //#####################  Anotation  ###################    
    else if (removeAheadSpace(input_str)[0]=='#'){
        printf("This is one anatation %s\n",removeAheadSpace(input_str));
    }
    
        // ##############  Function  ##############################
    else if (find(removeAheadSpace(input_str),"def ")==0){
        //printf("\n###### begin to define a function######\n");
        space=space+4;
        //printf("Now Space is %d\n",space);
        
        now_writting_function=TRUE;
        //char *output=defineAFunction(input_str);
        //printf("100---------------\n%s---------------\n",getStringFromFile("__walley_settings__.wy"));
        char *func_name=functionName(input_str);
        char *func_param_str=functionParameterStr(input_str);
        bool has_same_function_name=checkWhetherSameFunctionNameExists(func_name);
        if(has_same_function_name){
            //printf("Has Same Function Name\n");
            changeFunctionFromItsInitialOne(func_name,func_param_str);
            
        } else {
            //printf("Does Not Have Same Function Name\n");
            writeFunctionIntoFile(func_name,func_param_str);
            writeStringToFile("__walley_function__.wy","#~Begin\n");
            //writeStringToFIle("__walley_function__.wy","Begin\n");
            
            if(strcmp(func_param_str,"None")==0){
                //printf("This Function has no Parameter\n");
            } else {
                writeFunctionParameterOneByOneToFile(func_param_str);
                writeStringToFile("__walley_function__.wy","##Finish Init Params\n");
                //writeStringToFile("__walley_function__.wy","#Finish initialize parameters\n");
            }
        }
    }
    //#################### Basic Input To Run #############################
    else {
        //printf("\n\n######### Basic Input To Run #########\n");
    
    
    //#####################  println  ###################
    if (find(input_str, "println") != -1) {
        char* output = println_from_var_file(file_name,strInBrackets(input_str));
        printf("%s", output);
    }
    //#####################  print  ###################
    else if (find(input_str, "print") != -1) {
        char* output = print_from_var_file(file_name,strInBrackets(input_str));
        printf("%s", output);
    }
    //#####################  Eval  ###################
    else if (isExpression(input_str)){
        char *var_name=variableName(input_str);
        char *var_value=variableValue(input_str);
        char *var_value_type=variableValueType(var_value);
        //printf("#### The Variable Name is :%s\n",var_name);
        //printf("#### The Variable Value is :%s\n",var_value);
        //printf("#### The Variable Value Type is :%s\n",var_value_type);
        //printf("The Variable Value after put known Variable in is :%s\n",putKnownVariableIntoExpression(var_value));
        
        
        // ################### Basic Calculation ##################################
        if(strcmp(var_value_type,"unknown type")!=0&&strcmp(var_value_type,"function")!=0){
            bool has_same_value_name=checkWhetherSameVarNameExistsFromFile(file_name,var_name);

            if(has_same_value_name==TRUE){
                //var_value=countFromExpression(var_value);
                var_value=Walley_Eval_With_Variable_From_File(file_name,var_value);
                var_value_type=variableValueType(var_value);
                changeTheVarValueFromItsInitialOneFromFile(file_name,var_name,var_value,var_value_type);   
            } else {
                //printf("enter here\n");
                //var_value=countFromExpression(var_value);
                var_value=Walley_Eval_With_Variable_From_File(file_name,var_value);
                var_value_type=variableValueType(var_value);
                writeVarNameAndVarValueIntoAppointedFile(file_name,var_name,var_value,var_value_type);
            }
        } 
        
        //############### Run Function ############################
        else if ((strcmp(var_value_type,"function")!=0)){
          printf("This is Function\n");
        }
        
        //############## Unknown ###############################
        else {
            printf("Unknown Type\n");
        }
        
    }  
    // ##############  Is Not Expression ######################
    
        
    

        
        
    //#####################  Delete Space  ###################
    //} else if(strcmp("",removeBackSpace(removeAheadSpace(input_str)))==0){
    //    printf("Empty Input");
        //space=space-4;
        
    //#####################  Mistake  ###################
            else {
                if (strcmp(input_str, "None") != 0) {
                   //// printf("Not None\n");
                    Walley_Eval_With_Variable_From_File(file_name, input_str);
                   //// printf("Mistake May occurred which calling function Walley_Run_For_Appointed_File;\nThis Language is under development");
                }
            }
            //printf("\nRequired space num is %d\n",space);
        }  
    
        //#################### Set Settigns ################################
        char temp2[100];
        sprintf(temp2,"%d",space);
        changeTheVarValueFromItsInitialOneFromFile(setting_file,"space",(char*)temp2,"int");
        sprintf(temp2,"%d",now_writting_function);
        changeTheVarValueFromItsInitialOneFromFile(setting_file,"now_writting_function",(char*)temp2,"int");
        sprintf(temp2,"%d",now_writting_class);
        changeTheVarValueFromItsInitialOneFromFile(setting_file,"now_writting_class",(char*)temp2,"int");
        sprintf(temp2,"%d",now_run_if);
        changeTheVarValueFromItsInitialOneFromFile(setting_file,"now_run_if",(char*)temp2,"int");
        changeTheVarValueFromItsInitialOneFromFile(setting_file,"last_if_sentence",last_if_sentence,"string");
                
        if(continue_run==TRUE ){
            //printf("continue run\n");
           //// printf("temp input str is |%s|\n",temp_input_str);
           //// printf("removeAheadSpace(input_str) is |%s|\n",removeAheadSpace(input_str));
            if(find_gang_gang==TRUE){
               //// printf("find \\\n");
                Walley_Run_For_Appointed_File(file_name,setting_file,temp_file_name,substr(temp_input_str,find(temp_input_str,"\\n")+2,(int)strlen(temp_input_str)));

            } else {
               //// printf("did not find \\\n");
                Walley_Run_For_Appointed_File(file_name,setting_file,temp_file_name,substr(temp_input_str,find(temp_input_str,"\n")+1,(int)strlen(temp_input_str)));
            }
        }
    }
    }
}

void Walley_Run_For_Default(char* input_str) {
   //// printf("#### Walley_Run_For_Default ####\n");
    Walley_Run_For_Appointed_File("__walley__.wy","__walley_settings__.wy","__walley_file__.wy",input_str);
   }

void Walley_Initialize(){
    FILE *fp;
    
    Walley_Initialize_Var_File("__walley__.wy");
    
    fp=fopen("__walley_function__.wy","w");
    if(fp==NULL){
        printf("Failed to initialize function");
    } else {
        fputs("#~\n",fp);
        fclose(fp);
    }
    
    /*
    fp=fopen("__walley_settings__.wy","w");
    if(fp==NULL){
        printf("Failed to initialize settings");
    } else {
        fputs("#~\n",fp);
        fputs("space:0:int\n",fp);
        fputs("now_writting_function:0:int\n",fp);
        fputs("now_writting_class:0:int\n",fp);
        fputs("now_run_if:0:int\n",fp);
        fputs("last_if_sentence:\"None\":string\n",fp);
        fclose(fp);
    }**/
    Walley_Initialize_Settings_File("__walley_settings__.wy");
    
    fp=fopen("__walley_file__.wy","w");
    if(fp==NULL){
        printf("Failed to initialize file");
    } else {
        fputs("#Temp File In Order To Run goto\n",fp);
        fclose(fp);
    }
   //// printf("###### Walley Initailize! ######\n###### Version 1.0 ######\n");
    int int_size = sizeof (int);
    int double_size = sizeof (double);
    int char_size = sizeof (char);
    //// printf("int size :%d\n", int_size);
    //// printf("double size :%d\n", double_size);
    //// printf("char size :%d\n\n", char_size);
    ////char cwd[1000];
    ////getcwd(cwd, sizeof (cwd));
    ////printf("Current Working Directory%s\n\n\n\n",cwd);
}

void Walley_Finalize(){
    if(remove("__walley__.wy")){
        printf("Can not finalize\n");
        exit(0);
    }
    ////else
    ////    printf("\n\n###### Finalize ######");
    
    if(remove("__walley_function__.wy")){
        printf("Can not finalize Function\n");
        exit(1);
    }
    ////else
    ////    printf("\n\n###### Finalize Function ######");
    
    if(remove("__walley_settings__.wy")){
        printf("Can not finalize Settings\n");
        exit(2);
    }
    ////else
    ////    printf("\n\n###### Finalize Settings ######");
    
    if(remove("__walley_file__.wy")){
       printf("Can not finalize File\n");
        exit(3);
    }
    ////else
    ////    printf("\n\n##### Finalize File #####");
    //Walley_Initialize();
    ////printf("\n############################################################################\n\n");
    ////printf("\nDone!\n");
    
}


char *Walley_Run_One_Function(char *input_str){
    /*
    FILE *fp;
    fp=fopen("__walley_temp__.wy","w");
    if(fp==NULL){
        printf("Failed to initialize temp function");
    } else {
        fputs("",fp);
        fclose(fp);
    }
    
    fp=fopen("__walley_settings_temp__.wy","w");
    if(fp==NULL){
        printf("Failed to initialize temp settings");
    } else {
        fputs("space:0:int\n",fp);
        fputs("now_writting_function:0:int\n",fp);
        fputs("now_writting_class:0:int\n",fp);
        fclose(fp);
    }**/
    
    
    
   //// printf("#### Walley_Run_One_Function ####\n");
    input_str=removeBackSpace(input_str);
    input_str=removeAheadSpace(input_str);
    char *temp=malloc(sizeof(char)*(int)strlen(input_str)+sizeof(char)*1);
    temp=substr(input_str, 0, find(input_str,")"));
    strcat(temp,"  ):");
    input_str=temp;
    
    //char *func_name=substr(input_str, find(input_str,"def")+3,find(input_str,"("));
    char *func_name=substr(input_str,0,find(input_str,"("));
    func_name=removeAheadSpace(func_name);
    func_name=removeBackSpace(func_name);    

    char *parameter_str=substr(input_str, find(input_str,"(")+1,find(input_str,")"));
    //printf("#### parameter_str is %s ####\n",parameter_str);
    parameter_str=removeAheadSpace(parameter_str);
    //printf("#### parameter_str is %s ####\n",parameter_str);
    parameter_str=removeBackSpace(parameter_str);
    //printf("###### Parameter is : %s ######\n",parameter_str);
    
    
    int para_num=count_str(parameter_str,",")+1;
    
    if(stringIsEmpty(parameter_str)){
        para_num=0;
        parameter_str="None";
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
    file_var_temp_name[(int)strlen(file_var_temp_name)]=0;
    //fp=fopen("__walley_temp__.wy","w");
    Walley_Initialize_Var_File(file_var_temp_name);
   //// printf("==== file_var_temp_name %s\n",file_var_temp_name);
    
    char *file_settings_temp_name=malloc(sizeof(char)*((int)strlen("__walley_settings_temp___.wy")+(int)strlen(func_name)));
    strcat(file_settings_temp_name,"__walley_settings_temp_");
    strcat(file_settings_temp_name,func_name_temp);
    strcat(file_settings_temp_name,"__.wy");
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
   //// printf("==== file_settings_temp_name %s\n",file_settings_temp_name);
    
    char *file_file_temp_name=malloc(sizeof(char)*((int)strlen(func_name)+(int)strlen("__walley_file_temp___.wy")));
    strcat(file_file_temp_name,"__walley_file_temp_");
    strcat(file_file_temp_name,func_name_temp);
    strcat(file_file_temp_name,"__.wy");
    //fp=fopen("__walley_settings_temp__.wy","w");
    fp=fopen(file_file_temp_name,"w");
    if(fp==NULL){
        printf("Failed to initialize file");
    } else {
        fputs("#Temp File In Order To Run goto\n",fp);
        fclose(fp);
    }  
   //// printf("file_file_temp_name %s\n",file_file_temp_name);
    
    
    bool find_function=FALSE;
    bool begin=FALSE;
    bool finish=FALSE;
    bool finish_init_param=FALSE;
    
    char *temp_temp=malloc(sizeof(char)*((int)strlen(func_name)+1));
    strcat(temp_temp,func_name);
    strcat(temp_temp,":");


    char *temp2 = malloc(sizeof (char) *(int) strlen(parameter_str) + 1);
    strcat(temp2, parameter_str);
    strcat(temp2, ",");
    parameter_str = temp2;

    int from_index=0;
    int count=0;
    char output[1000]="";
    
    char arr[1000]="";
    fp = fopen("__walley_function__.wy", "r");
    while ((fgets(arr, 1000, fp)) != NULL) {
        //char one_line[1000];
        
        if(find(arr,temp_temp)!=-1){
           //// printf("Find Function\n");
            find_function=TRUE;
        }
        if(find_function==TRUE && find(arr,"#~End\n")!=-1){
           //// printf("Find End\n");
            finish=TRUE;
        }
        
        if(finish==TRUE){
            //printf("Finish\n\n");
            break;
            
        }
        if(finish_init_param==TRUE && finish==FALSE){
            strcat(output,arr);
            //printf("------->%s\n",arr);
            //Walley_Run(arr);
            //Walley_Run_For_Appointed_File("__walley_temp__.wy","__walley_settings_temp__.wy",arr);
              Walley_Run_For_Appointed_File(file_var_temp_name,file_settings_temp_name,file_file_temp_name,arr);        
        }
        if(begin==TRUE&&finish_init_param==FALSE){
            //if(strcmp(parameter_str,"None")==0){
            if(strcmp(parameter_str,"None,")==0){
                finish_init_param=TRUE;
                continue;
            } else {
                // 12,13,12,
                //printf("Enter Here\n");
                char *arr_arr;
                if(arr[(int)strlen(arr)-1]=='\n'){
                //if(find(arr,"\n")!=-1)
                    arr_arr=malloc(sizeof(char)*((int)strlen(arr)-1));
                    arr_arr=substr(arr,0,(int)strlen(arr)-1);
                } else {
                    arr_arr=malloc(sizeof(char)*((int)strlen(arr)));
                    strcat(arr_arr,arr);
                }
                arr_arr=removeBackSpace(arr_arr);
                strcat(output,arr_arr);
                strcat(output,substr(parameter_str,from_index,find_from_index_not_in_string(parameter_str,",",from_index+1)));
                strcat(output,"\n");
                char *var_name=substr(arr_arr,0,find(arr_arr,"="));
                char *var_value=substr(parameter_str,from_index,find_from_index_not_in_string(parameter_str,",",from_index+1));
                if(stringIsDigit(var_value)==FALSE && strcmp(variableValueType(var_value),"string")!=0){
                    //var_value=getValueFromValueName("__walley__.wy",var_name);
                    var_value=getValueFromValueName("__walley__.wy",var_value);
                }
                
                strcat(arr_arr,var_value);
                //strcat(one_line,substr(parameter_str,from_index,find_from_index(parameter_str,",",from_index+1)));
                //Walley_Run(arr_arr);
                
                
                //printf("------->%s\n",arr_arr);
                //Walley_Run(arr_arr);
                //Walley_Run_For_Appointed_File("__walley_temp__.wy","__walley_settings_temp__.wy",arr_arr);
                Walley_Run_For_Appointed_File(file_var_temp_name,file_settings_temp_name,file_file_temp_name,arr_arr);
                
                from_index=find_from_index_not_in_string(parameter_str,",",from_index+1)+1;
                if((from_index+1)>=(int)strlen(parameter_str)){
                    finish_init_param=TRUE;        
                    //printf("finish init param\n");
                    
                }
            }
        }
        
        if(find_function==TRUE && find(arr,"#~Begin\n")!=-1){
            begin=TRUE;
        }
    }
    //remove("__walley_temp__.wy");
    //remove("__walley_settings_temp__.wy");
    remove(file_var_temp_name);
    remove(file_settings_temp_name);
    
    //printf("The output is \n####################\n%s####################\n",output);
    return "None";
}

void Walley_Remove_Variable_And_Value_From_File(char* file_var_name, char *var_name) {
   //// printf("#### Walley_Remove_Variable_And_Value_From_File ####\n");
    bool existed = checkWhetherSameVarNameExistsFromFile(file_var_name, var_name);
   //// printf("%d\n",existed);
    if (existed == TRUE) {
        char *var_value = getValueFromValueName(file_var_name, var_name);
        char *var_value_type = variableValueType(var_value);
        bool delete_only_one_row = TRUE;
        if (strcmp(var_value_type, "list") == 0 || strcmp(var_value_type, "dictionary") == 0) {
            delete_only_one_row = FALSE;
           //// printf("It is list or dictionary\n");
        }
        char *end_sentence=malloc(sizeof(char)*((int)strlen("#~End::\n")+(int)strlen(var_name)));//#~End:__temp__:
        strcat(end_sentence,"#~End:");
        strcat(end_sentence,var_name);
        strcat(end_sentence,":\n");
        
        bool begin_to_copy=TRUE;
        FILE *fp;
        char arr[1000] = "";
        char output[10000] = "";
        if ((fp = fopen(file_var_name, "r")) == NULL) {
            perror("File open error!\n");
            exit(1);
        }

        while ((fgets(arr, 1000, fp)) != NULL) {
            if (find_not_in_string(arr, ":")==-1) {
                continue;
            }
            char *var_name_in_file = substr(arr, 0, find(arr, ":"));
            if (strcmp(var_name_in_file, var_name) != 0) {
                if (begin_to_copy == TRUE)
                        strcat(output, arr);
            } else if (delete_only_one_row == TRUE)
                continue;
            else if(delete_only_one_row == FALSE && begin_to_copy==TRUE){
                begin_to_copy=FALSE;
            }
            
            if(strcmp(end_sentence,arr)==0){
                begin_to_copy=TRUE;
            }

        }
        
        char *str_to_file=malloc(sizeof(char)*(int)strlen(output));
        int i=0;
        for(i=0;i<(int)strlen(output);i++){
            str_to_file[i]=output[i];
        }
        
        fclose(fp);
        fp=fopen(file_var_name,"w");
        fputs(str_to_file,fp);
        fclose(fp);

    }
}
//############################### Update Var and Var_Value to File#############################
// If var existed, then replace
// else create new one.
void Walley_Update_Var_And_Var_Value_To_File(char *file_var_name, char *var_name, char *var_value){
   //// printf("#### Walley_Update_Var_And_Var_Value_To_File ####\n");
    char *var_value_type = variableValueType(var_value);
    bool has_same_var_name = checkWhetherSameVarNameExistsFromFile(file_var_name, var_name);
    
    if (has_same_var_name == TRUE) {
        char *previous_var_value=getValueFromValueName(file_var_name,var_name);
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
               //// printf("&&&&&&& Enter Here 1 \n");
                changeTheOneVarValueFromItsInitialOneFromFileOrAddVarNameAndValueForDictionary(file_var_name, var_name, var_value);

            } else {
               
                if(strcmp(previous_var_value_type,"dictionary")==0||strcmp(previous_var_value_type,"list")==0){
                    Walley_Remove_Variable_And_Value_From_File(file_var_name,var_name);
                    writeVarNameAndVarValueIntoAppointedFile(file_var_name, var_name, var_value, var_value_type);
                }
                //printf("&&&&&&& Enter Here 2 \n");
                //var_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(var_value, file_var_name);
                //var_value = Walley_Eval_With_Variable_From_File(file_var_name, var_value);
                //var_value_type = variableValueType(var_value);
                else{
                        //printf("here2\n");
                        changeTheVarValueFromItsInitialOneFromFile(file_var_name, var_name, var_value, var_value_type);
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
           //// printf("Find Dictionary Type Value");
            writeVarNameAndVarValueIntoAppointedFileForDictionary(file_var_name, var_name, var_value);

        }            // Eg a{"Hello"} is one element of dictionary
        else if (find_not_in_string(var_name, "{") != -1 && find_not_in_string(var_name, "}") != -1) {
           //// printf("&&&&&&& Enter Here 1 \n");
            changeTheOneVarValueFromItsInitialOneFromFileOrAddVarNameAndValueForDictionary(file_var_name, var_name, var_value);

        }            // Initialize simple value
        else {
            //printf("++++++++++++enter here\n");
            //var_value=countFromExpression(var_value);
            //var_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(var_value, file_var_name);
            //var_value = Walley_Eval_With_Variable_From_File(file_var_name, var_value);
            //var_value_type = variableValueType(var_value);
            writeVarNameAndVarValueIntoAppointedFile(file_var_name, var_name, var_value, var_value_type);
        }
    }   
}

/*
 *This function is mainly about  Walley_Run_One_Function_And_Return_Value. get_var_from_file_name is you get parameter
 * value from the file that you appointed.
 */
//char *Walley_Run_One_Function_And_Return_Value(char *input_str){
char *Walley_Run_One_Function_And_Return_Value(char *input_str,char *get_var_from_file_name){
   //// printf("\n#### Walley_Run_One_Function_And_Return_Value ####\n");
    char* return_var_name="None";
    char* return_value;
   //// printf("Function is |%s|\n",input_str);
    
    
    input_str=removeBackSpace(input_str);
    input_str=removeAheadSpace(input_str);
    
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
    func_name=trim(func_name);    

   //// printf("here\n");
   //// printf("%s\n",input_str);
    char *parameter_str=substr(input_str, find(input_str,"(")+1,find(input_str,")"));
   //// printf("here\n");
    //printf("#### parameter_str is %s ####\n",parameter_str);
    parameter_str=removeAheadSpace(parameter_str);
    //printf("#### parameter_str is %s ####\n",parameter_str);
    parameter_str=removeBackSpace(parameter_str);
    //printf("###### Parameter is : %s ######\n",parameter_str);
    
    
    int para_num=count_str(parameter_str,",")+1;
    
    if(stringIsEmpty(parameter_str)){
        para_num=0;
        parameter_str="None";
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
    file_var_temp_name[(int)strlen(file_var_temp_name)]=0;
    //fp=fopen("__walley_temp__.wy","w");
    Walley_Initialize_Var_File(file_var_temp_name);
   //// printf("==== file_var_temp_name %s\n",file_var_temp_name);
    
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
   //// printf("==== file_settings_temp_name %s\n",file_settings_temp_name);
    
    char *file_file_temp_name=malloc(sizeof(char)*((int)strlen(func_name)+(int)strlen("__walley_file_temp___.wy")+1));
    strcat(file_file_temp_name,"__walley_file_temp_");
    strcat(file_file_temp_name,func_name_temp);
    strcat(file_file_temp_name,"__.wy");
    file_file_temp_name[(int)strlen(file_file_temp_name)]=0;
    //fp=fopen("__walley_settings_temp__.wy","w");
    fp=fopen(file_file_temp_name,"w");
    if(fp==NULL){
        printf("Failed to initialize file");
    } else {
        fputs("#Temp File In Order To Run goto\n",fp);
        fclose(fp);
    }  
   //// printf("file_file_temp_name %s\n",file_file_temp_name);
    
    
    bool find_function=FALSE;
    bool begin=FALSE;
    bool finish=FALSE;
    bool finish_init_param=FALSE;
    bool find_return=FALSE;
    
    char *temp_temp=malloc(sizeof(char)*((int)strlen(func_name)+1));
    strcat(temp_temp,func_name);
    strcat(temp_temp,":");


    char *temp2 = malloc(sizeof (char) *(int) strlen(parameter_str) + 2);
    strcat(temp2, parameter_str);
    strcat(temp2, ",");
    temp2[(int)strlen(temp2)]=0;
    parameter_str = temp2;

    int from_index=0;
    int count=0;
    char output[1000]="";
    
    char arr[1000]="";
    fp = fopen("__walley_function__.wy", "r");
    while ((fgets(arr, 1000, fp)) != NULL) {
        //char one_line[1000];
        //printf("----arr----%s\n",arr);
        if(find_function==TRUE && strcmp("return",substr(removeBackSpace(removeAheadSpace(arr)),0,6))==0){
            
            //find_return=TRUE;
           //// printf("--------Find Return--------");
            Walley_Run_For_Appointed_File(file_var_temp_name, file_settings_temp_name,file_file_temp_name,"#FIND RETURN");
            finish=TRUE;
            return_var_name=substr(arr,find(arr,"return")+7,(int)strlen(arr));
            return_var_name=removeAheadSpace(return_var_name);
            return_var_name=removeBackSpace(return_var_name);
            if(return_var_name[(int)strlen(return_var_name)-1]=='\n'){
                return_var_name=substr(return_var_name,0,(int)strlen(return_var_name)-1);
            }
            //printf("Return Var Name is :%s\n",return_var_name);
            break;
        }
        
        if(find(arr,temp_temp)!=-1){
            //printf("Find Function\n");
            find_function=TRUE;
        }
        if(find_function==TRUE && find(arr,"#~End\n")!=-1){
            //printf("Find End\n");
            finish=TRUE;
        }
        
        if(finish==TRUE){
            //printf("Finish\n\n");
            break;
            
        }
        if(finish_init_param==TRUE && finish==FALSE){
            strcat(output,arr);
            //printf("------->%s\n",arr);
            //Walley_Run(arr);
            //Walley_Run_For_Appointed_File("__walley_temp__.wy","__walley_settings_temp__.wy",arr);
            char *temp=removeAheadSpace(removeBackSpace(arr));
            //printf("----After remove space---> %s ---\n",temp);
            if (isFunction(temp)) {
                //printf("Is Function1111\n");
                printf("%s\n", Walley_Run_One_Function_And_Return_Value(temp, file_var_temp_name));
            }
            else {
               //// printf("*************** GO THERE ***************");
                // if is_instance_value is true, save like Rohit.age to __walley__.wy 
                bool is_instance_value = FALSE;
                if (isExpression(arr)) {
                   //// printf("********* %s IT IS EXPRESSION ********\n", arr);
                    char *var_name2 = variableName(arr);
                    char *user;
                    if (find_not_in_string(var_name2, ".") != -1) {
                        user = substr(var_name2, 0, find_not_in_string(var_name2, "."));
                        bool is_instance = checkWhetherSameInstanceExisted("__walley__.wy", user);
                        if (is_instance)
                            is_instance_value = TRUE;
                        else
                            is_instance_value = FALSE;
                    }

                }
                if (is_instance_value == FALSE) {
                    Walley_Run_For_Appointed_File(file_var_temp_name, file_settings_temp_name, file_file_temp_name, arr);
                } else {
                   //// printf("************ IT IS INSTANCE VALUE ************");
                   //// printf("************ %s **********\n", arr);
                    Walley_Run_For_Appointed_File(file_var_temp_name, file_settings_temp_name, file_file_temp_name, arr);
                    char *var_name3 = variableName(arr);
                    char *var_value3 = getValueFromValueName(file_var_temp_name, var_name3);
                    Walley_Update_Var_And_Var_Value_To_File("__walley__.wy", var_name3, var_value3);
                }
            }
        }
        
        /*
        if(begin==TRUE&&finish_init_param==FALSE){
            printf("Begin to Initialize parameters\n");
            //printf("param str is %s\n",parameter_str);
            //if(strcmp(parameter_str,"None")==0){
            if(strcmp(parameter_str,"None,")==0){
                //printf("Params is None\n");
                finish_init_param=TRUE;
                continue;
            } 

            // 12,13,12,
            //printf("Enter Here\n");
            char *arr_arr;
            if (arr[(int) strlen(arr) - 1] == '\n') {
                //if(find(arr,"\n")!=-1)
                arr_arr = malloc(sizeof (char) *((int) strlen(arr) - 1));
                arr_arr = substr(arr, 0, (int) strlen(arr) - 1);
            } else {
                arr_arr = malloc(sizeof (char) *((int) strlen(arr)));
                strcat(arr_arr, arr);
            }
            arr_arr = removeBackSpace(arr_arr);
            strcat(output, arr_arr);
            strcat(output, substr(parameter_str, from_index, find_from_index_not_in_string(parameter_str, ",", from_index + 1)));
            strcat(output, "\n");
            char *var_name = substr(arr_arr, 0, find(arr_arr, "="));
            char *var_value = substr(parameter_str, from_index, find_from_index_not_in_string(parameter_str, ",", from_index + 1));
            if (stringIsDigit(var_value) == FALSE && strcmp(variableValueType(var_value), "string") != 0) {
      
                //var_value = getValueFromValueName("__walley__.wy", var_value);
                //printf("@@@@@@@@@@ Get Value From File %s\n",get_var_from_file_name);
                var_value = getValueFromValueName(get_var_from_file_name, var_value);
            }
            //printf("@@@@@@@@@@ Did not get value\n");
            strcat(arr_arr, var_value);
            //strcat(one_line,substr(parameter_str,from_index,find_from_index(parameter_str,",",from_index+1)));
            //Walley_Run(arr_arr);


            //printf("------->%s\n",arr_arr);
            //Walley_Run(arr_arr);
            //Walley_Run_For_Appointed_File("__walley_temp__.wy","__walley_settings_temp__.wy",arr_arr);
            if ((int) strlen(removeAheadSpace(removeBackSpace(arr_arr))) != 0)
                Walley_Run_For_Appointed_File(file_var_temp_name, file_settings_temp_name,file_file_temp_name,arr_arr);

            from_index = find_from_index_not_in_string(parameter_str, ",", from_index + 1) + 1;
            if ((from_index + 1) >= (int) strlen(parameter_str)) {
                finish_init_param = TRUE;
                //printf("finish init param\n");

            }

        }*/
        if (begin == TRUE && finish_init_param == FALSE) {
            //printf("Initialize parameters\n");
            //printf("param str is %s\n",parameter_str);
            //if(strcmp(parameter_str,"None")==0){
            //printf("PARAMETER is %s\n", parameter_str);
            
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
               //// printf("finish_init_param\n");
                continue;
            }
            
            
            
            if (stringIsEmpty(substr(arr_arr, find_not_in_string(arr_arr, "=")+1, (int)strlen(arr_arr)))==FALSE
                &&checkWhetherSameVarNameExistsFromFile(file_var_temp_name, substr(arr_arr, 0, find_not_in_string(arr_arr, "=")))==FALSE) {
                //Walley_Run_Third_Generation(file_var_temp_name, file_settings_temp_name,file_file_temp_name,"__walley_function__.wy",arr_arr);
                Walley_Run_For_Appointed_File(file_var_temp_name, file_settings_temp_name,file_file_temp_name,arr_arr);
            }
            
            if (strcmp(parameter_str, "None,") == 0) {
               //// printf("Params is None\n");
                //finish_init_param = TRUE;
                continue;
            }
            
            
            char *var_value;
            if(find_from_index_not_in_str_list_dict(parameter_str, ",",from_index+1)==-1)
                continue;
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
            
            
            
            
            
            strcat(output, arr_arr);
            strcat(output, substr(parameter_str, from_index, find_from_index_not_in_string(parameter_str, ",", from_index + 1)));
            strcat(output, "\n");
            
           //// printf("------->%s\n",arr_arr);
            
            //Walley_Run(arr_arr);
            //Walley_Run_For_Appointed_File("__walley_temp__.wy","__walley_settings_temp__.wy",arr_arr);
            if ((int) strlen(removeAheadSpace(removeBackSpace(arr_arr))) != 0){
                //Walley_Run_Third_Generation(file_var_temp_name, file_settings_temp_name,file_file_temp_name,"__walley_function__.wy",arr_arr);
                Walley_Run_For_Appointed_File(file_var_temp_name, file_settings_temp_name,file_file_temp_name,arr_arr);
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
       //// printf("------Return None------\n");
        return_value="None";
    } else {
        //printf("Enter Else\n");
        //return_var_name=substitueExistedVarValueFromFile(return_var_name,"__walley_temp__.wy");
        return_var_name=substitueExistedVarValueFromFile(return_var_name,file_var_temp_name);
        //printf("After substitueExistedVarValueFromFile, return var name is :%s\n",return_var_name);
        return_value=Walley_Eval(return_var_name);
        //return_value="Hi";
    }
    
    
    
    //remove("__walley_temp__.wy");
    //remove("__walley_settings_temp__.wy");
    Walley_Run_For_Appointed_File(file_var_temp_name, file_settings_temp_name,file_file_temp_name,"#end function");

    remove(file_var_temp_name);
    remove(file_settings_temp_name);
    remove(file_file_temp_name);
    
    //printf("The output is \n####################\n%s####################\n",output);
    return return_value;
}

char *Walley_Substitue_Var_And_Function_Return_Value_From_File(char* input_str, char *file_var_name) {//, char *file_function_name){
   //// printf("#### Walley_Substitue_Var_And_Function_Return_Value_From_File ####\n");
    //printf("%s, %s\n",input_str,file_var_name);
    //######### replace the thing inside the {} and []
    //substitueValueInDictionaryAndList(input_str,file_var_name);
    int i = 0;
    int begin = 0; //begin of { and [
    int end = 0; // end of } and ]
    for (i = 0; i < (int) strlen(input_str); i++) {
        if (charIsInString(input_str, i) == FALSE && input_str[i] == '{') {
            //printf("______------______FIND {}\n");
            begin = i;
            end = find_from_index_not_in_string(input_str, "}", begin + 1);
            char *check = substr(input_str, begin, end + 1);
            while (count_str_not_in_string(check, "{") != count_str_not_in_string(check, "}")) {
                end = find_from_index_not_in_string(input_str, "}", end + 1);
                check = substr(input_str, begin, end + 1);
            }
            char *replace_str = substr(input_str, begin + 1, end);
            if (stringIsEmpty(replace_str) == FALSE) {//from x{i} get i
                if (finishFindingVarAndFunction(replace_str) == FALSE) {
                    char *with_str = Walley_Substitue_Var_And_Function_Return_Value_From_File(replace_str, file_var_name);
                    input_str = replace_from_index_to_index(input_str, replace_str, with_str, begin + 1, end);
                }
            }
            //printf("Replace %s with %s, the input_str is %s\n",replace_str,with_str,input_str);
        }

        if (charIsInString(input_str, i) == FALSE && input_str[i] == '[') {
            begin = i;
            end = find_from_index_not_in_string(input_str, "]", begin + 1);
            char *check = substr(input_str, begin, end + 1);
            while (count_str_not_in_string(check, "[") != count_str_not_in_string(check, "]")) {
                end = find_from_index_not_in_string(input_str, "]", end + 1);
                check = substr(input_str, begin, end + 1);
            }
            char *replace_str = substr(input_str, begin + 1, end);
            if (stringIsEmpty(replace_str) == FALSE) {
                if (finishFindingVarAndFunction(replace_str) == FALSE) {//from x{i} get i
                    char *with_str = Walley_Substitue_Var_And_Function_Return_Value_From_File(replace_str, file_var_name);
                    input_str = replace_from_index_to_index(input_str, replace_str, with_str, begin + 1, end);
                }
            }
        }

        if (charIsInString(input_str, i) == FALSE && input_str[i] == '(') {
            begin = i;
            end = find_from_index_not_in_string(input_str, ")", begin + 1);
            char *check = substr(input_str, begin, end + 1);
            while (count_str_not_in_string(check, "(") != count_str_not_in_string(check, ")")) {
                end = find_from_index_not_in_string(input_str, ")", end + 1);
                check = substr(input_str, begin, end + 1);
            }
            char *replace_str = substr(input_str, begin + 1, end);
            if (stringIsEmpty(replace_str) == FALSE) {
                if (finishFindingVarAndFunction(replace_str) == FALSE) {//from x{i} get i
                    char *with_str = Walley_Substitue_Var_And_Function_Return_Value_From_File(replace_str, file_var_name);
                    input_str = replace_from_index_to_index(input_str, replace_str, with_str, begin + 1, end);
                }
            }
        }


    }
   //// printf("AFTER REPLACE THE THING IN [] AND {}\nTHE INPUT IS |%s|\n", input_str);
   //// printf("input str is :%s\nlength is %d\n", input_str, (int) strlen(input_str));
    //printf("Required File is %s\n",file_var_name);
    bool find_alpha = FALSE;
    bool finish_find_var = FALSE;
    bool find_function = FALSE;
    //int begin=0;
    //int end=(int)strlen(input_str);
    //int i=0;
    begin = 0;
    end = (int) strlen(input_str);
    i = 0;


    char *output = malloc(sizeof (char) *((int) strlen(input_str) + 1));
    //char output[1000]="";
    for (i = 0; i < (int) strlen(input_str); i++) {
        output[i] = input_str[i];
    }
    output[(int) strlen(input_str)] = 0;
    //printf("Output now is %s\n",output);

    //char *output=malloc(sizeof(char)*1000);
    //strcat(output,input_str);

    bool has_var = FALSE;
    for (i = 0; i < (int) strlen(input_str); i++) {
        //printf("#### Enter Loop Output is %s\n####",output);
        //printf("#### Output Length is %d\n",(int)strlen(output));
        //printf("*********** %c End is %d --->%s\n", input_str[i], end, output);
        int temp_length = (int) strlen(output);
        /*
        if (finishFindingVarAndFunction(output) == TRUE) {
            printf("Finish Finding Var And Function, output is |%s|\n", output);
            output = substr(output, 0, temp_length);
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
            if (input_str[i]=='[') {
                if (count_str_not_in_string(substr(input_str, 0, i), "[")==count_str_not_in_string(substr(input_str, 0, i), "]")) {
                    find_function=TRUE;
                } else {
                    find_function=FALSE;
                }
            }
            else{
                find_function=TRUE;
            }
            //printf("Find Function\n");
        }
        if (find_function) {
            //printf("@@@@@ Enter Find Function @@@@@\n");
            find_function = FALSE;
            //printf("@@@@@ Enter Find Function @@@@@\n");
            char *func_name = substr(input_str, begin, i);
           //// printf("Func_Name is %s\n", func_name);
            bool it_is_slice=FALSE;// = checkWhetherSameVarNameExistsFromFile(file_var_name, func_name);
            if (checkWhetherSameVarNameExistsFromFile(file_var_name, func_name)==TRUE||
                strcmp(variableValueType(func_name),"string")==0||
                strcmp(variableValueType(func_name), "list")==0) {
                it_is_slice=TRUE;
            }
           //// printf("it is function %d\n", it_is_slice);
            if (it_is_slice == FALSE) {
                find_function = FALSE;
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
               //// printf("#### First Generation FUNCTION is |%s| ####\n", function);
                if (find(substr(function, 0, find(function, "(")), ".") != -1 && charIsInString(function, find(function, ".")) == FALSE) {
                    char *user = substr(function, 0, find(function, "."));
                    bool instance_existed = checkWhetherSameInstanceExisted(file_var_name, user);
                    bool var_existed = checkWhetherSameVarNameExistsFromFile(file_var_name, user);
                    
                    bool only_var_existed = var_existed;
                    
                    char *user_value=Walley_Substitue_Var_And_Function_Return_Value_From_File(user, file_var_name);
                    char *function_temp=replace_not_in_string(function, user, user_value);
                    
                    if (strcmp(variableValueType(user), "string")==0||strcmp(variableValueType(user), "list")==0) {
                        var_existed=TRUE;
                    }
                    
                    if (instance_existed == FALSE && var_existed == TRUE) {
                       //// printf("function is %s\nfile_var_name is %s\n", function, file_var_name);
                       // return_value = Walley_Run_Special_Function(function_temp, file_var_name);
                        if (only_var_existed==TRUE) {
                            return_value=Walley_Run_Special_Function(function, file_var_name);
                        } else {
                            return_value = Walley_Run_Special_Function(function_temp, file_var_name);
                        }
                    } else {
                        return_value = Walley_Run_One_Function_And_Return_Value(function, "__walley__.wy");
                    }
                }


                    //################### Embeded Function ###############################################################
                else if (find(function, "int(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = to_int(temp_value);
                } else if (find(function, "double(")== 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = to_double(temp_value);
                } else if (find(function, "nstr(")== 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = to_nstr(temp_value);
                } else if (find(function, "str(")== 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = to_string(temp_value);
                } else if (find(function, "sin(")== 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = math_sin(temp_value);
                } else if (find(function, "cos(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = math_cos(temp_value);
                } else if (find(function, "tan(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = math_tan(temp_value);
                } else if (find(function, "log10(")== 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = math_log10(temp_value);
                } else if (find(function, "exp(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = math_exp(temp_value);
                } else if (find(function, "type(")== 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = var_value_type(temp_value);
                   //// printf("Find type() and return value is %s\n", return_value);
                } else if (find(function, "num(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = to_num(temp_value);
                } else if (find(function, "time(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = simple_time(temp_value);
                } else if (find(function, "file_readlines(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = file_readlines(temp_value);
                } else if (find(function, "file_writelines(")==0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    temp_value=toCString(temp_value);
                    char *file_name = substr(temp_value, 0, find_not_in_string(temp_value, ","));
                    char *lines = substr(temp_value, find_not_in_string(temp_value, ",") + 1, (int) strlen(temp_value));
                    file_name = toCString(file_name);
                    lines=toCString(lines);
                    return_value = file_writelines(file_name,lines);
                } else if (find(function, "remove_file(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = file_removefile(temp_value);
                } else if (find(function, "create_file(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = file_createfile(temp_value);
                } else if (find(function, "system(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = walley_system(temp_value);
                } else if (find(function, "input(") == 0) {
                    char *temp1 = substr(function, find(function, "(") + 1, (int) strlen(function) - 1);
                    char *temp_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(temp1, file_var_name);
                    temp_value = Walley_Eval_With_Variable_From_File(file_var_name, temp_value);
                    return_value = var_input(temp_value);
                }

                    //#################################################################
                else {



                    return_value = Walley_Run_One_Function_And_Return_Value(function, "__walley__.wy");
                }
                
                end=index_of_youkuohao+1;
                int begin_temp = begin + (int) strlen(output)-(int) strlen(input_str);
                int end_temp = end + (int) strlen(output)-(int) strlen(input_str);
                //printf("For input_str Begin %d, End %d\n", begin, end);
                //printf("Begin %d, End %d\n", begin_temp, end_temp);
                //printf("Before change,input_str is %s output is %s\n", input_str, output);
                output = replace_from_index_to_index(output, function, return_value, begin_temp, end_temp);

                i = index_of_youkuohao;
                find_alpha = FALSE;
                has_var = TRUE;
                finish_find_var = FALSE;
                continue;
            } else {
               //// printf("It is slice\n");
                //int index_of_rect = find_from_index_not_in_string(input_str, "]", i + 1);
                int index_of_rect = find_from_index_not_in_str_list_dict_parenthesis(input_str, "]", i + 1);
                while (input_str[index_of_rect+1]=='[') {
                    index_of_rect= find_from_index_not_in_str_list_dict_parenthesis(input_str, "]", index_of_rect+ 1);
                }
                // case like x[0:1].toupper()
                if (input_str[index_of_rect+1]=='.') {
                   //// printf("Find . after ]");
                    find_alpha=TRUE;
                    find_function=FALSE;
                    continue;
                }
                
                char *slice_str = substr(input_str, i, index_of_rect + 1);
                char *value_of_var ;//= getValueFromValueName(file_var_name, func_name);
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
                end=index_of_rect+1;
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
            }
        }

        if (find_alpha == TRUE && isSign(input_str[i]) && charIsInString(input_str, i) == FALSE) {
            find_alpha = FALSE;
            end = i;
            //printf("@@@@@@ end %d\n",end);
            finish_find_var = TRUE;

        }
        if (find_alpha == TRUE && ((isJudgeSign(input_str[i])) || input_str[i] == ')' || input_str[i]==','|| input_str[i]==' ') && charIsInString(input_str, i) == FALSE && charIsInList(input_str, i)==FALSE && charIsInDictionary(input_str, i)==FALSE) {
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
            if (find_not_in_string(var_name, ".") != -1) {
                char *user = substr(var_name, 0, find_not_in_string(var_name, "."));
                if (checkWhetherSameInstanceExisted("__walley__.wy", user) == TRUE) {
                    var_value = getValueFromValueName("__walley__.wy", var_name);
                }
                else {
                    var_value = getValueFromValueName(file_var_name, var_name);
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
            int begin_temp = begin + (int) strlen(output)-(int) strlen(input_str);
            int end_temp = end + (int) strlen(output)-(int) strlen(input_str);

            //printf("Begin %d, End %d\n",begin_temp,end_temp);
            //printf("Before change, output is %s\n",output);
            output = replace_from_index_to_index(output, var_name, var_value, begin_temp, end_temp);
            //printf("Output is %s\n",output);
            has_var = TRUE;
            finish_find_var = FALSE;
            find_alpha = FALSE;
            //free(var_name);
            //free(var_value);
        }
        //printf("--End this loop, output is %s\n",output);

    }

    //if(has_var==FALSE){
    //    return input_str;
    //}
    output=Walley_Eval_All_From_File(file_var_name, output);
   //// printf("Walley_Substitue_Var_And_Function_Return_Value_From_File !!!!!!output is %s\n", output);
    return output;
}

char *Walley_Print(char *var_in_file_name, char *input_str){
   //// printf("#### Walley_Print ####\n");
    input_str=Walley_Substitue_Var_And_Function_Return_Value_From_File(input_str,var_in_file_name);
    //printf("%s\n",input_str);
    char *output=toCString(Walley_Eval_With_Variable_From_File(var_in_file_name,input_str));
    if (find(output, "\\n")!=-1) {
        output=replace(output, "\\n", "\n");
    }
    return output;
}
char *Walley_Println(char *var_in_file_name, char *input_str){
   //// printf("#### Walley_Println ####\n");
    /*
    input_str=Walley_Substitue_Var_And_Function_Return_Value_From_File(input_str,var_in_file_name);
    char *input= Walley_Eval_With_Variable_From_File(var_in_file_name,input_str);
    input=toCString(input);
    char *output=malloc(sizeof(char)*(int)strlen(input));
    strcat(output,input);
    strcat(output,"\n");
    return output;*/
    return append(Walley_Print(var_in_file_name,input_str), "\n");
}

bool Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(char *input_str, char *var_in_file_name){
   //// printf("#### Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function ####\n");
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
    input_str=Walley_Substitue_Var_And_Function_Return_Value_From_File(input_str,var_in_file_name);
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
   //// printf("####----->%s\n",input_str);
   //// printf("Here\n");
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
    bool has_same_var_name = checkWhetherSameVarNameExistsFromFile(file_var_name, var_name);
    
    if (has_same_var_name == TRUE) {
        char *previous_var_value=getValueFromValueName(file_var_name,var_name);
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
                //var_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(var_value, file_var_name);
                //var_value = Walley_Eval_With_Variable_From_File(file_var_name, var_value);
                //var_value_type = variableValueType(var_value);
                else{
                        //printf("here2\n");
                        changeTheVarValueFromItsInitialOneFromFile(file_var_name, var_name, var_value, var_value_type);
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
            //var_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(var_value, file_var_name);
            //var_value = Walley_Eval_With_Variable_From_File(file_var_name, var_value);
            //var_value_type = variableValueType(var_value);
            writeVarNameAndVarValueIntoAppointedFile(file_var_name, var_name, var_value, var_value_type);
        }
    }   
}**/


//############################### If is expression, DO THAT ###################################

void Walley_Eval_And_Update_Var_And_Value_To_File(char* file_var_name,char* input_str) {
    //else if (isExpression(input_str)==TRUE){
   //// printf("#### Walley_Eval_And_Update_Var_And_Value_To_File ####\n");
    char *var_name = variableName(input_str);
    char *var_value = variableValue(input_str);
    char *var_value_type = variableValueType(var_value);
   //// printf("#### The Variable Name is :%s\n",var_name);
   //// printf("#### The Variable Value is :%s\n", var_value);
   //// printf("#### The Variable Value Type is :%s\n", var_value_type);
    //Walley_Substitue_Var_And_Function_Return_Value_From_File AND Walley_Eval_With_Variable_From_File
    //Do not support operation of list and dictionary now
    if(strcmp("list",var_value_type)!=0 && strcmp("dictionary",var_value_type)!=0){
       //// printf("var value type is not list or dictionary\n");
        var_value = Walley_Substitue_Var_And_Function_Return_Value_From_File(var_value, file_var_name);
    }
    var_value = Walley_Eval_With_Variable_From_File(file_var_name, var_value);
    var_value_type = variableValueType(var_value);
    
   //// printf("#### The Variable Name is :%s\n", var_name);
   //// printf("#### The Variable Value is :%s\n", var_value);
   //// printf("#### The Variable Value Type is :%s\n", var_value_type);
    //printf("The Variable Value after put known Variable in is :%s\n",putKnownVariableIntoExpression(var_value));


    // ################### Basic Calculation ##################################
    //if(strcmp(var_value_type,"unknown type")!=0){//&&strcmp(var_value_type,"function")!=0){
    Walley_Update_Var_And_Var_Value_To_File(file_var_name,var_name,var_value);
}


void Walley_Judge_Run_Anotation_For_While_Def_Class(char *file_var_name,char *setting_file,char *input_str) {
   //// printf("Walley_Judge_Run_Anotation_For_While_Def_Class----->|%s|,|%s|,|%s|\n",file_var_name,setting_file,input_str);
    input_str = removeAheadSpace(input_str);
    
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
    //I add this value here in order to run now_run_if.
    bool can_run_basic_input = TRUE;
    bool run_goto = FALSE;
    int space_of_first_while_sentence = atoi(getValueFromValueName(setting_file, "space_of_first_while_sentence"));
    int space_of_first_for_sentence = atoi(getValueFromValueName(setting_file, "space_of_first_for_sentence"));
    int space_of_first_def_sentence = atoi(getValueFromValueName(setting_file, "space_of_first_def_sentence"));
    int space_of_first_class_sentence = atoi(getValueFromValueName(setting_file,"space_of_first_def_sentence"));
    
    int current_space=atoi(getValueFromValueName(setting_file,"current_space"));
   //// printf("current_space is %d\n",current_space);

    //#####################  Anotation  ###################    
    if (input_str[0] == '#') {
        //printf("This is one anatation %s\n", removeAheadSpace(input_str));
        printf("");
    }
    else if (find(input_str,"class ")==0){
       //// printf("#### begin to define a class ####\n");
        now_writting_class=TRUE;
        space_of_first_class_sentence=space;
        space=space+4;
        
        char *class_name=className(input_str);
        char *class_mother=classMother(input_str);
        char *__temp_class__=getValueFromValueName(file_var_name,"__temp_class__");
        __temp_class__=dictionaryAddKeyAndValue(__temp_class__,toString(class_name),toString(class_mother));
        changeTheWholeVarValueFromItsInitialOneFromFileForDictionary(file_var_name,"__temp_class__",__temp_class__);
        
        char *__string_in_temp_class__=getValueFromValueName(file_var_name,"__string_in_temp_class__");
        //char *temp=malloc(sizeof(char)*((int)strlen("#Begin to define class...\\nClass name:\\n")+1+(int)strlen(class_name)));
        __string_in_temp_class__=dictionaryAddKeyAndValue(__string_in_temp_class__,toString(class_name),toString("#Begin to define class...\\n"));
        
        
       //// printf("__string_in_temp_class__ is %s\n",__string_in_temp_class__);
        changeTheWholeVarValueFromItsInitialOneFromFileForDictionary(file_var_name,"__string_in_temp_class__",__string_in_temp_class__);
        
        
       //// printf("class_name is %s, class extends %s\n",class_name,class_mother);
        
        changeTheVarValueFromItsInitialOneFromFile(file_var_name,"__temp_class_name_now_writting__",toString(class_name),"string");
        
    }
    // ##############  Function  ##############################
    else if (find(input_str, "def ") == 0) {
       //// printf("\n###### begin to define a function######\n");
        space_of_first_def_sentence = space;
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
               //// printf("This Function has no Parameter\n");
                writeStringToFile("__walley_function__.wy","#### Parameters  are None ####\n");
                writeStringToFile("__walley_function__.wy", "##Finish Init Params\n");
            } else {
                writeFunctionParameterOneByOneToFile(func_param_str);
                writeStringToFile("__walley_function__.wy", "##Finish Init Params\n");
                //writeStringToFile("__walley_function__.wy","#Finish initialize parameters\n");
            }
        }
    }//################## Judge Whether this whether an if sentence ##########################
    else if (find(input_str, "if ") == 0 || find(input_str, "elif ") == 0 || find(input_str, "else") == 0) {
       //// printf("now judge if sentence\n");
        char *sentence = "";
        char *temp_for_sentence = removeAheadSpace(removeBackSpace(input_str));
        bool can_run=TRUE;
        space=current_space;
        
        if (find(input_str, "if ") == 0) {
           //// printf("Find If\n");
            sentence = substr(temp_for_sentence, find(temp_for_sentence, "if ") + 3, (int) strlen(temp_for_sentence) - 1);
            last_if_sentence = sentence;
            can_run = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(sentence, file_var_name);
           //// printf("++++++can run is %d\n",can_run);
            
            // if can run.
            // Write last_if_sentence to __temp_if__
            //if(can_run==TRUE){
            char *__temp_if__=getValueFromValueName(file_var_name,"__temp_if__");
            __temp_if__=listAppendOneElement(__temp_if__,last_if_sentence);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__temp_if__",__temp_if__);
            //}
            char *__temp_if_space__=getValueFromValueName(file_var_name,"__temp_if_space__");
            char temp_num[100];
            sprintf(temp_num,"%d",space);
            __temp_if_space__=listAppendOneElement(__temp_if_space__,temp_num);
            
            char *__has_run_if__=getValueFromValueName(file_var_name,"__has_run_if__");
            //char temp_num[100];
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
                    char *index_str = malloc(sizeof (char) *((int) strlen(temp_length) + 2));
                    strcat(index_str, "[");
                    strcat(index_str, temp_length);
                    strcat(index_str, "]");
                    __temp_if_space__ = listRemoveOneElementAtOneIndex(__temp_if_space__, index_str);
                    __temp_if__=listRemoveOneElementAtOneIndex(__temp_if__,index_str);
                    __has_run_if__=listRemoveOneElementAtOneIndex(__has_run_if__,index_str);
                    changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__temp_if__",__temp_if__);

                }
                
                
            }
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__has_run_if__",__has_run_if__);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__temp_if_space__",__temp_if_space__);
            
        } else if (find(input_str, "elif ") == 0) {
           //// printf("Find elif\n");
            //sentence = substr(temp_for_sentence, find(temp_for_sentence, "elif ") + 5, (int) strlen(temp_for_sentence) - 1);
            //int length_of_temp = (int) strlen("not ( ") + 1 + (int) strlen(" ) and (  )")+(int) strlen(last_if_sentence)+(int) strlen(sentence);
            //char *temp_for_sentence2 = malloc(sizeof (char) *length_of_temp);
            //strcat(temp_for_sentence2, "not ( ");
            
            
            
            //strcat(temp_for_sentence2, last_if_sentence);
            char *__temp_if__=getValueFromValueName(file_var_name,"__temp_if__");
            int length=valueNumOfList(__temp_if__);
            char temp_length[100];
            
            char *__has_run_if__=getValueFromValueName(file_var_name,"__has_run_if__");
            
            int i=0;
            int index;
            char *__temp_if_space__=getValueFromValueName(file_var_name,"__temp_if_space__");
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
            char *index_str=malloc(sizeof(char)*((int)strlen(temp_length)+2));
            strcat(index_str,"[");
            strcat(index_str,temp_length);
            strcat(index_str,"]");
            last_if_sentence=valueOfListAtIndexString(__temp_if__,index_str);
            bool has_run_if=atoi(valueOfListAtIndexString(__has_run_if__,index_str));
            
            
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
            can_run = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(sentence, file_var_name);
            // if can run.
            // Write last_if_sentence to __temp_if__
            //if(can_run==TRUE){
            __temp_if__ = getValueFromValueName(file_var_name, "__temp_if__");
            length = valueNumOfList(__temp_if__);
            //char temp_length[100];
            sprintf(temp_length, "%d", length - 1);
            char *var_name_str = malloc(sizeof (char) *((int) strlen(temp_length) + 2 + (int) strlen("__temp_if__")));
            strcat(var_name_str, "__temp_if__[");
            strcat(var_name_str, temp_length);
            strcat(var_name_str, "]");
            changeTheOneVarValueFromItsInitialOneFromFileForList(file_var_name, var_name_str, sentence);
            //}
            if(has_run_if==TRUE){
               //// printf("********* HAS RUN IF **********");
                can_run=FALSE;
            } else if (can_run==TRUE){
                int length_of_has_run_if__=valueNumOfList(__has_run_if__);
                char temp4[100];
                sprintf(temp4,"%d",length_of_has_run_if__-1);
                char *var_name_str2=malloc(sizeof(char)*((int)strlen("__has_run_if__")+3+(int)strlen(temp4)));
                strcat(var_name_str2,"__has_run_if__[");
                strcat(var_name_str2,temp4);
                strcat(var_name_str2,"]");
                var_name_str2[(int)strlen(var_name_str2)]=0;
                changeTheOneVarValueFromItsInitialOneFromFileForList(file_var_name,var_name_str2,"1");
            }
        }
        
        
        
        else if (find(input_str, "else") == 0) {
           //// printf("Find else\n");
            
            char *__temp_if__=getValueFromValueName(file_var_name,"__temp_if__");
            int length=valueNumOfList(__temp_if__);
            char temp_length[100];
            
            char *__has_run_if__=getValueFromValueName(file_var_name,"__has_run_if__");
            
            int i=0;
            int index;
            char *__temp_if_space__=getValueFromValueName(file_var_name,"__temp_if_space__");
            for(i=0;i<length;i++){
                int number=atoi(valueOfListAtIndex(__temp_if_space__,i));
               //// printf("number is %d\n",number);
               //// printf("current space is %d\n",current_space);
                if(number==current_space){
                   //// printf("number is %d, current_space is %d\n",number,current_space);
                    index=i;
                    break;
                }
            }
            
            //sprintf(temp_length,"%d",length-1);
            sprintf(temp_length,"%d",index);
            char *index_str=malloc(sizeof(char)*((int)strlen(temp_length)+2));
            strcat(index_str,"[");
            strcat(index_str,temp_length);
            strcat(index_str,"]");
            last_if_sentence=valueOfListAtIndexString(__temp_if__,index_str);
            bool has_run_if=atoi(valueOfListAtIndexString(__has_run_if__,index_str));
            
           //// printf("last is sentence is %s\n", last_if_sentence);

            //if(strcmp("None",last_if_sentence)!=0){
            can_run = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(last_if_sentence, file_var_name);
           //// printf("can_run is %d\n", can_run);
            if (can_run == 1)
                can_run = 0;
            else
                can_run = 1;
            //else{
            //    can_run=0;
            //}
            last_if_sentence = "\"None\"";
            
            //Delete the final __temp_if__ in file
           //// printf("index str is %s\n",index_str);
            __temp_if__=listRemoveOneElementAtOneIndex(__temp_if__,index_str);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__temp_if__",__temp_if__);
            
            __temp_if_space__=listRemoveOneElementAtOneIndex(__temp_if_space__,index_str);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__temp_if_space__",__temp_if_space__);
            
            __has_run_if__=listRemoveOneElementAtOneIndex(__has_run_if__,index_str);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__has_run_if__",__has_run_if__);
            if(has_run_if==TRUE){
               //// printf("********* HAS RUN IF **********");
                can_run=FALSE;
            }
                
            
        }
       //// printf("Enter here\n");
       //// printf("Sentence is |%s|\nLength is %d\n", sentence, (int) strlen(sentence));
        //bool can_run = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(sentence, file_name);
        if (can_run) {
            now_run_if = TRUE;
           //// printf("\n\n\n\n\n\n!!!!!Can Run!!!!!\n");
            space = space + 4;
            //last_if_sentence=sentence;
        } else {
            now_run_if = FALSE;
           //// printf("\n\n\n\n\n\n!!!!!! Can not run !!!!!!\n");
            
        }
    }//#################### While Sentence ##################################
    else if (find(input_str, "while ") == 0) {
        //now_writting_while=TRUE;
        last_while_sentence = removeAheadSpace(input_str);
        last_while_sentence = substr(last_while_sentence, 6, find(last_while_sentence, ":"));
        last_while_sentence = removeBackSpace(last_while_sentence);

        bool can_run_while = Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function(last_while_sentence, file_var_name);
        if (can_run_while == FALSE) {
           //// printf("Can Not Run While");
            now_writting_while = FALSE;
            last_while_sentence = "None";
        } else {
           //// printf("Can Run While\n");
            now_writting_while = TRUE;
            space_of_first_while_sentence = space;
            space = space + 4;
            
            // Write last_while_sentence to __temp_while__
            char *temp_while_var_value=getValueFromValueName(file_var_name,"__temp_while__");
            temp_while_var_value=listAppendOneElement(temp_while_var_value,last_while_sentence);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__temp_while__",temp_while_var_value);
            
            char temp_space[100];
            sprintf(temp_space,"%d",space_of_first_while_sentence);
            char *temp_while_space=getValueFromValueName(file_var_name,"__temp_while_space__");
            temp_while_space=listAppendOneElement(temp_while_space,temp_space);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__temp_while_space__",temp_while_space);
            
        }
    }        //#################### For Sentence #####################################
    else if (find(input_str, "for ") == 0) {// && removeBackSpace(input_str)[(int) strlen(removeBackSpace(input_str)) - 1] == ':') {
       //// printf("#### Find For ####\n");
        temp_i = substr(input_str, find(input_str, "for ") + 4, find(input_str, " in"));
        temp_i = removeAheadSpace(removeBackSpace(temp_i));
        char *in_what = substr(input_str, find(input_str, " in ") + 4, (int) strlen(removeBackSpace(input_str)) - 1);
        in_what = removeAheadSpace(removeBackSpace(in_what));
        in_what = Walley_Substitue_Var_And_Function_Return_Value_From_File(in_what, file_var_name);
        //printf("i is |%s|, in_what is |%s|\n", temp_i, in_what);
        now_writting_for = TRUE;
        //temp_i_in_for_sentence=getValueFromValueName(file_name,in_what);
        temp_i_in_for_sentence = in_what;
        if (strcmp(variableValueType(temp_i_in_for_sentence), "string") == 0) {
           //// printf("It is string\n");
            temp_i_in_for_sentence = changeStringToList(temp_i_in_for_sentence);
        }
        //printf("i is |%s|\n", temp_i_in_for_sentence);

        space_of_first_for_sentence = space;
        space = space + 4;
        
        
        // Write temp_i_in_for_sentence to __temp_for__  eg
        // for i in [1,2,3,4]:     write [1,2,3,4] to __temp_for__
            char *temp_for_var_value=getValueFromValueName(file_var_name,"__temp_for__");
            temp_for_var_value=listAppendOneElement(temp_for_var_value,temp_i_in_for_sentence);
            //printf("####$$$$$ %s\n",temp_for_var_value);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__temp_for__",temp_for_var_value);
            
           //// printf("@@@@@@@@@@@@HERE\n");
            
            char *__temp_i__=getValueFromValueName(file_var_name,"__temp_i__");
            __temp_i__=listAppendOneElement(__temp_i__,temp_i);
            changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__temp_i__",__temp_i__);
            //char temp_space[100];
            //sprintf(temp_space,"%d",space_of_first_while_sentence);
            //char *temp_while_space=getValueFromValueName(file_var_name,"__temp_while_space__");
            //temp_while_space=listAppendOneElement(temp_while_space,temp_space);
            //changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name,"__temp_while_space__",temp_while_space);
    }
    
    
//#################### Set Settigns ################################
   //// printf("#### Set Settings ####\n\n\n");
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
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "space_of_first_for_sentence", (char*) temp2, "int");
    sprintf(temp2, "%d", space_of_first_def_sentence);
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "space_of_first_def_sentence", (char*) temp2, "int");
    sprintf(temp2, "%d", space_of_first_class_sentence);
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "space_of_first_class_sentence", (char*) temp2, "int");
    
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "last_if_sentence", last_if_sentence, "string");
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "last_while_sentence", last_while_sentence, "string");
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "string_in_while_loop", string_in_while_loop, "string");
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "string_in_for_loop", string_in_for_loop, "string");
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "temp_i", temp_i, "string");
    changeTheVarValueFromItsInitialOneFromFile(setting_file, "temp_i_in_for_sentence", temp_i_in_for_sentence, "string");
}