
#include <math.h>
#include "../h_Files_HIL/ConstantsTJ1200.h"
#include "../h_Files_HIL/getTJ1200HILSizeConst.h"



void getTJ1200SizeConst(double *Alt_Elem, double *MN_Elem, double *Fn_Elem, double *AS_Elem, double *SteadyOp_Elem, 
     double *PowerMan_Elem, double *NcFANMap_Elem, double *WcFANMap_Elem, double *Wc_per_Nc_FAN, double *NcHPCMap_Elem, 
     double *WcHPCMap_Elem, double *Wc_per_Nc_HPC, double *NcHPTMap_Elem, double *PRHPTMap_Elem, double *WcHPTMap_Elem)
{

/* Loads sizes of linearization points */

    *AS_Elem = TJ1200_AS_ELEM;

    *Alt_Elem = TJ1200_ALT_ELEM;

    *Fn_Elem = TJ1200_FN_ELEM;

    *MN_Elem = TJ1200_MN_ELEM;

    *NcFANMap_Elem = TJ1200_FAN_NC;

    *NcHPCMap_Elem = TJ1200_FAN_NC;

    *NcHPTMap_Elem = TJ1200_HPT_NC;

    *PRHPTMap_Elem = TJ1200_HPT_PR;

    *PowerMan_Elem = TJ1200_TOTAL_ELEM;

    *SteadyOp_Elem = TJ1200_FN_ELEM *TJ1200_MN_ELEM;

    *WcFANMap_Elem = TJ1200_FAN_NC * TJ1200_FAN_PR;;

    *WcHPCMap_Elem = TJ1200_FAN_NC * TJ1200_FAN_PR;

    *WcHPTMap_Elem = TJ1200_HPT_NC * TJ1200_HPT_PR;

    *Wc_per_Nc_FAN = TJ1200_FAN_PR;

    *Wc_per_Nc_HPC = TJ1200_FAN_PR;

}