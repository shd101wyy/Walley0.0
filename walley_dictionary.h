/* 
 * File:   walley_dictionary.h
 * Author: shd101wyy
 *
 * Created on August 31, 2012, 9:59 PM
 */

#include "walley_list.h"
/*
 * 
Dictionary

Init 
a={}
a{"hello"}=1
a{"hi"}=2

a={"hello":1,"hi":2}


Format
a:{"hello":1,"hi":2}:dictionary
#~Begin:a:
a{"hello"}=1
a{"hi"}=2
#~End:a:

 * format:    
dic:{a:1,b:{c:1,d:2}}:dictionary:
#~Begin:dic:
dic{a}:1:int:
dic{b}:{c:1,d:2}:dictionary:
#~Begin:dic{b}:
dic{b}{c}:1:int:
dic{b}{d}:2:int:
#~End:dic{b}:
#~End:dic:

Declare
a{"hi"}=2
// do not forget a{'hi'} is the same

Change Value
the same as above

a.key()=["hello","hi"];

 * */
/*
 * eg valueAtKey("{'Hello':11,'Hi':2}","'Hello'")---->11
 */
char* valueAtKey(char *dictionary, char *key){
   //// printf("#### valueAtKey ####\n");
   //// printf("%s, %s\n",dictionary,key);
    if(find(dictionary,key)==-1|| find(dictionary,"{")==-1 || find(dictionary,"}")==-1){
        printf("Mistake occurred while calling function valueAtKey\nkey %s did not find in dictionary %s\n",key,dictionary);
        exit(1);
    } else {
        char *value;
        if(find_from_index_not_in_string(dictionary,",",find(dictionary,key))!=-1){
                value=substr(dictionary,find_from_index_not_in_string(dictionary,":",find(dictionary,key))+1,find_from_index_not_in_string(dictionary,",",find(dictionary,key)));
        } else {
                value=substr(dictionary,find_from_index_not_in_string(dictionary,":",find(dictionary,key))+1,find_from_index_not_in_string(dictionary,"}",find(dictionary,key)));
        }
        value=removeAheadSpace(removeBackSpace(value));
        return value;
    }
    
}

/*
 * eg keyOfDictionaryAsList("{a:1,b:2}")----->[a,b]
 */
char *keyOfDictionaryAsList(char *dictionary){
    if(strcmp(dictionary,"{}")==0)
        return "[]";
   //// printf("#### keyOfDictionaryAsList ####\ninput |%s|\n",dictionary);
    if(find(dictionary,"{")==-1 || find(dictionary,"}")==-1){
        printf("Mistake occurred while calling function keyOfDictionaryAsList\ndictionary %s mistake\n",dictionary);
        exit(1);
    }
    dictionary=trim(dictionary);
    
    dictionary=append(",", substr(dictionary, 1, (int)strlen(dictionary)));
    
    int i=0;
    bool find_key=FALSE;
    char output[1000]="";
    int begin=0;
    int end=0;
    strcpy(output,"[");
    for(i=0;i<(int)strlen(dictionary);i++){
        bool in_dict=FALSE;
        if(count_str(substr(dictionary,0,i+1),"{")!=count_str(substr(dictionary,0,i+1),"}"))
            in_dict=TRUE;
        //printf("%d-->%c--->%d\n",i,dictionary[i],in_dict);
        if(find_key==FALSE && dictionary[i]==',' && charIsInString(dictionary,i)==FALSE && in_dict==FALSE){
            find_key=TRUE;
            begin=i+1;
        }
        
        if(find_key==TRUE && dictionary[i]==':' && charIsInString(dictionary,i)==FALSE && in_dict==FALSE){
            find_key=FALSE;
            end=i;
            strcat(output,substr(dictionary,begin,end));
            strcat(output,",");
        }
        
    }
    dictionary[0]='{';
    char *output2=(char*)malloc(sizeof(char)*((int)strlen(output)+1));
    for(i=0;i<(int)strlen(output)-1;i++){
        output2[i]=output[i];
    }
    output2[(int)strlen(output)-1]=']';
    output2[(int)strlen(output)]=0;
    
    return output2;
}
/*
 * get the num of key
 * eg numOfDictionaryKey("{'Hello':11,'Hi':2}","'Hello'")---->2 ge
 */
