/* 
 * File:   walley_string.h
 * Author: shd101wyy
 *
 * Created on August 17, 2012, 12:34 PM
 */
#include <stdio.h>
#include <stdlib.h>
typedef int bool;
#define TRUE 1
#define FALSE 0
#include <string.h>


char* substr(char* input_str, int from_index, int to_index) {
    if (from_index < 0){// || to_index > (int) strlen(input_str)) {
        printf("\nMistake occurred while calling function substr\nPlease Check\n");
        printf("the input_str is %s from_index %d to_index %d\n\n",input_str,from_index,to_index);
        return "\nMistake occurred while calling function substr\nPlease Check\n";
    }
    else if (from_index==to_index){
        //printf("RETURN NONE");
        return "";
    }
    else {
        //printf("\n\nFunction substr:\nThe input_str is %s\nthe from_index is %d\nthe to_index is %d\n", input_str, from_index, to_index);
        if(to_index>(int)strlen(input_str))
            to_index=(int)strlen(input_str);
        int length = to_index - from_index;
        int i;
        char *output = malloc((1+length) * sizeof (char));
        for (i = 0; i < length; i++) {
            //*(output + i) = *(input_str + from_index + i);
            output[i] = input_str[from_index + i];
            //printf("\n%c\n\n",output[i]);
        }
        output[length]=0;
        //printf("The substr is %s\n\n\n", output);
        //printf("\ninput_str is %s\n",input_str);
        //char *output_str = output;
        //return output_str;
        return output;

    }
}

//char *substr(const char *s,int n1,int n2)/*从s中提取下标为n1~n2的字符组成一个新字符串，然后返回这个新串的首地址*/
/*{
  char *sp=malloc(sizeof(char)*(n2-n1+1));
  int i,j=0;
  for (i=n1; i<n2; i++) {
   sp[j++]=s[i];
  }
  sp[j]=0;
  return sp;
}*/

char *append(char *input_str, char *append_str){
    //printf("$$ |%s| $$ |%s|\n",input_str,append_str);
    int length_of_input_str=(int)strlen(input_str);
    int length_of_append_str=(int)strlen(append_str);
    char *temp=malloc(sizeof(char)*(length_of_input_str+length_of_append_str+1));
    int i=0;
    for(i=0;i<length_of_input_str;i++){
        temp[i]=input_str[i];
    }
    for(i=0;i<length_of_append_str;i++){
        temp[i+length_of_input_str]=append_str[i];
    }
    temp[(int)strlen(temp)]=0;
    temp=substr(temp,0,length_of_input_str+length_of_append_str);
    return temp;
}

