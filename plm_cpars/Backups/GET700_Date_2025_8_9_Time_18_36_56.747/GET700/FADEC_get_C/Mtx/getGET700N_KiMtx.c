

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700N_KiMtx(floating *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700N_KiMtx[1] = {7.81506e-06};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700N_KiMtx + i);
};
};