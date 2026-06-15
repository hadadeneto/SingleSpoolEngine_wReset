


void getTJ1200DwmMtx(double *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200DwmMtx[1] = {0.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200DwmMtx + i);
};
};