/* 
 * This file is to create a large file by using open and lseek functions.
 * date:2017/11/07
 * author:Chris Bao
 * */

#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
void printError(const char* error);

int main(int argc,char* argv[])
{
	int fd;
	off_t offset;
	if(argc < 3 || strcmp(argv[1],"--help")== 0){
		printf("Usage:filename offset\n");
		exit(EXIT_SUCCESS);
	}
	fd = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR);
	if(fd == -1)
		printError("Open failed\n");
	offset = atoll(argv[2]);
	if(lseek(fd,offset,SEEK_CUR) == -1)
		printError("seek flag failed\n");
	if(write(fd,"test",4) == -1)
		printError("write failed");
	if(close(fd))
		printError("close failed");
	exit(EXIT_SUCCESS);
}

void printError(const char* error){
	printf("Error:%s\n",error);
	exit(EXIT_FAILURE);
}
