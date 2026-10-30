

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTF300FNcMaxContMtx(floating *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TF300FNcMaxContMtx[11] = {1.86296e+03, 1.75055e+03, 1.65925e+03, 1.58840e+03, 1.53603e+03, 1.49975e+03, 1.47670e+03, 1.41996e+03, 1.41587e+03, 1.41377e+03, 1.41412e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF300FNcMaxContMtx + i);
};
};