/* 
 * File:   walley_list.h
 * Author: shd101wyy
 *
 * Created on August 31, 2012, 4:27 PM
 */

#include "walley_file_operation.h"
//#################### valueOfListAtIndex("[1,2,3,4]",0)---->1
char *valueOfListAtIndex(char *list,int index){
    if(find(list,"[")==-1 || find(list,"]")==-1)
        printf("Mistake occurred while calling function valueOfListAtIndex\nInput %sis not a list\n",list);
    list=trim(list);
    list=substr(list,1,(int)strlen(list)-1);
    char *temp=malloc(sizeof(char)*(2+(int)strlen(list)));
    strcpy(temp,",");
    strcat(temp,list);
    temp[1+(int)strlen(list)]=0;
    /* For Example [1,2]--->,1,2*/
    list=temp;
    
    int num_of_comma=count_str_not_in_string(list,",");
    if(num_of_comma<=index){
        printf("Mistake occurred while calling function valueOfListAtIndex\nIndex is outside the boundary\nList |%s| and index %d\n",list,index);
        exit(1);
    }
        
    
    int i=0;
    int begin=-1;
    int end=(int)strlen(list)-1;
    for(;i<index+1;i++){
            begin=find_from_index_not_in_string(list,",",begin+1);
    }
    
    char *output;
    if(find_from_index_not_in_string(list,",",begin+1)==-1){
        output=substr(list,begin+1,(int)strlen(list));
    } else {
        end=find_from_index_not_in_string(list,",",begin+1);
        output=substr(list,begin+1,end);
    }
    if(strcmp(output,"")==0)
        output="None";
    return output;
    
}

//#################### valueOfListAtIndexString("[1,[2],3,4]","[1][0]")---->2
char *valueOfListAtIndexString(char *list,char *index_str){
    //printf("1");
    char *index_str_temp=substr(index_str,find(index_str,"[")+1,find(index_str,"]"));
    int index=atoi(index_str_temp);
    if(find(list,"[")==-1 || find(list,"]")==-1){
        printf("Mistake occurred while calling function valueOfListAtIndexString\nInput %s is not a list\n",list);
        exit(0);
    }
    if(count_str_not_in_string(list,"[")!=count_str_not_in_string(list,"]")){
        printf("Mistake occurred while calling function valueOfListAtIndexString\nInput %s is not a list because the num of [ and ] is different\n",list);
        exit(0);  
    }
    
    
    list=removeBackSpace(list);
    list=removeAheadSpace(list);
    list=substr(list,1,(int)strlen(list)-1);
    char *temp=malloc(sizeof(char)*(2+(int)strlen(list)));
    strcpy(temp,",");
    strcat(temp,list);
    temp[1+(int)strlen(list)]=0;
    /* For Example [1,2]--->,1,2
                   [1,[2,3],3]--->,1,[2,3],3*/
    
    list=temp;
    
    int num_of_comma=count_str(list,",");
    if(num_of_comma<=index){
        printf("Mistake occurred while calling function valueOfListAtIndexString\nIndex is outside the boundary\n");
        exit(1);
    }
        
    
    int i=0;
    int begin=-1;
    int end=(int)strlen(list)-1;
    for(;i<index+1;i++){
            begin=find_from_index_not_in_string(list,",",begin+1);
          
            int left_fangkuohaoshu=count_str(substr(list,0,begin),"[" );
            int right_fangkuohaoshu=count_str(substr(list,0,begin),"]");
            while(left_fangkuohaoshu!=right_fangkuohaoshu){
                begin=find_from_index_not_in_string(list,",",begin+1);
                left_fangkuohaoshu=count_str(substr(list,0,begin),"[" );
                right_fangkuohaoshu=count_str(substr(list,0,begin),"]");
            }
    }
    
    char *output;
    if(find_from_index_not_in_string(list,",",begin+1)==-1){
        output=substr(list,begin+1,(int)strlen(list));
    } else {
        end = find_from_index_not_in_string(list, ",", begin + 1);
        
        int left_fangkuohaoshu = count_str(substr(list, 0, end), "[");
        int right_fangkuohaoshu = count_str(substr(list, 0, end), "]");
        while (left_fangkuohaoshu != right_fangkuohaoshu) {
            end = find_from_index_not_in_string(list, ",", end + 1);
            if(end==-1)
                end=(int)strlen(list);
            left_fangkuohaoshu = count_str(substr(list, 0, end), "[");
            right_fangkuohaoshu = count_str(substr(list, 0, end), "]");
            
        }
        output=substr(list,begin+1,end);
    }
    if(strcmp(output,"")==0)
        output="None";
   
    if(strcmp(variableValueType(output),"list")==0){
        if(count_str(index_str,"[")>1){
            char *temp_temp=substr(index_str,find(index_str,"]")+1,(int)strlen(index_str));
            output=valueOfListAtIndexString(output,temp_temp);         
        }
    }
    return output;
}

