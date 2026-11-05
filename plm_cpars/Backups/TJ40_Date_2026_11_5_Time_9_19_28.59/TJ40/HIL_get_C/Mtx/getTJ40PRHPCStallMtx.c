

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ40PRHPCStallMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ40PRHPCStallMtx[8] = {6.79505e+00, 5.70520e+00, 5.00215e+00, 4.01452e+00, 3.17641e+00, 2.52046e+00, 1.87882e+00, 1.49158e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ40PRHPCStallMtx + i);
};
};