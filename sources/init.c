#include "init.h"
#include "exit.h"
#include "utils.h"
#include "text.h"

#include <string.h>

// TODO: Improve this
void parse_args(int argc, char **argv);
void parse_config();

void Init (int argc, char **argv)
{
	/* Temporarily use stderr as log file until the real one has been determined */
	conf.logfile.fd = stderr;

	throw_err(ERR_INFO, TEXT_INITIALIZING);

	/* Initialize config values */
	conf.conf_file.path = NULL;
	conf.logfile.path = (char *) malloc(CONF_READ_BUF_SIZE);
	conf.flags = 0;

	parse_args(argc, argv);

	/* Prepare config file */
	if (!conf.conf_file.path)
	{
		conf.conf_file.path = DEFAULT_CONFIG_FILE;
	}

	parse_config();


	/* Now try to open the real log file */
	if (!conf.logfile.path)
	{
		conf.logfile.path = DEFAULT_LOG_FILE;
	}
	conf.logfile.fd = fopen(conf.logfile.path, "a");

	if (!conf.logfile.fd)
	{
		fprintf(stderr, TEXT_ERROR_FILE_LOG_OPEN, DEFAULT_LOG_FILE);
		Abort(ERR_INTERN);
	}

	throw_err(ERR_INFO, TEXT_INITIALIZING_DONE);
}

void parse_line(char *line, int lineno)
{
	/* i is for source string, j for destination */
	int i = 0, j = 0;
	char words[CONF_READ_BUF_SIZE];
	char c = line[0], b = 1;

	/* If we've reached a comment we might as well leave */
	/* Trust that the string is NULL-terminated because it should be */
	while (c != '#' && c != 0x00)
	{
		if (TEST_CHAR_WORD(c))
		{
			words[j] = c;		// Append to the list
			b = 1;			// Last char was not a seperator
			j++;
		} else if (TEST_CHAR_SEPERATOR(c))
		{
			/* If the last char was already a seperator we don't need another one */
			if (b)
			{
				words[j] = ' ';	// Put seperator in the list
				b = 0;		// Last char was seperator
				j++;
			}
		}

		i++;
		c = line[i];
	}
	words[j] = 0x00;	// Null-terminate the string

	/* Back up values for logging */
	char bak_param[CONF_READ_BUF_SIZE];
	char bak_words[CONF_READ_BUF_SIZE];
	strcpy(bak_words, words);

	int type = 0;			// Wich confige param is being set this line
	const char *delim = " ";	// The delimiter, we're using ' ' here;
	
	/* Get the first token */
	char *token = strtok(words, delim);

	/* The line did not contain any information (empty line, comment) */
	if (!token)
	{
		return;
	}

	/* Backup */
	strcpy(bak_param, token);

	if (strcmp(token, CONF_LOG_PARAM) == 0) {
		type = CONF_LOG_ID;
	} else if (strcmp(token, CONF_WORKER_IP4_PARAM) == 0) {
		type = CONF_WORKER_IP4_ID;
	} else if (strcmp(token, CONF_WORKER_IP6_PARAM) == 0) {
		type = CONF_WORKER_IP6_ID;
	} else {
		throw_err(ERR_INTERN, "In config file %s line %d parameter not recognised: %s\n",
			conf.conf_file.path, lineno, bak_param);
	}

	/* Get the next token */
	token = strtok(NULL, delim);
	if (!token)
	{
		throw_err(ERR_INTERN, "In config file %s line %d missing value after parameter %s\n",
			conf.conf_file.path, lineno, bak_param);
		return;
	}

	// DEBUG
	/*
	throw_err(ERR_INFO, "[%s:%d]: %s = %s from\n%s\n",
		conf.conf_file.path, lineno, bak_param, token, line);
	*/

	switch (type)
	{
		case CONF_LOG_ID:
		{
			strcpy(conf.logfile.path, token);
			break;
		}

		case CONF_WORKER_IP4_ID:
		{
			worker_create();
			// TODO: Implement networking
			env.workers[env.worker_count - 1].ipv4 = 0;
			env.workers[env.worker_count - 1].ipv6[0] = 0;
			env.workers[env.worker_count - 1].ipv6[1] = 0;
			env.workers[env.worker_count - 1].ipv6[2] = 0;
			env.workers[env.worker_count - 1].port = 0;
			break;
		}

		case CONF_WORKER_IP6_ID:
		{
			worker_create();
			// TODO: Implement networking
			env.workers[env.worker_count - 1].ipv4 = 0;
			env.workers[env.worker_count - 1].ipv6[0] = 0;
			env.workers[env.worker_count - 1].ipv6[1] = 0;
			env.workers[env.worker_count - 1].ipv6[2] = 0;
			env.workers[env.worker_count - 1].port = 0;
			break;
		}

		default:
		{
			/* This should not even occur */
			throw_err(ERR_INTERN, TEXT_ERROR_FILE_CONF_PARSE,
				conf.conf_file.path, lineno, line, bak_words);
		}
	}

	while (token != NULL)
	{
		token = strtok(NULL, delim);
	}
}

