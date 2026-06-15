

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200N_KpMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200N_KpMtx[1] = {7.84696e-07};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200N_KpMtx + i);
};
};