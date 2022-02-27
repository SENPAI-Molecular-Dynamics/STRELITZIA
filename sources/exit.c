#include "exit.h"
#include "utils.h"
#include "text.h"

/* Standard exit procedure */
void Exit()
{
	uint32_t num;

	throw_err(ERR_INFO, TEXT_ERROR_EXITING);
	print_sys_stats(__FILE__, __LINE__);

	/* Halt all the workers */
	setall_flag(MFLAG_HALT);

	/* If not all have halted */
	if (num = expect_flag(WFLAG_HALTING, WORKER_HALT_TIMEOUT_MILLIS))
	{
		throw_err(ERR_HEAVY_WARN, TEXT_ERROR_WORKER_TIMEOUT_HALT, num);
	}
	
	print_sys_stats(__FILE__, __LINE__);

	/* Close connections with worker nodes */
	setall_flag(MFLAG_DISCONN);

	/* If not all have disconnected */
	if (num = expect_nflag(WFLAG_CONNECTED, WORKER_DISCONN_TIMEOUT_MILLIS))
	{
		throw_err(ERR_HEAVY_WARN, TEXT_ERROR_WORKER_TIMEOUT_DISCONN, num);
	}

	print_sys_stats(__FILE__, __LINE__);

	/* Exit worker processes */
	setall_flag(MFLAG_EXIT);

	/* If not all have exited */
	if (num = expect_nflag(WFLAG_ALIVE, WORKER_EXIT_TIMEOUT_MILLIS))
	{
		throw_err(ERR_HEAVY_WARN, TEXT_ERROR_WORKER_TIMEOUT_EXIT, num);
	}

	print_sys_stats(__FILE__, __LINE__);

	/* All the threads that have exited we can join with */
	for (uint32_t i = 0; i < env.worker_count; i++)
	{
		if (!(env.workers[i].wflags & WFLAG_ALIVE))
		{
			pthread_join(env.workers[i].tid, NULL);
		}
	}

	// TODO: Collect stuff from worker structs and clean up

	throw_err(ERR_INFO, TEXT_ERROR_EXITING_DONE);

	/* Don't accidentally close stdio */
	if (conf.logfile.fd != stderr && conf.logfile.fd != stdout)
	{
		fclose(conf.logfile.fd);
	}

	exit(COF_EX_SUCC);
}

/* 
 * Something has gone horribly wrong.
 * Notify everyone to abort and exit.
 */
void Abort(const int error_code)
{
	/* Set the aborting flag so the system knows */
	conf.flags |= FLAG_ABORTING;

	/* Halt all the workers */
	setall_flag(MFLAG_HALT);
	/* Close connections with worker nodes */
	setall_flag(MFLAG_DISCONN);
	/* Exit worker processes */
	setall_flag(MFLAG_EXIT);

	/* Attempt to push all errors to COFFIN */
	for (uint32_t i = 0; i < env.error_count; i++)
	{
		// TODO: Implement
	}

	exit(COF_EX_FAIL);
}

