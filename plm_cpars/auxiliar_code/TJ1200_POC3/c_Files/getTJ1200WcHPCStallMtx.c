


void getTJ1200WcHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200WcHPCStallMtx[10] = {1.46062e+00, 2.02938e+00, 2.82961e+00, 3.37470e+00, 4.03166e+00, 4.89943e+00, 5.83044e+00, 6.78060e+00, 7.50953e+00, 8.08707e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200WcHPCStallMtx + i);
};
};