//
//  walley_operator_fraction.h
//  Walley
//
//  Created by shd101wyy on 12-11-9.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

#include "walley_operator.h"
#include "mathomatic_walley/mathomatic.h"

char *eval_for_fraction(char *input_str);
char *simplify_fraction(char *num1_str, char *num2_str);
char *addParenthesisForPower(char *input_str);

// 1.2-->6/5  2-->2
char *changeDecimalToFraction(char *input_str){
    input_str=cleanDotZeroAfterNum(input_str);
    if (find(input_str, ".")==-1) {
        return input_str;
    }
    else{
        int num_after_dot=(int)strlen(input_str)-1-find(input_str, ".");
        input_str=replace(input_str, ".", "");

        return simplify_fraction(input_str, intToCString(pow(10, num_after_dot)));
    }
}

// get 1 from 1/3
char *numerator_of_fraction(char *fraction){
    int index_of_gang=find(fraction, "/");
    if (index_of_gang==-1) {
        return fraction;
    }   else {
    return substr(fraction, 0, index_of_gang);
    }
}

char *denominator_of_fraction(char *fraction){
    int index_of_gang=find(fraction, "/");
    if (index_of_gang==-1) {
        return "1";
    }else {
    return substr(fraction, index_of_gang+1, (int)strlen(fraction));
    }
}

//simplify_fraction("3","6")--->"1/2"
//simplify_fraction("4","5")--->"4/5"
//simplify_fraction("4.3","2")--->"43/20"
char *simplify_fraction(char *num1_str, char *num2_str){
    // did not find param like "4/3"
    //printf("num1 %s num2 %s\n",num1_str,num2_str);
    num1_str=cleanDotZeroAfterNum(num1_str);
    num2_str=cleanDotZeroAfterNum(num2_str);
    
    bool is_negative=FALSE;
    int num_of_minus=count_str(num1_str, "-")+count_str(num2_str, "-");
    if (num_of_minus%2!=0) {
        is_negative=TRUE;
    }
    
    if (find(num1_str,"/")==-1 && find(num2_str,"/")==-1) {
        int num_of_ten_need_to_times=0;
        int index_of_dot1=find(num1_str,".");
        int index_of_dot2=find(num2_str,".");
        int num1_of_ten_need_to_times=0;
        int num2_of_ten_need_to_times=0;
        if (index_of_dot1==-1) {
            num1_of_ten_need_to_times=0;
        }else{
            num1_of_ten_need_to_times=(int)strlen(num1_str)-1-index_of_dot1;
        }
        
        if (index_of_dot2==-1) {
            num2_of_ten_need_to_times=0;
        }else{
            num2_of_ten_need_to_times=(int)strlen(num2_str)-1-index_of_dot2;
        }
        if (num1_of_ten_need_to_times>=num2_of_ten_need_to_times) {
            num_of_ten_need_to_times=num1_of_ten_need_to_times;
        }
        else{
            num_of_ten_need_to_times=num2_of_ten_need_to_times;
        }
        
        // if params are 0.3 4---->3 40
        double num1=atof(num1_str);
        double num2=atof(num2_str);
        num1=abs(num1);
        num2=abs(num2);
        num1=num1*pow(10, num_of_ten_need_to_times);
        num2=num2*pow(10, num_of_ten_need_to_times);
        
        //printf("num1 is %f, num2 is %f\n",num1,num2);
        
    
        int smaller_number=(int)num1;
        if (num1>abs(num2)) {
            smaller_number=(int)num2;
        }
        
        int num1_int=(int)num1;
        int num2_int=(int)num2;
        
        //printf("num1_int is %d, num2_int is %d, smaller_number is %d\n",num1_int,num2_int,smaller_number);
        
        int i=0;
        for (i=2; i<=smaller_number; i++) {
            if (num1_int%i==0 && num2_int%i==0) {
                num1_int=num1_int/i;
                num2_int=num2_int/i;
                while (num1_int%i==0 && num2_int%i==0) {
                    num1_int=num1_int/i;
                    num2_int=num2_int/i;
                }
            }
        }
        
        
        
        if (num2_int==1) {
            if (is_negative) {
                return intToCString(-1*num1_int);
            }
            return intToCString(num1_int);
        }
        // get denominator and numerator after simplified
        char *output=append(intToCString(num1_int), "/");
        output=append(output, intToCString(num2_int));
        if (is_negative) {
            output=append("-", output);
        }
        return output;
    }
    // find / in num1_str or num2_str
    // like 1/3 4 or 2/3 4/5
    else{
        int index_of_gang_of_num1=find(num1_str, "/");
        int index_of_gang_of_num2=find(num2_str, "/");
        // like 2 and 1/3 --->2/(1/3)--->6
        if (index_of_gang_of_num1==-1 && index_of_gang_of_num2!=-1) {
            char* denominator=substr(num2_str, index_of_gang_of_num2+1, (int)strlen(num2_str));
            char* numerator=substr(num2_str,0,index_of_gang_of_num2);
            denominator=numToCString(atof(denominator)*atof(num1_str));
            return simplify_fraction(denominator, numerator);
        }
        // like 1/3 and 2---> (1/3)/2--->1/6
        else if (index_of_gang_of_num2==-1 && index_of_gang_of_num1!=-1) {
            char* denominator=substr(num1_str, index_of_gang_of_num1+1, (int)strlen(num1_str));
            char* numerator=substr(num1_str,0,index_of_gang_of_num1);
            denominator=numToCString(atof(denominator)*atof(num2_str));
            return simplify_fraction(numerator, denominator);
        }
        // like 1/3 and 2/3--->(1/3)/(2/3)--->1/2
        else {
            char* denominato_num1=substr(num1_str, index_of_gang_of_num1+1, (int)strlen(num1_str));
            char* numerator_num1=substr(num1_str,0,index_of_gang_of_num1);
            char* denominator_num2=substr(num2_str, index_of_gang_of_num2+1, (int)strlen(num2_str));
            char* numerator_num2=substr(num2_str,0,index_of_gang_of_num2);
            char* denominator=numToCString(atof(denominato_num1)*atof(numerator_num2));
            char* numerator=numToCString(atof(numerator_num1)*atof(denominator_num2));
            return simplify_fraction(numerator, denominator);
        }
    }
    return "Mistake occurred while calling function simplify_fraction";
}

// 1/3-->TRUE 2/4-->FALSE
bool fraction_is_simplified(char *numerator, char *denominator){
    char *fraction=simplify_fraction(numerator,denominator);
    char *fraction_origin=append(numerator, "/");
    fraction_origin=append(fraction_origin, denominator);
    if (strcmp(fraction_origin, fraction)==0) {
        return TRUE;
    }
    else{
        return FALSE;
    }
}


// like 1/3+2/3--->1/1  2/3+2/5-->16/15

char *fraction_plus(char *num1_str, char *num2_str){
    if (strcmp(num2_str, "0")==0) {
        return simplify_fraction(num1_str, "1");
    }
    if (strcmp(num1_str, "0")==0) {
        return simplify_fraction(num2_str, "1");
    }
    char *numerator_num1=numerator_of_fraction(num1_str);
    char *denominator_num1=denominator_of_fraction(num1_str);
    
    char *numerator_num2=numerator_of_fraction(num2_str);
    char *denominator_num2=denominator_of_fraction(num2_str);
    
    char *numerator=numToCString(atof(numerator_num1)*atof(denominator_num2)+atof(numerator_num2)*atof(denominator_num1));
    char *denominator=numToCString(atof(denominator_num1)*atof(denominator_num2));
    
    //printf("numerator %s\ndenominator %s\n",numerator,denominator);
    return simplify_fraction(numerator, denominator);
}

char *fraction_minus(char *num1_str, char *num2_str){
    char *numerator_num1=numerator_of_fraction(num1_str);
    char *denominator_num1=denominator_of_fraction(num1_str);
    
    char *numerator_num2=numerator_of_fraction(num2_str);
    char *denominator_num2=denominator_of_fraction(num2_str);
    
    char *numerator=numToCString(atof(numerator_num1)*atof(denominator_num2)-atof(numerator_num2)*atof(denominator_num1));
    char *denominator=numToCString(atof(denominator_num1)*atof(denominator_num2));
    
    //printf("numerator %s\ndenominator %s\n",numerator,denominator);
    return simplify_fraction(numerator, denominator);
}

//num1*num2
char *fraction_time(char *num1_str, char *num2_str){
    char *numerator_num1=numerator_of_fraction(num1_str);
    char *denominator_num1=denominator_of_fraction(num1_str);
    
    char *numerator_num2=numerator_of_fraction(num2_str);
    char *denominator_num2=denominator_of_fraction(num2_str);
    
    char *numerator=numToCString(atof(numerator_num1)*atof(numerator_num2));
    char *denominator=numToCString(atof(denominator_num1)*atof(denominator_num2));
    
    //printf("numerator %s\ndenominator %s\n",numerator,denominator);
    return simplify_fraction(numerator, denominator);
}
// num1/num2
char *fraction_divide(char *num1_str, char *num2_str){
    return simplify_fraction(num1_str, num2_str);
}
// make 1.2-->12/10--->6/5
char *double_to_fraction(char *num){
    return simplify_fraction(num, "1");
}
// make 3/2-->1.5
char *fraction_to_double(char *num){
    char *input_str=numToCString(atof(numerator_of_fraction(num))/atof(denominator_of_fraction(num)));
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
    //printf("input_str is %s\n",input_str);
    return input_str;
}
char *fraction_power(char *num1_str, char *num2_str){
    char *num1_d=denominator_of_fraction(num1_str);
    char *num1_n=numerator_of_fraction(num1_str);
    num1_str=simplify_fraction(num1_n, num1_d);
    
    char *num2_d=denominator_of_fraction(num2_str);
    char *num2_n=numerator_of_fraction(num2_str);
    num2_str=simplify_fraction(num2_n, num2_d);
    
    if (stringIsDigit(num2_str)) {
        char *d=denominator_of_fraction(num1_str);
        char *n=numerator_of_fraction(num1_str);
        
        d=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof(d), atof(num2_str), '^')));
        n=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof(n), atof(num2_str), '^')));
        
        return simplify_fraction(n, d);
    }
    else{
        if (stringIsDigit(num1_str)) {
            return append(num1_str, append("^", append("(", append(num2_str, ")"))));
        }
        else{
            num1_str=append("(", append(num1_str, ")"));
            return append(num1_str, append("^", append("(", append(num2_str, ")"))));
        }
    }
    
    
}

