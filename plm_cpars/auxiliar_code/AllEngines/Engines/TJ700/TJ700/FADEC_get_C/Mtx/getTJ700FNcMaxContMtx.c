

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ700FNcMaxContMtx(floating *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ700FNcMaxContMtx[11] = {4.77632e+03, 4.56829e+03, 4.39542e+03, 4.25654e+03, 4.14895e+03, 4.06890e+03, 4.01187e+03, 3.97305e+03, 3.94932e+03, 3.93016e+03, 3.92347e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ700FNcMaxContMtx + i);
};
};