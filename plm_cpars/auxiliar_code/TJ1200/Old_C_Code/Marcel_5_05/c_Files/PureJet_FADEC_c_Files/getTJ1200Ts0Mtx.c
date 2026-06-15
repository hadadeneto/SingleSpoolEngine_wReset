


void getTJ1200Ts0Mtx(double *Pointer)
{
int i;
int TotalElem = 13;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200Ts0Mtx[13] = {2.88150e+02, 2.81650e+02, 2.75154e+02, 2.68655e+02, 2.62158e+02, 2.55677e+02, 2.49184e+02, 2.42699e+02, 2.36215e+02, 2.29733e+02, 2.23252e+02, 2.18427e+02, 2.16936e+02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200Ts0Mtx + i);
};
};