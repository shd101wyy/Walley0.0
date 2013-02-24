//
//  walley_lexical.h
//  Walley
//
//  Created by shd101wyy on 13-2-12.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_string.h"
bool isSign(char sign);
bool isJudgeSign(char sign);

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


const char* W_KEYWORDS[]={"if","elif","else","for","while","switch","case","def","class"};   //12-3=9     ,"syms","global","<@"}; //12
const char W_WHITESPACES[]={' ','\n','\t'};//3
const char* W_OPERATOR[]={"+","-","**","*","^","/","\\","%"};//8
const char* W_JUDGESIGN[]={"<",">","<=",">=","==","!="};//6
const char* W_RELATION[]={"and","or"};//2
//const char* W_NUMBER;      1234  12.4
//const char* W_ID;          Hello123
//const char* W_STRING;      'Hello' "Hello"
//const char* W_DICTIONARY;  {"A":12}
//const char* W_LIST_TABLE;   [1,2,3]  [["a"]=12,[0]=2]
//const char* W_ASSIGNMENT_OPERATOR;  = sign
//const char* W_PUNCTUATION;        : , ;

char * TOKEN_analyzeTokenClass(char *token_string){
    if (strcmp(token_string, ":")==0||strcmp(token_string, ",")==0||strcmp(token_string, ";")==0) {
        return "W_PUNCTUATION";
    }
    if (token_string[0]=='"'||token_string[0]=='\'') {
        return "W_STRING";
    }
    
    if (token_string[0]=='[') {
        return "W_LIST_TABLE";
    }
    
    if (token_string[0]=='{') {
        return "W_DICTIONARY";
    }
    
    if (strcmp(token_string, "=")==0) {
        return "W_ASSIGNMENT_OPERATOR";
    }
    
    int i=0;
    int length=12-3; //W_KEYWORDS
    for (i=0; i<length; i++) {
        if (strcmp(W_KEYWORDS[i], token_string)==0) {
            return "W_KEYWORDS";
        }
    }
    
    length=3;
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
    
    length=6;
    for (i=0; i<length; i++) {
        if (strcmp(W_JUDGESIGN[i], token_string)==0) {
            return "W_JUDGESIGN";
        }
    }
    length=2;
    for (i=0; i<length; i++) {
        if (strcmp(W_RELATION[i], token_string)==0) {
            return "W_RELATION";
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



struct TOKEN* Walley_Lexica_Analysis(char *input_str){
    struct TOKEN *token=NULL;
    TOKEN_initTOKEN(&token);
    int length=(int)strlen(input_str);
    int i=0;
    int start=0;
    int end=0;
    char type='b'; // 'i' for id, 'b' for blank 's' for judge sign or sign(operator),'t' for "" '' [] {} type, 'c' for :
    char t=' ';
    i=1;
    if (isalpha(input_str[0])||isdigit(input_str[0])) {
        type='i';
    }
    if (input_str[0]=='"') {
        type='t';
        t='s'; //string
        int final_index=indexOfFinal(input_str, 0);
        char *token_string=substr(input_str, 0,final_index+1);
        char *token_class=TOKEN_analyzeTokenClass(token_string);
        TOKEN_addProperty(&token, token_class, token_string,0,final_index);
        i=final_index+1;
        start=i;
        
        if (isJudgeSign(input_str[i])||isSign(input_str[i])) {
            type='s';
        }
        else if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
            type='b';
        }
        else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
            type='c';
        else{
            type='i';
        }


    }
    if (input_str[0]=='\'') {
        type='t';
        t='s'; //string
        int final_index=indexOfFinal(input_str, 0);
        char *token_string=substr(input_str, 0,final_index+1);
        char *token_class=TOKEN_analyzeTokenClass(token_string);
        TOKEN_addProperty(&token, token_class, token_string,0,final_index);
        i=final_index+1;
        start=i;
        
        if (isJudgeSign(input_str[i])||isSign(input_str[i])) {
            type='s';
        }
        else if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
            type='b';
        }
        else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
            type='c';
        else{
            type='i';
        }

    }
    if (input_str[0]=='{') {
        type='t';
        t='d'; //dict
        int final_index=indexOfFinal(input_str, 0);
        char *token_string=substr(input_str, 0,final_index+1);
        char *token_class=TOKEN_analyzeTokenClass(token_string);
        TOKEN_addProperty(&token, token_class, token_string,0,final_index);
        i=final_index+1;
        start=i;
        
        if (isJudgeSign(input_str[i])||isSign(input_str[i])) {
            type='s';
        }
        else if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
            type='b';
        }
        else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
            type='c';
        else{
            type='i';
        }

    }
    if (input_str[0]=='[') {
        type='t';
        t='l'; //list or table
        int final_index=indexOfFinal(input_str, 0);
        char *token_string=substr(input_str, 0,final_index+1);
        char *token_class=TOKEN_analyzeTokenClass(token_string);
        TOKEN_addProperty(&token, token_class, token_string,0,final_index);
        i=final_index+1;
        start=i;
        
        if (isJudgeSign(input_str[i])||isSign(input_str[i])) {
            type='s';
        }
        else if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
            type='b';
        }
        else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
            type='c';
        else{
            type='i';
        }

    }
    if (input_str[0]==':') {
        type='c';
    }
    
    for(;i<length;i++){
        if(type=='t'){
            start=i-1;
            int final_index=indexOfFinal(input_str, i-1);
            char *token_string=substr(input_str, i-1, final_index+1);
            char *token_class=TOKEN_analyzeTokenClass(token_string);
            TOKEN_addProperty(&token, token_class, token_string,i-1,final_index);
            i=final_index+1;
            start=i;
            
            if (isJudgeSign(input_str[i])||isSign(input_str[i])) {
                type='s';
            }
            else if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
                type='b';
            }
            else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
                type='c';
            else if(input_str[i]=='"'||input_str[i]=='\''||input_str[i]=='P'||input_str[i]=='[')
                type='t';
            else{
                type='i';
            }
        }
        else if (type=='i'){
            //if (isalpha(input_str[i])||isdigit(input_str[i])||input_str[i]=='_') {
            if (charIsInParenthesis(input_str, i)==TRUE||(input_str[i]!=' '&&input_str[i]!='\n'&&input_str[i]!='\t'&&isJudgeSign(input_str[i])==FALSE&&isSign(input_str[i])==FALSE&&
                input_str[i]!='"'&&input_str[i]!='\''&&input_str[i]!='{'&&input_str[i]!='['
                &&input_str[i]!=':'&&input_str[i]!=','&&input_str[i]!=';')) {
                continue;
            }
            else{
                end=i;
                char *token_string=substr(input_str, start, end);
                char *token_class=TOKEN_analyzeTokenClass(token_string);
                TOKEN_addProperty(&token, token_class, token_string,start,end-1);
                start=end;
                
                
                if (isJudgeSign(input_str[i])||isSign(input_str[i])) {
                    type='s';
                }
                else if (input_str[i]=='"') {
                    type='t';
                    t='s'; //string
                }
                else if (input_str[i]=='\'') {
                    type='t';
                    t='s'; //string
                }
                else if (input_str[i]=='{') {
                    type='t';
                    t='d'; //dict
                }
                else if (input_str[i]=='[') {
                    type='t';
                    t='l'; //list or table
                }
                else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
                    type='c';
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
                char *token_class=TOKEN_analyzeTokenClass(token_string);
                TOKEN_addProperty(&token, token_class, token_string,start,end-1);
                start=end;
                if (isJudgeSign(input_str[i])||isSign(input_str[i])) {
                    type='s';
                }
                else if (input_str[i]=='"') {
                    type='t';
                    t='s'; //string
                }
                else if (input_str[i]=='\'') {
                    type='t';
                    t='s'; //string
                }
                else if (input_str[i]=='{') {
                    type='t';
                    t='d'; //dict
                }
                else if (input_str[i]=='[') {
                    type='t';
                    t='l'; //list or table
                }
                else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
                    type='c';

                else{
                    type='i';
                }
            }
        }
        
        else if(type=='s'){
            if (isSign(input_str[i])==TRUE||isJudgeSign(input_str[i])==TRUE) {
                continue;
            }
            else{
                end=i;
                char *token_string=substr(input_str, start, end);
                char *token_class=TOKEN_analyzeTokenClass(token_string);
                TOKEN_addProperty(&token, token_class, token_string,start,end-1);
                start=end;
                if (input_str[i]==' '||input_str[i]=='\n'||input_str[i]=='\t') {
                    type='b';
                }
                else if (input_str[i]=='"') {
                    type='t';
                    t='s'; //string
                }
                else if (input_str[i]=='\'') {
                    type='t';
                    t='s'; //string
                }
                else if (input_str[i]=='{') {
                    type='t';
                    t='d'; //dict
                }
                else if (input_str[i]=='[') {
                    type='t';
                    t='l'; //list or table
                }
                else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
                    type='c';
                else{
                    type='i';
                }
            }
        }
        
        else if(type=='c'){
            if (input_str[i-1]==';') {
                printf("%s\n",input_str);
                char *temp_str="";
                temp_str=Str_appendSpaceAhead(temp_str, i-1);
                printf("%s^\n",temp_str);
                printf("Error. Walley does not need ; in sentence\n");
                exit(0);
            }
            TOKEN_addProperty(&token, "W_PUNCTUATION", charToString(input_str[i-1]),i-1,i-1);
            start=i;
            if (isJudgeSign(input_str[i])||isSign(input_str[i])) {
                type='s';
            }
            else if (input_str[i]=='"') {
                type='t';
                t='s'; //string
            }
            else if (input_str[i]=='\'') {
                type='t';
                t='s'; //string
            }
            else if (input_str[i]=='{') {
                type='t';
                t='d'; //dict
            }
            else if (input_str[i]=='[') {
                type='t';
                t='l'; //list or table
            }

            else if (input_str[i]==' '||input_str[i]=='\t'||input_str[i]=='\n')
                type='b';
            else if(input_str[i]==':'||input_str[i]==';'||input_str[i]==',')
                type='c';
            else
                type='i';
            
        }
        
        
    }
    
    
    
        // final add token
        end=length;
    if (start<end) {
        char *token_string=substr(input_str, start, end);
        char *token_class=TOKEN_analyzeTokenClass(token_string);
        TOKEN_addProperty(&token, token_class, token_string,start,end-1);
    }

    
        return token;
}

