

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTF300NcHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TF300NcHPTMapMtx[7] = {3.03872e-01, 3.54517e-01, 4.05162e-01, 4.55807e-01, 5.06453e-01, 5.57098e-01, 1.01291e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF300NcHPTMapMtx + i);
};
};