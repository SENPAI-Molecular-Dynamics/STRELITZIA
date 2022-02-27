#ifndef NETWORK_H
#define NETWORK_H

#include <sys/socket.h>
#include <arpa/inet.h>
// #include <netinet/in.h>
// #include <netdb.h>

#include "defines.h"

/* Connects to an IPv4 address */
int connect_v4(int *errnum, char *ip_str, uint16_t port);
/* Connects to an IPv6 address */
int connect_v6(int *errnum, char *ip_str, uint16_t port);

/* Connects to a UNIX socket */
int connect_unix();

#endif // !NETWORK_H
