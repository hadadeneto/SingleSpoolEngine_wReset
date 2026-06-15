


void getTJ200NcHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200NcHPTMapMtx[7] = {3.00001e-01, 3.50001e-01, 4.00001e-01, 4.50001e-01, 5.00001e-01, 5.50001e-01, 1.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200NcHPTMapMtx + i);
};
};