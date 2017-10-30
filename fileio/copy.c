#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"


#ifndef BUF_SIZE	/* Allow "cc -D" to overrude definition */
#define BUF_SIZE 1024
#endif

int main(int argc,char* argv[])
{
	int inputFd,outputFd,openFlags;
	mode_t filePerms;	/* mode_t:被定义在sys/types.h和sys/stat.h中。是一个整型数据变量，来代表文件模式，在GNU C库中，是一个无符号类型,并不比unsigned int短 */
	ssize_t numRead;	/* ssize_t:是一个数据类型被用来代表在一次读或写操作中可以被读写的块的大小 */
	char buf[BUF_SIZE];
	
	if (argc != 3 || strcmp(argv[1],"--help") == 0)	/* strcmp()：被定义在string.h中用来比较两个数组，格式：int strcmp(const char* s1,const char* s2)，返回值为
							   一个整数有>0,<0和=0来表示是s1>s2，s1<s2,s1=s2 */
		usageErr("%s old-file new-file\n",argv[0]);
	/* Open input and output files */
	inputFd = open(argv[1],O_RDONLY);	/* 以只读方式打开文件名所示文件 */
	if(inputFd == -1)
		errExit("opening file %s",argv[1]);
	openFlags = O_CREAT | O_WRONLY | O_TRUNC;	/* O_*打头的宏定义在fcntl.h头文件，O_CREAT表示，如果文件不存在，则会创建一个文件。O_WRONLY表示，以写入方式打开文件。
							   O_TRUNC表示将文件初始化为0长度，这个模式只适用于常规文件，不适用于特殊文件例如目录或FIFO。*/
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
		    S_IROTH | S_IWOTH;		/* rw-rw-rw 表示文件的模式是用户权限：rw。用户组权限：rw，其他用户权限：rw */
	outputFd = open(argv[2],openFlags,filePerms); /* 利用open函数以openFlag定义的模式和文件的用户属性filePerms打开目标文件 */
	if(outputFd == -1)
		errExit("opening file %s",argv[2]);
	/* Transfer data until we encounter end of input or an error */

	while((numRead = read(inputFd,buf,BUF_SIZE)) > 0)
		if(write(outputFd,buf,numRead) != numRead)
			fatal("couldn't write whole buffer");
	if(numRead == -1)
		errExit("read");
	if(close(outputFd) == -1)
		errExit("close output");
	printf("Copy success\n");
	exit(EXIT_SUCCESS);
}