void parse_config()
{
	/* Try to open the config file */
	if (!conf.conf_file.path)
	{
		throw_err(ERR_INTERN, TEXT_ERROR_FILE_CONF_PATH);
	}

	throw_err(ERR_INFO, TEXT_FILE_CONF_PARSING, conf.conf_file.path);

	conf.conf_file.fd = fopen(conf.conf_file.path, "r");
	
	if (!conf.conf_file.fd)
	{
		throw_err(ERR_WARN, TEXT_ERROR_FILE_CONF_OPEN, conf.conf_file.path, DEFAULT_CONFIG_FILE);

		conf.conf_file.path = DEFAULT_CONFIG_FILE;
		conf.conf_file.fd = fopen(conf.conf_file.path, "r");
		
		if (!conf.conf_file.fd)
		{
			throw_err(ERR_INTERN, TEXT_ERROR_FILE_CONF_OPENDEF, conf.conf_file.path);
		}
	}	

	/* Actual parsing starts here */

	/* Get file length */
	// We actually don't need this I think, I'll just leave it here for now in case we do
	fseek(conf.conf_file.fd, 0, SEEK_END);
	conf.conf_file.len = ftell(conf.conf_file.fd);
	rewind(conf.conf_file.fd);

	if (conf.conf_file.len < 1)
	{
		throw_err(ERR_INTERN, TEXT_ERROR_FILE_CONF_EMPTY, conf.conf_file.path);
	}

	/* File is read line-by-line */
	int i = 0, l = 1;
	char c = 0x00;
	char cur_line[CONF_READ_BUF_SIZE];

	/* Check for EOF */
	while (feof(conf.conf_file.fd) == 0)
	{
		while (c != '\n')
		{
			/* Check for successful read */
			if (fread(&c, 1, 1, conf.conf_file.fd) == 1)
			{
				cur_line[i] = c;
				i++;

				/* I think it's fair to just crash here */
				if (i >= CONF_READ_BUF_SIZE - 1)
				{
					cur_line[CONF_READ_BUF_SIZE - 1] = 0x00;
					throw_err(ERR_INTERN, TEXT_ERROR_FILE_CONF_LONGLINE, cur_line);
				}
			} else {
				cur_line[i - 1] = 0x00;		// Null-terminate the string

				/* It wasn't EOF, so there's an error */
				if (feof(conf.conf_file.fd) == 0)
				{
					throw_err(ERR_INTERN, TEXT_ERROR_FILE_CONF_READING,
							conf.conf_file.path, cur_line);
				}

				/* Otherwise just leave the loop, it will exit on its own */
				cur_line[0] = 0x00;		// Make sure to not parse the line again
				break;
			}
		}

		cur_line[i - 1] = 0x00;		// Null-terminate the string
		c = 0x00;			// Reset c so we can continue
		i = 0;				// Also reset i
		l++;				// Next line in the file
		
		/* Now parse the line */
		parse_line(cur_line, l);
	}

	fclose(conf.conf_file.fd);
}

