


void getTJ200FNcMaxContMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200FNcMaxContMtx[10] = {1.08235e+03, 1.02637e+03, 9.80896e+02, 9.45508e+02, 9.19346e+02, 9.01236e+02, 8.89779e+02, 8.83523e+02, 8.81643e+02, 8.80975e+02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200FNcMaxContMtx + i);
};
};