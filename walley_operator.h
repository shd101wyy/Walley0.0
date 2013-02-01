/*
 * File:   walley_operator.h
 * Author: shd101wyy
 *
 * Created on August 26, 2012, 1:40 AM
 */
#include "walley_settings.h"
char *eval(char *input_str);
char *eval_CalculatePowerAtFirst_with_alpha(char *input_str);
char *eval_for_decimal_with_alpha(char *input_str);
char *eval_simple_str_with_alpha(char *input_str);
char *countFirstOrderSignAndChangeTheStrOnlyOnce_with_alpha(char *input_str);
char *Walley_Operator_with_alpha(char* num1_str,char* num2_str,char sign);
char* countFromExpression_with_alpha(char *var_value);
// 1.00000-->1
//13.00->13
//14--->14
char *cleanDotZeroAfterNum(char *num){
    if (find(num,".")==-1) {
        return num;
    }
    else{
        int length=(int)strlen(num);
        int i=length-1;
        int zero_that_need_to_delete=0;
        for (; i>=0; i--) {
            if (num[i]=='0') {
                zero_that_need_to_delete++;
                continue;
            }
            if (num[i]!='0'||num[i]=='.') {
                break;
            }
        }
        if(zero_that_need_to_delete!=0){
            num=substr(num, 0, length-zero_that_need_to_delete);
        }
        if (num[(int)strlen(num)-1]=='.') {
            num=substr(num, 0, (int)strlen(num)-1);
        }
        return num;
    }
}

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
        output=((int)num1)%((int)num2);
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
        
        if (var_value[0]!='0') {
            if (var_value[0]=='-') {
                var_value=append("0",var_value);
            }else{
                var_value=append("0+", var_value);
            }
            var_value=append(var_value, "+0");
        }
        
        
        double output;
        
        char *my_output_str="";
        
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
        
        //printf("input %s\n",input);
        
        for (; i <(int)strlen(input); i++) {
            if (isSign(input[i]) == TRUE) {
                num1_str = substr(input, temp, i);
                //printf("sign %c\n",input[i]);
                //printf("num1_str %s\n",num1_str);
                j = i + 1;
                int final_place=0; // for a+b+4--->final_place=3
                for (; j < (int) strlen(input); j++) {
                    if (input[i]=='+'&&input[i+1]=='+') {
                        num2_str="1";
                        i++;
                        break;
                    }
                    if (input[i]=='-'&&input[i+1]=='-') {
                        num2_str="1";
                        i++;
                        break;
                    }
                    
                    if (isSign(input[j]) == TRUE) {
                        num2_str = substr(input, i + 1, j);
                        final_place=j;
                        break;
                    }
                    if (j == (int) strlen(input) - 1) {
                        num2_str = substr(input, i + 1, j + 1);
                        final_place=j+1;
                        break;
                    }
                }
                //temp=i;
                //printf("/n Begin %d\n",begin);
                //printf("num1_str %s, num2_str %s, previous_num %s\n",num1_str,num2_str,numToCString(previous_num));
                //printf("my_output_str %s\n",my_output_str);
                
                num1 = atof(num1_str);
                num2 = atof(num2_str);
                //printf("num1 %f, num2 %f, input[i] %c\n",num1,num2,input[i]);
                if (begin == FALSE) {
                    //####################################################
                    // I plan to add new code here\n
                    
                    if(stringIsAlpha(num1_str)){
                        // a+b+3+4
                        if (stringIsAlpha(num2_str)) {
                            my_output_str=append(my_output_str, substr(input, 0, final_place));
                            previous_num=0;
                            output=previous_num;
                            begin=TRUE;
                        }
                        // a+3+4
                        else{
                            my_output_str=append(my_output_str, substr(input, 0, i+1)); // get a+
                            previous_num=num2;
                            output=previous_num;
                            if (input[i]=='-') {
                                previous_num=-previous_num;
                                output=previous_num;
                            }
                            begin=TRUE;
                        }
                    }
                    // num1 is not string while num2 is . like   3+a+4+5
                    else if (stringIsAlpha(num2_str)){
                        my_output_str=append(my_output_str, substr(input, i, final_place));  // get +a
                        previous_num=num1;
                        output=previous_num;
                        begin=TRUE;
                    }
                    
                    else{
                        
                        
                        //#####################################################
                        
                        
                        previous_num = Walley_Operator(num1, num2, input[i]);
                        output = previous_num;
                        begin = TRUE;
                        
                        //my_output_str=append(my_output_str, "+");
                        //my_output_str=append(my_output_str, numToCString(output));
                        
                    }
                }
                // Begin =TRUE
                else {
                    
                    // I add new code here to solve a+3+5 like problem
                    //#####################################################
                    // 3+4+a+5-->7+a+5
                    if (stringIsAlpha(num2_str)) {
                        my_output_str=append(my_output_str, substr(input, i, final_place)); // get +a
                        //previous_num=num1;
                        output=previous_num;
                    }
                    else{
                        //####################################################
                        
                        previous_num = Walley_Operator(previous_num, num2, input[i]);
                        output = previous_num;
                        
                    }
                }
            }
        }
        
        //printf("END %s\n",my_output_str);
        char *temp_output=numToCString(output);
        if (temp_output[0]=='-') {
            my_output_str=append(my_output_str, temp_output);
            
        }
        else{
            my_output_str=append(my_output_str, "+");
            my_output_str=append(my_output_str, temp_output);
            
        }
        my_output_str=cleanDotZeroAfterNum(my_output_str);
        //printf("my_output_str is |%s|\n",my_output_str);
        if (my_output_str[0]=='+') {
            my_output_str=substr(my_output_str, 1, (int)strlen(my_output_str));
        }
        return my_output_str;
        /*
         //printf("%f\n", output);
         char output_str[1000];
         sprintf(output_str, "%f", output);
         //printf("$$$$$$ %s\n",var_value);
         //char *output_temp=malloc(sizeof(char)*(int)strlen(output_str));
         //strcat(output,output_str);
         //return output_temp;
         char *output_output=malloc(sizeof(char)*(int)strlen(output_str));
         int a=0;
         for(a=0;a<(int)strlen(output_str);a++){
         output_output[a]=output_str[a];
         }
         
         //return (char*)output_str;
         return output_output;*/
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
    
    
    
    for(;i<(int)strlen(input_str);i++){
        if(isdigit(input_str[i])){
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
            char *output_temp=(char*)malloc(sizeof(char)*1000);
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

// calculate outside parenthesis
char *eval_simple_str(char *input_str){
    while(hasFirstOrderSignExist(input_str)==TRUE){
        input_str=countFirstOrderSignAndChangeTheStrOnlyOnce(input_str);
    }
    return countFromExpression(input_str);
}



char *eval_CalculatePowerAtFirst(char *input_str){
    int count_of_power=count_str(input_str, "^");
    int i=0;
    for (i=0; i<count_of_power; i++) {
        //printf("enter\n");
        int index_of_power=find(input_str, "^");
        // 2^3 (2)^3 2^(3) (2)^(3)
        int left=0;
        int right=0;
        
        
        // Find Left.
        //(2)^3
        if (input_str[index_of_power-1]==')') {
            int num_of_right=0;
            int num_of_left=0;
            int j=index_of_power-1;
            for (j=index_of_power-1; j>=0; j--) {
                if (input_str[j]==')') {
                    num_of_right++;
                    continue;
                }
                if (input_str[j]=='(') {
                    num_of_left++;
                    if (num_of_left==num_of_right) {
                        left=j;
                        break;
                    }
                    else
                        continue;
                }
            }
            
        }
        //2^3
        else{
            int j=index_of_power-1;
            for (j=index_of_power-1; j>=0; j--) {
                if (isdigit(input_str[j])==FALSE) {
                    left=j+1;
                    break;
                }
                if (j==0) {
                    left=0;
                    break;
                }
            }
            
        }
        
        //2^(3)
        if (input_str[index_of_power+1]=='(') {
            int num_of_left=0;
            int num_of_right=0;
            int j=index_of_power+1;
            for (; j<(int)strlen(input_str); j++) {
                if (input_str[j]=='(') {
                    num_of_left++;
                    continue;
                }
                if (input_str[j]==')') {
                    num_of_right++;
                    if (num_of_left==num_of_right) {
                        right=j;
                        break;
                    }
                    else
                        continue;
                }
            }
        }
        //2^2
        else{
            int j=index_of_power+1;
            for (j=index_of_power+1; j<(int)strlen(input_str); j++) {
                if (isdigit(input_str[j])==FALSE) {
                    right=j-1;
                    break;
                }
                if(j==(int)strlen(input_str)-1){
                    right=(int)strlen(input_str)-1;
                    break;
                }
            }
            
        }
        char *replace_str=substr(input_str, left, right+1);
        char *left_str=substr(input_str, left, index_of_power);
        char *right_str=substr(input_str, index_of_power+1, right+1);
        
        
        left_str=eval(left_str);
        right_str=eval(right_str);
        char *with_str=numToCString(pow(atof(left_str), atof(right_str)));
        with_str=cleanDotZeroAfterNum(with_str);
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, left, right+1);
        
        
    }
    return input_str;
}


// calculate include parenthesis
// This function has some problems now.
// It does not calculate ^ at first
// 2*3^2 should be 18 while it while be 6^2=36..
// I will modify later.
// finish modifying
char *eval(char *input_str){
    //printf("#### eval ####\ninput_str %s\n",input_str);
    
    input_str=trim(input_str);
    input_str=eval_CalculatePowerAtFirst(input_str);
    int count_of_left_bracket=count_str(input_str,"(");
    int count_of_right_bracket=count_str(input_str,")");
    
    //char *output;
    if(count_of_left_bracket!=count_of_right_bracket){
        printf("Mistakes occurred while calling function eval:\nnum of ( != num of )");
        exit(1);
    }
    while(count_str(input_str,"(")!=0){
        int index_of_final_left_bracket=find(input_str, "(");
        int index_of_first_right_bracket=find(input_str, ")");
        while (TRUE) {
            
            int temp=find_from_index(input_str, "(", index_of_final_left_bracket+1);
            if (temp==-1 || temp>index_of_first_right_bracket) {
                break;
            }
            else {
                index_of_final_left_bracket=temp;
            }
            
        }
        char *temp=substr(input_str,0,index_of_final_left_bracket);
        char *part_output=eval_simple_str(substr(input_str,index_of_final_left_bracket+1,index_of_first_right_bracket));
        temp=append(temp,part_output);
        temp=append(temp,substr(input_str,index_of_first_right_bracket+1,(int)strlen(input_str)));
        input_str=temp;
    }
    input_str=eval_simple_str(substr(input_str,0,(int)strlen(input_str)));
    
    
    // Delete 0 after
    int a=(int)strlen(input_str)-1;
    int place=(int)strlen(input_str);
    if (find(input_str, ".") != -1) {
        for (; a >= 0; a--) {
            if (input_str[a] == '0')
                place--;
            else
                break;
        }
    }
    if(place!=(int)strlen(input_str))
        input_str=substr(input_str,0,place);
    if(input_str[(int)strlen(input_str)-1]=='.')
        input_str=substr(input_str,0,(int)strlen(input_str)-1);
    return input_str;
}


char *eval_CalculatePowerAtFirst_with_alpha(char *input_str){
    int count_of_power=count_str(input_str, "^");
    int i=0;
    for (i=0; i<count_of_power; i++) {
        //printf("enter\n");
        int index_of_power=find(input_str, "^");
        // 2^3 (2)^3 2^(3) (2)^(3)
        int left=0;
        int right=0;
        
        
        // Find Left.
        //(2)^3
        if (input_str[index_of_power-1]==')') {
            int num_of_right=0;
            int num_of_left=0;
            int j=index_of_power-1;
            for (j=index_of_power-1; j>=0; j--) {
                if (input_str[j]==')') {
                    num_of_right++;
                    continue;
                }
                if (input_str[j]=='(') {
                    num_of_left++;
                    if (num_of_left==num_of_right) {
                        left=j;
                        break;
                    }
                    else
                        continue;
                }
            }
            
        }
        //2^3
        else{
            int j=index_of_power-1;
            for (j=index_of_power-1; j>=0; j--) {
                if (isdigit(input_str[j])==FALSE&&isalpha(input_str[j])==FALSE&&input_str[j]!='_') {
                    left=j+1;
                    break;
                }
                if (j==0) {
                    left=0;
                    break;
                }
            }
            
        }
        
        //2^(3)
        if (input_str[index_of_power+1]=='(') {
            int num_of_left=0;
            int num_of_right=0;
            int j=index_of_power+1;
            for (; j<(int)strlen(input_str); j++) {
                if (input_str[j]=='(') {
                    num_of_left++;
                    continue;
                }
                if (input_str[j]==')') {
                    num_of_right++;
                    if (num_of_left==num_of_right) {
                        right=j;
                        break;
                    }
                    else
                        continue;
                }
            }
        }
        //2^2
        else{
            int j=index_of_power+1;
            for (j=index_of_power+1; j<(int)strlen(input_str); j++) {
                if (isdigit(input_str[j])==FALSE&&isalpha(input_str[j])==FALSE&&input_str[j]!='_') {
                    right=j-1;
                    break;
                }
                if(j==(int)strlen(input_str)-1){
                    right=(int)strlen(input_str)-1;
                    break;
                }
            }
            
        }
        char *replace_str=substr(input_str, left, right+1);
        char *left_str=substr(input_str, left, index_of_power);
        char *right_str=substr(input_str, index_of_power+1, right+1);
        
        left_str=eval_for_decimal_with_alpha(left_str);
        right_str=eval_for_decimal_with_alpha(right_str);
        char *with_str="";//numToCString(pow(atof(left_str), atof(right_str)));
        // 3^4
        if (stringIsDigit(left_str)&&stringIsDigit(right_str)) {
            with_str=numToCString(pow(atof(left_str), atof(right_str)));
            with_str=cleanDotZeroAfterNum(with_str);
        }
        else{
            with_str=append("(", append(left_str, ")^("));
            with_str=append(with_str, append(right_str, ")"));
        }
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, left, right+1);
        
        
    }
    return input_str;
}