int find(char *from_str, char *find_str) {
    int index = -1;
    bool find_index = TRUE;
    int i;
    int j;
    
    for (i = 0; i < (int) strlen(from_str); i++) {
        // I add one code here.
        find_index=TRUE;
        if (from_str[i] == find_str[0]) {
            //printf("Find The same\n");
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
    //printf("%d",index);
    return index;
}


int find_from_index_to_index(char *from_str, char *find_str, int from_index, int to_index) {
    if (from_index < 0 || to_index > (int) strlen(from_str)) {
        printf("Mistake occurred which calling function find_from_index_to_index");
        return -1;
    } else {
        int index = -1;
        bool find_index = TRUE;
        int i;
        int j;
        for (i = from_index; i < to_index; i++) {
            find_index = TRUE;
            if (from_str[i] == find_str[0]) {
                for (j = 0; j < (int) strlen(find_str); j++) {
                    if (find_str[j] != from_str[i + j]) {
                        find_index = FALSE;
                        break;
                    }
                }
                if (find_index == TRUE) {
                    //find_index = TRUE;
                    index = i;
                    break;
                }
            }
        }
        return index;
    }
}

int find_from_index(char *from_str, char *find_str, int from_index) {
    if (from_index < 0) {
        printf("Mistake occurred which calling function find_from_index");
        return -1;
    } else {
        int index = -1;
        bool find_index = TRUE;
        int i;
        int j;
        for (i = from_index; i < (int) strlen(from_str); i++) {
            find_index = TRUE;
            if (from_str[i] == find_str[0]) {
                //printf("%c==%c\n",from_str[i],find_str[0]);
                for (j = 0; j < (int) strlen(find_str); j++) {
                    if (find_str[j] != from_str[i + j]) {
                        //printf("%c!=%c\n",find_str[j],from_str[i+j]);
                        find_index = FALSE;
                        break;
                    }
                    //printf("|%c| == |%c| ",find_str[j],from_str[i+j]);
                }
                if (find_index == TRUE) {
                    //find_index = TRUE;
                    //printf("FIND INDEX\n");
                    index = i;
                    break;
                }
            }
        }
        return index;
    }
}

int find_to_index(char *from_str, char *find_str, int to_index) {
    if (to_index > (int) strlen(from_str)) {
        printf("Mistake occurred which calling function find_to_index");
        return -1;
    } else {
        int index = -1;
        bool find_index = TRUE;
        int i;
        int j;
        for (i = 0; i < to_index; i++) {
            find_index = TRUE;
            if (from_str[i] == find_str[0]) {
                for (j = 0; j < (int) strlen(find_str); j++) {
                    if (find_str[j] != from_str[i + j]) {
                        find_index = FALSE;
                        break;
                    }
                }
                if (find_index == TRUE) {
                    //find_index = TRUE;
                    index = i;
                    break;
                }
            }
        }
        return index;
    }
}

/*
char* replace(char* input_str, char* replace_str, char* with_str) {
    int i;
    char *input_str_copy=input_str;
    char output[1000] = "";
    for (i = 0; i < (int) strlen(input_str); i++) {
        if (input_str[i] == replace_str[0]) {
            printf("input_str is %s\ni is %d\ni+(int)strlen(replace_str) is %d\n", input_str, i, i + (int) strlen(replace_str));
            char *temp = substr(input_str_copy, i, i + (int) strlen(replace_str));
            printf("The length of input_str is %d", (int) strlen(input_str));
            printf("Find equal\n");
            printf("Temp is %s\nreplace_str is %s\n", temp, replace_str);
            printf("The length of temp is %d\n", (int) strlen(temp));
            if (strcmp(temp, replace_str) == 0) {
                printf("Find replace_str\n");
                strcat(output, replace_str);
                i = i + (int) strlen(replace_str) - 1;
            } else {
                output[(int) strlen(output)] = input_str[i];
            }
        } else {
            output[(int) strlen(output)] = input_str[i];
        }
    }
    char *output_str = output;
    return output_str;
}*/
char* replace(char* input_str, char* replace_str, char* with_str) {
    //printf("#### replace ####\n");
    int i;
    int j;

    //char *input_str_copy = input_str;
    char output[1000] = "";
    int length_of_input_str=(int)strlen(input_str);
    for (i = 0; i < length_of_input_str; i++) {
        if (input_str[i] == replace_str[0]) {
            bool is_equal = TRUE;
            for (j = 0; j < (int) strlen(replace_str); j++) {
                if (replace_str[j] != input_str[i + j]) {
                    is_equal = FALSE;
                    //printf("\nis_equal=FALSE\n");
                }
            }
            if (is_equal == TRUE) {
                //printf("Find replace_str\n");
                strcat(output, with_str);
                i = i + (int) strlen(replace_str) - 1;
            } else {
                output[(int) strlen(output)] = input_str[i];
            }
        } else {
            output[(int) strlen(output)] = input_str[i];
        }
    }
    //char *output_str = output;
    //printf("Output is %s\n",output);
    int length=(int)strlen(output);
    char *output_str=malloc(sizeof(char)*(int)strlen(output));
    //printf("%% %d %%\n",(int)strlen(output));
    int a=0;
    for(a=0;a<(int)strlen(output);a++){
        output_str[a]=output[a];
    }
    output_str=substr(output_str,0,length);
    return output_str;
}
char* replace_from_index_to_index(char *input_str, char* replace_str, char* with_str, int from_index, int to_index){
    char *ahead;
    char *back;
    char *middle;
    if(from_index!=0)
        ahead=substr(input_str,0,from_index);
    else
        ahead="";
    if(to_index!=(int)strlen(input_str))
        back=substr(input_str,to_index,(int)strlen(input_str));
    else
        back="";
    middle=substr(input_str,from_index,to_index);
    middle=replace(middle,replace_str,with_str);
    
    char *output=malloc(sizeof(char)*((int)strlen(middle)+(int)strlen(ahead)+(int)strlen(back)+1));
    strcat(output,ahead);
    strcat(output,middle);
    strcat(output,back);
    output[(int)strlen(output)]=0;
    //printf("#### replace_from_index_to_index---- input str %s, output %s\n",input_str,output);
    return output;
        
}
int count_str(char *input_str, char *count_str){
    int count=0;
    int i=0;
    int from=0;
    for(;i<(int)strlen(input_str);i++){
        if(find_from_index(input_str,count_str,from)==-1)
            break;
        else{
            from=find_from_index(input_str,count_str,from)+1;
            count+=1;
        }
    }
    return count;
}



/*
 eg: charIsInString("'Hello'",2)----->TRUE
 * Very Important Function
 bool charIsInString(char *input_str, int char_index){
    char *temp=substr(input_str,0,char_index);
    //char *temp=substr(input_str,0,char_index+1);
    //char char_to_check=input_str[char_index];
    bool in_string=FALSE;
    if(find(temp,"\"")!=-1){
        if(count_str(temp,"\"")%2!=0){
            in_string=TRUE;
        } 
    }        
    if(find(temp,"'")!=-1){
       if (count_str(temp,"'")%2!=0){
            in_string=TRUE;
        }
    }
    //printf("Char is in string --->input_str : %s\n",input_str);
    return in_string;
}
 * The below is the newest version
 */
 bool charIsInString(char *input_str, int char_index){
    //char *temp=substr(input_str,0,char_index);
    //char *temp=substr(input_str,0,char_index+1);
    //char char_to_check=input_str[char_index];
     if(char_index>=(int)strlen(input_str)){
         printf("Mistake occurred whiling calling function charIsInString\nOut of index, input_str %s with index %d\n",input_str,char_index);
         exit(0);
     }
    bool in_string=FALSE;
    bool find_double_quote=FALSE;
    bool find_single_quote=FALSE;
    int i=0;
    for(i=0;i<(int)strlen(input_str);i++){
        //printf("-->%c\n",input_str[i]);
        if(i==char_index){
            //printf("There %d\n",in_string);
                break;
        }
        if(find_double_quote==TRUE && input_str[i]=='"'){
            //printf("here\n");
            find_double_quote=FALSE;
            in_string=FALSE;
            continue;
        }
        if(input_str[i]=='\''&&find_double_quote==FALSE&&find_single_quote==TRUE){
            find_single_quote=FALSE;
            in_string=FALSE;
            continue;
        }
        
        if(input_str[i]=='"'&&find_double_quote==FALSE){
            find_double_quote=TRUE;
            in_string=TRUE;
            continue;
        }
        if(input_str[i]=='\''&&find_double_quote==FALSE&&find_single_quote==FALSE){
            find_single_quote=TRUE;
            in_string=TRUE;
            continue;
        } 
    }
    //printf("Char is in string --->input_str : %s\n",input_str);
    if(input_str[char_index]=='"')
            in_string=FALSE;
    if(find_double_quote==FALSE && find_single_quote==TRUE && input_str[char_index]=='\'')
        in_string=FALSE;
    return in_string;
}
// change "heLlo" to "HELLO"

char *stringToUpperCase(char *input_str) {
    //printf("---->%s\n", input_str);
    int i = 0;
    int length = (int) strlen(input_str);
    //printf("length %d\n", length);
    char temp[10000] = "";
    for (i = 0; i < length; i++) {
        //printf("%c\n", input_str[i]);
        if (isalpha(input_str[i]) == TRUE && charIsInString(input_str,i)==FALSE) {
            //if(input_str[i]>='a'&&input_str[i]<='z'){
            //printf("here %c\n", toupper(input_str[i]));
            temp[i] = toupper(input_str[i]);
        } else {
            temp[i] = input_str[i];
        }
    }
    char *output=malloc(sizeof(char)*((int)strlen(temp)+1));
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    output[(int)strlen(output)]=0;
    //printf("String to upper case----->%s\n", temp);
    return output;
}
char *stringToLowerCase(char *input_str) {
    //printf("---->%s\n", input_str);
    int i = 0;
    int length = (int) strlen(input_str);
    //printf("length %d\n", length);
    char temp[10000] = "";
    for (i = 0; i < length; i++) {
        //printf("%c\n", input_str[i]);
        if (isalpha(input_str[i]) == TRUE && charIsInString(input_str,i)==FALSE) {
            //if(input_str[i]>='a'&&input_str[i]<='z'){
            //printf("here %c\n", toupper(input_str[i]));
            temp[i] = tolower(input_str[i]);
        } else {
            temp[i] = input_str[i];
        }
    }
    char *output=malloc(sizeof(char)*((int)strlen(temp)+1));
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    output[(int)strlen(output)]=0;
    //printf("String to lower case----->%s\n", temp);
    return output;
}
/*
 
 * eg find_not_in_string("'hello',hello",he)--->9
 */

int find_not_in_string(char *from_str, char *find_str) {
    int index = -1;
    bool find_index = TRUE;
    int i;
    int j;
    for (i = 0; i < (int) strlen(from_str); i++) {
        // I add one code here.
        find_index=TRUE;
        if (from_str[i] == find_str[0] && charIsInString(from_str,i)==FALSE) {
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



/*
 * eg replace_not_in_string("'Hello',Hello","Hello","a")---->"'Hello',a"
 */
char* replace_not_in_string(char* input_str, char* replace_str, char* with_str) {
    //printf("#### replace not in string ####\n");
    //printf("#### |%s|\n, replace|%s|\n, with|%s|\n, ####\n",input_str,replace_str,with_str);
    int i;
    int j;

    char output[10000]="";
    //char *output=malloc(sizeof(char)*(1000));
    //printf("Hello\n");
    //printf("%d",(int)strlen(output));
    int length_of_input_str=(int)strlen(input_str);
    int length_of_with_str=(int)strlen(with_str);
    
    for (i = 0; i < length_of_input_str; i++) {
        //printf("WITH STR ----->|%s|, %d\n",with_str,(int)strlen(with_str));
        //printf("---->%c %c %d\n",input_str[i],replace_str[0],charIsInString(input_str,i));
        if (input_str[i] == replace_str[0] && charIsInString(input_str,i)==FALSE) {
            bool is_equal = TRUE;
            //printf("00000 Equal, %c\n",replace_str[0]);
            for (j = 0; j < (int) strlen(replace_str); j++) {
                if (replace_str[j] != input_str[i + j]) {
                    is_equal = FALSE;
                    //printf("\nis_equal=FALSE\n");
                }
            }
            if (is_equal == TRUE) {
                //printf("Find replace_str\n");
                //printf("input str %s\n",input_str);
                //if((int)strlen(with_str)!=0)
                with_str=substr(with_str,0,length_of_with_str);
                //printf("OUTPUT---->|%s|\n",output);
                //printf("with str-->|%s|\n",with_str);
                if(length_of_with_str!=0)
                    strcat(output, with_str);
                //printf("OUTPUT---->|%s|\n",output);
                //printf("input str %s\n",input_str);
                //printf("i is %d\n",i);
                i = i + (int) strlen(replace_str) - 1;
                
                //printf("i is %d\n",i);
            } else {
                output[(int) strlen(output)] = input_str[i];
            }
        } else {
            output[(int) strlen(output)] = input_str[i];
        }
        //printf("--->%c\n",input_str[i]);
    }
    //char *output_str = output;
    //printf("Output is %s\n",output);
    int length=(int)strlen(output);
    char *output_str=malloc(sizeof(char)*length);
    //printf("%% %d %%\n",(int)strlen(output));
    int a=0;
    for(a=0;a<length;a++){
        output_str[a]=output[a];
    }
    output_str=substr(output_str,0,length);
    //printf("OUTPUT---->|%s|\n",output);
    return output_str;
}

/*
 * eg replace_not_in_string_for_times("'Hello',Hello Hello","Hello","a",1)---->"'Hello',a,Hello"
 */
char* replace_not_in_string_for_times(char* input_str, char* replace_str, char* with_str, int time) {
    //printf("#### replace not in string ####\n");
    //printf("#### |%s|\n, replace|%s|\n, with|%s|\n, ####\n",input_str,replace_str,with_str);
    int i;
    int j;
    
    int count=0;

    char output[10000]="";
    //char *output=malloc(sizeof(char)*(1000));
    //printf("Hello\n");
    //printf("%d",(int)strlen(output));
    int length_of_input_str=(int)strlen(input_str);
    int length_of_with_str=(int)strlen(with_str);
    
    for (i = 0; i < length_of_input_str; i++) {
        //printf("WITH STR ----->|%s|, %d\n",with_str,(int)strlen(with_str));
        //printf("---->%c %c %d\n",input_str[i],replace_str[0],charIsInString(input_str,i));
        if (input_str[i] == replace_str[0] && charIsInString(input_str,i)==FALSE && count<time) {
            bool is_equal = TRUE;
            //printf("00000 Equal, %c\n",replace_str[0]);
            for (j = 0; j < (int) strlen(replace_str); j++) {
                if (replace_str[j] != input_str[i + j]) {
                    is_equal = FALSE;
                    //printf("\nis_equal=FALSE\n");
                }
            }
            if (is_equal == TRUE) {
                count++;
                //printf("Find replace_str\n");
                //printf("input str %s\n",input_str);
                //if((int)strlen(with_str)!=0)
                with_str=substr(with_str,0,length_of_with_str);
                //printf("OUTPUT---->|%s|\n",output);
                //printf("with str-->|%s|\n",with_str);
                if(length_of_with_str!=0)
                    strcat(output, with_str);
                //printf("OUTPUT---->|%s|\n",output);
                //printf("input str %s\n",input_str);
                //printf("i is %d\n",i);
                i = i + (int) strlen(replace_str) - 1;
                
                //printf("i is %d\n",i);
            } else {
                output[(int) strlen(output)] = input_str[i];
            }
        } else {
            output[(int) strlen(output)] = input_str[i];
        }
        //printf("--->%c\n",input_str[i]);
    }
    //char *output_str = output;
    //printf("Output is %s\n",output);
    int length=(int)strlen(output);
    char *output_str=malloc(sizeof(char)*length);
    //printf("%% %d %%\n",(int)strlen(output));
    int a=0;
    for(a=0;a<length;a++){
        output_str[a]=output[a];
    }
    output_str=substr(output_str,0,length);
    //printf("OUTPUT---->|%s|\n",output);
    return output_str;
}

int find_from_index_not_in_string(char *from_str, char *find_str, int from_index) {
    if (from_index < 0) {
        printf("Mistake occurred which calling function find_from_index_not_in_string");
        return -1;
    } else {
        int index = -1;
        bool find_index = TRUE;
        int i;
        int j;
        for (i = from_index; i < (int) strlen(from_str); i++) {
            find_index = TRUE;
            if (from_str[i] == find_str[0] && charIsInString(from_str,i)==FALSE) {
                for (j = 0; j < (int) strlen(find_str); j++) {
                    if (find_str[j] != from_str[i + j]) {
                        find_index = FALSE;
                        break;
                    }
                }
                if (find_index == TRUE) {
                    //find_index = TRUE;
                    index = i;
                    break;
                }
            }
        }
        return index;
    }
}

int count_str_not_in_string(char *input_str, char *count_str){
    int count=0;
    int i=0;
    int from=0;
    for(;i<(int)strlen(input_str);i++){
        if(find_from_index_not_in_string(input_str,count_str,from)==-1)
            break;
        else{
            from=find_from_index_not_in_string(input_str,count_str,from)+1;
            count+=1;
        }
    }
    return count;
}

char *experiment(char *input_str){
    input_str=substr(input_str,0,2);
    printf("input_str %s\n",input_str);
    return "Hello";
}

char* removeBackSpace(char* input_message) {
    if ((int) strlen(input_message) != 0) {
        int i = (int) strlen(input_message) - 1;
        char *output = input_message;
        if (output[i] == ' ') {
            for (; i >= 0; i--) {
                if (input_message[i] != ' ') {
                    output = substr(input_message, 0, i + 1);
                    break;
                }
            }
        }
        return output;
    } else {
        return "";
    }

}

char* removeAheadSpace(char* input_message) {
    //printf("Input Message is %s\n",input_message);
    if ((int) strlen(input_message) != 0) {
        int i = 0;
        char *output = input_message;
        if (input_message[0] == ' ') {
            for (; i < (int) strlen(input_message); i++) {
                if (input_message[i] != ' ') {
                    output = substr(input_message, i, (int) strlen(input_message));
                    break;
                }
            }
        }
        //char *output_str=malloc(sizeof(char)*(int)strlen(output));
        //strcat(output_str,output);
        //return output_str;
        //printf("output is %s\n",output);
        return output;
    } else {
        return "";
    }
}

/*
 * removeAheadSpaceForNum("  Hi",1)---->" Hi")
 */
char *removeAheadSpaceForNum(char* input_message, int remove_n_spaces) {
    if ((int) strlen(input_message) != 0) {
        int i = 0;
        int count = 0;
        char *output = input_message;
        for (; i < (int) strlen(input_message); i++) {
            if (input_message[i] == ' ') {
                count++;
            }
            if (count == remove_n_spaces) {
                output = substr(input_message, i + 1, (int) strlen(input_message));
                break;
            }
        }
        return output;
    } else {
        return "";
    }
}

char *trim(char *input_str){
    return removeAheadSpace(removeBackSpace(input_str));
}

bool stringIsDigit(char *input_str){
    input_str=trim(input_str);
    if(input_str[0]=='-')
        input_str=substr(input_str,1,(int)strlen(input_str));
    bool isDigit=TRUE;
    int i=0;
    if(input_str[0]=='.')
        i=1;
    int initial=i;
    
    for(;i<(int)strlen(input_str);i++){
        if(input_str[i]=='.'&&i!=initial&&i!=(int)strlen(input_str)-1){
            continue;
        }
        if(isdigit(input_str[i])==FALSE){
            isDigit=FALSE;
            break;
        }
    }
    
    int numberOfDot=count_str(input_str,".");
    if(numberOfDot>1)
        isDigit=FALSE;
    
    return isDigit;
}

bool stringIsAlpha(char *input_str){
    input_str=trim(input_str);
    int i=0;
    int length=(int)strlen(input_str);
    bool is_alpha=TRUE;
    for (i=0; i<length; i++) {
        if (isalpha(input_str[i])==FALSE) {
            is_alpha=FALSE;
            break;
        }
    }
    return is_alpha;
}

bool charIsInList(char *input_str,int index){
    char *check_str=substr(input_str, 0, index+1);
    if(count_str_not_in_string(check_str, "[") != count_str_not_in_string(check_str, "]")){
        //printf("%c %d is in []\n",input_str[index],index);
        //printf("[ %d, ] %d\n",count_str_not_in_string(check_str, "["),count_str_not_in_string(check_str, "]"));
        return TRUE;
    }
    else{
        return FALSE;
    }
}


bool charIsInDictionary(char *input_str,int index){
    char *check_str=substr(input_str, 0, index+1);
    if(count_str_not_in_string(check_str, "{") != count_str_not_in_string(check_str, "}")){
        //printf("%c %d is in dictionary\n",input_str[index],index);
        //printf("RETURN TRUE\n");
        return TRUE;
    }
    else{
        //printf("RETURN FALSE\n");
        return FALSE;
    }
}

bool charIsInParenthesis(char *input_str, int index){
    char *check_str=substr(input_str, 0, index+1);
    if(count_str_not_in_string(check_str, "(") != count_str_not_in_string(check_str, ")")){
        //printf("%c %d is in dictionary\n",input_str[index],index);
        return TRUE;
    }
    else{
        return FALSE;
    }
}

int find_not_in_str_list_dict(char *from_str, char *find_str) {
    int index = -1;
    bool find_index = TRUE;
    int i;
    int j;
    for (i = 0; i < (int) strlen(from_str); i++) {
        // I add one code here.
        find_index=TRUE;
        if (from_str[i] == find_str[0] && charIsInString(from_str,i)==FALSE && charIsInDictionary(from_str, i)==FALSE && charIsInList(from_str, i)==FALSE) {
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
int find_from_index_not_in_str_list_dict(char *from_str, char *find_str, int from_index) {
    if (from_index < 0) {
        printf("Mistake occurred which calling function find_from_index_not_in_str_list_dict");
        return -1;
    } else {
        int index = -1;
        bool find_index = TRUE;
        int i;
        int j;
        for (i = from_index; i < (int) strlen(from_str); i++) {
            find_index = TRUE;
            if (from_str[i] == find_str[0] && charIsInString(from_str,i)==FALSE && charIsInDictionary(from_str, i)==FALSE && charIsInList(from_str, i)==FALSE) {
                for (j = 0; j < (int) strlen(find_str); j++) {
                    if (find_str[j] != from_str[i + j]) {
                        find_index = FALSE;
                        break;
                    }
                }
                if (find_index == TRUE) {
                    //find_index = TRUE;
                    index = i;
                    break;
                }
            }
        }
        return index;
    }
}
int count_str_not_in_str_list_dict(char *input_str, char *count_str){
    int count=0;
    int i=0;
    int from=0;
    for(;i<(int)strlen(input_str);i++){
        if(find_from_index_not_in_str_list_dict(input_str,count_str,from)==-1)
            break;
        else{
            from=find_from_index_not_in_str_list_dict(input_str,count_str,from)+1;
            count+=1;
        }
    }
    return count;
}

int find_not_in_str_list_dict_parenthesis(char *from_str, char *find_str) {
    int index = -1;
    bool find_index = TRUE;
    int i;
    int j;
    for (i = 0; i < (int) strlen(from_str); i++) {
        // I add one code here.
        find_index=TRUE;
        if (from_str[i] == find_str[0] && charIsInString(from_str,i)==FALSE && charIsInDictionary(from_str, i)==FALSE && charIsInList(from_str, i)==FALSE && charIsInParenthesis(from_str, i)==FALSE) {
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
int find_from_index_not_in_str_list_dict_parenthesis(char *from_str, char *find_str, int from_index) {
    if (from_index < 0) {
        printf("Mistake occurred which calling function find_from_index_not_in_str_list_dict");
        return -1;
    } else {
        int index = -1;
        bool find_index = TRUE;
        int i;
        int j;
        for (i = from_index; i < (int) strlen(from_str); i++) {
            find_index = TRUE;
            if (from_str[i] == find_str[0] && charIsInString(from_str,i)==FALSE && charIsInDictionary(from_str, i)==FALSE && charIsInList(from_str, i)==FALSE && charIsInParenthesis(from_str, i)==FALSE) {
                for (j = 0; j < (int) strlen(find_str); j++) {
                    if (find_str[j] != from_str[i + j]) {
                        find_index = FALSE;
                        break;
                    }
                }
                if (find_index == TRUE) {
                    //find_index = TRUE;
                    index = i;
                    break;
                }
            }
        }
        return index;
    }
}
int count_str_not_in_str_list_dict_parenthesis(char *input_str, char *count_str){
    int count=0;
    int i=0;
    int from=0;
    for(;i<(int)strlen(input_str);i++){
        if(find_from_index_not_in_str_list_dict_parenthesis(input_str,count_str,from)==-1)
            break;
        else{
            from=find_from_index_not_in_str_list_dict_parenthesis(input_str,count_str,from)+1;
            count+=1;
        }
    }
    return count;
}

