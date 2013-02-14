#include "walley_table.h"
int main(int argc, char **argv){
    char *x="[1,'apple'=12]";
    printf("%s\n",Table_formatTable(x));
    //printf("%d\n",Table_checkWhichIndexDoesNotExist(x,"[2]"));
    //printf("%s",Table_formatTableThatDoesNotExist("[0][1]","[1,2]"));
    return 0;
}