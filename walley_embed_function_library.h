/* 
 * File:   walley_embed_function_library.h
 * Author: shd101wyy
 *
 * Created on September 6, 2012, 3:08 PM
 */

//#include "walley_gui.h"
#include "walley_table.h"
//     1,2,3,4 index 0----->1
//     This function now has some problems......
//     I did not consider the , in list or ......
char* getParamAccordingToIndex(char *params_str, int index){
    params_str=append(params_str, ",");
    //1,2,3,4,
    int index_of_comma=0;
    while (index>0) {
        index_of_comma=find_from_index_not_in_str_list_dict(params_str, ",", index_of_comma+1);
        index--;
    }
    int index_of_final=find_from_index_not_in_str_list_dict(params_str, ",", index_of_comma+1);
    if (index_of_comma==0) {
        index_of_comma=-1;
    }
    char *output=substr(params_str, index_of_comma+1, index_of_final);
    output=trim(output);
    
    // printf("params_ste %s, index %d, output %s\n",params_str,index,output);
    return output;
}


int time_seed=0;
/*
 *function : to_int("'123'")----->"123" 
 *           to_int("12.3") ----->"12"
 *     
 */
char *to_int(char *input_str){
    input_str=removeAheadSpace(removeBackSpace(input_str));
    // string to int
    if(strcmp("string",variableValueType(input_str))==0) {
        input_str=substr(input_str,1,(int)strlen(input_str)-1);
        if(find(input_str,".")!=-1){
            input_str=substr(input_str,0,find(input_str,"."));
        }
        return input_str;
    }
    // double to int
    else if(strcmp("double",variableValueType(input_str))==0){
        input_str=substr(input_str,0,find(input_str,"."));
        return input_str;
    }
    // int to int
    else if (strcmp("int",variableValueType(input_str))==0){
        return input_str;
    }
    
    else {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Mistakes occurred while calling function to_int\nThe input_str %s is not string\nThis function only support string to int now\n",input_str);
        exit(1);
    }
}
/*
 *function : to_double("'123'")----->"123.0" 
 *function : to_double("'12.3'")----->"12.3" 
 */
char *to_double(char *input_str){
    input_str=trim(input_str);
    // string to double
    if (strcmp("string", variableValueType(input_str)) == 0) {
        input_str = substr(input_str, 1, (int) strlen(input_str) - 1);
        char *temp;
        if (find(input_str, ".") == -1) {
            temp = (char*)malloc(sizeof (char) *((int) strlen(input_str) + 3));
            strcpy(temp, input_str);
            strcat(temp, ".0");
            temp[(int) strlen(input_str) + 2] = 0;
            input_str = temp;
        }
        return input_str;
    }
        // int to double
    else if (strcmp("int", variableValueType(input_str)) == 0) {
        char *temp;
        temp = (char*)malloc(sizeof (char) *((int) strlen(input_str) + 3));
        strcpy(temp, input_str);
        strcat(temp, ".0");
        temp[(int) strlen(input_str) + 2] = 0;
        input_str = temp;
        return input_str;
    }
        // double to double
    else if (strcmp("double", variableValueType(input_str)) == 0) {
        return input_str;
    }
    
    else {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Mistakes occurred while calling function to_double\nThe input_str %s is not string\nThis function only support string to int now\n",input_str);
        exit(1);
    }
}
/*
 * function : to_num("'123'")------>123
 * function : to_num("123")------>123
 */
char *to_num(char *input_str){
    return to_double(input_str);
}

//   0.5---->1/2  d(1/2)---->0.5
char *to_fraction(char *input_str){
    return eval_for_fraction_with_alpha(input_str);
}


//   1/2---->0.5  f(0.5)---->1/2
char *to_decimal(char *input_str){
    return eval_for_decimal_with_alpha(input_str);
}



char *to_nstr(char *input_str){
   //// printf("#### to_nstr ####\n");
    if (strcmp("string", variableValueType(input_str)) == 0) {
        return toCString(input_str);
    }
    else {
        return input_str;
    }
}
/*
 *function : to_string("'123'")----->'123' string --> string just return
 *function : to_string("123")----->"12.3" 
 */
char *to_string(char *input_str){
    input_str=removeAheadSpace(removeBackSpace(input_str));
    if(strcmp("string",variableValueType(input_str))==0){
        return input_str;
    } else {
        char *temp="";
        temp=append("'",input_str);
        temp=append(temp,"'");        
        return temp;
    }
}

//Mon Dec 31 03:00:06 2012
char *simple_time(){
    time_t t;
    time(&t);
    //printf("%s",ctime(&t));
    char *temp=ctime(&t);
    temp=replace(temp,"\n","");
    return toString(temp);
}

char *walley_system(char *input_str){
    input_str=toCString(input_str);
    printf("\n\n####################################\n\n");
    system(input_str);
    printf("\n\n####################################\n\n");
    return "None";
}


// new code on Jan 3 2013
char *walley_system_return_str(char *cmd){
    FILE* pipe;
    #ifdef _WIN32
    pipe= _popen(cmd, "r");
    #else
    pipe= popen(cmd, "r");
    #endif

    
    if (!pipe) return "ERROR";
    char buffer[128];
    char result[1000] = "";
    while(fgets(buffer, 128, pipe) != NULL){
        strcat(result,buffer);
    }
    #ifdef _WIN32
    _pclose(pipe);
    #else
    pclose(pipe);
    #endif

    char *output=(char*)malloc(sizeof(char)*((int)strlen(result)+1));
    
    int i=0;
    for(;i<(int)strlen(result);i++){
        output[i]=result[i];
    }
    output[(int)strlen(result)]=0;
    output=toString(output);
    return output;
}


