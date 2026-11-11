

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Tt5Mtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Tt5Mtx[1] = {1.11668e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Tt5Mtx + i);
};
};