


void getGEJ85WfshMtx(double *Pointer)
{
int i;
int TotalElem = 1;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85WfshMtx[1] = {1.70000e-02};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85WfshMtx + i);
};
};