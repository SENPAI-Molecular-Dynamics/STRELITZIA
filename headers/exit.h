#ifndef EXIT_H
#define EXIT_H

/* Exit codes for Coffin */
#define EXIT_CODE_NORMAL 0
#define EXIT_CODE_ERR_INTERN 1
#define EXIT_CODE_ERR_CONFIG 2
#define EXIT_CODE_ERR_FATAL 3

#include "defines.h"

// TODO: Implement
/* Standard exit procedure */
void Exit(strelitzia_t *env);
/* 
 * Something has gone horribly wrong.
 * Notify everyone to abort and exit.
 */
void Abort(int exit_code);

#endif // !EXIT_H
