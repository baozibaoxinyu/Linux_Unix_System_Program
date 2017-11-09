#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int size = 2;
int main()
{
    char* str = malloc(1);
    strcpy(str,"1");
    printf("%d\n",sizeof(str[0]));
    int i = atoi(str);
    printf("%s %d\n",str,i);
    return 0;
}
