#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>
#define MAX_OF(type) \
    (((type)(~0LLU) > (type)((1LLU<<((sizeof(type)<<3)-1))-1LLU)) ? (long long unsigned int)(type)(~0LLU) : (long long unsigned int)(type)((1LLU<<((sizeof(type)<<3)-1))-1LLU))
#define MIN_OF(type) \
    (((type)(1LLU<<((sizeof(type)<<3)-1)) < (type)1) ? (long long int)((~0LLU)-((1LLU<<((sizeof(type)<<3)-1))-1LLU)) : 0LL)

int main(void)
{


	printf("SIZE_MAX      %llu\n", MAX_OF(size_t));
	printf("SIZE_MIN      %lld\n", MIN_OF(size_t));
    
	printf("SSIZE_MAX     %llu\n", MIN_OF(ssize_t));
	printf("SSIZE_MIN     %lld\n", MIN_OF(ssize_t));

	
	//printf("uint32_t = %lld..%llu\n", MIN_OF(uint32_t), MAX_OF(uint32_t));
	//printf("int32_t = %lld..%llu\n", MIN_OF(int32_t), MAX_OF(int32_t));
	//printf("uint64_t = %lld..%llu\n", MIN_OF(uint64_t), MAX_OF(uint64_t));
	//printf("int64_t = %lld..%llu\n", MIN_OF(int64_t), MAX_OF(int64_t));
	//printf("pid_t = %lld..%llu\n", MIN_OF(pid_t), MAX_OF(pid_t));
	//printf("time_t = %lld..%llu\n", MIN_OF(time_t), MAX_OF(time_t));
	//printf("intptr_t = %lld..%llu\n", MIN_OF(intptr_t), MAX_OF(intptr_t));
	//printf("unsigned char = %lld..%llu\n", MIN_OF(unsigned char), MAX_OF(unsigned char));
	//printf("char = %lld..%llu\n", MIN_OF(char), MAX_OF(char));
	//printf("uint8_t = %lld..%llu\n", MIN_OF(uint8_t), MAX_OF(uint8_t));
	//printf("int8_t = %lld..%llu\n", MIN_OF(int8_t), MAX_OF(int8_t));
	//printf("uint16_t = %lld..%llu\n", MIN_OF(uint16_t), MAX_OF(uint16_t));
	//printf("int16_t = %lld..%llu\n", MIN_OF(int16_t), MAX_OF(int16_t));
	//printf("off_t = %lld..%llu\n", MIN_OF(off_t), MAX_OF(off_t));

	printf("UCHAR_MAX     %llu\n", MAX_OF(unsigned char));
	printf("UCHAR_MIN     %lld\n", MIN_OF(unsigned char));
	

	
	
	printf("CHAR_MAX      %llu\n", MAX_OF(char));
	printf("CHAR_MIN      %lld\n", MIN_OF(char));

	printf("INT_MAX       %llu\n", MAX_OF(int));
	printf("INT_MIN       %lld\n", MIN_OF(int));
	
	printf("LONG_MAX      %llu\n", MAX_OF(long));
	printf("LONG_MIN      %lld\n", MIN_OF(long));
	
	printf("LLONG_MAX     %llu\n", MAX_OF(long long));
	printf("LLONG_MIN     %lld\n", MIN_OF(long long));

	
	return 0;
}
