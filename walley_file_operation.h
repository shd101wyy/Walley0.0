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
//#########################################################################################
//#########################################################################################
//#########################################################################################


bool checkWhetherSameFunctionNameExistsFromVar(char *function_name){
    bool has_same_func_name=FALSE;
    char *var_name_in_file="";
    int row=0;
    int length=atoi(FUNCTION[0]);
    while (row<length) {
       // printf("row-->%d\n",row);
        char *arr=FUNCTION[row];
        if(find(arr,":")==-1){
            row++;
            continue;
        }
        var_name_in_file=substr(arr,0,find(arr,":"));
        if (strcmp(var_name_in_file,function_name)==0){
            has_same_func_name=TRUE;
            break;
        }
        row++;
    }
    //fclose(fp);
    return has_same_func_name;
}


void writeFunctionIntoVar(char *func_name,char *func_param_str, char ***to_function_var) {
    
    char input_message[1000] = "";
    strcat(input_message, func_name);
    strcat(input_message, ":");
    strcat(input_message, func_param_str);
    strcat(input_message, ":");
    strcat(input_message, "\n");
    Str_addString(to_function_var, append("",input_message));
}




/* write a=6,b=3 into file*/
/* write a=6,b=3 into file*/
/* write a=6,b=3 into file*/
/* write a=6,b=3 into file*/
// Not modify
void writeFunctionParameterOneByOneToVar(char *func_param_str, char ***function){
    //// printf("Now Run Function writeFunctionParameterOneByOneToFile\n");
    if(strcmp("None",func_param_str)==0){
        //printf("This function has no parameters\n");
        //writeStringToFile("__walley_function__.wy","#### Finish Initialize Parameters ####\n");
        printf("");
    } else {
        func_param_str=append(func_param_str, ",");
        
        while(count_str(func_param_str,",")>0){
            char *param=substr(func_param_str,0,find(func_param_str,","));
            //char *temp_temp;
            if(find(param,"=")==-1){
                Str_addString(function, append(param, "=None\n"));
            }
            else{
                Str_addString(function, append(param, "\n"));
            }
            
            //writeStringToFile("__walley_function__.wy",temp_temp);
            func_param_str=substr(func_param_str,find(func_param_str,",")+1,(int)strlen(func_param_str));
        }
        //writeStringToFile("__walley_function__.wy","#### Finish Initialize Parameters ####\n");
        
    }
    
}


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
   // printf("Finish Clean Up\n");
    int i=0;
    fp=fopen(file_name, "w");
    for (i=0; i<count; i++) {
        //printf("%s\n",string_in_file[i]);
        fputs(string_in_file[i], fp);
        fputs("\n", fp);
    }
    fclose(fp);
    
}



