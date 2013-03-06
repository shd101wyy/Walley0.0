//
//  walley_core.h
//  Walley
//
//  Created by shd101wyy on 12-10-18.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

//
//  walley_core_final.h
//  Walley
//
//  Created by shd101wyy on 12-10-17.
//  Copyright (c) 2012年 shd101wyy. All rights reserved.
//

/*
 * File:   walley.h
 * Author: shd101wyy
 *
 * Created on August 17, 2012, 2:41 PM
 */


/*
 ################################################################################################################################
 ############################################ Attention #########################################################################
 ################################################################################################################################
 1.  The Token List here are all Token Without W_WHITESPACES 
 
 ################################################################################################################################
 ################################################################################################################################
 
*/


//#include "walley_function.h"
#include "walley_language.h"



/*
 *#################################################################################################################################
 */

void Walley_Initialize_Settings(struct VAR **settings){


    Var_addProperty(settings, "can_run_basic_input", "0", "int");

    //Var_addProperty(settings, "turn", "0", "int");

    Var_addProperty(settings, "fraction_mode", "1", "int");



}

void Walley_Initialize_Var(struct VAR **var){


    // now this function did nothing
    
    
}



void Walley_Initialize(){
    
    matho_init();

    
    Var_initVar(&VAR_var);
    Var_initVar(&VAR_settings);
    
    Str_initStringList(&TEMP_FILE);
    Str_initStringList(&FUNCTION);
    Str_initStringList(&WALLEY_EXPRESSION);
    AS_NAME="";
    //matho_init();
    
    //################ Initialize some necessary expression ##########################################################
    Str_addString(&WALLEY_EXPRESSION, "walley_show_var|show var");
    Str_addString(&WALLEY_EXPRESSION, "walley_decimal_mode|decimal mode");
    Str_addString(&WALLEY_EXPRESSION, "walley_fraction_mode|fraction mode");
    Str_addString(&WALLEY_EXPRESSION, "walley_is_fraction_mode|is fraction mode");
    
    //################################################################################################################
    
    
    
    Walley_Initialize_Var(&VAR_var);
    Walley_Initialize_Settings(&VAR_settings);
    Str_addString(&TEMP_FILE, "#Temp File In Order To Run goto");
    
    
    Str_initStringList(&STRING_IN_WHILE_LOOP);
    Str_initStringList(&STRING_IN_FOR_LOOP);
    
}

void Walley_Finalize(){
    free(VAR_var);
    free(VAR_settings);
    free(FUNCTION);
    free(TEMP_FILE);
    free(WALLEY_EXPRESSION);
// free(AS_NAME) is incorrect
}





//############################### Update Var and Var_Value to File#############################
// If var existed, then replace
// else create new one.

