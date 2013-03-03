//
//  walley_math_parser.h
//  Walley_MathParse
//
//  Created by shd101wyy on 13-2-14.
//  Copyright (c) 2013年 shd101wyy. All rights reserved.
//

#include "walley_math_infix_to_postfix.h"

/*
 Example
 The infix expression "5 + ((1 + 2) * 4) − 3" can be written down like this in RPN:
 
 5 1 2 + 4 * + 3 -
 The expression is evaluated left-to-right, with the inputs interpreted as shown in the following table (the Stack is the list of values the algorithm is "keeping track of" after the Operation given in the middle column has taken place):
 
 Input	Operation	Stack	Comment
 5	Push value	5
 1	Push value	1
 5
 2	Push value	2
 1
 5
 +	Add	3
 5	Pop two values (1, 2) and push result (3)
 4	Push value	4
 3
 5
 *	Multiply	12
 5	Pop two values (3, 4) and push result (12)
 +	Add	17	Pop two values (5, 12) and push result (17)
 3	Push value	3
 17
 −	Subtract	14	Pop two values (17, 3) and push result (14)
 Result	(14)
 When a computation is finished, its result remains as the top (and only) value in the stack; in this case, 14.
 
 The above example could be rewritten by following the "chain calculation" method described by HP for their series of RPN calculators:[4]
 
 As was demonstrated in the Algebraic mode, it is usually easier (fewer keystrokes) in working a problem like this to begin with the arithmetic operations inside the parentheses first.
 
 1 2 + 4 * 5 + 3 −
 
 */

struct Math_Data_Array MDA;


// put coeffiecient ahead a*3--> 3*a
// put 3+a---> a+3

char *Walley_Math_Parser_Decimal(char *input_str);

bool stringHasSign(char *input_str){
    int i=0;
    int length=(int)strlen(input_str);
    for (; i<length; i++) {
        if (isSign(input_str[i])) {
            return TRUE;
        }
    }
    return FALSE;
}

// x+4
// 012
// return 1
int indexOfFirstSign(char *input_str){
    int i=0;
    int length=(int)strlen(input_str);
    for (; i<length; i++) {
        if (isSign(input_str[i])) {
            return i;
        }
    }
    return -1;
}
int indexOfFirstSignFromBehind(char *input_str){
    int length=(int)strlen(input_str);
    int i=length-1;
    
    for (; i>=0; i--) {
        if (isSign(input_str[i])) {
            return i;
        }
    }
    return -1;
}

int find_not_in_parenthesis(char *from_str, char *find_str) {
    int index = -1;
    bool find_index = TRUE;
    int i;
    int j;
    for (i = 0; i < (int) strlen(from_str); i++) {
        // I add one code here.
        find_index=TRUE;
        if (from_str[i] == find_str[0] && charIsInParenthesis(from_str,i)==FALSE) {
            for (j = 0; j < (int) strlen(find_str); j++) {
                //printf("Find_Str[j] %c From_Str[i+j] %c\n",find_str[j],from_str[i+j]);
                if (find_str[j] != from_str[i + j]) {
                    //printf("!= %d %d\n",j,j+i);
                    find_index = FALSE;
                    break;
                }
            }
            if (find_index == TRUE) {
                //find_index = TRUE;
                //printf("Fin_Index--->%d\n",i);
                index = i;
                break;
            }
        }
    }
    return index;
}


// x---> 1 x 1
// 12--> 12 0 1
struct Math_Data changeValueToMathDate(char *value){
    struct Math_Data md;
    if (stringHasAlpha(value)==TRUE) {
        md.coefficient="1";
        md.value=value;
        md.power="1";
    }
    else{
        md.coefficient=value;
        md.value="0";
        md.power="1";
    }
    return md;
}

