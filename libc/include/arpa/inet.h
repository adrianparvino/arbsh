#ifndef _ARPA_INET_H
#define	_ARPA_INET_H

#ifdef __cplusplus
extern "C" {
#endif

#include <netinet/in.h>
#include <inttypes.h>

#define __NEED_socklen_t
#define __NEED_in_addr_t
#define __NEED_in_port_t
#define __NEED_uint16_t
#define __NEED_uint32_t
#define __NEED_struct_in_addr

#include <bits/alltypes.h>

uint32_t htonl(uint32_t);
uint16_t htons(uint16_t);
uint32_t ntohl(uint32_t);
uint16_t ntohs(uint16_t);

in_addr_t inet_addr (const char *);
char *inet_ntoa (struct in_addr);
int inet_pton (int, const char *, void *);
const char *inet_ntop (int, const void *, char *, socklen_t);

int inet_aton (const char *, struct in_addr *); /* nonstandard but widely used */

#undef INET_ADDRSTRLEN
#undef INET6_ADDRSTRLEN
#define INET_ADDRSTRLEN  16
#define INET6_ADDRSTRLEN 46

#ifdef __cplusplus
}
#endif

#endif