// Not modify
void Walley_Update_Var_And_Var_Value_To_Var(struct VAR **struct_var, char *var_name, char *var_value){
    //printf("#### Walley_Update_Var_And_Var_Value_To_File ####\n");
    //printf("var_name %s var_value %s\n",var_name,var_value);
    
    // var name type
    // 1 x
    // 2 x[0]
    // 3 x.a or x[0].a
       
    int index_of_left_bracket=find_not_in_string(var_name, "[");
    int index_of_right_bracket=find_from_behind_not_in_string(var_name, "]");
    // type 1 var_name
    if (index_of_left_bracket==-1) {
        if (Var_Existed(*struct_var, var_name)) {
            if ((variableValueType(var_value),"table")==0) {
                Table_updateTableToStructVar(struct_var, var_name, var_value);
            }
            else{
                Var_changeValueOfVar(struct_var, var_name, var_value, variableValueType(var_value));
            }
        }
        else{
            if (strcmp(variableValueType(var_value),"table")==0) {
                Table_updateTableToStructVar(struct_var, var_name, var_value);
            }
            else{
                Var_addProperty(struct_var, var_name, var_value, variableValueType(var_value));
            }
        }
    }
    // type 2 var_name
    else if(index_of_right_bracket==(int)strlen(var_name)-1){
        char *ahead_name=substr(var_name, 0, index_of_left_bracket);
        if (Var_Existed(*struct_var, ahead_name)==FALSE) {
            printf("ahead_name %s\n",ahead_name);
            Walley_Print_Error(CURRENT_INPUT_STR, "Invalid var name", 0);
        }
        else{
            // list
            if (isListElementForVar(*struct_var,var_name)) {
                changeTheOneVarValueFromItsInitialOneFromVarForList(struct_var, var_name, var_value);
            }
            // table
            else{
                char *ahead=ahead_name;
                char *string_index=substr(var_name, index_of_left_bracket, (int)strlen(var_name));
                char *temp_var_value=Var_getValueOfVar(*struct_var, ahead);
                //if (strcmp(variableValueType(temp_var_value), "table")==0) {
                    var_value=Table_addValueOrChangeValue(temp_var_value, string_index, var_value);
                    Var_changeValueOfVar(struct_var, ahead, var_value, "table");
                //}
                
            }
        }
    }
    // type 3 var_name
    else{
        if (Var_Existed(*struct_var, var_name)) {
            Var_changeValueOfVar(struct_var, var_name, var_value, variableValueType(var_value));
        }
        else{
            if (strcmp(variableValueType(var_value),"table")==0) {
                Table_updateTableToStructVar(struct_var, var_name, var_value);
            }
            else{
                Var_addProperty(struct_var, var_name, var_value, variableValueType(var_value));
            }
        }
    }
    
    /*
    char *var_value_type = variableValueType(var_value);
    bool has_same_var_name = Var_Existed(*struct_var, var_name);
    
    if (has_same_var_name == TRUE) {
        
        char *previous_var_value=Var_getValueOfVar(*struct_var,var_name);
        char *previous_var_value_type=variableValueType(previous_var_value);
        
        if (strcmp(var_value_type, "list") == 0 && find(var_name, "[") == -1) {
            
            if (find_not_in_string(var_name, "{")!=-1) {
                changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var, var_name, var_value);
            }
            //printf("Value type List, change the whole value of list to file\n");
            else  if(strcmp(previous_var_value_type,"list")==0)
                //changeTheWholeVarValueFromItsInitialOneFromFileForList(file_var_name, var_name, var_value);
                //changeTheWholeVarValueFromItsInitialOneFromVarForList(struct_var, var_name, var_value);
                Var_changeValueOfVar(struct_var, var_name, var_value, "list");
            else{
                //Walley_Remove_Variable_And_Value_From_File(file_var_name,var_name);
                Var_removeVar(struct_var, var_name);
                //writeVarNameAndVarValueIntoAppointedFileForList(file_var_name, var_name, var_value);
                writeVarNameAndVarValueIntoAppointedVarForList(struct_var, var_name, var_value);
            }
        }
        // x={a:1,b:2}, now the input is x={a:12}, so need to rewrite x.
        else if (strcmp(var_value_type, "dictionary") == 0 && find(var_name, "{") == -1) {
            if(strcmp(previous_var_value_type,"dictionary")==0){
                //changeTheWholeVarValueFromItsInitialOneFromFileForDictionary(file_var_name, var_name, var_value);
                changeTheWholeVarValueFromItsInitialOneFromVarForDictionary(struct_var, var_name, var_value);
            }
            else{
               // Walley_Remove_Variable_And_Value_From_File(file_var_name,var_name);
                Var_removeVar(struct_var, var_name);
                //writeVarNameAndVarValueIntoAppointedFileForDictionary(file_var_name, var_name, var_value);
                writeVarNameAndVarValueIntoAppointedVarForDictionary(struct_var, var_name, var_value);
            }
        }
                
        else {
            // Eg a[0] is one element of list a
            if (isListElementForVar(*struct_var, var_name)) {
                printf("IS ELEMENT FROM VAR\n");
                //changeTheOneVarValueFromItsInitialOneFromFileForList(file_var_name, var_name, var_value);
                changeTheOneVarValueFromItsInitialOneFromVarForList(struct_var, var_name, var_value);
            }
            // Eg a{"Hello"} is one element of dictionary
            else if (find_not_in_string(var_name, "{") != -1 && find_not_in_string(var_name, "}") != -1 && find_not_in_str_list_dict_parenthesis(var_name, ".")==-1) {
                //// printf("&&&&&&& Enter Here 1 \n");
                //changeTheOneVarValueFromItsInitialOneFromFileOrAddVarNameAndValueForDictionary(file_var_name, var_name, var_value);
               // printf("!!!!!!!!!!11111\n");
                changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var,var_name,var_value);
            }
            
            // x[0]=12, x is table
            // but x[0].a should not run code below
            else if (find_not_in_string(var_name,"[")!=-1&&find(var_name, ".")==-1){
                char *ahead=substr(var_name, 0, find_not_in_string(var_name, "["));
                char *string_index=substr(var_name, find_not_in_string(var_name, "["), (int)strlen(var_name));
                char *temp_var_value=Var_getValueOfVar(*struct_var, ahead);
                if (strcmp(variableValueType(temp_var_value), "table")==0) {
                    var_value=Table_addValueOrChangeValue(temp_var_value, string_index, var_value);
                    Var_changeValueOfVar(struct_var, ahead, var_value, "table");
                }
            }
            else {
                
                if(strcmp(previous_var_value_type,"dictionary")==0||strcmp(previous_var_value_type,"list")==0){
                    //Walley_Remove_Variable_And_Value_From_File(file_var_name,var_name);
                    Var_removeVar(struct_var, var_name);
                    //writeVarNameAndVarValueIntoAppointedFile(file_var_name, var_name, var_value, var_value_type);
                    Var_addProperty(struct_var, var_name, var_value, var_value_type);
                }
                //printf("&&&&&&& Enter Here 2 \n");
                //var_value = Walley_Substitute_Var_And_Function_Return_Value_From_File(var_value, file_var_name);
                //var_value = Walley_Eval_With_Variable_From_File(file_var_name, var_value);
                //var_value_type = variableValueType(var_value);
                else if(strcmp(var_value_type, "table")==0){
                    
                    Table_updateTableToStructVar(struct_var, var_name, var_value);
                }
                else{
                    Var_changeValueOfVar(struct_var, var_name, var_value, var_value_type);
                    
                }
            }
        }
    }
    
    // Does not have the same var name
    else {
        // Initialize List
        if (strcmp(var_value_type, "list") == 0) {
            
            if (find_not_in_string(var_name, "{")!=-1) {
                changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var, var_name, var_value);
            }
            else{
            
            //printf("Value type List, write the list and its value to file\n");
            //writeVarNameAndVarValueIntoAppointedFileForList(file_var_name, var_name, var_value);
            writeVarNameAndVarValueIntoAppointedVarForList(struct_var, var_name, var_value);
            }
        }
        // Initialize Dictionary
        else if (strcmp(var_value_type, "dictionary") == 0) {
            //// printf("Find Dictionary Type Value");
            //writeVarNameAndVarValueIntoAppointedFileForDictionary(file_var_name, var_name, var_value);
            
            if (find_not_in_string(var_name, "{")==-1) {
               // printf("ENTER HERE EHE\n");
                writeVarNameAndVarValueIntoAppointedVarForDictionary(struct_var, var_name, var_value);
            } else {
               // printf("ENTER HERE 2\n");
                changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var, var_name, var_value);
            }
            
            //printf("ENTER HERE EHE\n");
            //writeVarNameAndVarValueIntoAppointedVarForDictionary(struct_var, var_name, var_value);
        }            // Eg a{"Hello"} is one element of dictionary
        
        else if (strcmp(var_value_type, "table")==0){
            Table_updateTableToStructVar(struct_var, var_name, var_value);
        }
                                                                                                        // add new code here to fix x{'a'}.age=12 like problem
        else if (find_not_in_string(var_name, "{") != -1 && find_not_in_string(var_name, "}") != -1 && find_not_in_str_list_dict_parenthesis(var_name, ".")==-1) {
            //// printf("&&&&&&& Enter Here 1 \n");
            //changeTheOneVarValueFromItsInitialOneFromFileOrAddVarNameAndValueForDictionary(file_var_name, var_name, var_value);
            char *temp_var_name=substr(var_name, 0, find_not_in_string(var_name, "{"));
            if (Var_Existed(*struct_var, temp_var_name)==FALSE) {
                writeVarNameAndVarValueIntoAppointedVarForDictionary(struct_var, temp_var_name, "{}");
            }
            changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var,var_name,var_value);
        }
        
        // x[0]=12, x is table
        // x[0].a=12 x[0] is instance, so do not run code below
        else if (find_not_in_string(var_name,"[")!=-1 && find(var_name, ".")==-1){
            char *ahead=substr(var_name, 0, find_not_in_string(var_name, "["));
            
            
            
            char *string_index=substr(var_name, find_not_in_string(var_name, "["), (int)strlen(var_name));
            char *temp_var_value=Var_getValueOfVar(*struct_var, ahead);
            if (strcmp(variableValueType(temp_var_value), "table")==0) {
                var_value=Table_addValueOrChangeValue(temp_var_value, string_index, var_value);
                Var_changeValueOfVar(struct_var, ahead, var_value, "table");
            }
            else if(strcmp(variableValueType(temp_var_value), "list")==0){
                var_value=Table_addValueOrChangeValue(temp_var_value, string_index, var_value);
                Var_removeVar(struct_var, ahead);

                Var_addProperty(struct_var, ahead, var_value, "table");

            }
            else{
                Walley_Print_Error(CURRENT_INPUT_STR, "Var Name Illegal", 0);
            }
            
        }
        
        // Initialize simple value
        else {
            
            Var_addProperty(struct_var, var_name, var_value, var_value_type);
        }
    }
     */
}