char *walley_is_fraction_mode(){
    bool fraction_mode=atoi(Var_getValueOfVar(VAR_settings, "fraction_mode"));
    if (fraction_mode==TRUE) {
        return "TRUE";
    }
    else{
        return "FALSE";
    }
}
/*
 range(3)--->[0,1,2]
 range(1,5)-->[1,2,3,4]
 range(0,2,0.5)-->[0,0.5,1,1.5]
 
 */
char *math_range(char *input_str){
    if (strcmp(input_str, "0")==0) {
        return "[0]";
    }
    
    int num_of_param=numOfParameters(input_str);
    if (num_of_param==1) {
        //char *output="[";
        char *output;
        d_string(&output, "[");
        int num=atoi(input_str);
        
        
        if (num<0) {
            printf("%s\n",append("range(", append(input_str, ")")));
            printf("      ^\n");
            printf("Error.. Num must be larger or equal than 0\n");
            exit(0);
        }
        
        int i=0;
        for (; i<num; i++) {
            //output=append(output, intToCString(i));
            //output=append(output, ",");
            d_strcat(&output, intToCString(i));
            d_strcat(&output, ",");
        }
        //output=substr(output, 0, (int)strlen(output)-1);
        //output=append(output, "]");
        output[(int)strlen(output)-1]=']';
        return output;
    }
    else if(num_of_param==2){
        char *output="[";
        int num1=atoi(getParamAccordingToIndex(input_str,0));
        int num2=atoi(getParamAccordingToIndex(input_str,1));
        
        if (num2<num1) {
            printf("%s\n",append("range(", append(input_str, ")")));
            printf("      ^\n");
            printf("Error.. 2nd num must be larget than 1st num\n");
            exit(0);
        }
        
        int i=0;
        for (i=num1; i<num2; i++) {
            output=append(output, intToCString(i));
            output=append(output, ",");
        }
        output=substr(output, 0, (int)strlen(output)-1);
        output=append(output, "]");
        return output;
    }
    else if(num_of_param==3){
        char *output="[";
        double num1=atof(getParamAccordingToIndex(input_str,0));
        double num2=atof(getParamAccordingToIndex(input_str,1));
        double num3=atof(getParamAccordingToIndex(input_str,2));
        if (num2<num1) {
            printf("%s\n",append("range(", append(input_str, ")")));
            printf("      ^\n");
            printf("Error.. 2nd num must be larget than 1st num\n");
            exit(0);
        }
        if (num3<=0) {
            printf("%s\n",append("range(", append(input_str, ")")));
            printf("Error, the final num must >0\n");
            exit(0);
        }
        
        double i=0;
        for (i=num1; i<num2; i=i+num3) {
            output=append(output, numToCString(i));
            output=append(output, ",");
        }
        output=substr(output, 0, (int)strlen(output)-1);
        output=append(output, "]");
        return output;
    }

    else{
        printf("Error.. Function range can only be the format like\nrange(2)-->[0,1] or range(1,3)-->[1,2]");
        exit(0);
    }
}

char *math_sin(char *input_str){
    long double num=atof(input_str);
    num=sin(num);
    char output[100];
    sprintf(output,"%Lf",num);
    char *output_str=(char*)malloc(sizeof(char)*((int)strlen(output)+1));
    int i=0;
    for(i=0;i<(int)strlen(output);i++){
        output_str[i]=output[i];
    }
    output_str[(int)strlen(output)]=0;
    return output_str;
}
char *math_cos(char *input_str){
    double num=atof(input_str);
    num=cos(num);
    char output[100];
    sprintf(output,"%f",num);
    char *output_str=(char*)malloc(sizeof(char)*((int)strlen(output)+1));
    int i=0;
    for(i=0;i<(int)strlen(output);i++){
        output_str[i]=output[i];
    }
    output_str[(int)strlen(output)]=0;
    return output_str;
}

char *math_sec(char *input_str){
    double num=atof(input_str);
    num=1/cos(num);
    char output[100];
    sprintf(output,"%f",num);
    char *output_str=(char*)malloc(sizeof(char)*((int)strlen(output)+1));
    int i=0;
    for(i=0;i<(int)strlen(output);i++){
        output_str[i]=output[i];
    }
    output_str[(int)strlen(output)]=0;
    return output_str;
}

char *math_csc(char *input_str){
    double num=atof(input_str);
    num=1/sin(num);
    char output[100];
    sprintf(output,"%f",num);
    char *output_str=(char*)malloc(sizeof(char)*((int)strlen(output)+1));
    int i=0;
    for(i=0;i<(int)strlen(output);i++){
        output_str[i]=output[i];
    }
    output_str[(int)strlen(output)]=0;
    return output_str;
}



char *math_tan(char *input_str){
    
    double num=atof(input_str);
    num=tan(num);
    char output[100];
    sprintf(output,"%f",num);
    char *output_str=(char*)malloc(sizeof(char)*(1+(int)strlen(output)));
    int i=0;
    for(i=0;i<(int)strlen(output);i++){
        output_str[i]=output[i];
    }
    output_str[(int)strlen(output)]=0;
    return output_str;
}

