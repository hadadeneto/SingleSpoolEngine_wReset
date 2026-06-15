

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getGET700NcFANshContMtx(floating *Pointer)
{
int i;
int TotalElem = 12;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating GET700NcFANshContMtx[12] = {1.89394e-02, 3.78788e-02, 1.85606e-01, 3.33333e-01, 4.81061e-01, 6.28788e-01, 7.76515e-01, 9.24242e-01, 1.07197e+00, 1.21970e+00, 1.36742e+00, 1.51515e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GET700NcFANshContMtx + i);
};
};