/*
 *This function is mainly about  Walley_Run_One_Function_And_Return_Value. get_var_from_file_name is you get parameter
 * value from the file that you appointed.
 */
//char *Walley_Run_One_Function_And_Return_Value(char *input_str){


/*
 * ("add 1 2","add(num1,num2)|add num1 num2")
 */
char *Walley_Translate_To_Function_From_Var(char *input_str, char *best_match_sentence, struct VAR **struct_var){
    //printf("#### Walley_Translate_To_Function_From_Var ####\n");
    //printf("best match sentence |%s|, input_str |%s|\n",best_match_sentence,input_str);
    int index_of_gang=find(best_match_sentence, "|");
    if (index_of_gang==-1) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Mistake occurred while calling function Walley_Translate_To_Function\n input_str |%s|, best_match sentence error, |%s|\n",input_str,best_match_sentence);
        printf("it should be in format function|expression \n");
        exit(0);
    }
    char *function=substr(best_match_sentence, 0, index_of_gang);
    
    //if (stringIsEmpty(substr(function, find_not_in_str_list_dict(function, "(")+1, find_not_in_str_list_dict(function, ")")))==TRUE) {
    //    return function;
    //}
    
    char *expression=substr(best_match_sentence, index_of_gang+1, (int)strlen(best_match_sentence));
    expression=trim(expression);
    int num_of_small_sentence=numOfSmallSentences(input_str);
    int i=0;
    char *output=append(function, "(");
    
    
    for (i=0; i<num_of_small_sentence; i++) {
        char *sentence_at_input_str=sentenceAtIndexOfString(input_str, i);
        char *sentence_at_expression=sentenceAtIndexOfString(expression, i);
        
        
        // printf("@@ %s @@ %s\n",sentence_at_input_str,sentence_at_expression);
                                                                    // New code here on Dec 6
        if (strcmp(sentence_at_expression, sentence_at_input_str)!=0||Var_Existed(*struct_var, sentence_at_input_str)) {
            output=append(output, sentence_at_expression);
            output=append(output, "=");
            
            // New code here
            if (Var_Existed(*struct_var, sentence_at_input_str)) {
            
                sentence_at_input_str=Var_getValueOfVar(*struct_var, sentence_at_input_str);
           }
            
            output=append(output, sentence_at_input_str);
            if (i!=num_of_small_sentence-1) {
                output=append(output, ",");
            }
            // printf("@@@ %s @@@ %s\n",sentence_at_input_str,sentence_at_expression);
        }
    }
    output=append(output, ")");
    
    //// printf("WALLEY TRANSLATION |%s| |%s| |%s|\n",input_str,best_match_sentence,output);
    return output;
}

