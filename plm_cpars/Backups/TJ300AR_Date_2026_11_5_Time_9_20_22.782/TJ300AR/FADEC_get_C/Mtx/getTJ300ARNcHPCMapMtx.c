

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300ARNcHPCMapMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300ARNcHPCMapMtx[8] = {2.44512e-01, 2.85838e-01, 3.27164e-01, 3.68490e-01, 4.09816e-01, 4.51142e-01, 4.75249e-01, 5.13131e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300ARNcHPCMapMtx + i);
};
};