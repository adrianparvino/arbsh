#ifndef ARBPREC_FXDPNT_H
#define ARBPREC_FXDPNT_H

/* defines */
#define ARBT char	// designed to be any type
#define MAX(a,b)      ((a)>(b)?(a):(b))
#define MIN(a,b)      ((a)>(b)?(b):(a))

/* structures */
struct fxdpnt {	// fxdpnt fixed point type
	ARBT *number;	// The actual number
	char sign;	// Sign
	size_t lp;	// Length left of radix
	size_t rp;	// Length right of radix
	size_t len;	// Length of number (count of digits / limbs)
	size_t allocated;// Length of allocated memory
	size_t scale;
};

#endif
