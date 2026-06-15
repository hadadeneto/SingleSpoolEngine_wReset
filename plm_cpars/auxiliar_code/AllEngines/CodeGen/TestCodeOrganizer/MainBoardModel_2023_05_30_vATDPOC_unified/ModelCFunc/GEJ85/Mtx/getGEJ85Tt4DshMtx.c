


void getGEJ85Tt4DshMtx(double *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85Tt4DshMtx[1] = {4.00000e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85Tt4DshMtx + i);
};
};