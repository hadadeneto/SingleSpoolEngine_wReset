

#include "../../../FADEC_Defines_H/FloatPoint_Precision.h"


void getTJ300RPRFANStallMtx(floating *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
floating TJ300RPRFANStallMtx[8] = {1.39388e+00, 1.31980e+00, 1.27202e+00, 1.20489e+00, 1.15297e+00, 1.11401e+00, 1.08141e+00, 1.05683e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ300RPRFANStallMtx + i);
};
};