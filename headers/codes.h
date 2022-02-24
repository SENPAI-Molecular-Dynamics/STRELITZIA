#ifndef CODES_H
#define CODES_H

/* Exit codes towards COFFIN */
// Like HTTP response codes (will eventually be replaced by them)
//#define COF_EX_SUCC 200
#define COF_EX_SUCC 0
#define COF_EX_FAIL 501

/* Exit codes from workers */
#define WOR_EX_SUCC 0
#define WOR_EX_FAIL 1

/* Error codes */
#define ERR_INTERN -2		// For when it's the interns fault /j (strelitzia internal errors)
#define ERR_FATAL -1		// General fatal error
#define ERR_UNSPEC 0		// Unspecified error, fatal
#define ERR_HEAVY_WARN 1	// Something is bad, but not enough to be fatal
#define ERR_WARN 2		// A warning. Wow.
#define ERR_INFO 3		// Simply information

/* Global flags */
#define FLAG_ABORTING 0x01	// When the system is aborting don't log errors, simply skip
#define FLAG_PLACEHOLDER1 0x02
#define FLAG_PLACEHOLDER2 0x04
#define FLAG_PLACEHOLDER3 0x08
#define FLAG_PLACEHOLDER4 0x10
#define FLAG_PLACEHOLDER5 0x20
#define FLAG_PLACEHOLDER6 0x40
#define FLAG_PLACEHOLDER7 0x80

/* Worker state flags */
#define WFLAG_UNFINISHED 0x01	// Worker is not fully functioning yet
#define WFLAG_READY	 0x02	// Worker is ready to receive work
#define WFLAG_WORKING	 0x04	// Worker is currently working
#define WFLAG_TIMEOUT	 0x08	// Worker has timed out
#define WFLAG_CRASH	 0x10	// We have received confirmation of the worker crashing
#define WFLAG_PLACEHOLDER5 0x20
#define WFLAG_PLACEHOLDER6 0x40
#define WFLAG_PLACEHOLDER7 0x80


/* Parameters */
#define ARG_LONG_CONF_FILE "--conf"
#define ARG_LONG_LOG_FILE "--log"
#define ARG_LONG_HELP "--help"

#define ARG_SHORT_CONF_FILE 'c'
#define ARG_SHORT_LOG_FILE 'l'
#define ARG_SHORT_HELP 'h'

/* Usage text (see utils.c print_usage()) */
#define USAGE_STRING "\
c / -c / --config	[file]	specify config file\n\
l / -l / --log		[file]	specify log file\n\
h / -h / --help			show this usage\n"

/* Names and reference ids of the config file parameters */
#define CONF_LOG_ID 1
#define CONF_LOG_PARAM "logfile"

#define CONF_WORKER_IP4_ID 2
#define CONF_WORKER_IP4_PARAM "worker_ipv4"

#define CONF_WORKER_IP6_ID 3
#define CONF_WORKER_IP6_PARAM "worker_ipv6"

#endif // !CODES_H