char *changeOperatorToStr(char sign){
    if (sign=='+') {
        return "#add#";
    }
    else if(sign=='-'){
        return "#minus#";
    }
    else if(sign=='*'){
        return "#time#";
    }
    else if(sign=='/'){
        return "#divide#";
    }
    else if(sign=='^'){
        return "#power#";
    }
    else if(sign=='%'){
        return "#percent#";
    }
    else{
        printf("Mistake occurred while calling function changeOperatorToStr\n%c is not sign\n",sign);
        exit(0);
    }
}
char *changeOperatorToStrForWhoStr(char *input_str){
    int i=0;
    char *output="";
    for (; i<(int)strlen(input_str); i++) {
        if (isSign(input_str[i])) {
            output=append(output, changeOperatorToStr(input_str[i]));
        }
        else{
            output=append(output, charToString(input_str[i]));
        }
    }
    return output;
}
char *changeOperatorStrToOriginalForWhoStr(char *input_str){
    input_str=replace(input_str, "#add#", "+");
    input_str=replace(input_str, "#minus#", "-");
    input_str=replace(input_str, "#time#", "*");
    input_str=replace(input_str, "#divide#", "/");
    input_str=replace(input_str, "#power#", "^");
    input_str=replace(input_str, "#percent#", "%");
    return input_str;
}

