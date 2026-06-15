


void getTJ40WcHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 8;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ40WcHPCStallMtx[8] = {6.87156e-01, 6.32804e-01, 5.49336e-01, 4.43545e-01, 3.33853e-01, 2.84908e-01, 2.13523e-01, 1.74895e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ40WcHPCStallMtx + i);
};
};