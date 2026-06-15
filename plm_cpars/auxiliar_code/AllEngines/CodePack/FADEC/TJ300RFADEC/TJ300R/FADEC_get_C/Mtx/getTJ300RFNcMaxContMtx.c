

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300RFNcMaxContMtx(floating *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300RFNcMaxContMtx[11] = {1.55875e+03, 1.48337e+03, 1.42266e+03, 1.37602e+03, 1.34224e+03, 1.31962e+03, 1.30616e+03, 1.29976e+03, 1.29921e+03, 1.30023e+03, 1.30180e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300RFNcMaxContMtx + i);
};
};