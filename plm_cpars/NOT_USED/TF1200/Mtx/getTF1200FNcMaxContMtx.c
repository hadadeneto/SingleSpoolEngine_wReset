


void getTF1200FNcMaxContMtx(double *Pointer)
{
int i;
int TotalElem = 12;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200FNcMaxContMtx[12] = {5.17417e+03, 4.79248e+03, 4.45012e+03, 4.18875e+03, 3.98230e+03, 3.83839e+03, 3.71672e+03, 3.61286e+03, 3.55838e+03, 3.52865e+03, 3.49800e+03, 3.47215e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200FNcMaxContMtx + i);
};
};