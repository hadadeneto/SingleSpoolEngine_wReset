

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ1200WcHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200WcHPCStallMtx[10] = {7.39013e+00, 6.86237e+00, 6.19625e+00, 5.32798e+00, 4.47720e+00, 3.68421e+00, 3.08387e+00, 2.58575e+00, 1.85449e+00, 1.33475e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200WcHPCStallMtx + i);
};
};