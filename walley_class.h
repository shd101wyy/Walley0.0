/* 
 * File:   walley_class.h
 * Author: shd101wyy
 *
 * Created on September 18, 2012, 2:41 PM
 */

#include "walley_slice.h"
/*
 *Define a Class
 * 
 * format:
 * class Hi:
 *     def showMessage(input_message):
 *         print("hello")
 * class Hello extends Hi:
 *     def showMessage2(input_message):
 *         print("hello2")
 * 
 *
 *  
*/

/*
 * This  function is mainly to get the class name
 * eg className("class hello:")------>hello
 * eg className("class hello extends hi:")------>hello
 * !!!! class_name can not be 'extends' or 'class'
 */
char *className(char *input_str){
    input_str=trim(input_str);
    char *class_name;
    int begin=find_not_in_string(input_str,"class ")+6;
    int end;
    if(find_not_in_string(input_str," extends ")==-1){
        end=find_from_index(input_str,":",begin+1);
        if(end==-1){
            printf("class define mistake occurred. please check.\nThe format should be 'class hi:' or 'class hi extends hello:");
            exit(0);
        }
        class_name=substr(input_str,begin,end);
        class_name=trim(class_name);
    }
    else{
        end=find_from_index(input_str," extends ",begin+1);
        class_name=substr(input_str,begin,end);
        class_name=trim(class_name);
    }
    return class_name;
}
/*
 * classMother is mainly to get what the class extends.
 * eg classMother("class hello:")------>"None"
 *    classMother("class hello extends hi:")------>"hi"
 */
char *classMother(char *input_str){
    input_str=trim(input_str);
    char *mother;
    if(find_not_in_string(input_str," extends ")==-1){
        mother="None";
    }
    else{
        int begin=find(input_str," extends ")+9;
        int end=find_from_index(input_str,":",begin+1);
        mother=substr(input_str,begin,end);
        mother=trim(mother);
    }
    return mother;
}

/*
 * This function now works without class extends
 * class hi:
 *     def showMessage(self):
 *         print("Hello")
 * 
 * then after run I can get __temp_string_in_class_sentence__=""#Begin to define class...\ndef showMessage(self):\n    print("Hello")\n""
 * put that string to string_in_class as parameter.
 * eg formatStringInClass("__walley__.",hi",#Begin to define class...\ndef showMessage(self):\n    print("Hello")\n")
 * 
 */