//calculate 9/2/4--->9/8
char *calculate_for_division_for_decimal(char *input_str){
    char *temp_input_str=changeOperatorStrToOriginalForWhoStr(input_str);
    if (stringIsDigit(temp_input_str)||stringIsFraction(temp_input_str)) {
        return input_str;
    }
    else{
        if (find(temp_input_str, "+")==-1&&find(temp_input_str, "-")==-1&&find(temp_input_str, "*")==-1&&find(temp_input_str, "^")==-1&&find(temp_input_str, "%")==-1) {
            //int num_of_division=count_str(temp_input_str, "/");
            int index_of_temp_input_str=find(temp_input_str, "/");
            char *numerator=substr(temp_input_str, 0, index_of_temp_input_str);
            //int first=index_of_temp_input_str;
            char *denominator=substr(temp_input_str, index_of_temp_input_str+1, (int)strlen(temp_input_str));
            denominator=replace(denominator, "#LEFT#","");
            denominator=replace(denominator, "#RIGHT#", "");
            denominator=replace(denominator, "/", "*");
            denominator=eval_for_decimal_with_alpha(denominator);
            denominator=append("#LEFT#", append(denominator, "#RIGHT#"));
            char *output=append(numerator, append("/", denominator));
            return changeOperatorToStrForWhoStr(output);
        }
        else{
            int index_of_temp_input_str=find(temp_input_str, "/");
            if (index_of_temp_input_str==-1) {
                return input_str;
            }
            else{
                char *numerator=substr(temp_input_str, 0, index_of_temp_input_str);
                //int first=index_of_temp_input_str;
                char *denominator=substr(temp_input_str, index_of_temp_input_str+1, (int)strlen(temp_input_str));
                denominator=replace(denominator, "#LEFT#","");
                denominator=replace(denominator, "#RIGHT#", "");
                denominator=replace(denominator, "/", "*");
                denominator=eval_for_decimal_with_alpha(denominator);
                
                if (stringHasAlpha(denominator)==FALSE&&isdigit(numerator[0])) { // 6*x*x/8
                    char *numerator_num=substr(temp_input_str, 0, find(temp_input_str, "*")); //6
                    char *rest=substr(temp_input_str, find(temp_input_str, "*"),index_of_temp_input_str);//*x*x
                    char *simplified=eval(append(numerator_num, append("/", denominator)));
                    char *output=append(simplified, rest);
                    return changeOperatorToStrForWhoStr(output);
                    
                }
                else{
                    denominator=append("#LEFT#", append(denominator, "#RIGHT#"));
                    //printf("denominator is %s\n",denominator);
                    char *output=append(numerator, append("/", denominator));
                    return changeOperatorToStrForWhoStr(output);
                }
            }
        }
    }
}
// it does not support + and - now
char* Walley_Operator_with_alpha(char* num1_str,char* num2_str,char sign){
    // after running codes..
    // it may have input_str like
    // x#time#3#time#y#divide#4
    
    // or
    // if has alpha like 3*x, then return 3#time#x
    char *output_output="";
    
    bool num1_is_digit=stringIsDigit(num1_str);
    bool num2_is_digit=stringIsDigit(num2_str);
    if (num1_is_digit==TRUE&&num2_is_digit==TRUE) {
        //return cleanDotZeroAfterNum(numToCString(Walley_Operator(atof(num1_str), atof(num2_str), sign)));
        output_output=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof(num1_str), atof(num2_str), sign)));
    }
    else{
        if (find(num1_str, "#")==-1) {
            char *output;
            //always put number ahead...
            //3*x
            if (num1_is_digit==TRUE && num2_is_digit==FALSE) {
                output=append(num1_str, changeOperatorToStr(sign));
                output=append(output, num2_str);
            }
            //x*3
            else if(num1_is_digit==FALSE && num2_is_digit==TRUE){
                if (sign!='^'&&sign!='/') {
                    output=append(num2_str, changeOperatorToStr(sign));
                    output=append(output, num1_str);
                }
                else{
                    output=append(num1_str, changeOperatorToStr(sign));
                    output=append(output, num2_str);
                    
                }
            }
            //x*y
            else{
                output=append(num1_str, changeOperatorToStr(sign));
                output=append(output, num2_str);
                
            }
            //return output;
            output_output=output;
        }
        // x#time#3#time#y/4
        else{
            // num1_str 3#time#x ; num2 x or 3 ; sign *
            if (isdigit(num1_str[0])) {
                if (num2_is_digit) {
                    int index=find(num1_str, "#");
                    char *num=substr(num1_str, 0, index);
                    char *replace_str=num;
                    char *with_str=Walley_Operator_with_alpha(num, num2_str, sign);
                    //return replace_from_index_to_index(num1_str, replace_str, with_str, 0, index+1);
                    output_output=replace_from_index_to_index(num1_str, replace_str, with_str, 0, index+1);;
                }
                else{
                    char *output=append(num1_str, changeOperatorToStr(sign));
                    output=append(output, num2_str);
                    //return output;
                    output_output=output;
                }
                
            }
            else{
                if (num2_is_digit) {
                    if (sign!='^'&&sign!='/') {
                        char *output=append(num2_str, changeOperatorToStr(sign));
                        output=append(output, num1_str);
                        //return output;
                        output_output=output;
                    }
                    else{
                        char *output=append(num1_str, changeOperatorToStr(sign));
                        output=append(output, num2_str);
                        //return output;
                        output_output=output;
                    }
                }
                else{
                    int index=find(num1_str, "#");
                    char *num=substr(num1_str, 0, index);
                    if (strcmp(num, num2_str)==0) {
                        //return replace_from_index_to_index(num1_str, num, "1", 0, index+1);
                        if (sign=='/') {
                            output_output=replace_from_index_to_index(num1_str, num, "1", 0, index+1);
                        }
                        if (sign=='*') {
                            output_output=replace_from_index_to_index(num1_str, num, append(num, append("#time#",num)), 0, index+1);
                            
                        }
                    }
                    else{
                        
                        char *output=append(num1_str, changeOperatorToStr(sign));
                        output=append(output, num2_str);
                        //return output;
                        output_output=output;
                    }
                }
            }
            
        }
    }
    if (sign=='/') {
        output_output=calculate_for_division_for_decimal(output_output);
    }
    return output_output;
    
}

