/**
 *Filename:readStringFromTerminal
 *Date:20171030
 *Author:Chris Bao
 */
#include <unistd.h>
#include <stdio.h>
#include "../lib/tlpi_hdr.h"

#define MAX_READ 99
int main(int argc,char* argv[])
{
	//if(strcmp(argv[1],"--help") == 0)
	//	usageErr("read string from terminal");
	char buffer[MAX_READ+1];
	ssize_t numRead;
	printf("Please input a string that less than 20 characters\n");
	numRead = read(STDIN_FILENO,buffer,MAX_READ);
	if(numRead == -1)
		errExit("read");
	buffer[numRead] = '\0';
	printf("The input data was: %s\n",buffer);
	return 0;
}
