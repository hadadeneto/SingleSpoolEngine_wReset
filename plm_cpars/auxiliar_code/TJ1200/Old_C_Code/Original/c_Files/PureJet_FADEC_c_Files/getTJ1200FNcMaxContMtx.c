


void getTJ1200FNcMaxContMtx(double *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200FNcMaxContMtx[11] = {5.52284e+03, 5.25448e+03, 5.03421e+03, 4.86037e+03, 4.72928e+03, 4.63584e+03, 4.57413e+03, 4.53688e+03, 4.51999e+03, 4.50942e+03, 4.50803e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200FNcMaxContMtx + i);
};
};