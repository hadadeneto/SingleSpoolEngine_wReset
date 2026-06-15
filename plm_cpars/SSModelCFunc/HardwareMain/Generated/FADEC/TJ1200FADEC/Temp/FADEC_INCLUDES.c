/*-------------------*/
/* STANDARD INCLUDES */
/*-------------------*/

/* Standard includes */
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

/*-----------------------------------------------*/
/* GENERAL INCLUDES - USED BY ALL FADECS AND HIL */
/*-----------------------------------------------*/

/* General .h files */
#include "FADEC_Functions_H/Ambient_TMATS.h"          /* Adapted from T-MATS */
#include "FADEC_Defines_H/constants_TMATS.h"        /* Adapted from T-MATS */
#include "FADEC_Defines_H/Control_Types.h"          /* Controller calculations */
#include "FADEC_Functions_H/ControlFunctions.h"       /* Controller calculations */
#include "FADEC_Defines_H/DigitalOutDefs.h"         /* Controller calculations */
#include "FADEC_Defines_H/Env_SampTime.h"           /* General Calculations*/
#include "FADEC_Functions_H/FailSafeFunctions.h"      /* Fault analysis */
#include "FADEC_Defines_H/FaultSim_Types.h"         /* Fault analysis */
#include "FADEC_Defines_H/FloatPoint_Precision.h"			/* Defines the size of used floating point */
#include "FADEC_Functions_H/functions_TMATS.h"        /* Adapted from T-MATS */
//#include "getTJ1200.h"              /* File containing all get functions for TJ1200 */
#include "FADEC_Defines_H/Interpolation_Types.h"    /* General Calculations*/
#include "FADEC_Defines_H/IO_Types.h"               /* Controller calculations */
//#include "FADEC_Functions_H/LinMtxFunctions.h"        /* General Calculations*/
#include "FADEC_Defines_H/Model_Types.h"            /* Used for model calculations */
#include "FADEC_Functions_H/MtxIntFunctions.h"        /* General Calculations*/
#include "FADEC_Functions_H/PeripheralDyn.h"          /* Functions describing peripherals dynamics */
#include "FADEC_Functions_H/PIMinMaxRF.h"             /* Controller calculations */
//#include "PIOil.h"                  /* Controller calculations */
#include "FADEC_Functions_H/ShutDownFunctions.h"      /* Controller calculations */
#include "FADEC_Functions_H/StartingFunctions.h"      /* Controller calculations */
#include "FADEC_Functions_H/TCFault.h"                /* Fault analysis */

/*-----------------*/
/* ENGINE INCLUDES */
/*-----------------*/

/* Engine .h files */
#include "TJ1200/FADEC_Constants_H/ConstantsTJ1200.h"
#include "TJ1200/FADEC_get_H/getTJ1200FADECContConst.h"
#include "TJ1200/FADEC_get_H/getTJ1200FADECMtx.h"       /* TJ1200 Engine Constants */
#include "TJ1200/FADEC_get_H/getTJ1200FADECSizeConst.h"

