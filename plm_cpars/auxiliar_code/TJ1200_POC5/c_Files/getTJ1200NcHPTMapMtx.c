


void getTJ1200NcHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200NcHPTMapMtx[7] = {3.02019e-01, 3.52356e-01, 4.02692e-01, 4.53029e-01, 5.03365e-01, 5.53702e-01, 1.00673e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200NcHPTMapMtx + i);
};
};