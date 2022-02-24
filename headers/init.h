#ifndef INIT_H
#define INIT_H

#include "defines.h"

/* Functions called when the respective argument was passed */
static int arg_found_help();
static int arg_found_conf(char *filename);
static int arg_found_log(char *filename);

void Init(int argc, char **argv);

#endif // !INIT_H
