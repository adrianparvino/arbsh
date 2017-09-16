#ifndef	_NETDB_H
#define	_NETDB_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _GNU_SOURCE
#define __NEED_size_t
#endif

#define __NEED_socklen_t
#define __NEED_uint32_t

#include <bits/alltypes.h>

struct addrinfo
{
	int ai_flags;
	int ai_family;
	int ai_socktype;
	int ai_protocol;
	socklen_t ai_addrlen;
	struct sockaddr *ai_addr;
	char *ai_canonname;
	struct addrinfo *ai_next;
};

#define IPPORT_RESERVED 1024

#define AI_PASSIVE      0x01
#define AI_CANONNAME    0x02
#define AI_NUMERICHOST  0x04
#define AI_V4MAPPED     0x08
#define AI_ALL          0x10
#define AI_ADDRCONFIG   0x20
#define AI_NUMERICSERV  0x400


#define NI_NUMERICHOST  0x01
#define NI_NUMERICSERV  0x02
#define NI_NOFQDN       0x04
#define NI_NAMEREQD     0x08
#define NI_DGRAM        0x10
/*#define NI_NUMERICSCOPE */

#define NI_MAXHOST 255
#define NI_MAXSERV 32

#define EAI_BADFLAGS   -1
#define EAI_NONAME     -2
#define EAI_AGAIN      -3
#define EAI_FAIL       -4
#define EAI_FAMILY     -6
#define EAI_SOCKTYPE   -7
#define EAI_SERVICE    -8
#define EAI_MEMORY     -10
#define EAI_SYSTEM     -11
#define EAI_OVERFLOW   -12

int getaddrinfo (const char *, const char *, const struct addrinfo *, struct addrinfo **);
void freeaddrinfo (struct addrinfo *);
int getnameinfo (const struct sockaddr *, socklen_t, char *, socklen_t, char *, socklen_t, int);
const char *gai_strerror(int);


/* Legacy functions follow (marked OBsolete in SUS) */

struct netent
{
	char *n_name;
	char **n_aliases;
	int n_addrtype;
	uint32_t n_net;
};

struct hostent
{
	char *h_name;
	char **h_aliases;
	int h_addrtype;
	int h_length;
	char **h_addr_list;
};
#define h_addr h_addr_list[0]

struct servent
{
	char *s_name;
	char **s_aliases;
	int s_port;
	char *s_proto;
};

struct protoent
{
	char *p_name;
	char **p_aliases;
	int p_proto;
};

extern int h_errno;

#define HOST_NOT_FOUND 1
#define TRY_AGAIN      2
#define NO_RECOVERY    3
#define NO_DATA        4

void sethostent (int);
void endhostent (void);
struct hostent *gethostent (void);
struct hostent *gethostbyaddr (const void *, socklen_t, int);
struct hostent *gethostbyname (const char *);

void setnetent (int);
void endnetent (void);
struct netent *getnetent (void);
struct netent *getnetbyaddr (uint32_t, int);
struct netent *getnetbyname (const char *);

void setservent (int);
void endservent (void);
struct servent *getservent (void);
struct servent *getservbyname (const char *, const char *);
struct servent *getservbyport (int, const char *);

void setprotoent (int);
void endprotoent (void);
struct protoent *getprotoent (void);
struct protoent *getprotobyname (const char *);
struct protoent *getprotobynumber (int);

#ifdef _GNU_SOURCE
const char *hstrerror(int);
int gethostbyname_r(const char *, struct hostent *, char *, size_t, struct hostent **, int *);
int gethostbyname2_r(const char *, int, struct hostent *, char *, size_t, struct hostent **, int *);
struct hostent *gethostbyname2(const char *, int);
int gethostbyaddr_r(const void *, socklen_t, int, struct hostent *, char *, size_t, struct hostent **, int *);
int getservbyport_r(int, const char *, struct servent *, char *, size_t, struct servent **);
int getservbyname_r(const char *, const char *, struct servent *, char *, size_t, struct servent **);
#endif


#ifdef __cplusplus
}
#endif

#endif
