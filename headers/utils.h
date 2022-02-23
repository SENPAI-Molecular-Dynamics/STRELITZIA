#ifndef UTILS_H
#define UTILS_H

#include "defines.h"

/* Not sure if this will ever be needed */
worker_t *worker_get_by_id(uint32_t id, worker_t *workers, uint32_t num_workers);

/* Warning and error messages */
void throw_err(const int err_code, const char *format, ...);

#endif // !UTILS_H
