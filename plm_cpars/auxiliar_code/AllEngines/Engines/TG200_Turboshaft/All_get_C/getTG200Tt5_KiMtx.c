

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTG200Tt5_KiMtx(floating *Pointer)
{
int i;
int TotalElem = 0;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TG200Tt5_KiMtx[0] = {

for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TG200Tt5_KiMtx + i);
};
};