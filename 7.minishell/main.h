#ifndef _MAIN_H_
#define _MAIN_H_
#include "def.h"

extern char cmdline[MAXLINE + 1];
extern char avline[MAXLINE + 1];
extern struct command cmd[PIPELINE];
extern char infile[MAXNAME + 1];
extern char outfile[MAXNAME + 1];

extern int cmd_count;
extern int backgnd;

extern char *lineptr;					/* 指向 lineptr */
extern char *avptr;					/* 指向 avline */
extern int append;
extern int lastpid;
extern int open_max;

#endif /* _MAIN_H_ */