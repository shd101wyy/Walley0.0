/* 
 * File:   main.c
 * Author: shd101wyy
 *
 * Created on August 17, 2012, 12:29 PM
 */


//#include "walley.h"
//#include "walley_gui.h"
//#include "OpenGL/gl.h"
//#include "OpenGL/glu.h"
//#include "walley_list.h"
//#include "walley_operator.h"
#include "walley.h"
int main(int argc, char **argv){
    
    
    //printf("%d\n",List_checkWhetherIndexAvailable("[1,[3,4],2]","[3]"));
    //printf("%s\n",Table_formatTable("[a=12]"));
    //int begin_end[2];
    //begin_end[0]=0;
    //begin_end[1]=0;
    //valueOfListAtIndexStringAndReturnBeginAndEnd(begin_end, "[0,[11,344],22]", "[2]");
    //exit(0);
    
    ARGV=argv;
    ARGC=argc;
    
    clock_t start,end;
    double run_time;
    start= clock();

    
    Str_initStringList(&INSTANCE_NAMES_LIST);
    CLASS_initCLASSList(&CLASS_LIST);
    //TL_initTokenList(&VAR_VALUE_TO_BE_COMPLETE);
    ////char cwd[1000];
    ////getcwd(cwd, sizeof (cwd));
    ////printf("Current Working Directory%s\n\n\n\n\n",cwd);
    ////printf("############################################################################\n\n");
    
    //glutInit(&argc, argv);
    
    
    

    
    
    char *string_in_out_wy="def print(input_str):\n\
    exp:\n\
        print input_str\n\
    walley_print(input_str)\n\
    \n\
def println(input_str):\n\
    exp:\n\
        println input_str\n\
    walley_println(input_str)\n\
    \n\
def random(num1=0,num2=1):\n\
    exp:\n\
        random from num1 to num2\n\
    decimal mode\n\
    output=walley_random()*(num2-num1)+num1\n\
    return output";

    if (argc == 1) {
        Walley_Initialize();
        
        
        
        
        // Pre-Run file
     
        //Walley_Parse_File("/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/out.wy");
        //Walley_Parse_File("/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/var.wy");
     
        // Change to
        /*
        
        Walley_Run(string_in_out_wy);
        Walley_Run("print(\"Welcome to Walley's World\")");
        while (TRUE) {
            printf("\n>>> ");
            char input_str[10000];
            gets(input_str);
            if (strcmp(input_str, "exit()") == 0)
                break;
            Walley_Run(input_str);
        }
        
        Walley_Finalize();
         */
        printf("Use Walley_Parse_Simple_String which is still under development\n");
        Walley_Initialize();
        //Walley_Parse(string_in_out_wy);
        Walley_Parse("print \"Welcome to Walley's World\"");
        
        Walley_Parse_String_List_Default(TO_RUN);
        
        while (TRUE) {
            printf("\n>>> ");
            char input_str[10000];
            gets(input_str);
            if (strcmp(input_str, "exit()") == 0)
                break;
            Walley_Parse(input_str);
        }
        
        Walley_Finalize();

    }
    else if (argc == 2) {
        char *param = argv[1];
        if (strcmp(param, "help") == 0) {
            printf("Walley Language 1.19\n");
            printf("Instruction:\n");
            printf("[file_name] means file_name is a variable\n\n");
            printf("walley                            ---->run line one by one\n");
            printf("walley [file_name]                ---->to run walley intelligent file (now some bugs here)\n");
            printf("walley test                       ---->begin test\n");
            //printf("walley setpath                    ---->set brain path\n");
            //printf("walley path                       ---->print the brain path\n");
            printf("walley version                    ---->show Walley Version\n");
            //printf("walley setpath [brain folder path]---->set brain path\n");
            //printf("walley recall [file_name]         ---->recall file to debug\n");
            printf("walley basic [file_name]          ---->run .wy file\n");
            printf("walley [embed type] functions     ---->show embed function ,eg walley string functions\n");
            printf("       Now support [string, list, dictionary]\n");
            printf("walley compile [file_name]        ---->compile file to wyc format file\n");
            printf("walley exec [file_name]           ---->create exectuable file by using gcc\n");
            printf("walley exec [file_name] [include 'walley.h' path]         ---->create exectuable file by using gcc\n");
            printf("walley lex [string]               ---->lex analysis test");
            printf("walley torun [file_name]          ---->format string from file to get string list");
            
        }
        else if (strcmp(param,"test")==0){
            printf("begin test!");
            
            
        }
        else if(strcmp(param, "version")==0){
            printf("Walley Version Now---->1.19\n");
        }
        else if(strcmp(param, "parse")==0){
            printf("Use Walley_Parse_Simple_String which is still under development\n");
                Walley_Initialize();
                //Walley_Parse(string_in_out_wy);
                Walley_Parse("print \"Welcome to Walley's World\"");
                while (TRUE) {
                    printf("\n>>> ");
                    char input_str[10000];
                    gets(input_str);
                    if (strcmp(input_str, "exit()") == 0)
                        break;
                    Walley_Parse(input_str);
                }
                
                Walley_Finalize();
        }
        else {
            /*
            Walley_Initialize();
            
            
            // Pre-Run file
     
            // Walley_Parse_File("/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/out.wy");
            // Walley_Parse_File("/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/var.wy");
     
            // Change to
            Walley_Run(string_in_out_wy);

            char *path="./";
            char *file_name=param;
            if (find(param, "/")!=-1) {
                path=substr(param, 0, find_from_behind(param, "/")+1);
                CURRENT_DIRECTORY=path;
                //file_name=substr(param,find_from_behind(param, "/")+1,(int)strlen(param));
                //printf("file name %s, path %s\n",file_name,path);
                //char *temp=append("cd ", path);
                //printf("temp is %s\n",temp);
                //system(temp);
                //system("ls");
            }
            
            FIRST_RUNNING_FILE=file_name;
            
            Walley_Parse_File(file_name);
            
            
            Walley_Finalize();
             */
            Walley_Initialize();
            
            Walley_Parse_String_List_Default(changeStringToStringList(string_in_out_wy));
            
            char *path="./";
            char *file_name=param;
            if (find(param, "/")!=-1) {
                path=substr(param, 0, find_from_behind(param, "/")+1);
                CURRENT_DIRECTORY=path;
            }
            
            FIRST_RUNNING_FILE=file_name;
            
            Walley_Parse_File(file_name);
            
            
            Walley_Finalize();

        }
    }
    else if (argc == 3){
        char *param1=argv[1];
        char *param2=argv[2];
        if (strcmp(param2, "functions")==0) {
            if (strcmp(param1, "string")==0) {
                printf("find\n");
                printf("replace\n");
                printf("count\n");
                printf("split\n");
                printf("length\n");
                printf("trim\n");
                printf("isdigit\n");
                printf("isalpha\n");
                printf("toupper\n");
                printf("tolower\n");
                printf("isupper\n");
                printf("islower\n");
                printf("reverse\n");
            }
            else if (strcmp(param1, "list")==0){
                printf("append\n");
                printf("length\n");
                printf("remove_at_index\n");
                printf("remove_element\n");
                printf("count\n");
            }
            else if(strcmp(param1, "dictionary")==0){
                printf("keys\n");
            }
            else{
                printf("It is now under development. Sorry, I can not find functions relevent with %s\n",param1);
            }
        }
        else if(strcmp(param1, "compile")==0){
            char *file_name=param2;
            char *make_file=append(file_name, "c");
            printf("Begin to compile....\n");
            char *string_in_file=getStringFromFile(file_name);
            char *binary=changeTextToBinary(string_in_file);

            FILE *compile_file=fopen(make_file, "w");
            fputs(binary, compile_file);
            fclose(compile_file);
            
            printf("Finish compiling\nFile %s created\n",make_file);
        }
        else if(strcmp(param1, "exec")==0){
            char *wy_file=param2;
            char *file_name=substr(param2, 0, find(param2, "."));
            printf("Begin to make exec file...\n");
            char *temp_file_name=append(file_name, ".c");
            FILE *temp_file=fopen(temp_file_name, "w");
            
            
            
char *copy_text="\
            //\n\
            //  main.c\n\
            //  WalleyExec\n\
            //\n\
            //  Created by shd101wyy on 12-11-28.\n\
            //  Copyright (c) 2012年 shd101wyy. All rights reserved.\n\
            //\n\
            \n\
#include <stdio.h>\n\
#include \"walley.h\"\n\
int main(int argc, char **argv)\n\
{\n\
char *string_in_out_wy=\"def print(input_str):\\n\\\n\
    exp:\\n\\\n\
        print input_str\\n\\\n\
    walley_print(input_str)\\n\\\n\
    \\n\\\n\
def println(input_str):\\n\\\n\
    exp:\\n\\\n\
        println input_str\\n\\\n\
    walley_println(input_str)\\n\\\n\
    \\n\\\n\
def random(num1=0,num2=1):\\n\\\n\
    exp:\\n\\\n\
        random from num1 to num2\\n\\\n\
    decimal mode\\n\\\n\
    output=walley_random()*(num2-num1)+num1\\n\\\n\
    return output\\n\\\n\
    \";\
            \n\
            \n\
    //#######################\n\
    Walley_Initialize();\n\
    Walley_Run(string_in_out_wy);\n\
    Walley_Parse_File(FILE_NAME);\n\
    Walley_Finalize();\n\
            \n\
    // insert code here...\n\
    return 0;\n\
            }";
            copy_text=replace(copy_text, "FILE_NAME",toString(wy_file) );
            fputs(copy_text, temp_file);
            fclose(temp_file);
            //printf("\n%s\n",copy_text);
            char *C_COMPILER="";
#ifdef __clang__
            printf("Begin to use Clang to compile\n");
            C_COMPILER="clang";
#elif __GNUC__
            printf("Begin to use GNU GCC to compile\n");
            C_COMPILER="gcc";
#else
            printf("No Clang or GNU GCC detect...exit");
            exit(0);
#endif
            
            char *systemp_to_run=append(C_COMPILER, " -g -o #FILE_NAME #TEMP_FILE_NAME -lm -I /Users/shd101wyy/Documents/workspace/xcode/Walley/Walley");
            systemp_to_run=replace(systemp_to_run, "#FILE_NAME", file_name);
            systemp_to_run=replace(systemp_to_run, "#TEMP_FILE_NAME", temp_file_name);
            //printf("\nsystem_to_run is %s\n",systemp_to_run);
            system(systemp_to_run);
            //remove(temp_file_name);
        }

        
        
        else if(strcmp(param1, "lex")==0){
            printf("Begin Lexical Analysis Test\n");
            printf("Begin to test |%s|\n",param2);
            param2=toCString(param2);
            struct TOKEN *token=Walley_Lexica_Analysis(param2);
            TL_PrintTOKEN(token);
        }
        else if(strcmp(param1, "torun")==0){
            printf("Begin to get TO_RUN string list\n");
            printf("From file |%s|\n",param2);
            param2=toCString(param2);
            
            Walley_Tool_get_TO_RUN_From_File(param2);
        }
        else if(strcmp(param1, "parse")==0){
            Walley_Initialize();
            
            Walley_Parse_String_List_Default(changeStringToStringList(string_in_out_wy));
            
            char *path="./";
            char *file_name=param2;
            if (find(param2, "/")!=-1) {
                path=substr(param2, 0, find_from_behind(param2, "/")+1);
                CURRENT_DIRECTORY=path;
            }
            
            FIRST_RUNNING_FILE=file_name;
            
            Walley_Parse_File(file_name);
            
            
            Walley_Finalize();

        }
    }
    else if(argc==4){
        if (strcmp(argv[1], "exec")==0) {
            char *param2=argv[2];
            char *wy_file=param2;
            char *file_name=substr(param2, 0, find(param2, "."));
            char *include_walley_h_path=argv[3];
            
            printf("Begin to make exec file...\n");
            char *temp_file_name=append(file_name, ".c");
            FILE *temp_file=fopen(temp_file_name, "w");
            
            
            
            char *copy_text="\
            //\n\
            //  main.c\n\
            //  WalleyExec\n\
            //\n\
            //  Created by shd101wyy on 12-11-28.\n\
            //  Copyright (c) 2012年 shd101wyy. All rights reserved.\n\
            //\n\
            \n\
            #include <stdio.h>\n";
            copy_text=append(copy_text, append("#include \"", append(include_walley_h_path, "\"\n")));
            
            
            
            char *temp="int main(int argc, char **argv)\n\
{\n\
char *string_in_out_wy=\"def print(input_str):\\n\\\n\
    exp:\\n\\\n\
        print input_str\\n\\\n\
    walley_print(input_str)\\n\\\n\
    \\n\\\n\
def println(input_str):\\n\\\n\
    exp:\\n\\\n\
        println input_str\\n\\\n\
    walley_println(input_str)\\n\\\n\
    \\n\\\n\
def random(num1=0,num2=1):\\n\\\n\
    exp:\\n\\\n\
        random from num1 to num2\\n\\\n\
    decimal mode\\n\\\n\
    output=walley_random()*(num2-num1)+num1\\n\\\n\
    return output\\n\\\n\
            \";\
            \n\
            \n\
            //#######################\n\
    Walley_Initialize();\n\
    Walley_Run(string_in_out_wy);\n\
    Walley_Parse_File(FILE_NAME);\n\
    Walley_Finalize();\n\
            \n\
    // insert code here...\n\
    return 0;\n\
            }";
            copy_text=append(copy_text, temp);
            copy_text=replace(copy_text, "FILE_NAME",toString(wy_file) );
            fputs(copy_text, temp_file);
            fclose(temp_file);
            //printf("\n%s\n",copy_text);
            
            
            char *C_COMPILER="";
            #ifdef __clang__
            printf("Begin to use Clang to compile\n");
            C_COMPILER="clang";
            #elif __GNUC__
            printf("Begin to use GNU GCC to compile\n");
            C_COMPILER="gcc";
            #else
            printf("No Clang or GNU GCC detect...exit");
            exit(0);
            #endif
            
            
            char *systemp_to_run=append(C_COMPILER, append(" -g -o #FILE_NAME #TEMP_FILE_NAME -lm -I ",include_walley_h_path));

            systemp_to_run=replace(systemp_to_run, "#FILE_NAME", file_name);
            systemp_to_run=replace(systemp_to_run, "#TEMP_FILE_NAME", temp_file_name);
            //printf("\nsystem_to_run is %s\n",systemp_to_run);
            system(systemp_to_run);
            //remove(temp_file_name);
        }
    }
    else{
        printf("......");
    }
    

    
    end=clock();
    run_time = (end - start) / (double) CLOCKS_PER_SEC ;
    printf("\n\nFinish Program\n");
    printf ("Run time is %g seconds\n", run_time);
    printf ("press any key to quit\n");
    getchar();
    
    return 0;
}


