


void getGEJ85NcFANMapMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85NcFANMapMtx[10] = {7.25514e-01, 8.70617e-01, 1.01572e+00, 1.08827e+00, 1.16082e+00, 1.23337e+00, 1.30593e+00, 1.37848e+00, 1.45103e+00, 1.52358e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85NcFANMapMtx + i);
};
};