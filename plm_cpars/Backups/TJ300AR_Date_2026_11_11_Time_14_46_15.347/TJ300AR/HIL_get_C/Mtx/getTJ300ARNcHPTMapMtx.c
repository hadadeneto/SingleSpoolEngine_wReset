

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300ARNcHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300ARNcHPTMapMtx[7] = {2.99102e-01, 3.48952e-01, 3.98802e-01, 4.48652e-01, 4.98503e-01, 5.48353e-01, 9.97005e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300ARNcHPTMapMtx + i);
};
};