char *Walley_Operator_For_Fraction(char *num1_str, char *num2_str, char sign){
    //printf("num1_str %s, num2_str %s, sign %c\n",num1_str,num2_str,sign);
    if (sign=='+') {
        return fraction_plus(num1_str, num2_str);
    }
    else if (sign=='-') {
        return fraction_minus(num1_str, num2_str);
    }
    else if (sign=='/'){
        return fraction_divide(num1_str, num2_str);
    }
    else if (sign=='*'){
        return fraction_time(num1_str, num2_str);
    }
    else if(sign=='^'){
        return fraction_power(num1_str,num2_str);
    }
    else{
        printf("Mistake occurred while calling function Walley_Operation_For_Fraction\nUnseen sign %c occurred\n",sign);
        return "Mistake occurred while calling function Walley_Operation_For_Fraction\nUnseen sign occurred\n";
    }
    
}


//check whether * / \ ^ % is in input_str
bool hasFirstOrderSignExistExceptDivide(char *input_str){
    bool has_sign=FALSE;
    int i=0;
    for(;i<(int)strlen(input_str);i++){
        if(input_str[i]=='*'||input_str[i]=='\\'||input_str[i]=='^'||input_str[i]=='%'){
            has_sign=TRUE;
        }
    }
    return has_sign;
}


char* countFromExpressionForFraction(char *var_value) {
    //printf("countFromExpressionForFraction input |%s|\n",var_value);
    var_value=append(var_value, "+0");
    //if (hasSign(var_value) == FALSE){
    //    //printf("$$$$$$ %s\n",var_value);
    //    return var_value;
    //}
    //else {
        
        char *output;
        char *input = var_value;
        //char sign;
        
        int i = 0;
        int j = 0;
        int temp = 0;
        
        //double num1;
        //double num2;
        //double previous_num;
        bool begin = FALSE;
        
        char *num1_str;
        char *num2_str;
        
        char *previous_num_str;
                
        for (; i <(int)strlen(input); i++) {
            if (isSign(input[i]) == TRUE&& input[i]!='/') {
                num1_str = substr(input, temp, i);
                //printf("sign %c\n",input[i]);
                //printf("num1_str %s\n",num1_str);
                j = i + 1;
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
                    if (isSign(input[j]) == TRUE && input[j]!='/') {
                        num2_str = substr(input, i + 1, j);
                        
                        break;
                    }
                    if (j == (int) strlen(input) - 1 && input[j]!='/') {
                        num2_str = substr(input, i + 1, j + 1);
                        break;
                    }
                }
                
                if (count_str(num1_str, "/")>1) {
                    // like 3/3/3/3
                    int index_of_first_gang=find(num1_str, "/");
                    int index_of_second_gang=find_from_index(num1_str, "/", index_of_first_gang+1);
                    char *temp_num=substr(num1_str, index_of_first_gang+1, index_of_second_gang);

                    while (index_of_second_gang!=-1) {
                        //printf("temp num is %s\n",temp_num);
                        int index_of_third_gang=find_from_index(num1_str, "/", index_of_second_gang+1);
                        if (index_of_third_gang==-1) {
                            temp_num=eval_simple_str(append(temp_num,append("*", substr(num1_str, index_of_second_gang+1, (int)strlen(num1_str)))));
                            break;
                        }
                        else{
                            temp_num=eval_simple_str(append(temp_num,append("*", substr(num1_str, index_of_second_gang+1, index_of_third_gang))));
                        }
                        index_of_second_gang=index_of_third_gang;
                        
                    }
                    char *numerator=substr(num1_str, 0, index_of_first_gang);
                    num1_str=append(numerator, append("/", temp_num));
                }
                
                if (count_str(num2_str, "/")>1) {
                    // like 3/3/3/3
                    int index_of_first_gang=find(num2_str, "/");
                    int index_of_second_gang=find_from_index(num2_str, "/", index_of_first_gang+1);
                    char *temp_num=substr(num2_str, index_of_first_gang+1, index_of_second_gang);
                    
                    while (index_of_second_gang!=-1) {
                        //printf("temp num is %s\n",temp_num);
                        int index_of_third_gang=find_from_index(num2_str, "/", index_of_second_gang+1);
                        if (index_of_third_gang==-1) {
                            temp_num=eval_simple_str(append(temp_num,append("*", substr(num2_str, index_of_second_gang+1, (int)strlen(num2_str)))));
                            break;
                        }
                        else{
                            temp_num=eval_simple_str(append(temp_num,append("*", substr(num2_str, index_of_second_gang+1, index_of_third_gang))));
                        }
                        index_of_second_gang=index_of_third_gang;
                        
                    }
                    char *numerator=substr(num2_str, 0, index_of_first_gang);
                    num2_str=append(numerator, append("/", temp_num));
                }


                
                
                if (begin == FALSE) {
                    previous_num_str = Walley_Operator_For_Fraction(num1_str, num2_str, input[i]);
                    output = previous_num_str;
                    //printf("%s\n",previous_num_str);
                    begin = TRUE;
                } else {
                    previous_num_str = Walley_Operator_For_Fraction(previous_num_str, num2_str, input[i]);
                    output = previous_num_str;
                }
            }
        }
        
        //printf("%f\n", output);
        return output;
   // }
}

char *countFirstOrderSignAndChangeTheStrOnlyOnceForFraction(char *input_str){
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
        
        if(isFirstOrderSign(input_str[i])==TRUE && input_str[i]!='/') {
            //printf("find first order sign %c\n",input_str[i]);
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
            //printf("num1 is %s\nnum2 is %s\n",num1_str,num2_str);
            //printf("num1 is %f\nnum2 is %f\n",atof(num1_str),atof(num2_str));
            
            // Here may be some problem...
            // I solved it tonight.
            
            
            char *output;
            if (stringIsFraction(num1_str)==TRUE||stringIsFraction(num2_str)==TRUE) {
                output=Walley_Operator_For_Fraction(num1_str, num2_str, input_str[i]);
            }
            else{
                output=numToCString(Walley_Operator(atof(num1_str),atof(num2_str),input_str[i]));
            }
            //printf("output--->%s\n",output);
            
            
            char *output_str=output;
            char *output_temp="";
            //printf("input_str is:%s\n",input_str);
            //printf("input_str is:%s\n",input_str);
            if(begin_of_first_num==0){
                output_temp=append(output_temp,output_str);
                if(end_of_second_num!=(int)strlen(input_str)-1){
                    output_temp=append(output_temp,substr(input_str,end_of_second_num+1,(int)strlen(input_str)));
                }
            }  else  {
                //printf("else\n");
                //printf("input_str :%s",input_str);
                //printf("substr :%s\n",substr(input_str,0,begin_of_first_num));
                output_temp=append(output_temp,substr(input_str,0,begin_of_first_num));
                if(end_of_second_num==(int)strlen(input_str)-1)
                    output_temp=append(output_temp,output_str);
                else{
                    //printf("enter here\n");
                    output_temp=append(output_temp,output_str);
                    output_temp=append(output_temp,substr(input_str,end_of_second_num+1,(int)strlen(input_str)));
                }
            }
            input_str=(char*)output_temp;
            break;
        }
    }
    
    //printf("The changed str is %s\n\n\n\n",input_str);
    return input_str;
}

char *eval_simple_str_for_fraction(char *input_str){
    /*
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
     */
    // for(;i<(int)strlen(input_str);i++){
    //printf("----->%s\n",input_str);
    while(hasFirstOrderSignExistExceptDivide(input_str)==TRUE){
        input_str=countFirstOrderSignAndChangeTheStrOnlyOnceForFraction(input_str);
    }
    //printf("input str now is |%s|\n",input_str);
    return countFromExpressionForFraction(input_str);
    // return (char*)output_str;
}

char *eval_for_fraction(char *input_str){
    //printf("#### eval ####\ninput_str %s\n",input_str);
    input_str=trim(input_str);
    /*
     if(input_str[0]!='('){
     //char *temp=malloc(sizeof(char)*strlen(input_str)+2);
     char temp[1000]="(";
     //temp="(";
     strcat(temp,input_str);
     
     strcat(temp,")");
     input_str=temp;
     }*/
    //int count=count_str(input_str,"(");
    //printf("count is %d\n",count);
    //printf("after automatically add (), the input_str is %s\n",input_str);
    
    int count_of_left_bracket=count_str(input_str,"(");
    int count_of_right_bracket=count_str(input_str,")");
    
    //char *output;
    if(count_of_left_bracket!=count_of_right_bracket){
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

printf("Mistakes occurred while calling function eval:\nnum of ( != num of )");
        exit(1);
    }
    
    
    //int index_of_final_left_bracket=0;
    //int index_of_first_right_bracket=(int)strlen(input_str)-1;
    
    //int i=0;
    while(count_str(input_str,"(")!=0){
        //printf("input_str |%s|\n",input_str);
        
        /*
         for(i=0;i<(int)strlen(input_str);i++){
         
         if(input_str[i]=='(')
         index_of_final_left_bracket=i;
         }
         for(i=0;i<(int)strlen(input_str);i++){
         
         if(input_str[i]==')'){
         index_of_first_right_bracket=i;
         break;
         }
         }
         */
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
        
        
        //printf("index of ( is %d\n",index_of_final_left_bracket);
        //printf("index of ) is %d\n",index_of_first_right_bracket);
        //printf("inside parenthesis |%s|\n",substr(input_str,index_of_final_left_bracket+1,index_of_first_right_bracket));
        
        char *temp=substr(input_str,0,index_of_final_left_bracket);
        char *part_output=eval_simple_str_for_fraction(substr(input_str,index_of_final_left_bracket+1,index_of_first_right_bracket));
        //printf("part_output %s\n",part_output);
        
        // 3/(6/2) case
        if (index_of_final_left_bracket!=0 && input_str[index_of_final_left_bracket-1]=='/') {
            int a=index_of_final_left_bracket-2;
            int index_of_first_num=0; // this initialization must be 0....
            // 3/(6/2)---> 3 is what i want
            for (a=index_of_final_left_bracket-2; index_of_final_left_bracket>=0; a--) {
                if (isdigit(input_str[a]) || input_str[a]==')' || input_str[a]=='(') {
                    continue;
                }
                else{
                    index_of_first_num=a+1;
                    break;
                }
            }
            char *first_num=substr(input_str, index_of_first_num, index_of_final_left_bracket-1);
            //printf("first_num %s\n",first_num);
            
            // 3/4/(3/4)case
            char *temp_value;
            if (index_of_first_num!=0 && input_str[index_of_first_num-1]=='/') {
                // multiply 4 and (3/4)
                temp_value=fraction_time(first_num, part_output);
            }
            else{
                // divide 4 by (3/4)
                temp_value=fraction_divide(first_num, part_output);
            }
            //printf("temp_value %s\n",temp_value);
            temp=substr(input_str, 0, index_of_first_num);
            temp=append(temp, temp_value);
            temp=append(temp,substr(input_str,index_of_first_right_bracket+1,(int)strlen(input_str)));
            input_str=temp;
            continue;
        }
        
        
        
        temp=append(temp,part_output);
        temp=append(temp,substr(input_str,index_of_first_right_bracket+1,(int)strlen(input_str)));
        //printf("temp now is %s\n",temp);
        input_str=temp;
        //printf("input_str is %s\n",input_str);
        //printf("count of ( %d\n",count_str(input_str, "("));
    }
    //printf("---> %s\n",input_str);
    input_str=eval_simple_str_for_fraction(input_str);
    //printf("final input_str %s\n",input_str);
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
    //printf("input_str is %s\n",input_str);
    if (strcmp(denominator_of_fraction(input_str),"1")==0) {
        return numerator_of_fraction(input_str);
    }
    return input_str;
}

