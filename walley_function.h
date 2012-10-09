/* 
 * File:   walley_function.h
 * Author: shd101wyy
 *
 * Created on August 17, 2012, 2:39 PM
 */
//#include "walley_string.h"
#include "walley_operator.h"
//#include "walley_list.h"

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
        //printf("intput %s\n",input_str);
        char out[1000] = "";
        strcat(out, "\"");
        strcat(out, input_str);
        strcat(out, "\"");
        //printf("%s\n",out);
        int length=(int)strlen(out);
        char *output = malloc(sizeof (char) *(length + 1));
        int i = 0;
        for (i = 0; i < (int) strlen(out); i++) {
            output[i] = out[i];
        }
        output[(int) strlen(output)] = 0;
        output=substr(output,0,length);
        //printf("output is %s\n",output);
        //exit(0);
        return output;
    }
}

char* strInBrackets(char *input_str){
    input_str=removeAheadSpace(input_str);
    input_str=removeBackSpace(input_str);
    int begin_index=find(input_str,"(");
    //int end_index=find(input_str,")");
    int end_index=(int)strlen(input_str)-1;
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
/*
    if (find(input_str, "\"") != -1) {
        if (find_to_index(input_str, "\"", index_of_first_equa) != -1
                && find_from_index(input_str, "\"", index_of_first_equa + 1) != -1) {
            inside = TRUE;
        } else {
            //printf("Mistakes may occurred while calling function checkWhetherEquaInsideString:\"\n");
            inside=FALSE;
        }
    } else if (find(input_str, "'") != -1) {
        if (find_to_index(input_str, "'", index_of_first_equa) != -1
                && find_from_index(input_str, "'", index_of_first_equa + 1) != -1) {
            inside = TRUE;
        } else {
            //printf("Mistakes may occurred while calling function checkWhetherEquaInsideString:'\n");
            inside=FALSE;
        }
    } else {
        //printf("Mistakes occurred while calling function checkWhetherEquaInsideString:");
        inside = FALSE;
    }**/
    return inside;
}

bool checkWhetherComplete(char *input_str){
    bool complete=TRUE;
    if(input_str[0]==input_str[(int)strlen(input_str)-1]||
            (input_str[0]=='['&&input_str[(int)strlen(input_str)-1]==']')||
            (input_str[0]=='{'&&input_str[(int)strlen(input_str)-1]=='}'))
        complete=TRUE;
    else
        complete=FALSE;
    return complete;
}


