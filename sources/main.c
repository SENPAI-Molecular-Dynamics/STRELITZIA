/*
 * main.c
 *
 * Licensed under GPLv3 license
 *
 */

#include "defines.h"

#include "init.h"
#include "exit.h"

/* Global stuff (At the end of defines.h) */
FILE *logfile;
strelitzia_t *lzenv;
uint8_t flags = 0;

int main(int argc, char **argv)
{
	arg_t args;
	args.argc = argc;
	args.argv = argv;

	Init(&args);

	Exit(&args);
	return 0;
}
