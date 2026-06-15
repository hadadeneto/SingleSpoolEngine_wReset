


void getTF1200FNcMaxContMtx(double *Pointer)
{
int i;
int TotalElem = 12;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200FNcMaxContMtx[12] = {5.16156e+03, 4.78021e+03, 4.45569e+03, 4.19332e+03, 3.98544e+03, 3.82419e+03, 3.70186e+03, 3.60986e+03, 3.54246e+03, 3.51274e+03, 3.48230e+03, 3.45683e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200FNcMaxContMtx + i);
};
};