// √(4)---2  √(8)--->2√(2) √(4/2)--->2/√2
char *simplify_root(char *input_str){
    int index_of_bracket=find(input_str, "(");
    char *output="None";
    if (index_of_bracket==-1) {
        printf("Mistake occurred whiling calling function simplify_root\nNo ( find\ncorrect format √(num)\n");
        exit(0);
    }else{
        char *num=substr(input_str, index_of_bracket+1, (int)strlen(input_str)-1);
        if(stringIsDigit(num)){
            // is integer
            if (find(num, ".")==-1) {
                double square_root=sqrt(atof(num));
                
                // can calculate directly like √(9) --->3
                if (square_root-(int)square_root==0) {
                    return intToCString((int)square_root);
                }
                // can not calculate directly like √(2)
                else{
                    // make √(8)--->2√2
                    int count=0;
                    int i=2;
                    int num_int=atoi(num);
                    int num_ahead=1;
                    for (i=2; i<num_int; i++) {
                        
                        if (num_int%i==0) {
                            int temp=num_int;
                            while (TRUE) {
                                if (temp%i==0) {
                                    temp=temp/i;
                                    count++;
                                }
                                else{
                                    break;
                                }
                            }
                            
                            int power=count/2;
                            num_int=num_int/pow(i,power*2);
                            num_ahead=num_ahead*pow(i,power);
                            
                            //printf("num_int %d\n",num_int);
                            //printf("num_ahead %d\n",num_ahead);
                        }
                        count=0;
                    }
                
                if (num_ahead!=1) {
                    //output=append("", intToCString(num_ahead));
                    output=append(intToCString(num_ahead),"*");

                }
                else{
                    output="";
                }
                output=append(output, "√");
                output=append(output, "(");
                output=append(output, intToCString(num_int));
                output=append(output, ")");
                }
            }
            // is decimal
            else{
                num=cleanDotZeroAfterNum(num);
                //printf("num is |%s|\n",num);
                if (find(num, ".")==-1) {
                    return simplify_root(append("(",append(num,")")));
                }
                else{
                    int num_after_dot=(int)strlen(num)-1-find(num, ".");
                    num=replace(num, ".", "");
                    char *temp=append(num, append("/", intToCString(pow(10, num_after_dot))));
                    temp=append("(", append(temp, ")"));
                    //printf("temp %s\n",temp);
                    return simplify_root(temp);
                }
            }
        }
    // √(4/9)
        else if (stringIsFraction(num)){
            char *numerator=numerator_of_fraction(num);
            char *denominator=denominator_of_fraction(num);
            
            numerator=numToCString(atof(denominator)*atof(numerator));
            denominator=numToCString(atof(denominator)*atof(denominator));
            
            //printf("numerator %s\n",numerator);
            //printf("denominator %s\n",denominator);
            
            char *numerator_simplified=simplify_root(append("√(", append(numerator,")")));
            char *denominator_simplified=simplify_root(append("√(", append(denominator,")")));

            //printf("numerator_simplified %s\n",numerator_simplified);
            //printf("denominator_simplified %s\n",denominator_simplified);
            
            //return √(2)/2
            if (find(numerator_simplified,"√")!=-1) {
                
                // 3√(2)/9------>√(2)/3
                if (isdigit(numerator_simplified[0])) {
                    char *num_ahead_numberator=substr(numerator_simplified, 0, find(numerator_simplified, "√"));
                    
                    //√(2)--->(2)
                    char *root_str=substr(numerator_simplified, find(numerator_simplified, "("), (int)strlen(numerator_simplified));
                    root_str=append("√", root_str);
                    
                    char *fraction=simplify_fraction(num_ahead_numberator, denominator_simplified);
                    char *temp_numerator=numerator_of_fraction(fraction);
                    
                    if (atof(temp_numerator)==1) {
                        return append(root_str, append("/", denominator_of_fraction(fraction)));
                    }
                    else{
                        return append(temp_numerator,append(root_str, append("/", denominator_of_fraction(fraction))));
                    }
                }
                else{
                    return append(numerator_simplified, append("/", denominator_simplified));
                }
            }
            // return fraction
            else{
                return simplify_fraction(numerator_simplified, denominator_simplified);
            }
            
        }
        else{
            printf("Mistake occurred whiling calling function simplify_root\nInside should be fraction or decimal\n");
        }

    }

    return output;
}

// 2^0.5--->√(2)    2^2---->4
char *changePowerToRoot(char *input_str){
    printf("changePowerToRoot %s\n",input_str);
    int index_of_power_sign=find_from_behind(input_str, "^");
    if (index_of_power_sign==-1) {
        printf("Mistake occurred whiling calling function changePowerToRoot\nNo ^ found\n");
        exit(0);
    }
    char *num=substr(input_str, 0, index_of_power_sign);
    char *power=substr(input_str, index_of_power_sign+1, (int)strlen(input_str));
    num=eval_for_fraction(num);
    power=eval_for_fraction(power);
    
    printf("num %s\npower %s\n",num,power);
    
    // 2^(1/2)   (1/2)^(3/4)
    if (stringIsFraction(power)==TRUE) {
        //(1/2)^(1/3)
        if (stringIsFraction(num)==TRUE) {
            char *numerator_of_power=numerator_of_fraction(power);
            char *denominator_of_power=denominator_of_fraction(power);
            
            /*
            bool can_use_root_sign=TRUE;
            int temp_denominator=atoi(denominator_of_power);
            while (TRUE) {
                if (temp_denominator%2!=0) {
                    can_use_root_sign=FALSE;
                    break;
                }
                else{
                    temp_denominator=temp_denominator/2;
                    if (temp_denominator==1) {
                        break;
                    }
                }
            }*/
            
            //(1/2)^(3/4)---->(1/2)^3
            num=append("(", append(num, ")"));
            char *temp=changePowerToRoot(append(num, append("^", numerator_of_power)));

            if (atoi(denominator_of_power)==2) {
                if (temp[0]=='(') {
                    return simplify_root(append("√", temp));
                }
                return simplify_root(append("√(", append(temp,")")));
            }
            else{
                return append(temp, append("^(1/", append(denominator_of_power, ")")));
            }

        }
        //2^(1/3)
        else{
            char *numerator_of_power=numerator_of_fraction(power);
            char *denominator_of_power=denominator_of_fraction(power);
            
            /*
            bool can_use_root_sign=TRUE;
            int temp_denominator=atoi(denominator_of_power);
            while (TRUE) {
                if (temp_denominator%2!=0) {
                    can_use_root_sign=FALSE;
                    break;
                }
                else{
                    temp_denominator=temp_denominator/2;
                    if (temp_denominator==1) {
                        break;
                    }
                }
            }*/
            
            //2^(3/4)--->2^3--->8
            char *temp=changePowerToRoot(append(num, append("^", numerator_of_power)));
            
            if (atoi(denominator_of_power)==2) {
                return simplify_root(append("√(", append(temp,")")));
            }
            else{
                return append(temp, append("^(1/", append(denominator_of_power, ")")));
            }
            
        }
    }
    
    //2^2
    else{
        // (1/2)^(2)
        if (stringIsFraction(num)==TRUE) {
            char *numerator=numerator_of_fraction(num);
            char *denominator=denominator_of_fraction(num);
            
            numerator=changePowerToRoot(append(numerator, append("^", power)));
            denominator=changePowerToRoot(append(denominator, append("^", power)));
            
            char *output=simplify_fraction(numerator, denominator);
            if (stringIsFraction(output)) {
                return append("(", append(output, ")"));
            } else {
                return output;
            }
            
            //return simplify_fraction(numerator, denominator);
            
        }
        //2^(2)
        else{
            return intToCString((int)pow(atoi(num),atoi(power)));
        }

    }
}

