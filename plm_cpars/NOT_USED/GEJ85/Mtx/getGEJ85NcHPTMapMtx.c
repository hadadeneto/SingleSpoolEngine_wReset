


void getGEJ85NcHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85NcHPTMapMtx[7] = {4.35305e-01, 5.07856e-01, 5.80407e-01, 6.52958e-01, 7.25509e-01, 7.98060e-01, 1.45102e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85NcHPTMapMtx + i);
};
};