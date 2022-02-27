#include "utils.h"
#include "exit.h"
#include "text.h"
#include "worker.h"

#include <stdarg.h>
#include <string.h>

/* Set the flag for all workers */
int setall_flag(uint8_t flag)
{
	for (uint32_t i = 0; i < env.worker_count; i++)
	{
		env.workers[i].mflags |= flag;
	}
}

/* Unset the flag for all workers */
int unsetall_flag(uint8_t flag)
{
	for (uint32_t i = 0; i < env.worker_count; i++)
	{
		env.workers[i].mflags &= ~flag;
	}
}

/* Wait for all workers to set the flag or timeout */
/* Returns number of timed out workers */
uint32_t expect_flag(uint8_t flag, int64_t timeout_millis)
{
	struct timespec start, now;
	clock_gettime(CLOCK_BOOTTIME, &start);
	now = start;

	uint32_t true_count = 0;

	while (timedelta_micro(now, start) < (timeout_millis * 1000))
	{
		true_count = 0;

		for (uint32_t i = 0; i < env.worker_count; i++)
		{
			if (env.workers[i].wflags & flag)
			{
				/* Temporarily set the timeout flag, we'll invert it afterwards */
				env.workers[i].mflags |= MFLAG_TIMEOUT;
				true_count++;
			}
		}

		/* All have responded */
		if (true_count == env.worker_count)
		{
			/* Make sure to unset any timeout flags */
			unsetall_flag(MFLAG_TIMEOUT);
			return 0;
		}

		/* Update the time */
		clock_gettime(CLOCK_BOOTTIME, &now);
	}

	/* Not all have responded */
	for (uint32_t i = 0; i < env.worker_count; i++)
	{
		/* Invert the timeout flag, so that the timed out ones have it set */
		env.workers[i].mflags ^= MFLAG_TIMEOUT;
	}

	return env.worker_count - true_count;
}

/* Wait for all workers to unset the flag or timeout */
/* Returns number of timed out workers */
uint32_t expect_nflag(uint8_t flag, int64_t timeout_millis)
{
	struct timespec start, now;
	clock_gettime(CLOCK_BOOTTIME, &start);
	now = start;

	uint32_t true_count = 0;

	while (timedelta_micro(now, start) < timeout_millis * 1000)
	{
		true_count = 0;

		for (uint32_t i = 0; i < env.worker_count; i++)
		{
			if (!(env.workers[i].wflags & flag))
			{
				/* Temporarily set the timeout flag, we'll invert it afterwards */
				env.workers[i].mflags |= MFLAG_TIMEOUT;
				true_count++;
			}
		}

		/* All have responded */
		if (true_count == env.worker_count)
		{
			/* Make sure to unset any timeout flags */
			unsetall_flag(MFLAG_TIMEOUT);
			return 0;
		}

		/* Update the time */
		clock_gettime(CLOCK_BOOTTIME, &now);
	}

	/* Not all have responded */
	for (uint32_t i = 0; i < env.worker_count; i++)
	{
		/* Invert the timeout flag, so that the timed out ones have it set */
		env.workers[i].mflags ^= MFLAG_TIMEOUT;
	}

	return env.worker_count - true_count;
}

worker_t *worker_create()
{
	env.worker_count++;
	worker_t *tmp = (worker_t *) reallocarray((void *) env.workers, env.worker_count, sizeof(worker_t));
	
	/* If we could not create a new worker */
	if (!tmp)
	{
		if (errno == ENOMEM)
		{
			throw_err(ERR_INTERN, TEXT_ERROR_MALLOC_OUTOFMEM);
		} else {
			throw_err(ERR_INTERN, TEXT_ERROR_MALLOC_FAILED, __FILE__, __LINE__);
		}
	}

	env.workers = tmp;
	worker_t *self = &env.workers[env.worker_count - 1];

	/* Set appropriate flags */
	self->mflags = MFLAG_HALT;
	self->wflags = WFLAG_HALTING;
	self->wflags |= WFLAG_ALIVE;

	/* Set information */
	self->errnum = WERRNO_NOTHING;
	self->id = env.worker_count;
	self->name = (char *) malloc(CONF_READ_BUF_SIZE);
	self->ip_str = (char *) malloc(CONF_READ_BUF_SIZE);

	return self;
}

/* Spawn the threads for each worker */
void workers_start()
{
	for (uint32_t i = 0; i < env.worker_count; i++)
	{
		worker_t *self = &env.workers[i];
		/* Spawn a thread for communicating with the worker */
		if (!pthread_create(&self->tid, NULL, worker_main_loop, (void *) self))
		{
			switch (errno)
			{
				case EAGAIN:
				{
					throw_err(ERR_INTERN, TEXT_ERROR_PTHREAD_SYS_LIMIT, self->id, self->ip_str);
				}
				case EINVAL:
				{
					throw_err(ERR_INTERN, TEXT_ERROR_PTHREAD_INVAL, self->id, self->ip_str);
				}
				case EPERM:
				{
					throw_err(ERR_INTERN, TEXT_ERROR_PTHREAD_PERM, self->id, self->ip_str);
				}
			}
		}
	}
}

