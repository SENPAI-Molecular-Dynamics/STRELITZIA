#include "utils.h"
#include "exit.h"

#include <stdarg.h>
#include <time.h>

worker_t *worker_get_by_id(uint32_t id, worker_t *workers, uint32_t num_workers)
{
	if (id > num_workers + 1)
	{
		return NULL;
	}

	return &workers[id - 1];
}

/* Warning and error messages */
void throw_err(const int err_code, const char *format, ...)
{
	/* If system is already aborting, don't do this */
	if (flags & FLAG_ABORTING)
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
			fprintf(logfile, "%s Info: ", timestr);
			break;
		}

		case ERR_WARN:
		{
			fprintf(logfile, "%s Warn: ", timestr);
			break;
		}

		case ERR_HEAVY_WARN:
		{
			fprintf(logfile, "%s Heavy Warning: ", timestr);
			break;
		}

		case ERR_UNSPEC | ERR_FATAL:
		{
			fprintf(logfile, "%s ERROR: ", timestr);
			break;
		}

		case ERR_INTERN:
		{
			fprintf(logfile, "%s Internal ERROR: ", timestr);
			break;
		}

		default:
			throw_err(ERR_WARN, "Unrecognised error type: %d\n", err_code);

	}

	vfprintf(logfile, format, variadic_args);

	/* Also nessecary. See above */
	va_end(variadic_args);

	/* For bad errors exit */
	if (err_code <= 0)
	{
		Abort(err_code);
	}
}

