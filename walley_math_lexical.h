//
//  walley_math_lexical.h
//  Walley
//
//  Created by shd101wyy on 13-2-19.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

//
//  walley_math_lexical.h
//  Walley_MathParse
//
//  Created by shd101wyy on 13-2-14.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_operator_fraction.h"

//
//  walley_lexical.h
//  Walley
//
//  Created by shd101wyy on 13-2-12.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//
/*
struct TOKEN{
    char *TOKEN_CLASS;
    char *TOKEN_STRING;
    int TOKEN_START;
    int TOKEN_END; // |"Hello"|  index of final "
};
void TOKEN_PrintTOKEN(struct TOKEN *token){
    int row=1;
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TOKEN_PrintTOKEN..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((token)->TOKEN_STRING);
    }
    while (row<length) {
        printf("%s:|%s|:\n",token[row].TOKEN_CLASS,token[row].TOKEN_STRING);
        row++;
    }
}

void TOKEN_initTOKEN(struct TOKEN **token){
    *token=(struct TOKEN*)malloc(sizeof(struct TOKEN)*1);
    (*token)->TOKEN_CLASS="__size_of_array__";
    (*token)->TOKEN_STRING="1";
}

void TOKEN_addProperty(struct TOKEN **token,char *token_class, char *token_string, int token_start, int token_end){
    
    int length=0;
    if (strcmp((*token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TOKEN_addProperty..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((*token)->TOKEN_STRING);
    }
    
    (*token)->TOKEN_STRING=intToCString(1+atoi((*token)->TOKEN_STRING));
    
    *token=(struct TOKEN*)realloc(*token, sizeof(struct TOKEN)*(length+1));
    (*token+length)->TOKEN_CLASS=token_class;
    (*token+length)->TOKEN_STRING=token_string;
    (*token+length)->TOKEN_START=token_start;
    (*token+length)->TOKEN_END=token_end;
    
}
*/

//const char W_WHITESPACES[]={' ','\n','\t'};//3
//const char* W_OPERATOR[]={"+","-","**","*","^","/","\\","%"};//8
//const char* W_NUMBER;      1234  12.4
//const char* W_ID;          Hello123
//const char* W_PUNCTUATION;        : , ;
const char W_LEFT_P='(';
const char W_RIGHT_P=')';

char * TOKEN_MATH_analyzeTokenClass(char *token_string){
    if ((int)strlen(token_string)==1) {
        if (token_string[0]==W_LEFT_P) {
            return "W_LEFT_P";
        }
        else if (token_string[0]==W_RIGHT_P)
            return "W_RIGHT_P";
        else{
            
        }
    }
    
    int length=3;
    int i=0;
    int j=0;
    bool is_white_space=TRUE;
    for (j=0; j<(int)strlen(token_string); j++) {
        bool satisfied=FALSE;
        for (i=0; i<length; i++) {
            if (W_WHITESPACES[i]==token_string[j]) {
                satisfied=TRUE;
            }
        }
        if (satisfied==FALSE) {
            is_white_space=FALSE;
            break;
        }
    }
    if (is_white_space) {
        return "W_WHITESPACES";
    }
    
    length=8;
    for (i=0; i<length; i++) {
        if (strcmp(W_OPERATOR[i], token_string)==0) {
            return "W_OPERATOR";
        }
    }
    
    if (stringIsDigit(token_string)) {
        return "W_NUMBER";
    }
    else{
        return "W_ID";
    }
}


//  [1,2,3,[3]]
//  012345678910
//  return 10
/*
int indexOfFinal(char *input_str, int first_index){
    char first_char=input_str[first_index];
    int i=first_index+1;
    int length=(int)strlen(input_str);
    if (first_char=='"') {
        for (; i<length; i++) {
            if (input_str[i]=='"'&&input_str[i-1]!='\\') {
                return i;
            }
        }
    }
    else if(first_char=='\''){
        for (; i<length; i++) {
            if (input_str[i]=='\''&&input_str[i-1]!='\\') {
                return i;
            }
        }
    }
    else if(first_char=='['){
        int left=1;
        int right=0;
        for (; i<length; i++) {
            if (input_str[i]=='['&&charIsInString(input_str, i)==FALSE) {
                left++;
            }
            if (input_str[i]==']'&&charIsInString(input_str, i)==FALSE) {
                right++;
            }
            if (left==right) {
                return i;
            }
        }
        
    }
    // {
    else{
        int left=1;
        int right=0;
        for (; i<length; i++) {
            if (input_str[i]=='{'&&charIsInString(input_str, i)==FALSE) {
                left++;
            }
            if (input_str[i]=='}'&&charIsInString(input_str, i)==FALSE) {
                right++;
            }
            if (left==right) {
                return i;
            }
        }
        
    }
    printf("Error! Can not find the final index of |%s|\n",input_str);
    exit(0);
}
*/

struct TOKEN* Walley_MATH_Lexica_Analysis(char *input_str){
    struct TOKEN *token=NULL;
    TL_initTokenList(&token);
    int length=(int)strlen(input_str);
    int i=0;
    int start=0;
    int end=0;
    char type='b'; // 'i' for id, 'b' for blank 's' sign(operator), 'p' for ()
    
