

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200PRHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200PRHPTMapMtx[21] = {1.43310e+00, 1.86621e+00, 1.97448e+00, 2.08276e+00, 2.19103e+00, 2.29931e+00, 2.40758e+00, 2.51586e+00, 2.62414e+00, 2.73241e+00, 2.84069e+00, 2.94896e+00, 3.05724e+00, 3.16552e+00, 3.27379e+00, 3.38207e+00, 3.49034e+00, 3.59862e+00, 3.70689e+00, 3.81517e+00, 4.03172e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200PRHPTMapMtx + i);
};
};