/*

	"Floating-point arithmetic is a systematic approximation of real 
	arithmetic, [...] Floating-point arithmetic can only represent a 
	finite subset of the continuum of real numbers.Consequently, certain 
	properties of real arithmetic, such as associativity of addition, do 
	not always hold for floating-point arithmetic" (IEEE-754-2008 3.2)

	"Unlike in a binary floating-point format, in a decimal floating-point
	format a number might have multiple representations. The set of 
	representations a floating-point number maps to is called the 
	floating-point number’s cohort" (IEEE-754-2008 3.5.1)
; 
*/

void printBits(size_t const size, void const * const ptr)
{
	unsigned char *b = (unsigned char*) ptr;
	unsigned char byte;
	int i, j;

	for (i=size-1;i>=0;i--)
	{
		for (j=7;j>=0;j--)
		{
			byte = (b[i] >> j) & 1;
			printf("%u", byte);
		}
	}
	puts("");
}
