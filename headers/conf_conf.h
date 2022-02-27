#ifndef CONF_CONF_H
#define CONF_CONF_H

#define CONF_TYPE_CHAR	1	// char
#define CONF_TYPE_STR	2	// char*
#define CONF_TYPE_U16	3	// uint16_t
#define CONF_TYPE_S16	4	// int16_t
#define CONF_TYPE_U32	5	// uint32_t
#define CONF_TYPE_S32	6	// int32_t
#define CONF_TYPE_U64	7	// uint64_t
#define CONF_TYPE_S64	8	// int64_t

/* logfile <filename:str> */
#define CONF_LOGFILE_ID		1
#define CONF_LOGFILE_VALNUM	1
#define CONF_LOGFILE_PARAM	"logfile"
#define CONF_LOGFILE_VALTYPES	{CONF_TYPE_STR}

/* worker <name:str> <type:char> <ip:str> <port:unsigned short> */
#define CONF_WORKER_ID		2
#define CONF_WORKER_VALNUM	4
#define CONF_WORKER_PARAM	"worker"
#define CONF_WORKER_VALTYPES	{CONF_TYPE_STR, \
				CONF_TYPE_CHAR, \
				CONF_TYPE_STR,	\
				CONF_TYPE_U16	}

#endif // !CONF_CONF_H
