#include "exit.h"

// TODO: Implement
/* Standard exit procedure */
void Exit(strelitzia_t *env)
{

}

/* 
 * Something has gone horribly wrong.
 * Notify everyone to abort and exit.
 */
void Abort(int exit_code)
{
	exit(exit_code);
}

