

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTF300PRHPCStallMtx(floating *Pointer)
{
int i;
int TotalElem = 12;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TF300PRHPCStallMtx[12] = {5.01169e+00, 4.66906e+00, 4.32642e+00, 3.98378e+00, 3.57280e+00, 3.07307e+00, 2.62291e+00, 2.23854e+00, 1.97013e+00, 1.76220e+00, 1.48123e+00, 1.29910e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF300PRHPCStallMtx + i);
};
};