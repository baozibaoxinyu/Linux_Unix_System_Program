/* filename:cp.c
 * date:20171105
 * author:Chris Bao
 * overview:This program is to copy oldfile to newfile
 * */
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "../lib/tlpi_hdr.h"
const int MAX_SIZE = 50;

int main(int argc,char* argv[])
{
	if(argc < 3 || strcmp(argv[1],"--help") == 0)
		usageErr("cp oldfile newfile\n");
	if(argc >3)
		cmdLineErr("command must be like: ./cp oldfile newfile\n");
	int fd_read,fd_write;
	char* buf = malloc(MAX_SIZE);
	ssize_t numRead;
	fd_read = open(argv[1],O_RDONLY);
	fd_write = open(argv[2],O_WRONLY | O_CREAT | O_EXCL,S_IRUSR | S_IWUSR); 
	if(fd_read == -1)
		errExit("open");
	if(fd_write == -1)
		errExit("open");
	while(numRead = read(fd_read,buf,MAX_SIZE))
		if(write(fd_write,buf,numRead) != numRead)
			fatal("count't write whole buffer");
	if(numRead == -1)
		errExit("read");
	if(close(fd_read) == -1 || close(fd_write) == -1)
		errExit("close");
	printf("copy success\n");
	exit(EXIT_SUCCESS);
}