int numOfDictionaryKey(char *dictionary){
    //printf("#### numOfDictionaryKey ####\n");
    char *list=keyOfDictionaryAsList(dictionary);
    return valueNumOfList(list);
}

//#################### valueOfDictionaryAtKeyString##########
/*eg valueOfDictionaryAtKeyString("{a:1,b:{c:1,d:2},e:20}","{a}")---->1
 *   valueOfDictionaryAtKeyString("{a:1,b:{c:1,d:2},e:20}","{b}{d}")---->2
 * 
 */
char *valueOfDictionaryAtKeyString(char *dict,char *key_str){
    // printf("#### valueOfDictionaryAtKeyString ####\n");
    // printf("dict |%s|\n, key_str |%s|\n",dict,key_str);
    dict=removeAheadSpace(removeBackSpace(dict));
    if(find(dict,"{")==-1 || find(dict,"}")==-1){
        printf("Mistake occurred while calling function valueOfDictionaryAtKeyString\nInput %s is not a dict\n",dict);
        exit(0);
    }
    if(count_str(dict,"{")!=count_str(dict,"}")){
        printf("Mistake occurred while calling function valueOfDictionaryAtKeyString\nInput %s is not a list because the num of { and } is different\n",dict);
        exit(0);  
    }
    int i=0;
    char *key;
    char *value;
    int num=count_str(key_str,"{");
    for(i=0;i<num;i++){
        key=substr(key_str,find(key_str,"{")+1,find(key_str,"}"));
        if(find(dict,key)==-1){
            printf("Mistake occurred while calling function valueOfDictionaryAtKeyString\nkey %s in dictionary %s not found\n",key,dict);
            exit(1);
        }
        if(find_from_index_not_in_string(dict,"{",find(dict,key))!=-1 && find_from_index_not_in_string(dict,"{",find(dict,key)) < find_from_index_not_in_str_list_dict(dict,",",find(dict,key))){
            value=substr(dict,find_from_index_not_in_string(dict,"{",find(dict,key)),find_from_index_not_in_string(dict,"}",find(dict,key))+1);
        } else {
            if(find_from_index_not_in_str_list_dict(dict,",",find(dict,key))!=-1)
                value=substr(dict,find_from_index_not_in_string(dict,":",find(dict,key))+1,find_from_index_not_in_str_list_dict(dict,",",find(dict,key)));
            else
                value=substr(dict,find_from_index_not_in_string(dict,":",find(dict,key))+1,(int)strlen(dict)-1);
        }
        key_str=substr(key_str,find(key_str,"}{")+1,(int)strlen(key_str));
        dict=value;
        //printf("---->value %s\n",value);
    }
    return value;
}
/*
 * eg dictionaryAddKeyAndValue("{a:1,b:2,c:12}","d","13")------>{a:1,b:2,c:12,d:13}
 */
char *dictionaryAddKeyAndValue(char *dictionary, char *key, char *value){
    dictionary=removeAheadSpace(removeBackSpace(dictionary));
    char *output=(char*)malloc(sizeof(char)*((int)strlen(dictionary)+(int)strlen(key)+(int)strlen(value)+3));
    strcpy(output,substr(dictionary,0,(int)strlen(dictionary)-1));
    strcat(output,",");
    strcat(output,key);
    strcat(output,":");
    strcat(output,value);
    strcat(output,"}");
    //may have problem here
    output[(int)strlen(dictionary)+(int)strlen(key)+(int)strlen(value)+2]=0;
    
    if(find_not_in_string(output,"{,")!=-1)
        output=replace_not_in_string(output,"{,","{");
    return output;
}

/*
 * eg dictionaryAddKeyAndValueInStringOrChangeOriginalValueByKey("{a:1,b:2,c:12}","{d}","13")------>{a:1,b:2,c:12,d:13}
 * eg dictionaryAddKeyAndValueInStringOrChangeOriginalValueByKey("{a:1,b:2,c:12}","{d}{e}","13")------>{a:1,b:2,c:12,d:{e:13}}
 * eg dictionaryAddKeyAndValueInStringOrChangeOriginalValueByKey("{a:1,b:{o:2},c:12}","{b}{f}","13")------>{a:1,b:{o:2,f:13},c:12,d:13}
 * eg dictionaryAddKeyAndValueInStringOrChangeOriginalValueByKey("{a:1}","{a}","13")---->"{a:13}"
 */
