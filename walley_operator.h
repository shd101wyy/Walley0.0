/* 
 * File:   walley_operator.h
 * Author: shd101wyy
 *
 * Created on August 26, 2012, 1:40 AM
 */
#include "walley_string.h"
#include "math.h"
#include <stdio.h>
bool isSign(char sign){
    bool is_sign=FALSE;
    if(sign=='+'||
            sign=='-'||
            sign=='*'||
            sign=='/'||
            sign=='\\'||
            sign=='%'||
            sign=='^')
        is_sign=TRUE;
    return is_sign;
}

bool isJudgeSign(char sign){
    //printf("input %c\n",sign);
    bool is_sign=FALSE;
    if(sign=='='||
            //sign=='>='||
            //sign=='<='||
            sign=='>'||
            sign=='<'||
            sign=='!'){
            //sign=='^')
        is_sign=TRUE;
    }
    return is_sign;
}
bool isFirstOrderSign(char sign){
    bool is_first_order_sign=FALSE;
    if(
            sign=='*'||
            sign=='/'||
            sign=='\\'||
            sign=='%'||
            sign=='^')
        is_first_order_sign=TRUE;
    return is_first_order_sign;
    
}

bool judge(bool p, bool q, char *condition){
    //printf("#### Judge ####\n");
    //printf("P is %d, Q is %d\n",p,q);
    bool output=FALSE;
    if(strcmp(condition,"and")==0){
        /*  P Q C
         *  1 1 1
         *  1 0 0
         *  0 1 0
         *  0 0 0
         */
        //printf("And\n");
        if(p==TRUE && q==TRUE){
            //printf("1\n");
            output=TRUE;
        }
        else if (p==TRUE && q==FALSE){
            //printf("2\n");
            output=FALSE;
        }
        else if (p==FALSE && q==TRUE){
            //printf("3\n");
            output=FALSE;
        }
        else{
            //printf("4\n");
            output=FALSE;
        }
 
    } else if (strcmp(condition,"or")==0){
        /* P Q C
         * 1 0 1
         * 1 1 1
         * 0 1 1
         * 0 0 0
         */
        //printf("Or\n");
        if(p==TRUE && q==TRUE)
            output=TRUE;
        else if (p==TRUE && q==FALSE)
            output=TRUE;
        else if (p==FALSE && q==TRUE)
            output=TRUE;
        else
            output=FALSE;        
    } else {
        printf("Mistake occurred while calling function Judge\nP is %d, Q is %d, condition is %s\n",p,q,condition);
    }
    //printf("Output---->%d\n",output);
    return output;
}

bool hasSign(char *input_str){
    bool has_sign=FALSE;
    int i=0;
    for(;i<(int)strlen(input_str);i++){
        if(input_str[i]=='*'||input_str[i]=='/'||input_str[i]=='\\'||input_str[i]=='^'||input_str[i]=='%'||input_str[i]=='+'||input_str[i]=='-'){
            has_sign=TRUE;
        }
    }
    return has_sign;   
}

// Did not consider when sign is in string
bool hasJudgeSign(char *input_str){
    bool has_sign=FALSE;
    if(find(input_str,"==")!=-1)
        has_sign=TRUE;
    else if(find(input_str,"!=")!=-1)
        has_sign=TRUE;
    else if(find(input_str,">")!=-1)
        has_sign=TRUE;
    else if(find(input_str,"<")!=-1)
        has_sign=TRUE;
    else if(find(input_str,">=")!=-1)
        has_sign=TRUE;
    else if(find(input_str,"<=")!=-1)
        has_sign=TRUE;
    return has_sign;
}

int indexOfJudgeSignFromIndex(char *input_str, int from_index){
    input_str=substr(input_str,from_index,(int)strlen(input_str));
    int index=-1;
    if(find(input_str,"==")!=-1)
        index=find(input_str,"=");
    else if(find(input_str,"!=")!=-1)
        index=find(input_str,"!=");
    else if(find(input_str,">")!=-1)
        index=find(input_str,">");
    else if(find(input_str,"<")!=-1)
        index=find(input_str,"<");
    else if(find(input_str,">=")!=-1)
        index=find(input_str,">=");
    else if(find(input_str,"<=")!=-1)
        index=find(input_str,"<=");
    else 
        index=-1;
    return index;
                
    
}



//check whether * / \ ^ % is in input_str
bool hasFirstOrderSignExist(char *input_str){
    bool has_sign=FALSE;
    int i=0;
    for(;i<(int)strlen(input_str);i++){
        if(input_str[i]=='*'||input_str[i]=='/'||input_str[i]=='\\'||input_str[i]=='^'||input_str[i]=='%'){
            has_sign=TRUE;
        }
    }
    return has_sign;
}

double Walley_Operator(double num1,double num2,char sign){
    double output=0;
    if (sign == '*') {
        output = num1*num2;
    } else if (sign == '/') {
        output = num1 / num2;
    } else if (sign == '\\') {
            output = num2 / num1;
    } else if (sign == '%'){
        output=(int)num1%(int)num2;
    } else if (sign == '^'){
        output=pow(num1,num2);
    } else if (sign == '+') {
        output = num1 + num2;
    } else if (sign == '-') {
        output = num1-num2;
    } else {
        printf("Mistake Occurred while calling function Walley_Operator");
        output=0; 
    }
    return output;
}