//(2^2)+(3^4)*2+6/4+4---->(2^2)+(3^4)+6/4+4
char* countFromExpressionForFractionAndRootAndPower(char *var_value) {
    if (find(var_value, "^")==-1) {
        return eval_for_fraction(var_value);
    }
    //printf("var_value %s\n",var_value);

    var_value=append(")+0+", var_value);
    var_value=append(var_value, "+0+(");
    //printf("var_value %s\n",var_value);

    //printf("var_value %s\n",var_value);
    // (2^2)+(3^4)*2+6/4+4---> )+0+(2^2)+(3^4)*2+6/4+4+0+(
    // 2*6---->)+0+2*6+0+(
    // (2^2)+(3^4)*2*2-6/4+4---> )+0+(2^2)+(3^4)*2*2-6/4+4+0+(

    int right_bracket=0;
    int left_bracket=find(var_value, "(");
    //char *temp_var_value=var_value;
    while (TRUE) {
        //)*2+3+2*(------>*2+3+2*
        while (TRUE) {
            char *temp_str=substr(var_value, 0, right_bracket+1);
            if (count_str(temp_str, ")")-count_str(temp_str,"(")!=1) {
                right_bracket=find_from_index(var_value, ")", right_bracket+1);
            }
            else{
                left_bracket=find_from_index(var_value, "(", right_bracket+1);
                break;
            }
        }
        
        char *middle=substr(var_value, right_bracket+1, left_bracket);
        
        if ((int)strlen(middle)==1) {
            right_bracket=find_from_index(var_value, ")", left_bracket+1);
            while (TRUE) {
                if (var_value[right_bracket+1]==')') {
                    right_bracket=right_bracket+1;
                }
                else{
                    break;
                }
            }
            left_bracket=find_from_index(var_value, "(", right_bracket+1);
            //printf("2right bracket %d left_bracket %d\n",right_bracket,left_bracket);
            if (right_bracket==-1) {
                break;
            }
            continue;
        }
        
        
        char *replace_str=middle;
        //printf("middle %s\n",middle);
        int index_of_plus=find(middle,"+");
        int index_of_minus=find(middle,"-");
        int index_ahead;
        
        //)*2+0+( ---->3
        if (index_of_minus==-1) {
            index_ahead=index_of_plus;
        }
        //)*2-2+0+( ---->3
        else if(index_of_minus<index_of_plus){
            index_ahead=index_of_minus;
        }
        //)*2+2-3+( ---->3
        else{
            index_ahead=index_of_plus;
        }
        
        int index_behind;
        int i=0;
        for (i=(int)strlen(middle)-1; i>=0; i--) {
            if (middle[i]=='+'||middle[i]=='-') {
                index_behind=i;
                break;
            }
        }
        
        char *middle2;
        char *middle2_output;
        if (index_behind==index_ahead) {
            middle2="";
            middle2_output=charToString(middle[index_ahead]);
        }else{
        
        //  a     b
        //*2+2-3+2+ ---->2-3+2
        middle2=substr(middle, index_ahead+1, index_behind);
        middle2_output=eval_for_fraction(middle2);
            //printf("middle2_output |%s|\n",middle2_output);
            if (strcmp(middle2_output, "0")==0) {
                middle2_output="";
            }
            else{
                middle2_output=append(charToString(middle[index_ahead]), middle2_output);
                middle2_output=append(middle2_output, charToString(middle[index_behind]));
            }
        }
        //printf("middle2_output %s\n",middle2_output);
        
        char *left;
        char *right;
        char *left_output="";
        char *right_output="";
        
        //  a b
        //*2+3+ --->*2 left
        
        //  a b
        //*2+3+2* --->2*right
        if (index_ahead==0) {
            left="";
            left_output="";
        }
        else{
            //  a b
            //*2+3+ --->*2 left -----> 2 cancel *
            left=substr(middle, 1, index_ahead);
            left_output=eval_for_fraction(left);
            
            if (stringIsFraction(left_output)==TRUE) {
                left_output=append("(", append(left_output, ")"));
            }
            
            left_output=append(charToString(middle[0]), left_output); // //*2*3+3+ --->*2 left -----> 2*3 cancel *--->*2*3
        }
        
        if (index_behind==(int)strlen(middle)-1) {
            right="";
            right_output="";
        }
        else{
            //  a b
            //*2+3+4* ---> 4* right --->4
            right=substr(middle, index_behind+1, (int)strlen(middle)-1);
            right_output=eval_for_fraction(right);
            
            if (stringIsFraction(right_output)==TRUE) {
                right_output=append("(", append(right_output, ")"));
            }
            
            right_output=append(right_output, charToString(middle[(int)strlen(middle)-1]));
        }
        char *with_str=append(left_output, middle2_output);
        with_str=append(with_str, right_output);
        
        //printf("replace %s\n",replace_str);
        //printf("with_str %s\n",with_str);
        
        var_value=replace_from_index_to_index(var_value, replace_str, with_str, right_bracket, left_bracket);
        //printf("var_value %s\n",var_value);
        //printf("1right bracket %d left_bracket %d\n",left_bracket,right_bracket);
        int from=left_bracket+1-((int)strlen(replace_str)-(int)strlen(with_str));
        if (from>=(int)strlen(var_value)) {
            break;
        }
        right_bracket=find_from_index(var_value, ")", from);
        while (TRUE) {
            if (var_value[right_bracket+1]==')') {
                right_bracket=right_bracket+1;
            }
            else{
                break;
            }
        }
        left_bracket=find_from_index(var_value, "(", right_bracket+1);

        //printf("2right bracket %d left_bracket %d\n",right_bracket,left_bracket);
        if (right_bracket==-1||left_bracket==-1) {
            break;
        }
    }
    
    int i=0;
    int from=0;
    int to=0;
    for (i=0; i<(int)strlen(var_value); i++) {
        if (var_value[i]=='('||isdigit(var_value[i])) {
            from=i;
            break;
        }
    }
    for (i=(int)strlen(var_value)-1; i>=0; i--) {
        if (var_value[i]==')'||isdigit(var_value[i])) {
            to=i;
            break;
        }
    }
    var_value=substr(var_value, from, to+1);
    //printf("var_value %s\n",var_value);
    return var_value;
}