char *countFirstOrderSignAndChangeTheStrOnlyOnce_with_alpha(char *input_str){
    int i=0;
    int j=0;
    int begin_of_first_num=0;
    int end_of_second_num=(int)strlen(input_str)-1;
    int place_of_first_order_sign;
    
    char *num1_str;
    char *num2_str;
    
    for(;i<(int)strlen(input_str);i++){
        if(isdigit(input_str[i])){
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
            num1_str=substr(input_str,begin_of_first_num,place_of_first_order_sign);
            num2_str=substr(input_str,place_of_first_order_sign+1,end_of_second_num+1);
            
            
            char* output_str=Walley_Operator_with_alpha(num1_str,num2_str,input_str[i]);
            
            char *output_temp=(char*)malloc(sizeof(char)*1000);
            
            if(begin_of_first_num==0){
                strcat(output_temp,output_str);
                if(end_of_second_num!=(int)strlen(input_str)-1){
                    strcat(output_temp,substr(input_str,end_of_second_num+1,(int)strlen(input_str)));
                }
            }  else  {
                strcat(output_temp,substr(input_str,0,begin_of_first_num));
                if(end_of_second_num==(int)strlen(input_str)-1)
                    strcat(output_temp,output_str);
                else{
                    strcat(output_temp,output_str);
                    strcat(output_temp,substr(input_str,end_of_second_num+1,(int)strlen(input_str)));
                }
            }
            input_str=(char*)output_temp;
            break;
        }
    }
    
    return input_str;
}