int TOKEN_numOfTOKEN_CLASS(struct TOKEN *token,char *token_class){
    int row=0;
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TOKEN_numOfTOKEN_CLASS..Can not find __size_of_array__");
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

// index_of_token_class starts from 0.
struct TOKEN TOKEN_returnTokenAccordingToIndexAndTokenClass(struct TOKEN *token,char *token_class, int index_of_token_class){
    int row=0;
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TOKEN_numOfTOKEN_CLASS..Can not find __size_of_array__");
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
    
    printf("Mistake occurred whiling calling function TOKEN_returnTokenAccordingToIndexAndTokenClass\nNo token found according to class %s and index %d",token_class,index_of_token_class);
    exit(0);

}


int TOKEN_indexOfFirstNoneWhiteSpaceToken(struct TOKEN *token){
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TOKEN_numOfTOKEN_CLASS..Can not find __size_of_array__");
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

int TOKEN_length(struct TOKEN *token){
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TOKEN_length..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((token)->TOKEN_STRING);
    }

    return length;
}

// Token Errors
void TOKEN_checkError(struct TOKEN *token,char *input_str){
    int length=0;
    if (strcmp((token)->TOKEN_CLASS,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);
        
        printf("TOKEN_PrintTOKEN..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((token)->TOKEN_STRING);
    }

    int num_of_keyword=TOKEN_numOfTOKEN_CLASS(token, "W_KEYWORDS");
    int num_of_W_ASSIGNMENT_OPERATOR=TOKEN_numOfTOKEN_CLASS(token, "W_ASSIGNMENT_OPERATOR");
    
    // Error 1.. More Keywords
    // eg "if if x==1:"
    if (num_of_keyword>1) {
        struct TOKEN more_token=TOKEN_returnTokenAccordingToIndexAndTokenClass(token, "W_KEYWORDS", 1);
        int start=more_token.TOKEN_START;
        printf("%s\n",input_str);
        char *temp_str="";
        temp_str=Str_appendSpaceAhead(temp_str, start);
        printf("%s^\n",temp_str);
        printf("Error. More Keywords |%s| occurred\n",more_token.TOKEN_STRING);
        exit(0);
    }
    
    // Error 2.. Miss :
    // eg "if x==1"
    if (num_of_keyword==1) {
        struct TOKEN final_token=token[length-1];
        if (strcmp(final_token.TOKEN_STRING, ":")!=0) {
            int end=final_token.TOKEN_END+1;
            printf("%s\n",input_str);
            char *temp_str="";
            temp_str=Str_appendSpaceAhead(temp_str, end);
            printf("%s^\n",temp_str);
            printf("Error. Miss |:| at the end of sentence\n");
            exit(0);
        }
    }
    
    // Error 3.. x =
    // eg "x=" miss assigned content
    if (num_of_W_ASSIGNMENT_OPERATOR==1 && strcmp(token[length-1].TOKEN_STRING,"=")==0) {
        int end=token[length-1].TOKEN_END;
        printf("%s\n",input_str);
        char *temp_str="";
        temp_str=Str_appendSpaceAhead(temp_str, end);
        printf("%s^\n",temp_str);
        printf("Error. Miss assigned content after =\n");
        exit(0);
    }
    
    
    // Error 4.. if x=12:
    // = should be ==
    if (num_of_keyword==1 && num_of_W_ASSIGNMENT_OPERATOR>=1) {
        int start=TOKEN_returnTokenAccordingToIndexAndTokenClass(token, "W_ASSIGNMENT_OPERATOR", 0).TOKEN_START;
        printf("%s\n",input_str);
        char *temp_str="";
        temp_str=Str_appendSpaceAhead(temp_str, start);
        printf("%s^\n",temp_str);
        printf("Error. Should not use =\nTry use == instead of = when comparing\n");
        exit(0);
    }
   
    // Error 5.. x=12=34
    if (num_of_W_ASSIGNMENT_OPERATOR>1) {
        int start=TOKEN_returnTokenAccordingToIndexAndTokenClass(token, "W_ASSIGNMENT_OPERATOR", 1).TOKEN_START;
        printf("%s\n",input_str);
        char *temp_str="";
        temp_str=Str_appendSpaceAhead(temp_str, start);
        printf("%s^\n",temp_str);
        printf("Error. More = occurred\n");
        exit(0);
    }
    
    // Error 6.. x=123:
    
    if (num_of_W_ASSIGNMENT_OPERATOR==1) {
        struct TOKEN final_token=token[length-1];
        char *token_class=final_token.TOKEN_CLASS;
        if (strcmp(token_class, "W_STRING")!=0&&
            strcmp(token_class,"W_NUMBER")!=0&&
            strcmp(token_class, "W_DICTIONARY")!=0&&
            strcmp(token_class, "W_LIST_TABLE")!=0&&
            strcmp(token_class, "W_ID")!=0) {
            int start=final_token.TOKEN_START;
            printf("%s\n",input_str);
            char *temp_str="";
            temp_str=Str_appendSpaceAhead(temp_str, start);
            printf("%s^\n",temp_str);
            printf("Error. invalid syntax\n");
            exit(0);
        }
    }
    
}


int TOKEN_numOfNoneWhitespaces(struct TOKEN *token){
    int length=TOKEN_length(token);
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

struct TOKEN *TOKEN_returnTokenWithoutWhitespaces(struct TOKEN *token){
    struct TOKEN *return_token;
    TOKEN_initTOKEN(&return_token);
    int length=TOKEN_length(token);
    int row=1;
    while (row<length) {
        if (strcmp("WHITESPACES", token[row].TOKEN_CLASS)!=0) {
            TOKEN_addProperty(&return_token, token[row].TOKEN_CLASS, token[row].TOKEN_STRING, token[row].TOKEN_START, token[row].TOKEN_END);
        }
        row++;
    }
    return return_token;
}

struct TOKEN *subtoken(struct TOKEN *token, int from_index, int to_index){
    if (from_index<=0) {
        printf("Error.. Token from_index <= 0\n");
        exit(2);
    }
    
    struct TOKEN *output_token;
    int i=from_index;
    for (; i<to_index; i++) {
        TOKEN_addProperty(&output_token, token[i].TOKEN_CLASS, token[i].TOKEN_STRING, token[i].TOKEN_START, token[i].TOKEN_END);
    }
    return output_token;
}

struct TOKEN TOKEN_nextToken(struct TOKEN *token, int index){
    int length=TOKEN_length(token);
    if (index+1==length) {
        struct TOKEN token_temp;
        token_temp.TOKEN_CLASS="None";
        token_temp.TOKEN_STRING="None";
        token_temp.TOKEN_START="None";
        token_temp.TOKEN_END="None";
        return token_temp;
    }
    else
        return token[index+1];
}

void TOKEN_addToken(struct TOKEN **token, struct TOKEN add_token){
    TOKEN_addProperty(token, add_token.TOKEN_CLASS, add_token.TOKEN_STRING, add_token.TOKEN_START, add_token.TOKEN_END);
}

char *TOKEN_toString(struct TOKEN *token){
    int length=TOKEN_length(token);
    int i=1;
    char *output="";
    for (; i<length; i++) {
        output=append(output, token[i].TOKEN_STRING);
    }
    return output;
}
