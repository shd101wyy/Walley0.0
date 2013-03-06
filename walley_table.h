//
//  walley_table.h
//  Walley
//
//  Created by shd101wyy on 13-1-30.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_dictionary.h"

/*

 ====================================================================
 table:
 
 x=[1,2,3]
 print x[0] --->1
 
 if the content in [] has = in string. then it is a table
 
 x=[1,2,3] translate to x=[[0]=1,[1]=2,[2]=3]
 
 x=[1,2,3,apple=12] translate to x=[[0]=1,[1]=2,[2]=3,["apple"]=12]
 
 print x["apple"] -----> 12
 
 eg
 constant_x=[
 pi=3.1415926,
 g=9.8,
 physics=[
 moon="MOON"
 ]
 ]
 println constant_x
 println constant_x["pi"]
 println constant_x["physics"]["moon"]
 
 output---->
 [["pi"]=3.1415926,["g"]=9.8,["physics"]=[["moon"]="MOON"]]
 3.1415926
 MOON

 ====================================================================

*/

// x=[1,2] ----> [[0]=1,[1]=2]
// x=[1,apple=1] ----> [[0]=1,[apple]=1]
// x=[1,rohit=[age=12,height=60]] ----> [[0]=1,[rohit]=[[age]=12,[height]=160]]
char *Table_formatTable(char *input_str){
    if (stringIsDigit(input_str)||stringIsAlphaAndSlash(input_str)||strcmp(variableValueType(input_str),"table")!=0) {
        return input_str;
    }
    int max_index=0;
    int num_of_element=valueNumOfList(input_str);
    char *output="[";
    int i=0;
    for (; i<num_of_element; i++) {
        char *inside=valueOfListAtIndex(input_str, i);
        if (find_not_in_str_list_dict(inside, "=")==-1) {
            if(inside[0]=='[')
                inside=Table_formatTable(inside);
            output=append(output, append("[", append(intToCString(max_index), append("]=",inside))));
            output=append(output, ",");
            max_index+=1;
        }
        else{
                // apple=12
                // ["apple"]=12
            if(inside[0]=='['){
                char *left=substr(inside,0, find_not_in_string(inside, "="));
                
                // check whether content in [] is string
                if (strcmp(variableValueType(substr(left, 1, find_not_in_string(inside, "=")-1)), "string")!=0&& stringIsDigit(toCString(substr(left, 1, find_not_in_string(inside, "=")-1)))==FALSE) {
                    printf("@@ |%s|\n",CURRENT_INPUT_STR);

printf("Mistakes occurred while formatting a table. The content in %s is not string\nQuit..",left);
                    exit(0);
                }
                
                char *right=substr(inside, find_not_in_string(inside, "=")+1, (int)strlen(inside));

                output=append(output, left);
                if (right[0]=='[') {
                    right=Table_formatTable(right);
                }
                output=append(output, "=");
                output=append(output, right);
                output=append(output, ",");
            }
            else{
                char *left=substr(inside,0, find_not_in_string(inside, "="));
                char *right=substr(inside, find_not_in_string(inside, "=")+1, (int)strlen(inside));
                    if (right[0]=='[') {
                        right=Table_formatTable(right);
                    }
                    
                output=append(output, append("[", append( toString(left),"]=")));
                output=append(output, right);
                output=append(output, ",");
            }
        
        }
    }
    int length_of_output=(int)strlen(output);
    output[length_of_output-1]=']';
    return output;
}


// x=[[0]=1,[1]=3]  valueOfTableAtIndex(x,[1])--->3
char *Table_valueOfTableAtStringIndex(char *input_str,char *string_index){
    char *first_string_index=substr(string_index, 0, find_not_in_string(string_index, "]")+1);
    char *rest_string_index=substr(string_index, find_not_in_string(string_index, "]")+1, (int)strlen(string_index));
    string_index=first_string_index;
    
    string_index=append(string_index, "=");
    int num_of_element=valueNumOfList(input_str);
    int i=0;
    for (; i<num_of_element; i++) {
        char *inside=valueOfListAtIndex(input_str, i);
        if(find(inside,string_index)==0){
            int length_of_string_index=(int)strlen(string_index);
            char *value=substr(inside, length_of_string_index, (int)strlen(inside));
            if (stringIsEmpty(rest_string_index)) {
                return value;
            }
            else{
                return Table_valueOfTableAtStringIndex(value,rest_string_index);
            }
            
        }
        else if(strcmp(variableValueType(input_str), "list")==0){
            return valueOfListAtIndexString(input_str, first_string_index);
        }
    }
    return "None";
}

