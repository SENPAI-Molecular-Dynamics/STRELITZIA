#ifndef DEFINES_H
#define DEFINES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//#include "universe.h"

/* Everything you might need from a file */
typedef struct
{
	char *path;
	FILE *fd;
	uint32_t file_len;
} file_t;

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

	/* Keep track of this */
	uint32_t frame_num;
	error_t *errs;
	uint32_t worker_count;
	worker_t *workers;

	/* The reason we're doing this */
	//universe_t *universe;
} strelitzia_t;

#endif // !DEFINES_H