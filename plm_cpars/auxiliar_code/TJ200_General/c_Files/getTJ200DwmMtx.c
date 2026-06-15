


void getTJ200DwmMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200DwmMtx[10] = {0.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200DwmMtx + i);
};
};