// x=[[0]=1,[1]=2] [0] exist
bool Table_checkWhetherStringIndexExist(char *input_str, char *string_index){
    if (strcmp(variableValueType(input_str),"list")!=0&&strcmp(variableValueType(input_str),"table")!=0) {
        return FALSE;
    }
    char *first_string_index=substr(string_index, 0, find_not_in_string(string_index, "]")+1);
    char *rest_string_index=substr(string_index, find_not_in_string(string_index, "]")+1, (int)strlen(string_index));
    string_index=first_string_index;
    
    string_index=append(string_index, "=");
    int num_of_element=valueNumOfList(input_str);
    int i=0;
    for (; i<num_of_element; i++) {
        char *inside=valueOfListAtIndex(input_str, i);
        if(find(inside,string_index)==0){
            int length_of_string_index=(int)strlen(string_index);
            char *value=substr(inside, length_of_string_index, (int)strlen(inside));
            if (stringIsEmpty(rest_string_index)) {
                return TRUE;
            }
            else{
                return Table_checkWhetherStringIndexExist(value,rest_string_index);
            }
            
        }
    }
    return FALSE;
}

// [[0]=1,[1]=2] [0] --->1
// [[0]=[[0]=1,[1]=2],[1]=2]  [0][1] ---->12
int Table_indexOfStringIndex(char *input_str, char *string_index){
    char *first_string_index=substr(string_index, 0, find_not_in_string(string_index, "]")+1);
    char *rest_string_index=substr(string_index, find_not_in_string(string_index, "]")+1, (int)strlen(string_index));
    string_index=first_string_index;
    string_index=append(string_index, "=");

    char *temp_input_str=substr(input_str, 1, (int)strlen(input_str)-1);
    
    int index_of_string_index=find_not_in_str_list_dict(temp_input_str, string_index);
    if (index_of_string_index==-1) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

printf("Mistakes occurred while calling function Table_indexOfStringIndex. No index found\n");
        exit(0);
    }
    index_of_string_index+=1;
    if (stringIsEmpty(rest_string_index)) {
        //printf("first %s\nrest %s\n",first_string_index,rest_string_index);
        return index_of_string_index;
    }
    char *value=Table_valueOfTableAtStringIndex(input_str, first_string_index);
    //printf("\nvalue--->%s\nrest_string_index--->%s\n",value,rest_string_index);
    return index_of_string_index+(int)strlen(string_index)+Table_indexOfStringIndex(value, rest_string_index);
}

// [[0]=1,[1]=[[0]=1,[1]=2]]      [1][2]  return 1.  [2] is the second index which is not existed.
//  return the index of string_index that does not exist.
int Table_checkWhichIndexDoesNotExist(char *table, char *string_index){
    char *first_string_index=substr(string_index, 0, find_not_in_string(string_index, "]")+1);
    char *rest_string_index=substr(string_index, find_not_in_string(string_index, "]")+1, (int)strlen(string_index));
    bool first_exist=Table_checkWhetherStringIndexExist(table, first_string_index);
    //printf("exist--->%d\n",first_exist);
    int index_that_does_not_exist=0;
    if (first_exist==TRUE) {
        if (stringIsEmpty(rest_string_index)) {
            return 1;
        }
        index_that_does_not_exist+=1;
        char *value=Table_valueOfTableAtStringIndex(table, first_string_index);
        //printf("value is %s\n",value);
        return index_that_does_not_exist+Table_checkWhichIndexDoesNotExist(value,rest_string_index);
    }
    //
    else{
        return 0;
    }
}

