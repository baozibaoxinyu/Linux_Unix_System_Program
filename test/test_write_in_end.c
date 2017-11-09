#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc,char* argv[])
{
    char buf[] = {"a"};
    int fd;
    fd = open(argv[1],O_WRONLY | O_CREAT | O_APPEND,S_IRUSR | S_IWUSR);
    int i = 0;
    for(;i<100;i++){
	//lseek(fd,0,SEEK_END);
	write(fd,buf,1);
    }
    return 0;
}
