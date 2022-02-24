/*
 * main.c
 *
 * Licensed under GPLv3 license
 *
 */

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

	// DEBUG
	#include "utils.h"

	throw_err(ERR_INFO, TEXT_INFO_FROM, __FILE__, __LINE__);
	throw_err(ERR_INFO, TEXT_INFO_FILE_CONFIG, conf.conf_file.path);
	throw_err(ERR_INFO, TEXT_INFO_FILE_LOG, conf.logfile.path);
	throw_err(ERR_INFO, TEXT_INFO_WORKER_NB, env.worker_count);
	for (uint32_t i = 0; i < env.worker_count; i++)
	{
		throw_err(ERR_INFO, TEXT_INFO_WORKER,
			env.workers[i].id, env.workers[i].flags, env.workers[i].ipv4,
			env.workers[i].ipv6[0], env.workers[i].ipv6[1], env.workers[i].ipv6[2],
			env.workers[i].port);
	}

	Exit();
	return 0;
}
