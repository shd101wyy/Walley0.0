/* 
 * File:   walley_function.h
 * Author: shd101wyy
 *
 * Created on August 17, 2012, 2:39 PM
 */
//#include "walley_string.h"
#include "walley_math_print.h"
//#include "walley_list.h"


// function isFunctionFromVar has problems.
// function deleteOneFunctionFromBehind has problems.


/*
 This function will remove \n behind input_str;
 */


char *removeNFromBack(char *input_str){
    while (input_str[(int)strlen(input_str)-1]=='\n') {
        if ((int)strlen(input_str)-1==0) {
            return "";
        }
        input_str=substr(input_str, 0,(int)strlen(input_str)-1);
    }
    return input_str;
}

/*
 * make string in c to string in walley
 * toString("Hello")----->"Hello" add double quote.
 */
char *toString(char *input_str){
    //printf("#### toString ####\n");
    input_str = trim(input_str);
    if ((input_str[0] == '\'' || input_str[0] == '"') && (int) strlen(input_str) != 1)
        return input_str;
    else {
        return append("\"", append(input_str, "\""));
    }
}

char* strInBrackets(char *input_str){
    input_str=removeAheadSpace(input_str);
    input_str=removeBackSpace(input_str);
    int begin_index=find(input_str,"(");
    
    int length=(int)strlen(input_str);
    int i=0;
    int end_index=-1;
    for (i=length-1; i>=0; i--) {
        if (input_str[i]==')') {
            end_index=i;
            break;
        }
    }
    
    //int end_index=(int)strlen(input_str)-1;
    if (begin_index==-1||end_index==-1){
        printf("\nMistake occurred while calling function strInBrackets\n");
        return "\nMistake occurred while calling function strInBrackets\n";
    } else {
        return substr(input_str,begin_index+1,end_index);   
    }
}

bool checkWhetherEquaIsInsideString(char *input_str) {
   //// printf("#### checkWhetherEquaIsInsideString ####\n");
    bool inside = FALSE;
    int index_of_first_equa = find_not_in_string(input_str, "=");
    input_str=substr(input_str,0,index_of_first_equa);
    int count_of_single_quote=count_str(input_str,"'");
    int count_of_double_quote=count_str(input_str,"\"");
    int sum=count_of_single_quote+count_of_double_quote;
    if(sum%2==0)
        inside=FALSE;
    else
        inside=TRUE;
    return inside;
}


char* checkValueType(char *input_str){
    char *type="";
    int index_of_first_equa=find(input_str,"=");
    if(index_of_first_equa!=-1&&checkWhetherEquaIsInsideString(input_str)==FALSE){
        //printf("index_of_first_equa is %d\n",index_of_first_equa);
        input_str=substr(input_str,index_of_first_equa+1,(int)strlen(input_str)); 
        //printf("input_str is :%s\n",input_str);
    }
    input_str=removeBackSpace(input_str);
    input_str=removeAheadSpace(input_str);
   //// printf("The input_str is %s\n",input_str);
    
    
    int index_of_first_syh=find(input_str,"\"");
    int index_of_first_dyh=find(input_str,"'");
    int index_of_first_list=find(input_str,"[");
    
    if(index_of_first_syh==0&&checkWhetherComplete(input_str)==TRUE){
        type="string";
    } else if (index_of_first_dyh==0&&checkWhetherComplete(input_str)==TRUE){
        type="string";
    } else if (index_of_first_list==0&&checkWhetherComplete(input_str)==TRUE){
        type="list";
    } else {
        type="unknown type";
    }
    
    
    return type;
    
}



char* variableName(char* input_message){
    if(find(input_message,"=")==-1){
        printf("\nMistake occurred while calling function variableName\nPlease check");
        return "None";
    } else {
        if(checkWhetherEquaIsInsideString(input_message)==TRUE){
            printf("\nMistake occurred while calling function variableName\nPlease check");
            return "None";
        } else {
            //printf("Enter else\n");
            int index_of_equa=find(input_message,"=");
            char *variable_name=substr(input_message,0,index_of_equa);
            variable_name=removeBackSpace(variable_name);
            return variable_name;
        }
    }
}

char* variableValue(char* input_message){
    if(find(input_message,"=")==-1){
        printf("\nMistake occurred while calling function variableValue\nPlease check");
        return "None";
    } else {
        if(checkWhetherEquaIsInsideString(input_message)==TRUE||find(input_message,"=")==(int)strlen(input_message)-1){
            printf("\nMistake occurred while calling function variableValue\nPlease check");
            return "None";
        } else {
       
            int index_of_equa=find(input_message,"=");
           //// printf("$$index_of_equa is %d\n",index_of_equa);
            char *variable_value=substr(input_message,index_of_equa+1,(int)strlen(input_message));
            variable_value=removeBackSpace(variable_value);
            variable_value=removeAheadSpace(variable_value);
           //// printf("#### variableValue input |%s|, var_value |%s|####\n",input_message,variable_value);
            return variable_value;
        }
    }
}

