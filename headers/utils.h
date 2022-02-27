#ifndef UTILS_H
#define UTILS_H

#include "defines.h"

// TODO: Actually C funcions exist for this, might be something to consider: man 3 isalpha
/* Macro to check if char is a valid character */
#define TEST_CHAR_WORD(c) (c > 0x21 && c < 0x7F)
#define TEST_CHAR_SEPERATOR(c) (c == ' ' || c == '\t')

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

/* Macro to return the ith bit of x */
#define ret_bit(x, i) (x & (1 << i))
/* Macro to map the ith bit value of x to a char */
#define ret_bin(x, i) (ret_bit(x, i) ? '1' : '0')

/* Utility for working with flags */
#define MFLAG_ISSET(flag, worker) (worker->mflags & flag)
#define WFLAG_ISSET(flag, worker) (worker->wflags & flag)
#define WFLAG_UNSET(flag, worker) (worker->wflags &= ~flag)
#define MFLAG_UNSET(flag, worker) (worker->mflags &= ~flag)
#define WFLAG_SET(flag, worker) (worker->wflags |= flag)
#define MFLAG_SET(flag, worker) (worker->mflags |= flag)

/* Set the flag for all workers */
int setall_flag(uint8_t flag);
/* Unset the flag for all workers */
int unsetall_flag(uint8_t flag);
/* Wait for all workers to set the flag or timeout */
uint32_t expect_flag(uint8_t flag, int64_t timeout_millis);
/* Wait for all workers to unset the flag or timeout */
uint32_t expect_nflag(uint8_t flag, int64_t timeout_millis);

/* Create a new worker */
worker_t *worker_create();
/* Spawn the threads for each worker */
void workers_start();

/* Find next string in a char array of NULL-delimited strings ending in 2 NULL bytes*/
int next_word(char **words);

/* Calculate accurate timedelta from struct timespec in microseconds */
int64_t timedelta_micro(struct timespec a, struct timespec b);

/* Convert a string to an unsigned short. 0 if out of range */
uint16_t str_to_ushort(const char *str);

/* Prints len bits in binary starting from ptr into dst */
// WARN: this will segfault if the delivered string does not end in two NULL bytes 
void sprintb(char **dst, void *src, uint32_t len);

/* Warning and error messages */
// WARN: I don't think this is thread safe (Besides it's using a global var for the logfile). Don't use in threads
void throw_err(const int err_code, const char *format, ...);

/* Log some debugging information about the system */
void print_sys_stats(char *file, int line);

/* Usage text */
void print_usage();

#endif // !UTILS_H
