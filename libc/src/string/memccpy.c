#include <string.h>

void *memcppy(void *dest, const void *src, int c, size_t n) {
	char *source = src;
	char *destination = dest;
	int i;
	for (i = 0; i < n; ++i) {
		if (source[i] != c)
			destination[i] = source[i];
		else
			break;
	}
	if (n == ++i)
		return NULL;
	else
		return destination + i;
}