bool checkWhetherSameVarNameExists(char *var_name){
    FILE *fp;
    char arr[1000]="";
    bool has_same_var_name=FALSE;
    if ((fp = fopen("__walley__.wy", "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    }//// else {
     ////   printf("Function checkWhetherSameVarNameExists Find file\n");
    //// }
    //char *var_name_in_file="";
    while ((fgets(arr, 1000, fp)) != NULL) {
        if(find(arr,":")==-1)
            continue;
        char *var_name_in_file=substr(arr,0,find(arr,":"));
       //// printf("var_name is %s\n",var_name_in_file);
        if (strcmp(var_name_in_file,var_name)==0){
            has_same_var_name=TRUE;
            break;
        }
    }
    fclose(fp);
    return has_same_var_name;
}






bool isFunctionFromVar(char **FUNCTION_functions, char *input_str){
    bool is_function=TRUE;
    input_str = removeAheadSpace(input_str);
    if(count_str(input_str,"(")==0 || count_str(input_str, ")")==0){
        is_function=FALSE;
        //printf("Didn't find ( or )");
    }
    else {
        is_function=FALSE;
        char *function_name = substr(input_str, 0, find(input_str, "("));
       
        int row=0;
        int length_of_function=atoi(FUNCTION_functions[0]);
        while (row<length_of_function) {
           // printf("->%s\n",FUNCTION[row]);
            int index_of_maohao=find(FUNCTION_functions[row],":");
            if (index_of_maohao==-1) {
                row++;
                continue;
            }
            char *temp=substr(FUNCTION_functions[row],0, index_of_maohao);
            if (strcmp(temp, function_name)==0) {
               // printf("%s equals %s\n",temp,function_name);
                is_function=TRUE;
                break;
            }
            row++;
        }
        if (count_str(function_name," ")>0)
            is_function=FALSE;
    }
    return is_function;
}

char* variableValueType(char *variable_value){
    //printf("#### vairableValueType ####\n");
    //printf("Var Value |%s|\n",variable_value);
    variable_value=removeAheadSpace(variable_value);
    //printf("Var Value %s\n",variable_value);
    variable_value=removeBackSpace(variable_value);
    
    if (stringIsFraction(variable_value)) {
        return "fraction";
    }
    
    
    char *type="";
    int index_of_first_syh=find(variable_value,"\"");
    int index_of_first_dyh=find(variable_value,"'");
    int index_of_first_list=find(variable_value,"[");
    int index_of_first_dict=find(variable_value,"{");
    //printf("Var Value %s\n",variable_value);
    if(index_of_first_syh==0&&checkWhetherComplete(variable_value)==TRUE){
        type="string";
    } else if (index_of_first_dyh==0&&checkWhetherComplete(variable_value)==TRUE){
        type="string";
    } else if (index_of_first_list==0&&checkWhetherComplete(variable_value)==TRUE){
        type="list";
    } else if (index_of_first_dict==0&&checkWhetherComplete(variable_value)==TRUE){
        type="dictionary";
    } else if(stringIsDigit(variable_value)){
        if(find(variable_value,".")!=-1)
            type="double";
        else
            type="int";
        // New add here
    } //else if(index_of_first_syh==-1&&index_of_first_dyh==-1&&index_of_first_list==-1){
    else if(index_of_first_list==-1){
        type="expression";
    }
    else {
        type="unknown type";
    }
    return type;
    
}

// Walley_String to C language String
char *toCString(char *input_str){
    input_str=trim(input_str);
    if(strcmp(variableValueType(input_str),"string")==0){
        return substr(input_str,1,(int)strlen(input_str)-1);
    }
    else{
        return input_str;
    }
}
bool isExpression(char *input_str){
    bool is_expression=TRUE;
    int index_of_equal=find_not_in_string(input_str,"=");
    if (index_of_equal==-1) {
        return FALSE;
    }
    if (input_str[index_of_equal+1]=='='||input_str[index_of_equal-1]=='>'||input_str[index_of_equal-1]=='<'||input_str[index_of_equal-1]=='!') {
        return FALSE;
    }
    if(index_of_equal!=-1&&checkWhetherEquaIsInsideString(input_str)==FALSE){
        
        //check whether = is in ()
        int index_of_left=find_not_in_string(input_str, "(");
        int index_of_right=find_not_in_string(input_str, ")");
        if (index_of_left<index_of_equal&&index_of_equal<index_of_right) {
            is_expression=FALSE;
        }
        else{
            is_expression=TRUE;
        }
    } else {
        is_expression=FALSE;
    }
    //printf("end %d, if 0 not, if 1 yes\n",is_expression);
    //printf("Input Str is |%s|\n",input_str);
    return is_expression;
}

char* getStringFromFile(char *file_name){
    /*
    FILE *fp;
    char arr[1000];

    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    }
    
    fclose(fp);
    return (char*)arr;**/
    FILE *fp;
    //char ch;
    char arr[10000]="";
    char output[10000]="";
    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
       // printf("Find file\n");
    //}

    while ((fgets(arr, 10000, fp)) != NULL) {
        //printf("%s\n",arr);
        strcat(output,arr);
        }
    fclose(fp);
    //printf("output is %s\n",output);
    //printf("output--->%s\n",output);
    char *output2;
    
    
    if((int)strlen(output)==0){
        output2="";
    } else {
        int a=0;
        output2 = malloc(sizeof (char) *(int) strlen(output)+sizeof(char));
        for (a = 0; a < (int) strlen(output); a++) {
            output2[a] = output[a];
        }
        output2[(int)strlen(output)]=0;
        //output2[(int)strlen(output)]="\0";
    }
    
    
    //strcat(output2,output);
    
    //printf("Function getStringFromFile: output is %s\n",output2);
    //printf("output2--->%s\n",output2);
    return output2;
}


// get string except   ' #include "" '
char* getStringFromFileExceptInclude(char *file_name){
    FILE *fp;
    char arr[10000]="";
    char output[10000]="";
    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
    // printf("Find file\n");
    //}
    
    while ((fgets(arr, 10000, fp)) != NULL) {
        char *temp_arr=trim(arr);
        if (find(temp_arr,"#include")==0) {
            continue;
        }
        strcat(output,arr);
    }
    fclose(fp);
    
    char *output2;
    
    
    if((int)strlen(output)==0){
        output2="";
    } else {
        int a=0;
        output2 = malloc(sizeof (char) *(int) strlen(output)+sizeof(char));
        for (a = 0; a < (int) strlen(output); a++) {
            output2[a] = output[a];
        }
        output2[(int)strlen(output)]=0;
        //output2[(int)strlen(output)]="\0";
    }
    
    
    //strcat(output2,output);
    
    //printf("Function getStringFromFile: output is %s\n",output2);
    //printf("output2--->%s\n",output2);
    return output2;
}


char* Walley_Eval(char *input_str){
    //printf("Walley_Eval %s\n",input_str);
    //return eval(input_str);
    
    input_str=replace(input_str, "**","^");
    
    
    // here may be some problem....
    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
    char *output;
    if (fraction_mode==TRUE) {
        
        
        // 0.8+2 return 2.8  8/10+2 return 14/5
        if (find(input_str,".")!=-1) {
            return eval_for_decimal_with_alpha(input_str);
        }
        else{
            // I changed the code to use mathomatic
            //output=eval_for_fraction_root_power(input_str);
            output=eval_for_fraction_with_alpha(input_str);
            //output=Walley_Mathomatic_Parse_For_Fraction(input_str);
        }
    }
    else{
        // I changed the code here to use mathomatic
        //output=eval(input_str);
        output=eval_for_decimal_with_alpha(input_str);
        //output=Walley_Mathomatic_Parse_For_Decimal(input_str);
    }
    return output;
}


bool stringHasAlphaExceptAlphaInString(char *input_str){
    
    while(find(input_str,"\"")!=-1){
        int first=find(input_str,"\"");
        int second=find_from_index(input_str,"\"",first+1);
        char *temp=substr(input_str,first,second+1);
        input_str=replace(input_str,temp,"");
    }
    
    while(find(input_str,"'")!=-1){
        int first=find(input_str,"'");
        int second=find_from_index(input_str,"'",first+1);
        char *temp=substr(input_str,first,second+1);
        input_str=replace(input_str,temp,"");
    }
    bool has_alpha=FALSE;
    int i=0;
    for(;i<(int)strlen(input_str);i++){
        if(isalpha(input_str[i])){
            has_alpha=TRUE;
            break;
        }
    }
    return has_alpha;  
}


char* findFirstVarNameOfExpression(char *input_str){
    
    while(find(input_str,"\"")!=-1){
        int first=find(input_str,"\"");
        int second=find_from_index(input_str,"\"",first+1);
        char *temp=substr(input_str,first,second+1);
        input_str=replace(input_str,temp,"");
    }
    
    while(find(input_str,"'")!=-1){
        int first=find(input_str,"'");
        int second=find_from_index(input_str,"'",first+1);
        char *temp=substr(input_str,first,second+1);
        input_str=replace(input_str,temp,"");
    }
    
    
    int begin=0;
    int end=(int)strlen(input_str)-1;
    
    int i=0;
    bool find_first_char=FALSE;
    
    for(;i<(int)strlen(input_str);i++){
        if(isalpha(input_str[i])){
            find_first_char=TRUE;
            begin=i;
        }
        
        if(find_first_char==TRUE&&!isalpha(input_str[i])){
            end=i-1;
            break;
        }
        
        if(find_first_char==TRUE&&i==(int)strlen(input_str)-1){
            end=i;
            break;
        }
        
        
    }
    char *var_name=substr(input_str,begin,end+1);
    //printf("function findFirstVarNameOfString:\ninput_str is %s\nvar_name is %s\n\n",input_str,var_name);
    return var_name;
    
}

char* findVarNameFromStringFromIndex(char *input_str,int from_index){
    
    input_str=substr(input_str,from_index,(int)strlen(input_str));
    return findFirstVarNameOfExpression(input_str);
    
}

/*
bool elementInExpressionAreAllString(char *input_str){
    int count=0;
    bool allAreString=TRUE;
    if(find(input_str,"\"")!=-1&&find(input_str,"'")!=-1){
        count=count_str(input_str,"\"");
        count=count+count_str(input_str,"'");
    } else if (find(input_str,"\"")!=-1){
        count=count_str(input_str,"\"");
    } else if (find(input_str,"'")!=-1){
        count=count_str(input_str,"'");
    } else {
        allAreString=FALSE;
    }
    
    return allAreString;
    
}**/

char *combineStringsToOneString(char *input_str){
   // printf("#### combineStringsToOneString ####\n");
   // printf("input_str %s\n",input_str);
    input_str=trim(input_str);
    if(find_not_in_string(input_str,"+")!=-1)
        input_str=replace_not_in_string(input_str,"+","#");
    int begin=0;
    int end=(int)strlen(input_str);
    int i=0;
    int length=(int)strlen(input_str);
    char temp[10000]="";
    strcat(temp,"\"");
    for(i=0;i<length;i++){
        if(input_str[i]=='#'&&charIsInString(input_str,i)==FALSE){
            end=i;
            char *string_to_append=substr(input_str,begin,end);
            string_to_append=trim(string_to_append);
            strcat(temp,substr(string_to_append,1,(int)strlen(string_to_append)-1));
            begin=end+1;
        }
    }
    end=(int)strlen(input_str);
    char *string_to_append=substr(input_str,begin,end);
    string_to_append=trim(string_to_append);
    strcat(temp,substr(string_to_append,1,(int)strlen(string_to_append)-1));
    strcat(temp,"\"");
    char *output=append("", temp);
    return output;
    
}

bool stringIsEmpty(char *input_str){
    input_str=trim(input_str);
    input_str=removeNFromBack(input_str);
    int i=0;
    bool isEmpty=TRUE;
    for(; i<(int)strlen(input_str);i++){
        if(input_str[i]!=' ')
            isEmpty=FALSE;
    }
    if (strcmp("\n", input_str)==0) {
        isEmpty=TRUE;
    }
    //// printf("Input Str |%s|,length %d,isEmpty %d\n",input_str,(int)strlen(input_str),isEmpty);
    return isEmpty;
}

/*
 * eg expressionIsAllString("'Hello'+'World'")------>TRUE
 *    expressionIsAllString("a+'hello'")------->FALSE
 */
bool expressionIsAllString(char *input_str){
    //printf("%s\n",input_str);
    bool all_are_string=FALSE;
    int i=0;
    int num_of_hao=0;  // num of " and '
    int num_of_plus=0;  // num of +
    for(i=0;i<(int)strlen(input_str);i++){
        //if(charIsInString(input_str,i)==FALSE && (input_str[i]=='\'' || input_str[i]=='"')){
        if((input_str[i]=='\'' || input_str[i]=='"')&&charIsInString(input_str,i)==FALSE){
            //printf("-->%c %d\n",input_str[i],i);
            num_of_hao++;
        }
        if(charIsInString(input_str,i)==FALSE && input_str[i]=='+')
            num_of_plus++;
    }
    num_of_hao=num_of_hao/2;
    if(num_of_hao==num_of_plus+1)
        all_are_string=TRUE;
    //if(num_of_hao==0 && num_of_plus==0)
    //    all_are_string=TRUE;
    //printf("Num of hao is %d, num of plus is %d\n",num_of_hao,num_of_plus);
    //printf("all are string %d\n",all_are_string);
    return all_are_string;
}

/*
 * eg finishFindingVarAndFunction("x+'Hello'")---->FALSE because x is here
 *    finishFindingVarAndFunction("Hello World")----->TRUE
 */
bool finishFindingVarAndFunction(char *input_str){
    int i=0;
    bool finish=TRUE;
    for(i=0;i<(int)strlen(input_str);i++){
        if(isalpha(input_str[i])==TRUE && charIsInString(input_str,i)==FALSE){
            finish=FALSE;
            break;
        }
    }
    return finish;
}


char* Walley_Eval_With_Variable_From_Var(struct VAR var[], char *input_str) {
    //printf("#### Walley_Eval_With_Variable_From_Var ####\n");
    //printf("------Input Str to this function is :|%s|------\n", input_str);
    
    // to solve input_str is -24 but output is 24
    if (input_str[0] == '-') {
        char *temp = malloc(sizeof (char) *((int) strlen(input_str) + 2));
        strcpy(temp, "0");
        strcat(temp, input_str);
        temp[(int) strlen(input_str) +1] = 0;
        input_str = temp;
    }
    

    char *output="";
    
    if (strcmp("list", variableValueType(input_str)) == 0) { // It doesn't work, I do not why
        //printf("It is list\n");
        return input_str;
    } else if (strcmp("dictionary", variableValueType(input_str)) == 0) { // It doesn't work, I do not why
        //printf("It is list\n");
        return input_str;
    } else if (stringIsDigit(input_str) == TRUE)
        return Walley_Eval(input_str);
    else if (expressionIsAllString(input_str) == TRUE) {
        //printf("all var are string\n");
        output = combineStringsToOneString(input_str);
        //printf("------> %s\n", output);
        //// printf("Function Walley_Eval_With_Variable all are string . \noutput------:%s\n", output);
        return output;
    }
    
     // I delete the following two sentences on 11/30 2:21
     // else if (find_not_in_string(input_str, ",") != -1)
     //   return input_str;
    
    
    else if (strcmp("None", input_str) == 0) {
        return "None";
    }
    
    // to solve |print 3+"hello"| problem
    else if(find(input_str,"\"")!=-1||find(input_str,"'")!=-1){
        char *output="";
        //printf("@@@ %s\n",input_str);
        int index_of_plus=find_not_in_str_list_dict_parenthesis(input_str, "+");
        if (index_of_plus==-1) {
            return input_str;
            printf("Mistake occurred while calling function Walley_Eval_With_Variable_From_Var\ninput_str %s can not be combined, no + found\n",input_str);
            exit(0);
        }
        int begin=0;
        while(TRUE){
            char *temp_str=substr(input_str, begin, index_of_plus);
            char *var_type=variableValueType(temp_str);
           // printf("temp_str is %s\n",temp_str);
           // printf("var_type is %s\n",var_type);
            if (strcmp(var_type,"string")==0||strcmp(var_type, "list")==0||strcmp(var_type, "dictionary")==0) {
             //   printf(" it is string list dictionary      %s\n",output);
                output=append(output, toCString(temp_str));
             //   printf(" it is string list dictionary      %s\n",output);
            }
            else{
                output=append(output, toCString(Walley_Eval_With_Variable_From_Var(var, temp_str)));
            }
            begin=index_of_plus+1;
            index_of_plus=find_from_index_not_in_str_list_dict_parenthesis(input_str, "+", begin);
            if (index_of_plus==-1) {
                temp_str=substr(input_str, begin, (int)strlen(input_str));
                var_type=variableValueType(temp_str);
               // printf("temp_str is %s\n",temp_str);
               // printf("var_type is %s\n",var_type);
                if (strcmp(var_type,"string")==0||strcmp(var_type, "list")==0||strcmp(var_type, "dictionary")==0) {
                    output=append(output, toCString(temp_str));
                }
                else{
                    output=append(output, toCString(Walley_Eval_With_Variable_From_Var(var, temp_str)));
                }
                break;
            }
            
        }
        
        return toString(output);
        
    }
    else {
        // I WRITE THE CODE IN SEPTEMBER 27
        /*
        int i = 0;
        int begin = 0;
        int end = (int) strlen(input_str);
        char *output = malloc(sizeof (char) *((int) strlen(input_str) + 1));
        for (i = 0; i < (int) strlen(input_str); i++) {
            output[i] = input_str[i];
        }
        output[(int) strlen(input_str)] = 0;
        bool has_var = FALSE;
        bool find_alpha = FALSE;
        bool finish_find_var = FALSE;
        for (i = 0; i < (int) strlen(input_str); i++) {
            //printf("#### Enter Loop Output is %s\n####",output);
            //printf("#### Output Length is %d\n",(int)strlen(output));
            //printf("*********** %c End is %d --->%s\n", input_str[i], end, output);
            int temp_length = (int) strlen(output);
            if (finishFindingVarAndFunction(output) == TRUE) {
                //// printf("Finish Finding Var And Function, output is |%s|\n", output);
                output = substr(output, 0, temp_length);
                break;
            }
            if (find_alpha == FALSE && (isalpha(input_str[i]) || input_str[i] == '_') && charIsInString(input_str, i) == FALSE) {
                //printf("Find alpha\n");
                //printf("--End this loop, output is %s\n",output);
                find_alpha = TRUE;
                begin = i;
                //printf("begin %d\n",begin);
            }
            
            if (find_alpha == TRUE && isSign(input_str[i]) && charIsInString(input_str, i) == FALSE) {
                find_alpha = FALSE;
                end = i;
                //printf("@@@@@@ end %d\n",end);
                finish_find_var = TRUE;
                
            }
            if (find_alpha == TRUE && ((isJudgeSign(input_str[i])) || input_str[i] == ')' || input_str[i] == ',' || input_str[i] == ' ') && charIsInString(input_str, i) == FALSE) {
                //printf("%d\n%d\n%d\n",find_alpha,(isJudgeSign(input_str[i])),input_str[i]==')');
                find_alpha = FALSE;
                end = i;
                //printf("------end %d\n",end);
                finish_find_var = TRUE;
                
            }
            if (find_alpha == TRUE && i == (int) strlen(input_str) - 1) {
                find_alpha = FALSE;
                end = i + 1;
                //printf("end %d\n",end);
                finish_find_var = TRUE;
            }
            //printf("--End this loop, output is %s\n",output);
            if (finish_find_var) {
                //printf("@@@@ Enter finish_find_var @@@@\n");
                //printf("------\n%s\n------\n",substr(input_str,begin,end));
                //printf("Begin %d, End %d\n",begin,end);
                char *var_name = substr(input_str, begin, end);
                char *var_value;
                if (find_not_in_string(var_name, ".") != -1) {
                    char *user = substr(var_name, 0, find_not_in_string(var_name, "."));
                    if (Var_Existed(VAR_var, user) == TRUE) {
                        //var_value = getValueFromValueName("__walley__.wy", var_name);
                        var_value=Var_getValueOfVar(VAR_var, var_name);
                    } else {
                        //var_value = getValueFromValueName(file_var_name, var_name);
                        var_value=Var_getValueOfVar(var, var_name);
                    }
                    
                } else {
                    if (Var_Existed(var, var_name) == TRUE) {
                        //var_value = getValueFromValueName(file_var_name, var_name);
                        var_value=Var_getValueOfVar(var, var_name);
                    } else {
                        var_value = var_name;
                    }
                }
                //printf("Var Name %s\nVar Value %s\n",var_name,var_value);
                int begin_temp = begin + (int) strlen(output)-(int) strlen(input_str);
                int end_temp = end + (int) strlen(output)-(int) strlen(input_str);
                
                //printf("Begin %d, End %d\n",begin_temp,end_temp);
                //printf("Before change, output is %s\n",output);
                output = replace_from_index_to_index(output, var_name, var_value, begin_temp, end_temp);
                //printf("Output is %s\n",output);
                has_var = TRUE;
                finish_find_var = FALSE;
                find_alpha = FALSE;
               
            }
            //printf("--End this loop, output is %s\n",output);
            
        }*/
        return Walley_Eval(input_str);
    }
    
    
    
}


/*
 * this function is used to solve Walley_Substitue problem
 * input-->'3+4,2+5'---->'7,7'
 */
char* Walley_Eval_All_From_Var(struct VAR struct_var[],char *input_str){
    //printf("--->%s\n",input_str);
    
    /* I delete this code on Dec 6
     * cause "x-->"+x can not be printed.
     * judge sign should be in str
    if (hasJudgeSign(input_str)==TRUE) {
        return input_str;
    }*/
    
    int m=0;
    for (m=0; m<(int)strlen(input_str); m++) {
        if (isJudgeSign(input_str[m])==TRUE && charIsInString(input_str, m)==FALSE) {
            return input_str;
        }
    }
    
    
    if (find_not_in_str_list_dict_parenthesis(input_str, ",")==-1) {
        //printf("\n\nDid not find\n");
        return Walley_Eval_With_Variable_From_Var(struct_var, input_str);
    }
    input_str=trim(input_str);
    input_str=append(input_str, ",");
    int begin=0;
    int end=(int)strlen(input_str);
    char *output="";
    //printf("---->%s\n",input_str);
    while (TRUE) {
        end=find_from_index_not_in_str_list_dict_parenthesis(input_str, ",", begin+1);
        if (end==-1) {
            break;
        }
        //printf("Begin %d, End %d\n",begin,end);
        char *sub=substr(input_str, begin, end);
        sub=Walley_Eval_With_Variable_From_Var(struct_var, sub);
        output=append(output, sub);
        output=append(output, ",");
        begin=end+1;
    }
    output=substr(output, 0, (int)strlen(output)-1);
    return output;
}




char *defineAFunction(char *input_str){
    int length_to=(int)strlen(substr(input_str, 0, find(input_str,")")))+4;
    char *temp=malloc(sizeof(char)*(length_to+1));
    strcpy(temp,substr(input_str, 0, find(input_str,")")));
    strcat(temp,"  ):");
    temp[length_to]=0;
    input_str=temp;
    
    
    input_str=removeAheadSpace(input_str);
    input_str=removeBackSpace(input_str);
    
    char *func_name=substr(input_str, find(input_str,"def")+3,find(input_str,"("));
    func_name=removeAheadSpace(func_name);
    func_name=removeBackSpace(func_name);
   //// printf("###### Function Name: %s ######\n",func_name);
    
        
    char *parameter_str=substr(input_str, find(input_str,"(")+1,find(input_str,")"));
    parameter_str=removeAheadSpace(parameter_str);
    parameter_str=removeBackSpace(parameter_str);
    
    
    int para_num=count_str(parameter_str,",")+1;
    
    if(stringIsEmpty(parameter_str)){
        para_num=0;
        parameter_str="None";
    }
   //// printf("###### Parameter is : %s ######\n",parameter_str);
   //// printf("you have %d paras",para_num);
    return "Now Design Function";
}

char *functionName(char *input_str){
    char *temp;
    temp=substr(input_str, 0, find(input_str,")"));
    
    // strcat problem 1
    //strcat(temp,"  ):");
    temp=append(temp, "  ):");
    
    
    input_str=temp;
    
    
    input_str=removeAheadSpace(input_str);
    input_str=removeBackSpace(input_str);
    
    char *func_name=substr(input_str, find(input_str,"def")+3,find(input_str,"("));
    func_name=removeAheadSpace(func_name);
    func_name=removeBackSpace(func_name);
    return func_name;
    
}

char *functionParameterStr(char *input_str){
    char *temp=append(substr(input_str, 0, find(input_str,")")), " ):");
    input_str=temp;   
    
    char *parameter_str=substr(input_str, find(input_str,"(")+1,find(input_str,")"));
    //printf("#### parameter_str is %s ####\n",parameter_str);
    parameter_str=removeAheadSpace(parameter_str);
    //printf("#### parameter_str is %s ####\n",parameter_str);
    parameter_str=removeBackSpace(parameter_str);
   //// printf("###### Parameter is : %s ######\n",parameter_str);
    
    
    int para_num=count_str(parameter_str,",")+1;
    
    if(stringIsEmpty(parameter_str)){
        para_num=0;
        parameter_str="None";
    }
    
    return parameter_str;
}

int numOfSpaceAheadString(char *input_str){
    int num=0;
    int i=0;
    //printf("%d",(int)strlen(input_str));
    //printf("'%c'\n",input_str[0]);
    if ((int) strlen(input_str) != 0) {
        for (; i < (int) strlen(input_str); i++) {
            if (input_str[i] != ' ') {
                break;
            } else {
                num = num + 1;
                //printf("index %d\n",i);
            }
        }
    }
    return num;
}

void writeStringToFile(char *file_name, char *str_to_file){
    //printf("#### writeStringToFile |%s|####\n",str_to_file);
    char *str_in_wy_ = getStringFromFile(file_name);
    //printf("str in wy %s\n",str_in_wy_);
    char *input_message=malloc(sizeof(char)*((int)strlen(str_to_file)+1));
    int i=0;
    for(i=0;i<(int)strlen(str_to_file);i++){
        input_message[i]=str_to_file[i];
    }
    input_message[(int)strlen(str_to_file)]=0;
    //printf("----Previous String in file is :%s\n----",str_in_wy);
    FILE *fw = fopen(file_name, "w");
    if((int)strlen(str_in_wy_)!=0)
        fputs(str_in_wy_, fw);
    fputs(input_message, fw);
    fclose(fw);    
}


//change later
void anaylizeExistedVariablesInExpression(char *input_str){
   //// printf("#### anaylizeExistedVariablesInExpression ####\n");
    //printf("input str is :%s\nlength is %d\n",input_str,(int)strlen(input_str));
    
    bool find_alpha=FALSE;
    bool finish_find_var=FALSE;
    bool find_function=FALSE;
    int begin=0;
    int end=(int)strlen(input_str);
    int i=0;
    for(;i<(int)strlen(input_str);i++){
        if(find_alpha==FALSE && isalpha(input_str[i])){
            find_alpha=TRUE;
            begin=i;
            //printf("begin %d\n",begin);
        }
        
        if(find_alpha==TRUE && input_str[i]=='('){
            find_function=TRUE;
            //printf("Find Function\n");
        }
        if(find_function){
            find_function=FALSE;
            //char *temp=substr(input_str,i,(int)strlen(input_str));
            int index_of_youkuohao=find_from_index(input_str,")",i);
            
            int num_of_zuo=count_str(substr(input_str,i,index_of_youkuohao+1),"(");
            int num_of_you = count_str(substr(input_str,i, index_of_youkuohao + 1), ")");
            //printf("zuo %d, you %d\n",num_of_zuo,num_of_you);
            while (num_of_zuo != num_of_you) {
                //printf("Bu Deng");
                index_of_youkuohao = find_from_index(input_str, ")", index_of_youkuohao + 1);
                num_of_zuo = count_str(substr(input_str,i, index_of_youkuohao + 1), "(");
                num_of_you = count_str(substr(input_str,i, index_of_youkuohao + 1), ")");
            }
            
            //printf("------\n%s\n-------\n",substr(input_str,begin,index_of_youkuohao+1));
            i=index_of_youkuohao;
            find_alpha=FALSE;
            continue;
        }
        
        if(find_alpha==TRUE && isSign(input_str[i])){
            find_alpha=FALSE;
            end=i;
            //printf("end %d\n",end);
            finish_find_var=TRUE;
            
        }
        if(find_alpha==TRUE && ((isJudgeSign(input_str[i])) || input_str[i]==')')){
            find_alpha=FALSE;
            end=i;
            //printf("end %d\n",end);
            finish_find_var=TRUE;
            
        }
        if(find_alpha==TRUE && i==(int)strlen(input_str)-1){
            find_alpha=FALSE;
            end=i+1;
            //printf("end %d\n",end);     
            finish_find_var=TRUE;
        }
        if(finish_find_var){
            //printf("------\n%s\n------\n",substr(input_str,begin,end));
            finish_find_var=FALSE;
        }
        
    }
}

//##################### This function has one problem############################

char *substitueExistedVarValueFromVar(char* input_str,struct VAR struct_var[]){//, char *file_function_name){
    //printf("input str is :%s\nlength is %d\n",input_str,(int)strlen(input_str));
    
    bool find_alpha=FALSE;
    bool finish_find_var=FALSE;
    bool find_function=FALSE;
    int begin=0;
    int end=(int)strlen(input_str);
    int i=0;
    //char *output=input_str;
    char *output=malloc(sizeof(char)*((int)strlen(input_str)+1));
    for(i=0;i<(int)strlen(input_str);i++){
        output[i]=input_str[i];
    }
    output[(int)strlen(input_str)]=0;
    bool has_var=FALSE;
    
    for(i=0;i<(int)strlen(input_str);i++){
        //printf("enter here\n");
        //printf("%s\n",output);
        //printf("i-->%d\n%c\n",i,input_str[i]);
        //printf("----find alpha %d--\n",find_alpha);
        if(find_alpha==FALSE && isalpha(input_str[i])){
            find_alpha=TRUE;
            begin=i;
            //printf("begin %d\n",begin);
        }
        
        if(find_alpha==TRUE && input_str[i]=='('){
            find_function=TRUE;
            //printf("Find Function\n");
        }
        if(find_function){
            find_function=FALSE;
            //char *temp=substr(input_str,i,(int)strlen(input_str));
            int index_of_youkuohao=find_from_index(input_str,")",i);
            
            int num_of_zuo=count_str(substr(input_str,i,index_of_youkuohao+1),"(");
            int num_of_you = count_str(substr(input_str,i, index_of_youkuohao + 1), ")");
            //printf("zuo %d, you %d\n",num_of_zuo,num_of_you);
            while (num_of_zuo != num_of_you) {
                //printf("Bu Deng");
                index_of_youkuohao = find_from_index(input_str, ")", index_of_youkuohao + 1);
                num_of_zuo = count_str(substr(input_str,i, index_of_youkuohao + 1), "(");
                num_of_you = count_str(substr(input_str,i, index_of_youkuohao + 1), ")");
            }
            
            //printf("------\n%s\n-------\n",substr(input_str,begin,index_of_youkuohao+1));
            i=index_of_youkuohao;
            find_alpha=FALSE;
            has_var=TRUE;
            continue;
        }
        
        if(find_alpha==TRUE && isSign(input_str[i])){
            find_alpha=FALSE;
            end=i;
            //printf("end %d\n",end);
            finish_find_var=TRUE;
            
        }
        if(find_alpha==TRUE && ((isJudgeSign(input_str[i])) || input_str[i]==')')){
            find_alpha=FALSE;
            end=i;
            //printf("--end-- %d\n",end);
            finish_find_var=TRUE;
            
        }
        if(find_alpha==TRUE && i==(int)strlen(input_str)-1){
            find_alpha=FALSE;
            end=i+1;
            //printf("end %d\n",end);
            finish_find_var=TRUE;
        }
        if(finish_find_var){
            //printf("------\n%s\n------\n",substr(input_str,begin,end));
            //printf("Begin %d, End %d\n",begin,end);
            char *var_name=substr(input_str,begin,end);
            //char *var_value=getValueFromValueName(file_var_name,var_name);
            char *var_value=Var_getValueOfVar(struct_var, var_name);
            
            //printf("Var Name %s\nVar Value %s\n",var_name,var_value);
            int begin_temp=begin+(int)strlen(output)-(int)strlen(input_str);
            int end_temp=end+(int)strlen(output)-(int)strlen(input_str);
            
            //printf("Begin %d, End %d\n",begin_temp,end_temp);
            //printf("Before change, output is %s\n",output);
            output=replace_from_index_to_index(output,var_name,var_value,begin_temp,end_temp);
            //printf("After change, output is %s\n",output);
            has_var=TRUE;
            finish_find_var=FALSE;
            find_alpha=FALSE;
           
        }
        
    }
    
    //if(has_var==FALSE){
    //    return input_str;
    //}
    //// printf("output is |%s|\n",output);
    return output;
}




/*
 * ########## Check whether shou run sentence
 ##########  Only support the conparison between numbers now
 * eg passConditionIfSentence("3>4")
 */
bool passConditionIfSentence(char *input_str){
    //// printf("#### passConditionIfSentence ####\n");
    //// printf("input_str is :|%s|\n",input_str);
    if (strcmp("TRUE", stringToUpperCase(input_str))==0) {
        return TRUE;
    }
    if (strcmp("FALSE", stringToUpperCase(input_str))==0) {
        return FALSE;
    }
    input_str=removeAheadSpace(input_str);
    input_str=removeBackSpace(input_str);

    /*
    char *temp=malloc(sizeof(char)*((int)strlen(input_str)+1));
    int a=0;
    for(a=0;a<(int)strlen(input_str);a++){
        temp[a]=input_str[a];
    }
    temp[(int)strlen(input_str)]=0;

    input_str=temp;
   */
    
    char *first_str;
    char *second_str;
    //int index=indexOfJudgeSignFromIndex(input_str,0);
    int i=0;
    int begin=0;
    bool find_var=FALSE;
    bool pass=FALSE;
    char *judge_sign;
    //input_str=substr(input_str,find(input_str,"if "),(int)strlen(input_str));
    //input_str=replace(input_str,"if ","");
    //input_str=removeAheadSpace(input_str);
    //printf("%s\n%d\n",input_str,(int)strlen(input_str));
    for(i=0;i<(int)strlen(input_str);i++){
        if(input_str[i]==' ')
            continue;
        if(find_var==FALSE && (isalpha(input_str[i]) || isdigit(input_str[i]) || input_str[i]=='\'' || input_str[i]=='"')){
            begin=i;
            find_var=TRUE;
            //printf("Find Var at index %d\n",i);
            
            //in order to support -2 > 1
            if(i>0 && isdigit(input_str[i]) && input_str[i-1]=='-')
                begin=begin-1;
        }
        
        
        if(isJudgeSign(input_str[i])==TRUE && find_var==TRUE && charIsInString(input_str,i)==FALSE){
            //printf("Find var is %d\n",find_var);
            //printf("Find Judge Sign at index %d\n",i);
            first_str=substr(input_str,begin,i);
            //printf("First str %s\n",first_str);
            if(isalpha(input_str[i+1])==TRUE || isdigit(input_str[i+1])==TRUE || input_str[i+1]=='\''||input_str[i+1]=='"' || input_str[i+1]=='-' || input_str[i+1]=='+'||input_str[i+1]=='*'||input_str[i+1]=='\\'){
                //printf("Enter 1\n");
                judge_sign=substr(input_str,i,i+1);
                //printf("judge sign is %s\n",judge_sign);
                //printf("%s\n",input_str);
                //printf("----- %d %d\n",i+1,(int)strlen(input_str));
                second_str=substr(input_str,i+1,(int)strlen(input_str));
                //printf("Second_Str is %s\n",second_str);
            }
            else{
                //printf("Enter 2\n");
                judge_sign=substr(input_str,i,i+2);
                second_str=substr(input_str,i+2,(int)strlen(input_str));
            }
            break;
        }
    }
    //##################################### Maybe some mistakes here ###################
    /*
     * I modified those codes on Dec 6
     *
    //first_str=Walley_Eval_With_Variable_From_File("__walley__.wy",first_str);
    //second_str=Walley_Eval_With_Variable_From_File("__walley__.wy",second_str);
    //printf("first_str is %s\n second_str is %s\n",first_str,second_str);
     */
    //printf("first str is %s\n second_str is %s\n",first_str,second_str);
    first_str=Walley_Eval_With_Variable_From_Var(NULL, first_str);
    second_str=Walley_Eval_With_Variable_From_Var(NULL, second_str);
    //#############################################################################
   //// printf("First %s\nSecond %s\nJudge Sign %s\n",first_str,second_str,judge_sign);
    first_str=removeAheadSpace(removeBackSpace(first_str));
    second_str=removeAheadSpace(removeBackSpace(second_str));
    char *first_str_type=variableValueType(first_str);
    char *second_str_type=variableValueType(second_str);
    //printf("num1 %f\nnum2 %f\n",num1,num2);
    if(strcmp(first_str_type,"string")==0 && strcmp(second_str_type,"string")==0){
       //// printf("It is the comparison between strings\n");
        first_str=substr(first_str,1,(int)strlen(first_str)-1);
        second_str=substr(second_str,1,(int)strlen(second_str)-1);
     if(strcmp(judge_sign,"==")==0){
        if(strcmp(first_str,second_str)==0){
            pass=TRUE;
        }
    } else if (strcmp(judge_sign,"!=")==0){
        if(strcmp(first_str,second_str)!=0){
            pass=TRUE;
        }
    } else if (strcmp(judge_sign,">")==0){
        //printf("enter here >\n");
        //printf("%s\n%s\n",first_str,second_str);
        if(strcmp(first_str,second_str)>0){
            pass=TRUE;
        }
    } else if (strcmp(judge_sign,"<")==0){
        if(strcmp(first_str,second_str)<0){
            pass=TRUE;
        }
    } else if (strcmp(judge_sign,">=")==0){
        if(strcmp(first_str,second_str)>=0){
            pass=TRUE;
        }
    } else if (strcmp(judge_sign,"<=")==0){
        if(strcmp(first_str,second_str)<=0){
            pass=TRUE;
        }
    } else {
        pass=FALSE;
        printf("Mistake occurred while calling function passConditionIfSentence\n");
    }       
        
        
        
    }
    
    else if((strcmp(first_str_type, "string")==0 && strcmp(second_str, "string")!=0)||(strcmp(first_str_type, "string")!=0 && strcmp(second_str, "string")==0)){
        return FALSE;
    }
    
    else {
        
        
        double num1=atof(eval_for_decimal_with_alpha(first_str));
        double num2=atof(eval_for_decimal_with_alpha(second_str));
        
        //printf("it is compared between number\n");
        //printf("Judge Sign %s\n",judge_sign);
    if(strcmp(judge_sign,"==")==0){
        //printf("enter\n");
        if(num1==num2){
            pass=TRUE;
        }
    } else if (strcmp(judge_sign,"!=")==0){
        if(num1!=num2){
            pass=TRUE;
        }
    } else if (strcmp(judge_sign,">")==0){
        if(num1>num2){
            pass=TRUE;
        }
    } else if (strcmp(judge_sign,"<")==0){
        if(num1<num2){
            pass=TRUE;
        }
    } else if (strcmp(judge_sign,">=")==0){
        if(num1>=num2){
            pass=TRUE;
        }
    } else if (strcmp(judge_sign,"<=")==0){
        if(num1<=num2){
            pass=TRUE;
        }
    } else {
        pass=FALSE;
        printf("Mistake occurred while calling function passConditionIfSentence\n");
    }
        
    }
   //// printf("------- pass is %d\n",pass);
    return pass;
}

/*
 eg, judgeWithAndAndOr("3>4 and 5<1 or 3>2")---->TRUE
 
 */
bool judgeWithAndAndOr(char *input_str){
    //printf("#### judgeWithAndAndOr ####\n");
    input_str=trim(input_str);
    bool pass=TRUE;
    char *temp=append("and ", input_str);
    temp=append(temp, " ");
    input_str=temp;
    //printf("@#@#|%s|\n",input_str);
    char *condition_sign;
    char *sentence;
    //int from_index=0;
//    bool just_begin=TRUE;
    bool find_not=FALSE;
    while(count_str_not_in_string(input_str,"and")!=0 || count_str_not_in_string(input_str,"or")!=0){
        //printf("--%s\n",input_str);
        //printf("enter\n");
        input_str=removeAheadSpace(input_str);
        condition_sign=substr(input_str,0,find_not_in_string(input_str," "));
        //printf("condition sign is %s\n",condition_sign);
        input_str=substr(input_str,find_not_in_string(input_str," ")+1,(int)strlen(input_str));
        //printf("input_str %s\n",input_str);
        input_str=removeAheadSpace(input_str);
        sentence=substr(input_str,0,find_not_in_string(input_str," "));
        //printf("sentence&&&& |%s|\n",sentence);
        if(strcmp("not",sentence)==0){
           //// printf("Find Not\n");
            find_not=TRUE;
            input_str=substr(input_str,find_not_in_string(input_str," ")+1,(int)strlen(input_str));
            sentence=substr(input_str,0,find_not_in_string(input_str," "));
        }
        //printf("sentence&&&&---> |%s|\n",sentence);
        bool temp=passConditionIfSentence(sentence);
        //printf("here\n");
        if(find_not==TRUE){
            if(temp==1){
                temp=0;
            } else {
                temp=1;
            }
            find_not=FALSE;
        }
//        if(just_begin==TRUE){
//            pass=temp;
//            just_begin=FALSE;
//        }
        //printf("temp is %d\npass is %d\n",temp,pass);
        //printf("condition sign is |%s|\n",condition_sign);
        pass=judge(temp,pass,condition_sign);
        
        //input_str=substr(input_str,find(input_str," ")+1,(int)strlen(input_str));
        input_str=substr(input_str,find_not_in_string(input_str," ")+1,(int)strlen(input_str));
        //printf("--%s\n",input_str);
    }
   // printf("++ Pass is ----> %d\n",pass);
    return pass;
}
/*eg judgeWithAndAndOrWithParenthesis("1<2 or (3>4 and 3==3)"):
 */
bool judgeWithAndAndOrWithParenthesis(char *input_str){
   //// printf("#### judgeWithAndAndOrWithParenthesis ####\n");
   //// printf("input_str ----> %s\n",input_str);
    int count_of_left=count_str(input_str,"(");
    int count_of_right=count_str(input_str,")");
    if(count_of_left != count_of_right){
        printf("Mistake occurred while calling function judgeWithAndAndOrWithParenthesis\ncount_of_left != count_of_right\n");
        exit(1);
    }
    while(count_str_not_in_string(input_str,"(")!=0){
        int left=find(input_str,"(");
        int right=find_from_index(input_str,")",left+1);
        char *temp=substr(input_str,left+1,right);
        //printf("Temp -------> %s\n",temp);
        //printf("$$$$$$$$$$$$\n");
        bool result=judgeWithAndAndOr(temp);
        char *result_str;
        if(result==1){
            result_str=" 1>0 ";
        } else {
            result_str=" 1<0 ";
        }
        //char *temp_temp=malloc(sizeof(char)*((int)strlen(input_str)+(int)strlen(result_str)-(int)strlen(temp)-2));
        //strcat(temp_temp,substr(input_str,0,left));
        //strcat(temp_temp,result_str);
        //strcat(temp_temp,substr(input_str,right+1,(int)strlen(input_str)));
        char *temp_temp=append(substr(input_str,0,left),result_str);
        temp_temp=append(temp_temp, substr(input_str,right+1,(int)strlen(input_str)));
        input_str=temp_temp;
    }
    if(find(input_str,"  ")!=-1){
        input_str=replace(input_str,"  "," ");
    }
    //printf("@@@@@@@@AAAAA  input_str is %s\n",input_str);
    return judgeWithAndAndOr(input_str);
}
/*Support variable
 */

bool judgeWithAndAndOrWithParenthesisAndVariablesFromVar(char *input_str, struct VAR struct_var[]){
    // I did not consider the situation when and or or is in string
    // I don not know what happened, but sometimes " space " can not be found
    if(find(input_str," and ")!=-1){
        input_str=replace(input_str," and ","+++++");
    }
    if(find(input_str," or ")!=-1){
        input_str=replace(input_str," or ","----");
    }
    //printf("%s\n",input_str);
    input_str=substitueExistedVarValueFromVar(input_str,struct_var);
    //printf("%s\n",input_str);
    if(find(input_str,"+++++")!=-1){
        input_str=replace(input_str,"+++++"," and ");
    }
    
    if(find(input_str,"----")!=-1){
        input_str=replace(input_str,"----"," or ");
    }
    //printf("%s\n",input_str);
    
    bool output=judgeWithAndAndOrWithParenthesis(input_str);
    return output;
}


/*
 
 * eg cleanJudgeSentence("4 > 3")---->"4>3"
 */
char *cleanJudgeSentence(char *judge_sentence){
    if(find_not_in_string(judge_sentence," > ")!=-1){
        judge_sentence=replace_not_in_string(judge_sentence," > ",">");
    } else if(find_not_in_string(judge_sentence," < ")!=-1){
        judge_sentence=replace_not_in_string(judge_sentence," < ","<");
    } else if(find_not_in_string(judge_sentence," == ")!=-1){
        judge_sentence=replace_not_in_string(judge_sentence," == ","==");
    } else if(find_not_in_string(judge_sentence," != ")!=-1){
        judge_sentence=replace_not_in_string(judge_sentence," != ","!=");
    } else if(find_not_in_string(judge_sentence," >= ")!=-1){
        judge_sentence=replace_not_in_string(judge_sentence," >= ",">=");
    } else if(find_not_in_string(judge_sentence," <= ")!=-1){
        judge_sentence=replace_not_in_string(judge_sentence," <= ","<=");
    }
    return judge_sentence;
}
/*
 * eg changeValueType("(int)","'123'")--------->123
 */
/*
char *changeValueType(char *value_type_to_be, char *value){
    value=removeAheadSpace(removeBackSpace(value));
    if(find(value_type_to_be,"int")!=-1){
        printf("Change value to int\n");
        if(value[0]=='\'' && ){
            
        }
    }
    
}**/

/*
 * this function is for special function in walley_core
 * eg x="Hello", x.find("Hello",1)
 * numOfParameters(" "Hello", 1")=2
 */
int numOfParameters(char *func_param){
    int i=0;
    int num=1;
    for(i=0;i<(int)strlen(func_param);i++){
        if(func_param[i]==',' && charIsInString(func_param,i)==FALSE && charIsInDictionary(func_param, i)==FALSE && charIsInList(func_param, i)==FALSE){
            num=num+1;
        }
        
    }
    return num;
}

/*
 * this function is for import
 * learned from python
 * like a file called math.wy
 * import math-->then add math. to the ahead of def sum(num1,num2)
 * import math as hi-->then add hi.
 */

/* This Code is So Old, so I tend to modify
char *functionOrClassAddAheadName(char *import_file_name, char *as_name) {
    printf("#### functionAddAheadName ####\n");
    printf("## import_file_name |%s| # as_name |%s|\n",import_file_name,as_name);
    import_file_name = trim(import_file_name);
    as_name = trim(as_name);
    //printf("import_file_name %s\n",import_file_name);
    //printf("as_name %s\n",as_name);
    FILE *fp = fopen(import_file_name, "r");
    char arr[1000] = "";
    char output[10000] = "";

    if (fp == NULL) {
        perror("File open error!\n");
        exit(1);
    }
    //else{
    //    printf("find file\n");
    //}

    while ((fgets(arr, 1000, fp)) != NULL) {
       //// printf("----> %s\n\n",arr);
        int space_num = numOfSpaceAheadString(arr);
        //printf("%d\n",space_num);
        if (space_num == 0) {
            if (find(arr, "def ") == 0) {
                char *remain = substr(arr, 4, (int) strlen(arr));
                remain = trim(remain);
                char *to_append;
                if (strcmp(as_name, "") != 0) {
                    to_append = malloc(sizeof (char) *(4 + 2 + (int) strlen(as_name)+(int) strlen(remain)));
                    strcat(to_append, "def ");
                    strcat(to_append, as_name);
                    strcat(to_append, ".");
                    strcat(to_append, remain);
                    to_append[(int) strlen(to_append)] = 0;
                } else {
                    to_append = malloc(sizeof (char) *(4 + 1 + (int) strlen(as_name)+(int) strlen(remain)));
                    strcat(to_append, "def ");
                    //strcat(to_append, as_name);
                    //strcat(to_append, ".");
                    strcat(to_append, remain);
                    to_append[(int) strlen(to_append)] = 0;
                }
                strcat(output, to_append);
            } else if (find(arr, "class ") == 0) {
                char *remain = substr(arr, 6, (int) strlen(arr));
                remain = trim(remain);
                char *to_append;
                if (strcmp(to_append, "") != 0) {
                    to_append = malloc(sizeof (char) *(8 + (int) strlen(as_name)+(int) strlen(remain)));
                    strcat(to_append, "class ");
                    strcat(to_append, as_name);
                    strcat(to_append, ".");
                    strcat(to_append, remain);
                    to_append[(int) strlen(to_append)] = 0;
                } else {
                    to_append = malloc(sizeof (char) *(7 + (int) strlen(as_name)+(int) strlen(remain)));
                    strcat(to_append, "class ");
                    //strcat(to_append,as_name);
                    //strcat(to_append,".");
                    strcat(to_append, remain);
                    to_append[(int) strlen(to_append)] = 0;
                }
                to_append[(int) strlen(to_append)] = 0;

                strcat(output, to_append);
            } else {
                strcat(output, arr);
            }
        } else {
            strcat(output, arr);
        }
    }

    fclose(fp);
    //printf("output is %s\n",output);
   //// printf("output--->%s\n",output);
    char *output2;


    if ((int) strlen(output) == 0) {
        output2 = "";
    } else {
        int a = 0;
        output2 = malloc(sizeof (char) *(int) strlen(output) + sizeof (char));
        for (a = 0; a < (int) strlen(output); a++) {
            output2[a] = output[a];
        }
        output2[(int) strlen(output)] = 0;
        //output2[(int)strlen(output)]="\0";
    }
    return output2;

}
*/

char *functionOrClassAddAheadName(char *import_file_name, char *as_name) {
   // printf("#### functionAddAheadName ####\n");
   // printf("## import_file_name |%s| # as_name |%s|\n",import_file_name,as_name);
    import_file_name = trim(import_file_name);
    as_name = trim(as_name);
    //printf("import_file_name %s\n",import_file_name);
    //printf("as_name %s\n",as_name);
    FILE *fp = fopen(import_file_name, "r");
    char arr[10000] = "";
    char *output="";
    
    if (fp == NULL) {
        perror("File open error!\n");
        exit(1);
    }
    //else{
    //    printf("find file\n");
    //}
    
    while ((fgets(arr, 10000, fp)) != NULL) {
        int space_num = numOfSpaceAheadString(arr);
        //printf("%d\n",space_num);
        if (space_num == 0) {
            if (find(arr, "def ") == 0) {
                char *remain = substr(arr, 4, (int) strlen(arr));
                remain = trim(remain);
                char *to_append;
                if (strcmp(as_name, "") != 0) {
                    to_append=append("def ", as_name);
                    to_append=append(to_append, append(".", remain));
                    
                } else {                    
                    to_append=append("def ", remain);
                }
                output=append(output, to_append);
            } else if (find(arr, "class ") == 0) {
                char *remain = substr(arr, 6, (int) strlen(arr));
                remain = trim(remain);
                char *to_append;
                if (strcmp(to_append, "") != 0) {                    
                    to_append=append("class ", as_name);
                    to_append=append(to_append, append(".", remain));
                    
                } else {                    
                    to_append=append("class ", remain);
                }                
                output=append(output, to_append);
            } else {

                // I changed the code here on Dec 4 to fix a.y ('a' is as_name) problem
                if (isExpression(arr)) {
                    output=append(output,append(append(as_name, "."), arr));
                } else {                
                    output=append(output, arr);
                }
            }
        } else {
            output=append(output, arr);
        }
    }
    
    fclose(fp);
    //printf("output is %s\n",output);
    //printf("output--->\n|%s|\n",output);
    return output;
}

char *getOneFunctionFromFile(char *import_file_name, char *func_name) {
    FILE *fp = fopen(import_file_name, "r");
    char arr[1000] = "";
    char output[10000] = "";

    if (fp == NULL) {
        perror("File open error!\n");
        exit(1);
    }
    //else{
    //    printf("find file\n");
    //}

    bool begin = FALSE;
    //bool finish=FALSE;
    while ((fgets(arr, 1000, fp)) != NULL) {
        if (stringIsEmpty(arr) == TRUE) {
            continue;
        }
        //printf("----> %s\n",arr);
        int space_num = numOfSpaceAheadString(arr);
        //printf("%d\n",space_num);
        if (begin == TRUE && space_num == 0) {
            if (arr[0] == '#') {
                strcat(output, arr);
                continue;
            } else {
                begin = FALSE;
                break;
            }
        }
        if (begin == TRUE) {
            strcat(output, arr);
        }
        if (space_num == 0) {
            char *temp = malloc(sizeof (char) *((int) strlen(func_name) + 2));
            strcpy(temp, func_name);
            strcat(temp, "(");
            temp[(int) strlen(func_name) + 1] = 0;

            if (find(arr, "def ") == 0 && find_not_in_string(arr, temp) != -1) {
                strcat(output, arr);
                begin = TRUE;
            } else if (find(arr, "class ") == 0 && find_not_in_string(arr, temp) != -1) {
                strcat(output, arr);
                begin = TRUE;
            }
        }
    }

    fclose(fp);
    //printf("output is %s\n",output);
    //printf("output--->%s\n",output);
    char *output2;


    if ((int) strlen(output) == 0) {
        output2 = "";
    } else {
        int a = 0;
        output2 = malloc(sizeof (char) *(int) strlen(output) + sizeof (char));
        for (a = 0; a < (int) strlen(output); a++) {
            output2[a] = output[a];
        }
        output2[(int) strlen(output)] = 0;
        //output2[(int)strlen(output)]="\0";
    }
    return output2;

}

/*
 ##########################################################################################################################
 This function is used for "from A import B as C" and mistake occurred while formating.
 C.B is formed whiling formating
 While the correct way should be replace B with C
 ##########################################################################################################################
char *getOneFunctionFromFileAndFormatItgetOneFunctionFromFile(char *import_file_name, char *func_name, char *as_name) {
    FILE *fp = fopen(import_file_name, "r");
    char arr[10000] = "";
    char output[10000] = "";

    if (fp == NULL) {
        perror("File open error!\n");
        exit(1);
    }
    //else{
    //    printf("find file\n");
    //}

    bool begin = FALSE;
    //bool finish=FALSE;
    while ((fgets(arr, 10000, fp)) != NULL) {
        if (stringIsEmpty(arr) == TRUE) {
            continue;
        }
        //printf("----> %s\n",arr);
        int space_num = numOfSpaceAheadString(arr);
        //printf("%d\n",space_num);
        if (begin == TRUE && space_num == 0) {
            if (arr[0] == '#') {
                strcat(output, arr);
                continue;
            } else {
                begin = FALSE;
                break;
            }
        }
        if (begin == TRUE) {
            strcat(output, arr);
        }
        if (space_num == 0) {
            char *temp = malloc(sizeof (char) *((int) strlen(func_name) + 2));
            strcat(temp, func_name);
            strcat(temp, "(");
            temp[(int) strlen(temp)] = 0;

            if (find(arr, "def ") == 0 && find_not_in_string(arr, temp) != -1) {
                char *remain = substr(arr, 4, (int) strlen(arr));
                remain = trim(remain);
                char *to_append;
                if (strcmp(as_name, "") != 0) {
                    to_append = malloc(sizeof (char) *(4 + 2 + (int) strlen(as_name)+(int) strlen(remain)));
                    strcat(to_append, "def ");
                    strcat(to_append, as_name);
                    strcat(to_append, ".");
                    strcat(to_append, remain);
                    to_append[(int) strlen(to_append)] = 0;
                } else {
                    to_append = malloc(sizeof (char) *(4 + 1 + (int) strlen(as_name)+(int) strlen(remain)));
                    strcat(to_append, "def ");
                    //strcat(to_append, as_name);
                    //strcat(to_append, ".");
                    strcat(to_append, remain);
                    to_append[(int) strlen(to_append)] = 0;
                }
                strcat(output, to_append);
                begin = TRUE;
            } else if (find(arr, "class ") == 0 && find_not_in_string(arr, temp) != -1) {
                char *remain = substr(arr, 4, (int) strlen(arr));
                remain = trim(remain);
                char *to_append;
                if (strcmp(to_append, "") != 0) {
                    to_append = malloc(sizeof (char) *(8 + (int) strlen(as_name)+(int) strlen(remain)));
                    strcat(to_append, "class ");
                    strcat(to_append, as_name);
                    strcat(to_append, ".");
                    strcat(to_append, remain);
                    to_append[(int) strlen(to_append)] = 0;
                } else {
                    to_append = malloc(sizeof (char) *(7 + (int) strlen(as_name)+(int) strlen(remain)));
                    strcat(to_append, "class ");
                    //strcat(to_append,as_name);
                    //strcat(to_append,".");
                    strcat(to_append, remain);
                    to_append[(int) strlen(to_append)] = 0;
                }
                strcat(output, to_append);
                begin = TRUE;
            }
        }
    }

    fclose(fp);
    //printf("output is %s\n",output);
    //printf("output--->%s\n",output);
    char *output2;


    if ((int) strlen(output) == 0) {
        output2 = "";
    } else {
        output2=append("", output);
    }
    return output2;

}
*/

char *getOneFunctionFromFileAndFormatItgetOneFunctionFromFile(char *import_file_name, char *func_name, char *as_name) {
    FILE *fp = fopen(import_file_name, "r");
    char arr[10000] = "";
    char *output = "";
    
    //printf("func_name %s as_name %s\n",func_name,as_name);
    
    if (fp == NULL) {
        perror("File open error!\n");
        exit(1);
    }
    //else{
    //    printf("find file\n");
    //}
    
    bool begin = FALSE;
    //bool finish=FALSE;
    while ((fgets(arr, 10000, fp)) != NULL) {
        if (stringIsEmpty(arr) == TRUE) {
            continue;
        }
        //printf("----> %s\n",arr);
        int space_num = numOfSpaceAheadString(arr);
        //printf("%d\n",space_num);
        if (begin == TRUE && space_num == 0) {
            if (arr[0] == '#') {
                output=append(output, arr);
                continue;
            } else {
                begin = FALSE;
                break;
            }
        }
        if (begin == TRUE) {
            output=append(output, arr);
        }
        if (space_num == 0) {
            if (isExpression(arr)) {
                char *var_name=variableName(arr);
                if (strcmp(var_name, func_name)==0) {
                    int index_of_equal=find(arr, "=");
                    return append(as_name,substr(arr, index_of_equal, (int)strlen(arr)) );
                }
            }
            char *temp = malloc(sizeof (char) *((int) strlen(func_name) + 2));
            strcpy(temp, func_name);
            strcat(temp, "(");
            temp[(int) strlen(func_name) + 1] = 0;
            
            if (find(arr, "def ") == 0 && find_not_in_string(arr, temp) != -1) {
                char *remain = substr(arr, 4, (int) strlen(arr));
                remain = trim(remain);
                char *to_append="";
                if (strcmp(as_name, "") != 0) {
                    to_append=append(to_append, "def ");
                    to_append=append(to_append, as_name);
                    to_append=append(to_append, substr(remain, find(remain, "("), (int)strlen(remain)));
                } else {
                    //to_append = malloc(sizeof (char) *(4 + 1 + (int) strlen(as_name)+(int) strlen(remain)));
                    to_append=append(to_append, "def ");
                    to_append=append(to_append, remain);
                }
                output=append(output, to_append);
                begin = TRUE;
            } else if (find(arr, "class ") == 0) {
                int index_of_class_name=find(arr, func_name);
                if (arr[index_of_class_name-1]!=' '||(arr[index_of_class_name+(int)strlen(func_name)]!=' '&&arr[index_of_class_name+(int)strlen(func_name)]!=':')) {
                    continue;
                }
                char *remain = substr(arr, 6, (int) strlen(arr));
                remain = trim(remain);
                char *to_append;
                if (strcmp(as_name, "") != 0) {
                    int index_of_extends=find(remain, "extends");
                    // Find Extends
                    if (index_of_extends!=-1) {
                        to_append=append("class ", as_name);
                        to_append=append(to_append, " ");
                        to_append=append(to_append, substr(remain, index_of_extends, (int)strlen(remain)));
                    } 
                    else {
                        to_append=append("class ", replace(remain,func_name,as_name));
                    }
                } else {
                    to_append=append(to_append, "class ");
                    to_append=append(to_append, remain);
                }
                output=append(output, to_append);
                begin = TRUE;
            }
        }
    }
    
    fclose(fp);
    return output;
}

bool checkWhetherStringExistsInFileNotInString(char *existing_file, char *check_str, int from_row){
    FILE *fp=fopen(existing_file,"r");
    bool existed=FALSE;
    if (fp!=NULL) {
        int i=0;
        char arr[10000]="";
        while (fgets(arr, 10000, fp)!=NULL) {
            char *arr_arr=removeNFromBack(arr);
            if (stringIsEmpty(arr_arr)) {
                continue;
            }
            if (i>=from_row) {
                existed=FALSE;
                int length=(int)strlen(arr_arr);
                int index=find_not_in_string(arr_arr, check_str);
                
                
                /*
                if (index!=-1) {
                    int index_of_last_char=index+(int)strlen(check_str)-1;
                    // most ahead
                    if (index==0) {
                        if (index_of_last_char<length-1) {
                            if (isalpha(arr_arr[index_of_last_char+1])==TRUE || arr_arr[index_of_last_char+1]=='_') {
                                existed=FALSE;
                                i++;
                                continue;
                            }
                        }
                    }
                    // most behind
                    else if (index>=1 && index_of_last_char==length-1) {
                        if (isalpha(arr_arr[index-1])==TRUE || arr_arr[index-1]=='_') {
                            existed=FALSE;
                            i++;
                            continue;
                        }
                    }
                    // middle
                    else {
                        if (isalpha(arr_arr[index-1])==TRUE || arr_arr[index-1]=='_' || isalpha(arr_arr[index_of_last_char+1])==TRUE || arr_arr[index_of_last_char+1]=='_') {
                            existed=FALSE;
                            i++;
                            continue;
                        }
                    }
                                        
                    existed=TRUE;
                    break;
                }
            */
                while (index!=-1) {
                    
                    int index_of_last_char=index+(int)strlen(check_str)-1;
                    // most ahead
                    if (index==0) {
                        if (index_of_last_char<length-1) {
                            if (isalpha(arr_arr[index_of_last_char+1])==TRUE || arr_arr[index_of_last_char+1]=='_') {
                                existed=FALSE;
                                index=find_from_index(arr_arr, check_str, index+1);
                                continue;
                            }
                        }
                    }
                    // most behind
                    else if (index>=1 && index_of_last_char==length-1) {
                        if (isalpha(arr_arr[index-1])==TRUE || arr_arr[index-1]=='_') {
                            existed=FALSE;
                            index=find_from_index(arr_arr, check_str, index+1);
                            continue;
                        }
                    }
                    // middle
                    else {
                        if (isalpha(arr_arr[index-1])==TRUE || arr_arr[index-1]=='_' || isalpha(arr_arr[index_of_last_char+1])==TRUE || arr_arr[index_of_last_char+1]=='_') {
                            existed=FALSE;
                            index=find_from_index(arr_arr, check_str, index+1);
                            continue;
                        }
                    }
                    
                    
                    existed=TRUE;
                    break;
                }
                
                if (existed==TRUE) {
                    break;
                }
                else{
                    i++;
                    continue;
                }
            }
            i++;
        }
        
    }
    
    fclose(fp);
    return existed;
}
// Auto clean unused variables in application
void Walley_Clean_Variables(char *existing_file, struct VAR struct_var[], int from_row){
    FILE *fp=fopen(existing_file,"r");
    if (fp!=NULL) {
        // after initialize walley.wy, some var remain....
        int i=0;
        while (struct_var[i].var_name!=NULL) {
            char *var_name=struct_var[i].var_name;
            bool exist=checkWhetherStringExistsInFileNotInString(existing_file, var_name, from_row);
            if (exist==FALSE) {

                // prevent from deleting those important variables.
                if (find(var_name, "__temp_while__")==0||
                    find(var_name, "__temp_while_space__")==0||
                    find(var_name, "__temp_string_in_while_loop__")==0||
                    find(var_name, "__temp_if__")==0||
                    find(var_name, "__temp_if__")==0||
                    find(var_name, "__temp_if_space__")==0||
                    find(var_name, "__has_run_if__")==0||
                    find(var_name, "__temp_for__")==0||
                    find(var_name, "__temp_i__")==0||
                    find(var_name, "__temp_string_in_for_loop__")==0||
                    find(var_name, "__temp_class__")==0||
                    find(var_name, "__temp_if__")==0||
                    find(var_name, "__temp_class_name_now_writting__")==0||
                    find(var_name, "__string_in_temp_class__")==0||
                    find(var_name, "__instance_name__")==0||
                    find(var_name, "__instance_var__")==0||
                    find(var_name, "__size_of_array__")==0
                    ) {
                    i++;
                    continue;
                }
                
                Var_removeVar(&struct_var, var_name);
            }
            i=i+1;
        }
    }
    fclose(fp);
}

char *changeIntToBinary(char x){
    unsigned i, n = (sizeof(x) * CHAR_BIT) - 1;
    char *output="";
    for (i = 0; i <= n; i++) {
        //printf("%d",(x >> (n-i)) & 1);
        output=append(output, intToCString((x >> (n-i)) & 1));
    }
    return output;
}

char *changeTextToBinary(char *input_str){
    char *binary="";
    int i;
    for( i=0; input_str[i]!='\0'; i++ )
    {
        char *bin=changeIntToBinary(input_str[i]);
        binary=append(binary, bin);
    }
    return binary;
}

char *changeTextToBinaryWithBoundary(char *input_str){
    char *binary="";
    int i;
    for( i=0; input_str[i]!='\0'; i++ )
    {
        char *bin=changeIntToBinary(input_str[i]);
        binary=append(binary, bin);
        binary=append(binary, "@");
    }
    return binary;
}

int changeBinaryToAscii(char *input_str){
    input_str=stringReverse(input_str);
    int length=(int)strlen(input_str);
    if (length!=8) {
        printf("Mistake occurred whiling calling function changeBinaryToAscii\ninput_str length is not 8\n");
        exit(2);
    }
    int i=0;
    int output_int=0;
    for (i=0; i<length; i++) {
        char temp=input_str[i];
        output_int+=atoi(charToString(temp))*pow(2, i);
        //printf("temp %c, output %d\n",temp,output_int);
    }
    //printf("output_int %d\n",output_int);
    return output_int;
}

char *changeBinaryToText(char *input_str){
    int length=(int)strlen(input_str);
    if (length%8!=0) {
        printf("Mistake occurred while translating Binary to Text\nBinary can not be divided by 8");
        exit(0);
    }
    int i=0;
    char *output="";
    for (; i<length-7; i=i+8) {
        char *temp_str=substr(input_str, i, i+8);
        output=append(output, charToString(changeBinaryToAscii(temp_str)));
    }
    return output;
}

void printBinary(unsigned char x) {
    unsigned i, n = (sizeof(x) * CHAR_BIT) - 1;
    
    for (i = 0; i <= n; i++) {
        printf("%d",(x >> (n-i)) & 1);
    }
    printf(" ");
}

/*
 For Example: FUNCTION_functions is :[
 show1:None:
 
 #~Begin
 
 ##Finish Init Params
 
 println "Show 1"
 
 
 #~End
 
 
 show2:None:
 
 #~Begin
 
 ##Finish Init Params
 
 show1()
 
 
 println "Show 2"
 
 
 #~End
]
 so functions are 
 show1
 show2
 
 return [show1,show2]
 
 
 */
char *getFunctionNameAndReturnList(char **FUNCTION_functions){
    int i=0;
    char *output="[";
    int length_of_Function_function=atoi(FUNCTION_functions[0]);
    while (i<length_of_Function_function) {
        if (strcmp(FUNCTION_functions[i], "#~Begin\n")==0) {
            char *function=FUNCTION_functions[i-1];
            function=substr(function, 0, find(function, ":"));
            output=append(output, append(function, ","));
        }
        i++;
    }
    output=substr(output, 0, (int)strlen(output)-1);
    output=append(output, "]");
    return output;
}
/*
 eg:
 
 a:1:int
 b:2:int
 return [a,b]
 
 */
char *getVarNameAndReturnList(struct VAR *struct_var){
    char *output="[";
    int i=0;
    int length=0;
    if (strcmp((struct_var)->var_name,"__size_of_array__")!=0) {
        printf("getVarNameAndReturnList..Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((struct_var)->var_value);
    }
    while (i<length) {
        char *var_name=struct_var[i].var_name;
        // prevent from deleting those important variables.
        if (find(var_name, "__temp_while__")==0||
            find(var_name, "__temp_while_space__")==0||
            find(var_name, "__temp_string_in_while_loop__")==0||
            find(var_name, "__temp_if__")==0||
            find(var_name, "__temp_if_space__")==0||
            find(var_name, "__has_run_if__")==0||
            find(var_name, "__temp_for__")==0||
            find(var_name, "__temp_i__")==0||
            find(var_name, "__temp_string_in_for_loop__")==0||
            find(var_name, "__temp_class__")==0||
            find(var_name, "__temp_class_name_now_writting__")==0||
            find(var_name, "__string_in_temp_class__")==0||
            find(var_name, "__instance_name__")==0||
            find(var_name, "__instance_var__")==0
            ) {
        }
        else{

            output=append(output, struct_var[i].var_name);
            output=append(output, ",");
        }
        
        i=i+1;
    }
    output=substr(output, 0, (int)strlen(output)-1);
    output=append(output, "]");
    return output;

}


// eg deleteOneFunctionFromBehind(FUNCTION,"print") will delete print function from FUNCTION
void deleteOneFunctionFromBehind(char **FUNCTION_functions, char *delete_func_name){
    int i=0;
    Str_addString(&FUNCTION_functions, NULL);
    while (FUNCTION_functions[i]!=NULL) {
        i++;
    }
    i=i-1;
    int final=i;
    int start=0;
    int end=final;
    char *func_name=append(delete_func_name, ":");
    while (i>=0) {
        if (find(FUNCTION_functions[i],func_name)==0) {
            //printf("FIND FUNCTION, BEGIN TO DELETE\n");
            start=i;
            break;
        }
        i--;
    }
    i=i+1;
    while (FUNCTION_functions[i]!=NULL) {
        //printf("------> |%s|\n",FUNCTION_functions[i]);
        if (find(FUNCTION_functions[i],"#~End\n")==0) {
            //printf("FIND END\n");
            end=i;
            break;
        }
        i++;
    }
    
    char **new_functions=malloc(sizeof(char**)*(final-end));
    i=0;
    while (i<(final-end)) {
        new_functions[i]=FUNCTION_functions[i+end];
        i++;
    }
    i=start;
    while (FUNCTION_functions[i]!=NULL) {
        FUNCTION_functions[i]=NULL;
        i++;
    }
    
    i=0;
    while (i<(final-end)) {
        FUNCTION_functions[start+i]=new_functions[i];
        i++;
    }
}