// [0][1] 12 -----> [0]=[[1]=12]
char *Table_formatTableThatDoesNotExist(char *string_index, char *value){
    value=Table_formatTable(value);
    char *first_string_index=substr(string_index, 0, find_not_in_string(string_index, "]")+1);
    char *rest_string_index=substr(string_index, find_not_in_string(string_index, "]")+1, (int)strlen(string_index));
    
    if (stringIsEmpty(rest_string_index)) {
        return append(first_string_index, append("=", value));
    }
    
    char *output=first_string_index;
    output=append(output, "=[");
    output=append(output, Table_formatTableThatDoesNotExist(rest_string_index,value));
    output=append(output, "]");
    return output;
}


char *Table_addValueOrChangeValue(char *table, char *string_index, char *change_to_value){
    int num_of_string_index=count_str_not_in_string(string_index, "[");
    int index_that_does_not_exist=Table_checkWhichIndexDoesNotExist(table, string_index);
    
    // exist.....
    if (index_that_does_not_exist==num_of_string_index) {
        // [[0]=1,[2]=2] #  [0] #  3
        int index_of_last_index=Table_indexOfStringIndex(table, string_index);
        // get 1
        // then index of = is
        int index_of_equal_sign=find_from_index_not_in_string(table,"=",index_of_last_index);
        char *value=Table_valueOfTableAtStringIndex(table, string_index);
        int index_of_comma=index_of_equal_sign+(int)strlen(value)+1;
        table=replace_from_index_to_index(table, value, change_to_value, index_of_equal_sign+1, index_of_comma);
        return Table_formatTable(table);
    }
    else{
        // [[0]=1] # [1] # 2
        if (index_that_does_not_exist==0) {
            char *output=substr(table, 1, (int)strlen(table)-1);
            // [0]=1
            //char *temp=append(string_index, append("=", change_to_value));
            char *temp=Table_formatTableThatDoesNotExist(string_index, change_to_value);
            // temp is [1]=2
            
            if (stringIsEmpty(output)) {
                output=temp;
            }
            else{
                output=append(output, append(",", temp));
            }
            // output is  [0]=1,[1]=2
            output=append("[",append(output, "]"));
           
            return Table_formatTable(output);
        }
        // [[0]=[[0]=1]]  #  [0][1]  #  2
        else{
            int i=0;
            int index_of_last_left=0;
            for (i=0; i<index_that_does_not_exist; i++) {
                index_of_last_left=find_from_index_not_in_string(string_index, "[", index_of_last_left+1);
            }
            // get [1] which is not existed
            // then get available index [0] that exist
            char *string_index_that_exists=substr(string_index, 0, index_of_last_left);
            char *string_index_that_does_not_exist=substr(string_index, index_of_last_left, (int)strlen(string_index));
            
            //printf("1-->%s\n2-->%s\n",string_index_that_exists,string_index_that_does_not_exist);
            
            int index_of_string_index_that_exists=Table_indexOfStringIndex(table, string_index_that_exists);
            int index_of_equal_sign=find_from_index_not_in_string(table,"=",index_of_string_index_that_exists);
            char *value=Table_valueOfTableAtStringIndex(table, string_index_that_exists);
            if (strcmp(variableValueType(value), "table")!=0) {
                printf("@@ |%s|\n",CURRENT_INPUT_STR);
                printf("Can not assign index to a number\n");
                exit(0);
            }
            
            int index_of_comma=index_of_equal_sign+(int)strlen(value)+1;
            
            char *replace_str=value;
            char *with_str=substr(replace_str, 0, (int)strlen(replace_str)-1);
            with_str=append(with_str, ",");
            with_str=append(with_str, Table_formatTableThatDoesNotExist(string_index_that_does_not_exist, change_to_value));
            with_str=append(with_str, "]");
            
            table=replace_from_index_to_index(table, replace_str, with_str, index_of_equal_sign+1, index_of_comma);
            return Table_formatTable(table);

        }
    }
}


void Table_updateTableToStructVar(struct VAR **struct_var,char *var_name, char *var_value){
    if (Var_Existed(*struct_var, var_name)) {
        Var_removeVar(struct_var, var_name);
    }
    var_value=Table_formatTable(var_value);
    Var_addProperty(struct_var, var_name, var_value, "table");
}

















