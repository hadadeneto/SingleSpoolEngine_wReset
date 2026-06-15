


void getTJ1200FNcMaxContMtx(double *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200FNcMaxContMtx[11] = {4.69792e+03, 4.46163e+03, 4.27072e+03, 4.12346e+03, 4.01627e+03, 3.94420e+03, 3.90154e+03, 3.88157e+03, 3.88002e+03, 3.88344e+03, 3.88852e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200FNcMaxContMtx + i);
};
};