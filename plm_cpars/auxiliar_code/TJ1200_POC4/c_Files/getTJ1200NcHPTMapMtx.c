


void getTJ1200NcHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200NcHPTMapMtx[7] = {3.01676e-01, 3.51956e-01, 4.02235e-01, 4.52514e-01, 5.02794e-01, 5.53073e-01, 1.00559e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200NcHPTMapMtx + i);
};
};