char* countFromExpression_with_alpha(char *var_value) {
    
    if (hasSign(var_value) == FALSE){
        //printf("$$$$$$ %s\n",var_value);
        return var_value;
    }
    else {
        
        if (var_value[0]!='0') {
            if (var_value[0]=='-') {
                var_value=append("0",var_value);
            }else{
                var_value=append("0+", var_value);
            }
            var_value=append(var_value, "+0");
        }
        
        
        double output;
        
        char *my_output_str="";
        
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
        
        for (; i < (int)strlen(input); i++) {
            if (isSign(input[i]) == TRUE) {
                num1_str = substr(input, temp, i);
                //printf("sign %c\n",input[i]);
                //printf("num1_str %s\n",num1_str);
                j = i + 1;
                int final_place=0; // for a+b+4--->final_place=3
                for (; j < (int) strlen(input); j++) {
                    if (input[i]=='+'&&input[i+1]=='+') {
                        num2_str="1";
                        i++;
                        break;
                    }
                    if (input[i]=='-'&&input[i+1]=='-') {
                        num2_str="1";
                        i++;
                        break;
                    }
                    
                    if (isSign(input[j]) == TRUE) {
                        num2_str = substr(input, i + 1, j);
                        final_place=j;
                        break;
                    }
                    if (j == (int) strlen(input) - 1) {
                        num2_str = substr(input, i + 1, j + 1);
                        final_place=j+1;
                        break;
                    }
                }
                //temp=i;
                //printf("/n Begin %d\n",begin);
                //printf("num1_str %s, num2_str %s, previous_num %s\n",num1_str,num2_str,numToCString(previous_num));
                //printf("my_output_str %s\n",my_output_str);
                
                num1 = atof(num1_str);
                num2 = atof(num2_str);
                //printf("num1 %f, num2 %f, input[i] %c\n",num1,num2,input[i]);
                if (begin == FALSE) {
                    //####################################################
                    // I plan to add new code here\n
                    
                    if(stringIsDigit(num1_str)==FALSE){
                        // a+b+3+4
                        if (stringIsDigit(num2_str)==FALSE) {
                            my_output_str=append(my_output_str, substr(input, 0, final_place));
                            previous_num=0;
                            output=previous_num;
                            begin=TRUE;
                        }
                        // a+3+4
                        else{
                            my_output_str=append(my_output_str, substr(input, 0, i+1)); // get a+
                            previous_num=num2;
                            output=previous_num;
                            if (input[i]=='-') {
                                previous_num=-previous_num;
                                output=previous_num;
                            }
                            begin=TRUE;
                        }
                    }
                    // num1 is not string while num2 is . like   3+a+4+5
                    else if (stringIsDigit(num2_str)==FALSE){
                        my_output_str=append(my_output_str, substr(input, i, final_place));  // get +a
                        previous_num=num1;
                        output=previous_num;
                        begin=TRUE;
                    }
                    
                    else{
                        
                        
                        //#####################################################
                        
                        
                        previous_num = Walley_Operator(num1, num2, input[i]);
                        output = previous_num;
                        begin = TRUE;
                        
                        //my_output_str=append(my_output_str, "+");
                        //my_output_str=append(my_output_str, numToCString(output));
                        
                    }
                }
                // Begin =TRUE
                else {
                    
                    // I add new code here to solve a+3+5 like problem
                    //#####################################################
                    // 3+4+a+5-->7+a+5
                    if (stringIsDigit(num2_str)==FALSE) {
                        my_output_str=append(my_output_str, substr(input, i, final_place)); // get +a
                        //previous_num=num1;
                        output=previous_num;
                    }
                    else{
                        //####################################################
                        
                        previous_num = Walley_Operator(previous_num, num2, input[i]);
                        output = previous_num;
                        
                    }
                }
            }
        }
        //printf("END %s\n",my_output_str);
        char *temp_output=numToCString(output);
        if (output!=0) {
            if (temp_output[0]=='-') {
                my_output_str=append(my_output_str, temp_output);
                
            }
            else{
                my_output_str=append(my_output_str, "+");
                my_output_str=append(my_output_str, temp_output);
                
            }
        }
        my_output_str=cleanDotZeroAfterNum(my_output_str);
        //printf("my_output_str is |%s|\n",my_output_str);
        if (my_output_str[0]=='+') {
            my_output_str=substr(my_output_str, 1, (int)strlen(my_output_str));
        }
        return my_output_str;
    }
}


