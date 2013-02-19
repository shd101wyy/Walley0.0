//
//  walley_math_print.h
//  Walley
//
//  Created by shd101wyy on 12-11-10.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//
#include "walley_math_parser.h"
/*
 // I GIVE UP THIS TEMPERIALY
 

 this head is used for solve print problem
 
 for example, 
 
 decimal print as decimal.
 
 
 fraction :
    1/2
 print as:
 
 1
---
 2
 
    23/2
 
  23
 ----
  2
 
   1/333
 
   1
 -----
  333
 
 root:
     √(3)
     
   /---
 (√  3  )
 
    2^(1/3)
 
 3/---
 √  2
 
 
 power 3^(2/3)
 
             2
             -
             3
            3
*/

// 1/3 ---->
//  1
// ---
//  3


/*
 root:
 √(3)
 
  | /---|
  |√  3 |
 
 2^(1/3)
 
 3/---
 √  2
 */

// stringAppendStrForTime("a"," ",2)-->"a  "
char *stringAppendStrForTime(char *input_str, char *append_str ,int time){
    int i=0;
    for (i=0; i<time; i++) {
        input_str=append(input_str, append_str);
    }
    return input_str;
}

// did not support √(√(2)) now
char *outputRoot(char *root){
    int horizentol=2;
    int index_of_left_bracket=find(root, "(");
    if (index_of_left_bracket==-1) {
        printf("Mistake occurred whiling calling function outputRoot\nFormat wrong, no ( find\n");
        exit(1);
    }else{
        char *num_str=substr(root, index_of_left_bracket+1, (int)strlen(root)-1);
        
        //is fraction
        if (stringIsFraction(num_str)==TRUE) {
            
        }
        //is is digit.
        else{
            
            int length=(int)strlen(num_str);
            horizentol=horizentol+length;
            char *first_row=" /";
            int i=0;
            for (i=0; i<horizentol; i++) {
                first_row=append(first_row, "-");
            }
            first_row=append(first_row, "\n");
            
            char *second_row="√  ";
            second_row=append(second_row, num_str);
            second_row=append(second_row, "\n");
            
            return append(first_row, second_row);
            
        }

    }
    return "None";
}

/*
 fraction :
 1/2::
 print as:
 
  1
 ---
  2
 
 23/2::
 
  23
 ----
  2
 
 1/333::
 
   1
 -----
  333
 
 */
char *outputFraction(char *fraction){
    char *numerator=numerator_of_fraction(fraction);
    char *denominator=denominator_of_fraction(fraction);
    
    int length1=(int)strlen(numerator);
    int length2=(int)strlen(denominator);
    int length=length1;
    bool numerator_is_bigger=TRUE;
    if (length2>length1) {
        length=length2;
        numerator_is_bigger=FALSE;
    }
    length+=2;
    char *first="";
    char *second="";
    char *third="";
    if (numerator_is_bigger) {
        first=append(" ",append(numerator, "\n"));
        second=append(stringAppendStrForTime("", "-", length),"\n");
        third=stringAppendStrForTime(third, " ", (length-length2)/2);
        third=append(append(third, denominator),"\n");

    }
    else{
        first=stringAppendStrForTime(first, " ", (length-length1)/2);
        first=append(append(first, numerator),"\n");
        second=append(stringAppendStrForTime("", "-", length),"\n");
        third=append(" ", denominator);
    }
    
    return append(first, append(second, third));
}


/*
 power 3^(2/3)
 
  2
  -
  3
 3
 
 power 323^2
 
     2
  323
 */
char *outputPower(char *input_str){
    int index_of_power_sign=find(input_str, "^");
    if (index_of_power_sign==-1) {
        printf("Mistake occurred whiling calling function changePowerToRoot\nNo ^ found\n");
        exit(0);
    }
    char *num=substr(input_str, 0, index_of_power_sign);
    char *power=substr(input_str, index_of_power_sign+1, (int)strlen(input_str));
    num=eval_for_fraction(num);
    power=eval_for_fraction(power);
    
    if (stringIsFraction(power)) {
        
    }
    
    else{
        if (stringIsFraction(num)) {
            
        }
        else{
            int length=(int)strlen(num);
            char *first="";
            first=stringAppendStrForTime(first, " ", length);
            first=append(first, power);
            first=append(first, "\n");
            char *second=num;
            second=append(second, "\n");
            return append(first, second);
        }
    }
    
    
    return "None";
}
