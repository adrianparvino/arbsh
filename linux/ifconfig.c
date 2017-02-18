#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <sys/socket.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netpacket/packet.h>
/*
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
*/
//#include <arpa/inet.h>


/* (Copyright) 2014, "ifconfig.c" C. Graff */


struct optn{
	int up;
	int tx;
	int arp;
	int mtu;
	int down; 
	int nmask;
	int bcast;
	int metric;
	int promisc; 
	int multicast; 
	char txstring[1000];
        char mtustring[1000];
	char bcaststring[1000];
	char nmaskstring[1000];
	char metricstring[1000];
}optn;


int show_ip(); 
void adrs(int); 
int flagsmodes(int);
int setip(char *, char *); 
void hwaddress(unsigned char *);
void bad_arg(char **, int, int, int);


int main(int argc, char *argv[])
{
	size_t len = 1000;
	int c = 1;
	int d = -1;
	int e = 0;
	char *arguments[len]; 

	optn.tx = 0;
	optn.up = 0;
	optn.mtu = 0;
	optn.arp = 0;
	optn.down = 0;
	optn.bcast = 0;
	optn.nmask = 0;
	optn.metric = 0;
	optn.promisc = 0;
	optn.multicast = 0;

	while ( c < argc )
	{ 


		if ( strcmp(argv[c], "up" ) == 0 )
			optn.up = 1;
		else if ( strcmp(argv[c], "down" ) == 0 )
                        optn.down = 1; 
		else if ( strcmp(argv[c], "down" ) == 0 )
                        optn.multicast = 1;
		else if ( strcmp(argv[c], "promisc" ) == 0 )
                        optn.promisc = 1;
		else if ( strcmp(argv[c], "-promisc" ) == 0 )
                        optn.promisc = 2;
		else if ( strcmp(argv[c], "-arp" ) == 0 )
                        optn.arp = 1;
		else if ( strcmp(argv[c], "arp" ) == 0 )
                        optn.arp = 2; 
		else if ( strcmp(argv[c], "multicast" ) == 0 )
                        optn.multicast = 1;
		
                   
		else if ( strcmp(argv[c], "mtu" ) == 0 )
		{ 
			bad_arg(arguments, c, d, argc);
			optn.mtu = 1; 
			strncpy (optn.mtustring, argv[++c], len); 
		}
		else if ( strcmp(argv[c], "metric" ) == 0 )
                {
                        bad_arg(arguments, c, d, argc);
                        optn.metric = 1;
                        strncpy (optn.metricstring, argv[++c], len);
                }
		else if ( strcmp(argv[c], "broadcast" ) == 0 )
		{ 
			bad_arg(arguments, c, d, argc);
			optn.bcast = 1; 
                        strncpy (optn.bcaststring, argv[++c], len); 
		}
		else if ( strcmp(argv[c], "netmask" ) == 0 )
                {
			bad_arg(arguments, c, d, argc);
                        optn.nmask = 1; 
                        strncpy (optn.nmaskstring, argv[++c], len); 
                }
		else if ( strcmp(argv[c], "txqueuelen" ) == 0 )
                {
			bad_arg(arguments, c, d, argc);
                        optn.tx = 1; 
                        strncpy (optn.txstring, argv[++c], len); 
                }
		else 	
		{ 
			arguments[++d] = malloc(len);
			memset(arguments[d], 0, len);
			strncpy (arguments[d], argv[c], len);
		}
		++c; 
	}
	
	while ( e < d + 1) 
		printf("%s\n", arguments[e++]); 

	if ( argc == 1 ) 
		show_ip(); 

	if ( d == 1 )
		setip(arguments[0], arguments[1]); 
	else if ( d == 0 )
		setip(arguments[0], NULL);
	
	e = 0;
	while ( e < d + 1)
                free(arguments[e++]);
	
	return 0;
}


int setip(char *iface_name, char *ip_addr)
{

	int sockfd = 0;
	struct ifreq ifr; 
	struct sockaddr_in sin;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
	strncpy(ifr.ifr_name, iface_name, IFNAMSIZ); 
	ioctl(sockfd, SIOCGIFFLAGS, &ifr);

	
	if ( optn.promisc == 1  ) 
		ifr.ifr_flags |= IFF_PROMISC; 
	if ( optn.promisc == 2  ) 
                ifr.ifr_flags &= ~IFF_PROMISC; 
	if ( optn.arp == 1 ) 
		ifr.ifr_flags |= IFF_NOARP; 
	if ( optn.arp == 2 ) 
                ifr.ifr_flags &= ~IFF_NOARP; 
	if ( optn.multicast == 1 ) 
                ifr.ifr_flags |= IFF_MULTICAST; 
	if ( optn.up == 1 ) 
		ifr.ifr_flags |= IFF_UP | IFF_RUNNING; 
	if ( optn.down == 1 ) 
		ifr.ifr_flags &= 0; 

	ioctl(sockfd, SIOCSIFFLAGS, &ifr);

	memset(&sin, 0, sizeof(struct sockaddr));
        sin.sin_family = AF_INET;
        sin.sin_port = 0;

	if ( ip_addr != NULL )
	{
		// int inet_aton(const char *cp, struct in_addr *inp);
		inet_aton(ip_addr, &sin.sin_addr.s_addr); 
		memcpy(&ifr.ifr_addr, &sin, sizeof(struct sockaddr));
		ioctl(sockfd, SIOCSIFADDR, &ifr);
	}
	if ( optn.bcast == 1 )
	{
		inet_aton(optn.bcaststring, &sin.sin_addr.s_addr); 
        	memcpy(&ifr.ifr_broadaddr, &sin, sizeof(struct sockaddr));
        	ioctl(sockfd, SIOCSIFBRDADDR, &ifr);
	}
	if ( optn.nmask == 1 )
        {
                inet_aton(optn.nmaskstring, &sin.sin_addr.s_addr); 
                memcpy(&ifr.ifr_netmask, &sin, sizeof(struct sockaddr));
                ioctl(sockfd, SIOCSIFNETMASK, &ifr);
        } 
       	if ( optn.mtu > 0 )
        { 
		ifr.ifr_mtu = atoi(optn.mtustring);
                ioctl(sockfd, SIOCSIFMTU, &ifr);
        }
	if ( optn.tx > 0 )
        { 
		ifr.ifr_qlen = atoi(optn.txstring);
                ioctl(sockfd, SIOCSIFTXQLEN, &ifr);
	}
	if ( optn.metric > 0 )
        {
                ifr.ifr_metric = atoi(optn.metricstring);
                ioctl(sockfd, SIOCSIFMETRIC, &ifr);
        }
	close(sockfd);
	return 0;
}