// calculate outside parenthesis
char *eval_simple_str_with_alpha(char *input_str){
    // at this place, eg 3*x+5.
    // I will replace 3*x with 3#time#x    #time# ---> *
    while(hasFirstOrderSignExist(input_str)==TRUE){
        input_str=countFirstOrderSignAndChangeTheStrOnlyOnce_with_alpha(input_str);
    }
    //printf("$$$---> %s\n",input_str);
    // Afte running the above code.
    // input_str maybe like.
    // 3#time#x#time#y+5/3
    return countFromExpression_with_alpha(input_str);
}
//clean_code  1/(4)--->1/4  1/(x+4)--->1/(x+4)
char *clean_math_output_for_decimal(char *input_str){
    int num_of_bracket=count_str(input_str, "(");
    int i=0;
    for (; i<num_of_bracket; i++) {
        int right=find(input_str, ")");
        int left=right;
        for (; left>=0; left--) {
            if (input_str[left]=='(') {
                break;
            }
        }
        
        char *string_in_bracket=substr(input_str, left+1, right);
        char *replace_str=substr(input_str, left, right+1);
        // can not remove bracket
        if (stringHasAlpha(string_in_bracket) && stringIsAlpha(string_in_bracket)==FALSE) {
            input_str=replace_from_index_to_index(input_str, replace_str, append("#LEFT#", append(string_in_bracket, "#RIGHT#")), left, right+1);
        }
        // can remove bracket
        else{
            input_str=replace_from_index_to_index(input_str, replace_str, string_in_bracket, left, right+1);
        }
        
    }
    input_str=replace(input_str,"#LEFT#","(");
    input_str=replace(input_str,"#RIGHT#",")");
    
    
    
    // clean ((...)) like
    
    int num_of_right_bracket=count_str(input_str, ")");
    int index_of_right=find(input_str, ")");
    int from_index_for_right=0;
    int from_index_for_left=index_of_right;
    i=0;
    for (; i<num_of_right_bracket; i++) {
        index_of_right=find_from_index(input_str, ")", from_index_for_right);
        from_index_for_right=index_of_right+1;
        if (index_of_right==-1) {
            break;
        }
        int index_of_left=0;
        if (index_of_right!=(int)strlen(input_str)-1) {
            if (input_str[index_of_right+1]==')') {
                index_of_left=find_from_behind_from_index(input_str, "(", from_index_for_left);
                from_index_for_left=index_of_left-1;
                if (index_of_left==-1) {
                    printf("Mistake occurred while calling function clean_math_output_for_decimal\n No left ( found\n");
                }
            }
            if (index_of_left!=0) {
                if (input_str[index_of_left-1]=='(') {
                    // can clean ((
                    char *replace_str=substr(input_str, index_of_left-1, index_of_right+2);
                    char *with_str=substr(input_str, index_of_left, index_of_right+1);
                    from_index_for_right=index_of_right-1;
                    // a+(((Hello)))
                    // a+((Hello))
                    from_index_for_left=index_of_left-1;
                    input_str=replace_from_index_to_index(input_str, replace_str, with_str, index_of_left-1, index_of_right+2);
                }
                else{
                    // can not clean
                    from_index_for_right=index_of_right+1;
                    from_index_for_left=index_of_left-1;
                }
            }
        }
    }

    return input_str;
}

