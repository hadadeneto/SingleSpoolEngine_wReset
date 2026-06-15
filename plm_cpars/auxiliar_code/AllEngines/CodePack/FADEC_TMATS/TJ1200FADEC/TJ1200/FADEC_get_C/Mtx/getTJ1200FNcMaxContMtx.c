

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ1200FNcMaxContMtx(floating *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ1200FNcMaxContMtx[11] = {4.99348e+03, 4.76509e+03, 4.57956e+03, 4.43522e+03, 4.32862e+03, 4.25493e+03, 4.20851e+03, 4.18334e+03, 4.17559e+03, 4.17230e+03, 4.17379e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200FNcMaxContMtx + i);
};
};