/* Find next string in a char array of NULL-delimited strings ending in 2 NULL bytes*/
/* WARN: this will segfault if the delivered string does not end in two NULL bytes */
int next_word(char **words)
{
	int len = strlen(*words) + 1;

	/* If the beginning char of the next string is NULL, this is the end */
	if ((*words)[len] == 0x00)
	{
		return 0;
	}

	/* Update the pointer to the beginning of the next string */
	*words += len;

	/* How much it was shifted by */
	return len;
}

/* Calculate accurate timedelta from struct timespec in microseconds */
int64_t timedelta_micro(struct timespec a, struct timespec b)
{
	int64_t micros = (a.tv_nsec - b.tv_nsec) / 1000;
	micros += (a.tv_sec - b.tv_sec) * 1000000;

	return micros;
}

/* Calculate accurate timedelta from struct timespec in nanoseconds */
int64_t timedelta_nano(struct timespec a, struct timespec b)
{
	int64_t nanos = (a.tv_nsec - b.tv_nsec);
	nanos += (a.tv_sec - b.tv_sec) * 1000000000;

	return nanos;
}

uint16_t str_to_ushort(const char *str)
{
	long val = strtol(str, NULL, 0);
	
	if (val <= 0 || val >= (1 << 16))
	{
		return 0;
	}

	return (uint16_t) val;
}

/* Prints len bits in binary starting from ptr into dst */
void sprintb(char **dst, void *src, uint32_t len)
{
	char *cptr = (char *) src;
	for (uint32_t i = 0; i < len; i++)
	{
		sprintf(*dst + i, "%c", ret_bin(cptr[i / 8], 7 - i % 8));
	}
}

/* Warning and error messages */
// WARN: I don't think this is thread safe (Besides it's using a global var for the logfile). Don't use in threads
void throw_err(const int err_code, const char *format, ...)
{
	/* If system is already aborting, don't do this */
	if (conf.flags & FLAG_ABORTING)
	{
		return;
	}

	/* Nessecary for variadic functions. Look at $ man 3 stdarg */
	va_list variadic_args;
	va_start(variadic_args, format);

	/* Get current time */
	char timestr[1024];
	time_t t = time(NULL);
	struct tm *p = localtime(&t);
	strftime(timestr, 1024, "[%F %H:%M:%S]", p);

	/* Now look how bad the error was */
	switch (err_code)
	{
		case ERR_INFO:
		{
			fprintf(conf.logfile.fd, "%s %s", timestr, TEXT_INFO);
			break;
		}

		case ERR_WARN:
		{
			fprintf(conf.logfile.fd, "%s %s", timestr, TEXT_WARNING);
			break;
		}

		case ERR_HEAVY_WARN:
		{
			fprintf(conf.logfile.fd, "%s %s", timestr, TEXT_HEAVWARN);
			break;
		}

		case ERR_UNSPEC | ERR_FATAL:
		{
			fprintf(conf.logfile.fd, "%s %s", timestr, TEXT_ERROR);
			break;
		}

		case ERR_INTERN:
		{
			fprintf(conf.logfile.fd, "%s %s", timestr, TEXT_INTERROR);
			break;
		}

		case ERR_CONFIG:
		{
			fprintf(conf.logfile.fd, "%s %s", timestr, TEXT_CONFERR);
		}

		default:
			throw_err(ERR_WARN, TEXT_PANIC, err_code);

	}

	vfprintf(conf.logfile.fd, format, variadic_args);

	/* Also nessecary. See above */
	va_end(variadic_args);

	/* For bad errors exit */
	if (err_code <= 0)
	{
		Abort(err_code);
	}
}

/* Log some debugging information about the system */
void print_sys_stats(char *file, int line)
{
	char *mflags = (char *) malloc(9);
	char *wflags = (char *) malloc(9);
	mflags[9] = 0x00;
	wflags[9] = 0x00;

	throw_err(ERR_INFO, TEXT_INFO_FROM, file, line);
	throw_err(ERR_INFO, TEXT_INFO_FILE_CONFIG, conf.conf_file.path);
	throw_err(ERR_INFO, TEXT_INFO_FILE_LOG, conf.logfile.path);
	throw_err(ERR_INFO, TEXT_INFO_WORKER_NB, env.worker_count);
	for (uint32_t i = 0; i < env.worker_count; i++)
	{
		worker_t *worker = &env.workers[i];

		sprintb(&mflags, &worker->mflags, 8);
		sprintb(&wflags, &worker->wflags, 8);

		throw_err(ERR_INFO, TEXT_INFO_WORKER,
			worker->id, worker->name, mflags, wflags, worker->errnum, worker->port, worker->ip_str);
	}

	free(mflags);
	free(wflags);
}

void print_usage()
{
	// USAGE_STRING defined in codes.h
	printf(TEXT_USAGE);
}

