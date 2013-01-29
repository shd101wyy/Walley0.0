/* 
 * File:   walley_language.h
 * Author: shd101wyy
 *
 * Created on September 25, 2012, 4:57 PM
 */

//#include "walley_core_fourth_generation.h"
//#include "walley_core_final.h"
#include "walley_class.h"


/*
 * Walley_Language::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 * Translate natural language to walley language
 * 
 * substitue:
 * PRINT(PARAMS):PRINT PARAMS
   VAR = PARAMS:VAR IS PARAMS
   VAR = FUNCTION(PARAMS):VAR = FUNCTION WITH PARAMS
 
 * 
 *
 * 
 */
/*
 * clean space inside list, dictionary, or parenthesis
 * eg cleanSpaceInListDictParenthesis("x = [1,2   ,4]")--->"x = [1,2,4]"
 */
char *cleanSpaceInListDictParenthesis(char *input_str){
    int i=0;
    int length=(int)strlen(input_str);
    char temp[10000]="";
    bool is_inside=FALSE;
    for (i=0; i<length; i++) {
        if((input_str[i]=='{'||
            input_str[i]=='['||
            input_str[i]=='(')&&charIsInString(input_str, i)==FALSE){
            is_inside=TRUE;
            strcat(temp, substr(input_str, i, i+1));
            continue;
        }
        if (input_str[i]=='}'&&charIsInString(input_str, i)==FALSE && charIsInDictionary(input_str, i)==FALSE) {
            is_inside=FALSE;
            strcat(temp, substr(input_str, i, i+1));
            continue;
        }
        else if(input_str[i]==']'&&charIsInString(input_str, i)==FALSE && charIsInList(input_str, i)==FALSE){
            is_inside=FALSE;
            strcat(temp, substr(input_str, i, i+1));
            continue;
        }
        else if(input_str[i]==')' && charIsInString(input_str, i)==FALSE && charIsInParenthesis(input_str, i)==FALSE){
            is_inside=FALSE;
            strcat(temp, substr(input_str, i, i+1));
            continue;
        }
        if (is_inside==FALSE) {
            strcat(temp, substr(input_str, i, i+1));
        }
        else{
            if (input_str[i]==' '&&charIsInString(input_str, i)==FALSE) {
                continue;
            }
        else{
            strcat(temp, substr(input_str, i, i+1));
            }
        }
    }
    char *output=append("", temp);
    return output;
}
/*
 * clean or add spaces between two sentences
 */

char *cleanUpSentence(char *input_str){
    
    // replace string in <@ >
    char **SAVE_STR_IN_EXP;
    Str_initStringList(&SAVE_STR_IN_EXP);
    int INDEX=0;
    int m=0;
    int num_of_expression=count_str_not_in_string(input_str, "<@");
    for (; m<num_of_expression; m++) {
        int left=find_from_behind_not_in_string(input_str, "<@");
        int right=find_from_index_not_in_string(input_str, ">", left+1);
        if (right==-1) {
            break;
        }
        char *string_in_side=substr(input_str, left+2, right);
        string_in_side=cleanUpSentence(string_in_side);
        char *replace_str=append("<@", append(string_in_side, ">"));
        char *with_str=append("#SAVED_", intToCString(INDEX));
        Str_addString(&SAVE_STR_IN_EXP, replace_str);
        INDEX++;
        input_str=replace_from_index_to_index(input_str, replace_str, with_str, left, right+1);
    }
    
    
    
    input_str=cleanSpaceInListDictParenthesis(input_str);
    int num_of_space_ahead=numOfSpaceAheadString(input_str);
    input_str=trim(input_str);
    int length=(int)strlen(input_str);
    int i=0;
    char temp[10000]="";
    int index_of_temp=0;
    bool has_found_space=FALSE;
    
    
    for(i=0;i<num_of_space_ahead;i++){
        temp[index_of_temp]=' ';
            index_of_temp+=1;
    }
    for(i=0;i<length;i++){
        //printf("--->%c %d %d\n",input_str[i],charIsInString(input_str,i),has_found_space);
        if(input_str[i]==' '&& charIsInString(input_str,i)==FALSE && has_found_space==TRUE){
            if (i+4<(int)strlen(input_str)) {
                if (input_str[i+1]=='a' && input_str[i+2]=='n' &&input_str[i+3]=='d' &&input_str[i+4]==' ' ) {
                    temp[index_of_temp]=' ';
                    index_of_temp+=1;
                    continue;
                }
                if (input_str[i+1]=='o' && input_str[i+2]=='r' && input_str[i+3]==' ') {
                    temp[index_of_temp]=' ';
                    index_of_temp+=1;
                    continue;
                }
            }
            
            continue;
        }
        if(charIsInString(input_str,i)==TRUE||
           charIsInParenthesis(input_str, i)==TRUE||
           charIsInList(input_str, i)==TRUE||
           charIsInDictionary(input_str, i)==TRUE){
            temp[index_of_temp]=input_str[i];
            index_of_temp+=1;
            continue;
        }
        if(input_str[i]!=' '){
            // >= <= ==
            if(i!=length-1&&((input_str[i]=='='&&input_str[i+1]=='=')
                    ||(input_str[i]=='>'&&input_str[i+1]=='=')
                    ||(input_str[i]=='<'&&input_str[i+1]=='='))
                    && has_found_space==FALSE){
                //temp[index_of_temp]=' ';
                //index_of_temp+=1;
                temp[index_of_temp]=input_str[i];
                index_of_temp+=1;
                temp[index_of_temp]=input_str[i+1];
                index_of_temp+=1;
                //temp[index_of_temp]=' ';
                //index_of_temp+=1;
                has_found_space=FALSE;
                i++;
                continue;
            }
            else if(i!=length-1&&((input_str[i]=='='&&input_str[i+1]=='=')
                    || (input_str[i] == '>' && input_str[i + 1] == '=')
                    || (input_str[i] == '<' && input_str[i + 1] == '='))
                    && has_found_space == TRUE) {
                index_of_temp=index_of_temp-1;
                temp[index_of_temp] = input_str[i];
                index_of_temp += 1;
                temp[index_of_temp]=input_str[i+1];
                index_of_temp+=1;
                //temp[index_of_temp] = ' ';
                //index_of_temp += 1;
                has_found_space = TRUE;
                i++;
                continue;
            }
            //else if(isSign(input_str[i])==TRUE && has_found_space==FALSE){
            else if (isJudgeSign(input_str[i])==TRUE && has_found_space==FALSE){
                //temp[index_of_temp]=' ';
                //index_of_temp+=1;
                temp[index_of_temp]=input_str[i];
                index_of_temp+=1;
                //temp[index_of_temp]=' ';
                //index_of_temp+=1;
                
                //has_found_space=FALSE;  it used to be FALSE
                has_found_space=TRUE;
                continue;
            }
            else if (isJudgeSign(input_str[i])==TRUE && has_found_space==TRUE){
                //temp[index_of_temp]=' ';
                //index_of_temp+=1;
                index_of_temp=index_of_temp-1;
                if (isJudgeSign(temp[index_of_temp])) {
                    index_of_temp=index_of_temp+1;
                }
                temp[index_of_temp]=input_str[i];
                index_of_temp+=1;
                //temp[index_of_temp]=' ';
                //index_of_temp+=1;
                has_found_space=TRUE;
                
                continue;
            }
            else if(input_str[i]=='=' && has_found_space==FALSE){
                temp[index_of_temp]=' ';
                index_of_temp+=1;
                temp[index_of_temp]=input_str[i];
                index_of_temp+=1;
                temp[index_of_temp]=' ';
                index_of_temp+=1;
                has_found_space=TRUE;
                continue;
            }
            //else if(isSign(input_str[i])==TRUE && has_found_space==TRUE){
            else if(input_str[i]=='=' && has_found_space==TRUE){
                //temp[index_of_temp]=' ';
                //index_of_temp+=1;
                temp[index_of_temp]=input_str[i];
                index_of_temp+=1;
                temp[index_of_temp]=' ';
                index_of_temp+=1;
                has_found_space=TRUE;
                continue;
            }
            
            /*
            else if (isJudgeSign(input_str[i])==TRUE && has_found_space==FALSE){
                temp[index_of_temp]=' ';
                index_of_temp+=1;
                temp[index_of_temp]=input_str[i];
                index_of_temp+=1;
                temp[index_of_temp]=' ';
                index_of_temp+=1;
                has_found_space=TRUE;
                continue;
            }
            else if (isJudgeSign(input_str[i])==TRUE && has_found_space==TRUE){
                //temp[index_of_temp]=' ';
                //index_of_temp+=1;
                temp[index_of_temp]=input_str[i];
                index_of_temp+=1;
                temp[index_of_temp]=' ';
                index_of_temp+=1;
                has_found_space=TRUE;
                continue;
            }*/
            //else if ((input_str[i]==','||input_str[i]==':'||input_str[i]=='('||input_str[i]==')') && has_found_space==FALSE){
            else if ((input_str[i]==','||input_str[i]==':') && has_found_space==FALSE){
                temp[index_of_temp]=' ';
                index_of_temp+=1;
                temp[index_of_temp]=input_str[i];
                index_of_temp+=1;
                temp[index_of_temp]=' ';
                index_of_temp+=1;
                has_found_space=TRUE;
                continue;
            }
//            else if ((input_str[i]==','||input_str[i]==':'||input_str[i]=='('||input_str[i]==')') && has_found_space==TRUE){
            else if ((input_str[i]==','||input_str[i]==':') && has_found_space==TRUE){
            //temp[index_of_temp]=' ';
                //index_of_temp+=1;
                temp[index_of_temp]=input_str[i];
                index_of_temp+=1;
                temp[index_of_temp]=' ';
                index_of_temp+=1;
                has_found_space=TRUE;
                continue;
            }
            else{
                //printf("enter here\n");
                temp[index_of_temp]=input_str[i];
                index_of_temp+=1;
                has_found_space=FALSE;
                if (isSign(input_str[i])) {
                    has_found_space=TRUE;
                }
                continue;
            }
        }
        if(input_str[i]==' '&&charIsInString(input_str,i)==TRUE){
            temp[index_of_temp]=input_str[i];
            index_of_temp+=1;
            //has_found_space=FALSE;
            continue;
        }
            
        if(input_str[i]==' ' && charIsInString(input_str,i)==FALSE && has_found_space==FALSE){
            has_found_space=TRUE;
            temp[index_of_temp]=input_str[i];
            index_of_temp+=1;
            continue;
        }
    }
    int length_of_temp=(int)strlen(temp);
    char *output=(char*)malloc(sizeof(char)*(length_of_temp+1));
    for(i=0;i<length_of_temp;i++){
        output[i]=temp[i];
    }
    
    //strlen problem 1
    //output[(int)strlen(output)]=0;
    output[length_of_temp]=0;
    
    output=substr(output,0,length_of_temp);
    output=removeBackSpace(output);
    
    
    // restore string in <@ >
    m=0;
    for (; m<INDEX; m++) {
        output=replace(output,append("#SAVED_", intToCString(m)),SAVE_STR_IN_EXP[m+1]);
    }
    
    return output;
}

