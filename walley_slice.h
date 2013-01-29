/* 
 * File:   walley_slice.h
 * Author: shd101wyy
 *
 * Created on September 21, 2012, 4:03 PM
 */

#include "walley_embed_function_library.h"

/*
 * x="Hello"
 * x[0,2]="Hel"   1
 * x[0,2)="He"    2
 * x(0,2]="el"    3
 * x(0,2)="e"     4
 * 
 */
/*
 * sliceIncludeBothSide("'hello'",0,2)--->"'hel'"
 */
char *sliceIncludeBothSides(char *input_str,int left,int right){
   //// printf("#### sliceIncludeBothSides ####\n");
   //// printf("|%s|  |%d|  |%d|\n",input_str,left,right);
    input_str=trim(input_str);
    if(strcmp("string",variableValueType(input_str))==0){
        //printf("it is string\n");
        input_str=toCString(input_str);
        char *output=substr(input_str,left,right+1);
        return toString(output);
    }
    else if(strcmp("list",variableValueType(input_str))==0){
        //printf("it is list\n");
        char output[10000]="";
        int i=left;
        //int num = valueNumOfList(input_str);
        strcpy(output, "[");
        for (i = left; i <= right; i++) {
            //char temp[100];
            //sprintf(temp, "%d", i);
            char *temp=intToCString(i);
            
            char *index_str = (char*)malloc(sizeof (char) *(3 + (int) strlen(temp)));
            strcpy(index_str, "[");
            strcat(index_str, temp);
            strcat(index_str, "]");
            index_str[2+ (int) strlen(temp)] = 0;
            //printf("->%s\n", index_str);
            char *value_at_index = valueOfListAtIndexString(input_str, index_str);
            strcat(output, value_at_index);
            if (i != right) {
                strcat(output, ",");
            }
        }
        strcat(output, "]");
        char *output2 = (char*)malloc(sizeof (char) *((int) strlen(output) + 1));
        for (i = 0; i < (int) strlen(output); i++) {
            output2[i] = output[i];
        }
        output2[(int) strlen(output)] = 0;
        return output2;
    } else {
        printf("Mistake occurred while calling function sliceIncludeBothSides\nOnly support list and string now");
        exit(0);
    }
}

char *sliceNotIncludeBothSides(char *input_str, int left, int right) {
    return sliceIncludeBothSides(input_str, left + 1, right - 1);
}

char *sliceOnlyIncludeLeftSide(char *input_str, int left, int right) {
    return sliceIncludeBothSides(input_str, left, right - 1);
}

char *sliceOnlyIncludeRightSide(char *input_str, int left, int right) {
    return sliceIncludeBothSides(input_str, left + 1, right);
}

/*
 * slice("[1,2,3,4,5]","[1,2]")--->[2,3]
 */
char *slice(char *input_str, char *slice) {
   //// printf("#### slice ####\n");
   //// printf("|%s| \n|%s|\n",input_str,slice);
    slice = trim(slice);
    char left = slice[0];
    char right = slice[(int) strlen(slice) - 1];
    char *inside = substr(slice, 0 + 1, (int) strlen(slice) - 1);
    //printf("Inside %s\n",inside);
    if (find_not_in_string(inside, ",") != -1) {
        int num1 = atoi(substr(slice, 1, find(slice, ",")));
        int num2 = atoi(substr(slice, find(slice, ",") + 1, right));
        //printf("num1 %d, num2 %d\n",num1,num2);
        if (left == '[' && right == ']') {
            return sliceIncludeBothSides(input_str, num1, num2);
        } else if (left == '[' && right == ')') {
            return sliceOnlyIncludeLeftSide(input_str, num1, num2);
        } else if (left == '(' && right == ')') {
            return sliceNotIncludeBothSides(input_str, num1, num2);
        } else if (left == '(' && right == ']') {
            return sliceOnlyIncludeRightSide(input_str, num1, num2);
        } else {
            printf("Mistake occurred while calling function slice\nIt is not a slice");
            exit(0);
        }
    } else {
        //printf("here\n");
        int num = atoi(substr(slice, 1, right));
        if (strcmp("string", variableValueType(input_str)) == 0) {
            //printf("it is string\n");
            input_str = toCString(input_str);
            char *output = substr(input_str, num, num + 1);
            return toString(output);
        } else if (strcmp("list", variableValueType(input_str)) == 0) {
            char output[10000] = "";
           
            //char temp[100];
            //sprintf(temp, "%d", num);
            char *temp=intToCString(num);
            
            char *index_str =(char*) malloc(sizeof (char) *(3 + (int) strlen(temp)));
            strcpy(index_str, "[");
            strcat(index_str, temp);
            strcat(index_str, "]");
            index_str[2+ (int) strlen(temp)] = 0;
            //printf("->%s\n", index_str);
            char *value_at_index = valueOfListAtIndexString(input_str, index_str);
            strcat(output, value_at_index);


            //strcat(output, "]");
            int i = 0;
            char *output2 =(char*) malloc(sizeof (char) *((int) strlen(output) + 1));
            for (i = 0; i < (int) strlen(output); i++) {
                output2[i] = output[i];
            }
            output2[(int) strlen(output)] = 0;
            return output2;

        }
        else{
            printf("Mistake occurred while calling function slice\nIt is not a slice or value type wrong\n");
            exit(0);
        }
    }

}
/*
 * like python slice
 */