char *formatStringInClass(char *instance_name, char *string_in_class){
    printf("#### formatStringInClass ####\n");
    if(string_in_class[0]=='"'|| string_in_class[0]=='\''){
        string_in_class=substr(string_in_class,1,(int)strlen(string_in_class)-1);
        printf("''''''");
    }// "def ..."--->def ...
    printf("|%s|\n\n",string_in_class);    
    // instance is a  //a=hi()
    // then instance_dot="a."
    
    char temp[1000]="";
    strcat(temp,instance_name);
    strcat(temp,".");
    printf("temp length %d\n",(int)strlen(temp));
    char *instance_dot=malloc(sizeof(char)*((int)strlen(temp)+1));

    int i=0;
    for(i=0;i<(int)strlen(temp);i++){
        instance_dot[i]=temp[i];
    }
    instance_dot[(int)strlen(instance_dot)]=0;
   

    
    
    printf("%s %d\n",instance_dot,(int)strlen(instance_dot));
    // change self.year=10 -----> a.year=10
    string_in_class=replace_not_in_string(string_in_class,"self.",instance_dot);
    printf("|%s|\n\n",string_in_class);    
    // change showMessage(self,input_str):------->a.showMessage(input_str):
    // change showMessage(self):------->a.showMessage():
    // so I need to find "def " and "(self"
    int define=0;
    int left;   //find ( of def input():
    int right;
    char *temp_string_in_class=string_in_class;
    while(TRUE){
        printf("---->|%s|\n",temp_string_in_class);
        define=find_from_index_not_in_string(string_in_class,"def ",define+1);  
        left=find_from_index(string_in_class,"(",define+4);   //find ( of def input():
        right=find_from_index_not_in_string(string_in_class,")",left);
        // Did not find 'def '
        if(define==-1)
            break;
        printf("FIND DEFINE\n");
        char *string_in_parenthesis;
        char *whole_function=substr(string_in_class,define,right+1); //get 'def hello(self,input)' without ':'
        char *func_name=functionName(whole_function); //               get hello
        printf("###### func name is %s ####\n",func_name);
        if(left+1!=right){
            string_in_parenthesis=substr(string_in_class,left+1,right);//get self,input
            if(stringIsEmpty(string_in_parenthesis))
                string_in_parenthesis="";
        }
        else
            string_in_parenthesis="";
        if(find_not_in_string(string_in_parenthesis,"self")!=-1){
            // find self in parameter.
            string_in_parenthesis=replace_not_in_string(string_in_parenthesis,"self","");
 
            char *new_func_name=malloc(sizeof(char)*((int)strlen(func_name)+(int)strlen(instance_name)+1));
            strcat(new_func_name,instance_name);
            strcat(new_func_name,".");
            strcat(new_func_name,func_name);// change func name of  hello(self) to------>a.hello(self).
            func_name=new_func_name;
        }
        
        // change 'def hello(self)'--->'def a.hello()'
        char *new_function=malloc(sizeof(char)*((int)strlen("def ()")+(int)strlen(func_name)+(int)strlen(string_in_parenthesis)));
        strcat(new_function,"def ");
        strcat(new_function,func_name);
        strcat(new_function,"(");
        strcat(new_function,string_in_parenthesis);
        strcat(new_function,")");
        temp_string_in_class=replace_from_index_to_index(temp_string_in_class,whole_function,new_function,define-1,right+1);
        if (find_not_in_string(temp_string_in_class, "(,") != -1)
            temp_string_in_class = replace_not_in_string(temp_string_in_class, "(,", "(");
        else if (find_not_in_string(temp_string_in_class, ",)") != -1)
            temp_string_in_class = replace_not_in_string(temp_string_in_class, ",)", ")");
    }
    
    string_in_class = temp_string_in_class;
    
    // delete (self, and (self) and ,self) while has no def ahead. super.init(self)
    int super_position=find_not_in_string(temp_string_in_class," super.");
    
    while(super_position!=-1){
        printf("FIND Super.\n");
        left=find_from_index_not_in_string(temp_string_in_class,"(",super_position+6);
        right = find_from_index_not_in_string(temp_string_in_class, ")", left);
        char *string_in_parenthesis; // = substr(string_in_class, left + 1, right);
        if (left + 1 != right) {
            string_in_parenthesis = substr(temp_string_in_class, left + 1, right); //get self,input
            if (stringIsEmpty(string_in_parenthesis))
                string_in_parenthesis = "";
        } else {
            string_in_parenthesis = "";
        }
        if (find_not_in_string(string_in_parenthesis, "self") != -1) {
            
            char *whole_function=substr(temp_string_in_class,super_position,right+1); //get ' super.init(self)'
            printf("------ whole function is %s -------\n\n\n",whole_function);
            char *func_name=substr(temp_string_in_class,super_position,left);
            func_name=trim(func_name);
            printf("------ func name is %s -------\n\n\n ",func_name);
            string_in_parenthesis=replace_not_in_string(string_in_parenthesis,"self","");
            char *new_function_name = malloc(sizeof (char) *((int) strlen(func_name)+(int) strlen(instance_name) + 3));
            strcat(new_function_name, " ");
            strcat(new_function_name, instance_name);
            strcat(new_function_name, ".");
            strcat(new_function_name,func_name); //' rohit.super.init
            new_function_name[(int) strlen(new_function_name)] = 0;

            char *new_function = malloc(sizeof (char) *((int) strlen("()")+1+(int) strlen(new_function_name)+(int) strlen(string_in_parenthesis)));
            
            strcat(new_function, new_function_name);
            strcat(new_function, "(");
            strcat(new_function, string_in_parenthesis);
            strcat(new_function, ")");
            
            new_function[(int) strlen(new_function)] = 0;
            temp_string_in_class = replace_from_index_to_index(temp_string_in_class, whole_function, new_function,super_position-1,right+1);
            if (find_not_in_string(temp_string_in_class, "(,") != -1)
                temp_string_in_class = replace_not_in_string(temp_string_in_class, "(,", "(");
            else if (find_not_in_string(temp_string_in_class, ",)") != -1)
                temp_string_in_class = replace_not_in_string(temp_string_in_class, ",)", ")");
        }
        super_position=find_from_index_not_in_string(temp_string_in_class," super.",super_position+1);
    }
    
    
    string_in_class = temp_string_in_class;
    printf("#### Finish formatClass ####\n#### output |%s| ####\n ",string_in_class);
    return string_in_class;
}

