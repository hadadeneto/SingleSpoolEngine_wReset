

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTF1200WcHPCStallMtx(floating *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TF1200WcHPCStallMtx[10] = {3.64907e+00, 3.38847e+00, 3.05956e+00, 2.63083e+00, 2.21074e+00, 1.81918e+00, 1.52274e+00, 1.27678e+00, 9.15704e-01, 6.59066e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200WcHPCStallMtx + i);
};
};