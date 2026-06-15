

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300ARFNcMaxContMtx(floating *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300ARFNcMaxContMtx[11] = {1.62309e+03, 1.54689e+03, 1.48421e+03, 1.43456e+03, 1.39689e+03, 1.36968e+03, 1.35113e+03, 1.33934e+03, 1.33326e+03, 1.32894e+03, 1.32769e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300ARFNcMaxContMtx + i);
};
};