/*
 * eg x is hi()
 * add x to __instance_name__ in __walley__.wy
 */
void addInstanceNameToFile(char *instance_name,char *file_name){
    char *__instance_name__=getValueFromValueName(file_name,"__instance_name__");
    __instance_name__=listAppendOneElement(__instance_name__,toString(instance_name));
    changeTheWholeVarValueFromItsInitialOneFromFileForList(file_name,"__instance_name__",__instance_name__);
}
/*
 * we have x in __instance_name__
 * now we call function x.show(), we need to know whether x is in __instance_name__
 */
bool checkWhetherSameInstanceExisted(char *file_name, char *instance_name){
    char *__instance_name__=getValueFromValueName(file_name,"__instance_name__");
    instance_name=toString(instance_name);
    if(find(__instance_name__,instance_name)!=-1)
        return TRUE;
    else
        return FALSE;
}


/*
 * get
 * class person:     //rohit is person
 * //def rohit.super.init(age)
 * def rohit.person.init(age)
 *     rohit.age=age
 *     print("person age is "+str(rohit.age))
 * 
 * rohit is Rohit() //Rohit extends person
 * formatStringInMotherClass("__walley__.wy","rohit","Rohit")
 */
// mother is a Walley_String

char *formatStringInAnyClassFromFile(char *file_var_name, char *instance_name, char *class_name, bool isFirstClass) {
    //char *instance_name=son; 
    printf("\n\n#### formatStringInAnyClassFromFile ####\n");

    if (class_name[0] != '\"')
        class_name = toString(class_name);

    char *__string_in_temp_class__ = getValueFromValueName(file_var_name, "__string_in_temp_class__");
    //printf("----%s----\n",__string_in_temp_class__);
    //printf("----%s----\n",class_name);
    //char *__class_now__ = toString(class_name);
    char *string_in_class = valueAtKey(__string_in_temp_class__, class_name);
    //printf("\nhere\n");
    char *__temp_class__ = getValueFromValueName(file_var_name, "__temp_class__");
    char *mother = valueAtKey(__temp_class__, class_name);
    //char *string_in_mother_class = valueAtKey(__string_in_temp_class__, mother);

    char temp[1000] = "";
    strcat(temp, instance_name);
    strcat(temp, ".");
    char *instance_dot = malloc(sizeof (char) *((int) strlen(temp) + 1));
    int i = 0;
    for (i = 0; i < (int) strlen(temp); i++) {
        instance_dot[i] = temp[i];
    }
    instance_dot[(int) strlen(instance_dot)] = 0;

    if (string_in_class[0] == '"' || string_in_class[0] == '\'') {
        string_in_class = substr(string_in_class, 1, (int) strlen(string_in_class) - 1);

    }

    if (mother[0] == '"' || mother[0] == '\'') {
        mother = substr(mother, 1, (int) strlen(mother) - 1);

    }

    if (class_name[0] == '"' || class_name[0] == '\'') {
        class_name = substr(class_name, 1, (int) strlen(class_name) - 1);

    }

    //printf("%s %d\n", instance_dot, (int) strlen(instance_dot));
    // change self.year=10 -----> a.year=10
    string_in_class = replace_not_in_string(string_in_class, "self.", instance_dot);
    //printf("|%s|\n\n", string_in_mother_class);
    // change showMessage(self,input_str):------->a.showMessage(input_str):
    // change showMessage(self):------->a.showMessage():
    // so I need to find "def " and "(self"
    int define = 0;
    int left=0; //find ( of def input():
    int right=0;
    char *temp_string_in_class = string_in_class;
    if (isFirstClass == TRUE) {
        while (TRUE) {
            printf("---->|%s|\n", temp_string_in_class);
            define = find_from_index_not_in_string(temp_string_in_class, "def ", define + 1);
            left = find_from_index(temp_string_in_class, "(", define + 4); //find ( of def input():
            right = find_from_index_not_in_string(temp_string_in_class, ")", left);
            // Did not find 'def '
            if (define == -1)
                break;
            //printf("FIND DEFINE\n");
            char *string_in_parenthesis="";
            char *whole_function = substr(temp_string_in_class, define, right + 1); //get 'def hello(self,input)' without ':'
            char *func_name = functionName(whole_function); //               get hello
            //printf("###### func name is %s ####\n", func_name);
            if (left + 1 != right) {
                string_in_parenthesis = substr(temp_string_in_class, left + 1, right); //get self,input
                if (stringIsEmpty(string_in_parenthesis))
                    string_in_parenthesis = "";
            } else {
                string_in_parenthesis = "";
            }
            printf("&&&&& String in Params %s \n &&&&&&&\n",string_in_parenthesis);
            if (find_not_in_string(string_in_parenthesis, "self") != -1) {
                // find self in parameter.
                
                printf("====== Find Self\n");
                printf("string_in_parenthesis======|%s|\n",string_in_parenthesis);
                string_in_parenthesis = replace_not_in_string(string_in_parenthesis, "self", "");
                printf("string_in_parenthesis======|%s|\n",string_in_parenthesis);
                
                char *new_func_name = malloc(sizeof (char) *((int) strlen(func_name)+(int) strlen(instance_name) + 1));
                strcat(new_func_name, instance_name);
                strcat(new_func_name, ".");
                strcat(new_func_name, func_name); // change func name of  hello(self) to------>a.hello(self).
                func_name = new_func_name;
            }

            // change 'def hello(self)'--->'def a.hello()'
            char *new_function = malloc(sizeof (char) *((int) strlen("def ()")+(int) strlen(func_name)+(int) strlen(string_in_parenthesis)));
            strcat(new_function, "def ");
            printf("Func_Name %s\n",func_name);
            strcat(new_function, func_name);
            strcat(new_function, "(");
            printf("String In () %s\n",string_in_parenthesis);
            strcat(new_function, string_in_parenthesis);
            strcat(new_function, ")");
            printf("DEFIND %d RIGHT %d\n",define,right);
            printf("-1****************\n\n\n\n%s\n*************\n\n\n\n",temp_string_in_class);
            printf("$$$$$$$$$$$$$$$$$$\n %s\n ",substr(temp_string_in_class,define-1,right+1));
            
            temp_string_in_class = replace_from_index_to_index(temp_string_in_class, whole_function, new_function, define - 2, right + 1);
            printf("0****************\n\n\n\n%s\n*************\n\n\n\n",temp_string_in_class);
            if (find_not_in_string(temp_string_in_class, "(,") != -1)
                temp_string_in_class = replace_not_in_string(temp_string_in_class, "(,", "(");
            else if (find_not_in_string(temp_string_in_class, ",)") != -1)
                temp_string_in_class = replace_not_in_string(temp_string_in_class, ",)", ")");
            printf("1****************\n\n\n\n%s\n*************\n\n\n\n",temp_string_in_class);
        }
        
        printf("2****************\n\n\n\n%s\n*************\n\n\n\n",temp_string_in_class);
    }
    else {
        while (TRUE) {
            //printf("---->|%s|\n", temp_string_in_class);
            define = find_from_index_not_in_string(temp_string_in_class, "def ", define + 1);
            left = find_from_index(temp_string_in_class, "(", define + 4); //find ( of def input():
            right = find_from_index_not_in_string(temp_string_in_class, ")", left);
            // Did not find 'def '
            if (define == -1)
                break;
            //printf("FIND DEFINE\n");
            char *string_in_parenthesis="";
            char *whole_function = substr(temp_string_in_class, define, right + 1); //get 'def hello(self,input)' without ':'
            char *func_name = functionName(whole_function); //               get hello
            //printf("###### func name is %s ####\n", func_name);
            if (left + 1 != right) {
                string_in_parenthesis = substr(temp_string_in_class, left + 1, right); //get self,input
                if (stringIsEmpty(string_in_parenthesis))
                    string_in_parenthesis = "";
            } else
                string_in_parenthesis = "";
            if (find_not_in_string(string_in_parenthesis, "self") != -1) {
                // find self in parameter.
                string_in_parenthesis = replace_not_in_string(string_in_parenthesis, "self", "");

                char *new_func_name = malloc(sizeof (char) *((int) strlen(func_name)+(int) strlen(instance_name) + 3 +(int)strlen(class_name)));
                strcat(new_func_name, instance_name);
                strcat(new_func_name, ".");
                strcat(new_func_name,class_name);
                strcat(new_func_name,".");
                strcat(new_func_name, func_name); // change func name of  hello(self) to------>a.hello(self).
                new_func_name[(int)strlen(new_func_name)]=0;
                func_name = new_func_name;
            }

            // change 'def hello(self)'--->'def a.hello()'
            char *new_function = malloc(sizeof (char) *((int) strlen("def ()")+(int) strlen(func_name)+(int) strlen(string_in_parenthesis)));
            strcat(new_function, "def ");
            strcat(new_function, func_name);
            strcat(new_function, "(");
            strcat(new_function, string_in_parenthesis);
            strcat(new_function, ")");
            temp_string_in_class = replace_from_index_to_index(temp_string_in_class, whole_function, new_function, define - 2, right + 1);
            if (find_not_in_string(temp_string_in_class, "(,") != -1)
                temp_string_in_class = replace_not_in_string(temp_string_in_class, "(,", "(");
            else if (find_not_in_string(temp_string_in_class, ",)") != -1)
                temp_string_in_class = replace_not_in_string(temp_string_in_class, ",)", ")");
        }        
    }

    string_in_class = temp_string_in_class;
    
    // delete (self, and (self) and ,self) while has no def ahead. super.init(self)
    int super_position = find_not_in_string(temp_string_in_class, " super.");
    bool find_super = FALSE;
    while (super_position != -1) {
        //printf("Super Position is %d\n",super_position);
        //printf("4********\n%s\n*******\n", temp_string_in_class);
        //printf("FIND Super.\n");
        left = find_from_index_not_in_string(temp_string_in_class, "(", super_position + 6);
        right = find_from_index_not_in_string(temp_string_in_class, ")", left);
        char *string_in_parenthesis; // = substr(string_in_class, left + 1, right);
        if (left + 1 != right) {
            string_in_parenthesis = substr(temp_string_in_class, left + 1, right); //get self,input
            if (stringIsEmpty(string_in_parenthesis))
                string_in_parenthesis = "";
        } else {
            string_in_parenthesis = "";
        }
        if (find_not_in_string(string_in_parenthesis, "self") != -1) {
            find_super = TRUE;
            char *whole_function = substr(temp_string_in_class, super_position, right + 1); //get ' super.init(self)'
            //printf("------ whole function is %s -------\n\n\n", whole_function);
            char *func_name = substr(temp_string_in_class, super_position, left);
            func_name = trim(func_name);
            func_name = replace(func_name, "super.", ""); // super.init--->init
            //printf("------ func name is %s -------\n\n\n ", func_name);
            string_in_parenthesis = replace_not_in_string(string_in_parenthesis, "self", "");
            char *new_function_name = malloc(sizeof (char) *((int) strlen(mother)+(int) strlen(func_name)+(int) strlen(instance_name) + 4));
            strcat(new_function_name, " ");
            strcat(new_function_name, instance_name);
            strcat(new_function_name, ".");
            strcat(new_function_name, mother);
            strcat(new_function_name, ".");
            strcat(new_function_name, func_name); //' rohit.super.init
            new_function_name[(int) strlen(new_function_name)] = 0;

            char *new_function = malloc(sizeof (char) *((int) strlen("()") + 1 + (int) strlen(new_function_name)+(int) strlen(string_in_parenthesis)));

            strcat(new_function, new_function_name);
            strcat(new_function, "(");
            strcat(new_function, string_in_parenthesis);
            strcat(new_function, ")");

            new_function[(int) strlen(new_function)] = 0;
            //printf("1********\n%s\n*******\n", temp_string_in_class);
            temp_string_in_class = replace_from_index_to_index(temp_string_in_class, whole_function, new_function, super_position - 1, right + 1);
            //printf("2********\n%s\n*******\n", temp_string_in_class);
            //printf("6********\n%s\n*******\n", temp_string_in_class);
            int length=(int)strlen(temp_string_in_class);
            if (find_not_in_string(temp_string_in_class, "(,") != -1){
                //printf("FIND (,");
                temp_string_in_class = replace_not_in_string(temp_string_in_class, "(,", "(");
            }
            else if (find_not_in_string(temp_string_in_class, ",)") != -1){
                //printf("FIND ,)");
                temp_string_in_class = replace_not_in_string(temp_string_in_class, ",)", ")");
            }
            temp_string_in_class=substr(temp_string_in_class,0,length);
            //printf("5********\n%s\n*******\n", temp_string_in_class);
        }
        super_position = find_from_index_not_in_string(temp_string_in_class, " super.", super_position + 1);
    }
    //printf("3********\n%s\n*******\n", temp_string_in_class);
    string_in_class = temp_string_in_class;
    if (find_super == TRUE) {
        printf("FIND SUPER..\n");
        //printf("********\n%s\n*******\n", string_in_class);
        char *mother_string = formatStringInAnyClassFromFile(file_var_name, instance_name, toString(mother),FALSE);
        printf("@@@@\n@@@@\n%s\n",mother_string);
        char out[10000]="";
        strcat(out,mother_string);
        strcat(out,string_in_class);
        
        //char *temp_str = malloc(sizeof (char) *((int) strlen(mother_string)+(int) strlen(string_in_class) + 1));
        char *temp_str = malloc(sizeof (char) *((int) strlen(out)+1));
        int i=0;
        for(i=0;i<(int)strlen(out);i++){
            temp_str[i]=out[i];
        }
        temp_str[(int) strlen(temp_str)] = 0;
        string_in_class = temp_str;
    }



    printf("******\n*****\n|%s|\n",string_in_class);
    return string_in_class;
}


