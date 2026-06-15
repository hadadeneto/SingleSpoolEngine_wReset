


void getTJ200NcHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200NcHPTMapMtx[7] = {3.02822e-01, 3.53292e-01, 4.03762e-01, 4.54232e-01, 5.04703e-01, 5.55173e-01, 1.00941e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200NcHPTMapMtx + i);
};
};