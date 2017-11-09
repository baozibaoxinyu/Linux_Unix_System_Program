#include <stdio.h>
#include <stdlib.h>	//For strtol() function and atoi() function
#include <limits.h>	//For INT_MAX and INT_MIN
#include <errno.h>	//For error macro
/* This file is to test errno flag that defined in Linxu-x86_64 macro */
int main()
{
	const char* err = "E";
	long a;
	errno = 0;
	a = strtol(err,NULL,10);
	printf("INT_MAX = %d,INI_MIN  = %d\n",INT_MAX,INT_MIN);
	printf("ERANGE = %d\n",ERANGE);
	if(errno == ERANGE){
		printf("Error : Out of Range");
		exit(EXIT_FAILURE);
	}
	if(a > INT_MAX || a < INT_MIN)
		printf("Number is larger than INT_MAX or less than INT_MIN\n");
	printf("atoi result is %d\n",(int)a);
	return 0;

}
