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
        printf("Var_addProperty..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((*var)->var_value);
    }
    
    (*var)->var_value=intToCString(1+atoi((*var)->var_value));
    
    *var=realloc(*var, sizeof(struct VAR)*(length+1));
    (*var+length)->var_name=var_name;
    (*var+length)->var_type=var_type;
    (*var+length)->var_value=var_value;    
}
int Var_Existed(struct VAR var[], char *var_name){
    int existed=0;
    int i=0;
    int length=0;
    if (strcmp((var)->var_name,"__size_of_array__")!=0) {
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
        printf("Var_removeVar..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((*var)->var_value);
    }
    
    
    int i=0;
    int find_var=0;
    
    while (i<length) {
        if (find_var==1) {
            (*var+i-1)->var_name=(*var+i)->var_name;
            (*var+i-1)->var_type=(*var+i)->var_type;
            (*var+i-1)->var_value=(*var+i)->var_value;
            i++;
            continue;
        }
        if (strcmp((*var+i)->var_name,remove_var_name)==0) {
            find_var=1;
        }
        i=i+1;
    }
    if (find_var==1) {
       
        (*var+length-1)->var_name=NULL;
        (*var+length-1)->var_type=NULL;
        (*var+length-1)->var_value=NULL;
        *var=realloc(*var, sizeof(struct VAR)*(length-1));
        (*var)->var_value=intToCString(atoi((*var)->var_value)-1);
    }
    
}

void Var_changeValueOfVar(struct VAR *var, char *var_name, char *var_value, char *var_type){
    int i=0;
    int length=0;
    if (strcmp((var)->var_name,"__size_of_array__")!=0) {
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
    int i=0;
    int length=0;
    if (strcmp((var)->var_name,"__size_of_array__")!=0) {
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
    //return "None";
    return var_name;
}



