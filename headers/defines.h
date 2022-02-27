#ifndef DEFINES_H
#define DEFINES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>

#include "codes.h"
//#include "universe.h"

//#define DEFAULT_CONFIG_FILE "/etc/senpaimd/strelitzia.conf"
#define DEFAULT_CONFIG_FILE "./strelitzia.conf"
//#define DEFAULT_LOG_FILE "/var/log/strelitzia.log"
#define DEFAULT_LOG_FILE "./strelitzia.log"
#define CONF_READ_BUF_SIZE 1024		// Max line length of config file

// TODO: This might belong in the config file too
// TODO: Make a defaults.h
/* Timeouts for various events */
#define WORKER_HALT_TIMEOUT_MILLIS 3000		// 3 Seconds for halting
#define WORKER_DISCONN_TIMEOUT_MILLIS 3000	// 3 Seconds for disconnecting
#define WORKER_EXIT_TIMEOUT_MILLIS 1000		// 1 Second for exiting

/* Everything you might need from a file */
typedef struct
{
	char *path;
	FILE *fd;
	uint32_t len;
} file_t;

typedef struct
{
	uint8_t flags;
	file_t conf_file;
	file_t logfile;
} config_t;

/* Information about each worker */
typedef struct
{
	/* Reference */
	uint32_t id;
	char *name;

	/* Keep track of the state of a worker */
	uint8_t mflags;		// Set by manager
	uint8_t wflags;		// Set by worker

	/* Networking */
	char *ip_str;		// String for of the IP address
	uint16_t port;		// The port to connect to
	int sockfd;		// File descriptor of the socket to the worker node

	/* Associated thread */
	pthread_t tid;

	/* Timing */
	// TODO: This is just a placeholder
	time_t start, finish;
	/* The range of atoms to work on */
	uint64_t atom_range[2];
	/* The work returned */
	char *result;

	/* If the worker encounters an error */
	uint32_t errnum;
} worker_t;

/* Errors may contain this information */
typedef struct
{
	/* Who is responsible */
	uint32_t worker_id;
	// Or perhaps ?
	worker_t *culprit;
	
	/* What happened? */
	uint32_t errnum;
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
	uint32_t error_count;
	error_t *errs;
	uint32_t worker_count;
	worker_t *workers;

	/* The reason we're doing this */
	//universe_t *universe;
} strelitzia_t;

/* Global stuff */
extern strelitzia_t env;
extern config_t conf;

#endif // !DEFINES_H
