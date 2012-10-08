/* 
 * File:   walley_file_operation.h
 * Author: shd101wyy
 *
 * Created on September 1, 2012, 4:37 PM
 */
#include "walley_function.h"
//#########################################################################################
//#########################################################################################
//#########################################################################################
void writeVarNameAndVarValueIntoAppointedFile(char *file_name,char *var_name,char *var_value,char *var_value_type) {
    char *str_in_wy = getStringFromFile(file_name);

    FILE *fp = fopen(file_name, "w");
    char input_message[1000] = "";
    strcat(input_message, var_name);
    strcat(input_message, ":");
    strcat(input_message, var_value);
    strcat(input_message, ":");
    strcat(input_message, var_value_type);
    strcat(input_message, ":");
    strcat(input_message, "\n");
    printf("Input Message is %s\n", input_message);
    fputs(str_in_wy, fp);
    fputs(input_message, fp);
    fclose(fp);
}
void writeVarNameAndVarValueIntoFile(char *var_name,char *var_value,char *var_value_type) {
    /*
    char *str_in_wy = getStringFromFile("__walley__.wy");

    FILE *fp = fopen("__walley__.wy", "w");
    char input_message[1000] = "";
    strcat(input_message, var_name);
    strcat(input_message, ":");
    strcat(input_message, var_value);
    strcat(input_message, ":");
    strcat(input_message, var_value_type);
    strcat(input_message, "\n");
    printf("Input Message is %s\n", input_message);
    fputs(str_in_wy, fp);
    fputs(input_message, fp);
    fclose(fp);**/
    writeVarNameAndVarValueIntoAppointedFile("__walley__.wy",var_name,var_value,var_value_type);
}
//#########################################################################################
//#########################################################################################
//#########################################################################################