void MDL_operator_for_decimal(struct Math_Data_List *mdl, struct Math_Data md, char sign){
       
    int length=(*mdl).length;
    if (sign=='+' || sign=='-') {
        
        int i=0;
        bool find_same_symbol=FALSE;
        for (; i<length; i++) {
            // find same symbol or number
            if (strcmp((*mdl).math_data_list[i].value,md.value)==0) {
                find_same_symbol=TRUE;
                (*mdl).math_data_list[i].coefficient= cleanDotZeroAfterNum(numToCString(Walley_Operator(atof((*mdl).math_data_list[i].coefficient), atof(md.coefficient), sign)));
            }
        }
        if (find_same_symbol==FALSE) {
            if (sign=='-') {
                md.coefficient=append("-", md.coefficient);
            }
            MDL_addMathData(mdl, md);
        }
    }
    else if(sign=='*'||sign=='/'){
        
        if (length==1) {
            (*mdl).math_data_list[length-1].coefficient=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof((*mdl).math_data_list[length-1].coefficient), atof(md.coefficient), sign)));
            if (stringHasAlpha(md.value)==TRUE) {
                if (stringHasAlpha((*mdl).math_data_list[length-1].value)==TRUE) {
                    
                    if (sign=='*') {
                        char *temp_value=(*mdl).math_data_list[length-1].value;
                        struct TOKEN *tl=Walley_MATH_Lexica_Analysis(temp_value);
                        int length_of_tl=TL_length(tl);
                        
                        //a*a
                        if (length_of_tl==2) {
                            if (strcmp(md.value,(*mdl).math_data_list[length-1].value)==0) {
                                (*mdl).math_data_list[length-1].power=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof((*mdl).math_data_list[length-1].power), atof(md.power), '+')));
                            }
                            else{
                                int i=1;
                                int smallest_end_index=0;
                                bool can_be_smaller_one=FALSE;
                                for (; i<length_of_tl; i++) {
                                    if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                        if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                            smallest_end_index=tl[i].TOKEN_END+1;
                                            can_be_smaller_one=TRUE;
                                            break;
                                        }
                                    }
                                }
                                
                                if (can_be_smaller_one==FALSE) {
                                    (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("*", md.value));
                                }
                                else{
                                    
                                    (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index), append("*", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value)))));
                                }
                                
                            }
                        }
                        else{
                            int i=1;
                            int smallest_end_index=0;
                            bool can_be_smaller_one=FALSE;
                            for (; i<length_of_tl; i++) {
                                if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                    if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                        smallest_end_index=tl[i].TOKEN_END+1;
                                        can_be_smaller_one=TRUE;
                                        break;
                                    }
                                }
                            }
                            
                            if (can_be_smaller_one==FALSE) {
                                (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("*", md.value));
                            }
                            else{
                                
                                (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index), append("*", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value)))));
                            }
                        }
                        
                        
                        
                    }
                    else{
                        // b/b
                        if (strcmp(md.value, (*mdl).math_data_list[length-1].value)==0) {
                            (*mdl).math_data_list[length-1].power=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof((*mdl).math_data_list[length-1].power), atof(md.power), '-')));
                            if (strcmp("0", (*mdl).math_data_list[length-1].power)==0) {
                                (*mdl).math_data_list[length-1].power="1";
                                (*mdl).math_data_list[length-1].coefficient="1";
                                (*mdl).math_data_list[length-1].value="0";
                                
                            }
                        }
                        else{
                            char *temp_value=(*mdl).math_data_list[length-1].value;
                            struct TOKEN *tl=Walley_MATH_Lexica_Analysis(temp_value);
                            int length_of_tl=TL_length(tl);
                            if (length_of_tl==2) {
                                if (strcmp(md.value,(*mdl).math_data_list[length-1].value)==0) {
                                    (*mdl).math_data_list[length-1].power=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof((*mdl).math_data_list[length-1].power), atof(md.power), '-')));
                                }
                                else{
                                    int i=1;
                                    int smallest_end_index=0;
                                    bool can_be_smaller_one=FALSE;
                                    for (; i<length_of_tl; i++) {
                                        if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                            if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                                smallest_end_index=tl[i].TOKEN_END+1;
                                                can_be_smaller_one=TRUE;
                                                break;
                                            }
                                        }
                                    }
                                    
                                    if (can_be_smaller_one==FALSE) {
                                        (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("/", md.value));
                                    }
                                    else{
                                        char *append_power=append("^(", append((*mdl).math_data_list[length-1].power, ")"));
                                        if (strcmp((*mdl).math_data_list[length-1].power, "1")==0) {
                                            append_power="";
                                        }
                                        (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index),append(append_power,append("/", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value))))));
                                        (*mdl).math_data_list[length-1].power="1";
                                    }
                                    
                                }
                                
                            }
                            
                            else{
                                int i=1;
                                int smallest_end_index=0;
                                bool can_be_smaller_one=FALSE;
                                for (; i<length_of_tl; i++) {
                                    if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                        if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                            smallest_end_index=tl[i].TOKEN_END+1;
                                            can_be_smaller_one=TRUE;
                                            break;
                                        }
                                    }
                                }
                                
                                if (can_be_smaller_one==FALSE) {
                                    (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("/", md.value));
                                }
                                else{
                                    (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index), append("/", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value)))));
                                }
                                
                            }
                            
                        }
                    }
                    
                }
                else{
                    (*mdl).math_data_list[length-1].value=md.value;
                }
            }
            
        }
        else{
            char *temp_string=MDL_changeMathDataListToString((*mdl));
            temp_string=append("(", append(temp_string, ")"));
            (*mdl).math_data_list=(struct Math_Data*)realloc((*mdl).math_data_list, sizeof(struct Math_Data)*1);
            (*mdl).length=1;
            if (strcmp(md.value, "0")==0) {
                (*mdl).math_data_list[0].coefficient=md.coefficient;
                (*mdl).math_data_list[0].value=temp_string;
            }
            else{
                (*mdl).math_data_list[0].coefficient=temp_string;
                (*mdl).math_data_list[0].value=md.value;
            }
            
            
            
        }
    }
    // 3^a
    // a^3
    // 3^3
    else{
        // a^3
        // a^a
        if (stringHasAlpha((*mdl).math_data_list[length-1].value)==TRUE) {
            if (strcmp(md.value, "0")==0) {
                // a^3
                (*mdl).math_data_list[length-1].power=md.coefficient;
                
            }
            else{
                (*mdl).math_data_list[length-1].power=md.value;
            }
        }
        
        // 3^a
        // 3^2
        else{
            if (strcmp(md.value, "0")==0) {
                
                (*mdl).math_data_list[length-1].coefficient=cleanDotZeroAfterNum(numToCString(Walley_Operator(atof((*mdl).math_data_list[length-1].coefficient), atof(md.coefficient), sign)));
            }
            else{
                (*mdl).math_data_list[length-1].power=md.value;
            }
        }
    }
    
}

