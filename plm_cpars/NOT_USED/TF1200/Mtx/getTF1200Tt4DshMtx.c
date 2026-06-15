


void getTF1200Tt4DshMtx(double *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200Tt4DshMtx[1] = {4.00000e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200Tt4DshMtx + i);
};
};