


void getTJ40NcHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ40NcHPTMapMtx[7] = {2.99881e-01, 3.49861e-01, 3.99841e-01, 4.49821e-01, 4.99802e-01, 5.49782e-01, 9.99603e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ40NcHPTMapMtx + i);
};
};