//#################### valueOfListAtIndexStringAndReturnBeginAndEnd("[1,[2],3,4]","[1][0]")---->4
void valueOfListAtIndexStringAndReturnBeginAndEnd(int begin_end[],char *list,char *index_str){
        
    char *index_str_temp=substr(index_str,find(index_str,"[")+1,find(index_str,"]"));
    int index=atoi(index_str_temp);
    if(find(list,"[")==-1 || find(list,"]")==-1){
        printf("Mistake occurred while calling function valueOfListAtIndexStringAndReturnBeginAndEnd\nInput %s is not a list\n",list);
        exit(0);
    }
    if(count_str_not_in_string(list,"[")!=count_str_not_in_string(list,"]")){
        printf("Mistake occurred while calling function valueOfListAtIndexStringAndReturnBeginAndEnd\nInput %s is not a list because the num of [ and ] is different\n",list);
        exit(0);  
    }
    
    
    list=removeBackSpace(list);
    list=removeAheadSpace(list);
    list=substr(list,1,(int)strlen(list)-1);
    /* For Example [1,2]--->,1,2
                   [1,[2,3],3]--->,1,[2,3],3*/
    
    list=append(",", list);
    
    int num_of_comma=count_str(list,",");
    if(num_of_comma<=index){
        printf("Mistake occurred while calling function valueOfListAtIndexStringAndReturnBeginAndEnd\nIndex is outside the boundary\n");
        exit(1);
    }
        
    
    int i=0;
    int begin=-1;
    int end=(int)strlen(list)-1;
    for(i=0;i<index+1;i++){
            begin=find_from_index_not_in_string(list,",",begin+1);
          
            int left_fangkuohaoshu=count_str(substr(list,0,begin),"[" );
            int right_fangkuohaoshu=count_str(substr(list,0,begin),"]");
            while(left_fangkuohaoshu!=right_fangkuohaoshu){
                begin=find_from_index_not_in_string(list,",",begin+1);
                left_fangkuohaoshu=count_str(substr(list,0,begin),"[" );
                right_fangkuohaoshu=count_str(substr(list,0,begin),"]");
            }
    }
    
    char *output;
    if(find_from_index_not_in_string(list,",",begin+1)==-1){
        output=substr(list,begin+1,(int)strlen(list));
        begin_end[0]+=begin+1;
        begin_end[1]=begin_end[0]+((int)strlen(list)-begin-1);
        
    } else {
        end = find_from_index_not_in_string(list, ",", begin + 1);
        int left_fangkuohaoshu = count_str_not_in_string(substr(list, 0, end), "[");
        int right_fangkuohaoshu = count_str_not_in_string(substr(list, 0, end), "]");
        while (left_fangkuohaoshu != right_fangkuohaoshu) {
            end = find_from_index_not_in_string(list, ",", end + 1);
            
            if(end == -1){
                end=(int)strlen(list);
                break;
            } 
            
            left_fangkuohaoshu = count_str(substr(list, 0, end), "[");
            right_fangkuohaoshu = count_str(substr(list, 0, end), "]");
            
        }
        output=substr(list,begin+1,end);
        begin_end[0]=begin_end[0]+begin+1;
        begin_end[1]=begin_end[0]+(end-begin-1);
    }
    if(strcmp(output,"")==0)
        output="None";
    
    if(strcmp(variableValueType(output),"list")==0){
        if(count_str(index_str,"[")>1){
            char *temp_temp=substr(index_str,find(index_str,"]")+1,(int)strlen(index_str));
            valueOfListAtIndexStringAndReturnBeginAndEnd(begin_end,output,temp_temp);         
        }
    }
}


