#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H
/* 此头文件声明了errMsg(),errExit(),err_exit()以及errExitEN()函数，用以诊断系统调用和库函数时发生的错误。
 * errMsg()函数会在标准错误设备上打印消息。除了将一个终止换行符自动追加到输出字符串尾部以外，该函数的参数
 * 列表与printf()所用相同。errMsg()函数会打印出与当前errno值相对应的错误文本，其中包括了错误名以及由strerror()
 * 返回的错误描述，外加由参数列表指定的格式化输出。
 *
 * errExit()函数的操作方式与errMsg相似，功能上会以如下两种方式之一来终止程序。1，调用exit()退出。2，若将环境变量EF_DUMPCORE
 * 定义为非空字符串，则调用abort()退出，同时生成核心转储(core dump)文件，供调试器调试用。
 *
 * err_exit()类似与errExit()，但存在两方面的差异：
 * 1，打印错误消息之前，err_exit()不会刷新标准输出。
 * 2，err_exit()终止进程使用的是_exit()，而非exit()。这一退出方式略去了对stdio缓冲区的刷新以及对退出处理程序(exit handler)的调用。
 * 好处是在编写的库函数创建了子进程，且该子进程因发生错误而需要终止时，err_exit()可以用到。避免了对子进程继承自父进程(即调用进程)
 * 的stdio缓冲区副本进行刷新，且不会调用由父进程所建立的退出处理程序。
 *
 * errExitEN()函数与errExit()大体相同，区别在于：
 * errExitEN()只会打印与errnum参数中给定的错误号(error number)相对应的文本。在调用POSIX线程API的程序示例中，主要使用errExitEN()来处理错误。
 * POSIX线程函数会在其结果中返回一个(POSIX线程函数返回0表示成功)错误号(正数，类型为errno所专用)。
 * 对于POSIX线程函数，可用如下代码来诊断错误：
 * 效率不高的代码：
 * errno = pthread_create(&thread,NULL,func,&arg);
 * if(errno != 0)
 * 	errExit("pthread_create");
 * 因为errno已被定义为宏，展开后是返回可修改左值的一个函数调用，每调用errno都会引发一次函数调用。效率降低。
 * 效率高的代码：
 * int s;
 * s = pthread_create(&thread,NULL,func,&arg);
 * if(s != 0)
 * 	errExitEN(s,"pthread_create";
 * */
void errMsg(const char* format,...);	/* ...表明参数不确定 */

#ifdef _GNUC_
/* 这个宏是阻止运行'gcc -Wall'命令时，出现'control reaches end of non-void function'的警告信息。
 * 这种情况的意思是控制达到了非空函数的末尾，这种警告可能出现的情况是一些本该有返回值的函数在函数结尾没有返
 * 回值，要提醒检查是否每个函数都有返回值 */
#define NORETURN _attribute_ ((_noreturn_))	/* _attribute_ 是gcc编译器对一个声明的属性的设定在声明后加上
						   _attribute_ ((ATTRIBUTE))可以将声明指定为ATTRIBUTE对应的
						   属性 _noreturn_属性用于函数，表示函数从不返回 */
#else
#define NORETURN
#endif

void errExit(const char* format,...) NORETURN;
void err_exit(const char* format,...) NORETURN;
void errExitEN(int errnum,const char* format,...) NORETURN;
/* 对于其他类型的错误使用fatal(),usageErr(),cmdLineErr()函数来处理。
 * fatal()函数用来诊断一般性错误，其中包括未设置errno的库函数错误。除了将一个终止换行符自动追加到输出字符串尾部外，fatal函数的
 * 参数列表与printf()基本相同。该函数在标准错误(stderr)上打印格式化输出，像errExit()一样终止程序。
 * usageErr()用来诊断命令行参数使用方面的错误。其参数列表风格与printf()相同，并在标准错误上打印字符串"Usage:"，随之以格式化输出，
 * 然后调用exit()终止程序。
 * cmdLineErr()与usageErr()类似，但其错误诊断是针对特定程序的命令行参数。
 */
void fatal(const char* format,...) NORETURN;
void usageErr(const char* format,...) NORETURN;
void cmdLineErr(const char* format,...) NORETURN;

#endif
