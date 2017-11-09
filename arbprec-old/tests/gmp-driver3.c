#include <stdio.h>
#include <gmp.h>

int main(void)
{
    mpf_t f;
    mpf_init_set_str(f, "312312314.11231231231231235926", 10);
    gmp_printf("%.5Ff\n", f);
    return 0;
}
