#include "exit.h"
#include "utils.h"

/* Standard exit procedure */
void Exit(arg_t *args)
{
	throw_err(ERR_INFO, "Exiting\n");

	if (!lzenv)
	{
		throw_err(ERR_INTERN, "env was NULL\n");
	}

	// I should be freeing this here, but that makes everything more complicated
	// Because I can't free it if it's the default value from #define
	// And it's just a few bytes anyways and the program is in the process of exiting...
	// free(lzenv->config.path);
	free(lzenv);

	if (!args)
	{
		throw_err(ERR_INTERN, "args was NULL\n");
	}

	// Same as above. Maybe I'll fix it later.
	// free(args->log_file);
	// free(args->config_file);

	throw_err(ERR_INFO, "Done exiting\n");

	/* Don't accidentally close stderr */
	if (logfile != stderr)
	{
		fclose(logfile);
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
	flags |= FLAG_ABORTING;

	/* Attempt to push all errors to COFFIN */
	for (uint32_t i = 0; i < lzenv->error_count; i++)
	{
		// TODO: Implement
	}

	exit(COF_EX_FAIL);
}

