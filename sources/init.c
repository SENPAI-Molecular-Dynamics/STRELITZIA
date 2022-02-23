#include "init.h"
#include "exit.h"
#include "utils.h"

void parse_args(arg_t *args);
void parse_config(file_t *file);

void Init (arg_t *args)
{
	/* Temporarily use stderr as log file until the real one has been determined */
	logfile = stderr;

	throw_err(ERR_INFO, "Initializing\n");

	lzenv = malloc(sizeof(strelitzia_t));

	// TODO: Do better checking here, i.e. out of memory, etc
	if (!lzenv)
	{
		throw_err(ERR_INTERN, "Env was NULL\n");
	}

	/* Init args */
	if (!args)
	{
		throw_err(ERR_INTERN, "Args was NULL\n");
	}

	args->config_file = NULL;
	args->log_file = NULL;
	args->flags = 0;

	parse_args(args);

	/* Prepare config file */
	if (!args->config_file)
	{
		lzenv->config.path = DEFAULT_CONFIG_FILE;
	} else {
		lzenv->config.path = args->config_file;
	}

	parse_config(&lzenv->config);

	/* Now that all config has been read, we can use the real logfile (Still default here) */
	if (!args->log_file)
	{
		logfile = fopen(DEFAULT_LOG_FILE, "a");
	} else {
		logfile = fopen(args->log_file, "a");
	}
	if (!logfile)
	{
		fprintf(stderr, "Failed to open log file %s\n", DEFAULT_LOG_FILE);
		Abort(ERR_INTERN);
	}

	throw_err(ERR_INFO, "Done initializing\n");
}

void parse_args(arg_t *args)
{
	throw_err(ERR_INFO, "Parsing arguments\n");

	args->config_file = DEFAULT_CONFIG_FILE;
	args->log_file = DEFAULT_LOG_FILE;
}

void parse_config(file_t *file)
{
	throw_err(ERR_INFO, "Parsing config file %s\n", file->path);

	if (!file->path)
	{
		throw_err(ERR_INTERN, "Config file path was NULL\n");
	}

	file->fd = fopen(file->path, "r");
	
	// TODO: Should we ignore missing config or fail?
	if (!file->fd)
	{
		throw_err(ERR_WARN, "Failed to open config file %s. Skipping\n", file->path);
		return;
	}	

	fclose(file->fd);
}

