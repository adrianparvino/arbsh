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
	//size_t j = 0;
	//int set[2] = { 0, 0 };
	
	//int iseven = 0;
	size_t total_len = a->float_pos;


	//if (total_len % 2 == 0)
	//	iseven = 1;

	//if (!(iseven))
	//	set[0] = a->number[0];

	for (i = 0;i < total_len; ++i)
	{
		
		//if (i % 2 == 0)
		//	set[0] = a->number[i];
		//	printf("%d\n", i); 
		
	
		
		
	}
	
	return c;
}