char *math_cot(char *input_str){
    
    double num=atof(input_str);
    num=1/tan(num);
    char output[100];
    sprintf(output,"%f",num);
    char *output_str=(char*)malloc(sizeof(char)*((int)strlen(output)+1));
    int i=0;
    for(i=0;i<(int)strlen(output);i++){
        output_str[i]=output[i];
    }
    output_str[(int)strlen(output)]=0;

    return output_str;
}


char *math_exp(char *input_str){
    double num=atof(input_str);
    num=exp(num);
    char output[100];
    sprintf(output,"%f",num);
    char *output_str=(char*)malloc(sizeof(char)*((int)strlen(output)+1));
    int i=0;
    for(i=0;i<(int)strlen(output);i++){
        output_str[i]=output[i];
    }
    output_str[(int)strlen(output)]=0;
    return output_str;
}

char *math_log10(char *input_str) {
    double num = atof(input_str);
    num = log10(num);
    char output[100];
    sprintf(output, "%f", num);
    char *output_str = (char*)malloc(sizeof (char) *((int) strlen(output)+1));
    int i = 0;
    for (i = 0; i < (int) strlen(output); i++) {
        output_str[i] = output[i];
    }
    output_str[(int)strlen(output)]=0;
    return output_str;
}


/*
 * x=input() ---> input 10, then x is 10
 * x=input("--->") ---> print ---> at first and then input, input 10, get x = 10
 * 
 */
char *var_input(char *input_str) {
    if (stringIsEmpty(input_str)) {
        char *output = (char*)malloc(sizeof (char) *(10000));
        gets(output);
        //scanf("%s",output);
        //return toString(output);
        return append("\"", append(output, "\""));
        //return output;
    }
    else{
        input_str=toCString(input_str);
        input_str=replace(input_str, "\\n", "\n");
        printf("%s",input_str);
        char *output = (char*)malloc(sizeof (char) *(10000));
        gets(output);
        //scanf("%s",output);
        return append("\"", append(output, "\""));
        //printf("return output---> %s\n",toString(output));
        //return toString(output);
        //return output;
    }
}

/*
 * var_value_type("1")---->"int"
 */
char *var_value_type(char *input_str){
    char *type=(char*)malloc(sizeof(char)*(3+(int)strlen(variableValueType(input_str))));
    strcpy(type,"'");
    strcat(type,variableValueType(input_str));
    strcat(type,"'");
    type[2+(int)strlen(variableValueType(input_str))]=0;
    return type;
}

/*######################### Function for String ##################################################################################*/
//#################################################################################################################################
/*
 * x="Hello"  x.find("H").     x is user, "H" is find_str
 * eg string_find("Hello","H")----->0
 */
char *string_find(char *user,char* find_str){
   //// printf("#### x.find('hi') ####\n");
    user=substr(user,1,(int)strlen(user)-1);
    if(strcmp(variableValueType(find_str),"string")==0)
        find_str=substr(find_str,1,(int)strlen(find_str)-1);
    int index=find(user,find_str);
    
    //char temp[100];
    //sprintf(temp,"%d",index);
    char *temp=intToCString(index);
    
    char *output=(char*)malloc(sizeof(char)*((int)strlen(temp)+1));
    int i=0;
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    output[(int)strlen(temp)]=0;
    return output;
}
/* x="Hello", x.find("Hello",1) now " "Hello", 1 " is parameter
 * x.find("e",[1,3]) find from index 1 to 3 (3 is not included)
 * eg string_find_from_index("'Hello'","'l',2")
 */
char *string_find_from_index(char *user, char *func_param){
   //// printf("#### eg x.find('hi',2) ####\n");
    user=substr(user,1,(int)strlen(user)-1);
    char *find_str=substr(func_param,0,find_not_in_string(func_param,","));
    find_str=removeAheadSpace(removeBackSpace(find_str));
    find_str=substr(find_str,1,(int)strlen(find_str)-1);
    
    char *from_index=substr(func_param,find_not_in_string(func_param,",")+1,(int)strlen(func_param));
    from_index=removeAheadSpace(removeBackSpace(from_index));
    
    // find from index to index
    if (strcmp(variableValueType(from_index), "list")==0) {
        int num_of_value=valueNumOfList(from_index);
        if (num_of_value>2) {
            printf("@@ |%s|\n",CURRENT_INPUT_STR);

            printf("Mistake occurred whiling calling function string_find_from_index\n%s is not a correct list, only two or one number are allowed\n",from_index);
            exit(0);
        }
        //x.find("e",[1])
        else if(num_of_value==1){
            int from=atoi(valueOfListAtIndex(from_index, 0));
            int index=find_from_index(user,find_str,from);

            //char temp[100];
            //sprintf(temp,"%d",index);
            char *temp=intToCString(index);
            
            char *output=(char*)malloc(sizeof(char)*((int)strlen(temp)+1));
            int i=0;
            for(i=0;i<(int)strlen(temp);i++){
                output[i]=temp[i];
            }
            output[(int)strlen(temp)]=0;
            return output;
        }
        // x.find("e",[0,3]
        else {
            int from=atoi(valueOfListAtIndex(from_index, 0));
            int to=atoi(valueOfListAtIndex(from_index, 1));
            int index=find_from_index_to_index(user, find_str, from, to);
            return intToCString(index);
        }
        
    }
    
    // find from index
    else {
    int from=atoi(from_index);
    int index=find_from_index(user,find_str,from);

    //char temp[100];
    //sprintf(temp,"%d",index);
        char *temp=intToCString(index);
        
    char *output=(char*)malloc(sizeof(char)*((int)strlen(temp)+1));
    int i=0;
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
        output[(int)strlen(temp)]=0;
    return output;
    }
}
/* x="Hello", x.replace("e","a") ----> "Hallo"
 * eg string_replace("'Hello'","llo","a")---->Hao
 */
