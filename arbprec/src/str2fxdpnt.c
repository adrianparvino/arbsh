#include <arbprec/arbprec.h>

fxdpnt *arb_str2fxdpnt(const char *str)
{
	// Convert a string to an arb `fxdpnt'
	// This only works with base 10 because of the ascii "-'0'"
	// To make it work with any base then a function that is the opposite of
	// src/arb_highbase must be contrived
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

