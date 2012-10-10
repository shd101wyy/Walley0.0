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
    char *temp=malloc(sizeof(char)*(1+(int)strlen(list)));
    strcat(temp,",");
    strcat(temp,list);
    //printf("--%s\n",temp);
    /* For Example [1,2]--->,1,2*/
    list=temp;
    
    int num_of_comma=count_str_not_in_string(list,",");
    //printf("comma is %d\n",num_of_comma);
    if(num_of_comma<=index){
        printf("Mistake occurred while calling function valueOfListAtIndex\nIndex is outside the boundary\n");
        exit(1);
    }
        
    
    int i=0;
    int begin=-1;
    int end=(int)strlen(list)-1;
    for(;i<index+1;i++){
            begin=find_from_index_not_in_string(list,",",begin+1);
            //printf("2--%d\n",begin);
    }
    
    char *output;
    if(find_from_index_not_in_string(list,",",begin+1)==-1){
        output=substr(list,begin+1,(int)strlen(list));
    } else {
        end=find_from_index_not_in_string(list,",",begin+1);
        output=substr(list,begin+1,end);
    }
    //printf("begin is %d, end is %d\n",begin,end);
    if(strcmp(output,"")==0)
        output="None";
    return output;
    
}

//#################### valueOfListAtIndexString("[1,[2],3,4]","[1][0]")---->2
char *valueOfListAtIndexString(char *list,char *index_str){
    //printf("1");
    char *index_str_temp=substr(index_str,find(index_str,"[")+1,find(index_str,"]"));
    int index=atoi(index_str_temp);
    //free(index_str_temp);
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
    char *temp=malloc(sizeof(char)*(1+(int)strlen(list)));
    strcat(temp,",");
    strcat(temp,list);
    //printf("--%s\n",temp);
    /* For Example [1,2]--->,1,2
                   [1,[2,3],3]--->,1,[2,3],3*/
    
    list=temp;
    //printf("list is %s\nIndex is %d\n",list,index);
    
    int num_of_comma=count_str(list,",");
    //printf("comma is %d\n",num_of_comma);
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
            //printf("Left %d, Right %d\n",left_fangkuohaoshu,right_fangkuohaoshu);
            while(left_fangkuohaoshu!=right_fangkuohaoshu){
                //printf("find , in side list,index is %d\n",begin);
                begin=find_from_index_not_in_string(list,",",begin+1);
                left_fangkuohaoshu=count_str(substr(list,0,begin),"[" );
                right_fangkuohaoshu=count_str(substr(list,0,begin),"]");
                //index=index-1;
            }
            //printf("2--%d\n",begin);
    }
    
    char *output;
    if(find_from_index_not_in_string(list,",",begin+1)==-1){
        //printf("list %s\nbegin %d\n",list,begin);
        output=substr(list,begin+1,(int)strlen(list));
    } else {
        //printf("list %s\nbegin %d\n",list,begin);
        end = find_from_index_not_in_string(list, ",", begin + 1);
        
        int left_fangkuohaoshu = count_str(substr(list, 0, end), "[");
        int right_fangkuohaoshu = count_str(substr(list, 0, end), "]");
        //printf("Left %d, Right %d\n", left_fangkuohaoshu, right_fangkuohaoshu);
        while (left_fangkuohaoshu != right_fangkuohaoshu) {
            end = find_from_index_not_in_string(list, ",", end + 1);
            if(end==-1)
                end=(int)strlen(list);
            left_fangkuohaoshu = count_str(substr(list, 0, end), "[");
            right_fangkuohaoshu = count_str(substr(list, 0, end), "]");
            
        }
        output=substr(list,begin+1,end);
    }
    //printf("begin is %d, end is %d\n",begin,end);
    if(strcmp(output,"")==0)
        output="None";
   
    //printf("variable value is %s\nvariable value type is %s\n",output,variableValueType(output));
    if(strcmp(variableValueType(output),"list")==0){
        if(count_str(index_str,"[")>1){
            //printf("Befor change index_str, it is %s\n",index_str);
            //printf("Output is %s\n",output);
            char *temp_temp=substr(index_str,find(index_str,"]")+1,(int)strlen(index_str));
            //printf("After change, it is %s\n",temp_temp);
            //printf("output is %s, index_str is %s",output,temp_temp);
            output=valueOfListAtIndexString(output,temp_temp);         
        }
    }
    return output;
}

