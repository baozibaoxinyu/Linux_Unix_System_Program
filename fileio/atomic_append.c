/* 本程序的目的是为了展示为何以O_APPEND标志打开文件来保障操作的原子性
 * 是必要的。
 * */
#include <stdio.h>
#include <stdlib.h>		/* For atoi function */
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>		/* For strcmp function */
#include <unistd.h>
#include "../lib/tlpi_hdr.h"
int main(int argc,char* argv[])
{
    if(argc < 2 || strcmp(argv[1],"--help") == 0)
	usageErr("filename num-bytes [x]\n");
    int fd;
    int flag;
    if(argc == 3)
	flag = 1;
    else if(argc == 4 && strcmp(argv[3],"x")==0)
	flag = 0;
    //int flag = strcmp(argv[3],"x");	    这条语句是有问题的，会出现bug
    if(flag != 0)
	fd = open(argv[1],O_WRONLY | O_CREAT | O_APPEND ,S_IRUSR | S_IWUSR);
    else
	fd = open(argv[1],O_WRONLY | O_CREAT ,S_IRUSR | S_IWUSR);
    if(fd == -1)
	errExit("open");
    char* buf = malloc(1);
   // char buf[] = {"a"};
    int size = atoi(argv[2]);
    printf("flag is %d,size is %d\n",flag,size);
    strcpy(buf,"a");
    printf("buf length is %d\n",strlen(buf));
    for(int i = 0;i<size;++i){
	if(flag != 0)
	    if(write(fd,buf,1) == -1)
		errExit("write");
	if(flag == 0){
	    if(lseek(fd,0,SEEK_END) == -1)
		errExit("lseek");
	    if(write(fd,buf,1) == -1)
		errExit("write");
	}
    }
    if(close(fd) == -1)
	errExit("close");
    free(buf);
    exit(EXIT_SUCCESS);
}
