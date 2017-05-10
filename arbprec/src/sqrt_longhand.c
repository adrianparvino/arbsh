#include <arbprec/arbprec.h>

/*

           2  3. 8
	  ___________
	\/ 5,69.00,00
           4
          ----
      4_3) 1,69
           1,29
           -----
       46_8) 40.00
             37.44

                      ...
*/


bigflt *arbprec_sqrt_longhand(bigflt *a, bigflt *c)
{
	/* not yet implemented, use the notes above to finish this */

	size_t i = 0;
	size_t j = 0;
	size_t k = 0;

        int *mir = arbprec_malloc(sizeof(int) * a->len);
        int *tmir = arbprec_malloc(sizeof(int) * a->len);
	int *and = arbprec_malloc(sizeof(int) * a->len);

	int set[2] = { 0, 0 };
	int iseven = 0;

	size_t total_len = a->float_pos;

	if ( total_len % 2 == 0 )
		iseven = 1;

	for (i = 0 ; i < total_len ; ++i)
	{
		
	}
	
	return c;
}