/*
 Clean up sentences backup
 char *cleanUpSentence(char *input_str){
 int num_of_space_ahead=numOfSpaceAheadString(input_str);
 input_str=trim(input_str);
 int length=(int)strlen(input_str);
 int i=0;
 char temp[10000]="";
 int index_of_temp=0;
 bool has_found_space=FALSE;
 for(i=0;i<num_of_space_ahead;i++){
 temp[index_of_temp]=' ';
 index_of_temp+=1;
 }
 for(i=0;i<length;i++){
 //printf("--->%c %d %d\n",input_str[i],charIsInString(input_str,i),has_found_space);
 if(input_str[i]==' '&& charIsInString(input_str,i)==FALSE && has_found_space==TRUE){
 continue;
 }
 if(charIsInString(input_str,i)==TRUE){
 temp[index_of_temp]=input_str[i];
 index_of_temp+=1;
 continue;
 }
 if(input_str[i]!=' '){
 // >= <= ==
 if(i!=length-1&&((input_str[i]=='='&&input_str[i+1]=='=')
 ||input_str[i]=='>'&&input_str[i+1]=='='
 ||input_str[i]=='<'&&input_str[i+1]=='=')
 && has_found_space==FALSE){
 //temp[index_of_temp]=' ';
 //index_of_temp+=1;
 temp[index_of_temp]=input_str[i];
 index_of_temp+=1;
 temp[index_of_temp]=input_str[i+1];
 index_of_temp+=1;
 //temp[index_of_temp]=' ';
 //index_of_temp+=1;
 has_found_space=FALSE;
 i++;
 continue;
 }
 else if(i!=length-1&&((input_str[i]=='='&&input_str[i+1]=='=')
 || input_str[i] == '>' && input_str[i + 1] == '='
 || input_str[i] == '<' && input_str[i + 1] == '=')
 && has_found_space == TRUE) {
 temp[index_of_temp] = input_str[i];
 index_of_temp += 1;
 temp[index_of_temp]=input_str[i+1];
 index_of_temp+=1;
 //temp[index_of_temp] = ' ';
 //index_of_temp += 1;
 has_found_space = TRUE;
 i++;
 continue;
 }
 //else if(isSign(input_str[i])==TRUE && has_found_space==FALSE){
 else if(input_str[i]=='=' && has_found_space==FALSE){
 temp[index_of_temp]=' ';
 index_of_temp+=1;
 temp[index_of_temp]=input_str[i];
 index_of_temp+=1;
 temp[index_of_temp]=' ';
 index_of_temp+=1;
 has_found_space=TRUE;
 continue;
 }
 //else if(isSign(input_str[i])==TRUE && has_found_space==TRUE){
 else if(input_str[i]=='=' && has_found_space==TRUE){
 //temp[index_of_temp]=' ';
 //index_of_temp+=1;
 temp[index_of_temp]=input_str[i];
 index_of_temp+=1;
 temp[index_of_temp]=' ';
 index_of_temp+=1;
 has_found_space=TRUE;
 continue;
 }
 
 else if (isJudgeSign(input_str[i])==TRUE && has_found_space==FALSE){
 temp[index_of_temp]=' ';
 index_of_temp+=1;
 temp[index_of_temp]=input_str[i];
 index_of_temp+=1;
 temp[index_of_temp]=' ';
 index_of_temp+=1;
 has_found_space=TRUE;
 continue;
 }
 else if (isJudgeSign(input_str[i])==TRUE && has_found_space==TRUE){
 //temp[index_of_temp]=' ';
 //index_of_temp+=1;
 temp[index_of_temp]=input_str[i];
 index_of_temp+=1;
 temp[index_of_temp]=' ';
 index_of_temp+=1;
 has_found_space=TRUE;
 continue;
 }
 else if ((input_str[i]==','||input_str[i]==':'||input_str[i]=='('||input_str[i]==')') && has_found_space==FALSE){
 temp[index_of_temp]=' ';
 index_of_temp+=1;
 temp[index_of_temp]=input_str[i];
 index_of_temp+=1;
 temp[index_of_temp]=' ';
 index_of_temp+=1;
 has_found_space=TRUE;
 continue;
 }
 else if ((input_str[i]==','||input_str[i]==':'||input_str[i]=='('||input_str[i]==')') && has_found_space==TRUE){
 //temp[index_of_temp]=' ';
 //index_of_temp+=1;
 temp[index_of_temp]=input_str[i];
 index_of_temp+=1;
 temp[index_of_temp]=' ';
 index_of_temp+=1;
 has_found_space=TRUE;
 continue;
 }
 else{
 temp[index_of_temp]=input_str[i];
 index_of_temp+=1;
 has_found_space=FALSE;
 continue;
 }
 }
 if(input_str[i]==' '&&charIsInString(input_str,i)==TRUE){
 temp[index_of_temp]=input_str[i];
 index_of_temp+=1;
 //has_found_space=FALSE;
 continue;
 }
 
 if(input_str[i]==' ' && charIsInString(input_str,i)==FALSE && has_found_space==FALSE){
 has_found_space=TRUE;
 temp[index_of_temp]=input_str[i];
 index_of_temp+=1;
 continue;
 }
 }
 //printf("%s\n",temp);
 char *output=malloc(sizeof(char)*((int)strlen(temp)+1));
 for(i=0;i<(int)strlen(temp);i++){
 output[i]=temp[i];
 }
 output[(int)strlen(output)]=0;
 output=substr(output,0,(int)strlen(temp));
 output=removeBackSpace(output);
 return output;
 }

 
 */
/*
 * eg input '  def sum( a,  b):------>'  def sum(a,b):'
 */
char *removeSpaceForDictionaryListAndParenthesis(char *input_str){
    char *output=cleanUpSentence(input_str);
    if(find_not_in_string(output,"( ")!=-1)
        output=replace_not_in_string(output,"( ","(");
    if(find_not_in_string(output," )")!=-1)
        output=replace_not_in_string(output," )",")");
    if(find_not_in_string(output," , ")!=-1)
        output=replace_not_in_string(output," , ",",");
    return output;
}
// eg Hello , I am Yiyi ---->5
int numOfSmallSentences(char *input_str){
    input_str=trim(input_str);
    input_str=cleanUpSentence(input_str);
    input_str=trim(input_str);
    //printf("#### numOfSmallSentences ####\n");
    //printf("input_str--->|%s|\n",input_str);
    int length=(int)strlen(input_str);
    int i=0;
    int has_found_space=FALSE;
    int count=1;
    for(i=0;i<length;i++){
        if(input_str[i]==' ' && charIsInString(input_str,i)==FALSE && has_found_space==TRUE){
            continue;
        }
        if(input_str[i]!=' '){
            has_found_space=FALSE;
            continue;
        }
        if(input_str[i]==' ' && charIsInString(input_str,i)==FALSE && has_found_space==FALSE){
            count=count+1;
            has_found_space=TRUE;
            continue;
        }
    }
    //printf("Num return %d\n",count);
    return count;
}
/*
 * eg sentenceAtIndexOfString("Hello I am Yiyi", 0)---->Hello
 */