char* checkValueType(char *input_str){
    char *type="";
    int index_of_first_equa=find(input_str,"=");
    if(index_of_first_equa!=-1&&checkWhetherEquaIsInsideString(input_str)==FALSE){
        //printf("index_of_first_equa is %d\n",index_of_first_equa);
        input_str=substr(input_str,index_of_first_equa+1,(int)strlen(input_str)); 
        //printf("input_str is :%s\n",input_str);
    }
    /*
    // Delete space ahead
    int i = 0;
    for (i=0; i < (int) strlen(input_str); i++) {
        if (input_str[i] != ' ') {
            //printf("\nfirst char %c\n",input_str[i]);
            //printf("input_str is :%s\n",input_str);
            //printf("Length of input_str is :%d\n",(int)strlen(input_str));
            //printf("substr is :%s\n",substr(input_str, i, (int)strlen(input_str)));

            input_str = substr(input_str, i, (int)strlen(input_str));
            //printf("input_str is :%s\n",input_str);
            break;
        }
    }
    // Delete space behind
    for (i=(int)strlen(input_str)-1; i >=0; i--) {
        if (input_str[i] != ' ') {
            input_str = substr(input_str, 0, i+1);
            break;
        }
    }*/
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
    char ch;
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


bool checkWhetherSameVarNameExistsFromFile(char *file_name,char *var_name){
    //printf("check");
    //printf("#### checkWhetherSameVarNameExistsFromFile ####\n");
    FILE *fp;
    char ch;
    char arr[1000]="";
    bool has_same_var_name=FALSE;
    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
      //  printf("\nFunction checkWhetherSameVarNameExistsFromFile Find file\n");
    //}
    //char *var_name_in_file="";
    while ((fgets(arr, 1000, fp)) != NULL) {
        //printf("arr---->%s\n",arr);
        if(find(arr,":")==-1)
            continue;
        char *var_name_in_file=substr(arr,0,find(arr,":"));
        //printf("var_name is %s\n",var_name_in_file);
        if (strcmp(var_name_in_file,var_name)==0){
            has_same_var_name=TRUE;
            //printf("has_same_var_name\n");
            break;
        }
    }
    //printf("Enter here\n");
    fclose(fp);
    //printf("has same var name is %d\n",has_same_var_name);
    return has_same_var_name;
}

// It is the same as checkWhetherSameVarNameExistsFromFile
bool checkWhetherSameVerbExistedFromFile(char *file_name,char *var_name){
    //printf("check");
    //printf("#### checkWhetherSameVarNameExistsFromFile ####\n");
    FILE *fp;
    char ch;
    char arr[1000]="";
    bool has_same_var_name=FALSE;
    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
      //  printf("\nFunction checkWhetherSameVerbExistedFromFile Find file\n");
    //}
    //char *var_name_in_file="";
    while ((fgets(arr, 1000, fp)) != NULL) {
        if(find(arr,":")==-1)
            continue;
        char *var_name_in_file=substr(arr,0,find(arr,":"));
        if (strcmp(var_name_in_file,var_name)==0){
            has_same_var_name=TRUE;
            break;
        }
    }
    fclose(fp);
    return has_same_var_name;
}

bool isFunction(char *input_str){
    //printf("#### isFunction ###\n");
    //printf("input_str %s\n",input_str);
    bool is_function=TRUE;
    input_str = removeAheadSpace(input_str);
    if(count_str(input_str,"(")==0 || count_str(input_str, ")")==0){
        is_function=FALSE;
        //printf("Didn't find ( or )");
    }
    else {
        char *function_name = substr(input_str, 0, find(input_str, "("));
        if (checkWhetherSameVarNameExistsFromFile("__walley_function__.wy", function_name))
            is_function = TRUE;
        else
            is_function = FALSE;
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
    } else {
        type="unknown type";
    } 
    //printf("here\n");
    
    bool is_func=isFunction(variable_value);
    //printf("there \n");
    if(is_func)
        type="function";
    
    //printf("Var Value %s\n",variable_value);
    //printf("type is %s\n",type);
    return type;

}
// Walley_String to C language String
char *toCString(char *input_str){
    input_str=trim(input_str);
    if(strcmp(variableValueType(input_str),"string")==0)
        return substr(input_str,1,(int)strlen(input_str)-1);
    else
        return input_str;
}
bool isExpression(char *input_str){
    bool is_expression=TRUE;
    if(find_not_in_string(input_str,"=")!=-1&&checkWhetherEquaIsInsideString(input_str)==FALSE){
        is_expression=TRUE;
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
    char arr[1000]="";
    char output[10000]="";
    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
       // printf("Find file\n");
    //}

    while ((fgets(arr, 1000, fp)) != NULL) {
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


char *eval(char *input_str){
    //printf("#### eval ####\ninput_str %s\n",input_str);
    input_str=trim(input_str);
    
    if(input_str[0]!='('){
        //char *temp=malloc(sizeof(char)*strlen(input_str)+2);
        char temp[1000]="(";
        //temp="(";
        strcat(temp,input_str);
        
        strcat(temp,")");
        input_str=temp;
    }
    int count=count_str(input_str,"(");
    //printf("count is %d\n",count);
    //printf("after automatically add (), the input_str is %s\n",input_str);
    
    int count_of_left_bracket=count_str(input_str,"(");
    int count_of_right_bracket=count_str(input_str,")");
    
    //char *output;
    if(count_of_left_bracket!=count_of_right_bracket){
        printf("Mistakes occurred while calling function eval:\nnum of ( != num of )");
        exit(1);
    }
    
    
    int index_of_final_left_bracket=0;
    int index_of_first_right_bracket=(int)strlen(input_str)-1;
    
    int i=0;
    while(count_str(input_str,"(")!=1){
        
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
        
        //printf("index of ( is %d\n",index_of_final_left_bracket);
        //printf("index of ) is %d\n",index_of_first_right_bracket);
        
        char *temp=malloc(sizeof(char)*(int)strlen(input_str));
        temp=substr(input_str,0,index_of_final_left_bracket);
        char *part_output=eval_simple_str(substr(input_str,index_of_final_left_bracket+1,index_of_first_right_bracket));
        strcat(temp,part_output);
        strcat(temp,substr(input_str,index_of_first_right_bracket+1,(int)strlen(input_str)));
        input_str=temp;
     
    }
    
    input_str=eval_simple_str(substr(input_str,1,(int)strlen(input_str)-1));
    
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
    return input_str;  
}

char* Walley_Eval(char *input_str){
    return eval(input_str);
}

bool stringHasAlpha(char *input_str){
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
   //// printf("#### combineStringsToOneString ####\n");
   //// printf("input_str %s\n",input_str);
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
    char *output=malloc(sizeof(char)*((int)strlen(temp)+1));
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    output[(int)strlen(output)]=0;
    //printf("input string is %s\n",input_str);
    /*
    input_str=removeBackSpace(input_str);
    input_str=removeAheadSpace(input_str);
    
    int num=0;
    bool finish_string=FALSE;
    bool find_first_sign=FALSE;
    int i=0;
    char *temp=malloc(sizeof(char)*(int)strlen(input_str));
    int begin=0;
    int end=(int)strlen(input_str)-1;
    //printf("begin is %d, end is %d\n",begin,end);
    
    for(i=0;i<(int)strlen(input_str);i++){
        
        if(num%2==0 && (input_str[i]=='\'' || input_str[i]=='"')){
            //printf("\nfind '\n");
            begin=i;
            //printf("begin is %d end is %d\n",begin,end);
            num++;
            continue;
        }
        
        
        if(num%2!=0&&(input_str[i]=='\'' || input_str[i]=='"')){
            end=i;
            num++;
            //printf("end is %d\n",end);
            finish_string=TRUE;
        }
        
        
        if(finish_string==TRUE){
            char *temp_temp=substr(input_str,begin+1,end);
            strcat(temp,temp_temp);
            finish_string=FALSE;
        } 
        //printf("What happened\n");
    }    
    //printf("temp is %s\n",temp);
    char *output=malloc(sizeof(char)*(int)strlen(temp)+sizeof(char)*2);
    
    if(input_str[0]=='"'&&find(input_str,"'")==-1){
        output[0]='"';
        strcat(output,temp);
        strcat(output,"\"");
    } else {
        output[0] = '\'';
        strcat(output, temp);
        strcat(output, "'");
    }
    **/
   //// printf("--->%s\n",output);
    return output;
    
}

bool stringIsEmpty(char *input_str){
    int i=0;
    bool isEmpty=TRUE;
    for(; i<(int)strlen(input_str);i++){
        if(input_str[i]!=' ')
            isEmpty=FALSE;
    }
    return isEmpty;
}
char *getValueFromValueName(char *file_name,char *var_name){
    //printf("#### getValueFromValueName ####\n");
    //printf("%s, %s\n",file_name,var_name);
    //printf("%s\n",file_name);
    FILE *fp;
    char ch;
    char arr[1000]="";
    char output[1000]="";
    int final_shuangyinhao=0;
    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("getValueFromValueName,File open error!\n");
        exit(1);
    } //else {
      //  printf("Find file\n");
    //}
    char *var_value="None";
    while ((fgets(arr, 1000, fp)) != NULL) {
        char *func_name_in_file=substr(arr,0,find(arr,":"));
        if (strcmp(func_name_in_file, var_name) == 0) {
            final_shuangyinhao=find_from_index_not_in_string(arr,":",find_not_in_string(arr,":")+1);
           // while(find_from_index(arr,":",final_shuangyinhao+1)!=-1){
           //     int temp=final_shuangyinhao;
           //     final_shuangyinhao=find_from_index(arr,":",final_shuangyinhao+1);
           //     if(final_shuangyinhao==-1)
           //         final_shuangyinhao=temp;
           //    printf("final_shuangyinhao %d\n",final_shuangyinhao);
           //}
            int a=0;
            int place[10000];
            int count=0;
            for(a=0;a<(int)strlen(arr);a++){
                if(arr[a]==':' && charIsInString((char*)arr,a)==FALSE){
                    place[count]=a;
                    //printf("%d\n",place[count]);
                    count++;
                }
            }
            final_shuangyinhao=place[count-1-1];
            //printf("arr is |%s|,%d,%d\n",arr,find_not_in_string(arr,":")+1,find_from_index_not_in_string(arr,":",final_shuangyinhao));
            //var_value=substr(arr,find(arr,":")+1,find_from_index(arr,":",find(arr,":")+1));
            var_value=substr(arr,find_not_in_string(arr,":")+1,find_from_index_not_in_string(arr,":",final_shuangyinhao));
            break;
        } 
        //free(func_name_in_file);
    }
    //printf("VAR VALUE is %s\n",var_value);
    fclose(fp);
    return var_value;
}
char* Walley_Eval_With_Variable_From_File(char *file_var_name, char *input_str) {
   //// printf("#### Walley_Eval_With_Variable_From_File ####\n");
   //// printf("------Input Str to this function is :|%s|------\n", input_str);

    // to solve input_str is -24 but output is 24
    if (input_str[0] == '-') {
        char *temp = malloc(sizeof (char) *((int) strlen(input_str) + 2));
        strcat(temp, "0");
        strcat(temp, input_str);
        temp[(int) strlen(temp)] = 0;
        input_str = temp;
    }

    int from_index = 0;

    bool all_var_are_string = TRUE;

    int var_num = 0;

    char *output;

    //printf("|%c|\n",input_str[(int)strlen(input_str)-1]);
    char *input_str_type = variableValueType(input_str);
    //printf("type is %s\n",input_str_type);
    //printf("|%c,%c|\n",input_str[0],input_str[(int)strlen(input_str)-1]);
    //printf("input _str |%s|\n",input_str);
    //bool enterLoop=FALSE;
    if (strcmp("list", variableValueType(input_str)) == 0) { // It doesn't work, I do not why
        //printf("It is list\n");
        return input_str;
    } else if (strcmp("dictionary", variableValueType(input_str)) == 0) { // It doesn't work, I do not why
        //printf("It is list\n");
        return input_str;
    } else if (stringIsDigit(input_str) == TRUE)
        return input_str;
    else if (expressionIsAllString(input_str) == TRUE) {
       //// printf("all var are string\n");
        output = combineStringsToOneString(input_str);
        //printf("------> %s\n", output);
       //// printf("Function Walley_Eval_With_Variable all are string . \noutput------:%s\n", output);
        return output;
    } else if (find_not_in_string(input_str, ",") != -1)
        return input_str;
    else if (strcmp("None", input_str) == 0) {
        return "None";
    } else {
        /*
        printf("Normal Eval\n");
        while (stringHasAlphaExceptAlphaInString(input_str)) {
            //enterLoop=TRUE;
            if(finishFindingVarAndFunction(input_str)){
                break;
            }
            char* var_name = findVarNameFromStringFromIndex(input_str, from_index);
            //printf("input_str is %s var_name is %s length of var_name is %d\n",input_str,var_name,(int)strlen(var_name));


            FILE *fp;
            char ch;
            char arr[1000] = "";

            if ((fp = fopen(var_in_file_name, "r")) == NULL) {
                perror("File open error!!\n");
                exit(1);
            } //else {
            //printf("Find file\n");
            //}
            //char *var_name_in_file="";
            bool find_required_var_name = FALSE;

            while ((fgets(arr, 1000, fp)) != NULL) {

                if (strcmp(var_name, substr(arr, 0, find(arr, ":"))) == 0) {
                    find_required_var_name = TRUE;

                    var_num += 1;

                    char *var_value = substr(arr, find(arr, ":") + 1, find_from_index(arr, ":", find(arr, ":") + 1));
                    char *var_type = substr(arr, find_from_index(arr, ":", find(arr, ":") + 1), (int) strlen(arr));
                    //var_type=removeBackSpace(var_type);
                    //var_type=removeAheadSpace(var_type);

                    if (find(var_type, "string") != -1) {
                        var_type = "string";
                    } else if (find(var_type, "int") != -1) {
                        var_type = "int";
                    } else if (find(var_type, "double") != -1) {
                        var_type = "double";
                    }

                    //printf("var_type is %s",var_type);
                    if (strcmp(var_type, "string") != 0) {
                        all_var_are_string = FALSE;
                        //printf("not all var are string\nbecause the var type now is %s\n",var_type);
                        //printf("length of var_type is %d\n",(int)strlen(var_type));
                    }


                    char *temp = malloc(sizeof (char) *(int) strlen(input_str));

                    strcat(temp, substr(input_str, 0, find(input_str, var_name)));
                    strcat(temp, var_value);
                    strcat(temp, substr(input_str, find(input_str, var_name)+(int) strlen(var_name), (int) strlen(input_str)));

                    from_index = find(input_str, var_name)+(int) strlen(var_value);

                    input_str = temp;
                    //printf("after temp, input_str is %s\nfrom index is %d\nvariable_name is %s\n", input_str,from_index,var_name);

                }
                //else {
                  //  continue;
                //}
            }
            if (find_required_var_name == FALSE) {
                printf("Mistake occurred while calling function: Walley_Eval_With_Variable_From_File\nUnseen var_name %s appeared\n", var_name);
                //exit(1);
            }

            fclose(fp);
        }
        output = Walley_Eval(input_str);
        printf("------> %s\n", output);
        //printf("Function Walley_Eval_With_Variable \noutput------:%s\n",output);
        return output;
         * **/
        // I WRITE THE CODE IN SEPTEMBER 27
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
                    if (checkWhetherSameInstanceExisted("__walley__.wy", user) == TRUE) {
                        var_value = getValueFromValueName("__walley__.wy", var_name);
                    } else {
                        var_value = getValueFromValueName(file_var_name, var_name);
                    }

                } else {
                    if (checkWhetherSameVarNameExistsFromFile(file_var_name, var_name) == TRUE) {
                        var_value = getValueFromValueName(file_var_name, var_name);
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
                //free(var_name);
                //free(var_value);
            }
            //printf("--End this loop, output is %s\n",output);

        }
       //// printf("output is %s\n",output);
        return Walley_Eval(output);
    }



}

/*
 * this function is used to solve Walley_Substitue problem
 * input-->'3+4,2+5'---->'7,7'
 */
char* Walley_Eval_All_From_File(char *file_var_name,char *input_str){
    //printf("--->%s\n",input_str);
    if (find_not_in_str_list_dict_parenthesis(input_str, ",")==-1) {
        return input_str;
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
        sub=Walley_Eval_With_Variable_From_File(file_var_name, sub);
        output=append(output, sub);
        output=append(output, ",");
        begin=end+1;
    }
    output=substr(output, 0, (int)strlen(output)-1);
    return output;
}

char* Walley_Eval_With_Variable(char *input_str){
   //// printf("#### Run Walley_Eval_With_Variable ####\n");
    //bool done=FALSE;
    /*
    int from_index = 0;
    
    bool all_var_are_string=TRUE;
    
    int var_num=0;
    
    if(stringHasAlpha(input_str)==FALSE){
        char *type=variableValueType(input_str);
        if(strcmp(type,"string")!=0)
            all_var_are_string=FALSE;
    }
    
    while (stringHasAlpha(input_str)) {
        char* var_name = findVarNameFromStringFromIndex(input_str, from_index);
        //printf("lalala input_str is %s, from_index is %d\n", input_str, from_index);
        //printf("var_name is %s\n,var_name in file is %s\n", var_name, substr(arr, 0, find(arr, ":")));
        if(strcmp(var_name,"")==0)
            break;
        FILE *fp;
        char ch;
        char arr[1000]="";
        
        if ((fp = fopen("__walley__.wy", "r")) == NULL) {
            perror("File open error!\n");
            exit(1);
        } //else {
            //printf("Find file\n");
        //}
        //char *var_name_in_file="";
        bool find_required_var_name=FALSE;

        while ((fgets(arr, 1000, fp)) != NULL) {
            
            if (strcmp(var_name, substr(arr, 0, find(arr, ":"))) == 0) {
                find_required_var_name=TRUE;
                
                var_num+=1;
                
                char *var_value = substr(arr, find(arr, ":") + 1, (int) strlen(arr));
                var_value=removeAheadSpace(var_value);
                var_value=removeBackSpace(var_value);
                
                printf("value is %s value type %s\n",var_value,variableValueType(var_value));
                
                printf("count of \" is %d\n",count_str(var_value,"\""));
                
                if(strcmp(variableValueType(var_value),"string")!=0)
                    all_var_are_string=FALSE;
                
                char *temp = malloc(sizeof (char) *(int) strlen(input_str));
                //printf("1\n");
                strcat(temp, substr(input_str, 0, find(input_str, var_name)));
                //printf("2\n");
                strcat(temp, var_value);
                strcat(temp, substr(input_str, find(input_str, var_name)+(int) strlen(var_name), (int) strlen(input_str)));
                //printf("3\n");
                //printf("temp is %s\n", temp);

                from_index = find(input_str, var_name)+(int) strlen(var_value);

                input_str = temp;
                printf("after temp, input_str is %s\nfrom index is %d\nvariable_name is %s\n", input_str,from_index,var_name);
                
            }        
        }
        if(find_required_var_name==FALSE){
            printf("Mistake occurred while calling function: Walley_Eval_With_Variable\nUnseen var_name %s appeared\n",var_name);
            exit(1);
        }
        
        fclose(fp);
    }
   
    printf("------ %s",input_str);
    return input_str;**/
    
    //input_str=putKnownVariableIntoExpression(input_str);
    /*
    int from_index = 0;
    
    bool all_var_are_string=TRUE;
    
    int var_num=0;
    
    //bool enterLoop=FALSE;
    
  
    
    while (stringHasAlphaExceptAlphaInString(input_str)) {
        //enterLoop=TRUE;
        char* var_name = findVarNameFromStringFromIndex(input_str, from_index);
        //printf("input_str is %s var_name is %s length of var_name is %d\n",input_str,var_name,(int)strlen(var_name));
 
        
        FILE *fp;
        char ch;
        char arr[1000]="";
        
        if ((fp = fopen("__walley__.wy", "r")) == NULL) {
            perror("File open error!\n");
            exit(1);
        } //else {
            //printf("Find file\n");
        //}
        //char *var_name_in_file="";
        bool find_required_var_name=FALSE;

        while ((fgets(arr, 1000, fp)) != NULL) {
            
            if (strcmp(var_name, substr(arr, 0, find(arr, ":"))) == 0) {
                find_required_var_name=TRUE;
                
                var_num+=1;
                
                char *var_value = substr(arr, find(arr, ":") + 1, find_from_index(arr,":",find(arr, ":") + 1));
                char *var_type = substr(arr, find_from_index(arr,":",find(arr, ":") + 1), (int)strlen(arr));
                //var_type=removeBackSpace(var_type);
                //var_type=removeAheadSpace(var_type);

                if (find(var_type, "string") != -1) {
                    var_type = "string";
                } else if (find(var_type, "int") != -1) {
                    var_type = "int";
                } else if (find(var_type, "double") != -1) {
                    var_type = "double";
                }
                
                //printf("var_type is %s",var_type);
                if(strcmp(var_type,"string")!=0){
                    all_var_are_string=FALSE;
                    //printf("not all var are string\nbecause the var type now is %s\n",var_type);
                    //printf("length of var_type is %d\n",(int)strlen(var_type));
                }
                
                
                char *temp = malloc(sizeof (char) *(int) strlen(input_str));
               
                strcat(temp, substr(input_str, 0, find(input_str, var_name)));
                strcat(temp, var_value);
                strcat(temp, substr(input_str, find(input_str, var_name)+(int) strlen(var_name), (int) strlen(input_str)));
                
                from_index = find(input_str, var_name)+(int) strlen(var_value);

                input_str = temp;
                //printf("after temp, input_str is %s\nfrom index is %d\nvariable_name is %s\n", input_str,from_index,var_name);
                
            }        
        }
        if(find_required_var_name==FALSE){
            printf("Mistake occurred while calling function: Walley_Eval_With_Variable\nUnseen var_name %s appeared\n",var_name);
            exit(1);
        }
        
        fclose(fp);
    }
    if(find(input_str,"\"")==-1&&find(input_str,"'")==-1){
        all_var_are_string=FALSE;
    }
    
    printf("------ %s\n",input_str);
    char *output;
    if(all_var_are_string==TRUE){
        //printf("all var are string\n");
        output=combineStringsToOneString(input_str);
        //printf("Function Walley_Eval_With_Variable all are string . \noutput------:%s\n",output);
        return output;
    } else {
        output=Walley_Eval(input_str);
        //printf("Function Walley_Eval_With_Variable \noutput------:%s\n",output);
        return output;
    }**/
    return Walley_Eval_With_Variable_From_File("__walley__.wy",input_str);
}


char *defineAFunction(char *input_str){
    char *temp=malloc(sizeof(char)*(int)strlen(input_str)+sizeof(char)*1);
    temp=substr(input_str, 0, find(input_str,")"));
    strcat(temp,"  ):");
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
    char *temp=malloc(sizeof(char)*(int)strlen(input_str)+sizeof(char)*1);
    temp=substr(input_str, 0, find(input_str,")"));
    strcat(temp,"  ):");
    input_str=temp;
    
    
    input_str=removeAheadSpace(input_str);
    input_str=removeBackSpace(input_str);
    
    char *func_name=substr(input_str, find(input_str,"def")+3,find(input_str,"("));
    func_name=removeAheadSpace(func_name);
    func_name=removeBackSpace(func_name);
    return func_name;
    
}

char *functionParameterStr(char *input_str){
    char *temp=malloc(sizeof(char)*(int)strlen(input_str)+sizeof(char)*1);
    strcat(temp,substr(input_str, 0, find(input_str,")")));
    //temp=substr(input_str, 0, find(input_str,")"));
    //printf("#### temp is %s ####\n",temp);
    strcat(temp," ):");
    //printf("#### temp is %s ####\n",temp);
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
    //strcat(input_message, str_to_file);
    //char *input_message=malloc(sizeof(char)*(int)strlen(str_in_wy)+sizeof(char)*(int)strlen(str_to_file));
    //strcat(input_message,str_in_wy);
    //strcat(input_message,str_to_file);
    
    //fputs(input_message,fp);
    //free(input_message);
    
    //fprintf(fw,"%s",str_in_wy_);
    //fprintf(fw,"%s",input_message);
    if((int)strlen(str_in_wy_)!=0)
        fputs(str_in_wy_, fw);
    fputs(input_message, fw);
    //fputs(str_to_file, fp);
   // printf("input_str--------%s\n",str_to_file);
    //printf("input_message----%s\n",input_message);
    fclose(fw);    
    //free(input_message);
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
            char *temp=substr(input_str,i,(int)strlen(input_str));
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
        if(find_alpha==TRUE && (isJudgeSign(input_str[i])) || input_str[i]==')'){
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
    return all_are_string;
        
}
//##################### This function has one problem############################
// Now Problem is solved
char *substitueExistedVarValueFromFile(char* input_str,char *file_var_name){//, char *file_function_name){
    //printf("input str is :%s\nlength is %d\n",input_str,(int)strlen(input_str));
    
    bool find_alpha=FALSE;
    bool finish_find_var=FALSE;
    bool find_function=FALSE;
    int begin=0;
    int end=(int)strlen(input_str);
    int i=0;
    //char *output=input_str;
    char *output=malloc(sizeof(char)*(int)strlen(input_str));
    for(i=0;i<(int)strlen(input_str);i++){
        output[i]=input_str[i];
    }
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
            char *temp=substr(input_str,i,(int)strlen(input_str));
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
            char *var_value=getValueFromValueName(file_var_name,var_name);
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
     
            //char *temp=malloc(sizeof(char)*(int)strlen(output));
            //printf("length %d\n",(int)strlen(output));
            //strcat(temp,output);
            //free(output);
            //output=temp;
            //printf("o\n");
            //free(var_name);
            //free(var_value);
        }
        
    }
    
    //if(has_var==FALSE){
    //    return input_str;
    //}
   //// printf("output is |%s|\n",output);
    return output;
}

void cleanFunctionFile(char *file_func_name){
        char *output=getStringFromFile(file_func_name);
        //// if(output[(int)strlen(output)-1]=='\n')
            //// printf("\\n");
        int i=0;
        char *output_output=malloc(sizeof(char)*(int)strlen(output));
        int begin=0;
        int first=find(output,"\n");
        int second=find_from_index(output,"\n",first+1);
        
        //printf("First %d, Second %d\n",first,second);
        for(;i<count_str(output,"\n");i++){
            if(second==-1){
                break;
            }
            char *first_str=substr(output,begin,first);
            char *second_str=substr(output,first+1,second);
            first_str=removeBackSpace(first_str);
            second_str=removeBackSpace(second_str);
            //printf("First-%s\nSecond-%s\n",first_str,second_str);
            if(strcmp(first_str,second_str)==0){
                //printf("Find Same\n");
                char *temp=removeAheadSpace(first_str);
                if(find(temp,"def ")==0){
                    int end_of_shuang=find(first_str,":");
                    int temp_num=end_of_shuang;
                    while(find_from_index(first_str,":",end_of_shuang+1)!=-1){
                        temp_num=end_of_shuang;
                        end_of_shuang=find_from_index(first_str,":",end_of_shuang+1);
                        if(end_of_shuang==-1)
                            break;
                    }
                    first_str=substr(first_str,0,temp_num+1);
                }
                    
                strcat(output_output,first_str);
                strcat(output_output,"\n");
                begin=second+1;
                first=find_from_index(output,"\n",begin);
                second=find_from_index(output,"\n",first+1);               
            } else {
                //printf("Not Same\n");
                char *temp=removeAheadSpace(first_str);
                if(find(temp,"def ")==0){
                    int end_of_shuang=find(first_str,":");
                    int temp_num=end_of_shuang;
                    while(find_from_index(first_str,":",end_of_shuang+1)!=-1){
                        temp_num=end_of_shuang;
                        end_of_shuang=find_from_index(first_str,":",end_of_shuang+1);
                        if(end_of_shuang==-1)
                            break;
                    }
                    first_str=substr(first_str,0,temp_num+1);
                }
                strcat(output_output,first_str);
                strcat(output_output,"\n");
                //strcat(output_output,second_str);
                //strcat(output_output,"\n");
                begin=first+1;
                first=find_from_index(output,"\n",begin);
                second=find_from_index(output,"\n",first+1);
                //printf("-----first %d-- ----second %d--\n",first,second);
            }
         
            
            
        }
        //printf("%s",output_output);
        FILE *fp2=fopen(file_func_name,"w");
        fputs(output_output,fp2);
        fclose(fp2);
}

char* print_from_var_file(char *var_in_file_name, char *input_str){
    return Walley_Eval_With_Variable_From_File(var_in_file_name,input_str);
}
char* print(char *input_str){
    /*
    if(strcmp(checkValueType(input_str),"string")==0){
       
        if(input_str[0]=='\"'||input_str[0]=='\''){
            input_str=substr(input_str,1,(int)strlen(input_str)-1);
        } else {
            input_str="mistake occurred while calling function print";
        }
        //printf("The input_str is %s",input_str);
        return input_str;
    } else {
        printf("mistake occurred while calling function print");
        return "mistake occurred while calling function print";
    }**/
    return print_from_var_file("__walley__.wy",input_str);
}
char *println_from_var_file(char *var_in_file_name, char *input_str){
    char *input= Walley_Eval_With_Variable_From_File(var_in_file_name,input_str);
    char *output=malloc(sizeof(char)*(int)strlen(input));
    strcat(output,input);
    strcat(output,"\n");
    return output;
}
char* println(char *input_str){
    /*
    if(strcmp(checkValueType(input_str),"string")==0){
        if(input_str[0]=='\"'||input_str[0]=='\''){
            input_str=substr(input_str,1,(int)strlen(input_str)-1);
        } else {
            input_str="mistake occurred while calling function print";
        }
        return strcat(input_str,"\n");
    } else {
        printf("mistake occurred while calling function print");
        return "mistake occurred while calling function print";
    }**/
    //char *input=Walley_Eval_With_Variable(input_str);
    //char *output=malloc(sizeof(char)*(int)strlen(input));
    //strcat(output,input);
    //strcat(output,"\n");
    //return output;
    return println_from_var_file("__walley__.wy",input_str);
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
    //printf("%s\n",input_str);
    //input_str[(int)strlen(input_str)-1]=' ';
    //printf("%s\n",input_str);
    char *temp=malloc(sizeof(char)*((int)strlen(input_str)+1));
    int a=0;
    for(a=0;a<(int)strlen(input_str);a++){
        temp[a]=input_str[a];
    }
    temp[(int)strlen(input_str)]=0;
    //strcat(temp,input_str);
    //strcat(temp," ");
    input_str=temp;
    
    //printf("Temp is |%s|\n",input_str);
    //printf("Temp Length is %d\n",(int)strlen(input_str));
    
    char *first_str;
    char *second_str;
    int index=indexOfJudgeSignFromIndex(input_str,0);
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
    first_str=Walley_Eval_With_Variable_From_File("__walley__.wy",first_str);
    second_str=Walley_Eval_With_Variable_From_File("__walley__.wy",second_str);
    //#############################################################################
   //// printf("First %s\nSecond %s\nJudge Sign %s\n",first_str,second_str,judge_sign);
    double num1=atof(first_str);
    double num2=atof(second_str);
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
        
        
        
    } else {
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
    input_str=removeAheadSpace(input_str);
    input_str=removeBackSpace(input_str);
    bool pass=TRUE;
    char *temp=malloc(sizeof(char)*(5+(int)strlen(input_str)));
    strcat(temp,"and ");
    strcat(temp,input_str);
    strcat(temp," ");
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
   //// printf("++ Pass is ----> %d\n",pass);
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
        char *temp_temp=malloc(sizeof(char)*((int)strlen(input_str)+(int)strlen(result_str)-(int)strlen(temp)-2));
        strcat(temp_temp,substr(input_str,0,left));
        strcat(temp_temp,result_str);
        strcat(temp_temp,substr(input_str,right+1,(int)strlen(input_str)));
        input_str=temp_temp;
    }
    if(find(input_str,"  ")!=-1){
        input_str=replace(input_str,"  "," ");
    }
   //// printf("@@@@@@@@AAAAA  input_str is %s\n",input_str);
    return judgeWithAndAndOr(input_str);
}
/*Support variable
 */