/*
char *old_slice(char *input_str, char *slice){
   //// printf("#### old_slice ####\n");
   //// printf("|%s| \n|%s|\n",input_str,slice);
    slice = trim(slice);
    //char left = slice[0];
    //char right = slice[(int) strlen(slice) - 1];
    char *inside = substr(slice, 0 + 1, (int) strlen(slice) - 1);
    inside=trim(inside);
    //printf("Inside %s\n",inside);
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
            num2=atoi(Walley_Eval(substr(slice, find_not_in_string(slice, ":") + 1, (int)strlen(slice)-1)));
            return sliceOnlyIncludeLeftSide(input_str,num1,num2);
        }
        else if (inside[0]!=':'&&inside[(int)strlen(inside)-1]==':'){
            //char *type=variableValueType(input_str);
            //num1=atoi(substr(slice, 1, find_not_in_string(slice, ":")));
            num1=atoi(Walley_Eval(substr(slice, 1, find_not_in_string(slice, ":"))));
            //num2=Walley_Eval(num2);
            if(strcmp(input_str,"list")==0){
                num2=valueNumOfList(input_str);
            }
            else if (strcmp(input_str,"string")==0){
                num2=(int)strlen(toCString(input_str));
            }
            return sliceOnlyIncludeLeftSide(input_str, num1, num2);
        }
        else {
            //num1 = atoi(substr(slice, 1, find(slice, ":")));
            //num2 = atoi(substr(slice, find(slice, ":") + 1, right));
            num1=atoi(Walley_Eval(substr(slice, 1, find_not_in_string(slice, ":"))));
            num2=atoi(Walley_Eval(substr(slice, find_not_in_string(slice, ":") + 1, (int)strlen(slice)-1)));
            return sliceOnlyIncludeLeftSide(input_str, num1, num2);
        }


    } 
    // x[1,2]
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
    //x[0]
    else {
        //printf("here\n");
        char *num_str = substr(slice, 1, (int)strlen(slice)-1);
        //printf("num_str %s\n",num_str);
        int num=atoi(Walley_Eval(num_str));
            
        if (strcmp("string", variableValueType(input_str)) == 0) {
           //// printf("it is string\n");
           //// printf("num is %d\n",num);
            input_str = toCString(input_str);
            char *output = substr(input_str, num, num + 1);
           //// printf("return is %s\n",toString(output));
            return toString(output);
        } else if (strcmp("list", variableValueType(input_str)) == 0) {
           //// printf("it is list\n");
            char *output = malloc(sizeof(char)*1000);
            
            char *value_at_index = valueOfListAtIndexString(input_str, slice);
            strcpy(output, value_at_index);


            //strcat(output, "]");
            int i = 0;
            char *output2 = malloc(sizeof (char) *((int) strlen(output) + 1));
            for (i = 0; i < (int) strlen(output); i++) {
                output2[i] = output[i];
            }
            output2[(int) strlen(output)] = 0;
            return output2;

        }
        else{
            printf("Mistake occurred while calling function slice\nIt is not a slice or value type wrong\n");
            printf("If you want use dictionary, please try x{'a'} like expression\n");
            exit(0);
        }
    }    
}
*/