char *sentenceAtIndexOfString(char *input_str, int index){
    //printf("#### sentenceAtIndexOfString ####\n");
    //printf("input_str |%s|, index |%d|\n",input_str,index);
    input_str=trim(input_str);
    input_str=cleanUpSentence(input_str);
    //printf("input_str |%s|\n",input_str);
    //printf("Num --> %d",numOfSmallSentences(input_str));
    if(index>=numOfSmallSentences(input_str)){
        printf("Mistake occurred whiling calling function sentenceAtIndexOfString\nIndex out of bound\ninput_str |%s|\n",input_str);
        exit(0);
    }
    //printf("---->|%s|\n",input_str);
    int begin=0;
    int end=0;
    int i=0;
    for(i=0;i<index;i++){
        begin=find_from_index_not_in_string(input_str," ",begin+1);
    }
    end=find_from_index_not_in_string(input_str," ",begin+1);
    if(begin!=-1 && end==-1){
        end=(int)strlen(input_str);
    }
    
    //printf("begin %d, end %d\n",begin,end);
    //printf("|%s|\n",trim(substr(input_str,begin,end)));
    char *output=trim(substr(input_str,begin,end));
    //printf("End sentenceAtIndexOfString\n");
    return output;
    
}

/*
 * check similaroty
 * get the num of same str except VAR
 * eg Walley_Find_Similarity_Between_Two_Str("PRINT VAR","PRINT(VAR)")------->2 because there is one PRINT and VAR the same
 *    Walley_Find_Similarity_Between_Two_Str("PRINT VAR WITH","PRINT(VAR)WITH")------->3
 */
int Walley_Find_Similarity_Between_Two_Str(char *input_str, char *compare_to_str){
    //printf("#### Walley_Find_Similarity_Between_Two_Str ####\n");
    //printf("----> %s\n",input_str);
    //printf("----> %s\n",compare_to_str);
    int i=0;
    //int index_for_compare_to_str;
    input_str=cleanUpSentence(input_str);
    compare_to_str=cleanUpSentence(compare_to_str);
    
    input_str=stringToUpperCase(input_str);
    compare_to_str=stringToUpperCase(compare_to_str);
    
    
    //int num=numOfSmallSentences(input_str);
    int similarity=0;
    //int index_of_same=-1;
    //printf("%s\n%s\n",input_str,compare_to_str);
    //for(i=0;i<num;i++){
    for(i=0;i<numOfSmallSentences(input_str);i++){
        if(stringIsEmpty(input_str)||stringIsEmpty(compare_to_str))
            break;
        char *input_str_index_string=sentenceAtIndexOfString(input_str,i);
        int j=0;//index_of_same+1;
        for(;j<numOfSmallSentences(compare_to_str);j++){
            char *compare_to_string_index_string=sentenceAtIndexOfString(compare_to_str,j);
            //printf("-->%s || %s\n",input_str_index_string,compare_to_string_index_string);
            if(strcmp(compare_to_string_index_string,input_str_index_string)==0 ){
            //if(find(compare_to_string_index_string,input_str_index_string)!=-1
            //        ||find(input_str_index_string,compare_to_string_index_string)!=-1){
              //  printf("******** Find Same\n");
                
                similarity+=1;
                
                compare_to_str=append(compare_to_str," ");
                input_str=append(input_str," ");
                
                compare_to_string_index_string=append(compare_to_string_index_string," ");
                input_str_index_string=append(input_str_index_string," ");
                //printf("Here\n");
                compare_to_str=replace_not_in_string_for_times(compare_to_str,compare_to_string_index_string,"",1);
                input_str=replace_not_in_string_for_times(input_str,input_str_index_string,"",1);
                
                if(find_not_in_string(compare_to_str,"  ")!=-1)
                    compare_to_str=replace_not_in_string(compare_to_str,"  "," ");
                if(find_not_in_string(input_str,"  ")!=-1)
                    input_str=replace_not_in_string(input_str,"  "," ");
                input_str=trim(input_str);
                compare_to_str=trim(compare_to_str);
                //printf("--->|%s|\n-->|%s|\n\n",input_str,compare_to_str);
        
                //j=j-1;
                i=i-1;
                //index_of_same=j;
                
                break;
            }
            
        }
    }
    //printf("END Walley_Find_Similarity_Between_Two_Str\n\n");
    return similarity;
}

/*
 * Walley_Compare_Sentence_From_Memory("__walley_language__.wy","VAR IS VAR")----->"VAR = VAR"
 */
/*
char *Walley_Compare_Sentence_From_Memory(char *walley_language_file,char *input_str){
   //// printf("#### Walley_Compare_Sentence_From_Memory ####\n");
    FILE *fp=fopen(walley_language_file,"r");
    char arr[1000]="";
    if (fp == NULL) {
        perror("Walley_Compare_Sentence_From_Memory,File open error!\n");
        exit(1);
    } 
    char *output="None";
    while ((fgets(arr, 1000, fp)) != NULL) {
        if(find_not_in_string(arr,"|")==-1)
            continue;
        char *change=substr(arr,0,find_not_in_string(arr,"|"));
        if(strcmp(change,input_str)==0){
            //printf("Find change language!!!!\n");
            output=substr(arr,find_not_in_string(arr,"|")+1,find_from_index_not_in_string(arr,"|",find_not_in_string(arr,"|")+1));//(int)strlen(arr)-1);
            break;
        }
    }
    if (strcmp(input_str, output) != 0) {
        //printf("input %s output %s\n",input_str,output);
        while (TRUE) {
            char *temp = Walley_Compare_Sentence_From_Memory(walley_language_file, output);
            if (strcmp(temp, "None") == 0 || strcmp(temp,output)==0)
                break;
            else {
                output = temp;
            }
        }
    } 
    //else {
    //    printf("EQUAL %s %s\n",input_str,output);
    //}
    output=trim(output);
    //printf("--->%s\n",output);
    return output;
}
*//*
char *Walley_Compare_Sentence_From_Memory(char **walley_language_file,char *input_str){
    //// printf("#### Walley_Compare_Sentence_From_Memory ####\n");
    char *output="None";
    int row=0;
    while (walley_language_file[row] != NULL) {
        char *arr=walley_language_file[row];
        if(find_not_in_string(arr,"|")==-1){
            row++;
            continue;
        }
        char *change=substr(arr,0,find_not_in_string(arr,"|"));
        if(strcmp(change,input_str)==0){
            //printf("Find change language!!!!\n");
            output=substr(arr,find_not_in_string(arr,"|")+1,find_from_index_not_in_string(arr,"|",find_not_in_string(arr,"|")+1));//(int)strlen(arr)-1);
            break;
        }
        row++;
    }
    if (strcmp(input_str, output) != 0) {
        //printf("input %s output %s\n",input_str,output);
        while (TRUE) {
            char *temp = Walley_Compare_Sentence_From_Memory(walley_language_file, output);
            if (strcmp(temp, "None") == 0 || strcmp(temp,output)==0)
                break;
            else {
                output = temp;
            }
        }
    }
    //else {
    //    printf("EQUAL %s %s\n",input_str,output);
    //}
    output=trim(output);
    //printf("--->%s\n",output);
    return output;
}
*/
// this function will ask you whether it is VAR or not......
/*
char *Walley_Analyze_Sentence_Manually(char *input_str) {
    input_str = trim(input_str);
    input_str = cleanUpSentence(input_str);
    int num = numOfSmallSentences(input_str);
    int index = 0;
    char temp[10000] = "";
    bool find_var_and_not_interrupted = FALSE;
    //int var_index=1;
    for (index = 0; index < num; index++) {
        char *string_at_index = sentenceAtIndexOfString(input_str, index);
        char *var_type = variableValueType(string_at_index);
       // if ((strcmp(string_at_index, ",") == 0 || strcmp(string_at_index, "and") == 0) && find_var_and_not_interrupted == TRUE) {
        if (strcmp(string_at_index, ",") == 0 && find_var_and_not_interrupted == TRUE) {

            continue;
        }
        if (strcmp(var_type, "list") == 0 || strcmp(var_type, "dictionary") == 0 || strcmp(var_type, "string") == 0) {
            //||stringIsDigit(string_at_index)){
            printf("|%s| in |%s| at index %d---->Var Y");
            if (find_var_and_not_interrupted == TRUE)
                continue;
            else {
                strcat(temp, "VAR");
                strcat(temp, " ");
                find_var_and_not_interrupted = TRUE;
                continue;
            }
        }
        
        printf("|%s| in |%s| at index %d---->Var? Y/N\n",string_at_index,input_str,index);
        char *answer=malloc(sizeof(char)*10);//[1000]="";
        //answer="";
        //char answer[100];
        gets(answer);
        //scanf("%s",&answer);
        printf("answer is %s\n",answer);
        answer=stringToUpperCase(answer);
        if(strcmp(answer,"Y")==0||strcmp(answer,"YES")==0){
            printf("It is Yes\n");
            if(find_var_and_not_interrupted==TRUE)
                continue;
            else{
                find_var_and_not_interrupted=TRUE;
                strcat(temp,"VAR");
                strcat(temp," ");
            }
        }
        else {
            strcat(temp,string_at_index);
            strcat(temp," ");
            find_var_and_not_interrupted=FALSE;
        }
        printf("****** %s\n",temp);
    }
    int i = 0;
    char *output = malloc(sizeof (char) *((int) strlen(temp) + 1));
    for (i = 0; i < (int) strlen(temp); i++) {
        output[i] = temp[i];
    }
    output[(int) strlen(output)] = 0;
    output = substr(output, 0, (int) strlen(temp));
    output = trim(output);
    output = stringToUpperCase(output);
    printf("output is %s\n",output);
    return output;
}
*//*
char *Walley_Analyze_Sentence_Manually(char *input_str) {
    input_str = trim(input_str);
    if (find_not_in_string(input_str, " the ")!=-1) {
        input_str=replace_not_in_string(input_str, " the ", " ");
    }
    input_str = cleanUpSentence(input_str);
    int num = numOfSmallSentences(input_str);
    int index = 0;
    char temp[10000] = "";
    bool find_var_and_not_interrupted = FALSE;
    //int var_index=1;
    for (index = 0; index < num; index++) {
        char *string_at_index = sentenceAtIndexOfString(input_str, index);
        char *var_type = variableValueType(string_at_index);
       // if ((strcmp(string_at_index, ",") == 0 || strcmp(string_at_index, "and") == 0) && find_var_and_not_interrupted == TRUE) {
        if (strcmp(string_at_index, ",") == 0 && find_var_and_not_interrupted == TRUE) {
            continue;
        }
        if (strcmp(var_type, "list") == 0 || strcmp(var_type, "dictionary") == 0 || strcmp(var_type, "string") == 0) {
            //||stringIsDigit(string_at_index)){
            printf("|%s| in |%s| at index %d---->Var Y",string_at_index,input_str,index);
            if (find_var_and_not_interrupted == TRUE)
                continue;
            else {
                strcat(temp, "VAR");
                
                printf("Var Index?");
                printf("press enter if var has no index\n");
                printf("---->");
                char *index=malloc(sizeof(char)*10);
                gets(index);
                
                if(stringIsEmpty(index)){
                    strcat(temp, " ");
                    find_var_and_not_interrupted = TRUE;
                    continue;
                }
                else{
                    strcat(temp,index);
                    strcat(temp," ");
                    find_var_and_not_interrupted = FALSE;
                    continue;
                }
                
                
            }
        }
        
        //char *answer=malloc(sizeof(char)*10);//[1000]="";
        //answer="";
        char answer2[100];
        printf("|%s| in |%s| at index %d---->Var? Y/N\n",string_at_index,input_str,index);
        //gets(answer2);
        scanf("%s",answer2);
        printf("answer is %s\n",answer2);
        char *answer=append("", answer2);
        answer=stringToUpperCase(answer);
        if (strcmp(answer, "Y") == 0 || strcmp(answer, "YES") == 0) {
            printf("It is Yes\n");
            printf("Var Index?");
            printf("press enter if var has no index\n");
            printf("---->");
            //char *index = malloc(sizeof (char) *10);
            char index[100];
            //gets(index);
            scanf("%s",index);
            if (find_var_and_not_interrupted==TRUE && stringIsEmpty(index)==TRUE)
                continue;
            else{
                //find_var_and_not_interrupted=TRUE;
                strcat(temp,"VAR");
                //strcat(temp," ");
                
                //printf("Var Index?");
                //printf("press enter if var has no index\n");
                //printf("---->");
                //char *index=malloc(sizeof(char)*10);
                //gets(index);
                
                if(stringIsEmpty(index)){
                    strcat(temp, " ");
                    find_var_and_not_interrupted = TRUE;
                    continue;
                }
                else{
                    strcat(temp,index);
                    strcat(temp," ");
                    find_var_and_not_interrupted = FALSE;
                    continue;
                }
            }
        }
        else {
            strcat(temp,string_at_index);
            strcat(temp," ");
            find_var_and_not_interrupted=FALSE;
        }
        printf("****** %s\n",temp);
    }
    int i = 0;
    char *output = malloc(sizeof (char) *((int) strlen(temp) + 1));
    for (i = 0; i < (int) strlen(temp); i++) {
        output[i] = temp[i];
    }
    output[(int) strlen(temp)] = 0;
    output = substr(output, 0, (int) strlen(temp));
    output = trim(output);
    output = stringToUpperCase(output);
   //// printf("output is %s\n",output);
    return output;
}*/

