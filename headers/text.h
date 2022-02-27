/*
 * text.h
 *
 * Licensed under GPLv3
 *
 */

#ifndef TEXT_H
#define TEXT_H

/* Terminal escape sequences */
#define LINE_RESET    "\33[2K\r" /* Erases the current line */
#define COLOR_RESET  "\x1B[0m"   /* Set the text color to default */
#define COLOR_RED    "\x1B[31m"
#define COLOR_GREEN  "\x1B[32m"
#define COLOR_YELLOW "\x1B[33m"

/* Error prefixes */
<<<<<<< HEAD
#define TEXT_BANG	"[" COLOR_RED "!" COLOR_RESET "] "
#define TEXT_INFO	TEXT_BANG COLOR_YELLOW	"INFORMATION   " COLOR_RESET ": "
#define TEXT_WARNING	TEXT_BANG COLOR_YELLOW	"WARNING       " COLOR_RESET ": "
#define TEXT_HEAVWARN	TEXT_BANG COLOR_RED	"HEAVY WARNING " COLOR_RESET ": "
#define TEXT_ERROR	TEXT_BANG COLOR_RED	"ERROR         " COLOR_RESET ": "
#define TEXT_INTERROR	TEXT_BANG COLOR_RED	"INTERNAL ERROR" COLOR_RESET ": "
#define TEXT_CONFERR	TEXT_BANG COLOR_RED	"CONFIG ERROR  " COLOR_RESET ": "
#define TEXT_PANIC	TEXT_BANG COLOR_RED	"!!! PANIC !!! " COLOR_RESET ": Unknown error code !\n"
#define TEXT_SUCCESS	TEXT_BANG COLOR_GREEN	"OK            " COLOR_RESET ": "
=======
#define TEXT_INFO                  "INFORMATION"    COLOR_RESET ": "
#define TEXT_WARNING  COLOR_YELLOW "WARNING"        COLOR_RESET ": "
#define TEXT_HEAVWARN COLOR_RED    "HEAVY WARNING"  COLOR_RESET ": "
#define TEXT_ERROR    COLOR_RED    "ERROR"          COLOR_RESET ": "
#define TEXT_INTERROR COLOR_RED    "INTERNAL ERROR" COLOR_RESET ": "
#define TEXT_PANIC    COLOR_RED    "!!! PANIC !!!"  COLOR_RESET ": Unknown error code !\n"
#define TEXT_SUCCESS  COLOR_GREEN  "OK"             COLOR_RESET ": "
>>>>>>> 3da5b17eb93caae77b67c572bede6e6bfef2f9c0

/* Error messages */
#define TEXT_ERROR_EXITING		"Exiting\n"
#define TEXT_ERROR_EXITING_DONE		"Exiting DONE\n"

<<<<<<< HEAD
#define TEXT_ERROR_MALLOC_OUTOFMEM	"Ran out of memory\n"
#define TEXT_ERROR_MALLOC_FAILED	"Unknown error at memory allocation [%s:%d]\n"
=======
#define TEXT_ERROR_MALLOC_OUTOFMEM    "malloc: Ran out of memory\n"
#define TEXT_ERROR_MALLOC_FAILED      "malloc: Unknown error [%s:%d]\n"
>>>>>>> 3da5b17eb93caae77b67c572bede6e6bfef2f9c0

#define TEXT_ERROR_FILE_LOG_OPEN	"Failed to open log file %s\n"

#define TEXT_ERROR_FILE_CONF_PARSE	"In config file %s line %d error parsing line \n%s\n%s\n"
#define TEXT_ERROR_FILE_CONF_PATH	"Config file path was NULL\n"
#define TEXT_ERROR_FILE_CONF_OPEN	"Failed to open config file %s. Trying default at %s\n"
#define TEXT_ERROR_FILE_CONF_OPENDEF	"Failed to open default config file. Check if %s exists\n"
#define TEXT_ERROR_FILE_CONF_EMPTY	"Config file %s is empty"
#define TEXT_ERROR_FILE_CONF_LONGLINE	"Line in config file is too long:\n%s\n"
#define TEXT_ERROR_FILE_CONF_READING	"Unexpected error reading from %s. Last line:\n %s\n"
#define TEXT_ERROR_FILE_CONF_PARAM	"In config file %s line %d parameter not recognised: %s\n"
#define TEXT_ERROR_FILE_CONF_VAL_TRAILING	"Trailing value found for parameter %s in %s:%d\n"
#define TEXT_ERROR_FILE_CONF_VAL_INVALID	"Invalid value %s for parameter %s in %s:%d\n"
#define TEXT_ERROR_FILE_CONF_VAL_MISSING	"Missing value after %s for parameter %s in %s:%d\n"