// var_value is "shd101wyy123/shd101wyy", slice is [x.find("/"):]
char *Walley_Slice(char *var_value, char *slice,struct VAR **struct_var, char ***FUNCTION_functions){
    
    slice = trim(slice);
    
    if (strcmp(variableValueType(var_value), "table")==0) {
        return Table_valueOfTableAtStringIndex(var_value, slice);
    }
    
    int count=count_str(slice, "][");
    int a=0;
    for (; a<count; a++) {
        int index=find(slice, "][");
        char *temp_slice=substr(slice, 0, index+1);
        slice=substr(slice, index+1, (int)strlen(slice));
        var_value=Walley_Slice(var_value, temp_slice, struct_var, FUNCTION_functions);
    }
    
    
    
    char *inside = substr(slice, 0 + 1, (int) strlen(slice) - 1);
    inside=trim(inside);
    //x[1:2]
    if (find_not_in_string(inside, ":") != -1) {
        int num1;
        int num2;
        if(inside[0]==':'&&inside[(int)strlen(inside)-1]==':'){
            return "None";
        }
        else if (inside[0]==':'&&inside[(int)strlen(inside)-1]!=':'){
            num1=0;
            //num2=atoi();
            //num1=Walley_Eval(num1);
            
            //num2=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(substr(slice, find_not_in_string(slice, ":") + 1, (int)strlen(slice)-1), struct_var, FUNCTION_functions));
            num2=atoi(substr(slice, find_not_in_string(slice, ":") + 1, (int)strlen(slice)-1));
            
            
            return sliceOnlyIncludeLeftSide(var_value,num1,num2);
        }
        else if (inside[0]!=':'&&inside[(int)strlen(inside)-1]==':'){
            
            //num1=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(substr(slice, 1, find_not_in_string(slice, ":")),struct_var,FUNCTION_functions));
            num1=atoi(substr(slice, 1, find_not_in_string(slice, ":")));

            
            if(strcmp(variableValueType(var_value),"list")==0){
                num2=valueNumOfList(var_value);
            }
            else if (strcmp(variableValueType(var_value),"string")==0){
                num2=(int)strlen(toCString(var_value));
            }
            return sliceOnlyIncludeLeftSide(var_value, num1, num2);
        }
        else {
            //num1 = atoi(substr(slice, 1, find(slice, ":")));
            //num2 = atoi(substr(slice, find(slice, ":") + 1, right));
            //num1=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(substr(slice, 1, find_not_in_string(slice, ":")),struct_var,FUNCTION_functions));
            //num2=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(substr(slice, find_not_in_string(slice, ":") + 1, (int)strlen(slice)-1),struct_var,FUNCTION_functions));
            num1=atoi(substr(slice, 1, find_not_in_string(slice, ":")));
            num2=atoi(substr(slice, find_not_in_string(slice, ":") + 1, (int)strlen(slice)-1));
            return sliceOnlyIncludeLeftSide(var_value, num1, num2);
        }
        
        
    }
    
    // I stop using this kind of slice on Jan 3 2013
    // x[1,2]
    /*
    else if (find_not_in_string(inside, ",") != -1) {
        int num1;
        int num2;
        if(inside[0]==','&&inside[(int)strlen(inside)-1]==','){
            return "None";
        }
        else if (inside[0]==','&&inside[(int)strlen(inside)-1]!=','){
            num1=0;
            //num2=atoi(substr(slice, find(slice, ",") + 1, right));
            //num1=Walley_Eval(num1);
            num2=atoi(Walley_Eval(substr(slice, find_not_in_string(slice, ",") + 1, (int)strlen(slice)-1)));
            return sliceOnlyIncludeLeftSide(input_str,num1,num2);
        }
        else if (inside[0]!=','&&inside[(int)strlen(inside)-1]==','){
            char *type=variableValueType(input_str);
            //num1=atoi(substr(slice, 1, find(slice, ",")));
            if(strcmp(type,"list")==0){
                num2=valueNumOfList(input_str);
            }
            else if (strcmp(input_str,"string")==0){
                num2=(int)strlen(toCString(input_str));
            }
            num1=atoi(Walley_Eval(substr(slice, 1, find_not_in_string(slice, ","))));
            //num2=Walley_Eval(num2);
            return sliceOnlyIncludeLeftSide(input_str, num1, num2);
        }
        else {
            //num1 = atoi(substr(slice, 1, find(slice, ",")));
            //num2 = atoi(substr(slice, find(slice, ",") + 1, right));
            num1=atoi(Walley_Eval(substr(slice, 1, find_not_in_string(slice, ","))));
            num2=atoi(Walley_Eval(substr(slice, find_not_in_string(slice, ",") + 1, (int)strlen(slice)-1)));
            return sliceOnlyIncludeLeftSide(input_str, num1, num2);
        }
        
        
    }
    */
    //x[0]
    else {
        //printf("here\n");
        char *num_str = substr(slice, 1, (int)strlen(slice)-1);
        //printf("num_str %s\n",num_str);
        //int num=atoi(Walley_Substitute_Var_And_Function_Return_Value_From_Var(num_str,struct_var,FUNCTION_functions));
        int num=atoi(num_str);

        if (strcmp("string", variableValueType(var_value)) == 0) {
            //// printf("it is string\n");
            //// printf("num is %d\n",num);
            var_value = toCString(var_value);
            char *output = substr(var_value, num, num + 1);
            //// printf("return is %s\n",toString(output));
            return toString(output);
        } else if (strcmp("list", variableValueType(var_value)) == 0) {
            //// printf("it is list\n");
            char *output = (char*)malloc(sizeof(char)*1000);
            
            char *value_at_index = valueOfListAtIndexString(var_value, slice);
            strcpy(output, value_at_index);
            
            
            //strcat(output, "]");
            int i = 0;
            char *output2 = (char*)malloc(sizeof (char) *((int) strlen(output) + 1));
            for (i = 0; i < (int) strlen(output); i++) {
                output2[i] = output[i];
            }
            output2[(int) strlen(output)] = 0;
            return output2;
            
        }
        else{
            printf("@@ |%s|\n",CURRENT_INPUT_STR);

            printf("Mistake occurred while calling function slice\nIt is not a slice or value type wrong\n");
            printf("If you want use dictionary, please try x{'a'} like expression\n");
            exit(0);
        }
    }    
    
}