int valueNumOfList(char *list){
    if (strcmp(list, "[]")==0) {
        return 0;
    }
    
    if(find_not_in_string(list,"[")==-1 || find_not_in_string(list,"]")==-1){
        printf("Mistake occurred while calling function valueNumOfList\nInput |%s| is not a list\n",list);
        exit(0);
    }
    if(count_str_not_in_string(list,"[")!=count_str_not_in_string(list,"]")){
        printf("Mistake occurred while calling function valueNumOfList\nInput |%s| is not a list because the num of [ %d and ] %d is different\n",list,count_str_not_in_string(list,"["),count_str_not_in_string(list,"]"));
        exit(0);  
    }
    
    
    list=removeBackSpace(list);
    list=removeAheadSpace(list);
    list=substr(list,1,(int)strlen(list)-1);
    char *temp=malloc(sizeof(char)*(3+(int)strlen(list)));
    strcpy(temp, ",");
    strcat(temp,list);
    strcat(temp,",");
    temp[2+(int)strlen(list)]=0;
    list=temp;
    
    int begin=0;
    bool just_begin=TRUE;
    int num=0;
    while (begin != -1) {
        if (just_begin == TRUE) {
            begin = -1;
            just_begin = FALSE;
        }
        begin = find_from_index_not_in_string(list, ",", begin + 1);
        if(begin==-1)
            break;
        if(begin!=0){
        int left_fangkuohaoshu = count_str(substr(list, 0, begin), "[");
        int right_fangkuohaoshu = count_str(substr(list, 0, begin), "]");
        while (left_fangkuohaoshu != right_fangkuohaoshu) {
            begin = find_from_index_not_in_string(list, ",", begin + 1);
            left_fangkuohaoshu = count_str(substr(list, 0, begin), "[");
            right_fangkuohaoshu = count_str(substr(list, 0, begin), "]");
                }
        }
        num+=1;
    }
    num-=1;
    return num;
}
/*format:    
a:[1,[1,2] ]:list:
#~Begin:a:
a[0]:1:list:
a[1]:[1,2]:list:
#~Begin:a[1]:
a[1][0]:1:int:
a[1][1]:2:int:
#~End:a[1]:
#~End:a:
*/

void formatStringForListInOrderToWtiteToVar(struct VAR **struct_var,char *var_name,char *var_value){
    
    Var_addProperty(struct_var, var_name, var_value, "list");
    
    int i=0;
    int num_of_value=valueNumOfList(var_value);
    for(i=0;i<num_of_value;i++){
        //char number[500];
        //sprintf(number,"%d",i);
        char *number=intToCString(i);
        
        char *index_str=malloc(sizeof(char)*((int)strlen(number)+3));
        strcpy(index_str,"[");
        strcat(index_str,number);
        strcat(index_str,"]");
        index_str[(int)strlen(number)+2]=0;
        char *var_value_from_list=valueOfListAtIndexString(var_value,index_str);
        char *value_type=variableValueType(var_value_from_list);
        if(strcmp(value_type,"list")==0){
            char *temp_var_name=malloc(sizeof(char)*((int)strlen(var_name)+2+i%10+1));
            strcpy(temp_var_name,var_name);
            strcat(temp_var_name,"[");
            //char temp_str[5000]="";
            //sprintf(temp_str,"%d",i);
            char *temp_str=intToCString(i);
            strcat(temp_var_name,temp_str);
            strcat(temp_var_name,"]");
            formatStringForListInOrderToWtiteToVar(struct_var,temp_var_name,var_value_from_list);
        } else {
            char *temp_var_name=malloc(sizeof(char)*((int)strlen(var_name)+3+i%10+1));
            strcpy(temp_var_name,var_name);
            strcat(temp_var_name,"[");
            //char temp_str[5000]="";
            //sprintf(temp_str,"%d",i);
            char *temp_str=intToCString(i);
            strcat(temp_var_name,temp_str);
            strcat(temp_var_name,"]");
                       
            Var_addProperty(struct_var, temp_var_name, var_value_from_list, value_type);
            
            
            
        }
        
    }
     
}

