


void getGEJ85NcFANshMtx(double *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85NcFANshMtx[1] = {0.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85NcFANshMtx + i);
};
};