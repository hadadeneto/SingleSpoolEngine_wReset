

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300ARPRHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300ARPRHPTMapMtx[21] = {1.26393e+00, 1.52787e+00, 1.59385e+00, 1.65983e+00, 1.72582e+00, 1.79180e+00, 1.85779e+00, 1.92377e+00, 1.98975e+00, 2.05574e+00, 2.12172e+00, 2.18770e+00, 2.25369e+00, 2.31967e+00, 2.38565e+00, 2.45164e+00, 2.51762e+00, 2.58360e+00, 2.64959e+00, 2.71557e+00, 2.84754e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300ARPRHPTMapMtx + i);
};
};