#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include "../../clib/string.h"
#include "../../clib/alloc.h"
//#include "alloc.h"

int main(void)
{
	char *some = gmalloc(100 * sizeof(char));
	return 0;
}


