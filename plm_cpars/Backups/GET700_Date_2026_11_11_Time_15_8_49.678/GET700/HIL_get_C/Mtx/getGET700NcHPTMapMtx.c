

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700NcHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700NcHPTMapMtx[7] = {2.77650e-01, 3.23924e-01, 3.70199e-01, 4.16474e-01, 4.62749e-01, 5.09024e-01, 9.25498e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700NcHPTMapMtx + i);
};
};