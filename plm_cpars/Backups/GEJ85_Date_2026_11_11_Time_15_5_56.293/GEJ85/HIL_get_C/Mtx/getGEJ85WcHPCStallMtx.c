

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGEJ85WcHPCStallMtx(floating *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GEJ85WcHPCStallMtx[7] = {2.13428e+01, 1.96459e+01, 1.61003e+01, 1.26192e+01, 1.03468e+01, 8.34832e+00, 6.54327e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85WcHPCStallMtx + i);
};
};