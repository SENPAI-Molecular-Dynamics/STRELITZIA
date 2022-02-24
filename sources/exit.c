#include "exit.h"
#include "utils.h"
#include "text.h"

/* Standard exit procedure */
void Exit()
{
	throw_err(ERR_INFO, TEXT_ERROR_EXITING);

	/* Also close the workers */

	throw_err(ERR_INFO, TEXT_ERROR_EXITING_DONE);

	/* Don't accidentally close stderr */
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

	/* Attempt to push all errors to COFFIN */
	for (uint32_t i = 0; i < env.error_count; i++)
	{
		// TODO: Implement
	}

	exit(COF_EX_FAIL);
}

