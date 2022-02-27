/*
 * main.c
 *
 * Licensed under GPLv3 license
 *
 */

//TODO: Networking, Error system

#include "defines.h"

#include "init.h"
#include "exit.h"
#include "text.h"

/* Global stuff (At the end of defines.h) */
strelitzia_t env;
config_t conf;

int main(int argc, char **argv)
{
	Init(argc, argv);
        printf(TEXT_SPLASH);

	// TODO: The program goes here

	Exit();
	return (EXIT_SUCCESS);
}
