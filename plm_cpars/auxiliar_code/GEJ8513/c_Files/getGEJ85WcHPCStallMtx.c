


void getGEJ85WcHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85WcHPCStallMtx[10] = {1.61719e+00, 2.24691e+00, 3.13292e+00, 3.73644e+00, 4.46382e+00, 5.42461e+00, 6.45542e+00, 7.50742e+00, 8.31449e+00, 8.95394e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85WcHPCStallMtx + i);
};
};