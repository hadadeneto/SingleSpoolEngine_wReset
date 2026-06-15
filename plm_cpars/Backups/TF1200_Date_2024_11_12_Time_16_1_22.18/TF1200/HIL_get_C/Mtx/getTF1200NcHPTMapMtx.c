


void getTF1200NcHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200NcHPTMapMtx[7] = {3.08457e-01, 3.59867e-01, 4.11276e-01, 4.62686e-01, 5.14095e-01, 5.65505e-01, 1.02819e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200NcHPTMapMtx + i);
};
};