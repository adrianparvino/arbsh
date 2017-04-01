#include <gunistd.h>

void gswab(void *from, void *to, ssize_t n) {
	char *fromm = from;
	char *too = to;
	for (int i = 0; i < n; i += 2) {
		char tmp = *(fromm + i);
		char tmpp = *(fromm + i + 1);
		*(too + i) = tmpp;
		*(too + i + 1) = tmp;
	}
}
