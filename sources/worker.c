#include "worker.h"
#include "defines.h"

#include "utils.h"

int worker_node_connect(worker_t *self);
int worker_node_disconnect(worker_t *self);

void worker_halt_routine(worker_t *self);
void worker_exit_routine(worker_t *self);

void flag_handle_halt(worker_t *self);
void flag_handle_conn(worker_t *self);
void flag_handle_exit(worker_t *self);

void *worker_main_loop(void *vself)
{
	worker_t *self = (worker_t *) vself;

	/* Catch before initialization is finished */
	while (MFLAG_ISSET(MFLAG_HALT, self))
	{
	}

	WFLAG_UNSET(WFLAG_HALTING, self);

	while (WFLAG_ISSET(WFLAG_ALIVE, self))
	{
		flag_handle_halt(self);
		flag_handle_conn(self);
		flag_handle_exit(self);

		// TODO: The program goes here
	}

	return NULL;
}

/* Connect to the worker node */
int worker_node_connect(worker_t *self)
{
	WFLAG_SET(WFLAG_CONNECTED, self);
}

/* Disconnect from the worker node */
int worker_node_disconnect(worker_t *self)
{
	WFLAG_UNSET(WFLAG_CONNECTED, self);
}

/* Called when halting */
void worker_halt_routine(worker_t *self)
{
	// TODO: Request worker node to halt

	WFLAG_SET(WFLAG_HALTING, self);

	/* While we're supposed to halt */
	while (MFLAG_ISSET(MFLAG_HALT, self))
	{
		/* Still listen for disconnect or exit commands */
		flag_handle_conn(self);
		
		if (MFLAG_ISSET(MFLAG_EXIT, self))
		{
			return;
		}
	}

	WFLAG_UNSET(WFLAG_HALTING, self);
}

/* Called to exit */
void worker_exit_routine(worker_t *self)
{
	WFLAG_UNSET(WFLAG_ALIVE, self);
}

void flag_handle_halt(worker_t *self)
{
	/* We're supposed to halt */
	if (MFLAG_ISSET(MFLAG_HALT, self))
	{
		worker_halt_routine(self);
	}
}

void flag_handle_conn(worker_t *self)
{
	/* We're supposed to disconnect */
	if (MFLAG_ISSET(MFLAG_DISCONN, self) && WFLAG_ISSET(WFLAG_CONNECTED, self))
	{
		worker_node_disconnect(self);
	}

	/* We're supposed to connect again */
	 if (!MFLAG_ISSET(MFLAG_DISCONN, self) && !WFLAG_ISSET(WFLAG_CONNECTED, self))
	{
		worker_node_connect(self);
	}
}

void flag_handle_exit(worker_t *self)
{
	if (MFLAG_ISSET(MFLAG_EXIT, self))
	{
		worker_exit_routine(self);
	}
}

