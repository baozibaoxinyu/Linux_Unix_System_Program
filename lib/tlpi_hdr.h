#ifndef TLPI_HDR_H
#define TLPI_HDR_H	/* Prevent accidental double inclusion */

#include <sys/types.h>	/* Type definitions usedd by many programs */
#include <stdio.h>	/* Standard I/O funtions */
#include <stdlib.h>	/* Prototypes of commonly used library functions,
			   plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>	/* Prototypes for many system calls */
#include <errno.h>	/* Declares errno and defines errno constants */
#include <string.h>	/* Commonly used string-handling functions */

#include "get_num.h"	/* Declares functions for handling numberic 
			   arguments (getInt(),getLong()) */
#include "error_functions.h" /* Declares self-defined error-handling funcions */
typedef enum{FALSE,TRUE} Boolean;
#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

#endif


