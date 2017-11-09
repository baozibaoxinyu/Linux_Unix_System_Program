/* This file is to open an existed file by O_APPEND flag,and set lseek at begining of this file,
 * and write data in it,test the data location in file
 * */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>	/* for strcmp function */
const int MAXSIZE = 100;
void usageExit(const char* usage);
void errExit(const char* opera);

int main(int argc,char* argv[])
{
    if(argc < 2 || strcmp(argv[1],"--help") == 0)
	usageExit("show data in file position\n");
    int fd,numRead;
    char* buff = malloc(MAXSIZE);
    fd = open(argv[1],O_WRONLY | O_APPEND);
    if(lseek(fd,0,SEEK_SET == -1))
	errExit("lseek");
    if(fd == -1)
	errExit("open\n");
    numRead = read(STDIN_FILENO,buff,MAXSIZE);
    if( numRead == -1)
	errExit("read\n");
    if(write(fd,buff,numRead) == -1)
	errExit("write\n");
    printf("Write success\n");
    free(buff);
    exit(EXIT_SUCCESS);
}
void usageExit(const char* usage){
    printf("Usage:%s\n",usage);
    exit(EXIT_FAILURE);
}
void errExit(const char* opera){
    printf("%s error,%s failed\n",opera,opera);
    exit(EXIT_FAILURE);
}
