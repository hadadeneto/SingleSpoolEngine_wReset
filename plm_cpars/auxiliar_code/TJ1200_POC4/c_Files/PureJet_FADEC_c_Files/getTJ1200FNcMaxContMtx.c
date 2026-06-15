


void getTJ1200FNcMaxContMtx(double *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200FNcMaxContMtx[11] = {4.54619e+03, 4.31773e+03, 4.13346e+03, 3.99167e+03, 3.88891e+03, 3.82032e+03, 3.78035e+03, 3.76232e+03, 3.76213e+03, 3.76682e+03, 3.77242e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200FNcMaxContMtx + i);
};
};