char *string_replace(char *user, char *func_param){
   // printf("#### eg x.replace('hi','i') ####\n");
    user=substr(user,1,(int)strlen(user)-1);
    char *replace_str=substr(func_param,0,find_not_in_string(func_param,","));
    replace_str=removeAheadSpace(removeBackSpace(replace_str));
    replace_str=substr(replace_str,1,(int)strlen(replace_str)-1);
    char *to_str=substr(func_param,find_not_in_string(func_param,",")+1,(int)strlen(func_param));
    to_str=removeAheadSpace(removeBackSpace(to_str));
    to_str=substr(to_str,1,(int)strlen(to_str)-1);
    char *output=replace(user,replace_str,to_str);
    char *output2=toString(output);
    return output2;  
}

char *string_replace_from_index(char *user, char *func_param){
    user=substr(user,1,(int)strlen(user)-1);
    char *replace_str=getParamAccordingToIndex(func_param, 0);
    replace_str=toCString(replace_str);
    char *to_str=getParamAccordingToIndex(func_param, 1);
    to_str=toCString(to_str);
    char *from_index=getParamAccordingToIndex(func_param, 2);
    //x=x.replace("e","l",[1,2])  or x=x.replace("e","l",[1])
    if (strcmp(variableValueType(from_index), "list")==0) {
        int num_of_value=valueNumOfList(from_index);
        if (num_of_value>2) {
            printf("@@ |%s|\n",CURRENT_INPUT_STR);

            printf("Mistake occurred whiling calling function string_replace_from_index\n%s is not a correct list, only two or one number are allowed\n",from_index);
            exit(0);
        }
        //x.find("e",[1])
        else if(num_of_value==1){
            int from=atoi(valueOfListAtIndex(from_index, 0));
            char *output=replace_from_index_to_index(user, replace_str, to_str, from, (int)strlen(user));
            return toString(output);
        }
        // x.find("e",[0,3]
        else {
            int from=atoi(valueOfListAtIndex(from_index, 0));
            int to=atoi(valueOfListAtIndex(from_index, 1));
            char *output=replace_from_index_to_index(user, replace_str, to_str, from, to);
            return toString(output);
        }
    }
    //x=x.replace("e","l",2)
    else{
        int from=atoi(from_index);
       // printf("user %s replace_str %s with_str %s from %d\n",user,replace_str,to_str,from);
        char *output=replace_from_index_to_index(user, replace_str, to_str, from, (int)strlen(user));
       // printf("output is %s\n",output);
        return toString(output);
    }
}

/*
 * x="Hello"  x.count("l")-------->2
 * string_count_str("'Hello'","'l'")
 */
char *string_count_str(char *user, char *func_param){
    user=substr(user,1,(int)strlen(user)-1);
    func_param=substr(func_param,1,(int)strlen(func_param)-1);
    int num=count_str(user,func_param);
    
    //char temp[100];
    //sprintf(temp,"%d",num);
    char *temp=intToCString(num);
    
    char *output=(char*)malloc(sizeof(char)*((int)strlen(temp)+1));
    int i=0;
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    output[(int)strlen(temp)]=0;
    return output;
}
/*
 * x="Hello"  x.length()----->5
 * string_length("Hello")
 */
char *string_length(char *user){
   //// printf("#### string_length ####\n");
    user=toCString(user);
    int length=(int)strlen(user);
    //length=length-2; // delete '' and ""
    
    //char temp[100];
    //sprintf(temp,"%d",length);
    char *temp=intToCString(length);
    
    char *output=(char*)malloc(sizeof(char)*((int)strlen(temp)+1));
    int i=0;
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    output[(int)strlen(temp)]=0;
   //// printf("output %s\n",output);
    return output;
}

char *string_isdigit(char *user){
    user=toCString(user);
    bool is_digit=stringIsDigit(user);
    if (is_digit==TRUE) {
        return "TRUE";
    }
    else{
        return "FALSE";
    }
}

char *string_isalpha(char *user){
    user=toCString(user);
    bool is_alpha=stringIsAlpha(user);
    if (is_alpha==TRUE){
        return "TRUE";
    }
    else{
        return "FALSE";
    }
}

char *string_toupper(char *user){
    user=toCString(user);
    user=stringToUpperCase(user);
    return toString(user);
}

char *string_tolower(char *user){
   //// printf("#### string_tolower ####\n---->%s\n",user);
    user=toCString(user);
    user=stringToLowerCase(user);
    return toString(user);
}

char *string_isupper(char *user){
    user=toCString(user);
    int i=0;
    int length=(int)strlen(user);
    bool isupper=TRUE;
    for (i=0; i<length; i++) {
        char temp=toupper(user[i]);
        if (temp!=user[i]) {
            isupper=FALSE;
            break;
        }
    }
    if (isupper==TRUE) {
        return "TRUE";
    }
    else{
        return "FALSE";
    }
}

