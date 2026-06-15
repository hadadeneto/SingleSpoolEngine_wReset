


void getTJ1200NcHPCMapMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200NcHPCMapMtx[10] = {5.00000e-01, 6.00000e-01, 7.00000e-01, 7.50000e-01, 8.00000e-01, 8.50000e-01, 9.00000e-01, 9.50000e-01, 1.00000e+00, 1.05000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200NcHPCMapMtx + i);
};
};