

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700Tt4_KiMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700Tt4_KiMtx[1] = {6.49846e-04};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700Tt4_KiMtx + i);
};
};