// Calculate like (y*3*4/5^2+x)*y*3*4+x^(3/4)*y--->12*(0.48*y+x)*y+(x)^0.75*y
char *eval_for_decimal_with_alpha(char *input_str){
    char **SAVE_EXPRESSION_THAT_HAS_ALPHA_IN_BRACKTER; // save (y*3*4/5^2+x) to #SAVED1#
    int INDEX_OFR_SAVE_EXPRESSION=0;                   //                             1
    Str_initStringList(&SAVE_EXPRESSION_THAT_HAS_ALPHA_IN_BRACKTER);
    input_str=trim(input_str);
    input_str=eval_CalculatePowerAtFirst_with_alpha(input_str);
    //printf("AFTER--->%s\n",input_str);
    int count_of_left_bracket=count_str(input_str,"(");
    int count_of_right_bracket=count_str(input_str,")");
    
    //char *output;
    if(count_of_left_bracket!=count_of_right_bracket){
        printf("Mistakes occurred while calling function eval:\nnum of ( != num of )");
        exit(1);
    }
    
    int num_of_left_bracket=count_str(input_str, "(");
    int x=0;
    for (; x<num_of_left_bracket; x++) {
        int index_of_final_left_bracket=find(input_str, "(");
        int index_of_first_right_bracket=find(input_str, ")");
        while (TRUE) {
            
            int temp=find_from_index(input_str, "(", index_of_final_left_bracket+1);
            if (temp==-1 || temp>index_of_first_right_bracket) {
                break;
            }
            else {
                index_of_final_left_bracket=temp;
            }
            
        }
        char *temp=substr(input_str,0,index_of_final_left_bracket);
        
        char *part_output=eval_simple_str_with_alpha(substr(input_str,index_of_final_left_bracket+1,index_of_first_right_bracket));
        if (findAlphaInString(part_output)==TRUE) {
            part_output=append("(", part_output);
            part_output=append(part_output, ")");
            Str_addString(&SAVE_EXPRESSION_THAT_HAS_ALPHA_IN_BRACKTER, part_output);
            part_output=append("#SAVED", append(intToCString(INDEX_OFR_SAVE_EXPRESSION), "#"));
            INDEX_OFR_SAVE_EXPRESSION++;
        }
        
        temp=append(temp,part_output);
        temp=append(temp,substr(input_str,index_of_first_right_bracket+1,(int)strlen(input_str)));
        input_str=temp;
    }
    //printf("1---> %s\n",input_str);
    input_str=eval_simple_str_with_alpha(input_str);
    //printf("2---> %s\n",input_str);
    
    x=INDEX_OFR_SAVE_EXPRESSION-1;
    for (; x>=0; x--) {
        char *replace_str=append("#SAVED", append(intToCString(x), "#"));
        char *with_str=SAVE_EXPRESSION_THAT_HAS_ALPHA_IN_BRACKTER[x+1];
        input_str=replace(input_str,replace_str, with_str);
    }    
    input_str=changeOperatorStrToOriginalForWhoStr(input_str);
    //for calculate_for_division_for_fraction
    input_str=replace(input_str, "#LEFT#", "(");
    input_str=replace(input_str, "#RIGHT#", ")");
    
    // Delete 0 after
    int a=(int)strlen(input_str)-1;
    int place=(int)strlen(input_str);
    if (find(input_str, ".") != -1) {
        for (; a >= 0; a--) {
            if (input_str[a] == '0')
                place--;
            else
                break;
        }
    }
    if(place!=(int)strlen(input_str))
        input_str=substr(input_str,0,place);
    if(input_str[(int)strlen(input_str)-1]=='.')
        input_str=substr(input_str,0,(int)strlen(input_str)-1);
    
    input_str=clean_math_output_for_decimal(input_str);
    return input_str;
    
}

