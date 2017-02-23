int dialip(const char *server, unsigned short port)
{
	int sck;
        struct sockaddr_in servaddr;

        gmemset(&servaddr, 0, sizeof(servaddr));
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


int dialurl(const char *host, unsigned short port)
{
        int sck;
        struct sockaddr_in servaddr;
        struct addrinfo *res, hints = { 0 };

        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        if (getaddrinfo(host, 0, &hints, &res))
                return -1;
        gmemcpy(&servaddr, res->ai_addr, sizeof servaddr);
        servaddr.sin_port = htons(port);
        freeaddrinfo(res);
        if (!(sck = socket(AF_INET, SOCK_STREAM, 0)))
		return -1;
        if ((connect(sck, (struct sockaddr *)&servaddr, sizeof servaddr)) == -1 )
                return -1;
        return sck;
}