void MDL_operator_for_fraction(struct Math_Data_List *mdl, struct Math_Data md, char sign){
    
    int length=(*mdl).length;
    if (sign=='+' || sign=='-') {
        
        int i=0;
        bool find_same_symbol=FALSE;
        for (; i<length; i++) {
            // find same symbol or number
            if (strcmp((*mdl).math_data_list[i].value,md.value)==0) {
                find_same_symbol=TRUE;
                (*mdl).math_data_list[i].coefficient= Walley_Operator_For_Fraction((*mdl).math_data_list[i].coefficient, md.coefficient, sign);
            }
        }
        if (find_same_symbol==FALSE) {
            if (sign=='-') {
                md.coefficient=append("-", md.coefficient);
            }
            MDL_addMathData(mdl, md);
        }
    }
    else if(sign=='*'||sign=='/'){
        
        if (length==1) {
            (*mdl).math_data_list[length-1].coefficient=Walley_Operator_For_Fraction((*mdl).math_data_list[length-1].coefficient, md.coefficient, sign);
            if (stringHasAlpha(md.value)==TRUE) {
                if (stringHasAlpha((*mdl).math_data_list[length-1].value)==TRUE) {
                    
                    if (sign=='*') {
                        char *temp_value=(*mdl).math_data_list[length-1].value;
                        struct TOKEN *tl=Walley_MATH_Lexica_Analysis(temp_value);
                        int length_of_tl=TL_length(tl);
                        
                        //a*a
                        if (length_of_tl==2) {
                            if (strcmp(md.value,(*mdl).math_data_list[length-1].value)==0) {
                                (*mdl).math_data_list[length-1].power=Walley_Operator_For_Fraction((*mdl).math_data_list[length-1].power, md.power, '+');
                            }
                            else{
                                int i=1;
                                int smallest_end_index=0;
                                bool can_be_smaller_one=FALSE;
                                for (; i<length_of_tl; i++) {
                                    if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                        if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                            smallest_end_index=tl[i].TOKEN_END+1;
                                            can_be_smaller_one=TRUE;
                                            break;
                                        }
                                    }
                                }
                                
                                if (can_be_smaller_one==FALSE) {
                                    (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("*", md.value));
                                }
                                else{
                                    
                                    (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index), append("*", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value)))));
                                }
                                
                            }
                        }
                        else{
                            int i=1;
                            int smallest_end_index=0;
                            bool can_be_smaller_one=FALSE;
                            for (; i<length_of_tl; i++) {
                                if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                    if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                        smallest_end_index=tl[i].TOKEN_END+1;
                                        can_be_smaller_one=TRUE;
                                        break;
                                    }
                                }
                            }
                            
                            if (can_be_smaller_one==FALSE) {
                                (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("*", md.value));
                            }
                            else{
                                
                                (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index), append("*", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value)))));
                            }
                        }
                        
                        
                        
                    }
                    else{
                        // b/b
                        if (strcmp(md.value, (*mdl).math_data_list[length-1].value)==0) {
                            (*mdl).math_data_list[length-1].power=Walley_Operator_For_Fraction((*mdl).math_data_list[length-1].power, md.power, '-');
                            if (strcmp("0", (*mdl).math_data_list[length-1].power)==0) {
                                (*mdl).math_data_list[length-1].power="1";
                                (*mdl).math_data_list[length-1].coefficient="1";
                                (*mdl).math_data_list[length-1].value="0";
                                
                            }
                        }
                        else{
                            char *temp_value=(*mdl).math_data_list[length-1].value;
                            struct TOKEN *tl=Walley_MATH_Lexica_Analysis(temp_value);
                            int length_of_tl=TL_length(tl);
                            if (length_of_tl==2) {
                                if (strcmp(md.value,(*mdl).math_data_list[length-1].value)==0) {
                                    (*mdl).math_data_list[length-1].power=Walley_Operator_For_Fraction((*mdl).math_data_list[length-1].power, md.power, '-');
                                }
                                else{
                                    int i=1;
                                    int smallest_end_index=0;
                                    bool can_be_smaller_one=FALSE;
                                    for (; i<length_of_tl; i++) {
                                        if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                            if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                                smallest_end_index=tl[i].TOKEN_END+1;
                                                can_be_smaller_one=TRUE;
                                                break;
                                            }
                                        }
                                    }
                                    
                                    if (can_be_smaller_one==FALSE) {
                                        (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("/", md.value));
                                    }
                                    else{
                                        char *append_power=append("^(", append((*mdl).math_data_list[length-1].power, ")"));
                                        if (strcmp((*mdl).math_data_list[length-1].power, "1")==0) {
                                            append_power="";
                                        }
                                        (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index),append(append_power,append("/", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value))))));
                                        (*mdl).math_data_list[length-1].power="1";
                                    }
                                    
                                }
                                
                            }
                            
                            else{
                                int i=1;
                                int smallest_end_index=0;
                                bool can_be_smaller_one=FALSE;
                                for (; i<length_of_tl; i++) {
                                    if (strcmp("W_ID",tl[i].TOKEN_CLASS)==0) {
                                        if (strcmp(tl[i].TOKEN_STRING, md.value)<=0) {
                                            smallest_end_index=tl[i].TOKEN_END+1;
                                            can_be_smaller_one=TRUE;
                                            break;
                                        }
                                    }
                                }
                                
                                if (can_be_smaller_one==FALSE) {
                                    (*mdl).math_data_list[length-1].value=append((*mdl).math_data_list[length-1].value, append("/", md.value));
                                }
                                else{
                                    (*mdl).math_data_list[length-1].value=append(substr(temp_value, 0, smallest_end_index), append("/", append(md.value,substr(temp_value, smallest_end_index, (int)strlen(temp_value)))));
                                }
                                
                            }
                            
                        }
                    }
                    
                }
                else{
                    (*mdl).math_data_list[length-1].value=md.value;
                }
            }
            
        }
        else{
            char *temp_string=MDL_changeMathDataListToString((*mdl));
            temp_string=append("(", append(temp_string, ")"));
            (*mdl).math_data_list=(struct Math_Data*)realloc((*mdl).math_data_list, sizeof(struct Math_Data)*1);
            (*mdl).length=1;
            if (strcmp(md.value, "0")==0) {
                (*mdl).math_data_list[0].coefficient=md.coefficient;
                (*mdl).math_data_list[0].value=temp_string;
            }
            else{
                (*mdl).math_data_list[0].coefficient=temp_string;
                (*mdl).math_data_list[0].value=md.value;
            }
            
            
            
        }
    }
    // 3^a
    // a^3
    // 3^3
    else{
        // a^3
        // a^a
        if (stringHasAlpha((*mdl).math_data_list[length-1].value)==TRUE) {
            if (strcmp(md.value, "0")==0) {
                // a^3
                (*mdl).math_data_list[length-1].power=md.coefficient;
                
            }
            else{
                (*mdl).math_data_list[length-1].power=md.value;
            }
        }
        
        // 3^a
        // 3^2
        else{
            if (strcmp(md.value, "0")==0) {
                
                (*mdl).math_data_list[length-1].coefficient=Walley_Operator_For_Fraction((*mdl).math_data_list[length-1].coefficient, md.coefficient, sign);
            }
            else{
                (*mdl).math_data_list[length-1].power=md.value;
            }
        }
    }
    
}

