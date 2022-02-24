#include "utils.h"
#include "exit.h"
#include "text.h"

#include <stdarg.h>
#include <time.h>

worker_t *worker_get_by_id(uint32_t id)
{
	if (id > env.worker_count)
	{
		return NULL;
	}

	// strelitzia has id 0, workers increasing from there
	return &env.workers[id - 1];
}

void worker_create()
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
	env.workers[env.worker_count - 1].id = env.worker_count;
	env.workers[env.worker_count - 1].flags = WFLAG_UNFINISHED;
}

/* Warning and error messages */
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

void print_usage()
{
	// USAGE_STRING defined in codes.h
	printf(TEXT_USAGE);
}