/* 
 * Takes a char** starting at the argument and a number of how many more there are
 * Returning the number of additional arguments used
 */
int parse_single_char_arg(char arg, char **argv, int remaining_args)
{
	switch(arg)
	{
		case ARG_SHORT_CONF_FILE:
		{
			if (remaining_args > 0)
			{
				return arg_found_conf(argv[1]);
			} else {
				throw_err(ERR_INTERN, TEXT_ERROR_ARG_EXPECTED_PARAM, arg);
			}
		}

		case ARG_SHORT_LOG_FILE:
		{
			if (remaining_args > 0)
			{
				return arg_found_log(argv[1]);
			} else {
				throw_err(ERR_INTERN, TEXT_ERROR_ARG_EXPECTED_PARAM, arg);
			}
		}

		case ARG_SHORT_HELP:
		{
			return arg_found_help();
		}
		
		default:
		{
			throw_err(ERR_INTERN, TEXT_ERROR_ARG_UNKNOWN, arg);
		}
	}
}

/* 
 * Takes a char** starting at the argument and a number of how many more there are
 * Returning the number of additional arguments used
 */
int parse_multi_char_arg(char **argv, int remaining_args)
{
	// Both first chars need to be --
	if (!(argv[0][0] == '-' && argv[0][1] == '-'))
	{
		throw_err(ERR_INTERN, TEXT_ERROR_ARG_NODOUBLEDASH, argv[0]);
	}

	if (strcmp(argv[0], ARG_LONG_CONF_FILE) == 0) {
		if (remaining_args > 0)
		{
			return arg_found_conf(argv[1]);
		} else {
			throw_err(ERR_INTERN, TEXT_ERROR_ARG_EXPECTED_PARAM, argv[0]);
		}
	} else if (strcmp(argv[0], ARG_LONG_LOG_FILE) == 0) {
		if (remaining_args > 0)
		{
			return arg_found_log(argv[1]);
		} else {
			throw_err(ERR_INTERN, TEXT_ERROR_ARG_EXPECTED_PARAM, argv[0]);
		}
	} else if (strcmp(argv[0], ARG_LONG_HELP) == 0) {
		return arg_found_help();
	} else {
		throw_err(ERR_INTERN, TEXT_ERROR_ARG_UNKNOWN, argv[0]);
	}
}

void parse_args(int argc, char **argv)
{
	throw_err(ERR_INFO, TEXT_ARG_PARSING);

	if (!argv)
	{
		throw_err(ERR_INTERN, TEXT_ERROR_ARG_ARGV_NULL);
	}

	// This can absolutely be done better, just a placeholder
	for (int i = 1; i < argc; i++)
	{
		// Single char arg
		if (argv[i][1] == 0x00)
		{
			throw_err(ERR_INFO, TEXT_ERROR_ARG_SINGLECHAR, argv[i]);
			i += parse_single_char_arg(argv[i][0], &argv[i], argc - i - 1);
		} else {
			// Have a - in front of everty other argument
			if (argv[i][0] == '-')
			{
				if (argv[i][2] == 0x00)
				{
					throw_err(ERR_INFO, TEXT_ERROR_ARG_SINGLECHAR, argv[i]);
					i += parse_single_char_arg(argv[i][1], &argv[i], argc - i - 1);
				} else {
					throw_err(ERR_INFO, TEXT_ERROR_ARG_MULTICHAR, argv[i]);
					i += parse_multi_char_arg(&argv[i], argc - i - 1);
				}
			} else {
				throw_err(ERR_INTERN, TEXT_ERROR_ARG_UNKNOWN2, argv[i], argv[i - 1]);
			}
		}
	}
}

static int arg_found_help()
{
	print_usage();
	return 0;
}
static int arg_found_conf(char *filename)
{
	conf.conf_file.path = filename;
	return 1;
}
static int arg_found_log(char *filename)
{
	conf.logfile.path = filename;
	return 1;
}