//time=2-->ex  3*4+5*6----> 3*4+30
//time=1-->ex  3*4+5*6----> 12+5*6
char *countFirstOrderSignAndChangeTheStrOnlyOnceForFractionAndRootAndPower(char *input_str,int time){
    //printf("%s   %d\n",input_str,time);
    input_str=addParenthesisForPower(input_str);
    int i=0;
    int j=0;
    int begin_of_first_num=0;
    int end_of_second_num=(int)strlen(input_str)-1;
    int place_of_first_order_sign;
    
    char *num1_str;
    char *num2_str;
    
    int time_time=1;
    
    char *input_str2=input_str;
    for(;i<(int)strlen(input_str);i++){
        if(isdigit(input_str[i]) || input_str[i]=='^'){
            continue;
        }
        
        if(input_str[i]=='+'||input_str[i]=='-'){
            begin_of_first_num=i+1;
        }
        
        if(isFirstOrderSign(input_str[i])==TRUE && input_str[i]!='/' && input_str[i]!='^') {
            //printf("find first order sign %c\n",input_str[i]);
            if (time_time!=time) {
                time_time++;
                continue;
            }
            
            j = i + 1;
            place_of_first_order_sign=i;
            
            for (; j < (int) strlen(input_str); j++) {
                // I just change this code here 9/17/2012
                if (isSign(input_str[j]) == TRUE && j!=i+1 &&input_str[j]!='^') {
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
            //printf("num1 %s   num2 %s\n",num1_str,num2_str);

            char *output_str;
            if (find(num1_str, "^")!=-1||find(num2_str,"^")!=-1) {
                
                return input_str;
                //break;
                //output_str=substr(input_str, begin_of_first_num, end_of_second_num+1);
            }
            else{
            //printf("input_str is:%s\n",input_str);
            //printf("num1 is %f\nnum2 is %f\n",atof(num1_str),atof(num2_str));
            
            //double output=Walley_Operator(atof(num1_str),atof(num2_str),input_str[i]);
            //output_str=numToCString(output);
            output_str=Walley_Operator_For_Fraction(num1_str, num2_str, input_str[i]);
            //printf("input_str is:%s\n",input_str);
            //printf("output_str is %s\n",output_str);
            }
            
            char *output_temp="";
            //printf("input_str is:%s\n",input_str);
            //printf("input_str is:%s\n",input_str);
            if(begin_of_first_num==0){
                output_temp=append(output_temp,output_str);
                if(end_of_second_num!=(int)strlen(input_str)-1){
                    output_temp=append(output_temp,substr(input_str,end_of_second_num+1,(int)strlen(input_str)));
                }
            }  else  {
                //printf("else\n");
                //printf("input_str :%s",input_str);
                //printf("substr :%s\n",substr(input_str,0,begin_of_first_num));
                output_temp=append(output_temp,substr(input_str,0,begin_of_first_num));
                if(end_of_second_num==(int)strlen(input_str)-1)
                    output_temp=append(output_temp,output_str);
                else{
                    //printf("enter here\n");
                    output_temp=append(output_temp,output_str);
                    output_temp=append(output_temp,substr(input_str,end_of_second_num+1,(int)strlen(input_str)));
                }
            }
            input_str=(char*)output_temp;
            break;
        }

        
    }
    
    //printf("The changed str is %s\n\n\n\n",input_str);
    if (strcmp(input_str, input_str2)==0) {
        return "None";
    }
    return input_str;
}

char *countFirstOrderSignAndChangeTheStrOnlyOnceForFractionAndRootAndPowerWithAddingParenthesisForPower(char *input_str,int time){
    //printf("%s   %d\n",input_str,time);
    //input_str=addParenthesisForPower(input_str);
    int i=0;
    int j=0;
    int begin_of_first_num=0;
    int end_of_second_num=(int)strlen(input_str)-1;
    int place_of_first_order_sign;
    
    char *num1_str;
    char *num2_str;
    
    int time_time=1;
    
    char *input_str2=input_str;
    for(;i<(int)strlen(input_str);i++){
        if(isdigit(input_str[i]) || input_str[i]=='^'){
            continue;
        }
        
        if(input_str[i]=='+'||input_str[i]=='-'){
            begin_of_first_num=i+1;
        }
        
        if(isFirstOrderSign(input_str[i])==TRUE && input_str[i]!='/' && input_str[i]!='^') {
            //printf("find first order sign %c\n",input_str[i]);
            if (time_time!=time) {
                time_time++;
                continue;
            }
            
            j = i + 1;
            place_of_first_order_sign=i;
            
            for (; j < (int) strlen(input_str); j++) {
                // I just change this code here 9/17/2012
                if (isSign(input_str[j]) == TRUE && j!=i+1 &&input_str[j]!='^') {
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
            //printf("num1 %s   num2 %s\n",num1_str,num2_str);
            
            if (stringIsFraction(num1_str)) {
                char *numerator=numerator_of_fraction(num1_str);
                char *denominator=denominator_of_fraction(num1_str);
                if(fraction_is_simplified(numerator,denominator)==FALSE){
                    char *with_str=simplify_fraction(numerator, denominator);
                    with_str=append("(", with_str);
                    with_str=append(with_str, ")");
                    input_str=replace_from_index_to_index(input_str,num1_str,with_str,begin_of_first_num,place_of_first_order_sign);
                    i=i+((int)strlen(with_str)-(int)strlen(num1_str))-1;
                    continue;
                }
            }
            
            if (stringIsFraction(num2_str)) {
                char *numerator=numerator_of_fraction(num2_str);
                char *denominator=denominator_of_fraction(num2_str);
                if(fraction_is_simplified(numerator,denominator)==FALSE){
                    char *with_str=simplify_fraction(numerator, denominator);
                    with_str=append("(", with_str);
                    with_str=append(with_str, ")");
                    input_str=replace_from_index_to_index(input_str,num2_str,with_str,place_of_first_order_sign+1,end_of_second_num+1);
                    i=i+((int)strlen(with_str)-(int)strlen(num2_str))-1;
                    continue;
                }
            }
            
            
            

            
            //Problem occurred....
            //num1_str or num2_str may be fraction.
            
            
            
            
            char *output_str;
            if (find(num1_str, "^")!=-1||find(num2_str,"^")!=-1) {
                
                return input_str;
                //break;
                //output_str=substr(input_str, begin_of_first_num, end_of_second_num+1);
            }
            else{
                //printf("input_str is:%s\n",input_str);
                //printf("num1 is %f\nnum2 is %f\n",atof(num1_str),atof(num2_str));
                
                //double output=Walley_Operator(atof(num1_str),atof(num2_str),input_str[i]);
                //output_str=numToCString(output);
                output_str=Walley_Operator_For_Fraction(num1_str, num2_str, input_str[i]);
                //printf("input_str is:%s\n",input_str);
                //printf("output_str is %s\n",output_str);
            }
            
            char *output_temp="";
            //printf("input_str is:%s\n",input_str);
            //printf("input_str is:%s\n",input_str);
            if(begin_of_first_num==0){
                output_temp=append(output_temp,output_str);
                if(end_of_second_num!=(int)strlen(input_str)-1){
                    output_temp=append(output_temp,substr(input_str,end_of_second_num+1,(int)strlen(input_str)));
                }
            }  else  {
                //printf("else\n");
                //printf("input_str :%s",input_str);
                //printf("substr :%s\n",substr(input_str,0,begin_of_first_num));
                output_temp=append(output_temp,substr(input_str,0,begin_of_first_num));
                if(end_of_second_num==(int)strlen(input_str)-1)
                    output_temp=append(output_temp,output_str);
                else{
                    //printf("enter here\n");
                    output_temp=append(output_temp,output_str);
                    output_temp=append(output_temp,substr(input_str,end_of_second_num+1,(int)strlen(input_str)));
                }
            }
            input_str=(char*)output_temp;
            break;
        }
    }
    
    //printf("The changed str is %s\n\n\n\n",input_str);
    if (strcmp(input_str, input_str2)==0) {
        return "None";
    }
    return input_str;
}

// 3+2^2------>3+(2^2)    3+2^2*6--->3+(2^2)*6
char *addParenthesisForPower(char *input_str){
    //printf("|%s|\n",input_str);
    int i=0;
    int count_of_power=count_str(input_str, "^");
    for (i=0; i<count_of_power; i++) {
        int index_of_power=find(input_str, "^");
        int j=i;
        while (j!=0) {
            index_of_power=find_from_index(input_str, "^", index_of_power+1);
            j--;
        }
        
        int left;
        int right;
        
        j=index_of_power;
        for (j=index_of_power-1; j>=0; j--) {
            if (input_str[j]==')') {
                int k=j;
                int temp_right=0;
                int temp_left=0;
                for (k=j; k>=0; k--) {
                    if (input_str[k]==')') {
                        temp_right++;
                        continue;
                    }
                    if (input_str[k]=='(') {
                        temp_left++;
                        if (temp_left==temp_right) {
                            left=k;
                            break;
                        }
                    }
                }
                break;
            }
            
            if (isdigit(input_str[j])==FALSE && input_str[j]!='.') {
                left=j+1;
                break;
            }
            if (j==0) {
                left=0;
                break;
            }
        }
        j=index_of_power+1;
        for (j=index_of_power+1; j<(int)strlen(input_str); j++) {
            if (input_str[j]=='(') {
                int k=j;
                int temp_right=0;
                int temp_left=0;
                for (k=j; k<(int)strlen(input_str); k++) {
                    if (input_str[k]=='(') {
                        temp_right++;
                        continue;
                    }
                    if (input_str[k]==')') {
                        temp_left++;
                        if (temp_left==temp_right) {
                            right=k;
                            break;
                        }
                    }
                }
                break;
            }

            
            if (isdigit(input_str[j])==FALSE && input_str[j]!='.') {
                right=j-1;
                break;
            }
            if (j==(int)strlen(input_str)-1) {
                right=(int)strlen(input_str)-1;
            }
        }
        
        //printf("%s\n",input_str);
        //printf("left-1 %c right+1 %c\n",input_str[left-1],input_str[right+1]);
        // here may be some problem, but i do not want to solve
        // left may be 0, so left-1 may be -1
        if (input_str[left-1]!='(' || input_str[right+1]!=')') {
            char *temp=substr(input_str, left, right+1);
            char *temp2=append("(", append(temp, ")"));
            input_str=replace_from_index_to_index(input_str, temp, temp2, left, right+1);
        }
    }
    return input_str;
}

// default no decimal existed
char *addParenthesisForPowerAndCalculateIfNecessary(char *input_str){
    //printf("|%s|\n",input_str);
    int i=0;
    int count_of_power=count_str(input_str, "^");
    for (i=0; i<count_of_power; i++) {
        //printf("input_str %s\n",input_str);
        int index_of_power=find(input_str, "^");
        int j=i;
        while (j!=0) {
            index_of_power=find_from_index(input_str, "^", index_of_power+1);
            j--;
        }
        
        int left;
        int right;
        
        j=index_of_power;
        for (j=index_of_power-1; j>=0; j--) {
            if (input_str[j]==')') {
                int k=j;
                int temp_right=0;
                int temp_left=0;
                for (k=j; k>=0; k--) {
                    if (input_str[k]==')') {
                        temp_right++;
                        continue;
                    }
                    if (input_str[k]=='(') {
                        temp_left++;
                        if (temp_left==temp_right) {
                            left=k;
                            break;
                        }
                    }
                }
                break;
            }
            
            if (isdigit(input_str[j])==FALSE && input_str[j]!='.') {
                left=j+1;
                break;
            }
            if (j==0) {
                left=0;
                break;
            }
        }
        j=index_of_power+1;
        for (j=index_of_power+1; j<(int)strlen(input_str); j++) {
            if (input_str[j]=='(') {
                int k=j;
                int temp_right=0;
                int temp_left=0;
                for (k=j; k<(int)strlen(input_str); k++) {
                    if (input_str[k]=='(') {
                        temp_right++;
                        continue;
                    }
                    if (input_str[k]==')') {
                        temp_left++;
                        if (temp_left==temp_right) {
                            right=k;
                            break;
                        }
                    }
                }
                break;
            }
            
            
            if (isdigit(input_str[j])==FALSE && input_str[j]!='.') {
                right=j-1;
                break;
            }
            if (j==(int)strlen(input_str)-1) {
                right=(int)strlen(input_str)-1;
            }
        }
        
        char *power_str=substr(input_str, left, right+1);
        //printf("find %s\n",substr(input_str, left, right+1));
        char *base=substr(power_str,0,find(power_str, "^"));
        char *power=substr(power_str, find(power_str, "^")+1, (int)strlen(power_str));
        
        if (base[0]=='('&&base[(int)strlen(base)-1]==')') {
            base=substr(base, 1,(int)strlen(base)-1);
        }
        
        if (power[0]=='('&&power[(int)strlen(power)-1]==')') {
            power=substr(power, 1,(int)strlen(power)-1);
        }
        //printf("power is %s\n",power);
        char *decimal_power=fraction_to_double(power);
        
        // power is integer
        char *with_str="";
        if (atof(decimal_power)==atoi(decimal_power)) {
            // base if fraction
            if (stringIsFraction(base)) {
                char *numerator=numerator_of_fraction(base);
                char *denominator=denominator_of_fraction(base);
                numerator=intToCString(pow(atoi(numerator),atoi(power)));
                denominator=intToCString(pow(atoi(denominator),atoi(power)));
                with_str=simplify_fraction(numerator, denominator);
                
                input_str=replace_from_index_to_index(input_str, power_str, with_str, left, right+1);
                count_of_power--;
                i--;
                continue;
            }
            // base if integer... this place thinks base is integer defaultly.
            else{
                with_str=intToCString(pow(atoi(base),atoi(power)));
                input_str=replace_from_index_to_index(input_str, power_str, with_str, left, right+1);
                count_of_power--;
                i--;
                continue;
            }
                        
        }
        
        
        //printf("%s\n",input_str);
        //printf("left-1 %c right+1 %c\n",input_str[left-1],input_str[right+1]);
        // here may be some problem, but i do not want to solve
        // left may be 0, so left-1 may be -1
        
        if (input_str[left-1]!='(' || input_str[right+1]!=')') {
            char *temp=substr(input_str, left, right+1);
            char *temp2=append("(", append(temp, ")"));
            input_str=replace_from_index_to_index(input_str, temp, temp2, left, right+1);
        }
    }
    //printf("AFTER ADD %s\n",input_str);
    return input_str;
}


char *eval_simple_str_for_fraction_power_root(char *input_str){
    //printf("1111input_str %s\n",input_str);

    int calculate_appointed_order_calculation=1;
    
    
    while(TRUE){
        //printf("\n\n\n\ncalculate_appointed_order_calculation---->%d\n",calculate_appointed_order_calculation);
        char *temp=countFirstOrderSignAndChangeTheStrOnlyOnceForFractionAndRootAndPower(input_str,calculate_appointed_order_calculation);
        //printf("temp is %s\n",temp);
        if (strcmp(temp, "None")==0) {
            //printf("break");
            break;
        }
        else{
            input_str=temp;
        }
        calculate_appointed_order_calculation++;
    }
    //printf("come out\n");
    //printf("input str now is |%s|\n",input_str);
    return countFromExpressionForFractionAndRootAndPower(input_str);
    // return (char*)output_str;
}

//(2^4)^0.5 --->(2^4)^(1/2)
char *changeAllDecimalToFraction(char *input_str){
    int count_of_dot=count_str(input_str, ".");
    int i=0;
    for (i=0;i<count_of_dot;i++) {
        int index_of_dot=find(input_str, ".");
        int left=index_of_dot;
        int right=index_of_dot;
        int a=0;
        for (a=index_of_dot-1; a>=0; a--) {
            if (isdigit(input_str[a])==FALSE) {
                left=a+1;
                break;
            }
            if (a==0) {
                left=0;
                break;
            }
        }
        for(a=index_of_dot+1;a<(int)strlen(input_str);a++){
            if (isdigit(input_str[a])==FALSE) {
                right=a-1;
                break;
            }
            if (a==(int)strlen(input_str)-1) {
                right=(int)strlen(input_str)-1;
                break;
            }
        }
        
        char *decimal=substr(input_str, left, right+1);
        char *with_str=double_to_fraction(decimal);
        with_str=append("(", with_str);
        with_str=append(with_str, ")");
        input_str=replace_from_index_to_index(input_str, decimal, with_str, left, right+1);
    }
    return input_str;
}



char *eval_for_fraction_root_power(char *input_str){
    //printf("#### eval_for_fraction_root_power ####\ninput_str %s\n",input_str);
    input_str=trim(input_str);
    input_str=changeAllDecimalToFraction(input_str);
    input_str=addParenthesisForPowerAndCalculateIfNecessary(input_str);
    //printf("#### eval_for_fraction_root_power ####\ninput_str %s\n",input_str);
    
    
    /*
     if(input_str[0]!='('){
     //char *temp=malloc(sizeof(char)*strlen(input_str)+2);
     char temp[1000]="(";
     //temp="(";
     strcat(temp,input_str);
     
     strcat(temp,")");
     input_str=temp;
     }*/
    //int count=count_str(input_str,"(");
    //printf("count is %d\n",count);
    //printf("after automatically add (), the input_str is %s\n",input_str);
    
    int count_of_left_bracket=count_str(input_str,"(");
    int count_of_right_bracket=count_str(input_str,")");
    
    //char *output;
    if(count_of_left_bracket!=count_of_right_bracket){
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

printf("Mistakes occurred while calling function eval_for_fraction_root_power:\nnum of ( != num of )");
        exit(1);
    }
    
    
    //int index_of_final_left_bracket=0;
    //int index_of_first_right_bracket=(int)strlen(input_str)-1;
    
    //int i=0;
    while(count_str(input_str,"(")!=0){
        //printf("--->%s\n",input_str);

        int index_of_final_left_bracket;//=find(input_str, "(");
        int index_of_first_right_bracket=find(input_str, ")");
        
        int k=0;
        for (k=index_of_first_right_bracket; k>=0; k--) {
            if (input_str[k]=='(') {
                index_of_final_left_bracket=k;
                break;
            }
        }
        
        /*
        while (TRUE) {
            
            int temp=find_from_index(input_str, "(", index_of_final_left_bracket+1);
            if (temp==-1 || temp>index_of_first_right_bracket) {
                break;
            }
            else {
                index_of_final_left_bracket=temp;
            }
            
        }*/
        
        
        //printf("index of ( is %d\n",index_of_final_left_bracket);
        //printf("index of ) is %d\n",index_of_first_right_bracket);
        //printf("inside parenthesis |%s|\n",substr(input_str,index_of_final_left_bracket+1,index_of_first_right_bracket));
        
        char *temp="";
        if (input_str[index_of_first_right_bracket+1]=='^') {
            temp=substr(input_str,0,index_of_final_left_bracket);
            temp=append(temp, "[");
        }
        else{
            temp=substr(input_str,0,index_of_final_left_bracket);
        }
        char *part_output;
        char *string_in_bracket=substr(input_str,index_of_final_left_bracket+1,index_of_first_right_bracket);
        //printf("string_in_bracket %s\n",string_in_bracket);
        //printf("input_str is %s\n",input_str);
        if (find(string_in_bracket, "^")!=-1) {
            //((3/9*(6^3)*2)^0.5)--->3/9*[6^3]*2--->[3/9*[6^3]*2]--->[[3/9*[6^3]*2]^0.5]
            // Mistake will occurred, so I need to change the code
            int z=find(string_in_bracket,"^");
            int index_of_left=-1; //index of [
            for (; z>=0; z--) {
                if (string_in_bracket[z]=='[') {
                    index_of_left=z;
                    break;
                }
            }
            
                // not (3/9*[6^3]*2+[2^3]*2) case
            if (index_of_left!=-1) {
                //printf("FIND[]");
                    // calculate 3/9* *2+ *2
                    
                int calculate_appointed_order_calculation=1;
                    
                    
                while(TRUE){
                    //printf("\n\n\n\ncalculate_appointed_order_calculation---->%d\n",calculate_appointed_order_calculation);
                    char *temp=countFirstOrderSignAndChangeTheStrOnlyOnceForFractionAndRootAndPowerWithAddingParenthesisForPower(string_in_bracket,calculate_appointed_order_calculation);
                        //printf("temp is %s\n",temp);
                    if (strcmp(temp, "None")==0) {
                        //printf("break");
                        break;
                    }
                    else{
                        string_in_bracket=temp;
                    }
                    calculate_appointed_order_calculation++;
                }
                    
                part_output=string_in_bracket;
                
                
            }
                //
            else{
                    part_output=append("[", append(string_in_bracket, "]"));
            }
    
        }
        else{
            part_output=eval_for_fraction_root_power(string_in_bracket);
            if (stringIsFraction(part_output)||part_output[0]=='-') {
                part_output=append("{", append(part_output, "}"));
            }
            
        }
        //printf("part_output %s\n",part_output);
        
        // 3/(6/2) case
        if (index_of_final_left_bracket!=0 && input_str[index_of_final_left_bracket-1]=='/' && find(string_in_bracket, "^")==-1) {
            int a=index_of_final_left_bracket-2;
            int index_of_first_num=0; // this initialization must be 0....
            // 3/(6/2)---> 3 is what i want
            for (a=index_of_final_left_bracket-2; index_of_final_left_bracket>=0; a--) {
                if (isdigit(input_str[a]) || input_str[a]==')' || input_str[a]=='(') {
                    continue;
                }
                else{
                    index_of_first_num=a+1;
                    break;
                }
            }
            char *first_num=substr(input_str, index_of_first_num, index_of_final_left_bracket-1);
            //printf("first_num %s\n",first_num);
            
            // 3/4/(3/4)case
            char *temp_value;
            if (index_of_first_num!=0 && input_str[index_of_first_num-1]=='/') {
                // multiply 4 and (3/4)
                temp_value=fraction_time(first_num, part_output);
            }
            else{
                // divide 4 by (3/4)
                temp_value=fraction_divide(first_num, part_output);
            }
            //printf("temp_value %s\n",temp_value);
            temp=substr(input_str, 0, index_of_first_num);
            temp=append(temp, temp_value);

            //printf("that char is %c\n",input_str[index_of_first_right_bracket+1]);
            if (input_str[index_of_first_right_bracket+1]=='^') {
                //printf("it is ^");
                temp=append(temp, "]");
            }
            
            temp=append(temp,substr(input_str,index_of_first_right_bracket+1,(int)strlen(input_str)));
            input_str=temp;
            continue;
        }
        
        
        
        temp=append(temp,part_output);
        
        //printf("that char is %c\n",input_str[index_of_first_right_bracket+1]);
        if (input_str[index_of_first_right_bracket+1]=='^') {
            //printf("it is ^");
            temp=append(temp, "]");
        }

        
        
        temp=append(temp,substr(input_str,index_of_first_right_bracket+1,(int)strlen(input_str)));
        //printf("temp now is %s\n",temp);
        input_str=temp;
        //printf("input_str is %s\n",input_str);
        //printf("count of ( %d\n",count_str(input_str, "("));
    }
    //printf("---> %s\n",input_str);
    if (find(input_str, "^")!=-1) {
        input_str=replace(input_str, "[", "(");
        input_str=replace(input_str, "]", ")");
    }
    if (find(input_str, "{")!=-1) {
        input_str=replace(input_str, "{", "(");
        input_str=replace(input_str, "}", ")");
    }
    //printf("---> %s\n",input_str);
    input_str=eval_simple_str_for_fraction_power_root(input_str);
    
    
    
    //printf("final input_str %s\n",input_str);
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
    //printf("input_str is %s\n",input_str);
    if (strcmp(denominator_of_fraction(input_str),"1")==0) {
        return numerator_of_fraction(input_str);
    }
    
    //change ((-5)^(3/4)) to (-5)^(3/4)
    //if (input_str[0]=='('&&input_str[(int)strlen(input_str)-1]==')') {
    //    input_str=substr(input_str, 1, (int)strlen(input_str)-1);
    //}
    return input_str;
}

// 2^0.5--->√(2)    2^2---->4
char *changePowerToRoot_ForEvalFinal(char *input_str){
    printf("changePowerToRoot %s\n",input_str);
    int index_of_power_sign=find_from_behind(input_str, "^");
    if (index_of_power_sign==-1) {
        printf("Mistake occurred whiling calling function changePowerToRoot\nNo ^ found\n");
        exit(0);
    }
    char *num=substr(input_str, 0, index_of_power_sign);
    char *power=substr(input_str, index_of_power_sign+1, (int)strlen(input_str));
    //num=eval_for_fraction(num);
    //power=eval_for_fraction(power);
    
    printf("num %s\npower %s\n",num,power);
    
    // 2^(1/2)   (1/2)^(3/4)
    if (stringIsFraction(power)==TRUE) {
        //(1/2)^(1/3)
        if (stringIsFraction(num)==TRUE) {
            char *numerator_of_power=numerator_of_fraction(power);
            char *denominator_of_power=denominator_of_fraction(power);
            
            /*
             bool can_use_root_sign=TRUE;
             int temp_denominator=atoi(denominator_of_power);
             while (TRUE) {
             if (temp_denominator%2!=0) {
             can_use_root_sign=FALSE;
             break;
             }
             else{
             temp_denominator=temp_denominator/2;
             if (temp_denominator==1) {
             break;
             }
             }
             }*/
            
            //(1/2)^(3/4)---->(1/2)^3
            num=append("(", append(num, ")"));
            char *temp=changePowerToRoot(append(num, append("^", numerator_of_power)));
            
            if (atoi(denominator_of_power)==2) {
                if (temp[0]=='(') {
                    return simplify_root(append("√", temp));
                }
                return simplify_root(append("√(", append(temp,")")));
            }
            else{
                return append(temp, append("^(1/", append(denominator_of_power, ")")));
            }
            
        }
        //2^(1/3)
        else if(stringIsDigit(num)==TRUE){
            char *numerator_of_power=numerator_of_fraction(power);
            char *denominator_of_power=denominator_of_fraction(power);
            
            /*
             bool can_use_root_sign=TRUE;
             int temp_denominator=atoi(denominator_of_power);
             while (TRUE) {
             if (temp_denominator%2!=0) {
             can_use_root_sign=FALSE;
             break;
             }
             else{
             temp_denominator=temp_denominator/2;
             if (temp_denominator==1) {
             break;
             }
             }
             }*/
            
            //2^(3/4)--->2^3--->8
            char *temp=changePowerToRoot(append(num, append("^", numerator_of_power)));
            
            if (atoi(denominator_of_power)==2) {
                return simplify_root(append("√(", append(temp,")")));
            }
            else{
                return append(temp, append("^(1/", append(denominator_of_power, ")")));
            }
            
        }
        else{
            char *numerator_of_power=numerator_of_fraction(power);
            char *denominator_of_power=denominator_of_fraction(power);
            
            
            //(1/2)^(3/4)---->(1/2)^3
            num=append("(", append(num, ")"));
            char *temp=num;
            
            if (atoi(denominator_of_power)==2 && atoi(numerator_of_power)==1) {
                if (temp[0]=='(') {
                    return simplify_root(append("√", temp));
                }
                return simplify_root(append("√(", append(temp,")")));
            }
            else{
                return input_str;
            }
            
        }
    }
    
    
    
    
    //2^2
    else if(stringIsDigit(power)==TRUE){
        // (1/2)^(2)
        if (stringIsFraction(num)==TRUE) {
            char *numerator=numerator_of_fraction(num);
            char *denominator=denominator_of_fraction(num);
            
            numerator=changePowerToRoot(append(numerator, append("^", power)));
            denominator=changePowerToRoot(append(denominator, append("^", power)));
            
            char *output=simplify_fraction(numerator, denominator);
            if (stringIsFraction(output)) {
                return append("(", append(output, ")"));
            } else {
                return output;
            }
            
            //return simplify_fraction(numerator, denominator);
            
        }
        //2^(2)
        else if(stringIsDigit(num)){
            return intToCString((int)pow(atoi(num),atoi(power)));
        }
        else{
            // ((1/3)*(6^3)*2+(3/2)*(2^4))^0.5
            return input_str;
        }
        
    }
    // ((1/3)*(6^3)*2+(3/2)*(2^4))^0.5
    else {
        return input_str;
    }
}


char *eval_final(char *input_str){
    input_str=eval_for_fraction_root_power(input_str);
    //printf("after eval %s\n",input_str);
        
    int num_of_power=count_str(input_str, "^");
    int begin=0;
    int i=0;
    while (i<num_of_power) {
        int left=find_from_index(input_str, "(", begin);
        int right=find_from_index(input_str, ")", left+1);
        while (TRUE) {
            char *str=substr(input_str, left, right+1);
            if (count_str(str, "(")!=count_str(str, ")")) {
                right=find_from_index(input_str, ")", right+1);
            }
            else{
                break;
            }
        }
        begin=right+1;
        
        char *replace_str=substr(input_str, left, right+1);
        
        if (find(replace_str, "^")==-1) {
            begin=begin;
            continue;
        }
        
        char *string_inside_parenthensis=substr(replace_str, 1, (int)strlen(replace_str)-1);
        char *with_str=changePowerToRoot_ForEvalFinal(string_inside_parenthensis);
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, left, right+1);
        
        begin=begin-((int)strlen(replace_str)-(int)strlen(with_str));
        i++;
    }
    
    int index_of_root=find(input_str, "√");
    char *save="";
    if (index_of_root!=-1) {
        printf("find √\n");
        while (TRUE) {
            int left=0;
            int right=find_from_index(input_str, ")", index_of_root);
            int i=index_of_root-1;
            for (i=index_of_root-1; i>=0; i--) {
                if (i==0) {
                    left=i;
                    break;
                }
                if (isdigit(input_str[i])==FALSE) {
                    left=i+1;
                    break;
                }
            }
            char *replace_str=substr(input_str, left, right+1);
            save=append(save, replace_str);
            save=append(save, ",");
            
            index_of_root=find_from_index(input_str, "√", index_of_root+1);
            if (index_of_root==-1) {
                break;
            }
        }
    }
    //printf("save is %s\n",save);
    return input_str;
}

char *eval_decimal(char *input_str){
    return eval(eval_for_fraction_root_power(input_str));
}

/*
char *Walley_Mathomatic_Parse_For_Fraction(char *input_str){
        
    // replace sin cos 
    // change  (sin(3)+1)/cos(3)--->(X1+1)/(X2)
    //
    char **replace_str_list=(char**)malloc(sizeof(char*)*10000);
    int i=0;
    while (count_str(input_str, "sin(")!=0) {
        int index=find(input_str, "sin(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    while (count_str(input_str, "cos(")!=0) {
        int index=find(input_str, "cos(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    while (count_str(input_str, "tan(")!=0) {
        int index=find(input_str, "tan(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    while (count_str(input_str, "cot(")!=0) {
        int index=find(input_str, "cot(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    while (count_str(input_str, "sec(")!=0) {
        int index=find(input_str, "sec(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    while (count_str(input_str, "csc(")!=0) {
        int index=find(input_str, "csc(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    while (count_str(input_str, "exp(")!=0) {
        int index=find(input_str, "exp(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    while (count_str(input_str, "log10(")!=0) {
        int index=find(input_str, "log10(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    
    //printf("input_str now is %s\n",input_str);
    
    char *output;
    char *temp=append("x=",input_str);
    
    
    
    matho_parse(temp, NULL);
    //matho_process("x", &output);
    matho_process("code", &output);
    output=substr(output, find(output, "=")+1, (int)strlen(output)-1);
    output=trim(output);
    
    
    // return sin cos tan cot sec csc exp log10
    int a=0;
    for (a=0; a<i; a++) {
        char *replace_str_a=replace_str_list[a];
        int index_of_mark=find(replace_str_a ,"#");
        char *replace_str=substr(replace_str_a, 0, index_of_mark);
        char *with_str=substr(replace_str_a, index_of_mark+1, (int)strlen(replace_str_a));
        output=replace(output,with_str,replace_str);
    }
    
    //printf("output is |%s|\n",output);
    if (output[0]=='('&&output[(int)strlen(output)-1]==')') {
        output=substr(output, 1, (int)strlen(output)-1);
    }
    return output;
}

char *Walley_Mathomatic_Parse_For_Decimal(char *input_str){
    
    char *output;
    char *temp=append("x=",input_str);
    
    matho_parse(temp, NULL);
    //matho_process("x", &output);
    matho_process("code", &output);
    output=substr(output, find(output, "=")+1, (int)strlen(output)-1);
    output=trim(output);
        
    if (output[0]=='('&&output[(int)strlen(output)-1]==')') {
        output=substr(output, 1, (int)strlen(output)-1);
    }
    
    output=cleanDotZeroAfterNum(output);

    //printf("Output is |%s|\n",output);
    
    return output;
}
*/


/* 
 ############################################################################################################################
 ############################################################################################################################
 ############################################################################################################################
 ############################################################################################################################
 ############# New Fraction Math Parser Support Var uninitialized written by Yiyi Wang on Dec 26 ############################
 ############################################################################################################################
 ############################################################################################################################
 ############################################################################################################################
 ############################################################################################################################

 
 */


char *eval_for_fraction_with_alpha(char *input_str);


//calculate 9/2/4--->9/8
char *calculate_for_division_for_fraction(char *input_str){
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
                    char *simplified=simplify_fraction(numerator_num, denominator);
                    //   3/4
                    if (stringIsFraction(simplified)) {
                        char *temp_numerator=numerator_of_fraction(simplified);
                        char *temp_denominator=denominator_of_fraction(simplified);
                        char *output=append(temp_numerator, append(rest, append("/", temp_denominator)));
                        output=changeOperatorToStrForWhoStr(output);
                        return output;
                    }
                    // 3
                    else{
                        char *output=append(simplified, rest);
                        return changeOperatorToStrForWhoStr(output);
                    }
                }
                else{
                    denominator=append("#LEFT#", append(denominator, "#RIGHT#"));
                    
                    char *output=append(numerator, append("/", denominator));
                    return changeOperatorToStrForWhoStr(output);
                }
            }
        }
    }
}

