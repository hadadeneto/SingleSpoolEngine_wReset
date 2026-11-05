

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300ARPRHPCStallMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300ARPRHPCStallMtx[8] = {4.34556e+00, 3.71637e+00, 3.31050e+00, 2.74032e+00, 2.25647e+00, 1.87778e+00, 1.50735e+00, 1.28380e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300ARPRHPCStallMtx + i);
};
};