bool judgeWithAndAndOrWithParenthesisAndVariables(char *input_str, char *var_in_file_name){
    // I did not consider the situation when and or or is in string
    // I don not know what happened, but sometimes " space " can not be found
    if(find(input_str," and ")!=-1){
        input_str=replace(input_str," and ","+++++");
    }
    if(find(input_str," or ")!=-1){
        input_str=replace(input_str," or ","----");
    }
    //printf("%s\n",input_str);
    input_str=substitueExistedVarValueFromFile(input_str,var_in_file_name);
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
 * eg clearTextInFile("__walley_file__.wy")
 * will clean all of the text in that file
 */
void clearTextInFile(char *file_name){
    FILE *fp=fopen(file_name,"w");
    if(fp==NULL){
        printf("Mistake occurred while calling function clearTextInFile\nCan not clean");
    } else {
        fputs("#Clean File Successfully\n",fp);
        fclose(fp);
    }   
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
/*
 * this function is for special function in walley_core
 * eg x="Hello", x.find("Hello",1)
 * numOfParameters(" "Hello", 1")=2
 */
int numOfParameters(char *func_param){
    int i=0;
    int num=1;
    for(i=0;i<(int)strlen(func_param);i++){
        if(func_param[i]==',' && charIsInString(func_param,i)==FALSE){
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
char *functionOrClassAddAheadName(char *import_file_name, char *as_name) {
   //// printf("#### functionAddAheadName ####\n");
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
            strcat(temp, func_name);
            strcat(temp, "(");
            temp[(int) strlen(temp)] = 0;

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

char *getOneFunctionFromFileAndFormatItgetOneFunctionFromFile(char *import_file_name, char *func_name, char *as_name) {
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
