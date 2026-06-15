


void getTJ200FNcMaxContMtx(double *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200FNcMaxContMtx[11] = {1.20684e+03, 1.14916e+03, 1.10273e+03, 1.06707e+03, 1.04127e+03, 1.02393e+03, 1.01369e+03, 1.00886e+03, 1.00847e+03, 1.00928e+03, 1.01059e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200FNcMaxContMtx + i);
};
};