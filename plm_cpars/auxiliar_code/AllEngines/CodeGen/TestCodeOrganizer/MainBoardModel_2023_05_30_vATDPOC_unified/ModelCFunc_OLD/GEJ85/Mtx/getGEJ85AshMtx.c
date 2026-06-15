


void getGEJ85AshMtx(double *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85AshMtx[1] = {-5.00000e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85AshMtx + i);
};
};