#ifndef WORKER_PROTO_H
#define WORKER_PROTO_H

#include <unistd.h>
#include <string.h>

/* Macro to write a string to sockfd */
#define SENTP_WRITE_STR(sockfd, str) write(sockfd, (void *) str, strlen(str))
/* Write a \n */
#define SENTP_WRITE_NL(sockfd) SENTP_WRITE_STR(sockfd, "\n")
/* Write a \n terminated string to sockfd */
#define SENTP_WRITE_STRNL(sockfd, str) SENTP_WRITE_STR(sockfd, str); SENTP_WRITE_NL(sockfd)

#define SENTP_MAX_READ_SIZE 1024

#define SENTP_NAME	"SENTP"
#define SENTP_VERSION	"1.0"

#define SENTP_HEADER	SENTP_NAME " " SENTP_VERSION
#define SENTP_TRAILER	SENTP_NAME " END"

#define SENTP_TYPE_CONTROL	"CONTROL"
#define SENTP_TYPE_BINARY	"BINARY"
#define SENTP_TYPE_ERROR	"ERROR"

#define SENTP_CONTROL_INIT	"INIT"
#define SENTP_CONTROL_EXIT	"EXIT"
#define SENTP_CONTROL_HALT	"HALT"
#define SENTP_CONTROL_CONT	"CONT"

#define SENTP_BIN_DESC_UNIVERSE	"UNIVERSE"
#define SENTP_BIN_DESC_RESULTS	"RESULTS"
#define SENTP_BIN_DESC_CONFIG	"CONFIG"

/* Write the heading line and trailer */
#define SENTP_WRITE_HEADER(sockfd) SENTP_WRITE_STRNL(sockfd, SENTP_HEADER)
#define SENTP_WRITE_TRAILER(sockfd) SENTP_WRITE_STRNL(sockfd, SENTP_TRAILER)

/* Write a control sequence */
#define SENTP_WRITE_CTRL(sockfd, ctrl_str) SENTP_WRITE_HEADER(sockfd);\
	SENTP_WRITE_STRNL(sockfd, SENTP_TYPE_CONTROL);\
	SENTP_WRITE_NL(sockfd);\
	\
	SENTP_WRITE_STRNL(sockfd, ctrl_str);\
	\
	SENTP_WRITE_NL(sockfd);\
	SENTP_WRITE_TRAILER(sockfd);

/* Write a binary sequence from void *binary of length len with descriptor desc */
#define SENTP_WRITE_BIN(sockfd, desc, binary, len) SENTP_WRITE_HEADER(sockfd);\
	SENTP_WRITE_STRNL(sockfd, SENTP_TYPE_BINARY);\
	SENTP_WRITE_STRNL(sockfd, desc);\
	dprintf(sockfd, "%d\n", len);\
	SENTP_WRITE_NL(sockfd);\
	\
	write(sockfd, binary, len);\
	\
	SENTP_WRITE_NL(sockfd);\
	SENTP_WRITE_NL(sockfd);\
	SENTP_WRITE_TRAILER(sockfd);

#endif // !WORKER_PROTO_H
