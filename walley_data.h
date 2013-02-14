//
//  walley_data.h
//  CPractice
//
//  Created by shd101wyy on 12-10-17.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

#include "walley_string.h"

struct VAR{
    char *var_name;
    char *var_value;
    char *var_type;
};

void Var_PrintVar(struct VAR *struct_var){
    int row=0;
    int length=0;
    if (strcmp((struct_var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Var_PrintVar..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((struct_var)->var_value);
    }
    while (row<length) {
        printf("%s:%s:%s:\n",struct_var[row].var_name,struct_var[row].var_value,struct_var[row].var_type);
        row++;
    }
}

void Var_initVar(struct VAR **var){
    *var=(struct VAR*)malloc(sizeof(struct VAR)*1);
    (*var)->var_name="__size_of_array__";
    (*var)->var_value="1";
    (*var)->var_type="int";
}
void Var_addProperty(struct VAR **var,char *var_name, char *var_value, char *var_type){
    
    int length=0;
    if (strcmp((*var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Var_addProperty..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((*var)->var_value);
    }
    
    (*var)->var_value=intToCString(1+atoi((*var)->var_value));
    
    *var=(struct VAR*)realloc(*var, sizeof(struct VAR)*(length+1));
    (*var+length)->var_name=var_name;
    (*var+length)->var_type=var_type;
    (*var+length)->var_value=var_value;    
}
int Var_Existed(struct VAR var[], char *var_name){
    int existed=0;
    int i=0;
    int length=0;
    if (strcmp((var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Var_Existed..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((var)->var_value);
    }

    while (i<length) {
    
        if (strcmp(var[i].var_name,var_name)==0) {
            existed=1;
            break;
        }
        i=i+1;
    }
    return existed;
}

void Var_removeVar(struct VAR **var, char *remove_var_name){
    
    
    int length=0;
    if (strcmp((*var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Var_removeVar..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((*var)->var_value);
    }
    
    
    int i=0;
    int find_var=0;
    int remove_num=0;
    bool is_deleting_list_or_dict=FALSE;
    
    
    char *delete_var_type="";
    char *delete_var_name="";
    
    
    while (i<length) {
        if (find_var==1) {
            if(is_deleting_list_or_dict==TRUE&&strcmp(delete_var_type, "list")==0){
                char *temp_var_name=(*var+i)->var_name;
                int index_of=find(temp_var_name,"[");
                if(index_of!=-1){
                    char *ahead=substr(temp_var_name, 0, index_of);
                    if (strcmp(ahead, delete_var_name)==0) {
                        remove_num+=1;
                        (*var+i)->var_name=NULL;
                        (*var+i)->var_value=NULL;
                        (*var+i)->var_type=NULL;
                        i++;
                        continue;
                    }
                    else{
                        is_deleting_list_or_dict=FALSE;
                    }
                }
                else{
                    is_deleting_list_or_dict=FALSE;
                }
            }
            else if(is_deleting_list_or_dict==TRUE && strcmp(delete_var_type, "dictionary")==0){
                char *temp_var_name=(*var+i)->var_name;
                int index_of=find(temp_var_name,"{");
                if(index_of!=-1){
                    char *ahead=substr(temp_var_name, 0, index_of);
                    if (strcmp(ahead, delete_var_name)==0) {
                        remove_num+=1;
                        (*var+i)->var_name=NULL;
                        (*var+i)->var_value=NULL;
                        (*var+i)->var_type=NULL;
                        i++;
                        continue;
                    }
                    else{
                        is_deleting_list_or_dict=FALSE;
                    }
                }
                else{
                    is_deleting_list_or_dict=FALSE;
                }
            }
            else{
                is_deleting_list_or_dict=FALSE;
            }
            
            if(is_deleting_list_or_dict==FALSE){
            
                (*var+i-remove_num)->var_name=(*var+i)->var_name;
                (*var+i-remove_num)->var_type=(*var+i)->var_type;
                (*var+i-remove_num)->var_value=(*var+i)->var_value;
                i++;
            }
            continue;
            
            
        }
        if (strcmp((*var+i)->var_name,remove_var_name)==0) {
            find_var=1;
            remove_num+=1;
            if (strcmp((*var+i)->var_type, "dictionary")==0||strcmp((*var+i)->var_type, "list")==0) {
                is_deleting_list_or_dict=TRUE;
                delete_var_name=(*var+i)->var_name;
                delete_var_type=(*var+i)->var_type;
            }
        }
        i=i+1;
    }
    if (find_var==1) {
       
        //(*var+length-remove_num)->var_name=NULL;
        //(*var+length-remove_num)->var_type=NULL;
        //(*var+length-remove_num)->var_value=NULL;
        int a=length-remove_num;
        for (; a<length; a++) {
            (*var+a)->var_name=NULL;
            (*var+a)->var_type=NULL;
            (*var+a)->var_value=NULL;
        }
        *var=(struct VAR*)realloc(*var, sizeof(struct VAR)*(length-remove_num));
        (*var)->var_value=intToCString(atoi((*var)->var_value)-remove_num);
    }
       
}

void Var_changeValueOfVar(struct VAR *var, char *var_name, char *var_value, char *var_type){
    int i=0;
    int length=0;
    if (strcmp((var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((var)->var_value);
    }
    
    while (i<length) {
        if (strcmp((var+i)->var_name,var_name)==0) {
            (var+i)->var_value=var_value;
            (var+i)->var_type=var_type;
            break;
        }
        i=i+1;
    }
}

char *Var_getValueOfVar(struct VAR *var, char *var_name){
    
    if (strcmp(var_name, "None")==0) {
        return "None";
    }
    
    int i=0;
    int length=0;
    if (strcmp((var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Var_getValueOfVar..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((var)->var_value);
    }
    
    while (i<length) {
        if (strcmp(var[i].var_name,var_name)==0) {
            return var[i].var_value;
        }
        i=i+1;
    }

    
    
    printf("Undefined var |%s|\n",var_name);
    exit(0);
    return var_name;
}