/*
 * class person:
    def init(self,age):
        self.age=age
        print("person age is "+str(self.age))
   class Rohit extends person:
    def init(self,age):
        super.init(self,age)
        print("Rohit age is "+str(self.age))
 * 
 * rohit is Rohit(16)
 *     ||
 *     ||
 *     \/
 * class Rohit extends person:
 * def rohit.init(age):
 *     //rohit.super.init(age)
 *     rohit.person.init(age)
 *     print("Rohit age is "+str(rohit.age))
 * 
 * class person:
 * def rohit.person.init(age)
 *     rohit.age=age
 *     print("person age is "+str(rohit.age))
 * 
 * 
 */
//formatStringInClassWithExtendFromFile("__walley__.wy","Rohit is person():")

char *formatStringInClassWithExtendFromFile(char *file_var_name, char *input_str) {
    printf("#### formatStringInClassWithExtendFromFile ####");
    input_str=trim(input_str);
    char *instance_name = substr(input_str, 0, find_not_in_string(input_str, " is "));
    char *__class__ = substr(input_str, find_not_in_string(input_str, " is ") + 4, (int) strlen(input_str));
    instance_name = trim(instance_name);
    __class__ = trim(__class__);
    char *class_name = substr(__class__, 0, find(__class__, "("));
    char *parameter = substr(__class__, find(__class__, "(") + 1, find_not_in_string(__class__, ")"));

    char *__string_in_temp_class__ = getValueFromValueName(file_var_name, "__string_in_temp_class__");
    char *__class_now__ = toString(class_name);
    char *string_in_class = valueAtKey(__string_in_temp_class__, __class_now__);

    char *__temp_class__ = getValueFromValueName(file_var_name, "__temp_class__");
    char *mother = valueAtKey(__temp_class__, __class_now__);

    // has no extends
    if (strcmp("None", mother) == 0) {
        printf("EXTENDS Nothing\n");
        return formatStringInClass(instance_name, string_in_class);
    }        // has extends
    else {
/*
        printf("Has extends\n");
        if (string_in_class[0] == '"' || string_in_class[0] == '\'') {
            string_in_class = substr(string_in_class, 1, (int) strlen(string_in_class) - 1);
            printf("''''''");
        }// "def ..."--->def ...
        printf("|%s|\n\n", string_in_class);
        **/
        // "def ..."--->def ...
        // format string in mother class....

        /*
        char temp[1000] = "";
        strcat(temp, instance_name);
        strcat(temp, ".");
        printf("temp length %d\n", (int) strlen(temp));
        char *instance_dot = malloc(sizeof (char) *((int) strlen(temp) + 1));

        int i = 0;
        for (i = 0; i < (int) strlen(temp); i++) {
            instance_dot[i] = temp[i];
        }
        instance_dot[(int) strlen(instance_dot)] = 0;




        printf("%s %d\n", instance_dot, (int) strlen(instance_dot));
        // change self.year=10 -----> a.year=10
        string_in_mother_class = replace_not_in_string(string_in_mother_class, "self.", instance_dot);
        printf("|%s|\n\n", string_in_mother_class);
        // change showMessage(self,input_str):------->a.showMessage(input_str):
        // change showMessage(self):------->a.showMessage():
        // so I need to find "def " and "(self"
        int define = 0;
        int left; //find ( of def input():
        int right;
        char *temp_string_in_class = string_in_mother_class;
        while (TRUE) {
            printf("---->|%s|\n", temp_string_in_class);
            define = find_from_index_not_in_string(temp_string_in_class, "def ", define + 1);
            left = find_from_index(temp_string_in_class, "(", define + 4); //find ( of def input():
            right = find_from_index_not_in_string(temp_string_in_class, ")", left);
            // Did not find 'def '
            if (define == -1)
                break;
            printf("FIND DEFINE\n");
            char *string_in_parenthesis;
            char *whole_function = substr(temp_string_in_class, define, right + 1); //get 'def hello(self,input)' without ':'
            char *func_name = functionName(whole_function); //               get hello
            if (left + 1 != right) {
                string_in_parenthesis = substr(temp_string_in_class, left + 1, right); //get self,input
                if (stringIsEmpty(string_in_parenthesis))
                    string_in_parenthesis = "";
            } else
                string_in_parenthesis = "";
            if (find_not_in_string(string_in_parenthesis, "self") != -1) {
                // find self in parameter.
                string_in_parenthesis = replace_not_in_string(string_in_parenthesis, "self", "");

                char *new_func_name = malloc(sizeof (char) *((int) strlen(func_name)+(int) strlen(instance_name) + 1+(int)strlen(".super.")));
                strcat(new_func_name, instance_name);
                strcat(new_func_name, ".super.");
                strcat(new_func_name, func_name); // change func name of  hello(self) to------>a.hello(self).
                new_func_name[(int)strlen(new_func_name)]=0;
                func_name = new_func_name;
            }

            // change 'def hello(self)'--->'def a.hello()'
            char *new_function = malloc(sizeof (char) *((int) strlen("def ()")+1+(int) strlen(func_name)+(int) strlen(string_in_parenthesis)));
            strcat(new_function, "def ");
            strcat(new_function, func_name);
            strcat(new_function, "(");
            strcat(new_function, string_in_parenthesis);
            strcat(new_function, ")");
            new_function[(int)strlen(new_function)]=0;
            temp_string_in_class = replace_from_index_to_index(temp_string_in_class, whole_function, new_function,define-1,right+1);
            if (find_not_in_string(temp_string_in_class, "(,") != -1)
                temp_string_in_class = replace_not_in_string(temp_string_in_class, "(,", "(");
            else if (find_not_in_string(temp_string_in_class, ",)") != -1)
                temp_string_in_class = replace_not_in_string(temp_string_in_class, ",)", ")");
        }

        string_in_mother_class = temp_string_in_class;
        printf("\n\n\n************* OUTPUT0 **************\n");
        printf("|%s|\n\n\n",string_in_mother_class);**/
        /*
        char *string_in_mother_class=formatStringInMotherClass(file_var_name,instance_name,mother);
        string_in_class=formatStringInClass(instance_name,string_in_class);
        
        char *output=malloc(sizeof((int)strlen(string_in_mother_class)+(int)strlen(string_in_class)+1));
        strcat(output,string_in_mother_class);
        strcat(output,string_in_class);
        output[(int)strlen(output)]=0;
        char *output2=replace_not_in_string(output,"\n","");
        printf("LENGTH IS %d\n",(int)strlen(output));
        printf("\n\n\n\n\n************* OUTPUT **************\n");
        printf("|%s|\n",output);
        return output2;**/
        return formatStringInAnyClassFromFile(file_var_name,instance_name,__class_now__,TRUE);
        
    }
}

bool checkWhetherSameClassExisted(char *file_var_name, char *class_name){
    printf("#### checkWhetherSameClassExisted ####\n");
    class_name=toString(class_name);
    printf("class_name %s\n",class_name);
    char *__class__=getValueFromValueName(file_var_name,"__temp_class__");
    char *key_list=keyOfDictionaryAsList(__class__);
    int num=valueNumOfList(key_list);
    int i=0;
    bool existed=FALSE;
    for(i=0;i<num;i++){
        char *value=valueOfListAtIndex(key_list,i);
        if(strcmp(value,class_name)==0){
            existed=TRUE;
            break;
        }
    }
    printf("Existed ? %d\n",existed);
    return existed;
}