//clean_code  1/(4)--->1/4  1/(x+4)--->1/(x+4)
char *clean_math_output_for_fraction(char *input_str){
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

char *eval_CalculatePowerAtFirst_with_alpha_for_fraction(char *input_str){
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
        
        left_str=eval_for_fraction_with_alpha(left_str);
        right_str=eval_for_fraction_with_alpha(right_str);
        char *with_str="";//numToCString(pow(atof(left_str), atof(right_str)));
        //printf("left %s right %s\n",left_str,right_str);
        // 3^4
        if (stringIsDigit(left_str)&&stringIsDigit(right_str)) {
            with_str=numToCString(pow(atof(left_str), atof(right_str)));
            with_str=cleanDotZeroAfterNum(with_str);
        }
        else if(stringHasAlpha(left_str)||stringHasAlpha(right_str)){
            bool left_str_has_alpha=stringHasAlpha(left_str);
            bool right_str_has_alpha=stringHasAlpha(right_str);
            if (left_str[0]!='('&&(left_str_has_alpha||stringIsFraction(left_str))&&stringIsAlpha(left_str)==FALSE&&stringIsDigit(left_str)==FALSE) {
                with_str=append("(", append(left_str, ")^("));
            }
            else{
                with_str=append(left_str, "^");
            }
            if (right_str[0]!='('&&(right_str_has_alpha||stringIsFraction(right_str))&&stringIsAlpha(left_str)==FALSE&&stringIsDigit(right_str)==FALSE) {
                with_str=append(with_str, append("(", append(right_str, ")")));
            }
            else{
                with_str=append(with_str, right_str);
            }
            
        }
        else{
            char *temp_with_var=numToCString(pow((double)atof(eval(left_str)), (double)atof(eval(right_str))));
            int temp_length1=(int)strlen(temp_with_var);
            temp_with_var=cleanDotZeroAfterNum(temp_with_var);
            int temp_length2=(int)strlen(temp_with_var);
            //printf("temp_with_var %s\n",temp_with_var);
            if (atof(temp_with_var)==(int)atof(temp_with_var)) {
                with_str=temp_with_var;
            }
            // there maybe some mistake
            else if (temp_length1-temp_length2>=5){
                with_str=temp_with_var;
            }
            else{
                // this code below may affect efficiency....
                with_str=eval_for_fraction_root_power(input_str);
            }
            
            //printf("with_str--->%s\n",with_str);
        }
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, left, right+1);
        
        
    }
    return input_str;
}

