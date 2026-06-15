


void getTF1200NcHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200NcHPTMapMtx[7] = {2.72725e-01, 3.18180e-01, 3.63634e-01, 4.09088e-01, 4.54542e-01, 4.99996e-01, 9.09084e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200NcHPTMapMtx + i);
};
};