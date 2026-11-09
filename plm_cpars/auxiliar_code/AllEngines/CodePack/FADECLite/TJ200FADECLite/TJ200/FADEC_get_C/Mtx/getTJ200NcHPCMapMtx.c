

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ200NcHPCMapMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ200NcHPCMapMtx[8] = {5.18816e-01, 6.06503e-01, 6.94191e-01, 7.81878e-01, 8.69565e-01, 9.57252e-01, 1.00840e+00, 1.08878e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200NcHPCMapMtx + i);
};
};