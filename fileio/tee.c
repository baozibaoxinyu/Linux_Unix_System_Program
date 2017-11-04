/* filename:tee.c
 * date:20171104
 * author:Chris Bao
 * Overview:这个程序的目的，是模仿tee命令，从终端读取数据写到指定文件
 * 和标准输出，默认情况下会覆盖同名文件，-a命令可以以追加模式在文件末
 * 尾增加数据。
 * */
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include "../lib/tlpi_hdr.h"
const MAX_SIZE = 1000;

int main(int argc,char* argv[])
{
	int fd,numRead; /* declare file descriptor and number of read */
	char* buf = malloc(MAX_SIZE);
	/* 如果第二个参数是--help命令，调用
 	 * usageErr函数，输出相关函数的功能 */
	if(argc < 2 || strcmp(argv[1],"--help") == 0)
		usageErr("从标准输入读取数据并写入标准输出和指定文件\n");
	/* 从终端读取数据，使用read函数将终端的数据读到指定字符串数组中 */
	if(argc == 2)
		/* if argc = 2,open mode is write&read and it's length is 0,if file don't exist,it would be create. */
		fd = open(argv[1],O_RDWR | O_CREAT | O_TRUNC,S_IRUSR | S_IWUSR);
	if(argc > 2 && (strcmp(argv[1],"-a") == 0 ||strcmp(argv[1],"--append")== 0))
		/* if argc = 3,open mode is write&read and add data to file end */
		fd = open(argv[2],O_RDWR | O_CREAT | O_APPEND,S_IRUSR | S_IWUSR);
	if(fd == -1)
		errExit("open");
	while(1){
		numRead = read(STDIN_FILENO,buf,MAX_SIZE);
		if(numRead == -1)
			errExit("read");
		if(strcmp(argv[1],"-a")!= 0 ||strcmp(argv[1],"--append")!= 0 ){
			if(lseek(fd,0,SEEK_END)== -1)
				errExit("lseek");
		}
		if(write(fd,buf,numRead) == -1)
			errExit("write file");
		if(write(STDOUT_FILENO,buf,numRead)== -1)
			errExit("write stdout");
	}
	free(buf);
	exit(EXIT_SUCCESS);
}
