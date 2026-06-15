


void getGEJ85NcFANMapMtx(double *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85NcFANMapMtx[7] = {5.00000e-01, 6.00000e-01, 7.00000e-01, 8.00000e-01, 9.00000e-01, 1.00000e+00, 1.05000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85NcFANMapMtx + i);
};
};