//#################### valueOfListAtIndexStringAndReturnBeginAndEnd("[1,[2],3,4]","[1][0]")---->4
void valueOfListAtIndexStringAndReturnBeginAndEnd(int begin_end[],char *list,char *index_str){
    //printf("1");
   //// printf("#### valueOfListAtIndexStringAndReturnBeginAndEnd ####\n");
   //// printf("list %s\n,index_str %s\n",list,index_str);
    //begin_end[0]=0;
    //begin_end[1]=0;
    
    char *index_str_temp=substr(index_str,find(index_str,"[")+1,find(index_str,"]"));
    int index=atoi(index_str_temp);
    //free(index_str_temp);
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
    char *temp=malloc(sizeof(char)*(1+(int)strlen(list)));
    strcat(temp,",");
    strcat(temp,list);
    //printf("--%s\n",temp);
    /* For Example [1,2]--->,1,2
                   [1,[2,3],3]--->,1,[2,3],3*/
    
    list=temp;
   //// printf("list is %s\nIndex is %d\n",list,index);
    
    int num_of_comma=count_str(list,",");
    //printf("comma is %d\n",num_of_comma);
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
            //printf("Left %d, Right %d\n",left_fangkuohaoshu,right_fangkuohaoshu);
            while(left_fangkuohaoshu!=right_fangkuohaoshu){
                //printf("find , in side list,index is %d\n",begin);
                begin=find_from_index_not_in_string(list,",",begin+1);
                left_fangkuohaoshu=count_str(substr(list,0,begin),"[" );
                right_fangkuohaoshu=count_str(substr(list,0,begin),"]");
                //index=index-1;
            }
            //printf("2--%d\n",begin);
    }
    //printf("list %s\n",list);
    //printf("begin is %d\n",begin);
    //printf("from begin to end of str is %s\n",substr(list,begin,(int)strlen(list)));
    char *output;
    if(find_from_index_not_in_string(list,",",begin+1)==-1){
        //printf("here\n");
        //printf("list %s\nbegin %d\n",list,begin);
        output=substr(list,begin+1,(int)strlen(list));
        begin_end[0]+=begin+1;
        begin_end[1]+=(int)strlen(list);
        
    } else {
        //printf("there\n");
        //printf("list %s\nbegin %d\n",list,begin);
        end = find_from_index_not_in_string(list, ",", begin + 1);
        //printf("end %d\n",end);
        int left_fangkuohaoshu = count_str(substr(list, 0, end), "[");
        int right_fangkuohaoshu = count_str(substr(list, 0, end), "]");
        //printf("Left %d, Right %d\n", left_fangkuohaoshu, right_fangkuohaoshu);
        while (left_fangkuohaoshu != right_fangkuohaoshu) {
            //printf("Enter while\n");
            end = find_from_index_not_in_string(list, ",", end + 1);
            //printf("end is |%d|\n",end);
            
            if(end == -1){
               //// printf("end!=-1");
                end=(int)strlen(list);
                break;
            } 
            
            left_fangkuohaoshu = count_str(substr(list, 0, end), "[");
            right_fangkuohaoshu = count_str(substr(list, 0, end), "]");
            
        }
        output=substr(list,begin+1,end);
        //printf("after %s\n",output);
        begin_end[0]=begin_end[0]+begin+1;
        //begin_end[1]=begin_end[1]+end;
        begin_end[1]=begin_end[0]+(end-begin-1);
    }
    //printf("begin is %d, end is %d\n",begin,end);
    if(strcmp(output,"")==0)
        output="None";
    
    //printf("variable value is %s\nvariable value type is %s\n",output,variableValueType(output));
    if(strcmp(variableValueType(output),"list")==0){
        if(count_str(index_str,"[")>1){
            //printf("Befor change index_str, it is %s\n",index_str);
            //printf("Output is %s\n",output);
            char *temp_temp=substr(index_str,find(index_str,"]")+1,(int)strlen(index_str));
            //printf("After change, it is %s\n",temp_temp);
            //printf("output is %s, index_str is %s",output,temp_temp);
           //// printf("Find another list\n");
           //// printf("%%%%begin %d, end %d\n",begin_end[0],begin_end[1]);
            valueOfListAtIndexStringAndReturnBeginAndEnd(begin_end,output,temp_temp);         
        }
    }
   //// printf("%%%%begin %d, end %d\n",begin_end[0],begin_end[1]);
}