bool checkWhetherSameFunctionNameExists(char *function_name){
    FILE *fp;
    char ch;
    char arr[1000]="";
    bool has_same_func_name=FALSE;
    if ((fp = fopen("__walley_function__.wy", "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
      //  printf("Function checkWhetherSameFunctionNameExists Find file\n");
    //}
    char *var_name_in_file="";
    while ((fgets(arr, 1000, fp)) != NULL) {
        if(find(arr,":")==-1)
            continue;
        var_name_in_file=substr(arr,0,find(arr,":"));
        if (strcmp(var_name_in_file,function_name)==0){
            has_same_func_name=TRUE;
            break;
        }
    }
    fclose(fp);
    return has_same_func_name;
}



//#########################################################################################
//#########################################################################################
//#########################################################################################
void changeTheVarValueFromItsInitialOneFromFile(char *file_name,char *var_name,char *var_value, char *var_value_type){
    //printf("1---------------\n%s---------------\n",getStringFromFile(file_name));
    //printf("Function changeTheVarValueFromItsInitialOneFromFile\nfile name %s\nvar_name %s\nvar_value %s\nvar_value_type %s\n",file_name,var_name,var_value,var_value_type);
    FILE *fp;
    char ch;
    char arr[1000]="";
    char output[10000]="";
    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
      //  printf("Find file %s\n",file_name);
    //}
    
    while ((fgets(arr, 1000, fp)) != NULL) {
        //printf("arr is :%s\n",arr);
        if(find(arr,":")==-1){
            strcat(output, arr);
            continue;
        }
        char *var_name_in_file=substr(arr,0,find(arr,":"));
        if (strcmp(var_name_in_file, var_name) == 0) {
            strcat(output, var_name);
            strcat(output, ":");
            strcat(output, var_value);
            strcat(output, ":");
            strcat(output, var_value_type);
            strcat(output, ":");
            strcat(output, "\n");
     
        } else {
            strcat(output, arr);
        }
    }
    //printf("1 Input Message is %s\n", output);
    fclose(fp);
    fp=fopen(file_name, "w");
    fputs(output,fp);
    fclose(fp);
    //printf("2 Input Message is %s\n", output);
}



void changeTheVarValueFromItsInitialOne(char *var_name,char *var_value, char *var_value_type){
    /*
    FILE *fp;
    char ch;
    char arr[1000]="";
    char output[1000]="";
    if ((fp = fopen("__walley__.wy", "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
      //  printf("Find file\n");
    //}
    char *var_name_in_file="";
    while ((fgets(arr, 1000, fp)) != NULL) {
        var_name_in_file=substr(arr,0,find(arr,":"));
        if (strcmp(var_name_in_file, var_name) == 0) {
            strcat(output, var_name);
            strcat(output, ":");
            strcat(output, var_value);
            strcat(output, ":");
            strcat(output, var_value_type);
            strcat(output, "\n");
     
        } else {
            strcat(output, arr);
        }
    }
    fclose(fp);
    fp=fopen("__walley__.wy", "w");
    fputs(output,fp);
    fclose(fp);
    printf("Input Message is %s\n", output);*
     */
    changeTheVarValueFromItsInitialOneFromFile("__walley__.wy",var_name,var_value,var_value_type);
}
//#########################################################################################
//#########################################################################################
//#########################################################################################


void writeFunctionIntoFile(char *func_name,char *func_param_str) {
    char *str_in_wy = getStringFromFile("__walley_function__.wy");

    FILE *fp = fopen("__walley_function__.wy", "w");
    char input_message[1000] = "";
    strcat(input_message, func_name);
    strcat(input_message, ":");
    strcat(input_message, func_param_str);
    strcat(input_message, ":");
    //strcat(input_message, var_value_type);
    strcat(input_message, "\n");
    printf("Input Function is %s\n", input_message);
    fputs(str_in_wy, fp);
    fputs(input_message, fp);
    fclose(fp);
}

void changeFunctionFromItsInitialOne(char *func_name,char *func_param_str){
    FILE *fp;
    char ch;
    char arr[1000]="";
    char output[1000]="";
    if ((fp = fopen("__walley_function__.wy", "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
      //  printf("Find file\n");
    //}
    char *func_name_in_file="";
    while ((fgets(arr, 1000, fp)) != NULL) {
        func_name_in_file=substr(arr,0,find(arr,":"));
        if (strcmp(func_name_in_file, func_name) == 0) {
            strcat(output, func_name);
            strcat(output, ":");
            strcat(output, func_param_str);
            //strcat(output, ":");
            //strcat(output, var_value_type);
            strcat(output, "\n");
     
        } else {
            strcat(output, arr);
        }
    }
    fclose(fp);
    //printf("Output is %s\n",output);
    fp=fopen("__walley_function__.wy", "w");
    fputs(output,fp);
    fclose(fp);
    printf("Input Function is %s\n", output);
}

/* write a=6,b=3 into file*/
/* write a=6,b=3 into file*/
void writeFunctionParameterOneByOneToFile(char *func_param_str){
    printf("Now Run Function writeFunctionParameterOneByOneToFile\n");
    if(strcmp("None",func_param_str)==0){
        printf("This function has no parameters\n");
        //writeStringToFile("__walley_function__.wy","#### Finish Initialize Parameters ####\n");
    } else {
        char *temp=malloc(sizeof(char)*((int)strlen(func_param_str)+1));
        strcat(temp,func_param_str);
        strcat(temp,",");
        func_param_str=temp;
        
        while(count_str(func_param_str,",")>0){
            char *param=substr(func_param_str,0,find(func_param_str,","));
            char *temp_temp;
            if(find(param,"=")==-1){
                temp_temp=malloc(sizeof(char)*((int)strlen(param)+2));
                strcat(temp_temp,param);
                strcat(temp_temp,"=\n");
            }
            else{
                temp_temp=malloc(sizeof(char)*((int)strlen(param)+1));
                strcat(temp_temp,param);
                strcat(temp_temp,"\n");
            }
             
            writeStringToFile("__walley_function__.wy",temp_temp);
            func_param_str=substr(func_param_str,find(func_param_str,",")+1,(int)strlen(func_param_str));
        }
        //writeStringToFile("__walley_function__.wy","#### Finish Initialize Parameters ####\n");
        
    }
    
}

/*
void writeFunctionParameterOneByOneToFile(char *func_param_str){
    
    if(strcmp("None",func_param_str)==0){
        printf("This function has no parameters\n");
    } else {
        printf("----Function Parameters String is %s----\n",func_param_str);
        char *temp=malloc(sizeof(char)*((int)strlen(func_param_str)+1));
        strcat(temp,func_param_str);
        strcat(temp,",");
        temp=replace(temp,",","=,");

        func_param_str=temp;
        printf("----Function Parameters String is %s----\nLength is %d\n",func_param_str,(int)strlen(func_param_str));
        
        while(count_str(func_param_str,",")>0){
            printf("func_param_str now is %s\n",func_param_str);
            char *param=substr(func_param_str,0,find(func_param_str,","));
            //char *temp_temp=malloc(sizeof(char)*((int)strlen(param)+2));
            char *temp_temp=malloc(sizeof(char)*((int)strlen(param)+2));
            strcat(temp_temp,param);
            
            //strcat(temp_temp, "=\n");
            strcat(temp_temp, "\n");
            temp_temp = removeAheadSpace(temp_temp);
            temp_temp = removeBackSpace(temp_temp);
            printf("----Temp is %s----\n", temp_temp);
            printf("func_param_str now is %s\n",func_param_str);
            writeStringToFile("__walley_function__.wy",temp_temp);
            printf("func_param_str now is %s\n",func_param_str);
            func_param_str=substr(func_param_str,find(func_param_str,",")+1,(int)strlen(func_param_str));
            printf("func_param_str now is %s\n",func_param_str);
            //free(temp_temp);
            //free(param);
            
            if (count_str(func_param_str, ",") == 1) {
                printf("----Only one para left---- \n");
                printf("----para %s----\n", func_param_str);
                char *param = substr(func_param_str, 0, find(func_param_str, ","));
                //char *temp_temp = malloc(sizeof (char) *((int) strlen(param) + 2));
                char *temp_temp=malloc(sizeof(char)*((int)strlen(param)+1));
                strcat(temp_temp, param);
                //strcat(temp_temp, "=\n");
                strcat(temp_temp, "\n");
                temp_temp=removeAheadSpace(temp_temp);
                temp_temp=removeBackSpace(temp_temp);
                printf("----Temp is %s----\n",temp_temp);
                writeStringToFile("__walley_function__.wy", temp_temp);
                free(temp_temp);
                break;
            
        }
        
    }
    printf("----Finish Running function writeFunctionParameterOneByOneToFile----\n");
}
 * **/
/*
char* putKnownVariableIntoExpression(char *input_str){
        printf("Run putKnownVariableIntoExpression\n");
    //bool done=FALSE;
    int from_index = 0;
    
    bool all_var_are_string=TRUE;
    
    int var_num=0;
    
    while (stringHasAlphaExceptAlphaInString(input_str)) {
        char* var_name = findVarNameFromStringFromIndex(input_str, from_index);

        FILE *fp;
        char ch;
        char arr[1000]="";
        
        if ((fp = fopen("__walley__.wy", "r")) == NULL) {
            perror("File open error!\n");
            exit(1);
        } //else {
            //printf("Find file\n");
        //}
        //char *var_name_in_file="";
        bool find_required_var_name=FALSE;

        while ((fgets(arr, 1000, fp)) != NULL) {
            
            if (strcmp(var_name, substr(arr, 0, find(arr, ":"))) == 0) {
                find_required_var_name=TRUE;
                
                var_num+=1;
                
                char *var_value = substr(arr, find(arr, ":") + 1, find_from_index(arr,":",find(arr, ":") + 1));
                char *var_type = substr(arr, find_from_index(arr,":",find(arr, ":") + 1), (int)strlen(arr));
                
                if(strcmp(var_type,"string")!=0)
                    all_var_are_string=FALSE;
                
                char *temp = malloc(sizeof (char) *(int) strlen(input_str));
               
                strcat(temp, substr(input_str, 0, find(input_str, var_name)));
                strcat(temp, var_value);
                strcat(temp, substr(input_str, find(input_str, var_name)+(int) strlen(var_name), (int) strlen(input_str)));
                
                from_index = find(input_str, var_name)+(int) strlen(var_value);

                input_str = temp;
                printf("after temp, input_str is %s\nfrom index is %d\nvariable_name is %s\n", input_str,from_index,var_name);
                
            }        
        }
        if(find_required_var_name==FALSE){
            printf("Mistake occurred while calling function: Walley_Eval_With_Variable\nUnseen var_name %s appeared\n",var_name);
            exit(1);
        }
        
        fclose(fp);
    }
    printf("------ %s\n",input_str);
    return input_str;
}**/

/*
 * clean up file
 * to make sentences in order
 *  |
 *  |
 *  V
 */

void cleanWalleyLanguageFile(char *file_name){
    //printf("file_name is %s\n",file_name);
    FILE *fp=fopen(file_name, "r");
    char arr[10000];
    if (fp==NULL) {
        printf("No File %s Found\n",file_name);
        exit(0);
    }
    
    char *string_in_file[10000];
    int count=0;
    
    while (fgets(arr, 10000, fp)!=NULL) {
        //printf("--->%s count-->%d\n",arr,count);
        char *to_copy;
        if (arr[(int)strlen(arr)-1]=='\n') {
            to_copy=substr(arr, 0, (int)strlen(arr)-1);
        }else {
            to_copy=substr(arr, 0, (int)strlen(arr));
        }
        if (stringIsEmpty(to_copy)==TRUE) {
            continue;
        }
        string_in_file[count]=to_copy;
        count++;
    }
    fclose(fp);
    while (TRUE) {
        int i=0;
        bool can_exit=TRUE;
        for (i=0; i<count-1; i++) {
            if (strcmp(string_in_file[i], string_in_file[i+1])>0) {
                can_exit=FALSE;
            }
        }
        if (can_exit==TRUE) {
            break;
        }
        // Clean
        else{
            for (i=0; i<count-1; i++) {
                if (strcmp(string_in_file[i], string_in_file[i+1])>0) {
                    char *temp=string_in_file[i];
                    string_in_file[i]=string_in_file[i+1];
                    string_in_file[i+1]=temp;
                }
            }
        }
    }
    printf("Finish Clean Up\n");
    int i=0;
    fp=fopen(file_name, "w");
    for (i=0; i<count; i++) {
        //printf("%s\n",string_in_file[i]);
        fputs(string_in_file[i], fp);
        fputs("\n", fp);
    }
    fclose(fp);
    
}
