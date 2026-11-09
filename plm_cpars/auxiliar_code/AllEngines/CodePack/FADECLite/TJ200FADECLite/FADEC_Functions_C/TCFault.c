/*
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % August 21, 2021
 * %
 * %  This is a file that contains various functions for use in the HIL code
 * % *************************************************************************/

//#include "constants_TMATS.h"
#include <math.h>
#include <stdint.h>
// #include "IO_Types.h"
// #include "Env_SampTime.h"
#include "../FADEC_Defines_H/Control_Types.h"
#include "../FADEC_Defines_H/FaultSim_Types.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"
// #include "Model_Types.h"

//floating ADC_Read();

/*******************************************************************************
 *
 *	FUNCTION:		TCFault()
 *
 *	PURPOSE:		Verifies wether thermocouple values are to be altered due to faults
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		EngineFaults *FaultsP, struct SensedPars *SensorsP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void TCFault(struct SensedPars *SensorsP, SensorFaults *FaultsP, SensorFaults *FaultSensAuthP, TCFaults *Ts2_0, TCFaults *Ts2_1, TCFaults *Tt4_0, TCFaults *Tt4_1, TCFaults *Tt4_2, TCFaults *TBear_0, TCFaults *TBear_1, TCFaults *TBear_2, floating TCOpen)

{

    /* Each union is reset to null values */
    Ts2_0->TCFaultBits = 0;
    Ts2_1->TCFaultBits = 0;
    Tt4_0->TCFaultBits = 0;
    Tt4_1->TCFaultBits = 0;
    Tt4_2->TCFaultBits = 0;

    /*---------*/
    /*SECTION 2*/
    /*---------*/

    /*Ts2 SENSOR 1 */

    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Ts2_0_SCV & FaultSensAuthP->SensFaults.Ts2_0_SCV)
    {
        Ts2_0->Faults.SCV = 1;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Ts2_0_SCG & FaultSensAuthP->SensFaults.Ts2_0_SCG)
    {
        Ts2_0->Faults.SCG = 1;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Ts2_0_Open & FaultSensAuthP->SensFaults.Ts2_0_Open)
    {
        Ts2_0->Faults.OC = 1;
        SensorsP->Ts2[0] = TCOpen;
    }

    /*Ts2 SENSOR 2*/

    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Ts2_1_SCV & FaultSensAuthP->SensFaults.Ts2_1_SCV)
    {
        Ts2_1->Faults.SCV = 1;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Ts2_1_SCG & FaultSensAuthP->SensFaults.Ts2_1_SCG)
    {
        Ts2_1->Faults.SCG = 1;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Ts2_1_Open & FaultSensAuthP->SensFaults.Ts2_1_Open)
    {
        Ts2_1->Faults.OC = 1;
        SensorsP->Ts2[1] = TCOpen;
    }

    /*---------*/
    /*SECTION 4*/
    /*---------*/

    /*Tt4 SENSOR 1 */

    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Tt4_0_SCV & FaultSensAuthP->SensFaults.Tt4_0_SCV)
    {
        Tt4_0->Faults.SCV = 1;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Tt4_0_SCG & FaultSensAuthP->SensFaults.Tt4_0_SCG)
    {
        Tt4_0->Faults.SCG = 1;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Tt4_0_Open & FaultSensAuthP->SensFaults.Tt4_0_Open)
    {
        Tt4_0->Faults.OC = 1;
        SensorsP->Tt4[0] = TCOpen;
    }

    /*Tt4 SENSOR 2*/

    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Tt4_1_SCV & FaultSensAuthP->SensFaults.Tt4_1_SCV)
    {
        Tt4_1->Faults.SCV = 1;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Tt4_1_SCG & FaultSensAuthP->SensFaults.Tt4_1_SCG)
    {
        Tt4_1->Faults.SCG = 1;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Tt4_1_Open & FaultSensAuthP->SensFaults.Tt4_1_Open)
    {
        Tt4_1->Faults.OC = 1;
        SensorsP->Tt4[1] = TCOpen;
    }

    /*Tt4 SENSOR 3*/

    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Tt4_2_SCV & FaultSensAuthP->SensFaults.Tt4_2_SCV)
    {
        Tt4_2->Faults.SCV = 1;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Tt4_2_SCG & FaultSensAuthP->SensFaults.Tt4_2_SCG)
    {
        Tt4_2->Faults.SCG = 1;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.Tt4_2_Open & FaultSensAuthP->SensFaults.Tt4_2_Open)
    {
        Tt4_2->Faults.OC = 1;
        SensorsP->Tt4[2] = TCOpen;
    }

    /* BEARINGS */

    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.TB_0_Open & FaultSensAuthP->SensFaults.TB_0_Open)
    {
        TBear_0->Faults.OC = 1;
        SensorsP->TBear[0] = TCOpen;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.TB_1_Open & FaultSensAuthP->SensFaults.TB_1_Open)
    {
        TBear_1->Faults.OC = 1;
        SensorsP->TBear[1] = TCOpen;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->SensFaults.TB_2_Open & FaultSensAuthP->SensFaults.TB_2_Open)
    {
        TBear_2->Faults.OC = 1;
        SensorsP->TBear[2] = TCOpen;
    }

};