//I just find that this function has a lot of problem....
char *dictionaryAddKeyAndValueInStringOrChangeOriginalValueByKey(char *dictionary, char *key, char *value){
   // printf("#### dictionaryAddKeyAndValueInStringOrChangeOriginalValueByKey ####\n");
   // printf("## Dictionary %s\n#### key %s\n#### value %s\n",dictionary,key,value);
    int length=(int)strlen(dictionary);
    char *temp=(char*)malloc(sizeof(char)*(length+4));
    strcpy(temp,"XX:");
    strcat(temp,dictionary);
    temp[length+3]=0;
    dictionary=temp;
    char *key_copy=key;
    if(find_not_in_string(key,"}{")!=-1){
        key=replace_not_in_string(key,"}{",",");
    }
 
    key=replace_not_in_string(key,"{","");
    key=replace_not_in_string(key,"}",",");//{a}{b}---->a,b, {a}----->a,
    dictionary=trim(dictionary);

    int i=0;
    int begin=0;
    int count_of_douhao=count_str_not_in_string(key,",");
   
    
    bool existed=TRUE;
    char *last_key="XX";
    char *temp_dict;
    char *output2;
    char *final_key;
    for(i=0;i<count_of_douhao;i++){
        char *temp_key=substr(key,begin,find_from_index_not_in_string(key,",",begin)); // a,b,---->a
        char *temp=(char*)malloc(sizeof(char)*((int)strlen(temp_key)+2));
        strcpy(temp,temp_key);
        strcat(temp,":");
        temp[(int)strlen(temp_key)+1]=0;
        temp=trim(temp);
        if(find_not_in_string(dictionary,temp)!=-1){
            last_key=temp;
        }
        else{
            existed=FALSE;
          
            int begin_of_left=find_not_in_string(dictionary,last_key)+(int)strlen(last_key);

            begin_of_left=find_from_index_not_in_string(dictionary, "{",begin_of_left);
            
            int end_of_last_right=find_from_index_not_in_string(dictionary,"}",begin_of_left);
            while (TRUE) {
                char *temp_str=substr(dictionary, begin_of_left, end_of_last_right+1);
                if (count_str_not_in_string(temp_str, "{")==count_str_not_in_string(temp_str, "}")) {
                    break;
                }
                else{
                    end_of_last_right=find_from_index_not_in_string(dictionary, "}",end_of_last_right+1);
                }
            }

            
            temp_dict=substr(dictionary,begin_of_left,end_of_last_right+1);

            // eg if b:2 is not in XX:{a:2}------> temp_dict={a:2}
            int j=i;
            char *temp_temp=substr(temp_dict,0,(int)strlen(temp_dict)-1);
                //{a:2}----->{a:2
            char output[1000]="";
            strcpy(output,temp_temp);
            for (j = i; j < count_of_douhao; j++) {
                char *temp_key2 = substr(key, begin, find_from_index_not_in_string(key, ",", begin)); // a,b,---->a
                char *temp2 =(char*) malloc(sizeof (char) *((int) strlen(temp_key2) + 2));
                strcpy(temp2, temp_key2);
                strcat(temp2, ":");
                temp2[(int) strlen(temp_key2) + 1]=0;
                if (j+1==count_of_douhao){
                    strcat(output,",");
                    strcat(output,temp2);
                    strcat(output,value);  //{a:2 + ,b:1
                    
                    output2=(char*)malloc(sizeof(char)*((int)strlen(output)+j-i+2));

                    strcpy(output2,output);
                    int a=0;
                    for(a=0;a<(j-i+1);a++){
                        strcat(output2,"}");
                    }
                    output2[(int)strlen(output)+j-i+1]=0;

                    
                } else {
                    strcat(output,",");
                    strcat(output,temp2);
                    strcat(output,"{"); // {a:2,b:{
                }
                begin=find_from_index_not_in_string(key,",",begin+1)+1;
            }
            break;
        }
        if(i+1==count_of_douhao){
            final_key=temp_key;
        }
        
        begin=find_from_index_not_in_string(key,",",begin+1)+1;
    }
    
    
    if(existed==TRUE){
        //{a}--->a
        char *value2=valueOfDictionaryAtKeyString(dictionary,key_copy);
        char *temp=(char*)malloc(sizeof(char)*((int)strlen(final_key)+2+(int)strlen(value2)));
        strcpy(temp,final_key);  // a
        strcat(temp,":");  // a:
        strcat(temp,value2); //a:12
        temp[sizeof(char)*((int)strlen(final_key)+1+(int)strlen(value2))]=0;
        char *temp2=(char*)malloc(sizeof(char)*((int)strlen(final_key)+2+(int)strlen(value)));
        strcpy(temp2,final_key);
        strcat(temp2,":");
        strcat(temp2,value);
        temp2[(int)strlen(final_key)+1+(int)strlen(value)]=0;
        dictionary=replace_not_in_string(dictionary,temp,temp2);
    } else {
      
        dictionary=replace(dictionary,temp_dict,output2);
        dictionary=replace_not_in_string(dictionary,"{,","{");
    }
    dictionary=substr(dictionary,3,(int)strlen(dictionary));
    return dictionary;
}