char* countFromExpression(char *var_value) {

    if (hasSign(var_value) == FALSE){
        //printf("$$$$$$ %s\n",var_value);
        return var_value;
    }
    else {

        double output;
        char *input = var_value;
        //char sign;

        int i = 0;
        int j = 0;
        int temp = 0;

        double num1;
        double num2;
        double previous_num;
        bool begin = FALSE;

        char *num1_str;
        char *num2_str;


        for (; i < strlen(input); i++) {
            if (isSign(input[i]) == TRUE) {
                num1_str = substr(input, temp, i);
                //printf("sign %c\n",input[i]);
                //printf("num1_str %s\n",num1_str);
                j = i + 1;
                for (; j < (int) strlen(input); j++) {
                    if (isSign(input[j]) == TRUE) {
                        num2_str = substr(input, i + 1, j);
                        break;
                    }
                    if (j == (int) strlen(input) - 1) {
                        num2_str = substr(input, i + 1, j + 1);
                        break;
                    }
                }
                //temp=i;
                num1 = atof(num1_str);
                num2 = atof(num2_str);
                //printf("num1 %f, num2 %f, input[i] %c\n",num1,num2,input[i]);
                if (begin == FALSE) {
                    previous_num = Walley_Operator(num1, num2, input[i]);
                    output = previous_num;
                    begin = TRUE;
                } else {
                    previous_num = Walley_Operator(previous_num, num2, input[i]);
                    output = previous_num;
                }
            }
        }

        //printf("%f\n", output);
        char output_str[1000];
        sprintf(output_str, "%f", output);
        //printf("$$$$$$ %s\n",var_value);
        //char *output_temp=malloc(sizeof(char)*(int)strlen(output_str));
        //strcat(output,output_str);
        //return output_temp;
        char *output_output=malloc(sizeof(char)*(int)strlen(output_str));
        int a;
        for(a=0;a<(int)strlen(output_str);a++){
            output_output[a]=output_str[a];
        }
        
        //return (char*)output_str;
        return output_output;
    }
}



char *countFirstOrderSignAndChangeTheStrOnlyOnce(char *input_str){
    int i=0;
    int j=0;
    int begin_of_first_num=0;
    int end_of_second_num=(int)strlen(input_str)-1;
    int place_of_first_order_sign;
    
    char *num1_str;
    char *num2_str;
    
    double num1;
    double num2;
    
    for(;i<(int)strlen(input_str);i++){
        if(isdigit(input_str[i])==TRUE){
            continue;
        }
        
        if(input_str[i]=='+'||input_str[i]=='-'){
            begin_of_first_num=i+1;
        }
        
        if(isFirstOrderSign(input_str[i])==TRUE) {
            j = i + 1;
            place_of_first_order_sign=i;
            
            for (; j < (int) strlen(input_str); j++) {
                // I just change this code here 9/17/2012
                if (isSign(input_str[j]) == TRUE && j!=i+1) {
                    end_of_second_num=j-1;
                    break;
                }
                if (j == (int) strlen(input_str) - 1) {
                    end_of_second_num=j;
                    break;
                }
            } 
                    
            //printf("input_str is:%s\n",input_str);
            //printf("begin of num1 is %d\n",begin_of_first_num);
            //printf("end of num2 is %d\n",end_of_second_num);
            
            num1_str=substr(input_str,begin_of_first_num,place_of_first_order_sign);
            num2_str=substr(input_str,place_of_first_order_sign+1,end_of_second_num+1);
            //printf("input_str is:%s\n",input_str);          
            //printf("num1 is %f\nnum2 is %f\n",atof(num1_str),atof(num2_str));
            
            double output=Walley_Operator(atof(num1_str),atof(num2_str),input_str[i]);
            char output_str[500];
            sprintf(output_str,"%f",output);
            //printf("input_str is:%s\n",input_str);
            //printf("output_str is %s\n",output_str);
            char *output_temp=malloc(sizeof(char)*1000);
            //printf("input_str is:%s\n",input_str);
            //printf("input_str is:%s\n",input_str);
            if(begin_of_first_num==0){
                strcat(output_temp,output_str);
                if(end_of_second_num!=(int)strlen(input_str)-1){
                    strcat(output_temp,substr(input_str,end_of_second_num+1,(int)strlen(input_str)));
                }
            }  else  {
                //printf("else\n");
                //printf("input_str :%s",input_str);
                //printf("substr :%s\n",substr(input_str,0,begin_of_first_num));
                strcat(output_temp,substr(input_str,0,begin_of_first_num));
                if(end_of_second_num==(int)strlen(input_str)-1)
                    strcat(output_temp,output_str);
                else{
                    //printf("enter here\n");
                    strcat(output_temp,output_str);                    
                    strcat(output_temp,substr(input_str,end_of_second_num+1,(int)strlen(input_str)));
                }
            }
            input_str=(char*)output_temp;
            break;
        }
    }
    
    //printf("The changed str is %s\n\n\n\n",input_str);
    return input_str;
}


char *eval_simple_str(char *input_str){
    int i=0;
    int j=0;
    
    int place_of_plus_and_minus=0;
    
    double num1;
    double num2;
    
    char *num1_str;
    char *num2_str;
    
    double part_count;
    char part_count_str[1000];
    
    double output;
    char output_str[1000];
    
    int end_of_second_num=(int)strlen(input_str)-1;
    int begin_of_first_num=0;
    
   // for(;i<(int)strlen(input_str);i++){
    while(hasFirstOrderSignExist(input_str)==TRUE){
        input_str=countFirstOrderSignAndChangeTheStrOnlyOnce(input_str);
    }
    return countFromExpression(input_str);
   // return (char*)output_str;
}