char *string_islower(char *user){
    user=toCString(user);
    int i=0;
    int length=(int)strlen(user);
    bool islower=TRUE;
    for (i=0; i<length; i++) {
        char temp=tolower(user[i]);
        if (temp!=user[i]) {
            islower=FALSE;
            break;
        }
    }
    if (islower==TRUE) {
        return "TRUE";
    }
    else{
        return "FALSE";
    }

}


/*
 * x="  Hello "  x.trim()---->"Hello"
 * string_trim("'Hello'")
 */
char *string_trim(char *user){
    user=trim(user);
    user=substr(user,1,(int)strlen(user)-1);
    char *output=trim(user);
    char *output2=(char*)malloc(sizeof(char)*((int)strlen(output)+3));
    strcpy(output2,"'");
    strcat(output2,output);
    strcat(output2,"'");
    output2[(int)strlen(output)+2]=0;
    return output2;  
}

/*
 * x="Hello,Hi"  x.split(",")-------->["Hello","Hi"];
 * string_count_str("'Hello,Hi'","','")
 */
char *string_split(char *user, char *func_param){
    user=toCString(user);           //"Hello,Hi"
    user=toCString(user);           // Hello,Hi
    func_param=toCString(func_param);//","
    func_param=toCString(func_param);//,
    char *return_list="[]";
    if (find_not_in_string(user,func_param)==-1) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Mistake occurred whiling calling function string_split, %s is not found in %s\n",func_param,user);
        exit(0);
    }
    int begin=0;
    int end=find_not_in_string(user,func_param);
    while (TRUE) {
        char *append_element=substr(user,begin,end);
        return_list=listAppendOneElement(return_list, toString(append_element));
        begin=end+(int)strlen(func_param);
        if (begin>=(int)strlen(user)) {
            break;
        }
        end=find_from_index_not_in_string(user, func_param, begin+1);
        if (end==-1) {
            end=(int)strlen(user);
            append_element=substr(user, begin, end);
            return_list=listAppendOneElement(return_list, toString(append_element));
            break;
        }
    }
    return return_list;
}

// x="Hello"
// x=x.reverse()--> "olleH"
char *string_reverse(char *user){
    user=toCString(user);
    user=stringReverse(user);
    return toString(user);
}



/*#################### Function for List ############################*/

/*
 * eg x=[1,2,3] x.append(5)---->x=[1,2,3,5]
 * list_append("[1,2,3]","4"]
 */
char *list_append(char *user, char *func_param){
   //// printf("#### list_append #### x.append(4) ####\n");
    char *output=listAppendOneElement(user,func_param);
   //// printf("#### list is |%s| ####\n",output);
    return output;
}
/*
 * eg x=[1,2,3] x.remove_at_index(0)------->x=[2,3]
 *    x=[1,[1,2],4] x.remove_at_index(1)------->x=[1,4]
 * list_remove_at_index("[1,2,3]","0")------->[2,3]
 */
char *list_remove_at_index(char *user, char *func_param){
    //printf("#### list_remove_at_index #### x.remove_at_index([0])\n");
    return listRemoveOneElementAtOneIndex(user,func_param);
}
/*
 * range(0,10)------->[0,1,2,3,4,5,6,7,8,9]
 */
//char *list_range(char *function_param){
//
//}

/*
 * list_length
 * eg: x=[1,2,[3,4],5].    x.length()=4  x[2].length()=2
 */
char *list_length(char *user){
    int num=valueNumOfList(user);

    //   char temp[100];
    //   sprintf(temp,"%d",num);
    char *temp=intToCString(num);
    
    char *output=(char*)malloc(sizeof(char)*((int)strlen(temp)+1));
    int i=0;
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    output[(int)strlen(temp)]=0;
    return output;
}
/*
 * list_remove_element
 * x=[1,2,3] x.remove_element(1)--->[2,3]
 * x=[1,2,3,1] x.remove_element(1)--->[2,3]
 * x=[1,[1],2] x.remove_element(1)--->[[1],2]
 */
char *list_remove_element(char *user, char *function_param){
    return listRemoveOneElementByValue(user,function_param);
}

/*
 * x=[1,1,2,3] x.count(1)---->2
 * x=[1,2,[1],2] x.count(1)---->1
 */
char *list_count(char *user, char *function_param){
    user=toCString(user);
    function_param=toCString(function_param);
    user=trim(user);
    user=substr(user, 1, (int)strlen(user)-1);
    int num=count_str_not_in_str_list_dict_parenthesis(user, function_param);
    
    //char temp[1000]="";
    //sprintf(temp, "%d",num);
    char *temp=intToCString(num);
    
    char *output=append("", temp);
    return output;
}

/*################## Function for Dictionary ############################*/
/*
 * x={a:1,b:2}  x.key()=[a.b]
 * dict_key("{a:1,b:2}")-------->"[a,b]"
 * 
 */
char *dict_key(char *user){
    return keyOfDictionaryAsList(user);
}