// return "VAR = VAR####{VAR:1,VAR:2}"
/*
char *Walley_Analyze_Sentence_Manually_And_Return_Dictionary_For_Var(char *input_str) {
    input_str = trim(input_str);
    input_str = cleanUpSentence(input_str);
    int num = numOfSmallSentences(input_str);
    int index = 0;
    char temp[10000] = "";
    
    char dictionary[10000]="";
    strcat(dictionary,"{");
            
    bool find_var_and_not_interrupted = FALSE;
    //int var_index=1;
    for (index = 0; index < num; index++) {
        char *string_at_index = sentenceAtIndexOfString(input_str, index);
        char *var_type = variableValueType(string_at_index);
       // if ((strcmp(string_at_index, ",") == 0 || strcmp(string_at_index, "and") == 0) && find_var_and_not_interrupted == TRUE) {
        if (strcmp(string_at_index, ",") == 0 && find_var_and_not_interrupted == TRUE) {
            continue;
        }
        if (strcmp(var_type, "list") == 0 || strcmp(var_type, "dictionary") == 0 || strcmp(var_type, "string") == 0) {
            //||stringIsDigit(string_at_index)){
            printf("|%s| in |%s| at index %d---->Var Y",string_at_index,input_str,index);
            if (find_var_and_not_interrupted == TRUE)
                continue;
            else {
                strcat(temp, "VAR");
                
                printf("Var Index?");
                printf("press enter if var has no index\n");
                printf("---->");
                char *index=malloc(sizeof(char)*10);
                gets(index);
                
                if(stringIsEmpty(index)){
                    strcat(temp, " ");
                    find_var_and_not_interrupted = TRUE;
                    
                    strcat(dictionary,"VAR:");
                    strcat(dictionary,string_at_index);
                    strcat(dictionary,",");
                    continue;
                }
                else{
                    strcat(temp,index);
                    strcat(temp," ");
                    find_var_and_not_interrupted = FALSE;
                    
                    strcat(dictionary,"VAR");
                    strcat(dictionary,index);
                    strcat(dictionary,":");
                    strcat(dictionary,string_at_index);
                    strcat(dictionary,",");
                    
                    continue;
                }
                
                
            }
        }
        
        printf("|%s| in |%s| at index %d---->Var? Y/N\n",string_at_index,input_str,index);
        char *answer=malloc(sizeof(char)*10);//[1000]="";
        //answer="";
        //char answer[100];
        gets(answer);
        //scanf("%s",&answer);
        printf("answer is %s\n",answer);
        answer=stringToUpperCase(answer);
        if (strcmp(answer, "Y") == 0 || strcmp(answer, "YES") == 0) {
            printf("It is Yes\n");
            printf("Var Index?");
            printf("press enter if var has no index\n");
            printf("---->");
            char *index = malloc(sizeof (char) *10);
            gets(index);
            if (find_var_and_not_interrupted==TRUE && stringIsEmpty(index)==TRUE)
                continue;
            else{
                //find_var_and_not_interrupted=TRUE;
                strcat(temp,"VAR");
                //strcat(temp," ");
                
                //printf("Var Index?");
                //printf("press enter if var has no index\n");
                //printf("---->");
                //char *index=malloc(sizeof(char)*10);
                //gets(index);
                
                if(stringIsEmpty(index)){
                    strcat(temp, " ");
                    find_var_and_not_interrupted = TRUE;
                    
                    strcat(dictionary,"VAR:");
                    strcat(dictionary,string_at_index);
                    strcat(dictionary,",");
                    
                    continue;
                }
                else{
                    strcat(temp,index);
                    strcat(temp," ");
                    find_var_and_not_interrupted = FALSE;
                    continue;
                }
            }
        }
        else {
            strcat(temp,string_at_index);
            strcat(temp," ");
            find_var_and_not_interrupted=FALSE;
        }
        printf("****** %s\n",temp);
    }
    dictionary[(int)strlen(dictionary)-1]='}';
    int i = 0;
    char *output = malloc(sizeof (char) *((int) strlen(temp) + 1));
    for (i = 0; i < (int) strlen(temp); i++) {
        output[i] = temp[i];
    }
    output[(int) strlen(output)] = 0;
    output = substr(output, 0, (int) strlen(temp));
    output = trim(output);
    output = stringToUpperCase(output);
   //// printf("output is %s\n",output);
   //// printf("Dictionary is %s\n",dictionary);
    
    
    return output;
}
*/
/*
 * This function could change "print 'Hello'" to "PRINT VAR[1]"
 */