/*
 *  * format:    
dic:{a:1,b:{c:1,d:2}}:dictionary:
#~Begin:dic:
dic{a}:1:int:
dic{b}:{c:1,d:2}:dictionary:
#~Begin:dic{b}:
dic{b}{c}:1:int:
dic{b}{d}:2:int:
#~End:dic{b}:
#~End:dic:
 */

void formatStringForDictionaryInOrderToWtiteVar(struct VAR **struct_var,char *var_name, char *var_value){
    int num_of_key=numOfDictionaryKey(var_value);
    char *key=keyOfDictionaryAsList(var_value);
    //printf("key is %s\n",key);
    Var_addProperty(struct_var, var_name, var_value, "dictionary");
    
    int i=0;
    for(i=0;i<num_of_key;i++){
        char *key_name=valueOfListAtIndex(key,i);
        //printf("Key Name ----> %s\n",key_name);
        char *temp_key=(char*)malloc(sizeof(char)*((int)strlen(key_name)+3));
        strcpy(temp_key,"{");
        strcat(temp_key,key_name);
        strcat(temp_key,"}");
        temp_key[(int)strlen(key_name)+2]=0;
        //printf("Temp Key ----> %s\n",temp_key);
        char *value=valueOfDictionaryAtKeyString(var_value,temp_key);
        //printf("Value    ----> %s\n",value);
        if (strcmp("dictionary",variableValueType(value))==0){ // Value Type is Dictionary
            char *temp_var_name=(char*)malloc(sizeof(char)*((int)strlen(temp_key)+(int)strlen(var_name)+1));
            strcpy(temp_var_name,var_name);
            strcat(temp_var_name,temp_key);
            temp_var_name[(int)strlen(temp_key)+(int)strlen(var_name)]=0;
            formatStringForDictionaryInOrderToWtiteVar(struct_var,temp_var_name,value);
            
        } else { //Not Dictionary
           
            Var_addProperty(struct_var, append(var_name, temp_key), value, variableValueType(value));
        }
    }
}


//######### Write dictionary to Var using an appointed format.
void writeVarNameAndVarValueIntoAppointedVarForDictionary(struct VAR **struct_var,char *var_name, char *var_value){

    if(strcmp(var_value,"{}")==0){
        Var_addProperty(struct_var, var_name, var_value, "dictionary");
    }
    else{
        formatStringForDictionaryInOrderToWtiteVar(struct_var, var_name, var_value);
   }
    
}