/*
 char *Walley_Math_Operator(char *value1, char *value2, char sign){
 printf("decimal %s %s %c\n",value1,value2,sign);
 
 if (JUST_INIT_MATH_LIST==TRUE) {
 printf("Enter Here\n");
 
 struct Math_Data md1=changeValueToMathDate(value1);
 MDL_addMathData(&(MDA.mdl[0]), md1);
 
 struct Math_Data md2=changeValueToMathDate(value2);
 
 MDL_operator_for_decimal(&(MDA.mdl[0]), md2, sign);
 
 JUST_INIT_MATH_LIST=FALSE;
 
 return "MDL";
 }
 
 else{
 if (strcmp(value1, "MDL")==0) {
 printf("\n\nit is MDL\n");
 struct Math_Data md2=changeValueToMathDate(value2);
 MDL_operator_for_decimal(&(MDA.mdl[0]), md2, sign);
 return "MDL";
 }
 
 
 if (stringIsDigit(value1)==TRUE) {
 
 // both value1 and value2 is digit
 if (stringIsDigit(value2)==TRUE) {
 return cleanDotZeroAfterNum(numToCString(Walley_Operator(atof(value1), atof(value2), sign)));
 }
 else{
 //3 * a
 //3 * 3*a
 //5 + 3*a
 //4 + 5+3*a
 
 // may not even enter this if
 if (stringHasSign(value2)==TRUE) {
 // + -
 if (sign=='+'||sign=='-') {
 int index_of_first_sign=indexOfFirstSign(value2);
 if (WALLEY_MATH_signOrder(value2[index_of_first_sign])==WALLEY_MATH_signOrder(sign)) {
 if (value2[index_of_first_sign]=='+'||value2[index_of_first_sign]=='-') {
 char *value3=substr(value2, 0, index_of_first_sign);
 value2=substr(value2, index_of_first_sign, (int)strlen(value2));
 value3=Walley_Math_Operator(value1, value3, sign);
 return append(value3, value2);
 }
 else{
 return append(value2, append(charToString(sign), value1));
 }
 }
 else{
 if (sign=='+') {
 return append(value2, append(charToString(sign), value1));
 
 }
 return append(value1, append(charToString(sign), value2));
 }
 }
 // * / % ^
 else{
 int index_of_first_sign=indexOfFirstSign(value2);
 if (WALLEY_MATH_signOrder(value2[index_of_first_sign])==WALLEY_MATH_signOrder(sign)&&(find_not_in_parenthesis(value2, "+")==-1&&find_not_in_parenthesis(value2, "-")==-1)) {
 
 if (value2[index_of_first_sign]=='*'||value2[index_of_first_sign]=='/'||value2[index_of_first_sign]=='%') {
 char *value3=substr(value2, 0, index_of_first_sign);
 value2=substr(value2, index_of_first_sign, (int)strlen(value2));
 value3=Walley_Math_Operator(value1, value3, sign);
 return append(value3, value2);
 }
 else{
 value2=append("(", append(value2, ")"));
 return append(value1, append(charToString(sign), value2));
 }
 }
 else{
 value2=append("(", append(value2, ")"));
 return append(value1,append(charToString(sign),value2));
 }
 
 }
 }
 else{
 return append(value1, append(charToString(sign), value2));
 }
 }
 
 }
 
 else{
 //3*a 4 *
 if (stringIsDigit(value2)==TRUE) {
 //a   + 5
 //3+a + 2
 
 if (stringHasSign(value1)) {
 // + -
 if (sign=='+'||sign=='-') {
 int index_of_first_sign=indexOfFirstSignFromBehind(value1);
 if (WALLEY_MATH_signOrder(value1[index_of_first_sign])==WALLEY_MATH_signOrder(sign)) {
 if (value1[index_of_first_sign]=='+'||value1[index_of_first_sign]=='-') {
 char *value3=substr(value1, index_of_first_sign+1, (int)strlen(value1));
 value1=substr(value1, 0,index_of_first_sign+1);
 value3=Walley_Math_Operator(value3, value2, sign);
 return append(value1, value3);
 }
 else{
 return append(value1, append(charToString(sign), value2));
 }
 }
 else{
 return append(value1, append(charToString(sign), value2));
 }
 }
 // * / % ^
 else{
 int index_of_first_sign=indexOfFirstSign(value1);
 if (WALLEY_MATH_signOrder(value1[index_of_first_sign])==WALLEY_MATH_signOrder(sign)&&(find_not_in_parenthesis(value1, "+")==-1&&find_not_in_parenthesis(value1, "-")==-1)) {
 if (value1[index_of_first_sign]=='*'||value1[index_of_first_sign]=='/'||value1[index_of_first_sign]=='%') {
 char *value3=substr(value1, 0, index_of_first_sign);
 value1=substr(value1, index_of_first_sign,(int)strlen(value1));
 value3=Walley_Math_Operator(value3, value2, sign);
 return append(value3, value1);
 }
 else{
 value1=append("(", append(value1, ")"));
 return append(value2, append(charToString(sign), value1));
 }
 }
 
 else{
 value1=append("(", append(value1, ")"));
 return append(value2, append(charToString(sign), value1));
 }
 }
 }
 
 else{
 return append(value1, append(charToString(sign), value2));
 
 }
 }
 //3*a * a
 else{
 if (stringHasSign(value1)&&stringHasSign(value2)) {
 int index1=indexOfFirstSignFromBehind(value1);
 int index2=indexOfFirstSign(value2);
 
 if (WALLEY_MATH_signOrder(value1[index1])==WALLEY_MATH_signOrder(value2[index2]) && WALLEY_MATH_signOrder(value1[index1])==sign) {
 char *value3=substr(value1, index1+1, (int)strlen(value1));
 value1=substr(value1, 0, index1+1);
 char *value4=substr(value2, 0, index2);
 value2=substr(value2, index2, (int)strlen(value2));
 char *value=Walley_Math_Operator(value3, value4, sign);
 return append(value1,append(value, value2));
 }
 else{
 return append(value1, append(charToString(sign), value2));
 }
 
 
 }
 else if(strcmp(value1, value2)==0){
 if (sign=='+') {
 return append("2*",value1);
 }
 else
 return "0";
 }
 return append(value1, append(charToString(sign), value2));
 }
 }
 
 }
 }
 
 char *Walley_Math_Operator_For_Fraction(char *value1, char *value2, char sign){
 printf("fraction %s %s %c\n",value1,value2,sign);
 if (stringIsDigit(value1)==TRUE) {
 
 // both value1 and value2 is digit
 if (stringIsDigit(value2)==TRUE) {
 return cleanDotZeroAfterNum(Walley_Operator_For_Fraction(value1, value2, sign));
 }
 else{
 //3 * a
 //3 * 3*a
 //5 + 3*a
 //4 + 5+3*a
 
 // may not even enter this if
 if (stringHasSign(value2)==TRUE) {
 // + -
 if (sign=='+'||sign=='-') {
 int index_of_first_sign=indexOfFirstSign(value2);
 if (value2[index_of_first_sign]=='+'||value2[index_of_first_sign]=='-') {
 char *value3=substr(value2, 0, index_of_first_sign);
 value2=substr(value2, index_of_first_sign, (int)strlen(value2));
 value3=Walley_Math_Operator_For_Fraction(value1, value3, sign);
 return append(value3, value2);
 }
 else{
 return append(value2, append(charToString(sign), value1));
 }
 }
 // * / % ^
 else{
 int index_of_first_sign=indexOfFirstSign(value2);
 if (value2[index_of_first_sign]=='*'||value2[index_of_first_sign]=='/'||value2[index_of_first_sign]=='%') {
 char *value3=substr(value2, 0, index_of_first_sign);
 value2=substr(value2, index_of_first_sign, (int)strlen(value2));
 value3=Walley_Math_Operator_For_Fraction(value1, value3, sign);
 return append(value3, value2);
 }
 else{
 value2=append("(", append(value2, ")"));
 return append(value1, append(charToString(sign), value2));
 }
 
 }
 }
 else{
 return append(value1, append(charToString(sign), value2));
 }
 }
 
 }
 
 else{
 //3*a 4 *
 if (stringIsDigit(value2)==TRUE) {
 //a   + 5
 //3+a + 2
 
 if (stringHasSign(value1)) {
 // + -
 if (sign=='+'||sign=='-') {
 int index_of_first_sign=indexOfFirstSignFromBehind(value1);
 if (value1[index_of_first_sign]=='+'||value1[index_of_first_sign]=='-') {
 char *value3=substr(value1, index_of_first_sign+1, (int)strlen(value1));
 value1=substr(value1, 0,index_of_first_sign+1);
 value3=Walley_Math_Operator_For_Fraction(value3, value2, sign);
 return append(value1, value3);
 }
 else{
 return append(value1, append(charToString(sign), value2));
 }
 }
 // * / % ^
 else{
 int index_of_first_sign=indexOfFirstSignFromBehind(value1);
 if (value1[index_of_first_sign]=='*'||value1[index_of_first_sign]=='/'||value1[index_of_first_sign]=='%') {
 char *value3=substr(value1, 0, index_of_first_sign);
 value1=substr(value1, index_of_first_sign,(int)strlen(value1));
 value3=Walley_Math_Operator_For_Fraction(value3, value2, sign);
 return append(value3, value1);
 }
 else{
 value1=append("(", append(value1, ")"));
 return append(value2, append(charToString(sign), value1));
 }
 }
 }
 
 else{
 return append(value1, append(charToString(sign), value2));
 
 }
 }
 //3*a * a
 else{
 if (stringHasSign(value1)&&stringHasSign(value2)) {
 int index1=indexOfFirstSignFromBehind(value1);
 int index2=indexOfFirstSign(value2);
 char *value3=substr(value1, index1+1, (int)strlen(value1));
 value1=substr(value1, 0, index1+1);
 char *value4=substr(value2, 0, index2);
 value2=substr(value2, index2, (int)strlen(value2));
 char *value=Walley_Math_Operator(value3, value4, sign);
 return append(value1,append(value, value2));
 }
 else if(strcmp(value1, value2)==0){
 if (sign=='+') {
 return append(value1, "*2");
 }
 else
 return "0";
 }
 return append(value1, append(charToString(sign), value2));
 }
 }
 }
 */


