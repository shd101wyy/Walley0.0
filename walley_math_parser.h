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
            //printf("Find The same\n");
            //printf("%c\n",from_str[i]);
            //char *temp = substr(from_str, i, i + (int) strlen(find_str));
            //printf("############%d\n",i);
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

// does not support symbolic calculation
char *Walley_Math_Operator(char *value1, char *value2, char sign){
    return cleanDotZeroAfterNum(numToCString(Walley_Operator(atof(value1), atof(value2), sign)));
}


// does not support symbolic calculation
char *Walley_Math_Operator_For_Fraction(char *value1, char *value2, char sign){
    return Walley_Operator_For_Fraction(value1, value2, sign);
}


// only supports decimal now
// the input_str is the postfix notation
char *Walley_Math_Parser_Decimal(char *input_str){
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
            char *value1=Str_PopString(&stack);
            char *value2=Str_PopString(&stack);
            
            if (stack[0]==NULL) {
                return append("-", cleanDotZeroAfterNum(value1));
            }
            
            char *output_str=Walley_Math_Operator(value2,value1, temp_str[0]);
            Str_addString(&stack, output_str);
            
        }
        // it is symbol or number
        else{
            Str_addString(&stack, temp_str);
        }
        
        
        start=end+1;
        end=find_from_index(input_str, " ", start);
    }
    
    return cleanDotZeroAfterNum(Str_PopString(&stack));
}

char *Walley_Math_Parser_Fraction(char *input_str){
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
            char *value1=Str_PopString(&stack);
            char *value2=Str_PopString(&stack);
            
            
            if (stack[0]==NULL) {
                return append("-", cleanDotZeroAfterNum(value1));
            }
            
            char *output_str=Walley_Math_Operator_For_Fraction(value2,value1, temp_str[0]);
            Str_addString(&stack, output_str);
            
        }
        // it is symbol or number
        else{
            Str_addString(&stack, temp_str);
        }
        
        
        start=end+1;
        end=find_from_index(input_str, " ", start);
    }
    return cleanDotZeroAfterNum(Str_PopString(&stack));
}

// judge f --> fraction
// ..... d --> decimal
char *Walley_Math_Eval(char *input_str, char judge){
    if (input_str[0]=='-') {
        input_str=append("0",input_str);
    }
    
    struct TOKEN *token=Walley_MATH_Lexica_Analysis(input_str);
    char *postfix=WALLEY_MATH_Infix_to_Postfix(token);
    // fraction
    if (judge=='f') {
        return Walley_Math_Parser_Fraction(postfix);
    }
    // decimal
    else{
        return Walley_Math_Parser_Decimal(postfix);
    }
}