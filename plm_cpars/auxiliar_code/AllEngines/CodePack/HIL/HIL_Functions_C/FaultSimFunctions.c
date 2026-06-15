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
#include "../FADEC_Defines_H/IO_Types.h"
#include "../FADEC_Defines_H/Env_SampTime.h"
#include "../FADEC_Defines_H/Control_Types.h"
#include "../FADEC_Defines_H/FaultSim_Types.h"
#include "../FADEC_Defines_H/Model_Types.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"


/*******************************************************************************
 *
 *	FUNCTION:		SensorFault()
 *
 *	PURPOSE:		Verifies wether sensor values must be altered due to faults
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

void SensFaultSim(SensorFaults *FaultsP, struct SensedPars *SensorsP, struct EnginePars *EngParsP)
{

    /*-----------*/
    /* SECTION 3 */
    /*-----------*/

    /*FAULTS ON Pt3 SENSOR 1*/

    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.Pt3_0_Short)
    {
        SensorsP->Pt3[0] = EngParsP->PSSHORT;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.Pt3_0_Open)
    {
        SensorsP->Pt3[0] = EngParsP->PSSOPEN;
    }

    /*---------*/
    /*  SHAFT  */
    /*---------*/

    /*RPM SENSOR 1*/

    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.RPM_0_Short)
    {
        SensorsP->RPM[0] = EngParsP->RPMSSHORT;//0;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.RPM_0_Open)
    {
        SensorsP->RPM[0] = EngParsP->RPMSOPEN;//0;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.RPM_0_PLoss1)
    {
        SensorsP->RPM[0] = SensorsP->RPM[0] * 2 / 3;
    }
        /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.RPM_0_PLoss2)
    {
        SensorsP->RPM[0] = SensorsP->RPM[0] / 3;
    }
    // /* Verifies each sensor and alters its value depending on the fault */
    // if(FaultsP->SensFaults.RPM_0_3PLoss)
    // {
    //     SensorsP->RPM[0] = 0;
    // }

    /*RPM SENSOR 2*/

    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.RPM_1_Short)
    {
        SensorsP->RPM[1] = EngParsP->RPMSSHORT;//0;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.RPM_1_Open)
    {
        SensorsP->RPM[1] = EngParsP->RPMSOPEN;//0;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.RPM_1_PLoss1)
    {
        SensorsP->RPM[1] = SensorsP->RPM[1] * 2 / 3;
    }
        /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.RPM_1_PLoss2)
    {
        SensorsP->RPM[1] = SensorsP->RPM[1] / 3;
    }
    // /* Verifies each sensor and alters its value depending on the fault */
    // if(FaultsP->SensFaults.RPM_1_3PLoss)
    // {
    //     SensorsP->RPM[1] = 0;
    // }

    /*------*/
    /* POIL */
    /*------*/

    /*Pt3 SENSOR 3*/

    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.POil_0_Short)
    {
        SensorsP->POil[0] = EngParsP->PSSHORT;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.POil_0_Open)
    {
        SensorsP->POil[0] = EngParsP->PSSOPEN;
    }

    /*--------*/
    /* PFUELL */
    /*--------*/

    /* Fuel Sensor */

    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.PFuel_0_Short)
    {
        SensorsP->PFuel[0] = EngParsP->PFUELSHORT;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.PFuel_0_Open)
    {
        SensorsP->PFuel[0] = EngParsP->PSSOPEN;
    }

    /*-----------*/
    /* VIBRATION */
    /*-----------*/

    /* Vibration SENSOR 0 */

    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.Vib_0_Short)
    {
        SensorsP->Vibration[0] = EngParsP->VIBSHORT;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->SensFaults.Vib_0_Open)
    {
        SensorsP->Vibration[0] = EngParsP->VIBOPEN;
    }

};