//################## Function for File Operation ###########################
// file_readline("'math.wy'") and return list form of string
char *file_readlines(char *walley_file_name){
   // printf("#### FILE_READLINES ####\n");
    walley_file_name=toCString(walley_file_name);
    walley_file_name=trim(walley_file_name);
    //printf("#### file_readlines ####\n");
   // printf("walley_file_name %s\n",walley_file_name);
    FILE *fp=fopen(walley_file_name,"r");
    if(fp==NULL){
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Mistake occurred whiling calling function file_readlines\nDoes not find %s\n",walley_file_name);
        fclose(fp);
        exit(0);
    }
    else{
        //char output[100000]="";
        //strcat(output,"[");
        char arr[100000] = "";
        char *output=append("","[");
        while (fgets(arr, 100000, fp) != NULL) {
            char *temp3=append("", arr);
            temp3=trim(temp3);
            temp3=removeNFromBack(temp3);
            temp3=replace(temp3, "\"", "\\\"");
            output=append(output, "\"");
            output=append(output, temp3);
            output=append(output, "\",");
        }

        fclose(fp);
        output[(int)strlen(output)-1]=']';
        char *output2=append("", output);
        return output2;
    }
}
// file_writelines("'walley.wy','str to file'")
char *file_writelines(char *file_name,char *lines){
   // printf("#### file_writelines ####\n");
   // printf("-- %s -- %s --\n",file_name,lines);
    //printf("parameters is %s\n",params);
    //params=trim(params);
    //char *file_name=substr(params,0,find_not_in_string(params,","));
    //char *lines=substr(params,find_not_in_string(params,",")+1,(int)strlen(params));
    file_name=toCString(file_name);
    FILE *fp=fopen(file_name,"w");
    if(fp==NULL){
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Mistake occurred whiling calling function file_writelines\nNo file %s found",file_name);
        fclose(fp);
        exit(1);
    }
    else{
        fputs(lines,fp);
        fclose(fp);
        return "None";
    }
}

char *file_removefile(char *file_name){
    file_name=trim(file_name);
    file_name=toCString(file_name);
    remove(file_name);
    return "None";
}

char *file_createfile(char *file_name){
   //// printf("#### file_createfile ####\n");
    file_name=trim(file_name);
    file_name=toCString(file_name);
    FILE *fp=fopen(file_name,"w");
    if(fp==NULL){
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Failed to create %s\n",file_name);
        exit(0);
    }
    //else {
    //    fputs("#~",fp);
    //}
    fclose(fp);
    return "None";
}

char *file_addstrtofile(char *params){
    //// printf("#### file_createfile ####\n");
    char *file_name=getParamAccordingToIndex(params, 0);
    file_name=trim(file_name);
    file_name=toCString(file_name);
    char *add_str=getParamAccordingToIndex(params, 1);
    add_str=toCString(add_str);
    writeStringToFile(file_name, add_str);
    return "None";
}



char *file_readFileNameInDirectory(char *directory_name){
    directory_name=toCString(directory_name);
    DIR *dir;
    struct dirent *file;
    dir=opendir(directory_name);
    char *output="[";
    if (dir!=NULL) {
        while ((file=readdir(dir))) {
            //puts(file->d_name);
            output=append(output, "\"");
            output=append(output, file->d_name);
            output=append(output, "\",");
        }
        closedir(dir);

        output[(int)strlen(output)-1]=']';
        return output;
    }
    else{
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Mistake occurred while calling function file_readFileNameInDirectory\nNo directory %s found\n",directory_name);
        exit(0);
    }

}

// This function is used for importing modules like python
// eg getModulePathFromDirectory("test.test2.ex2")
/*
 |-- test2.wyp--ex2.wy
 test.wyp-
 |__
 */
