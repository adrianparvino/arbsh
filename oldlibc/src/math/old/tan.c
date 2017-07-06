#include <gmath.h>

/* not working! falls back to trig identity */

double gtan(double x)
{
        /* x = x + x^3/3 + 2x^5/15 + 17x^7/315 + ...  */
        /* double factorials */
        /* x + 2x^3/3! + 16x^5/5! + 272 x^7/7! */
        /* tan(x) = x + ((1/3) * (x^3)) + ((2/15) * (x^5)) + ((17/315) * (x^7)) + ((62/2835) * (x^9)) + ...     */

        /* tan(x) = x + 2 x^3/3! + 16 x^5/5! + 272 x^7/7! */

	/* not working! fall back to trig identity */
        return (gsin(2*x) / (gcos(2*x) + 1));

}


