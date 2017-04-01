#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_OF(type) \
    (((type)(~0LLU) > (type)((1LLU<<((sizeof(type)<<3)-1))-1LLU)) ? (long long unsigned int)(type)(~0LLU) : (long long unsigned int)(type)((1LLU<<((sizeof(type)<<3)-1))-1LLU))
#define MIN_OF(type) \
    (((type)(1LLU<<((sizeof(type)<<3)-1)) < (type)1) ? (long long int)((~0LLU)-((1LLU<<((sizeof(type)<<3)-1))-1LLU)) : 0LL)

int main(int argc, char *argv[])
{
	argc = argc;
	//char *p = "MY_";
	char *p = "";
	printf("/* constants */\n");
	printf("#define CHAR_BITS    8\n\n");

	printf("/* Gnerated automatically by %s: */\n", argv[0]);

	printf("#define %sSIZE_MAX     (%lluUL)\n", p, MAX_OF(size_t)); 
	printf("#define %sSIZE_MIN     %lld\n", p, MIN_OF(size_t)); 
	printf("#define %sSSIZE_MAX    %llu\n", p, MAX_OF(ssize_t));
	printf("#define %sSSIZE_MIN    %lld\n", p, MIN_OF(ssize_t)); 
	printf("#define %sUCHAR_MAX    %llu\n", p, MAX_OF(unsigned char));
	printf("#define %sUCHAR_MIN    %lld\n", p, MIN_OF(unsigned char)); 
	printf("#define %sCHAR_MAX     %llu\n", p, MAX_OF(char));
	printf("#define %sCHAR_MIN     %lld\n", p, MIN_OF(char)); 
	printf("#define %sINT_MAX      %llu\n", p, MAX_OF(int));
	printf("#define %sINT_MIN      %lld\n", p, MIN_OF(int)); 
	printf("#define %sLONG_MAX     %llu\n", p, MAX_OF(long));
	printf("#define %sLONG_MIN     %lld\n", p, MIN_OF(long)); 
	printf("#define %sLLONG_MAX    %llu\n", p, MAX_OF(long long));
	printf("#define %sLLONG_MIN    %lld\n", p, MIN_OF(long long));

	
	return 0;
}
