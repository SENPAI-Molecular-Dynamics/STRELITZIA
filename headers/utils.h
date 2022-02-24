#ifndef UTILS_H
#define UTILS_H

#include "defines.h"

/* Macro to check if char is a valid character */
#define TEST_CHAR_WORD(c) (c > 0x21 && c < 0x7F)
#define TEST_CHAR_SEPERATOR(c) (c == ' ' || c == '\t')

/* Not sure if this will ever be needed */
worker_t *worker_get_by_id(uint32_t id);

/* Create a new worker */
void worker_create();

/* Warning and error messages */
void throw_err(const int err_code, const char *format, ...);

/* Usage text */
void print_usage();

#endif // !UTILS_H
