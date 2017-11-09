/* 文件名：以独占方式创建一个文件的错误代码
 * 日期：20171102
 * 作者：包鑫宇
 * */
#include <stdio.h>	//standard input and output
#include <sys/types.h>	//for getpid function
#include <unistd.h>	//for read and write and close function
#include <sys/stat.h>	//for open function
#include <fcntl.h>	//for file control macro
#include <errno.h>

int main(int argc,char* argv[]){
	int fd;
	fd = open(argv[1],O_WRONLY);	/* Open 1:check if file exists */
	if(fd != -1){			/* Open succeeded */
		printf("[PID %ld] File \"%s\" already exists\n",
			(long)getpid(),argv[1]);
		close(fd);
	}
	else if(errno != ENOENT){
		printf("Open failed");	/* Failed for unexpected reason */
	}
	else{
		printf("[PID %ld]File \"%s\" doesn't exist yet\n",(long)getpid(),argv[1]);	/* Delay between check and create */
		if(argc> 2){
			sleep(5);	/* Suspend excution for 5 minutes */
			printf("[PID %ld]Done sleeping\n",(long)getpid());
		}
		/* WINDOW FOR FAILURE */
		fd = open(argv[1],O_WRONLY | O_CREAT,S_IRUSR|S_IWUSR);
		if(fd == -1)
			printf("Open again failed");
		printf("[PID %ld] Created file \"%s\" exclusively\n",
			(long)getpid(),argv[1]);
	}
}	
