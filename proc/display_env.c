/* show process environment variable */
#include "../lib/tlpi_hdr.h"

extern char** environ;		/* 外部引用全局变量environ */

int main(int argc,char* argv[])
{
    char** ep;
    for(ep = environ;*ep != NULL;++ep)
	puts(*ep);
    exit(EXIT_SUCCESS);
}