/* 
 * File:   main.c
 * Author: shd101wyy
 *
 * Created on August 17, 2012, 12:29 PM
 */


#include "walley.h"
#include "walley_gui.h"
//#include "OpenGL/gl.h"
//#include "OpenGL/glu.h"
//#include "walley_list.h"
//#include "walley_operator.h"

int main(int argc, char *argv[]){
    
    
    ////char cwd[1000];
    ////getcwd(cwd, sizeof (cwd));
    ////printf("Current Working Directory%s\n\n\n\n\n",cwd);
    ////printf("############################################################################\n\n");
    /*
    FILE *fp;
    bool path_file_existed=TRUE;
    fp=fopen("__walley_path__.wy", "r");
    if (fp==NULL) {
        printf("Path File Does not exist\nBegin to create new Path File\n");
        path_file_existed=FALSE;
    }
    fclose(fp);
    if (path_file_existed==FALSE) {
        fp=fopen("__walley_path__.wy", "w");
        fputs("#~Walley Path File ######\n", fp);
        char *language_path=malloc(sizeof(char)*(1000));
        printf("Please enter the path of Walley_Brain folder\n");
        printf("------>");
        gets(language_path);
        fputs("__walley_path__:", fp);
        language_path=toString(language_path);
        fputs(language_path, fp);
        fputs(":string:\n", fp);
        fputs("\n", fp);
        fclose(fp);
    }
        
    
    if (argc == 1) {
        Walley_Initialize();
        Walley_Run("print('Welcome to Walley's World)");
        while (TRUE) {
            printf("\n>>> ");
            char input_str[10000];
            //scanf("%s",&input_str);
            gets(input_str);
            //printf("output is %s\n",input_str);
            if (strcmp(input_str, "exit()") == 0)
                break;
            
            Walley_Agent_Run(input_str);

        }

        Walley_Finalize();
    }
    else if (argc == 2) {
        char *param = argv[1];
        if (strcmp(param, "help") == 0) {
            printf("Walley Language 0.65\n");
            printf("Instruction:\n");
            printf("[file_name] means file_name is a variable\n\n");
            printf("walley                            ---->run line one by one\n");
            printf("walley [file_name]                ---->to run walley intelligent file (now some bugs here)\n");
            printf("walley test                       ---->begin test\n");
            printf("walley setpath                    ---->set brain path\n");
            printf("walley path                       ---->print the brain path\n");
            printf("walley version                    ---->show Walley Version\n");
            printf("walley setpath [brain folder path]---->set brain path\n");
            printf("walley recall [file_name]         ---->recall file to debug\n");
            printf("walley basic [file_name]          ---->run .wy file\n");
            printf("walley [embed type] functions     ---->show embed function ,eg walley string functions\n");
            printf("       Now support [string, list, dictionary]\n");
        }
        else if (strcmp(param,"test")==0){
            printf("begin test!");
            
            
        }
        else if (strcmp(param, "setpath")==10){
            fp=fopen("__walley_path__.wy", "w");
            fputs("#~Walley Path File ######\n", fp);
            char *language_path=malloc(sizeof(char)*(1000));
            printf("Please enter the path of Walley_Brain folder\n");
            printf("\n------>");
            gets(language_path);
            fputs("__walley_path__:", fp);
            language_path=toString(language_path);
            fputs(language_path, fp);
            fputs(":string:\n", fp);
            fputs("\n", fp);
            fclose(fp);

        }
        else if(strcmp(param, "path")==0){
            char *path=getValueFromValueName("__walley_path__.wy", "__walley_path__");
            printf("Path is |%s|\n",path);
        }
        else if(strcmp(param, "version")==0){
            printf("Walley Version Now---->0.65\n");
        }
        else {
            Walley_Initialize();
            //Walley_Run_File(param);
            Walley_Agent_Run_File(param);
            Walley_Finalize();
        }
    }
    else if (argc == 3){
        char *param1=argv[1];
        char *param2=argv[2];
        if (strcmp(param1,"setpath")==0) {
            printf("Begin to set path\n");
            printf("Set %s\n",param2);
            fp=fopen("__walley_path__.wy", "w");
            fputs("#~Walley Path File ######\n", fp);
            //char *language_path=malloc(sizeof(char)*(1000));
            //printf("Please enter the path of Walley_Brain folder\n");
            //printf("------>");
            //gets(language_path);
            fputs("__walley_path__:", fp);
            param2=toString(param2);
            fputs(param2, fp);
            fputs(":string:\n", fp);
            fputs("\n", fp);
            fclose(fp);
        }
        else if(strcmp(param1, "recall")==0){
            Walley_Initialize();
            param2=toCString(param2);
            Walley_Agent_Recall(param2);
            Walley_Finalize();
        }
        else if(strcmp(param1, "basic")==0){
            Walley_Initialize();
            param2=toCString(param2);
            Walley_Run_File(param2);
            Walley_Finalize();
        }
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
            }
            else if (strcmp(param1, "list")==0){
                printf("append\n");
                printf("length\n");
                printf("remove_at_index\n");
                printf("remove_element\n");
                printf("count\n");
            }
            else if(strcmp(param1, "dictionary")==0){
                printf("key\n");
            }
            else{
                printf("It is now under development. Sorry, I can not find functions relevent with %s\n",param1);
            }
        }
    }
    else{
        printf("......");
    }*/
    Walley_Initialize();
    Walley_Run_File("/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/walley.wy");
     
    //printf("%d",charIsInDictionary("\"a\"", 0));
    //printf("Here\n");
    //addOneSentenceWalleyLangaugeSimilarityFile("/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/__walley_language_similarity__.wy","VAR IS TIME 2|3|");
    //cleanWalleyLanguageFile("/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/__walley_language_similarity__.wy");
    //printf("%d",strcmp("VAR IS A", "VAR IS A B"));
    //cleanWalleyLanguageFile("/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/__walley_language__.wy");
    //char *apple[100];
    //apple[0]="Hello";
    //apple[1]="Hi";
    //printf("%s",apple[1]);
    //printf("%s",Walley_Eval_All_From_File("__walley__.wy","3+4,2+5"));
    //char *string="if x>10 and x<12:";
    
    //printf("%s\n",cleanUpSentence(string));
    //printf("%s\n",Walley_Analyze_Sentence_Automatically("__walley__.wy", "/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/__walley_language_similarity__.wy","/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/__walley_language_verb__.wy" , string));
    //printf("%s\n",Walley_Translate("/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/__walley_language__.wy", "/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/__walley_language_similarity__.wy", "/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/__walley_language_verb__.wy", "__walley__.wy", string));
    
    //printf("%s\n",cleanSpaceInListDictParenthesis("x = [1,2,3 ,[1,   2]  ,4]"));
    
    //char* type=checkValueType("'[]  \"   ");
    //printf("\nvalue type :%s\n",type);
    //char *a="Hello World";
    //printf("%s",substr(a,2,12));
    
    /*
     Walley_Initialize();
     
     while(TRUE){
     
     printf("\n>>> ");
     char *input;
     gets(input);
     //printf("output is %s\n",input);
     if(strcmp(input,"exit()")==0)
     break;
     //printf("---------------\n%s---------------\n",getStringFromFile("__walley_function__.wy"));
     Walley_Run(input);
     
     }
     
     Walley_Finalize();*/
    
    //printf("|%s|",Walley_Substitue_Var_And_Function_Return_Value_From_File_Third_Generation("print a","__walley__.wy"));
    //char *parameter=substr("hello()",find("hello()","(")+1,find_not_in_string("hello()",")"));
    //printf("%s %d",parameter,(int)strlen(parameter));
    //           printf("%s",variableName("Rohit.age=age"));
    //char *input="class hello extends Hi :";
    //printf("class name |%s|, mother |%s|\n",className(input),classMother(input));
    //char *input_str="[1,2,3,4]";
    //char *input=eval_simple_str("1/+3");
    //char *output=trim(input);
    //printf("|%s|",input);
    //char *a="XX:{\"hi\":1}";  //XX:{"hi":1}
    //char *b="\"hi\":";   //"hi":
    //printf("%d",find_not_in_string(a,b));):\\n    print(\"Hello\")\\n\"";
    //char *a="#Begin to define class...\ndef init(self,input_message):\n    print(\"Init\")\n    self.input_message=input_message\ndef showMessage(self):\n    print(self.input_message)\n";
    //printf("%s",formatStringInClass("abcdef",a));
    //char *b="#Begin to define class...\\ndef showMessage(self):\nprint(\"Hello\")";
    //printf("%d",checkWhetherSameInstanceExisted("__walley__.wy","a"));
    //char *x=formatStringInAnyClassFromFile("__walley__.wy","rohit","Rohit",TRUE);
    //printf("*************\n\n\n%s\n\n\n************",x);
    //printf("%d",Walley_Find_Similarity_Between_Two_Str("A AB","C A A"));
    //printf("%s",replace_not_in_string_for_times("aa Hello,Hello","a","bb",1));
    //printf("\n%s",old_slice("'Hello'","[0:2]"));
    //system("/Users/shd101wyy/Documents/workspace/NetBeans/Walley/Maxima.app/Contents/MacOS/Maxima");
    //printf("%d",checkWhetherSameClassExisted("__walley__.wy","a"));
    //printf("%s",Walley_Compare_Sentence_From_Memory("__walley_language__.wy","B"));
    
    //printf("%d",find_not_in_str_list_dict("[1,2],", ","));
    //Walley_Initialize();
    //Walley_Run_File("/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/walley.wy");
    //Walley_Agent_Run_File("/Users/shd101wyy/Documents/workspace/xcode/Walley/Walley/walley.wi");
    //Walley_Finalize();
    //Walley_Agent_Recall("/Users/shd101wyy/Documents/workspace/NetBeans/Walley/practice.wi");
    //char *a=file_readlines("file.wy");
    //printf("%s",Walley_Analyze_Sentence_Manually("x equals sum a and b"));
    //printf("%s",getVarIndexStringAsList("VAR EQUALS VAR VAR1 AND VAR3"));
    //char *dict=malloc(sizeof(char)*1000);
    //printf("%s",Walley_Analyze_Sentence_Manually_And_Return_Dictionary_For_Var("x equals 3"));
    //printf("---->\n%s",dict);
    //printf("%s\n",getValueFromVarIndex("return num1+num2","RETURN VAR","VAR"));
    //printf("%s",Walley_Translate("__walley_language__.wy","__walley__.wy","write 'hello' to 'c.txt'"));
    //printf("%s",a);
    //printf("%s",valueOfListAtIndex(a,1));
    //char *test="\"Hello,'rohit's bro\"+'Hello'";
    //int num=27;
    //printf("%d %c",charIsInString(test,num),test[num]);
    //char *x=getOneFunctionFromFileAndFormatItgetOneFunctionFromFile("math.wy","ceil","a");
    //printf("%s\n",x);
    //printf("%s",Walley_Translate("__walley_language__.wy","__walley__.wy","define function with a,b,and c"));
    //printf("%d",Walley_Find_Similarity_Between_Two_Str("PRINT VAR","PRINT(VAR)"));
    
    //char *a="define circle with radius as a function: ";
    //a=stringToUpperCase(a);
    //printf("%s",Walley_Analyze_Sentence_Automatically("__walley__.wy", a));
    
    //char x[1000];
    //scanf("%s",&x);
    //printf("%s",x);
    
    //printf("%s\n",Walley_Translate("__walley_language__.wy","__walley__.wy","x is 10"));
    
    

    
    //Walley_Run_File("/Users/shd101wyy/Documents/workspace/NetBeans/Walley/practice.wy");
    //printf("%s %d",replace_not_in_string("Hello","He",""),(int)strlen(replace_not_in_string("Hello","He","")));
    //printf("%d",isFunction("hi()"));
    //printf("%s\n",variableValueType("[0,1,2,3,4,5,6,7,8,9]"));
    //Walley_Remove_Variable_And_Value_From_File("__walley__.wy","__temp__");
    //char *x="[1,2,3,4]";
    //printf("%s",replace(x,"1","2"));
    //printf("\n|%s|\n",getValueFromValueName("__walley_settings__.wy","string_in_for_loop"));//("{a:{f:1},b:2,c:12}","{b}","13"));
    //printf("%s\n",valueOfDictionaryAtKeyString("{a:1,b:2,c:{d:2,e:4}}","{b}"));//("{'Hello':1,'World':2,a:3}","d","12"));
    //printf("%s",changeStringToList("'Hello'"));
    //printf("%s\n",removeAheadSpaceForNum("  Hello",1));
    //printf("%s\n",to_string("123123"));
    //printf("%d",find_not_in_string("'hello',Hello","ell"));
    //printf("%d\n",(int)strlen("\""));
    
    //printf("4<5 or and " );
    //printf("%d\n",find("4<5 or and "," and "));

    //char *output=countFromExpression("3+4-5");
    //Walley_Initialize();
    
    //char *output=formatStringForListInOrderToWtiteFile("x","[1,2,[1,2,3],3]");
    //char *output=valueOfListAtIndexString("[1,[1,3,3],2]","[1]");
    //int num=valueNumOfList("['Hi',[1,2,3],1,2,[1,2],3,[1,2,3,4]]");
    //printf("output--->%s\n",output);
    //printf("%s",getStringFromFile("__walley__.wy"));
    //writeVarNameAndVarValueIntoAppointedFileForList("__walley__.wy","x","[1,[1,2],3]");
    //char *output=formatStringForListInOrderToWtiteFile("a","[1,2,3,4,5,['a']]");
    //printf("Begin\n");
    //printf("%d",output);
    //Walley_Run_For_Appointed_File("__walley__.wy","__walley_settings__.wy","println('HEllo')");
    //Walley_Run_File("experiment.wy");
    //Walley_Finalize();
    //Walley_Initialize();
    //writeVarNameAndVarValueIntoAppointedFileForList("__walley_function__.wy","a","[['a'],1,2,3,4,5,['a']]");
    //printf("#####Done First#####");
    //changeTheWholeVarValueFromItsInitialOneFromFileForList("__walley_function__.wy","a","[['Hello'],1,14]");
    //changeTheOneVarValueFromItsInitialOneFromFileForList("__walley_function__.wy","a[0]","13");
    //int begin_end[2];
    //int a=valueNumOfList("[2,[2,2,[2]],[16],3,4]");
    //printf("%d",a);
    //valueOfListAtIndexStringAndReturnBeginAndEnd(begin_end,"[1,20,[12],3,4]","[2]");
    //char *str_in_wy = valueOfListAtIndexString("[[[0,1],[0]],1,[2]","[2]");
    //printf("###########str_int_wy is \n:%s\n###########\n",str_in_wy);
    //printf("begin %d\nend %d\n",begin_end[0],begin_end[1]);
    //char *output=replace_from_index_to_index("a+a+a+d","a","c",0,5);
    //printf("%s",output);
    //char *a="Hello";
    //char *b=a;
    //b="Hi";
    //printf("%s\n%s",a,b);
    //printf("|%s|\n",cleanUpSentence("create file \"/Users/shd101wyy/Documents/workspace/NetBeans/Walley/b.txt\""));
    //substitueExistedVarValueFromFile("a+b+12","__walley__.wy","__walley_function__.wy");
    //anaylizeExistedVariablesInExpression("Hi('a')+2+a1+b+cc+1+ac+Hello((1+2),d)+2+N23+23");
//char *input="def hi(a,b):\
    def sum(a,b):\
        print(\"Sum\")\
        return a+b\
    def sub(a,b):\
        print(\"Sub\")\
        return a-b\
    def time(a,b):\
        print(\"Time\")\
        return a*b\
    def divide(a,b):\
        print(\"Divide\")\
        return a/b\
    print(\"Hi\")\
    sum(a,b)\
c=hi(122,30)\
print(c)\
#done\
"
    
    //Walley_Initialize();
    //Walley_Run_File("experiment.wy");
    //Walley_Run("c=hi(1,2)");
    //Walley_Run("")
    //Walley_Run_One_Function("sum(1,2)");
    //Walley_Run("a=1\nb=2\nprint(a+b)");
    //Walley_Run_One_Function("sum(a,c)");
    //char *output=Walley_Run_One_Function_And_Return_Value("substraction(15,10)");
    //char *output=Walley_Substitue_Var_And_Function_Return_Value_From_File("1+13","__walley__.wy");
    //char *return_var_name=substitueExistedVarValueFromFile("sum_sum","__walley_temp__.wy","__walley_function__.wy");
    
    //char *output=replace_from_index_to_index("10+1+a","a","10",5,6);
    //char *output=Walley_Substitue_Var_And_Function_Return_Value_From_File("sum(a,40)+1","__walley__.wy");
    //char *output=getStringFromFile("__walley_function__.wy");
    //char *output=Walley_Eval_With_Variable("1+2");
    //printf("%s\n",output);
    //cleanFunctionFile("__walley_function__.wy");
    //Walley_Run("sum(a,40)+1");
    //int num=numOfSpaceAheadString("        print(\"Sub\")");
    //printf("%d",num);
    //bool pass=Walley_Judge_With_And_And_Or_With_Parenthesis_And_Variables_Function("20>10 and (23>10 or 3<2)","__walley__.wy");
    //printf("%d",pass);
    //anaylizeExistedVariablesInExpression("a>10----3<d+++++(a>b----3<c)");
    //bool output=isListElement("__walley__.wy","x[0]");
    //bool output=isFunction("Hello()");
    //printf("%d\n",output);
    //init_windows(argc, argv, 600, 600, 10, 10, "Hello");
    //glutDisplayFunc(&drawPoint);
    return 0;
}

