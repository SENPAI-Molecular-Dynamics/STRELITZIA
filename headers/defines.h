#ifndef DEFINES_H
#define DEFINES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "codes.h"
//#include "universe.h"

//#define DEFAULT_CONFIG_FILE "/etc/senpai/strelitzia.conf"
#define DEFAULT_CONFIG_FILE "./strelitzia.conf"
//#define DEFAULT_LOG_FILE "/var/log/strelitzia.log"
#define DEFAULT_LOG_FILE "./strelitzia.log"

/* Everything you might need from a file */
typedef struct
{
	char *path;
	FILE *fd;
	uint32_t file_len;
} file_t;

typedef struct
{
	int argc;
	char **argv;
	
	uint8_t flags;

	char *config_file;
	char *log_file;
} arg_t;

/* Information about each worker */
typedef struct
{
	/* Reference */
	uint32_t id;

	/* Networking */
	// TODO: This is just a placeholder
	uint32_t ip;
	uint16_t port;

	/* Timing */
	// TODO: This is just a placeholder
	time_t start, finish;

	/* The range of atoms to work on */
	uint64_t atom_range[2];
	/* The work returned */
	char *result;

	/* If the worker encounters an error */
	uint32_t errno;
	char *errdesc;
} worker_t;

/* Errors may contain this information */
typedef struct
{
	/* Who is responsible */
	uint32_t worker_id;
	// Or perhaps ?
	worker_t *culprit;
	
	/* What happened? */
	uint32_t errno;
	char *desc;
} error_t;

/* Globally important stuff */
typedef struct
{
	/* Place for STRELITZIA to put its files. i.e. mountpoint of ramdisk */
	char *working_dir;

	/* Various files */
	file_t render_out;
	file_t mds_in, mdm_in, mdp_in;
	file_t config;

	/* Keep track of this */
	uint32_t frame_num;
	uint32_t error_count;
	error_t *errs;
	uint32_t worker_count;
	worker_t *workers;

	/* The reason we're doing this */
	//universe_t *universe;
} strelitzia_t;

/* Global stuff */
extern uint8_t flags;
extern FILE *logfile;
extern strelitzia_t *lzenv;

#endif // !DEFINES_H
