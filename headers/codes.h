#ifndef CODES_H
#define CODES_H

/* Exit codes towards COFFIN */
// Like HTTP response codes (will eventually be replaced by them)
//#define COF_EX_SUCC 200
#define COF_EX_SUCC 0
#define COF_EX_FAIL 501

/* Exit codes from workers */
#define WORKER_EXIT_SUCCESS 0
#define WORKER_EXIT_FAILURE 1

/* Error codes */
#define ERR_CONFIG	-3	// Config file error
#define ERR_INTERN	-2	// For when it's the interns fault /j (strelitzia internal errors)
#define ERR_FATAL	-1	// General fatal error
#define ERR_UNSPEC	 0	// Unspecified error, fatal
#define ERR_HEAVY_WARN	 1	// Something is bad, but not enough to be fatal
#define ERR_WARN	 2	// A warning. Wow.
#define ERR_INFO	 3	// Simply information

/* Global flags */
#define FLAG_ABORTING 0x01	// When the system is aborting don't log errors, simply skip
#define FLAG_PLACEHOLDER1 0x02
#define FLAG_PLACEHOLDER2 0x04
#define FLAG_PLACEHOLDER3 0x08
#define FLAG_PLACEHOLDER4 0x10
#define FLAG_PLACEHOLDER5 0x20
#define FLAG_PLACEHOLDER6 0x40
#define FLAG_PLACEHOLDER7 0x80

/* Worker state flags as set by worker */
#define WFLAG_ALIVE	0x01	// Worker is alive
#define WFLAG_HALTING	0x02	// Worker is not ready
#define WFLAG_WAITING	0x04	// Worker is ready to receive work
#define WFLAG_WORKING	0x08	// Worker is currently working

#define WFLAG_TIMEOUT	0x20	// Worker has timed out (self report)
#define WFLAG_CONNECTED 0x40	// Connection to worker node established

#define WFLAG_INTERRUPT 0x80	// Worker has important information for the manager

/* Worker state flags as set by manager */
#define MFLAG_HALT	0x01	// Halt all processing
#define MFLAG_DISCONN	0x02	// Disconnect from worker node
#define MFLAG_EXIT	0x04	// Exit

#define MFLAG_TIMEOUT	0x10	// For keeping track of timed out workers

#define MFLAG_IS_IP6	0x80	// 0 => IPv4, 1 => IPv6

/* Worker error numbers */
#define WERRNO_CONN_FAIL	1	// Failed to connect to worker

/* Parameters */
#define ARG_LONG_CONF_FILE "--conf"
#define ARG_LONG_LOG_FILE "--log"
#define ARG_LONG_HELP "--help"

#define ARG_SHORT_CONF_FILE 'c'
#define ARG_SHORT_LOG_FILE 'l'
#define ARG_SHORT_HELP 'h'

/* Names and reference ids of the config file parameters */
#define CONF_LOG_ID 1
#define CONF_LOG_PARAM "logfile"

#define CONF_WORKER_ID 2
#define CONF_WORKER_PARAM "worker"

#endif // !CODES_H
