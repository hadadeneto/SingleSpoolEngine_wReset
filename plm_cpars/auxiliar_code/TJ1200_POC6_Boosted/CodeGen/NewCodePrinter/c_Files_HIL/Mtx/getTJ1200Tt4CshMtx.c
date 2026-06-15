


void getTJ1200Tt4CshMtx(double *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200Tt4CshMtx[1] = {-6.00000e-02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200Tt4CshMtx + i);
};
};