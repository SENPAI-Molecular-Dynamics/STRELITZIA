#include "utils.h"

#include <stdarg.h>

worker_t *worker_get_by_id(uint32_t id, worker_t *workers, uint32_t num_workers)
{
	if (id > num_workers + 1)
	{
		return NULL;
	}

	return &workers[id - 1];
}

/* Warning and error messages */
void throw_err(const int type, const char *format, ...)
{
	FILE *stream;

	/* Which stream to log to, default stderr */
	#ifdef LOG_FILE
		if (!LOG_FILE)
		{
			fprintf(stderr, "Log file name specified was NULL. Defaulting to stderr\n");
			stream = stderr;
		} else {
			stream = fopen(LOG_FILE, "a");
		}
	#endif /* LOG_FILE */

	#ifndef LOG_FILE

	#ifdef LOG_STREAM
		stream = LOG_STREAM
	#endif /* LOG_STREAM */

	#ifndef LOG_STREAM
		stream = stderr;
	#endif /* !LOG_STREAM */

	#endif /* !LOG_FILE */

	/* Nessecary for variadic functions. Look at $ man 3 stdarg */
	va_list args;
	va_start(args, format);

	/* If we couldn't open the log file, we can't log. That's bad. */
	if (!stream)
	{
		vfprintf(stderr, format, args);

		#ifdef LOG_FILE
		fprintf(stderr, "\nThe above error occured but we could not open the log file %s.\n Exiting.\n", LOG_FILE);
		#endif /* LOG_FILE */
		#ifndef LOG_FILE
		fprintf(stderr, "\nThe above error occured but we could not open the log file.\n Exiting.\n");
		#endif /* !LOG_FILE */

		Abort(EXIT_CODE_ERR_CONFIG);
	}

	vfprintf(stream, format, args);

	/* Also nessecary. See above */
	va_end(args);

	// TODO: Implement
	/* Now look how bad the error was */
	switch (type)
	{
		case ERR_TYPE_INFO:
		{
			break;			
		}

		case ERR_TYPE_WARN:
		{
			break;			
		}

		case ERR_TYPE_ERR:
		{
			break;			
		}

		case ERR_TYPE_FATAL:
		{
			Abort(EXIT_CODE_ERR_FATAL);
			break;			
		}

		default:
		{
			throw_err(ERR_TYPE_INFO, "Unrecognised error type: %d\n", type);
		}

	}
}

