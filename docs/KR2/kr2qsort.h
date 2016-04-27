/* kr2qsort: sort v[left]...v[right] into increasing order */
//#include "swap.h"
void qswap(void *v[], int, int);
void kr2qsort(void *v[], int left, int right,
           int (*comp)(void *, void *))
{
    int i, last;
    
    if (left >= right)    /* do nothing if array contains */
        return;           /* fewer than two elements */
    qswap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++)
        if ((*comp)(v[i], v[left]) < 0)
            qswap(v, ++last, i);
    qswap(v, left, last);
    kr2qsort(v, left, last-1, comp);
    kr2qsort(v, last+1, right, comp);
}
/* swap: interchange v[i] and v[j] */
void qswap(int *v[], int i, int j)
{
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