/*******************************************************************************
 *
 *	FUNCTION:		SensorFault()
 *
 *	PURPOSE:		Verifies wether sensor values must be altered due to faults
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

void BiasFaultSim(FaultDetect *FaultsP, struct SensedPars *SensBiasP, struct SensedPars *SensorsP)
{
    /*-------------*/
    /* SENSOR BIAS */
    /*-------------*/

    /* Adds bias to Ts2 sensors */
    if(FaultsP->DetFaults.Ts2_0_Fault)
    {
        SensorsP->Ts2[0] = SensorsP->Ts2[0] + SensBiasP->Ts2[0];
    }
    if(FaultsP->DetFaults.Ts2_1_Fault)
    {
        SensorsP->Ts2[1] = SensorsP->Ts2[1] + SensBiasP->Ts2[1];
    }

    /* Adds bias to Pt3 sensors */
    if(FaultsP->DetFaults.Pt3_0_Fault)
    {
        SensorsP->Pt3[0] = SensorsP->Pt3[0] + SensBiasP->Pt3[0];
    }

    /* Adds bias to Tt4 sensors */
    if(FaultsP->DetFaults.Tt4_0_Fault)
    {
        SensorsP->Tt4[0] = SensorsP->Tt4[0] + SensBiasP->Tt4[0];
    }
    if(FaultsP->DetFaults.Tt4_1_Fault)
    {
        SensorsP->Tt4[1] = SensorsP->Tt4[1] + SensBiasP->Tt4[1];
    }
    if(FaultsP->DetFaults.Tt4_2_Fault)
    {
        SensorsP->Tt4[2] = SensorsP->Tt4[2] + SensBiasP->Tt4[2];
    }

    /* Adds bias to RPM sensors */
    if(FaultsP->DetFaults.RPM_0_Fault)
    {
        SensorsP->RPM[0] = SensorsP->RPM[0] + SensBiasP->RPM[0];
    }
    if(FaultsP->DetFaults.RPM_1_Fault)
    {
        SensorsP->RPM[1] = SensorsP->RPM[1] + SensBiasP->RPM[1];
    }

    /* Adds bias to POil sensors */
    if(FaultsP->DetFaults.POil_0_Fault)
    {
        SensorsP->POil[0] = SensorsP->POil[0] + SensBiasP->POil[0];
    }

    /* Adds bias to PFuel sensors */
    if(FaultsP->DetFaults.PFuel_0_Fault)
    {
        SensorsP->PFuel[0] = SensorsP->PFuel[0] + SensBiasP->PFuel[0];
    }

    /* Adds bias to Vibration sensors */
    if(FaultsP->DetFaults.Vib_0_Fault)
    {
        SensorsP->Vibration[0] = SensorsP->Vibration[0] + SensBiasP->Vibration[0];
    }

    /* Adds bias to bearings thermocouples */
    if(FaultsP->DetFaults.TB_0_Fault)
    {
        SensorsP->TBear[0] = SensorsP->TBear[0] + SensBiasP->TBear[0];
    }
    if(FaultsP->DetFaults.TB_1_Fault)
    {
        SensorsP->TBear[1] = SensorsP->TBear[1] + SensBiasP->TBear[1];
    }
    if(FaultsP->DetFaults.TB_2_Fault)
    {
        SensorsP->TBear[2] = SensorsP->TBear[2] + SensBiasP->TBear[2];
    }
}

/*******************************************************************************
 *
 *	FUNCTION:		BlowOut()
 *
 *	PURPOSE:		Alters the value of Wf if fuel system fault is identified
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		EngineFaults *FaultsP, floating *Wf
 *
 *	RETURNS:		Time
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void BlowOutSim(FaultDetect *FaultsP, floating *Wf)
{
    /* Verifies if engine blow out is to be simulated */
    if(FaultsP->DetFaults.BlowOut)
    {
        *Wf = 0;
    }
}

/*******************************************************************************
 *
 *	FUNCTION:		IgnitionFault()
 *
 *	PURPOSE:		Alters the value of Ignition flag for simulating ignition failure
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		FaultDetect *FaultsP, floating *Ignition
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void IgnitionFault(FaultDetect *FaultsP, int *Ignition)
{
    /* Verifies if engine blow out is to be simulated */
    if(FaultsP->DetFaults.Ignition)
    {
        *Ignition = 0;
    }
}

/*******************************************************************************
 *
 *	FUNCTION:		FuelSysFault()
 *
 *	PURPOSE:		Alters the value of Wf if fuel system fault is identified
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		EngineFaults *FaultsP, floating *Wf
 *
 *	RETURNS:		Time
 *
 *	COMMENTS:
 *
 *******************************************************************************/