// only supports decimal now
// the input_str is the postfix notation
char *Walley_Math_Parser_Decimal(char *input_str){
    MDA_init(&MDA);
    // MDA_0
    // MDA_1
    // MDA_2
    // ....
    
    
    
    int start=0;
    int end=find(input_str, " ");
    char **stack;
    Str_initStringList(&stack);
    
    while (TRUE) {
        if (end==-1) {
            break;
        }
        char *temp_str=substr(input_str, start, end);
        // it is sign
        if (isSign(temp_str[0])==TRUE) {
            char sign=temp_str[0];
            char *value2=Str_PopString(&stack);
            char *value1=Str_PopString(&stack);
            
            if (stack[0]==NULL) {
                return append("-", cleanDotZeroAfterNum(value2));
            }
            
            char *output_str;
            if (find(value1, "MDA_")==0 && find(value2, "MDA_")==0) {
                // printf("\nThey Are Both MDA\n");
                int mda_index1=atoi(substr(value1, 4, (int)strlen(value1)));
                int mda_index2=atoi(substr(value2, 4, (int)strlen(value2)));
                
                struct Math_Data_List mdl1=MDA.mdl[mda_index1];
                struct Math_Data_List mdl2=MDA.mdl[mda_index2];
                
                int length_of_mdl2=mdl2.length;
                
                int i=0;
                for (; i<length_of_mdl2; i++) {
                    MDL_operator_for_decimal(&mdl1, mdl2.math_data_list[i], sign);
                }
                
                MDA_pop(&MDA);
                MDA.mdl[mda_index1]=mdl1;
                
                output_str=value1;
            }
            else if (find(value1, "MDA_")==0) {
                int mda_index=atoi(substr(value1, 4, (int)strlen(value1)));
                // printf("\n\nit is MDL\n");
                struct Math_Data md2=changeValueToMathDate(value2);
                MDL_operator_for_decimal(&(MDA.mdl[mda_index]), md2, sign);
                output_str=value1;
            }
            else if(find(value2, "MDA_")==0){
                int mda_index=atoi(substr(value2, 4, (int)strlen(value2)));
                struct Math_Data md1=changeValueToMathDate(value1);
                MDL_operator_for_decimal(&(MDA.mdl[mda_index]), md1, sign);
                output_str=value2;
                
            }
            else{
                
                struct Math_Data_List temp_mdl;
                MDL_init(&temp_mdl);
                
                struct Math_Data md1=changeValueToMathDate(value1);
                MDL_addMathData(&temp_mdl, md1);
                
                struct Math_Data md2=changeValueToMathDate(value2);
                
                MDL_operator_for_decimal(&(temp_mdl), md2, sign);
                
                
                MDA_addMathDataList(&MDA, temp_mdl);
                
                output_str=append("MDA_", intToCString(MDA.length-1));
                
            }
            // printf("----> %s\n",output_str);
            Str_addString(&stack, output_str);
            
        }
        // it is symbol or number
        else{
            Str_addString(&stack, temp_str);
        }
        
        
        start=end+1;
        end=find_from_index(input_str, " ", start);
    }
    
    char *output=MDL_changeMathDataListToString(MDA.mdl[0]);
    //return cleanDotZeroAfterNum(Str_PopString(&stack));
    return output;
}




