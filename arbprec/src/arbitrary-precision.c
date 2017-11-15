#include <arbprec.h>

void arb_free(fxdpnt *flt)
{
        if (flt->number)
                free(flt->number);
        free(flt);
}

void arb_printold(fxdpnt *flt)
{
        size_t i = 0;

        if (flt->sign == '-')
                putchar(flt->sign);
        for (i = 0; i < flt->len ; ++i){
                if (flt->lp == i)
                        putchar('.');
                putchar(arb_highbase((flt->number[i])));
        }
        putchar('\n');
        fflush(stdout);
}

fxdpnt *arb_add_precision(fxdpnt *flt, size_t more)
{
        // Increase the precision of an arb `fxdpnt'
        flt = arb_expand(flt, flt->len + more);
        memset(flt->number + flt->len, 0, more * sizeof(ARBT));
        flt->len += more;
        return flt;
}
size_t rr(fxdpnt *flt)
{
        /* Right hand radix position */
        return flt->len - flt->lp;
}

size_t rl(fxdpnt *flt)
{
        /* Left hand radix position */
        return flt->lp;
}


void arb_init(fxdpnt *flt)
{
        flt->sign = '+';
        flt->len = flt->lp = 0;
}

void arb_flipsign(fxdpnt *flt)
{
        if (flt->sign == '+')
                flt->sign = '-';
        else if (flt->sign == '-')
                flt->sign = '+';
}

void arb_setsign(fxdpnt *a, fxdpnt *b, fxdpnt *c)
{
        arb_init(c);
        if (a->sign == '-')
                arb_flipsign(c);
        if (b->sign == '-')
                arb_flipsign(c);
}

void verbose(char *msg)
{
	if (verbosity)
		fprintf(stderr, "%s\n", msg);
}

int arb_highbase(int a)
{
	// Handle high bases
        static int uglyphs[36] = { '0', '1', '2', '3', '4', '5', '6', '7', '8',
                                '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                                'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}; 
        if (a < 36) 
              	return uglyphs[a]; 
        else // just use the ascii values for bases that are very high
                return a;
}


void arb_print(fxdpnt *flt)
{
        size_t i = 0;
	size_t len = 0;
	flt->len = flt->lp + flt->rp;

	if (flt->len == 0)
		len = flt->lp + flt->rp;
	else
		len = flt->len;

        if (flt->sign == '-')
                putchar(flt->sign);
        for (i = 0; i < len ; ++i){
                if (flt->lp == i)
                        putchar('.');
                putchar(arb_highbase((flt->number[i])));
        }
        putchar('\n');
        fflush(stdout);
}

void arb_error(char *message)
{
        fprintf(stderr, "%s\n", message);
        exit(1);
}

void *arb_malloc(size_t len)
{
        void *ret;
        if(!(ret = malloc(len)))
                arb_error("malloc failed\n");
        return ret;
}
fxdpnt *arb_alloc(size_t len)
{
        // Allocate the basic requirements of a arb `fxdpnt'
        fxdpnt *ret = arb_malloc(sizeof(fxdpnt));
        ret->number = arb_malloc(sizeof(int) * len);
        ret->sign = '+';
        ret->lp = 0;
        ret->allocated = len;
        ret->len = 0;
        ret->chunk = 4; // set to 4 to force worst case tests, change to >255
        return ret;
}

void *arb_realloc(void *ptr, size_t len)
{
        void *ret;
        if(!(ret = realloc(ptr, len)))
                arb_error("realloc failed\n");
        return ret;
}

fxdpnt *arb_expand(fxdpnt *flt, size_t request)
{
        // Enlarge or create a fxdpnt
        if (flt == NULL){
                flt = arb_alloc(request);
		flt->allocated = request;
        } else if (request > flt->allocated){
                flt->allocated = (request + flt->chunk);
                flt->number = arb_realloc(flt->number, flt->allocated * sizeof(ARBT));
        }
        return flt;
}

fxdpnt *arb_new_num (int length, int scale)
{
	fxdpnt *ret;
	ret = arb_malloc(sizeof(fxdpnt));
	ret->sign = '+';
	ret->lp = length;
	ret->rp = scale;
	ret->allocated = 0;
	ret->len = ret->lp + ret->rp;
	ret->number = arb_malloc(length+scale);
	ret->chunk = 4;
	memset(ret->number, 0, length+scale);
	return ret;
}

void arb_free_num (fxdpnt *num)
{
	if (num == NULL)
		return;
	if ((num)->number)
		free ((num)->number);
	free (num);
	num = NULL;
}

fxdpnt *arb_str2fxdpnt(const char *str)
{
        // Convert a string to a arb `fxdpnt'
        size_t i = 0; 
        int flt_set = 0, sign_set = 0;

        fxdpnt *ret = arb_expand(NULL, 1);
	ret->len =0;
	ret->lp =0;
	ret->rp =0;

        for (i = 0; str[i] != '\0'; ++i){
                if (str[i] == '.'){
                        flt_set = 1;
                        ret->lp = i - sign_set;
                }
                else if (str[i] == '+'){
                        sign_set = 1;
                        ret->sign = '+';
                }
                else if (str[i] == '-'){
                        sign_set = 1;
                        ret->sign = '-';
                }
                else{
                        ret = arb_expand(ret, ret->len + 1);
                        ret->number[ret->len++] = str[i] - '0';
                }
        }

        if (flt_set == 0) 
                ret->lp = ret->len;

        ret->rp = ret->len - ret->lp;


        return ret;
}

