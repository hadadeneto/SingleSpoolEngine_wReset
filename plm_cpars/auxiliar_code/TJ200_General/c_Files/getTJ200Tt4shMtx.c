


void getTJ200Tt4shMtx(double *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200Tt4shMtx[1] = {8.00000e+02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200Tt4shMtx + i);
};
};