char *Walley_Math_Parser_Fraction(char *input_str){
    MDA_init(&MDA);
    
    int start=0;
    int end=find(input_str, " ");
    char **stack;
    Str_initStringList(&stack);
    
    while (TRUE) {
        if (end==-1) {
            break;
        }
        char *temp_str=substr(input_str, start, end);
        // it is sign
        if (isSign(temp_str[0])==TRUE) {
            char sign=temp_str[0];
            char *value2=Str_PopString(&stack);
            char *value1=Str_PopString(&stack);
            
            if (stack[0]==NULL) {
                return append("-", cleanDotZeroAfterNum(value2));
            }
            
            char *output_str;
            if (find(value1, "MDA_")==0 && find(value2, "MDA_")==0) {
                // printf("\nThey Are Both MDA\n");
                int mda_index1=atoi(substr(value1, 4, (int)strlen(value1)));
                int mda_index2=atoi(substr(value2, 4, (int)strlen(value2)));
                
                struct Math_Data_List mdl1=MDA.mdl[mda_index1];
                struct Math_Data_List mdl2=MDA.mdl[mda_index2];
                
                int length_of_mdl2=mdl2.length;
                
                int i=0;
                for (; i<length_of_mdl2; i++) {
                    MDL_operator_for_fraction(&mdl1, mdl2.math_data_list[i], sign);
                }
                
                MDA_pop(&MDA);
                MDA.mdl[mda_index1]=mdl1;
                
                output_str=value1;
            }
            else if (find(value1, "MDA_")==0) {
                int mda_index=atoi(substr(value1, 4, (int)strlen(value1)));
                //printf("\n\nit is MDL\n");
                struct Math_Data md2=changeValueToMathDate(value2);
                MDL_operator_for_fraction(&(MDA.mdl[mda_index]), md2, sign);
                output_str=value1;
            }
            else if(find(value2, "MDA_")==0){
                int mda_index=atoi(substr(value2, 4, (int)strlen(value2)));
                struct Math_Data md1=changeValueToMathDate(value1);
                MDL_operator_for_fraction(&(MDA.mdl[mda_index]), md1, sign);
                output_str=value2;
                
            }
            else{
                
                struct Math_Data_List temp_mdl;
                MDL_init(&temp_mdl);
                
                struct Math_Data md1=changeValueToMathDate(value1);
                MDL_addMathData(&temp_mdl, md1);
                
                struct Math_Data md2=changeValueToMathDate(value2);
                
                MDL_operator_for_fraction(&(temp_mdl), md2, sign);
                
                MDA_addMathDataList(&MDA, temp_mdl);
                
                output_str=append("MDA_", intToCString(MDA.length-1));
                
            }
            // printf("----> %s\n",output_str);
            Str_addString(&stack, output_str);
            
        }
        // it is symbol or number
        else{
            Str_addString(&stack, temp_str);
        }
        
        
        start=end+1;
        end=find_from_index(input_str, " ", start);
    }
    
    char *output=MDL_changeMathDataListToString(MDA.mdl[0]);
    //return cleanDotZeroAfterNum(Str_PopString(&stack));
    return output;
}