/*
char *Walley_Analyze_Sentence(char *file_var_name, char *input_str){
    input_str=trim(input_str);
    input_str=cleanUpSentence(input_str);
    int num=numOfSmallSentences(input_str);
    int index=0;
    char temp[10000]="";
    bool find_var_and_not_interrupted=FALSE;
    //int var_index=1;
    for(index=0;index<num;index++){
        char *string_at_index=sentenceAtIndexOfString(input_str,index);
        bool var_existed=checkWhetherSameVarNameExistsFromFile(file_var_name,string_at_index);
        bool func_existed=checkWhetherSameFunctionNameExists(string_at_index);
        char *var_type=variableValueType(string_at_index);
        if((strcmp(string_at_index,",")==0 || strcmp(string_at_index,"and")==0) && find_var_and_not_interrupted==TRUE){
            continue;
        }
        if(var_existed==TRUE || func_existed==TRUE){
            //strcat(temp," ");
            strcat(temp,"VAR");
            strcat(temp," ");
            find_var_and_not_interrupted=TRUE;
            continue;
        }
        else if (strcmp(var_type,"list")==0||strcmp(var_type,"dictionary")==0||strcmp(var_type,"string")==0){
                //||stringIsDigit(string_at_index)){
            if(find_var_and_not_interrupted==TRUE)
                continue;
            else {
                //strcat(temp, " ");
                strcat(temp, "VAR");
                strcat(temp, " ");
                find_var_and_not_interrupted = TRUE;
                continue;
            }     
        }
        //else {
        //    find_var_and_not_interrupted=FALSE;
            //strcat(temp," ");
        //    strcat(temp,string_at_index);
        //    strcat(temp," ");
            //var_index=1;
        //    continue;
        //}
        printf("|%s| in |%s| at index %d---->Var? Y/N\n",string_at_index,input_str,index);
        char *answer=malloc(sizeof(char)*10);//[1000]="";
        scanf("%s",&answer);
        //gets(answer);
        printf("answer is %s\n",answer);
        answer=stringToUpperCase(answer);
        if(strcmp(answer,"Y")==0||strcmp(answer,"YES")==0){
            //printf("It is Yes\n");
            if(find_var_and_not_interrupted==TRUE)
                continue;
            else{
                find_var_and_not_interrupted=TRUE;
                strcat(temp,"VAR");
                strcat(temp," ");
            }
        }
        else {
            strcat(temp,string_at_index);
            strcat(temp," ");
            find_var_and_not_interrupted=FALSE;
        }
        
        
    }
    int i=0;
    char *output=malloc(sizeof(char)*((int)strlen(temp)+1));
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    output[(int)strlen(output)]=0;
    output=substr(output,0,(int)strlen(temp));
    output=trim(output);
    output=stringToUpperCase(output);
    return output;
}
*/
/*
char *Walley_Analyze_Sentence(struct VAR struct_var[], char *input_str){
    input_str=trim(input_str);
    input_str=cleanUpSentence(input_str);
    int num=numOfSmallSentences(input_str);
    int index=0;
    char temp[10000]="";
    bool find_var_and_not_interrupted=FALSE;
    //int var_index=1;
    for(index=0;index<num;index++){
        char *string_at_index=sentenceAtIndexOfString(input_str,index);
        bool var_existed=Var_Existed(struct_var,string_at_index);
        bool func_existed=checkWhetherSameFunctionNameExistsFromVar(string_at_index);
        char *var_type=variableValueType(string_at_index);
        if((strcmp(string_at_index,",")==0 || strcmp(string_at_index,"and")==0) && find_var_and_not_interrupted==TRUE){
            continue;
        }
        if(var_existed==TRUE || func_existed==TRUE){
            //strcat(temp," ");
            strcat(temp,"VAR");
            strcat(temp," ");
            find_var_and_not_interrupted=TRUE;
            continue;
        }
        else if (strcmp(var_type,"list")==0||strcmp(var_type,"dictionary")==0||strcmp(var_type,"string")==0){
            //||stringIsDigit(string_at_index)){
            if(find_var_and_not_interrupted==TRUE)
                continue;
            else {
                //strcat(temp, " ");
                strcat(temp, "VAR");
                strcat(temp, " ");
                find_var_and_not_interrupted = TRUE;
                continue;
            }
        }
        printf("|%s| in |%s| at index %d---->Var? Y/N\n",string_at_index,input_str,index);
        char *answer=malloc(sizeof(char)*10);//[1000]="";
        scanf("%s",answer);
        //gets(answer);
        printf("answer is %s\n",answer);
        answer=stringToUpperCase(answer);
        if(strcmp(answer,"Y")==0||strcmp(answer,"YES")==0){
            //printf("It is Yes\n");
            if(find_var_and_not_interrupted==TRUE)
                continue;
            else{
                find_var_and_not_interrupted=TRUE;
                strcat(temp,"VAR");
                strcat(temp," ");
            }
        }
        else {
            strcat(temp,string_at_index);
            strcat(temp," ");
            find_var_and_not_interrupted=FALSE;
        }
        
        
    }
    int i=0;
    char *output=malloc(sizeof(char)*((int)strlen(temp)+1));
    for(i=0;i<(int)strlen(temp);i++){
        output[i]=temp[i];
    }
    output[(int)strlen(temp)]=0;
    output=substr(output,0,(int)strlen(temp));
    output=trim(output);
    output=stringToUpperCase(output);
    return output;
}
*/
/*
 * eg getVarIndexStringAsList("VAR EQUALS VAR VAR1 AND VAR1")-->"[VAR,VAR,VAR1,VAR1]"
 */
char *getVarIndexStringAsList(char *input_str){
    //printf("#### getVarIndexStringAsList ####\n");
    //printf("-----> |%s|\n",input_str);
    char *temp=(char*)malloc(sizeof(char)*((int)strlen(input_str)+2));
    strcpy(temp,input_str);
    strcat(temp," ");
    temp[(int)strlen(input_str)+1]=0;
    input_str=temp;
    char output[10000]="";
    strcat(output,"[");
    int count_of_var=count_str_not_in_string(input_str,"VAR");
    if (count_of_var==0) {
        //char *output3=append(output, trim(input_str));
        //output3=append(output3, "]");
        //printf("VAR num is 0, return %s\n",output3);
        //return output3;
        return "[]";
    }
    while(count_of_var!=0){
        int begin=find_not_in_string(input_str,"VAR");
        int end=find_from_index_not_in_string(input_str," ",begin);
        // 'VAR ' 'VAR1 '
        char *var=substr(input_str,begin,end);
        var=trim(var);
        strcat(output,var);
        strcat(output,",");
        input_str=substr(input_str,end+1,(int)strlen(input_str));
        count_of_var=count_str_not_in_string(input_str,"VAR");
    }
    output[(int)strlen(output)-1]=']';
    
    char *output2=append("", output);
    return output2;
}
/*
 * ("x equals 12","VAR EQUALS VAR1","VAR1")----->12
 * ("x is sum 3 and 4","VAR IS VAR VAR1 AND VAR1","VAR1")----->3
 * ("x is sum 3 and 4","VAR IS VAR VAR1 AND VAR2","VAR2")----->4
 * ("write 'hi' to 'a.txt'","WRITE VAR1 TO VAR2","VAR1")----->'hi'
 */
