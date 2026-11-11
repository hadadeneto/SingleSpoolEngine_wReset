

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700N_KpMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700N_KpMtx[1] = {2.81943e-06};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700N_KpMtx + i);
};
};