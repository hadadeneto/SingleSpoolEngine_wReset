


void getGEJ85CwmMtx(double *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85CwmMtx[1] = {0.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85CwmMtx + i);
};
};