void Walley_Update_Functions_And_Vars_While_Importing(char *temp_file_to_run, struct VAR **struct_var, char ***FUNCTION_functions){
    

    // New code here to import
    struct VAR *temp_struct_var;
    Var_initVar(&temp_struct_var);
    struct VAR *temp_struct_settings;
    Var_initVar(&temp_struct_settings);

    char **temp_TEMP_FILE;Str_initStringList(&temp_TEMP_FILE);
    char **temp_FUNCTION_functions;Str_initStringList(&temp_FUNCTION_functions);
    
    
    Walley_Initialize_Var(&temp_struct_var);
    Walley_Initialize_Settings(&temp_struct_settings);
    
    
    
    //Walley_Run_For_Appointed_Var_String_List(&temp_struct_var, &temp_struct_settings, &temp_TEMP_FILE, temp_file_to_run, &temp_FUNCTION_functions, getStringFromFileAndReturnStringList(temp_file_to_run));
    Walley_Parse_String_List(&temp_struct_var, &temp_struct_settings, temp_file_to_run, &temp_FUNCTION_functions, getStringFromFileAndReturnStringList(temp_file_to_run));    
    //printf("####################\n");
    //Var_PrintVar(temp_struct_var);
    //printf("####################\n");
    int i=0;
    int length_of_temp_struct_var=0;
    if (strcmp((temp_struct_var)->var_name,"__size_of_array__")!=0) {
        printf("@@ |%s|\n",CURRENT_INPUT_STR);

        printf("Can not find __size_of_array__");
        exit(0);
    }
    else{
        length_of_temp_struct_var=atoi((temp_struct_var)->var_value);
    }

    
    while (i<length_of_temp_struct_var) {
        char *var_name=temp_struct_var[i].var_name;
        // prevent from deleting those important variables.
        if (
            find(var_name, "__size_of_array__")==0
            ) {
        }
        else{
            //printf("Begin To Add Var\n");
            Var_addProperty(struct_var, append(append(substr(AS_NAME, 1, (int)strlen(AS_NAME)), "."), var_name), temp_struct_var[i].var_value, variableValueType(temp_struct_var[i].var_value));
        }
        
        i=i+1;
    }
        
    
    /*
    char *__temp_class__=Var_getValueOfVar(temp_struct_var, "__temp_class__");
    char *__string_in_temp_class__=Var_getValueOfVar(temp_struct_var, "__string_in_temp_class__");
    char *class_list=keyOfDictionaryAsList(__temp_class__);
    //printf("class_list is %s\n",class_list);
    int num_of_key_of_dictionary=valueNumOfList(class_list);
    i=0;
    for (; i<num_of_key_of_dictionary; i++) {
        char *key=valueOfListAtIndex(class_list, i);
        char *string_in_class=valueAtKey(__string_in_temp_class__, key);
        //printf(" class name --->%s\n|%s|\n",valueOfListAtIndex(class_list, i),string_in_class);
        char *new_class_name=append(append(substr(AS_NAME, 1, (int)strlen(AS_NAME)), "."), toCString(valueOfListAtIndex(class_list, i)));
        char *change_dictionary=append("__string_in_temp_class__", append("{", append( toString(new_class_name), "}")));
        //printf("@@change_dictionary is %s\n",change_dictionary);
        changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var, change_dictionary, string_in_class);
        
        char *mother=valueAtKey(__temp_class__, key);
        char *change_dictionary2=append("__temp_class__", append("{", append( toString(new_class_name), "}")));
        changeTheOneVarValueFromItsInitialOneFromVarOrAddVarNameAndValueForDictionary(struct_var, change_dictionary2, mother);

    }*/
    
   
    char *function_list=getFunctionNameAndReturnList(temp_FUNCTION_functions);
    int num_of_function_in_list=valueNumOfList(function_list);
    i=0;
    for (i=0; i<num_of_function_in_list; i++) {
        int j=0;
        int length_of_temp_FUNCTION_functions=atoi(temp_FUNCTION_functions[0]);
        while (j<length_of_temp_FUNCTION_functions) {
            char *func_now=valueOfListAtIndex(function_list, i);
            //printf("------> |%s|\n",temp_FUNCTION_functions[j]);
            //printf("#%s\n",append(func_now, ":"));
            if (find(temp_FUNCTION_functions[j],append(func_now, ":"))==0) {
                //  printf("FIND %s from %s\n",append(func_now, ":"),temp_FUNCTION_functions[j]);
                temp_FUNCTION_functions[j]=append(append(substr(AS_NAME, 1, (int)strlen(AS_NAME)), "."), temp_FUNCTION_functions[j]);
                j++;
                continue;
            } else {
                func_now=append(func_now, "(");
                int begin=0;
                int index_of_func=0;
                while (TRUE) {
                    //x=a()*a()+b()
                    index_of_func=find_from_index(temp_FUNCTION_functions[j], func_now, begin);
                    if (index_of_func==-1) {
                        break;
                    }
                    // printf("index_of_func is %d\n",index_of_func);
                    int left=find_from_index(temp_FUNCTION_functions[j], "(", index_of_func);
                    // printf("left is %d\n",left);
                    int right=indexOfMostOutterBracket(temp_FUNCTION_functions[j], left);
                    // printf("right is %d\n",right);
                    char *replace_str=substr(temp_FUNCTION_functions[j], index_of_func, right+1);
                    // printf("replace str is %s\n",replace_str);
                    if (index_of_func==-1) {
                        break;
                    }
                    else if(index_of_func==0){
                        char *with_str=append(append(substr(AS_NAME, 1, (int)strlen(AS_NAME)), "."), replace_str);
                        temp_FUNCTION_functions[j]=replace_from_index_to_index(temp_FUNCTION_functions[j], replace_str, with_str, index_of_func, right+1);
                        begin=right+1+(int)strlen(with_str)-(int)strlen(replace_str);
                        continue;
                        
                    }else{
                        if (isalpha(temp_FUNCTION_functions[j][index_of_func-1])||isdigit(temp_FUNCTION_functions[j][index_of_func-1])||temp_FUNCTION_functions[j][index_of_func-1]=='_') {
                            begin=right+1;
                            continue;
                        }
                        else{
                            char *with_str=append(append(substr(AS_NAME, 1, (int)strlen(AS_NAME)), "."), replace_str);
                            temp_FUNCTION_functions[j]=replace_from_index_to_index(temp_FUNCTION_functions[j], replace_str, with_str, index_of_func, right+1);
                            begin=right+1+(int)strlen(with_str)-(int)strlen(replace_str);
                            continue;
                        }
                    }
                    
                }
                
                j++;
            }
        }
    }
   
    
    i=0;
    int length_of_temp_FUNCTION_functions=atoi(temp_FUNCTION_functions[0]);
    while (i<length_of_temp_FUNCTION_functions) {
        Str_addString(FUNCTION_functions, temp_FUNCTION_functions[i]);
        i++;
    }
   }