// judge f --> fraction
// ..... d --> decimal
char *Walley_Math_Eval(char *input_str, char judge){
    if (input_str[0]=='-') {
        input_str=append("0",input_str);
    }
    else{
        input_str=append("0+",input_str);
    }
    
    char **replace_str_list;
    Str_initStringList(&replace_str_list);
    int i=1;

    
    // change sin(1/4) to MATHH_1 mark
    if (judge=='f') {
        while (count_str(input_str, "sin(")!=0) {
            int index=find(input_str, "sin(");
            int index_of_left=find_from_index(input_str, "(", index);
            int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
            char *replace_str=substr(input_str, index, index_of_right+1);
            char *with_str=append("MATHH_", intToCString(i));
            input_str=replace_not_in_string(input_str, replace_str, with_str);
            replace_str_list[i]=append(replace_str, append("#", with_str));
            i++;
        }
        while (count_str(input_str, "cos(")!=0) {
            int index=find(input_str, "cos(");
            int index_of_left=find_from_index(input_str, "(", index);
            int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
            char *replace_str=substr(input_str, index, index_of_right+1);
            char *with_str=append("MATHH_", intToCString(i));
            input_str=replace_not_in_string(input_str, replace_str, with_str);
            replace_str_list[i]=append(replace_str, append("#", with_str));
            i++;
        }
        while (count_str(input_str, "tan(")!=0) {
            int index=find(input_str, "tan(");
            int index_of_left=find_from_index(input_str, "(", index);
            int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
            char *replace_str=substr(input_str, index, index_of_right+1);
            char *with_str=append("MATHH_", intToCString(i));
            input_str=replace_not_in_string(input_str, replace_str, with_str);
            replace_str_list[i]=append(replace_str, append("#", with_str));
            i++;
        }
        while (count_str(input_str, "cot(")!=0) {
            int index=find(input_str, "cot(");
            int index_of_left=find_from_index(input_str, "(", index);
            int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
            char *replace_str=substr(input_str, index, index_of_right+1);
            char *with_str=append("MATHH_", intToCString(i));
            input_str=replace_not_in_string(input_str, replace_str, with_str);
            replace_str_list[i]=append(replace_str, append("#", with_str));
            i++;
        }
        while (count_str(input_str, "sec(")!=0) {
            int index=find(input_str, "sec(");
            int index_of_left=find_from_index(input_str, "(", index);
            int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
            char *replace_str=substr(input_str, index, index_of_right+1);
            char *with_str=append("MATHH_", intToCString(i));
            input_str=replace_not_in_string(input_str, replace_str, with_str);
            replace_str_list[i]=append(replace_str, append("#", with_str));
            i++;
        }
        while (count_str(input_str, "csc(")!=0) {
            int index=find(input_str, "csc(");
            int index_of_left=find_from_index(input_str, "(", index);
            int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
            char *replace_str=substr(input_str, index, index_of_right+1);
            char *with_str=append("MATHH_", intToCString(i));
            input_str=replace_not_in_string(input_str, replace_str, with_str);
            replace_str_list[i]=append(replace_str, append("#", with_str));
            i++;
        }
        while (count_str(input_str, "exp(")!=0) {
            int index=find(input_str, "exp(");
            int index_of_left=find_from_index(input_str, "(", index);
            int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
            char *replace_str=substr(input_str, index, index_of_right+1);
            char *with_str=append("MATHH_", intToCString(i));
            input_str=replace_not_in_string(input_str, replace_str, with_str);
            replace_str_list[i]=append(replace_str, append("#", with_str));
            i++;
        }
        while (count_str(input_str, "log10(")!=0) {
            int index=find(input_str, "log10(");
            int index_of_left=find_from_index(input_str, "(", index);
            int index_of_right=indexOfMostOutterBracket(input_str, index_of_left);
            char *replace_str=substr(input_str, index, index_of_right+1);
            char *with_str=append("MATHH_", intToCString(i));
            input_str=replace_not_in_string(input_str, replace_str, with_str);
            replace_str_list[i]=append(replace_str, append("#", with_str));
            i++;
        }

    }
    
    struct TOKEN *token=Walley_MATH_Lexica_Analysis(input_str);
        
    char *postfix=WALLEY_MATH_Infix_to_Postfix(token);
        
    // fraction
    if (judge=='f') {
        // first time calculation
        char *output=Walley_Math_Parser_Fraction(postfix);
        
        // second time calculation
        token=Walley_MATH_Lexica_Analysis(output);
        postfix=WALLEY_MATH_Infix_to_Postfix(token);
        output=Walley_Math_Parser_Fraction(postfix);
        
        int a=1;
        for (a=1; a<i; a++) {
            char *replace_str_a=replace_str_list[a];
            int index_of_mark=find(replace_str_a ,"#");
            char *replace_str=substr(replace_str_a, 0, index_of_mark);
            char *with_str=substr(replace_str_a, index_of_mark+1, (int)strlen(replace_str_a));
            output=replace(output,with_str,replace_str);
        }

        return output;;
    }
    // decimal
    else{
        // first time calculation
        char *output=Walley_Math_Parser_Decimal(postfix);
        
        // second time calculation
        token=Walley_MATH_Lexica_Analysis(output);
        postfix=WALLEY_MATH_Infix_to_Postfix(token);
        output=Walley_Math_Parser_Decimal(postfix);
        
        return output;
    }
}