char *getModulePathFromDirectory(char *name_of_file_to_run,char *directory){
    //char *file_in_directory=file_readFileNameInDirectory("\"./\"");
    //printf("file_in_directory %s\n",file_in_directory);
    
    int begin=0;
    int index_of_dot=-1;
    //char *output="./";
    char *output=directory;
    //char *current_path="./";
    char *current_path=directory;
    while (TRUE) {
        index_of_dot=find_from_index(name_of_file_to_run, ".", begin);
        
        // check whether .wyp exist.
        // is exist, then it is package
        // else, it is module file.
        
        if (index_of_dot==-1) {
            char *temp_module=substr(name_of_file_to_run, begin, (int)strlen(name_of_file_to_run));
            char *temp_package=append(temp_module, ".wyp");
            if (find(file_readFileNameInDirectory(current_path), toString(temp_package))!=-1) {
                output=append(output,temp_package);
            }
            else{
                output=append(output, substr(name_of_file_to_run, begin, (int)strlen(name_of_file_to_run)));
                output=append(output, ".wy");
            }
            break;
        }
        
        char *temp_module=substr(name_of_file_to_run, begin, index_of_dot);
        char *temp_package=append(temp_module, ".wyp");
        if (find(file_readFileNameInDirectory(current_path), toString(temp_package))!=-1) {
            output=append(output, temp_package);
            output=append(output, "/");
            current_path=output;
        }
        else{
            //output=append(output, substr(name_of_file_to_run, begin, (int)strlen(name_of_file_to_run)));
            output=append(output,append(temp_module, ".wy"));
            break;
        }
        
        begin=index_of_dot+1;
    }
    
    
    return output;
}
//################## System ###############################################*/
char *walley_run_str(char *input_str);
char *walley_quit_program(){
    exit(0);
}
char *walley_show_var(struct VAR *struct_var){
    int row=0;
    
    int length=0;
    if (strcmp((struct_var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((struct_var)->var_value);
    }

    while (row<length) {
        char *var_name=struct_var[row].var_name;
        if (
            find(var_name, "__size_of_array__")==0
            ) {
            row++;
            continue;
        }else {

        
        printf("%s:%s:%s:\n",struct_var[row].var_name,struct_var[row].var_value,struct_var[row].var_type);
        row++;
        }
    }    return "None";
}

char *walley_get_current_terminal_commands(){
    int i=0;
    char *output="[";
    for (; i<ARGC; i++) {
        output=append(output, toString(ARGV[i]));
        if (i==ARGC-1) {
            output=append(output, "]");
        }
        else{
            output=append(output, ",");
        }
    }
    return output;
}

char *walley_random(){
    //printf("enter walley_random\n");
    srand( (unsigned)time(0));
    time_seed++;
    if (time_seed==100) {
        time_seed=0;
    }
    int i=0;
    double return_value_num;
    while (i<=time_seed) {
        return_value_num=rand()/(double)(RAND_MAX);
        //printf("%f\n",return_value_num);
        i++;
    }
    char *return_value=numToCString(return_value_num);
    
    return return_value;
}

/*
//################### For GUI ##############################################
char *walley_init_window(char *input_str){ //int width, int height, int x, int y, char *windows_name)
    char *width=getParamAccordingToIndex(input_str, 0);
    char *height=getParamAccordingToIndex(input_str, 1);
    char *x=getParamAccordingToIndex(input_str, 2);
    char *y=getParamAccordingToIndex(input_str, 3);
    char *window_name=getParamAccordingToIndex(input_str, 4);
    Walley3D_initWindows(atoi(width),atoi(height), atoi(x), atoi(y), window_name);
    return "None";
}


char *walley_set_projection(char *input_str){//double fovy, double aspect , double zNear, double zFar, double w1, double h1){
    char *fovy=getParamAccordingToIndex(input_str, 0);
    char *aspect=getParamAccordingToIndex(input_str, 1);
    char *zNear=getParamAccordingToIndex(input_str, 2);
    char *zFar=getParamAccordingToIndex(input_str, 3);
    char *w1=getParamAccordingToIndex(input_str, 4);
    char *h1=getParamAccordingToIndex(input_str, 5);
    Walley3D_setProjection(atof(fovy), atof(aspect), atof(zNear), atof(zFar), atof(w1), atof(h1));
    return "None";
}

char *walley_set_view(char *input_str){//double x, double y, double z, double look_at_x, double look_at_y, double look_at_z, double head_x, double head_y, double head_z
    
    char *x=getParamAccordingToIndex(input_str, 0);
    char *y=getParamAccordingToIndex(input_str, 1);
    char *z=getParamAccordingToIndex(input_str, 2);
    char *look_at_x=getParamAccordingToIndex(input_str, 3);
    char *look_at_y=getParamAccordingToIndex(input_str, 4);
    char *look_at_z=getParamAccordingToIndex(input_str, 5);
    char *head_x=getParamAccordingToIndex(input_str, 6);
    char *head_y=getParamAccordingToIndex(input_str, 7);
    char *head_z=getParamAccordingToIndex(input_str, 8);
    Walley3D_setView(atof(x), atof(y), atof(z), atof(look_at_x), atof(look_at_y), atof(look_at_z), atof(head_x), atof(head_y), atof(head_z));
    return "None";
}

char *walley_clear_screen(){
    Walley3D_clearScreen();
    return "None";
}

char *walley_set_color(char *input_str){
    char *red=getParamAccordingToIndex(input_str, 0);
    char *green=getParamAccordingToIndex(input_str, 1);
    char *blue=getParamAccordingToIndex(input_str, 2);
    Walley3D_setColor(atof(red), atof(green), atof(blue));
    return "None";
}

char *walley_draw_line(char *input_str){//double x1, double y1, double z1, double x2, double y2, double z2
    char *x1=getParamAccordingToIndex(input_str, 0);
    char *y1=getParamAccordingToIndex(input_str, 1);
    char *z1=getParamAccordingToIndex(input_str, 2);
    char *x2=getParamAccordingToIndex(input_str, 3);
    char *y2=getParamAccordingToIndex(input_str, 4);
    char *z2=getParamAccordingToIndex(input_str, 5);
    Walley3D_drawLine(atof(x1), atof(y1), atof(z1), atof(x2), atof(y2), atof(z2));
    return "None";
}

char *walley_translate(char *input_str){
    char *x=getParamAccordingToIndex(input_str, 0);
    char *y=getParamAccordingToIndex(input_str, 1);
    char *z=getParamAccordingToIndex(input_str, 2);
    Walley3D_translate(atof(x), atof(y), atof(z));
    return "None";
}

char *walley_rotate(char *input_str){
    char *angle=getParamAccordingToIndex(input_str, 0);
    char *x=getParamAccordingToIndex(input_str, 1);
    char *y=getParamAccordingToIndex(input_str, 2);
    char *z=getParamAccordingToIndex(input_str, 3);
    Walley3D_rotate(atof(angle),atof(x), atof(y), atof(z));
    return "None";
}
*/

//################## Special Function Summary #############################*/


char *Walley_Run_Special_Function_From_Var(char *function, struct VAR **struct_var) {
    //################### Special Function #########################################################
    /*
     * eg x="Hello"-----> x.find("He")----->0
     */
    //printf("#### Walley_Run_Special_Function ####\n");
    //// printf("FUNCTION %s, FILE_VAR_NAME %s\n",function,file_var_name);
    char *return_value;
    
    //// printf("Begin to run special function like x=[1,2,3]  x.append(12)\n");
    //// printf("---->Function %s\n---->file_var_name %s\n",function,file_var_name);
    // eg x="Hello"  x.find("Hi")
    // eg x.a=[]  x.a.append(3)  user x.a | func append(3)
    char *user = substr(function, 0, find_from_behind_not_in_str_list_dict_parenthesis(function, ".")); //------> x
    char *user_function = substr(function, find_from_behind_not_in_str_list_dict_parenthesis(function, ".") + 1, (int) strlen(function)); // -------->find("Hi")
    char *user_value; //= getValueFromValueName(file_var_name, user); // ------->x="Hello"
        
    if (Var_Existed(*struct_var, user)==TRUE) {
        user_value = Var_getValueOfVar(*struct_var, user);
    } else {
        user_value=user;
    }
    char *user_function_parameter = substr(user_function, find(user_function, "(") + 1, (int) strlen(removeBackSpace(user_function)) - 1); // ----->"Hi"  which is inside parenthesis

    int num_of_params = numOfParameters(user_function_parameter);
    //// printf("user---->%s\nuser_function---->%s\nuser_value---->%s\nuser_function_parameter %s\n---->num_of_param %d\n",user,user_function,user_value,user_function_parameter,num_of_params);
    // Special function for String
    if (strcmp("string", variableValueType(user_value)) == 0) {
        if (find(user_function, "find(") == 0) {
            if (num_of_params == 1)
                return_value = string_find(user_value, user_function_parameter);
            else if (num_of_params == 2)
                return_value = string_find_from_index(user_value, user_function_parameter);
            else{
                printf("%s\n",function);
                int index_of_dot=find_from_behind_not_in_str_list_dict_parenthesis(function, ".");
                printf("%s^\n",Str_appendSpaceAhead("", index_of_dot));
                printf("Error, find() only needs 2 params\n");
                exit(0);
            }
        } else if (find(user_function, "replace(") == 0) {
            if (num_of_params==2) {
                return_value=string_replace(user_value, user_function_parameter);
            }
            else if(num_of_params==3){
                return_value=string_replace_from_index(user_value, user_function_parameter);
            }
            printf("%s\n",function);
            printf("Error, replace() needs 2 or 3 params\n");
            exit(0);
        } else if (find(user_function, "count(") == 0) {
            return_value = string_count_str(user_value, user_function_parameter);
        } else if (find(user_function, "split(") == 0) {
            return_value = string_split(user_value, user_function_parameter);
        } else if (find(user_function,"length(")==0){
            //// printf("****** %s\n",user_value);
            return_value=string_length(user_value);
        } else if (find(user_function,"trim(")==0){
            return_value=string_trim(user_value);
        } else if (find(user_function,"isdigit(")==0){
            return_value=string_isdigit(user_value);
        } else if (find(user_function,"isalpha(")==0){
            return_value=string_isalpha(user_value);
        } else if (find(user_function,"toupper(")==0){
            return_value=string_toupper(user_value);
        } else if (find(user_function,"tolower(")==0){
            return_value=string_tolower(user_value);
        } else if (find(user_function,"isupper(")==0){
            return_value=string_isupper(user_value);
        } else if (find(user_function,"islower(")==0){
            return_value=string_islower(user_value);
        } else if (find(user_function,"reverse(")==0){
            return_value=string_reverse(user_value);
        } else {
            printf("This Special Function for String eg. x.find('x') is still under development\n");
        }
    }        // Special function for list
    else if (strcmp("list", variableValueType(user_value)) == 0) {
        if (find(user_function, "append(") == 0) {
            //printf("#### FIND APPEND\n");
            //printf("user value %s user_function_parameter %s\n",user_value,user_function_parameter);
            return_value = list_append(user_value, user_function_parameter);
            //changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name, user, return_value);
            Var_changeValueOfVar(struct_var, user, return_value, "list");
            
            //// printf("#### FINISH APPEND ####\n");
        } else if (find(user_function, "remove_at_index(") == 0) {
            return_value = list_remove_at_index(user_value, user_function_parameter);
            Walley_Update_Var_And_Var_Value_To_Var(struct_var, user, return_value);
        } else if (find(user_function, "length(") == 0) {
            return_value = list_length(user_value);
        } else if (find(user_function, "count(") == 0) {
            return_value = list_count(user_value, user_function_parameter);
        } else if (find(user_function,"remove_element(")==0){
            return_value= list_remove_element(user_value,user_function_parameter);
            //changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name, user, return_value);
            //Var_changeValueOfVar(struct_var, user, return_value, "list");
            Walley_Update_Var_And_Var_Value_To_Var(struct_var, user, return_value);

        }
    }        // Special function for dictionary
    else if (strcmp("dictionary", variableValueType(user_value)) == 0) {
        if (find(user_function, "key(") == 0) {
            return_value = dict_key(user_value);
        } else if (find(user_function, "keys(") == 0) {
            return_value = dict_key(user_value);
        }
    }
    else{
        printf("Error\n");
        exit(2);
    }
    //// printf("RETURN VALUE %s\n",return_value);
    return return_value;
}


