#ifndef UTILS_H
#define UTILS_H

#include "defines.h"
#include "exit.h"

/* Error levels for throw_err */
#define ERR_TYPE_INFO 2
#define ERR_TYPE_WARN 1
#define ERR_TYPE_ERR  0
#define ERR_TYPE_FATAL -1

/* Not sure if this will ever be needed */
worker_t *worker_get_by_id(uint32_t id, worker_t *workers, uint32_t num_workers);

/* Warning and error messages */
void throw_err(const int type, const char *format, ...);

#endif // !UTILS_H