/*
char *getValueFromVarIndex(char *original_str, char *format_str, char *var_index){
  
    char *temp1=append("# ",original_str);
    temp1=append(temp1," #");
    char *temp2=append("# ",format_str);
    temp2=append(temp2," #");
    
    char *var_list=getVarIndexStringAsList(format_str);
    
    original_str=temp1;
    original_str=stringToUpperCase(original_str);
    format_str=temp2;
    
    //printf("Original ---> %s\n",original_str);
    //printf("Format   ---> %s\n",format_str);
   
    int index=0;
    
    int end=(int)strlen(original_str);
    char *output_value="";
    while (TRUE) {
        int begin=0;
        char *var = valueOfListAtIndex(var_list, index);
        //printf("var is %s\n",var);
        int num_of_ori = numOfSmallSentences(original_str);
        int num_of_for = numOfSmallSentences(format_str);
        int i = 0;
        int j = 0;
        int last_j=-1;
        bool find_var = FALSE;
        for (i = 0; i < num_of_for; i++) {
            char *sentence_at_for = sentenceAtIndexOfString(format_str, i);
            //printf("--- %s --- %s --- %d\n",sentence_at_for,var,index);
            if (strcmp(sentence_at_for, var) == 0) {
                find_var = TRUE;
                //printf("FIND VAR\n");
                //printf("original str |%s|, index %d\n",original_str,last_j+2);
                char *sentence_at_ori=sentenceAtIndexOfString(original_str,last_j+2);
                //printf("sentence_at_ori is %s\n",sentence_at_ori);
                //printf("Begin is %d\n",begin);
                end = find_from_index_not_in_string(original_str, sentence_at_ori, begin);
                //printf("Begin is %d, End is %d\n",begin,end);
                output_value = substr(original_str, begin, end);
                output_value = trim(output_value);


                original_str = substr(original_str, end, (int) strlen(original_str));
                format_str = substr(format_str,find_not_in_string(format_str,var)+(int)strlen(var),(int)strlen(format_str));
                //format_str= substr(format_str,find_not_in_string(format_str,var))
                //printf("var is |%s| var index is |%s|\n",var,var_index);
                if (strcmp(var, var_index) == 0) {
                    return output_value;
                }
                break;
                //continue;
            }
            
            bool begin_count=FALSE;
            for (j = 0; j < num_of_ori; j++) {
                char *sentence_at_ori = sentenceAtIndexOfString(original_str, j);
                if (find_var==FALSE && strcmp(sentence_at_ori, sentence_at_for) == 0 ||find_not_in_string(sentence_at_for,"VAR")!=-1) {
                    begin = find_not_in_string(original_str, sentence_at_ori);
                    begin = begin + (int) strlen(sentence_at_ori);
                    last_j=j;
                    begin_count=TRUE;
                    continue;
                }
                if(strcmp(sentence_at_ori,sentence_at_for)!=0 && begin_count==TRUE)
                    break;
            }
        }
    
        index++;
    }
    return "None";
   
}
*/
/*
 * This function could change "print 'Hello'" to "PRINT VAR[1]"
 * And will not let you judge.
 * It will use __walley_language_verb__.wy to make verb unchange....
 *//*
char *Walley_Analyze_Sentence_Automatically(struct VAR struct_var[], char **walley_language_similarity_file, char **walley_language_verb_file, char *input_str) {
   //// printf("#### Walley_Analyze_Sentence_Automatically ####\n");
    input_str = trim(input_str);
    if (find_not_in_string(input_str, " the ")!=-1) {
        input_str=replace_not_in_string(input_str, " the ", " ");
    }
    input_str = cleanUpSentence(input_str);
   // printf("After clean up |%s|\n",input_str);
    int num = numOfSmallSentences(input_str);
    int index = 0;
    char temp[10000] = "";
    bool find_var_and_not_interrupted = FALSE;
    //int var_index=1;

    // Check Similarity
    bool similar = FALSE;
    char *compare_to;
    int row=0;
    while (walley_language_similarity_file[row]!= NULL) {
        char *arr=walley_language_similarity_file[row];
        if(find_not_in_string(arr,"|")==-1||trim(arr)[0]=='#'){
            row++;
            continue;
        }
        compare_to = substr(arr, 0, find_not_in_string(arr, "|"));
        int similarity_required = atoi(substr(arr, find_not_in_string(arr, "|") + 1, find_from_index_not_in_string(arr, "|", find_not_in_string(arr, "|") + 1)));
        //printf("compare to %s, similarity %d\n",compare_to,similarity_required);
        int similarity = Walley_Find_Similarity_Between_Two_Str(input_str, compare_to);
        //printf("similar %d\n",similarity);
        if (similarity_required == similarity) {
            similar = TRUE;
           //// printf("Find Similar Sentence\n");
            break;
        }
        row++;

    }
    if (similar == TRUE) {
        return compare_to;
    } else {
        bool find_if=FALSE;
       // printf("Come Here\n");
       // printf("Num %d\n",num);
        for (index = 0; index < num; index++) {
            char *string_at_index = sentenceAtIndexOfString(input_str, index);
            bool var_existed = Var_Existed(struct_var,  string_at_index);
            bool func_existed = checkWhetherSameFunctionNameExistsFromVar(string_at_index);
            bool is_verb = checkWhetherSameVerbExistedFromStrList(walley_language_verb_file, stringToLowerCase(string_at_index));
            char *var_type = variableValueType(string_at_index);
            //string_at_index=trim(string_at_index);
           // printf("string_at_index-->|%s|\n",string_at_index);
            
            if (strcmp("IF", stringToUpperCase(string_at_index))==0||
                strcmp("ELSE", stringToUpperCase(string_at_index))==0||
                strcmp("ELIF", stringToUpperCase(string_at_index))==0){
                find_if=TRUE;
            }
            
            //if ((strcmp(string_at_index, ",") == 0 || strcmp(string_at_index, "and") == 0) && find_var_and_not_interrupted == TRUE) {
            if (strcmp(string_at_index, ",") == 0  && find_var_and_not_interrupted == TRUE) {
                continue;
            }
            if (strcmp(stringToUpperCase(string_at_index),"AND")==0 && find_var_and_not_interrupted == TRUE) {
                if (find_if==FALSE) {
                    continue;
                }
                else{
                    strcat(temp, string_at_index);
                    strcat(temp, " ");
                    find_var_and_not_interrupted=FALSE;
                }
            }
            if (var_existed == TRUE || func_existed == TRUE) {
                //strcat(temp," ");
                strcat(temp, "VAR");
                strcat(temp, " ");
                find_var_and_not_interrupted = TRUE;
                continue;
            } else if (strcmp(var_type, "list") == 0 || strcmp(var_type, "dictionary") == 0 || strcmp(var_type, "string") == 0) {
                //||stringIsDigit(string_at_index)){
                if (find_var_and_not_interrupted == TRUE)
                    continue;
                else {
                    //strcat(temp, " ");
                    strcat(temp, "VAR");
                    strcat(temp, " ");
                    find_var_and_not_interrupted = TRUE;
                    continue;
                }
            } else if (is_verb == TRUE ||
                    strcmp(string_at_index, "(") == 0 ||
                    strcmp(string_at_index, ")") == 0 ||
                    strcmp(string_at_index, ":") == 0 ||
                    strcmp(stringToUpperCase(string_at_index), "IF") == 0 ||
                    strcmp(stringToUpperCase(string_at_index), "DEF") == 0 ||
                    strcmp(stringToUpperCase(string_at_index), "ELIF") == 0 ||
                    strcmp(stringToUpperCase(string_at_index), "ELSE") == 0 ||
                    strcmp(stringToUpperCase(string_at_index), "WHILE") == 0 ||
                    strcmp(stringToUpperCase(string_at_index), "FOR") == 0 ||
                    strcmp(stringToUpperCase(string_at_index), "CLASS") == 0) {
                strcat(temp, string_at_index);
                strcat(temp, " ");
                find_var_and_not_interrupted = FALSE;
            } else {
                if (find_var_and_not_interrupted == TRUE)
                    continue;
                else {
                    //strcat(temp, " ");
                    strcat(temp, "VAR");
                    strcat(temp, " ");
                    find_var_and_not_interrupted = TRUE;
                    continue;
                }
            }




        }
        int i = 0;
        char *output = malloc(sizeof (char) *((int) strlen(temp) + 1));
        for (i = 0; i < (int) strlen(temp); i++) {
            output[i] = temp[i];
        }
        output[(int) strlen(temp)] = 0;
        output = substr(output, 0, (int) strlen(temp));
        output = trim(output);
        output = stringToUpperCase(output);
        return output;
    }
}*/
// changeStringAtIndex("Hello yiyi", "Ilikeyou", 0)--->"Ilikeyou yiyi"
/*
char *changeStringAtIndex(char *input_str, char *change_to_str, int change_index){
    //printf("#### sentenceAtIndexOfString ####\n");
    //printf("input_str |%s|, index |%d|\n",input_str,index);
    input_str=trim(input_str);
    input_str=cleanUpSentence(input_str);
    //printf("input_str |%s|\n",input_str);
    //printf("Num --> %d",numOfSmallSentences(input_str));
    if(change_index>=numOfSmallSentences(input_str)){
        printf("Mistake occurred whiling calling function sentenceAtIndexOfString\nIndex out of bound\ninput_str |%s|\n",input_str);
        exit(0);
    }
    //printf("---->|%s|\n",input_str);
    int begin=0;
    int end=0;
    int i=0;
    for(i=0;i<change_index;i++){
        begin=find_from_index_not_in_string(input_str," ",begin+1);
    }
    end=find_from_index_not_in_string(input_str," ",begin+1);
    if(begin!=-1 && end==-1){
        end=(int)strlen(input_str);
    }
    
    //printf("begin %d, end %d\n",begin,end);
    //printf("|%s|\n",trim(substr(input_str,begin,end)));
    char *output=trim(substr(input_str,begin,end));
    
    output=replace_from_index_to_index(input_str, output, change_to_str, begin, end);
    
    //printf("End sentenceAtIndexOfString\n");
    return output;
    

}
*/

// Walley_Analyze_Sentence_By_Known_Variable("add a b","b,a")-------->"add VAR2 VAR1"
/*
char *Walley_Analyze_Sentence_By_Known_Variable(char *input_str, char *temp_function_parameter){
    if (strcmp(temp_function_parameter, "None")==0) {
        return input_str;
    }
    else{
     
        char *parameter_list=append("[", temp_function_parameter);
        parameter_list=append(parameter_list, "]");
        int num_of_list=valueNumOfList(parameter_list);
        int i=0;
        int count=1;
        for (i=0; i<num_of_list; i++) {
            char *element_at_i_index=valueOfListAtIndex(parameter_list, i);
            int num_of_small_sentence=numOfSmallSentences(input_str);
            int j=0;
            for (j=0; j<num_of_small_sentence; j++) {
                char *sentence=sentenceAtIndexOfString(input_str,j);
                if (strcmp(element_at_i_index, sentence)==0) {
                    input_str=changeStringAtIndex(input_str,append("VAR", intToCString(count)),j);
                    count++;
                }
            }
        }
        return input_str;
    }
}*/

/*
void Walley_Write_Language_To_Language_File(char *walley_language_file, char *translate_str, char *to_str){
    char *input=malloc(sizeof(char)*((int)strlen(translate_str)+(int)strlen(to_str)+4));
    strcpy(input,"\n");
    strcat(input,translate_str);
    strcat(input,"|");
    strcat(input,to_str);
    strcat(input,"|");
    input[(int)strlen(translate_str)+(int)strlen(to_str)+3]=0;
   //// printf("Input |%s|\n",input);
    writeStringToFile(walley_language_file,input);
    cleanWalleyLanguageFile(walley_language_file);
}*/


