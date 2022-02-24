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
strelitzia_t env;
config_t conf;

int main(int argc, char **argv)
{
	Init(argc, argv);

	// DEBUG
	#include "utils.h"

	throw_err(ERR_INFO, "From [%s:%d]:\n", __FILE__, __LINE__);
	throw_err(ERR_INFO, "Config file:	%s\n", conf.conf_file.path);
	throw_err(ERR_INFO, "Log file:		%s\n", conf.logfile.path);
	throw_err(ERR_INFO, "Workers:		%d\n", env.worker_count);
	for (uint32_t i = 0; i < env.worker_count; i++)
	{
		throw_err(ERR_INFO, "Worker %d: flags=%x, ipv4=%d, ipv6=%ld%ld%ld, port=%d\n",
			env.workers[i].id, env.workers[i].flags, env.workers[i].ipv4,
			env.workers[i].ipv6[0], env.workers[i].ipv6[1], env.workers[i].ipv6[2],
			env.workers[i].port);
	}

	Exit();
	return 0;
}
