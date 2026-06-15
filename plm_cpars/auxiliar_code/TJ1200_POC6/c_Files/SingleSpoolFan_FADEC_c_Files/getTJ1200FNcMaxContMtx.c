


void getTJ1200FNcMaxContMtx(double *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200FNcMaxContMtx[11] = {4.48631e+03, 4.26430e+03, 4.08477e+03, 3.94607e+03, 3.84493e+03, 3.77677e+03, 3.73599e+03, 3.71598e+03, 3.71316e+03, 3.71505e+03, 3.71914e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200FNcMaxContMtx + i);
};
};