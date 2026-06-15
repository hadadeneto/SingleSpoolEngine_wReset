

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ40FNcMaxContMtx(floating *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ40FNcMaxContMtx[11] = {5.06500e+02, 4.82427e+02, 4.63321e+02, 4.48975e+02, 4.38965e+02, 4.32688e+02, 4.29471e+02, 4.28595e+02, 4.29634e+02, 4.31179e+02, 4.32310e+02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ40FNcMaxContMtx + i);
};
};