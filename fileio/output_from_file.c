#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
const int BUFFER_MAX = 30;
const int FILENAME = 50;
int main()
{
	char* filename = malloc(sizeof(char)*FILENAME);
	char* buffer = malloc(sizeof(char)*BUFFER_MAX);
	errno = 0;
	int numRead = 0;
	printf("Enter the filename you want to show:");
	scanf("%s",filename);	//get file name from stdin(terminal)
	int fd = open(filename,O_RDONLY,S_IRUSR | S_IWUSR);	//open file in read only mode and user permission is read and write.
	if(fd == -1){
		printf("Open failed.Error number is %d\n",errno);
		exit(EXIT_FAILURE);
	}
	while((numRead = read(fd,buffer,BUFFER_MAX))){
		if(write(STDOUT_FILENO,buffer,numRead)!= numRead){
			printf("Couldn't write whole buffer\n");
			exit(EXIT_FAILURE);
		}
	}
	if(numRead == -1){
		printf("Read failed.Error number is %d\n",errno);
		exit(EXIT_FAILURE);
	}
	if(close(fd) == -1){
		printf("Close failed.Error number is %d\n");
		exit(EXIT_FAILURE);
	}
	free(filename);
	free(buffer);
	exit(EXIT_SUCCESS);
}
