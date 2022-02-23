/*
 * main.c
 *
 * Licensed under GPLv3 license
 *
 */

#include "defines.h"

#include "init.h"
#include "exit.h"

int main(int argc, char **argv)
{
	strelitzia_t *env = malloc(sizeof(strelitzia_t));
	Init(env);

	Exit(env);
	return 0;
}
