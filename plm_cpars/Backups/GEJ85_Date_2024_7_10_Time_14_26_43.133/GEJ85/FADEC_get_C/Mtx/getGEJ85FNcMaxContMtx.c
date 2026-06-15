


void getGEJ85FNcMaxContMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85FNcMaxContMtx[10] = {1.19968e+04, 1.13779e+04, 1.08548e+04, 1.04241e+04, 1.00787e+04, 9.80808e+03, 9.59963e+03, 9.44038e+03, 9.32249e+03, 9.27030e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85FNcMaxContMtx + i);
};
};