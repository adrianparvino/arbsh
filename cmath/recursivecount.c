#include <stdio.h>
#include <stdlib.h>
     
void f(int j)
{
	static void (*const ft[2])(int) = { f, exit };
	
     
	printf("%d\n", j);
	ft[j/1000](j + 1);
}
     
int main(int argc, char *argv[])
{
	f(1);
}
