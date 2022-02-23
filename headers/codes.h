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
#define FLAG_PLACEHOLDER6 0x20
#define FLAG_PLACEHOLDER7 0x40
#define FLAG_PLACEHOLDER8 0x80

#endif // !CODES_H