// it does not support + and - now
char* Walley_Operator_with_alpha_for_fraction(char* num1_str,char* num2_str,char sign){
    // after running codes..
    // it may have input_str like
    // x#time#3#time#y#divide#4
    
    char *output_output="";
    
    // or
    // if has alpha like 3*x, then return 3#time#x
    bool num1_is_digit=stringIsDigit(num1_str);
    bool num2_is_digit=stringIsDigit(num2_str);
        
    if (num1_is_digit==TRUE&&num2_is_digit==TRUE) {
        if (sign!='/') {
            //return cleanDotZeroAfterNum(numToCString(Walley_Operator(atof(num1_str), atof(num2_str), sign)));
            output_output=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof(num1_str), atof(num2_str), sign)));
            
        }
        else{
            //return changeOperatorToStrForWhoStr(Walley_Operator_For_Fraction(num1_str, num2_str, sign));
            output_output=changeOperatorToStrForWhoStr(Walley_Operator_For_Fraction(num1_str, num2_str, sign));;
            //output_output=Walley_Operator_For_Fraction(num1_str, num2_str, sign);
        }
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
                    char *with_str=Walley_Operator_with_alpha_for_fraction(num, num2_str, sign);
                    //return replace_from_index_to_index(num1_str, replace_str, with_str, 0, index+1);
                    output_output=replace_from_index_to_index(num1_str, replace_str, with_str, 0, index+1);
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
        output_output=calculate_for_division_for_fraction(output_output);
    }
    return output_output;
    
}

