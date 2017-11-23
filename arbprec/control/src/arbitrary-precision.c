#include <arbprec/arbprec.h>

void ccarb_free(fxdpnt *flt)
{
        if (flt->number)
                free(flt->number);
        free(flt);
}

void ccarb_init(fxdpnt *flt)
{
        flt->sign = '+';
        flt->len = flt->lp = 0;
}

int ccarb_highbase(int a)
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


void ccarb_print(fxdpnt *flt)
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
                putchar(ccarb_highbase((flt->number[i])));
        }
        putchar('\n');
        fflush(stdout);
}

void ccarb_error(char *message)
{
        fprintf(stderr, "%s\n", message);
        exit(1);
}

void *ccarb_malloc(size_t len)
{
        void *ret;
        if(!(ret = malloc(len)))
                ccarb_error("malloc failed\n");
        return ret;
}
fxdpnt *ccarb_alloc(size_t len)
{
        // Allocate the basic requirements of a arb `fxdpnt'
        fxdpnt *ret = ccarb_malloc(sizeof(fxdpnt));
        ret->number = ccarb_malloc(sizeof(ARBT) * len);
        ret->sign = '+';
        ret->lp = 0;
        ret->allocated = len;
        ret->len = 0;
        ret->chunk = 4; // set to 4 to force worst case tests, change to >255
        return ret;
}

void *ccarb_realloc(void *ptr, size_t len)
{
        void *ret;
        if(!(ret = realloc(ptr, len)))
                ccarb_error("realloc failed\n");
        return ret;
}

fxdpnt *ccarb_expand(fxdpnt *flt, size_t request)
{
        // Enlarge or create a fxdpnt
        if (flt == NULL){
                flt = ccarb_alloc(request); // do not use sizeof here, it's in arb_alloc
		flt->allocated = request;
        } else if (request > flt->allocated){
                flt->allocated = (request + flt->chunk);
                flt->number = ccarb_realloc(flt->number, flt->allocated * sizeof(ARBT));
        }
        return flt;
}

fxdpnt *ccarb_new_num (int length, int scale)
{
	fxdpnt *ret;
	ret = ccarb_malloc(sizeof(fxdpnt));
	ret->sign = '+';
	ret->lp = length;
	ret->rp = scale;
	ret->allocated = 0;
	ret->len = ret->lp + ret->rp;
	ret->number = ccarb_malloc((length+scale) * sizeof(ARBT));
	ret->chunk = 4;
	memset(ret->number, 0, (length+scale) * sizeof(ARBT));
	return ret;
}

void ccarb_free_num (fxdpnt *num)
{
	if (num == NULL)
		return;
	if ((num)->number)
		free ((num)->number);
	free (num);
	num = NULL;
}

fxdpnt *ccarb_str2fxdpnt(const char *str)
{
        // Convert a string to a arb `fxdpnt'
        size_t i = 0; 
        int flt_set = 0, sign_set = 0;

        fxdpnt *ret = ccarb_expand(NULL, 1);
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
                        ret = ccarb_expand(ret, ret->len + 1);
                        ret->number[ret->len++] = str[i] - '0';
                }
        }

        if (flt_set == 0) 
                ret->lp = ret->len;

        ret->rp = ret->len - ret->lp;


        return ret;
}
