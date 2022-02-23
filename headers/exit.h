#ifndef EXIT_H
#define EXIT_H

#include "defines.h"

// TODO: Implement
/* Standard exit procedure */
void Exit(arg_t *args);
/* 
 * Something has gone horribly wrong.
 * Notify everyone to abort and exit.
 */
void Abort(const int error_code);

#endif // !EXIT_H
