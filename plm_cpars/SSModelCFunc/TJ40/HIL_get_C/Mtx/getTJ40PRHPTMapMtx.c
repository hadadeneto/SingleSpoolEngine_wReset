

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ40PRHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ40PRHPTMapMtx[21] = {1.19813e+00, 1.39627e+00, 1.44580e+00, 1.49534e+00, 1.54487e+00, 1.59440e+00, 1.64394e+00, 1.69347e+00, 1.74300e+00, 1.79254e+00, 1.84207e+00, 1.89160e+00, 1.94114e+00, 1.99067e+00, 2.04020e+00, 2.08974e+00, 2.13927e+00, 2.18880e+00, 2.23834e+00, 2.28787e+00, 2.38694e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ40PRHPTMapMtx + i);
};
};