//########## Use this function only when the same var name list exits ########
/*This function will change the whole value of the dictionary*/
void changeTheWholeVarValueFromItsInitialOneFromVarForDictionary(struct VAR **struct_var, char *var_name, char *var_value){
    //// printf("#### changeTheWholeVarValueFromItsInitialOneFromFileForList ####\n");
    //// printf("#### %s, %s, %s ####\n",file_name,var_name,var_value);
    int row=0;
    int length=0;
    if (strcmp((*struct_var)->var_name,"__size_of_array__")!=0) {
        printf("Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((*struct_var)->var_value);
    }

    char *temp_var_name=append(var_name, "{");
    while (row<length) {
        if (strcmp(var_name,(*struct_var+row)->var_name)==0 || find((*struct_var+row)->var_name, temp_var_name)==0) {
            Var_removeVar(struct_var, (*struct_var+row)->var_name);
            length--;
            row--;
        }
        row++;
    }
    
    writeVarNameAndVarValueIntoAppointedVarForDictionary(struct_var, var_name, var_value);
}
/*Change one var value
 * eg if a{"Hello") existed in dictionary, this function will change the value of a{"Hello"} and write it to file
 * eg if a{"Hello") doesn't existed, this function will add a{"Hello"} to dictionary and write it to file.
 * eg changeTheOneVarValueFromItsInitialOneFromFileOrAddVarNameAndValueForDictionary("__walley__.wy","a{'hi'}","12")
 */

void changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct VAR **struct_var, char *change_var_name, char *to_var_value){
    // printf("#### changeTheOneVarValueFromItsInitialOneFromFileOrAddVarNameAndValueForDictionary ####\n");
    // printf("####  %s, %s\n",change_var_name,to_var_value);
    
    change_var_name=removeAheadSpace(removeBackSpace(change_var_name));
    char *whole_dictionary_name=substr(change_var_name,0,find(change_var_name,"{")); //a{'hi'}--->a
    char *key=substr(change_var_name,find_not_in_string(change_var_name,"{"),(int)strlen(change_var_name)); //a{'hi'}{'hello'}--->{'hi'}{'hello'}
    
    char *whole_value_of_dictionary=Var_getValueOfVar(*struct_var,whole_dictionary_name); // get value from file-----> {'hi':{'hello':1}}
    whole_value_of_dictionary=dictionaryAddKeyAndValueInStringOrChangeOriginalValueByKey(whole_value_of_dictionary,key,to_var_value);
   
    
    changeTheWholeVarValueFromItsInitialOneFromVarForDictionary(struct_var, whole_dictionary_name, whole_value_of_dictionary);
}

/*
 isDictionaryElement try to find out whether a{"Hello"} kind of var_name is existed in file in order to use function
 * eg: isListElement("__walley__.wy","a{"Hello"}");
 */
/*
bool isDictionaryElement(char *file_name, char *var_name){
    FILE *fp=fopen(file_name,"r");
    if(fp==NULL){
        printf("Mistake occurred while calling function isDictionaryElement\nNo Required File Found");
        exit(1);
    }
    //printf("Enter here\n");
    char *dict_var_name=substr(var_name,0,find(var_name,"{"));//a[0]-->a
    dict_var_name=removeAheadSpace(dict_var_name);
    bool find_var_name=FALSE;
    char arr[1000]="";
    while((fgets(arr,1000,fp))!=NULL){
        //printf("%s\n",arr);
        if(find(arr,":")==-1)
            continue;
        char *temp_var_name=substr(arr,0,find(arr,":"));
        //printf("Temp Var Name is %s\nList Var Name is %s\n",list_var_name,temp_var_name);
        if(strcmp(temp_var_name,dict_var_name)==0){
            //printf("Find var name");
            find_var_name=TRUE;
            break;
        }
        
    }
    fclose(fp);
    return find_var_name;
        
}**/

/*
 * This function is used to substitue the value in x[i]'s [] and x{i}'s i
 * substitueValueInDictionaryAndList("x{i}","__walley__.wy")---->x{"Hello"}, we know the value of i=
 * "hello", so we replace value of i in x{i}
 */
/*
 * //########### I Put this function into Walley_Substitue_........
char *substitueValueInDictionaryAndList(char *input_str,char *file_var_name){
    int i=0;
    int begin=0;  //begin of { and [
    int end=0;    // end of } and ]
    for(i=0;i<(int)strlen(input_str);i++){
        if(charIsInString(input_str,i)==FALSE && input_str[i]=='{'){
            begin=i;
            end=find_from_index(input_str,"}",begin+1);  
            char *replace_str=substr(input_str,begin+1,end);   //from x{i} get i
            char *with_str=Walley_Substitue_Var_And_Function_Return_Value_From_File(replace_str,file_var_name);
            input_str=replace_from_index_to_index(input_str,replace,with_str,begin+1,end);
        }
        
        if(charIsInString(input_str,i)==FALSE && input_str[i]=='['){
            begin=i;
            end=find_from_index(input_str,"]",begin+1);  
            char *replace_str=substr(input_str,begin+1,end);   //from x{i} get i
            char *with_str=Walley_Substitue_Var_And_Function_Return_Value_From_File(replace_str,file_var_name);
            input_str=replace_from_index_to_index(input_str,replace,with_str,begin+1,end);
        }
    }
    
}
 * **/