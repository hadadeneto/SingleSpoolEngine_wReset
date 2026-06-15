

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300RPRHPTMapMtx(floating *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300RPRHPTMapMtx[21] = {1.19655e+00, 1.39310e+00, 1.44224e+00, 1.49138e+00, 1.54052e+00, 1.58966e+00, 1.63879e+00, 1.68793e+00, 1.73707e+00, 1.78621e+00, 1.83535e+00, 1.88448e+00, 1.93362e+00, 1.98276e+00, 2.03190e+00, 2.08104e+00, 2.13017e+00, 2.17931e+00, 2.22845e+00, 2.27759e+00, 2.37586e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300RPRHPTMapMtx + i);
};
};