char *countFirstOrderSignAndChangeTheStrOnlyOnce_with_alpha_for_fraction(char *input_str){
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
            
            
            char* output_str=Walley_Operator_with_alpha_for_fraction(num1_str,num2_str,input_str[i]);
            
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

char* countFromExpression_with_alpha_for_fraction(char *var_value) {
    
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
        double previous_num=0;
        bool begin = FALSE;
        
        char *num1_str;
        char *num2_str;
        
        
        for (; i < (int)strlen(input); i++) {
            if (isSign(input[i]) == TRUE && input[i]!='/') {
                num1_str = substr(input, temp, i);
                //printf("sign %c\n",input[i]);
                //printf("num1_str %s\n",num1_str);

                
                j = i + 1;
                int final_place=0; // for a+b+4--->final_place=3
                for (; j < (int) strlen(input); j++) {
                    if (input[i]=='+'&&input[i+1]=='+'&&i+1==(int)strlen(input)-1) {
                        num2_str="1";
                        i++;
                        break;
                    }
                    if (input[i]=='-'&&input[i+1]=='-'&&i+1==(int)strlen(input)-1) {
                        num2_str="1";
                        i++;
                        break;
                    }
                    
                    if (isSign(input[j]) == TRUE && j!=i+1) {
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
                        char *temp_str=substr(input, i, final_place);
                        temp_str=replace(temp_str, "--", "");
                        my_output_str=append(my_output_str, temp_str);  // get +a
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
                
                i=j-1;
                
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
        
        // x=1*1-1*1
        if (stringIsEmpty(my_output_str)==TRUE) {
            my_output_str=temp_output;
        }
        
        my_output_str=cleanDotZeroAfterNum(my_output_str);
        if (my_output_str[0]=='+') {
            my_output_str=substr(my_output_str, 1, (int)strlen(my_output_str));
        }
        return my_output_str;
    }
}


// calculate outside parenthesis
char *eval_simple_str_with_alpha_for_fraction(char *input_str){
    // at this place, eg 3*x+5.
    // I will replace 3*x with 3#time#x    #time# ---> *
    while(hasFirstOrderSignExist(input_str)==TRUE){
        input_str=countFirstOrderSignAndChangeTheStrOnlyOnce_with_alpha_for_fraction(input_str);
    }
    // Afte running the above code.
    // input_str maybe like.
    // 3#time#x#time#y+5/3
    return countFromExpression_with_alpha_for_fraction(input_str);
}

// Calculate like (y*3*4/5^2+x)*y*3*4+x^(3/4)*y--->12*(0.48*y+x)*y+(x)^0.75*y
char *eval_for_fraction_with_alpha(char *input_str){
        
    char **replace_str_list;
    Str_initStringList(&replace_str_list);
    int INDEX_OF_SAVED_MATH_FUNCTIOn=1;
    while (count_str(input_str, "sin(")!=0) {
        int index=find(input_str, "sin(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        Str_addString(&replace_str_list, append(replace_str, append("#", with_str)));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
    while (count_str(input_str, "cos(")!=0) {
        int index=find(input_str, "cos(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        Str_addString(&replace_str_list, append(replace_str, append("#", with_str)));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
    while (count_str(input_str, "tan(")!=0) {
        int index=find(input_str, "tan(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        Str_addString(&replace_str_list, append(replace_str, append("#", with_str)));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
    while (count_str(input_str, "cot(")!=0) {
        int index=find(input_str, "cot(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        Str_addString(&replace_str_list, append(replace_str, append("#", with_str)));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
    while (count_str(input_str, "sec(")!=0) {
        int index=find(input_str, "sec(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        Str_addString(&replace_str_list, append(replace_str, append("#", with_str)));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
    while (count_str(input_str, "csc(")!=0) {
        int index=find(input_str, "csc(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        Str_addString(&replace_str_list, append(replace_str, append("#", with_str)));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
    while (count_str(input_str, "exp(")!=0) {
        int index=find(input_str, "exp(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        Str_addString(&replace_str_list, append(replace_str, append("#", with_str)));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
    while (count_str(input_str, "log10(")!=0) {
        int index=find(input_str, "log10(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(INDEX_OF_SAVED_MATH_FUNCTIOn));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        Str_addString(&replace_str_list, append(replace_str, append("#", with_str)));
        INDEX_OF_SAVED_MATH_FUNCTIOn++;
    }
        
    
    input_str=changeAllDecimalToFraction(input_str);
    //input_str=addParenthesisForPowerAndCalculateIfNecessary(input_str);
        
    
    char **SAVE_EXPRESSION_THAT_HAS_ALPHA_IN_BRACKTER; // save (y*3*4/5^2+x) to #SAVED1#
    int INDEX_OFR_SAVE_EXPRESSION=0;                   //                             1
    Str_initStringList(&SAVE_EXPRESSION_THAT_HAS_ALPHA_IN_BRACKTER);
    input_str=trim(input_str);
    input_str=eval_CalculatePowerAtFirst_with_alpha_for_fraction(input_str);
    int count_of_left_bracket=count_str(input_str,"(");
    int count_of_right_bracket=count_str(input_str,")");
    
    //char *output;
    if(count_of_left_bracket!=count_of_right_bracket){
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

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
        
        char *part_output=eval_simple_str_with_alpha_for_fraction(substr(input_str,index_of_final_left_bracket+1,index_of_first_right_bracket));
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
    
    input_str=eval_simple_str_with_alpha_for_fraction(input_str);
    
    x=INDEX_OFR_SAVE_EXPRESSION-1;
    for (; x>=0; x--) {
        char *replace_str=append("#SAVED", append(intToCString(x), "#"));
        char *with_str=SAVE_EXPRESSION_THAT_HAS_ALPHA_IN_BRACKTER[x+1];
        input_str=replace(input_str,replace_str, with_str);
    }
    input_str=changeOperatorStrToOriginalForWhoStr(input_str);

    input_str=replace(input_str, "--","+");
    
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
    
    input_str=clean_math_output_for_fraction(input_str);

    
    // return sin cos tan cot sec csc exp log10
    a=1;
    for (a=1; a<INDEX_OF_SAVED_MATH_FUNCTIOn; a++) {
        char *replace_str_a=replace_str_list[a];
        int index_of_mark=find(replace_str_a ,"#");
        char *replace_str=substr(replace_str_a, 0, index_of_mark);
        char *with_str=substr(replace_str_a, index_of_mark+1, (int)strlen(replace_str_a));
        input_str=replace(input_str,with_str,replace_str);
    }
    if (input_str[0]=='+') {
        input_str=substr(input_str, 1, (int)strlen(input_str));
    }
        
    return input_str;
    
}

// 3.0/4.0 ----> 3/4
char *Walley_Mathomatic_Clean_Dot_0(char *input_str){
    int i=0;
    for (i=0;i<(int)strlen(input_str)-1;i++){
        if (input_str[i]=='.'&&input_str[i+1]=='0'&&(i+2==(int)strlen(input_str)||isSign(input_str[i+2])||input_str[i+2]==' ')) {
            input_str=replace_from_index_to_index(input_str,".0" ,"",i, i+2);
            i=i-1;
        }
    }
    return input_str;
}


char *Walley_Mathomatic_Parse_For_Fraction(char *input_str){
    
    // replace sin cos
    // change  (sin(3)+1)/cos(3)--->(X1+1)/(X2)
    //
    
    char **replace_str_list;
    Str_initStringList(&replace_str_list);
    int i=1;
    while (count_str(input_str, "sin(")!=0) {
        int index=find(input_str, "sin(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    while (count_str(input_str, "cos(")!=0) {
        int index=find(input_str, "cos(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    while (count_str(input_str, "tan(")!=0) {
        int index=find(input_str, "tan(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    while (count_str(input_str, "cot(")!=0) {
        int index=find(input_str, "cot(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    while (count_str(input_str, "sec(")!=0) {
        int index=find(input_str, "sec(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    while (count_str(input_str, "csc(")!=0) {
        int index=find(input_str, "csc(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    while (count_str(input_str, "exp(")!=0) {
        int index=find(input_str, "exp(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    while (count_str(input_str, "log10(")!=0) {
        int index=find(input_str, "log10(");
        int index_of_left=find_from_index(input_str, "(", index);
        int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
        char *replace_str=substr(input_str, index, index_of_right+1);
        char *with_str=append("MATHH_", intToCString(i));
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, index, index_of_right+1);
        replace_str_list[i]=append(replace_str, append("#", with_str));
        i++;
    }
    
    //printf("input_str now is %s\n",input_str);
    
    char *output;
    char *temp=append("x=",input_str);    
    
    matho_parse(temp, NULL);
    //matho_process("x", &output);
    matho_process("code", &output);
    //printf("output----> %s\n",output);
    matho_clear();
    output=substr(output, find(output, "=")+1, (int)strlen(output)-1);
    output=trim(output);
    //printf("output----> %s\n",output);
    
    // return sin cos tan cot sec csc exp log10
    int a=1;
    for (a=1; a<i; a++) {
        char *replace_str_a=replace_str_list[a];
        int index_of_mark=find(replace_str_a ,"#");
        char *replace_str=substr(replace_str_a, 0, index_of_mark);
        char *with_str=substr(replace_str_a, index_of_mark+1, (int)strlen(replace_str_a));
        output=replace(output,with_str,replace_str);
    }
    
    //printf("output is |%s|\n",output);
    if (output[0]=='('&&output[(int)strlen(output)-1]==')') {
        output=substr(output, 1, (int)strlen(output)-1);
    }
    output=Walley_Mathomatic_Clean_Dot_0(output);

    return output;
}

char *Walley_Mathomatic_Parse_For_Decimal(char *input_str){
    
    char *output;
    char *temp=append("x=",input_str);
    
    matho_parse(temp, NULL);
    //matho_process("x", &output);
    matho_process("code", &output);
    matho_clear();
    output=substr(output, find(output, "=")+1, (int)strlen(output)-1);
    output=trim(output);
    
    if (output[0]=='('&&output[(int)strlen(output)-1]==')') {
        output=substr(output, 1, (int)strlen(output)-1);
    }
    
    
    output=cleanDotZeroAfterNumAndKeepOneZero(output);
    
    //printf("Output is |%s|\n",output);
    return output;
}