/*
// Translate print "hello world" to print("Hello World")

char *Walley_Translate(char **walley_language_file, char **walley_language_similarity_file, char **walley_language_verb_file, struct VAR struct_var[], char *input_str) {
   // printf("#### Walley_Translate ####\n");
   //// printf("----> %s\n", input_str);
    input_str = cleanUpSentence(input_str);
    
    if(stringIsEmpty(input_str)){
        return "";
    }
    else if (removeAheadSpace(input_str)[0]=='#'){
        return input_str;
    }
    else if (find_not_in_str_list_dict_parenthesis(input_str, "~#")!=-1){
        return input_str;
    }
    
    //printf("----> %s\n", input_str);
    int num_of_space_ahead=numOfSpaceAheadString(input_str);
   //// printf("num of space ahead is %d\n",num_of_space_ahead);
    input_str = trim(input_str);
   // printf("----> %s\n", input_str);

    if(find_not_in_string(input_str, " the ")!=-1)
        input_str=replace_not_in_string(input_str," the "," ");
    
    
    // Solve if else if elif else sentence problem
    char *temp_first_str=sentenceAtIndexOfString(input_str, 0);
    temp_first_str=stringToUpperCase(temp_first_str);
    if (strcmp("IF", temp_first_str)==0||
        strcmp("ELSE",temp_first_str)==0||
        strcmp("ELIF", temp_first_str)==0||
        strcmp("FOR", temp_first_str)==0||
        strcmp("WHILE",temp_first_str)==0) {
       //// printf("It is if else elif for while sentence\n");
        char *output=append(temp_first_str," ");
        int i=1;
        int num_of_sentences=numOfSmallSentences(input_str);
        for (i=1; i<num_of_sentences; i++) {
            char *string_at_index=sentenceAtIndexOfString(input_str, i);
            string_at_index=Walley_Translate(walley_language_file, walley_language_similarity_file, walley_language_verb_file, struct_var, string_at_index);
            output=append(output, string_at_index);
            output=append(output, " ");
        }
        output=cleanUpSentence(output);
        char *output2=malloc(sizeof(char)*((int)strlen(output)+num_of_space_ahead+1));
        int a=0;
        //// printf("num of space ahead is %d\n",num_of_space_ahead);
        for(a=0;a<num_of_space_ahead;a++){
            strcat(output2," ");
        }
        strcat(output2,output);
        output2[(int)strlen(output2)]=0;
        //return change_to_string;
    
        return output2;
    }
    else {
       // printf("HERE\n");
    //char *format_string=Walley_Analyze_Sentence(file_var_name,input_str);
    
    //char *brain_path="/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/";
    //char *walley_language_similarity_file=append(brain_path, "__walley_language_similarity__.wy");
    //char *walley_language_verb_file=append(brain_path, "__walley_language_verb__.wy");
    
    //char *format_string = Walley_Analyze_Sentence_Automatically(struct_var,walley_language_similarity_file,walley_language_verb_file, input_str); //--> PRINT VAR
        char *format_string = Walley_Analyze_Sentence_Automatically(struct_var,walley_language_similarity_file,walley_language_verb_file, input_str); //--> PRINT VAR
       // printf("HERE\n");
       // printf("format_string %s\n", format_string);
        char *change_to_string = Walley_Compare_Sentence_From_Memory(walley_language_file, format_string); //-->PRINT ( VAR )
       // printf("HERE2\n");

       // printf("input str %s\n",input_str);
       // printf("format_string %s\n", format_string);
       // printf("change to str %s\n",change_to_string);

    if (strcmp(change_to_string, "None") == 0) {
        printf("Sorry, I can not understand what you mean!\nYou can teach me.\n");
        printf("There are some similar sentence, from which may existed some you want similarly\n\n");

        printf("Input_str is %s\nformat_string is %s\n", input_str, format_string);
        printf("Do you think the fomat_string is a good kind of formating?\nY/N??\n");
        char *answer = malloc(sizeof (char) *10);
        //answer="";
        gets(answer);
        //char answer[100];
        //scanf("%s",&answer);
        printf("ANSWER IS %s\n",answer);
        answer = stringToUpperCase(answer);
        printf("ANSWER IS %s\n",answer);
        if (strcmp(answer, "Y") == 0 || strcmp(answer, "YES") == 0) {
            printf("Okay, now go on....\n");
            int similarity[10000];
            int row = 0;
            int row_for_walley_language_file=0;
            while (walley_language_file[row_for_walley_language_file] != NULL) {
                char *arr=walley_language_file[row_for_walley_language_file];
                if (find_not_in_string(arr, "|") == -1){
                    row_for_walley_language_file++;
                    continue;
                }
                char *change = substr(arr, 0, find_not_in_string(arr, "|"));
                int sim = Walley_Find_Similarity_Between_Two_Str(format_string, change);
                //if(sim==1)
                //    continue;
                if (sim<=1) {
                    row_for_walley_language_file++;
                    continue;
                }
                similarity[row] = sim;
                row = row + 1;
                row_for_walley_language_file++;
            }
            //fclose(fp);
            int row2 = 0;
            //for(row2=0;row2<row;row2++){
            //    printf("row %d --->%d\n",row2,similarity[row2]);
            //}
            int max = similarity[0];
            int max_lines[10000];
            int row3 = 0;
            for (row2 = 0; row2 <= row; row2++) {
                if (max < similarity[row2]) {
                    max = similarity[row2];
                    int temp = 0;
                    for (temp = 0; temp < row3; temp++) {
                        max_lines[temp] = 0;
                    }
                    row3 = 0;
                    //printf("%d Equal row2 %d row3 %d\n\n",max,row2,row3);
                    max_lines[row3] = row2;
                    row3 = row3 + 1;
                    continue;
                } else if (max == similarity[row2]) {
                    //printf("%d Equal row2 %d row3 %d\n\n",max,row2,row3);
                    max_lines[row3] = row2;
                    row3 = row3 + 1;
                }
                //printf("-- row %d, row3 %d\n",row2,row3);
            }
            row3 = row3 - 1;
            //printf("row3 %d\n",row3);
           // printf("Max is %d\n",max);
            int temp = 0;
            //for(temp=0;temp<=row3;temp++){
            //    printf("\nMax at row %d row3 %d\n\n",max_lines[temp],row3);
            //}

            //fp = fopen(walley_language_file, "r");
            //char arr[1000] = "";
            //memset(arr, 0, sizeof (arr));
            row = 0;
            row_for_walley_language_file=0;
            int count = 1;
            //while ((fgets(arr, 1000, fp)) != NULL) {
            while (walley_language_file[row_for_walley_language_file]!=NULL) {
                char *arr=walley_language_file[row_for_walley_language_file];
                if (find_not_in_string(arr, "|") == -1){
                    row_for_walley_language_file++;
                    continue;
                }
                for (temp = 0; temp <= row3; temp++) {
                    //printf("temp %d row %d\n",temp,row);
                    if (max_lines[temp] == row) {
                        // This print can not be annotated
                        printf("%d----> %s\n", count, arr);
                        count++;
                        //break;
                    }
                }
                row_for_walley_language_file++;
                row++;
            }
            
            
            int which_line = 0;
            printf("Please enter the one that match what you mean the best\nIf no one match your idea, please enter 0.\nWhich Line?-------->\n");
            scanf("%d", &which_line);
            if (which_line != 0) {
                printf("Okay, I understand what you mean!\nThinking in Progress.....");
                //char *to_string;
                //fp = fopen(walley_language_file, "r");
                //char arr[1000] = "";
                //memset(arr, 0, sizeof (arr));
                row = 0;
                char *to_string;
                //while ((fgets(arr, 1000, fp)) != NULL) {
                row_for_walley_language_file=0;
                while (walley_language_file[row_for_walley_language_file] != NULL) {
                    char *arr=walley_language_file[row_for_walley_language_file];
                    if (find_not_in_string(arr, "|") == -1){
                        row_for_walley_language_file++;
                        continue;
                    }
                    if (max_lines[count - 2] == row) {
                        char *temp_to_string = substr(arr, find_not_in_string(arr, "|") + 1, find_from_index_not_in_string(arr, "|", find_not_in_string(arr, "|") + 1));
                        to_string = malloc(sizeof (char) *((int) strlen(temp_to_string) + 1));
                        int o = 0;
                        for (o = 0; o < (int) strlen(temp_to_string); o++) {
                            to_string[o] = temp_to_string[o];
                        }
                        to_string[(int) strlen(to_string)] = 0;
                        break;
                    }
                    row_for_walley_language_file++;
                    row++;
                }
                //fclose(fp);
                char *temp_to_add=append(format_string, "|");
                temp_to_add=append(temp_to_add, to_string);
                temp_to_add=append(temp_to_add, "|");
                Str_addString(&walley_language_file, temp_to_add);
                //Walley_Write_Language_To_Language_File(walley_language_file, format_string, to_string);
                Walley_Write_Language_To_Language_File(append(BRAIN_PATH, "__walley_language__.wy"), format_string, to_string);
                return Walley_Translate(walley_language_file, walley_language_similarity_file,walley_language_verb_file,struct_var, input_str);
            } else {
                printf("Since no sentence satisfied your demand, you could create the sentence for your self!\n");
                printf("Now your translated language form is %s\nWhat do you want it to be translated to?\n", format_string);
                char *translate_to = malloc(sizeof (char) *100);
                printf("");
                //scanf("%s",&translate_to);
                gets(translate_to);
                while (TRUE) {
                    printf("--------->");
                    //memset(translate_to, 0, sizeof (translate_to));
                    //scanf("%s",&translate_to);
                    gets(translate_to);
                    printf("So now we want to \ntranslate:|%s|\nto       :|%s|\n", format_string, translate_to);
                    printf("Do you want me to memorize that?? Y/N/EXIT?\n");
                    char *answer = malloc(sizeof (char) *10);
                    //scanf("%s",&answer);
                    gets(answer);
                    answer = stringToUpperCase(answer);
                    if (strcmp(answer, "Y") == 0 || strcmp(answer, "YES") == 0) {
                        printf("You answered YES\n");
                        //Walley_Write_Language_To_Language_File(walley_language_file, format_string, translate_to);
                        char *temp_to_add=append(format_string, "|");
                        temp_to_add=append(temp_to_add, translate_to);
                        temp_to_add=append(temp_to_add, "|");
                        Str_addString(&walley_language_file, temp_to_add);
                        Walley_Write_Language_To_Language_File(append(BRAIN_PATH, "__walley_language__.wy"), format_string, translate_to);
                        
                        return Walley_Translate(walley_language_file, walley_language_similarity_file,walley_language_verb_file,struct_var, input_str);
                        break;
                    } else if (strcmp(answer, "EXIT") == 0) {
                        exit(0);
                    }
                }

            }
        } else {
            printf("Now I will make a format for your input string\nplease follow the order\n");
            char *true_format=Walley_Analyze_Sentence_Manually(input_str);
            int num_of_true_format=numOfSmallSentences(true_format);
            num_of_true_format-=count_str_not_in_string(true_format,"VAR");
            
            char temp_str[1000]="";
            sprintf(temp_str,"%d",num_of_true_format);
            
            char *temp_walley_similarity_file_path=append(BRAIN_PATH, "__walley_language_similarity__.wy");
            //writeStringToFile(walley_language_similarity_file,true_format);
            //writeStringToFile(walley_language_similarity_file,"|");
            //writeStringToFile(walley_language_similarity_file,temp_str);
            //writeStringToFile(walley_language_similarity_file,"|\n");
            
            char *temp_to_add=append(true_format, "|");
            temp_to_add=append(temp_to_add, temp_str);
            temp_to_add=append(temp_to_add, "|");
            Str_addString(&walley_language_similarity_file, temp_to_add);
            
            writeStringToFile(temp_walley_similarity_file_path,true_format);
            writeStringToFile(temp_walley_similarity_file_path,"|");
            writeStringToFile(temp_walley_similarity_file_path,temp_str);
            writeStringToFile(temp_walley_similarity_file_path,"|\n");
            cleanWalleyLanguageFile(temp_walley_similarity_file_path);
            
            return Walley_Translate(walley_language_file,walley_language_similarity_file,walley_language_verb_file, struct_var, input_str);
        }
    }

    else {

        char *var_list=getVarIndexStringAsList(format_string);
       // printf("var_list is %s\n",var_list);
        int num_of_var=valueNumOfList(var_list);
        int index=0;
        input_str=stringToUpperCase(input_str);
        for(index=0;index<num_of_var;index++){
            char *var=valueOfListAtIndex(var_list,index);
            //printf("VAR--------> |%s|\n",var);
            //printf("INPUT------> |%s|\n",input_str);
            char *value=getValueFromVarIndex(input_str,format_string,var);
            ////printf("VALUE IS %s\n",value);
            int index_of_var=find_not_in_string(change_to_string,var);
            int to_index=index_of_var+(int)strlen(var);
            change_to_string=replace_from_index_to_index(change_to_string,var,value,index_of_var,to_index);
            
            ////printf("Change_to_string is %s\n",change_to_string);
            
            int index_of_value=find_not_in_string(input_str,value);
            int to_index2=index_of_value+(int)strlen(value);
            input_str=replace_from_index_to_index(input_str,value,"",index_of_value,to_index2);
            if(find_not_in_string(input_str,"  ")!=-1)
                input_str=replace_not_in_string(input_str,"  "," ");
            input_str=trim(input_str);
            
            int index_of_var2=find_not_in_string(format_string,var);
            int to_index3=index_of_var2+(int)strlen(var);
            format_string=replace_from_index_to_index(format_string,var,"",index_of_var2,to_index3);
            format_string=trim(format_string);
        }
    }
    
    
    char *output=malloc(sizeof(char)*((int)strlen(change_to_string)+num_of_space_ahead+1));
    int i=0;
    for(i=0;i<num_of_space_ahead;i++){
        strcat(output," ");
    }
    strcat(output,change_to_string);
    output[(int)strlen(output)]=0;
    //return change_to_string;
    return output;
    }
}*/