int valueNumOfList(char *list){
    /*
    if(find(list,"[")==-1 || find(list,"]")==-1){
        printf("Mistake occurred while calling function valueNumOfList\nInput %sis not a list\n",list);
        exit(1);   
    }
    if(count_str(list,"[")!=count_str(list,"]")){
        printf("Mistake occurred while calling function valueNumOfList\nInput %s is not a list because the num of [ and ] is different\n",list);
        exit(0);  
    }
    list=removeAheadSpace(list);
    list=removeBackSpace(list);
    char *parameter_str=substr(list, find(list,"[")+1,find(list,"]"));
    //printf("#### parameter_str is %s ####\n",parameter_str);
    parameter_str=removeAheadSpace(parameter_str);
    //printf("#### parameter_str is %s ####\n",parameter_str);
    parameter_str=removeBackSpace(parameter_str);
    //printf("###### Parameter is : %s ######\n",parameter_str);
    
    
    int para_num=0;//count_str(parameter_str,",")+1;
    while(count_str(list,"[")!=1){
        printf("count_str is %d\n",(count_str(list,"[")));
        int left=find_from_index(list,"[",1);
        int right=find_from_index(list,"]",left);
        char *temp_str=substr(list,left,right+1);
        list=replace(list,temp_str,"");
        list=replace(list,",,",",");
        para_num+=1;
    }
    para_num+=count_str(list,",")+1;
    if(stringIsEmpty(parameter_str)){
        para_num=0;
        parameter_str="None";
    }
    return para_num;**/
    //printf("1");

    if(find_not_in_string(list,"[")==-1 || find_not_in_string(list,"]")==-1){
        printf("Mistake occurred while calling function valueNumOfList\nInput %s is not a list\n",list);
        exit(0);
    }
    if(count_str_not_in_string(list,"[")!=count_str_not_in_string(list,"]")){
        printf("Mistake occurred while calling function valueNumOfList\nInput %s is not a list because the num of [ %d and ] %d is different\n",list,count_str_not_in_string(list,"["),count_str_not_in_string(list,"]"));
        exit(0);  
    }
    
    
    list=removeBackSpace(list);
    list=removeAheadSpace(list);
    list=substr(list,1,(int)strlen(list)-1);
    //char *temp=malloc(sizeof(char)*(3+(int)strlen(list)));
    char *temp=malloc(sizeof(char)*(4+(int)strlen(list)));
    strcat(temp,",");
    strcat(temp,list);
    strcat(temp,",");
    //printf("--%s\n",temp);
    /* For Example [1,2]--->,1,2,
                   [1,[2,3],3]--->,1,[2,3],3,
                   [1,2,3,[1,2]]----> ,1,2,3,[1,2],
     */
           
    
    list=temp;
    //printf("Temp --->%s\n",temp);
        
    
    int i=0;
    int begin=0;
    int end=(int)strlen(list)-1;
    bool just_begin=TRUE;
    int num=0;
    while (begin != -1) {
        //printf("enter\nlist %s\n",list);
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
        //printf("Left %d, Right %d\n",left_fangkuohaoshu,right_fangkuohaoshu);
        while (left_fangkuohaoshu != right_fangkuohaoshu) {
            //printf("find , in side list,index is %d\n",begin);
            begin = find_from_index_not_in_string(list, ",", begin + 1);
            left_fangkuohaoshu = count_str(substr(list, 0, begin), "[");
            right_fangkuohaoshu = count_str(substr(list, 0, begin), "]");
            //index=index-1;
                }
        }
        //printf("2--%d\n",begin);d
        //printf("%d\n",begin);
        num+=1;
        //printf("Begin %d\n",begin);
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
char *formatStringForListInOrderToWtiteFile(char *var_name,char *var_value){
   //// printf("#### formatStringForListInOrderToWtiteFile ####\n");
    char input_message[100000] = "";
    //strcat(input_message, "\n");
    strcat(input_message, var_name);
    strcat(input_message, ":");
    strcat(input_message, var_value);
    strcat(input_message, ":");
    strcat(input_message, "list");
    strcat(input_message, ":");
    strcat(input_message, "\n");
    strcat(input_message, "#~Begin:");
    strcat(input_message, var_name);
    strcat(input_message ,":\n");
    
    int i=0;
    //printf("Enter here\n");
    int num_of_value=valueNumOfList(var_value);
    //printf("num of value is %d\n",num_of_value);
    //printf("var_value is %s\n",var_value);
    for(i=0;i<num_of_value;i++){
        //printf("-----> %d\n",i);
        //char *var_value_from_list=valueOfListAtIndex(var_value,i);
        char number[500];
        sprintf(number,"%d",i);
        char *index_str=malloc(sizeof(char)*((int)strlen(number)+2));
        strcat(index_str,"[");
        strcat(index_str,number);
        strcat(index_str,"]");
        //char *var_value_from_list=valueOfListAtIndex(var_value,i);
        char *var_value_from_list=valueOfListAtIndexString(var_value,index_str);
        char *value_type=variableValueType(var_value_from_list);
        //printf("HERE\n");
        if(strcmp(value_type,"list")==0){
            //printf("Find list\n");
            char *temp_var_name=malloc(sizeof(char)*((int)strlen(var_name)+2+i%10+1));
            strcat(temp_var_name,var_name);
            strcat(temp_var_name,"[");
            char temp_str[5000]="";
            sprintf(temp_str,"%d",i);
            strcat(temp_var_name,temp_str);
            strcat(temp_var_name,"]");
            //printf("temp_var_name is :%s\nvar_value_from_list is :%s\n",temp_var_name,var_value_from_list);
            //formatStringForListInOrderToWtiteFile(temp_var_name,var_value_from_list);
            strcat(input_message,formatStringForListInOrderToWtiteFile(temp_var_name,var_value_from_list));
            //free(temp_var_name);
        } else {
            //printf("It is not list\n");
            //printf("var_value_from_list is %s\n",var_value_from_list);
            char *temp_var_name=malloc(sizeof(char)*((int)strlen(var_name)+2+i%10+1));
            strcat(temp_var_name,var_name);
            strcat(temp_var_name,"[");
            char temp_str[5000]="";
            sprintf(temp_str,"%d",i);
            strcat(temp_var_name,temp_str);
            strcat(temp_var_name,"]");
            
            //printf("AAAA\n");
            
            strcat(input_message, temp_var_name);
            strcat(input_message, ":");
            strcat(input_message,var_value_from_list );
            strcat(input_message, ":");
            strcat(input_message, value_type);
            strcat(input_message, ":\n");
            
            
            //free(temp_var_name);        
            
        }
        //printf("EXIT\n");
        
    }

    strcat(input_message, "#~End:");
    strcat(input_message, var_name);
    strcat(input_message ,":\n");
    
    //printf("Input Message is \n:%s\n", input_message);
    char *output=malloc(sizeof(char)*(int)strlen(input_message));
    int a=0;
    for(a=0;a<(int)strlen(input_message);a++){
        output[a]=input_message[a];
    }
    //return input_message;
   //// printf("#### FINISH formatStringForListInOrderToWtiteFile ####\n");
    return output;
}

//######### Write List to File using an appointed format.
void writeVarNameAndVarValueIntoAppointedFileForList(char *file_name,char *var_name,char *var_value) {
    char *str_in_wy = getStringFromFile(file_name);
    //printf("###########str_int_wy is %s###########\n",str_in_wy);
    FILE *fp = fopen(file_name, "w");
    fputs(str_in_wy, fp);
    fputs("\n", fp);
    char *input_message=formatStringForListInOrderToWtiteFile(var_name,var_value);
    fputs(input_message, fp);
    fclose(fp);
    //free(fp);

}

//########## Use this function only when the same var name list exits ########
/*This function will change the whole value of the list*/
void changeTheWholeVarValueFromItsInitialOneFromFileForList(char *file_name, char *var_name, char *var_value){
   //// printf("#### changeTheWholeVarValueFromItsInitialOneFromFileForList ####\n");
   //// printf("#### %s, %s, %s ####\n",file_name,var_name,var_value);
    FILE *fp;
    char ch;
    char arr[1000]="";
    char output[10000]="";
    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
      //  printf("Find file %s\n",file_name);
    //}
    bool begin=FALSE;
    
    while ((fgets(arr, 1000, fp)) != NULL) {
        //#~End:a:
        //printf("arr -----> %s\n",arr);
        if (find(arr, "#~End:") != -1) {
            char *temp = malloc(sizeof (char) *(7)+(int) strlen(var_name));
            strcat(temp, "#~End:");
            strcat(temp, var_name);
            strcat(temp, ":");
            //printf("FIND END\n");
            //printf("temp is %s\n",temp);
            //printf("compare to %s\n",substr(arr, 0, (int) strlen(temp)));
            if (strcmp(substr(arr, 0, (int) strlen(temp)), temp) == 0) {
                //printf("Same\n");
                begin = FALSE;
                char *temp_temp = formatStringForListInOrderToWtiteFile(var_name, var_value);
                //printf("temp_temp is %s\n",temp_temp);
                strcat(output, temp_temp);
                //printf("---- output ----> %s\n",output);
                //free(temp_temp);
                continue;
            } 
            //printf("THERE1\n");
            
        }
        
        if(begin==TRUE)
            continue;
        
        if(find_not_in_string(arr,":")==-1 && begin==FALSE){
            strcat(output, arr);
            //printf("THERE2\n");
            continue;
        }        
        char *var_name_in_file = substr(arr, 0, find_not_in_string(arr, ":"));
        if (strcmp(var_name_in_file, var_name) != 0 && begin==FALSE) {
            //printf("######Not Same\n");
            //printf("THERE3\n");
            strcat(output, arr);
            //printf("%s\n",output);
        } 
        if(strcmp(var_name_in_file, var_name) == 0){
            //printf("#######Find Var Name\n");
            begin=TRUE;
        }
        //printf("THERE\n");
    }

    //printf("----output |%s|\n",output);
    fclose(fp);
    fp=fopen(file_name, "w");
    fputs(output,fp);
    fclose(fp);
    
}
/*Change one var value
 eg put a[0] or a[0][0] into var_name
 * will change the value of a[0]
 */
void changeTheOneVarValueFromItsInitialOneFromFileForList(char *file_name, char *change_var_name, char *to_var_value){
   //// printf("###### changeTheOneVarValueFromItsInitialOneFromFileForList ######\n");
    change_var_name=removeBackSpace(change_var_name);
    change_var_name=removeAheadSpace(change_var_name);
    char *var_name=substr(change_var_name,0,find_not_in_string(change_var_name,"["));
    char *var_value;
    
    char *index=substr(change_var_name,find_not_in_string(change_var_name,"["),(int)strlen(change_var_name));
    index=removeBackSpace(index);
    // eg now index =[1][2][3];
    
    
    FILE *fp;
    char ch;
    char arr[1000]="";

    if ((fp = fopen(file_name, "r")) == NULL) {
        perror("File open error!\n");
        exit(1);
    } //else {
      //  printf("Find file %s\n",file_name);
    //}

    while ((fgets(arr, 1000, fp)) != NULL) {
        if(find_not_in_string(arr,":")==-1){
            continue;
        }        
        char *var_name_in_file = substr(arr, 0, find_not_in_string(arr, ":"));
        if(strcmp(var_name_in_file, var_name) == 0){
           //// printf("#######Find Var Name\n------%s------\n",arr);
           //// printf("arr %s\n",arr);
            var_value=malloc(sizeof(char)*((int)strlen(substr(arr,find(arr,":")+1,find_from_index_not_in_string(arr,":",find(arr,":")+1)))));
            strcat(var_value,substr(arr,find_not_in_string(arr,":")+1,find_from_index_not_in_string(arr,":",find(arr,":")+1)));
            //var_value=substr(arr,find(arr,":")+1,find_from_index(arr,":",find(arr,":")+1));
            break;
        }
    }
    fclose(fp);

    //eg now index = [1][0]
    // var_value=[1,[2,3],3]
    
    char *original_value=valueOfListAtIndexString(var_value,index);
    int begin_end[2];
    begin_end[0]=0;
    begin_end[1]=0;
   //// printf("var value is %s\nindex is %s\nto_var_value is %s\n",var_value,index,to_var_value);
    valueOfListAtIndexStringAndReturnBeginAndEnd(begin_end,var_value,index);
    int begin=begin_end[0];
    int end=begin_end[1];
   //// printf("begin is %d\nend is %d\n",begin,end);
    char *change_change=malloc(sizeof(char)*((int)strlen(var_value)-(int)strlen(original_value)+(int)strlen(to_var_value)));
    //if(begin!=1)
    //    strcat(change_change,substr(var_value,0,begin-1));
    //else
    //    strcat(change_change,"[");
    //strcat(change_change,to_var_value);
    //strcat(change_change,substr(var_value,end,(int)strlen(var_value)));
   //// printf("Before change_change var_value is %s, original_value is %s, to_var_value is %s\n",var_value,original_value,to_var_value);
   //// printf("begin is %d, end+1 is %d\n",begin,end+1);
    change_change=replace_from_index_to_index(var_value,original_value,to_var_value,begin,end+1);
   //// printf("change change is %s\n",change_change);
    changeTheWholeVarValueFromItsInitialOneFromFileForList(file_name, var_name, change_change);

}
/*
 isListElement try to find out whether a[0] kind of var_name is existed in file in order to use function 
 * changeTheOneVarValueFromItsInitialOneFromFileForList
 * eg: isListElement("__walley__.wy","a[1]");
 */
bool isListElement(char *file_name, char *var_name){
    FILE *fp=fopen(file_name,"r");
    if(fp==NULL){
        printf("Mistake occurred while calling function isListElement\nNo Required File Found");
        exit(1);
    }
    //printf("Enter here\n");
    if (find_not_in_string(var_name, "[")==-1) {
        return FALSE;
    }
    char *list_var_name=substr(var_name,0,find_not_in_string(var_name,"["));//a[0]-->a
    list_var_name=removeAheadSpace(list_var_name);
    bool find_var_name=FALSE;
    char arr[1000]="";
    while((fgets(arr,1000,fp))!=NULL){
        //printf("%s\n",arr);
        if(find_not_in_string(arr,":")==-1)
            continue;
        char *temp_var_name=substr(arr,0,find_not_in_string(arr,":"));
        //printf("Temp Var Name is %s\nList Var Name is %s\n",list_var_name,temp_var_name);
        if(strcmp(temp_var_name,list_var_name)==0){
            //printf("Find var name");
            find_var_name=TRUE;
            break;
        }
        
    }
    fclose(fp);
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
        strcat(output,"[");
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
    //char *output=malloc(sizeof(char)*((int)strlen(list)+1+(int)strlen(append_element)+1));
    char *output;
    //strcat(output,list);
    output=append("", list);
    if(strcmp(list,"[")!=0){
        //strcat(output,",");//[1,2,
        output=append(output, ",");
    }
    //strcat(output,append_element); //[1,2,[3,4]
    output=append(output, append_element);
    //strcat(output,"]"); //[1,2,[3,4]]
    output=append(output,"]");
   //// printf("\n\nHERE-->ouput %s\n\n\n",output);
    return output;
}
/*
 * listRemoveOneElementAtOneIndex("[1,2,3]","[1]")----->[1,3]
 * listRemoveOneElementAtOneIndex("[1,[1,2],3]","[1]")----->[1,3]
 */

char *listRemoveOneElementAtOneIndex(char *list, char *index){
   //// printf("List is %s, index is %s",list,index);
    list=removeAheadSpace(removeBackSpace(list));
    char *replace_str=valueOfListAtIndexString(list,index);
   //// printf("replace_str is %s\n",replace_str);
    //list[0]=',';   //[1,2,3]----->,1,2,3]
    //char *replace_str=malloc(sizeof(char)*((int)strlen(replace)+1));
    //strcat(replace_str,",");
    //strcat(replace_str,replace1);
    //int i=0;
    int begin_end[2];
    begin_end[0]=0;
    begin_end[1]=0;
   //// printf("Enter here\n");
    valueOfListAtIndexStringAndReturnBeginAndEnd(begin_end,list,index);
    
   //// printf("Before change, list is |%s|,replace_str is |%s|, begin %d end %d length %d\n",list,replace_str,begin_end[0],begin_end[1],(int)strlen(list));
   //// printf("%c",list[begin_end[1]]);
    //list = replace_from_index_to_index(list,replace_str,"",begin_end[0],begin_end[1]+1);
    char *output;
    output=replace_from_index_to_index(list,replace_str,"",begin_end[0],begin_end[1]);
    free(list);
    if(find_not_in_string(output,",,")!=-1){
       //// printf("Find ,,\n");
        output = replace_not_in_string(output,",,",",");
    }
    if(find_not_in_string(output,",]")!=-1){
       //// printf("Find ,]\n");
        output= replace_not_in_string(output,",]","]");
    } 
    
    if(find_not_in_string(output,"[,")!=-1){
       //// printf("Find [,\n");
        output= replace_not_in_string(output,"[,","[");
    } 
    
   //// printf("Return list is %s\n",output);
    return output; 
}
/*
 * eg listRemoveOneElementByValue("[1,2,3]","1")---->"[2,3]"
 *    listRemoveOneElementByValue("[1,2,[1,3]]","1")----->[1,[3]]
 */
char *listRemoveOneElementByValue(char *list, char *remove_value){
    char *temp1=malloc(sizeof(char)*((int)strlen(remove_value)+2));
    strcat(temp1,"[");
    strcat(temp1,remove_value);
    strcat(temp1,",");   // temp is [1,2,3]-->[1,
    if(find_not_in_string(list,temp1)!=-1)
        list=replace_not_in_string(list,temp1,"[");
    char *temp2=malloc(sizeof(char)*((int)strlen(remove_value)+2));
    strcat(temp2,",");
    strcat(temp2,remove_value);
    strcat(temp2,"]"); //temp2 is [1,2,3]--->,3];
    if(find_not_in_string(list,temp2)!=-1)
        list=replace_not_in_string(list,temp2,"]");
    char *temp3=malloc(sizeof(char)*((int)strlen(remove_value)+2));
    strcat(temp3,"[");
    strcat(temp3,remove_value);
    strcat(temp3,"]"); // temp3 is [1,2,[3],4]---->[3]
    if(find_not_in_string(list,temp3)!=-1)
        list=replace_not_in_string(list,temp3,"");
    char *temp4=malloc(sizeof(char)*((int)strlen(remove_value)+2));
    strcat(temp4,",");
    strcat(temp4,remove_value);
    strcat(temp4,","); // temp4 is [1,2,3]--->,2,
    if(find_not_in_string(list,temp4)!=-1)
        list=replace_not_in_string(list,temp4,",");
    if(find_not_in_string(list,",,")!=-1)
        list=replace_not_in_string(list,",,",",");
    return list;
}