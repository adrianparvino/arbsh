int dialipaddr(const char *server, unsigned short port)
{
	int sck;
        struct sockaddr_in servaddr;

        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
        if (!(sck = socket(AF_INET, SOCK_STREAM, 0))) 
                return -1; 
        if (inet_pton(AF_INET, server, &servaddr.sin_addr) != 1) 
		return -1; 
        if ((connect(sck, (struct sockaddr*)&servaddr, sizeof(servaddr)) ) == -1) 
		return -1; 
        return sck;
}



static int dial(const char *host, unsigned short port)
{
        int sck;
        struct sockaddr_in sin;
        struct addrinfo *ai, hai = { 0 };

        hai.ai_family = AF_INET;
        hai.ai_socktype = SOCK_STREAM;
        if (getaddrinfo(host, 0, &hai, &ai))
                return -1;
        memcpy(&sin, ai->ai_addr, sizeof sin);
        sin.sin_port = htons(port);
        freeaddrinfo(ai);
        if (!(sck = socket(AF_INET, SOCK_STREAM, 0)))
		return -1;
        if ((connect(sck, (struct sockaddr *)&sin, sizeof sin)) == -1 )
                return -1;
        return sck;
}



int httpdial(char *host, char *type)
{
        int sck; 
	struct addrinfo hints, *res; 
        memset(&hints, 0, sizeof(hints)); 
        hints.ai_family = PF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM; 
        if ((getaddrinfo(host, type, &hints, &res)) != 0 )
               return -1;
        if ((sck = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1)
               return -1; 
        if ((connect(sck, res->ai_addr, res->ai_addrlen) ) == -1 )
               return -1; 
	freeaddrinfo(res);
	return sck; 
}