void bad_arg(char **arguments, int c, int d, int argcc)
{
	int e = 0;
	if ( c + 1 == argcc )
	{
		printf(" not enough args\n"); 
		while ( e < d + 1)
			free(arguments[e++]);
		exit (0);
	}
} 

int show_ip()
{
	struct ifmap;
	struct ifconf ifc;
	struct ifreq ifr[10]; 
//	struct ifreq *req;
//	struct ifreq ethreq;
	int sd, ifc_num, i; 

	sd = socket(PF_INET, SOCK_DGRAM, 0); 

	ifc.ifc_len = sizeof(ifr);
	ifc.ifc_ifcu.ifcu_buf = (caddr_t)ifr;

	ioctl(sd, SIOCGIFCONF, &ifc); 

	ifc_num = ifc.ifc_len / sizeof(struct ifreq); 

	for (i = 0; i < ifc_num ; ++i)
	{
		printf("%s", ifr[i].ifr_name); 

		ioctl(sd, SIOCGIFFLAGS, &ifr[i]); 
		flagsmodes(ifr[i].ifr_flags); 

		ioctl(sd, SIOCGIFADDR, &ifr[i]);
		printf("\taddr: \t"); 
		adrs(((struct sockaddr_in *)(&ifr[i].ifr_addr))->sin_addr.s_addr); 
	
		ioctl(sd, SIOCGIFBRDADDR, &ifr[i]);
		printf("\n\tBcast: \t");
		adrs(((struct sockaddr_in *)(&ifr[i].ifr_broadaddr))->sin_addr.s_addr);
	
		ioctl(sd, SIOCGIFNETMASK, &ifr[i]);
		printf("\n\tnmask: \t");
		adrs(((struct sockaddr_in *)(&ifr[i].ifr_netmask))->sin_addr.s_addr);

		ioctl(sd, SIOCGIFHWADDR, &ifr[i]);
		printf("\n\tHWaddr: \t");
		hwaddress((unsigned char *)ifr[i].ifr_hwaddr.sa_data);
	
		ioctl(sd, SIOCGIFMTU, &ifr[i]);
		printf ("\n\tMTU: %d", (ifr[i].ifr_mtu));

		ioctl(sd, SIOCGIFTXQLEN, &ifr[i]);
               	printf ("\n\ttxqueuelen: %d", (ifr[i].ifr_qlen));

               
		ioctl(sd, SIOCGIFMETRIC, &ifr[i]);
		if ( ifr[i].ifr_metric == 0 )
                	printf ("\n\tMetric: %d", 1); 
		else   	
			printf ("\n\tMetric: %d", ifr[i].ifr_metric );

		ioctl(sd, SIOCGIFMAP, &ifr[i]);
    		printf("\n\tmem= 0x%lx-", ifr[i].ifr_map.mem_start);
		printf("0x%lx  ", ifr[i].ifr_map.mem_end);
		printf("io= 0x%x  ", ifr[i].ifr_map.base_addr);
		printf("irq= %i  ", ifr[i].ifr_map.irq);
		printf("dma= %i  ", ifr[i].ifr_map.dma);
		printf("port= %i\n", ifr[i].ifr_map.port);
	
		printf("\n");
		printf("\n");
		
	}
	close(sd);
	return ifc_num;

}

void adrs(int b)
{
        printf("%d.%d.%d.%d ", b&0xFF,b>>8&0xFF,b>>16&0xFF,b>>24&0xFF);
}

void hwaddress(unsigned char *a)
{ 
        printf("%.2x:%.2x:%.2x:%.2x:%.2x:%.2x" , a[0], a[1], a[2], a[3], a[4], a[5]);
}

int flagsmodes(int f)
{
	printf("\n\t");
	if (f & IFF_UP) printf("UP "); 
	if (f & IFF_NOARP) printf("NOARP "); 
	if (f & IFF_SLAVE) printf("SLAVE ");
	if (f & IFF_MASTER) printf("MASTER ");
	if (f & IFF_PORTSEL) printf("PORTSEL ");
        if (f & IFF_DYNAMIC) printf("DYNAMIC "); 
	if (f & IFF_RUNNING) printf("RUNNING ");
	if (f & IFF_PROMISC) printf("PROMISC "); 
        if (f & IFF_LOOPBACK) printf("LOOPBACK "); 
        if (f & IFF_ALLMULTI) printf("ALLMULTI "); 
	if (f & IFF_BROADCAST) printf("BROADCAST ");
	if (f & IFF_MULTICAST) printf("MULTICAST ");
	if (f & IFF_AUTOMEDIA) printf("AUTOMEDIA ");
	if (f & IFF_NOTRAILERS) printf("NOTRAILERS ");
	if (f & IFF_POINTOPOINT) printf("POINTOPOINT "); 
	printf("\n");
	return 0;
}