    if (isalpha(input_str[0])||isdigit(input_str[0])) {
        type='i';
    }
    else if(input_str[0]=='('||input_str[0]==')')
        type='p';
    i=1;
    for(;i<length;i++){
        if (type=='i'){
            //if (isalpha(input_str[i])||isdigit(input_str[i])||input_str[i]=='_') {
            if (input_str[i]!=' '&&input_str[i]!='\n'&&input_str[i]!='\t'&&isSign(input_str[i])==FALSE&&input_str[i]!='('&&input_str[i]!=')') {
                continue;
            }
            else{
                end=i;
                char *token_string=substr(input_str, start, end);
                char *token_class=TOKEN_MATH_analyzeTokenClass(token_string);
                TL_addProperty(&token, token_class, token_string,start,end-1);
                start=end;
                
                
                if (isSign(input_str[i])) {
                    type='s';
                }
                else if(input_str[i]=='('||input_str[i]==')'){
                    type='p';
                }
                else{
                    type='b';
                }
            }
        }
        
        else if(type=='b'){
            if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
                continue;
            }
            else{
                end=i;
                char *token_string=substr(input_str, start, end);
                char *token_class=TOKEN_MATH_analyzeTokenClass(token_string);
                TL_addProperty(&token, token_class, token_string,start,end-1);
                start=end;
                if (isSign(input_str[i])) {
                    type='s';
                }
                else if(input_str[i]=='('||input_str[i]==')'){
                    type='p';
                }
                else{
                    type='i';
                }
            }
        }
        
        else if(type=='s'){
            if (isSign(input_str[i])==TRUE) {
                continue;
            }
            else{
                end=i;
                char *token_string=substr(input_str, start, end);
                char *token_class=TOKEN_MATH_analyzeTokenClass(token_string);
                TL_addProperty(&token, token_class, token_string,start,end-1);
                start=end;
                if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
                    type='b';
                }
                else if(input_str[i]=='('||input_str[i]==')'){
                    type='p';
                }
                else{
                    type='i';
                }
            }
        }
        else if(type=='p'){
            end=i;
            char *token_string=substr(input_str, start, end);
            char *token_class=TOKEN_MATH_analyzeTokenClass(token_string);
            TL_addProperty(&token, token_class, token_string,start,end-1);
            start=end;
            if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
                type='b';
            }
            else if(input_str[i]=='('||input_str[i]==')'){
                type='p';
            }
            else if (isSign(input_str[i])) {
                type='s';
            }
            else{
                type='i';
            }
            
            
        }
        
    }
    
    
    
    // final add token
    end=length;
    if (start<end) {
        char *token_string=substr(input_str, start, end);
        char *token_class=TOKEN_MATH_analyzeTokenClass(token_string);
        TL_addProperty(&token, token_class, token_string,start,end-1);
    }
    
    
    return token;
}

/*
int TL_numOfTOKEN_CLASS(struct TOKEN *token,char *token_class){
    int row=0;
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TL_numOfTOKEN_CLASS..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((token)->TOKEN_STRING);
    }
    int num=0;
    while (row<length) {
        if (strcmp(token_class, token[row].TOKEN_CLASS)==0) {
            num++;
        }
        row++;
    }
    return num;
}
*/
// index_of_token_class starts from 0.
/*
struct TOKEN TL_returnTokenAccordingToIndexAndTokenClass(struct TOKEN *token,char *token_class, int index_of_token_class){
    int row=0;
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TL_numOfTOKEN_CLASS..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((token)->TOKEN_STRING);
    }
    int num=-1;
    while (row<length) {
        if (strcmp(token_class, token[row].TOKEN_CLASS)==0) {
            num++;
        }
        if (num==index_of_token_class) {
            return token[row];
        }
        row++;
    }
    
    printf("Mistake occurred whiling calling function TL_returnTokenAccordingToIndexAndTokenClass\nNo token found according to class %s and index %d",token_class,index_of_token_class);
    exit(0);
    
}
*/

/*
int TL_indexOfFirstNoneWhiteSpaceToken(struct TOKEN *token){
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TL_numOfTOKEN_CLASS..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((token)->TOKEN_STRING);
    }
    int row=1;
    while (row<length) {
        if (strcmp(token[row].TOKEN_CLASS, "W_WHITESPACES")!=0) {
            return row;
        }
        row++;
    }
    printf("Error\nCan not find required none-whitespaces token\n");
    exit(0);
}
*/

/*
int TL_length(struct TOKEN *token){
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TL_length..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((token)->TOKEN_STRING);
    }
    
    return length;
}




int TL_numOfNoneWhitespaces(struct TOKEN *token){
    int length=TL_length(token);
    int row=1;
    int num=0;
    while (row<length) {
        if (strcmp(token[row].TOKEN_CLASS, "W_WHITESPACES")!=0) {
            num++;
        }
        row++;
    }
    return num;
}

struct TOKEN *TL_returnTokenListWithoutWhitespaces(struct TOKEN *token){
    struct TOKEN *return_token;
    TOKEN_initTOKEN(&return_token);
    int length=TL_length(token);
    int row=1;
    while (row<length) {
        if (strcmp("WHITESPACES", token[row].TOKEN_CLASS)!=0) {
            TOKEN_addProperty(&return_token, token[row].TOKEN_CLASS, token[row].TOKEN_STRING, token[row].TOKEN_START, token[row].TOKEN_END);
        }
        row++;
    }
    return return_token;
}
*/