/*
 * addOneSentenceWalleyLangaugeSimilarityFile("__walley_langauge_similarity__.wy","VAR IS VAR 2|3|")
 * insert "VAR IS VAR 2|3|" to file
 *
void addOneSentenceWalleyLangaugeSimilarityFile(char *file_name,char *add_sentence){
    printf("file_name is %s\n",file_name);
    FILE *fp=fopen(file_name, "r");
    char arr[10000];
    if (fp==NULL) {
        printf("No File %s Found\n",file_name);
        exit(0);
    }
    
    char *string_in_file[10000];
    int count=0;
    
    while (fgets(arr, 10000, fp)!=NULL) {
        if (stringIsEmpty(arr)==TRUE) {
            continue;
        }
        //printf("--->%s count-->%d\n",arr,count);
        char *to_copy;
        if (arr[(int)strlen(arr)-1]=='\n') {
            to_copy=substr(arr, 0, (int)strlen(arr)-1);
        }else {
            to_copy=substr(arr, 0, (int)strlen(arr));
        }
        string_in_file[count]=to_copy;
        count++;
    }
    fclose(fp);
    int i=0;
    bool find_place=FALSE;
    for(i=0;i<count-1;i++){
        //printf("|%s|\n",string_in_file[i]);
        if (string_in_file[i][0]=='#') {
            continue;
        }
        if (strcmp(add_sentence, string_in_file[i])>0 && strcmp(add_sentence, string_in_file[i+1])<0) {
            printf("Find the place to insert..\n");
            printf("Add sentence %s\nAfter %s\nAhead %s\n\n\n",add_sentence,string_in_file[i],string_in_file[i+1]);
            find_place=TRUE;
        }
    }
}
*/

// ("add 1 2","add num1 num2")=1 ("hello world","world hello")=0  compare in order.
int Walley_Find_Similarity_Between_Two_Str_In_Order(char *sentence1, char *sentence2){
    int num_sentence_of_sentence1=numOfSmallSentences(sentence1);
    int num_sentence_of_sentence2=numOfSmallSentences(sentence2);
    if (num_sentence_of_sentence1!=num_sentence_of_sentence2) {
        return 0;
    }
    int i=0;
    int similarity=0;
    for (i=0; i<num_sentence_of_sentence1; i++) {
        char *sentence1_element=sentenceAtIndexOfString(sentence1, i);
        char *sentence2_element=sentenceAtIndexOfString(sentence2, i);
        if (strcmp(sentence1_element, sentence2_element)==0) {
            similarity++;
        }
    }
    return similarity;
}

// the string in expresion should be "function|expression" kind
// ("add 1,2","{{add num1 num2},{add num1 num2 num3}}")------>add num1 num2
char *bestMathSentenceForExpression(char *input_sentence, char **expression){
    int i=0;
    input_sentence=cleanUpSentence(input_sentence);
    int num_of_small_sentence_of_input_sentence=numOfSmallSentences(input_sentence);
    char *return_sentence="None";
    int similarity=0;
    int length_of_expression=atoi(expression[0]);
    while (i<length_of_expression) {
        
        char *sentence;
        if (find(expression[i], "|")==-1) {
            sentence=expression[i];
        }
        else{
            sentence=substr(expression[i], find(expression[i], "|")+1, (int)strlen(expression[i]));
        }
        
        int num_of_expression_sentence=numOfSmallSentences(sentence);
        if (num_of_expression_sentence==num_of_small_sentence_of_input_sentence) {
            int simi=Walley_Find_Similarity_Between_Two_Str_In_Order(input_sentence, sentence);
            if (simi>similarity) {
                similarity=simi;
                return_sentence=expression[i];
            }
        }
        else{
            i++;
            continue;
        }
        
        i++;
    }
    return return_sentence;
}

/*
 * ("add 1 2","add(num1,num2)|add num1 num2")
 */
char *Walley_Translate_To_Function(char *input_str, char *best_match_sentence){
    int index_of_gang=find(best_match_sentence, "|");
    if (index_of_gang==-1) {
        printf("Mistake occurred while calling function Walley_Translate_To_Function\n best_match sentence error, |%s|\n",best_match_sentence);
        printf("it should be in format function|expression \n");
        exit(0);
    }
    char *function=substr(best_match_sentence, 0, index_of_gang);
    char *expression=substr(best_match_sentence, index_of_gang+1, (int)strlen(best_match_sentence));
    int num_of_small_sentence=numOfSmallSentences(input_str);
    int i=0;
    char *output=append(function, "(");
    for (i=0; i<num_of_small_sentence; i++) {
        char *sentence_at_input_str=sentenceAtIndexOfString(input_str, i);
        char *sentence_at_expression=sentenceAtIndexOfString(expression, i);
        if (strcmp(sentence_at_expression, sentence_at_input_str)!=0) {
            output=append(output, sentence_at_expression);
            output=append(output, "=");
            output=append(output, sentence_at_input_str);
            if (i!=num_of_small_sentence-1) {
                output=append(output, ",");
            }
        }
    }
    output=append(output, ")");
    return output;
}


