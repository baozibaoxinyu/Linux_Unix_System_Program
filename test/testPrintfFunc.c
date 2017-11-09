#include <stdio.h>

int main()
{
	char* str;
	char* name = "hello world";
	printf("The string is %s\n",name);
	int n = snprintf(str,5,"%s",name);
	printf("And the string that called snprintf function is %s and snprintf return value is %d.\n",str,n);
	int num = 2;
	int num1 = 3;
	printf("Using '*' to output arguments %*s\n",num,name);
	printf("Using 'n$' to output arguments %1$*2$d\n",num,num1);
	return 0;
}




