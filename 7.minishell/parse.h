#ifndef _PARSE_H_
#define _PARSE_H_
#include "def.h"
#include "execute.h"

void shell_loop(void);
int read_command(void);
int parse_command(void);
int execute_command(void);

void get_command(int i);
int check(const char *str);
void getname(char *name);
void print_command(void);

#endif	/* _PARSE_H_ */