/* Fuel system fault simulation */
void SysFaultSim(FaultDetect *FaultsP, struct EnginePars *EngParsP, struct EngineOutput *EngOutputP)
{

    /*--------------------*/
    /* LUBRICATION SYSTEM */
    /*--------------------*/

    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->DetFaults.POil_High)
    {
        EngOutputP->POil =  EngParsP->POILHIGH;

    }
    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->DetFaults.POil_Low)
    {
        EngOutputP->POil =  EngParsP->POILLOW;
    }

    /*-------------*/
    /* FUEL SYSTEM */
    /*-------------*/

    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->DetFaults.PFuel_High)
    {
        EngOutputP->PFuel =  EngParsP->PFUELHIGH;
    }
    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->DetFaults.PFuel_Low)
    {
        EngOutputP->PFuel = EngParsP->PFUELLOW;
    }

    /*------------*/
    /* MECHANICAL */
    /*------------*/

    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->DetFaults.OverTemp)
    {
        EngOutputP->Tt4 = EngParsP->Tt4HIGH;
    }

    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->DetFaults.OverSpeed)
    {
        EngOutputP->RPM = EngParsP->RPMHIGH;
    }

    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->DetFaults.VibrationHigh)
    {
        EngOutputP->Vibration = EngParsP->VIBHIGH;
    }

    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->DetFaults.TB_0_High)
    {
        EngOutputP->TBear[0] = EngParsP->TBearHIGH[0];
    }

    /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->DetFaults.TB_1_High)
    {
        EngOutputP->TBear[1] = EngParsP->TBearHIGH[1];
    }

        /* Verifies each sensor and alters its value depending on the fault */
    if (FaultsP->DetFaults.TB_2_High)
    {
        EngOutputP->TBear[2] = EngParsP->TBearHIGH[2];
    }


    /* Verifies each sensor and alters its value depending on the fault */
    if(FaultsP->DetFaults.Mec_Lock)
    {
        /* Rotation speed goes to zero */
        EngOutputP->RPM = 0;
        /* No pressure ratio is achieved at the compressor */
        EngOutputP->Pt3 = EngOutputP->Pt2;
        /* Combustion chamber temperature rises */
        EngOutputP->Tt4 = EngParsP->Tt4SHLCK;
        /* No temperature drop at turbine disk */
        EngOutputP->Tt5 = EngOutputP->Tt4;
        /* Vibration levels are high */
        EngOutputP->Vibration = EngParsP->VIBHIGH;
    }

};

/*******************************************************************************
 *
 *	FUNCTION:		SensorUpdt()
 *
 *	PURPOSE:		Updates sensors with values calculated by model
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		struct SensedPars *SensorsP, struct EngineOutput *EngOutputP
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

/* Updates the values of sensors with model calculations */
void SensorsUpdt(struct SensedPars *SensorsP, struct EngineOutput *EngOutputP)
{

    /*-----------*/
    /* SECTION 2 */
    /*-----------*/

    SensorsP->Ts2[0] = EngOutputP->Ts2;
    SensorsP->Ts2[1] = EngOutputP->Ts2;

    /*-----------*/
    /* SECTION 3 */
    /*-----------*/

    SensorsP->Pt3[0] = EngOutputP->Pt3;

    /*-----------*/
    /* SECTION 2 */
    /*-----------*/

    SensorsP->Tt4[0] = EngOutputP->Tt4;
    SensorsP->Tt4[1] = EngOutputP->Tt4;
    SensorsP->Tt4[2] = EngOutputP->Tt4;

    /*-------*/
    /* SHAFT */
    /*-------*/

    SensorsP->RPM[0] = EngOutputP->RPM;
    SensorsP->RPM[1] = EngOutputP->RPM;

    /*--------------*/
    /* LUBRICATION  */
    /*--------------*/

    SensorsP->POil[0] = EngOutputP->POil;

    /*------*/
    /* FUEL */
    /*------*/

    SensorsP->PFuel[0] = EngOutputP->PFuel;//EngOutputP->PFuel;

    /*-----------*/
    /* VIBRATION */
    /*-----------*/

    SensorsP->Vibration[0] = EngOutputP->Vibration;//EngOutputP->Vibration;

    /*-----------------------*/
    /* BEARINGS TEMPERATURES */
    /*-----------------------*/

    SensorsP->TBear[0] = EngOutputP->TBear[0];
    SensorsP->TBear[1] = EngOutputP->TBear[1];
    SensorsP->TBear[2] = EngOutputP->TBear[2];

};
