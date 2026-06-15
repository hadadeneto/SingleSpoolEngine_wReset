


void getTF1200BshMtx(double *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200BshMtx[1] = {8.00000e+04};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200BshMtx + i);
};
};