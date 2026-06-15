


void getTJ1200NcHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200NcHPTMapMtx[7] = {2.99998e-01, 3.49997e-01, 3.99997e-01, 4.49997e-01, 4.99996e-01, 5.49996e-01, 9.99993e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200NcHPTMapMtx + i);
};
};