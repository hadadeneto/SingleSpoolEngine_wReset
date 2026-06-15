

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700PRHPCStallMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700PRHPCStallMtx[8] = {1.08214e+01, 8.97436e+00, 7.78284e+00, 6.10900e+00, 4.68858e+00, 3.57688e+00, 2.48942e+00, 1.83313e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700PRHPCStallMtx + i);
};
};