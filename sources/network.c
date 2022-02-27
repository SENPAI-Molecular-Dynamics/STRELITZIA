#include "network.h"
#include "defines.h"

/* Connects to an IPv4 address */
int connect_v4(int *errnum, char *ip_str, uint16_t port)
{
	/* Open an IPv4 TCP socket */
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		*errnum = WERRNO_SOCK_OPEN_FAIL;
		return -1;
	}

	/* Set up the server address */
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = inet_addr(ip_str);

	/* Make the connection */
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		*errnum = WERRNO_CONN_FAIL;
		return -1;
	}

	return sockfd;
}

/* Connects to an IPv6 address */
int connect_v6(int *errnum, char *ip_str, uint16_t port)
{
	/* Open an IPv6 TCP socket */
	int sockfd = socket(AF_INET6, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		*errnum = WERRNO_SOCK_OPEN_FAIL;
		return -1;
	}

	/* Set up the server address */
	struct sockaddr_in6 serv_addr;
	serv_addr.sin6_family = AF_INET6;
	serv_addr.sin6_port = htons(port);
	if (inet_pton(AF_INET6, ip_str, (void *) &serv_addr.sin6_addr) != 1)
	{
		*errnum = WERRNO_ADDR_INVALID;
		return -1;
	}

	/* Make the connection */
	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		*errnum = WERRNO_CONN_FAIL;
		return -1;
	}

	return sockfd;
}