//######### Write List to Var using an appointed format.
void writeVarNameAndVarValueIntoAppointedVarForList(struct VAR **struct_var,char *var_name,char *var_value) {
    formatStringForListInOrderToWtiteToVar(struct_var, var_name, var_value);
}


//########## Use this function only when the same var name list exits ########
/*This function will change the whole value of the list*/
void changeTheWholeVarValueFromItsInitialOneFromVarForList(struct VAR **struct_var, char *var_name, char *var_value){
    // printf("#### changeTheWholeVarValueFromItsInitialOneFromFileForList ####\n");
    
    int row=0;
    int length=0;
    if (strcmp((*struct_var)->var_name,"__size_of_array__")!=0) {
        printf("Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((*struct_var)->var_value);
    }
    //struct VAR temp_var[];
    char *temp_var_name=append(var_name, "[");
    while (row<length) {
        if (strcmp(var_name,(*struct_var+row)->var_name)==0 || find((*struct_var+row)->var_name, temp_var_name)==0) {
            Var_removeVar(struct_var, (*struct_var+row)->var_name);
            length--;
            row--;
        }
        row++;
    }
   
    writeVarNameAndVarValueIntoAppointedVarForList(struct_var, var_name, var_value);
}

/*Change one var value
 eg put a[0] or a[0][0] into var_name
 * will change the value of a[0]
 */
void changeTheOneVarValueFromItsInitialOneFromVarForList(struct VAR **struct_var, char *change_var_name, char *to_var_value){
    //printf("###### changeTheOneVarValueFromItsInitialOneFromFileForList ######\n");
    change_var_name=removeBackSpace(change_var_name);
    change_var_name=removeAheadSpace(change_var_name);
    char *var_name=substr(change_var_name,0,find_not_in_string(change_var_name,"["));
    char *var_value;
    
    char *index=substr(change_var_name,find_not_in_string(change_var_name,"["),(int)strlen(change_var_name));
    index=removeBackSpace(index);
    // eg now index =[1][2][3];
    
    
    //FILE *fp;
    int row=0;
    int length=0;
    if (strcmp((*struct_var)->var_name,"__size_of_array__")!=0) {
        printf("Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((*struct_var)->var_value);
    }

    while (row<length) {
        char *var_name_in_file = (*struct_var+row)->var_name;
        if(strcmp(var_name_in_file, var_name) == 0){
            var_value=(*struct_var+row)->var_value;
            break;
        }
        row++;
    }
    
    //eg now index = [1][0]
    // var_value=[1,[2,3],3]
    char *original_value=valueOfListAtIndexString(var_value,index);
    int begin_end[2];
    begin_end[0]=0;
    begin_end[1]=0;

    valueOfListAtIndexStringAndReturnBeginAndEnd(begin_end,var_value,index);
    int begin=begin_end[0];
    int end=begin_end[1];
    
    char *change_change=replace_from_index_to_index(var_value,original_value,to_var_value,begin,end+1);
    changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, var_name, change_change);
    
}

/*
 isListElement try to find out whether a[0] kind of var_name is existed in file in order to use function 
 * changeTheOneVarValueFromItsInitialOneFromFileForList
 * eg: isListElement("__walley__.wy","a[1]");
 */
bool isListElementForVar(struct VAR *struct_var, char *var_name){
    if (find_not_in_string(var_name, "[")==-1) {
        return FALSE;
    }
    char *list_var_name=substr(var_name,0,find_not_in_string(var_name,"["));//a[0]-->a
    list_var_name=removeAheadSpace(list_var_name);
    bool find_var_name=FALSE;
    int row=0;
    
    int length=0;
    if (strcmp((struct_var)->var_name,"__size_of_array__")!=0) {
        printf("Can not find __size_of_array__");
        exit(0);
    }
    else{
        length=atoi((struct_var)->var_value);
    }
    
    
    //while (struct_var[row].var_name!=NULL) {
    while (row<length) {
        char *temp_var_name=struct_var[row].var_name;
        if(strcmp(temp_var_name,list_var_name)==0){
            find_var_name=TRUE;
            break;
        }
        row++;

    }
    return find_var_name;
}

/*
 * eg changeStringToList("'Hello'")------>['H','e','l','l','o']
 */
char *changeStringToList(char *input_str){
    input_str=removeAheadSpace(removeBackSpace(input_str));
    if(strcmp(variableValueType(input_str),"string")!=0){
        printf("Mistake occurred while calling function changeStringToList\n|%s| is not a string",input_str);
        exit(2);
    } else {
        char output[1000]="";
        strcpy(output,"[");
        input_str=substr(input_str,1,(int)strlen(input_str)-1);
        int i=0;
        for(i=0;i<(int)strlen(input_str);i++){
            strcat(output,"'");
            strcat(output,substr(input_str,i,i+1));
            strcat(output,"',");
        }
        output[(int)strlen(output)-1]=']';
        char *output2=malloc(sizeof(char)*((int)strlen(output)+1));
        for(i=0;i<(int)strlen(output);i++){
            output2[i]=output[i];
        }
        output2[(int)strlen(output)]=0;
        if(find_not_in_string(output2,"[[")!=-1){
            output2=replace_not_in_string(output2,"[[","[");
        }
        if(find_not_in_string(output2,"]]")!=-1){
            output2=replace_not_in_string(output2,"]]","]");
        }
        return output2;
    }
}
/*
 * listAppendOneElement("[1,2,3]","4")---->"[1,2,3,4]"
 * ListAppendOneElement("[1,2,3]","[3,4]"------>[1,2,3,[3,4]]
 */
char *listAppendOneElement(char *list, char *append_element){
   //// printf("#### listAppendOneElement ####\n");
    list=trim(list);
    list=substr(list,0,(int)strlen(list)-1);//[1,2]---->[1,2
    char *output;
    output=append("", list);
    if(strcmp(list,"[")!=0){
        //strcat(output,",");//[1,2,
        output=append(output, ",");
    }
    //strcat(output,append_element); //[1,2,[3,4]
    output=append(output, append_element);
    //strcat(output,"]"); //[1,2,[3,4]]
    output=append(output,"]");
    return output;
}
/*
 * listRemoveOneElementAtOneIndex("[1,2,3]","1")----->[1,3]
 * listRemoveOneElementAtOneIndex("[1,[1,2],3]","1")----->[1,3]
 */

char *listRemoveOneElementAtOneIndex(char *list, char *index){
   //// printf("List is %s, index is %s",list,index);
    
    index=trim(index);
    list=trim(list);
    if (index[0]=='['&&index[(int)strlen(index)-1]==']') {
        index=index;
    }
    else{
        index=append("[", index);
        index=append(index, "]");
    }
    
    char *replace_str=valueOfListAtIndexString(list,index);
   
    int begin_end[2];
    begin_end[0]=0;
    begin_end[1]=0;
    valueOfListAtIndexStringAndReturnBeginAndEnd(begin_end,list,index);
    
   
    char *output;
    output=replace_from_index_to_index(list,replace_str,"",begin_end[0],begin_end[1]);
    if(find_not_in_string(output,",,")!=-1){
        output = replace_not_in_string(output,",,",",");
    }
    if(find_not_in_string(output,",]")!=-1){
        output= replace_not_in_string(output,",]","]");
    } 
    
    if(find_not_in_string(output,"[,")!=-1){
        output= replace_not_in_string(output,"[,","[");
    } 
    
    return output; 
}
/*
 * eg listRemoveOneElementByValue("[1,2,3]","1")---->"[2,3]"
 *    listRemoveOneElementByValue("[1,2,[1,3]]","1")----->[2,[1,3]]
 *    listRemoveOneElementByValue("[1,1,1,1]","1")  -----> [1,1,1]
 */
char *listRemoveOneElementByValue(char *list, char *remove_value){
    list=substr(list, 1, (int)strlen(list)-1);
    int index=find_not_in_str_list_dict(list, remove_value);
    list=replace_from_index_to_index(list, remove_value, "", index, index+(int)strlen(remove_value));
    list=append("[", list);
    list=append(list, "]");
    list=replace_not_in_string(list, ",,", ",");
    list=replace_not_in_string(list, "[,", "[");
    list=replace_not_in_string(list, ",]", "]");
    //printf("%s\n",list);
    return list;
}