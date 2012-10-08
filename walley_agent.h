/* 
 * File:   walley_agent.h
 * Author: shd101wyy
 *
 * Created on September 30, 2012, 4:53 PM
 */

#include "walley_language.h";
void Walley_Agent_Respond(char *walley_language_file,char *walley_language_similarity_file, char *walley_language_verb_file,char* file_var_name, char *setting_file, char *temp_file_name, char* existing_file, char* input_str) {
    printf("######### Run Function Walley_Agent_Respond ######\n");
    
    // delete #.... after sentence
    char *temp_input_str2=trim(input_str);
    int index_of_jing=find_not_in_string(temp_input_str2, "#");
    if(index_of_jing!=-1 && index_of_jing !=0){
        input_str=substr(input_str, 0, find_not_in_string(input_str, "#"));
    }
    input_str=removeBackSpace(input_str);
    printf("Now input_str is %s\n",input_str);
    //

    
    char *translate_to=Walley_Translate(walley_language_file,walley_language_similarity_file,walley_language_verb_file,file_var_name,input_str);
    
    translate_to=stringToLowerCase(translate_to);
    translate_to=removeSpaceForDictionaryListAndParenthesis(translate_to);
    if(find_not_in_string(translate_to," (")!=-1)
        translate_to=replace_not_in_string(translate_to," (","(");
    if(find_not_in_string(translate_to," :")!=-1)
        translate_to=replace_not_in_string(translate_to," :",":");
    if (find_not_in_string(translate_to, "true")!=-1)
        translate_to=replace_not_in_string(translate_to, "true","TRUE");
    if (find_not_in_string(translate_to, "false")!=-1)
        translate_to=replace_not_in_string(translate_to, "false","FALSE");

    Walley_Run_Fourth_Generation(file_var_name,setting_file,temp_file_name,existing_file,translate_to);
}
