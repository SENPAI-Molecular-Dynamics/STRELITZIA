#include "worker.h"
#include "defines.h"

#include <string.h>
#include <unistd.h>

#include "utils.h"
#include "network.h"

void worker_node_connect(worker_t *self);
void worker_node_disconnect(worker_t *self);

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
		if (WFLAG_ISSET(WFLAG_CONNECTED, self))
		{
		}
	}

	return NULL;
}

/* Connect to the worker node */
void worker_node_connect(worker_t *self)
{
	/* If we're already connected, don't attempt to do so again */
	if (WFLAG_ISSET(WFLAG_CONNECTED, self))
	{
		return;
	}

	/* IPv6 or IPv4 ? */
	if (MFLAG_ISSET(MFLAG_IS_IP6, self))
	{
		/* If the connection failed, errnum has been set, also set the interrupt flag and halt */
		if ((self->sockfd = connect_v6(&self->errnum, self->ip_str, self->port)) < 0)
		{
			WFLAG_SET(WFLAG_INTERRUPT, self);
			WFLAG_SET(WFLAG_HALTING, self);
			return;
		}
	} else {
		/* If the connection failed, errnum has been set, also set the interrupt flag and halt */
		if ((self->sockfd = connect_v4(&self->errnum, self->ip_str, self->port)) < 0)
		{
			WFLAG_SET(WFLAG_INTERRUPT, self);
			WFLAG_SET(WFLAG_HALTING, self);
			return;
		}
	}

	// TODO: Tell worker node to initialize

	write(self->sockfd, (void *) self->name, strlen(self->name) + 1);

	/* Otherwise a connection was established, set the connected flag */
	WFLAG_SET(WFLAG_CONNECTED, self);
}

/* Disconnect from the worker node */
void worker_node_disconnect(worker_t *self)
{
	/* If we're already diconnected, don't attempt to do so again */
	if (!WFLAG_ISSET(WFLAG_CONNECTED, self))
	{
		return;
	}

	// TODO: Tell worker node to exit

	close(self->sockfd);
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
	/* If we're still connected let the manager know. The node should time out by itself though */
	if (self->errnum == WERRNO_NOTHING && WFLAG_ISSET(WFLAG_CONNECTED, self))
	{
		self->errnum = WERRNO_EXIT_EXIST_CONN;
	}

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