#define TEXT_ERROR_ARG_EXPECTED_PARAM	"Expected parameter for arg %c\n"
#define TEXT_ERROR_ARG_UNKNOWN		"Unknown argument %c\n"
#define TEXT_ERROR_ARG_UNKNOWN2		"Argument not recognised: %s. Also check %s\n"
#define TEXT_ERROR_ARG_NODOUBLEDASH	"Argument %s does not start with '--'\n"
#define TEXT_ERROR_ARG_ARGV_NULL	"argv was NULL\n"
#define TEXT_ERROR_ARG_SINGLECHAR	"Single char arg caught: %s\n"
#define TEXT_ERROR_ARG_MULTICHAR	"Multi char arg caught: %s\n"

#define TEXT_ERROR_PTHREAD_SYS_LIMIT	"Insufficient resources or system limit for creating thread with id %d at ip %s\n"
#define TEXT_ERROR_PTHREAD_INVAL	"Invalid initializing values for creating thread with id %d at ip %s\n"
#define TEXT_ERROR_PTHREAD_PERM		"Insufficient permissions for creating thread with id %d at ip %s\n"

#define TEXT_ERROR_WORKER_TIMEOUT_HALT	"%d workers have timed out on a HALT request\n"
#define TEXT_ERROR_WORKER_TIMEOUT_DISCONN	"%d workers have timed out on disconnecting from their nodes request\n"
#define TEXT_ERROR_WORKER_TIMEOUT_EXIT	"%d workers have timed out on exiting\n"

/* The splash screen */
#define TEXT_SPLASH "   _______________  ________    _______________   _______\n" \
                    "  / ___/_  __/ __ \\/ ____/ /   /  _/_  __/__  /  /  _/   |\n" \
                    "  \\__ \\ / / / /_/ / __/ / /    / /  / /    / /   / // /| |\n" \
                    " ___/ // / / _, _/ /___/ /____/ /  / /    / /___/ // ___ |\n" \
                    "/____//_/ /_/ |_/_____/_____/___/ /_/    /____/___/_/  |_|\n\n" \
                    "<< 2022 SENPAI Molecular Dynamics>>\n" \
                    "<< STRELITZIA and its source code are licensed under the terms of the GPLv3 license >>\n" \
                    "<< https://senpaimd.org | https://github.com/SENPAI-Molecular-Dynamics/STRELITZIA >> \n"

/* The usage tooltip (see utils.c print_usage() */
#define TEXT_USAGE "Usage: strelitzia" \
                   "c / -c / --config [file]  Specify config file\n" \
                   "l / -l / --log    [file]  Specify log file\n" \
                   "h / -h / --help           Show this usage\n" \



/* The information displayed at startup */
#define TEXT_INITIALIZING      "Initializing\n"
#define TEXT_INITIALIZING_DONE "Initializing DONE\n"

#define TEXT_INFO_FROM        "From [%s:%d]:\n"
#define TEXT_INFO_FILE_CONFIG "Config file:  %s\n"
#define TEXT_INFO_FILE_LOG    "Log file:     %s\n"
#define TEXT_INFO_WORKER_NB   "Workers:      %d\n"
#define TEXT_INFO_WORKER      "=>[%03d|%-8.8s]: [m:w]=%s:%s, port=%5d, ip=%-39s\n"



#define TEXT_FILE_CONF_PARSING "Parsing config file %s\n"
#define TEXT_ARG_PARSING       "Parsing arguments\n"

#endif
