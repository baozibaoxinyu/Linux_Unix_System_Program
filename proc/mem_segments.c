/* Show program variable position in every segment of process memory */
#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];		    /* Uninitialized data segment */
int primes[] = {2,3,5,7};	    /* Initialized data segment */
static int square(int x);	    /* Allocated in frame for square() */
static void doCalc(int val);	    /* Allocated in frame for doCalc() */

int main(int argc,char* argv[])	    /* Allocated in frame for main() */
{
    static int key = 1000;	    /* Intialized data segment */
    static char mbuf[10240000];	    /* Uninitialized data segment */
    char* p;			    /* Allocated in frame for main() */
    p = malloc(1024);		    /* Points to memory in heap segment */
    doCalc(key);
    exit(EXIT_SUCCESS);
}
static int square(int x){
    int result;			    /* Allocated in frame for square() */
    result = x*x;
    return result;		    /* Return value passed via register */
}
static void doCalc(int val){
    printf("The square of %d is %d\n",val,square(val));
    if(val < 100){
	int t;			    /* Allocated in frame for doCalc() */
	t = val * val * val;
	printf("The cube of %d is %d\n",val,t);
    }
}
