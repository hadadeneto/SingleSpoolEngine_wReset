

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTF1200RPMshMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TF1200RPMshMtx[1] = {0.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200RPMshMtx + i);
};
};