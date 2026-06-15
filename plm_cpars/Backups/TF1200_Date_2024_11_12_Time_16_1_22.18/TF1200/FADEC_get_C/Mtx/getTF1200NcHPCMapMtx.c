


void getTF1200NcHPCMapMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200NcHPCMapMtx[10] = {4.57162e-01, 5.48595e-01, 6.40027e-01, 6.85744e-01, 7.31460e-01, 7.77176e-01, 8.22892e-01, 8.68609e-01, 9.14325e-01, 9.60041e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200NcHPCMapMtx + i);
};
};