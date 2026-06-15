
    /*-----------------------------------------------------------*/
    /* VARIABLES INITIALIZATIONS IN CASE ENGINE START IS SKIPPED */
    /*															 */
    /* In those cases, ain initial operating condition where the */
    /* engine thrust is non-zero is considered					 */
    /*-----------------------------------------------------------*/

    if (SkipStart == 1 && StartComplete == 0)
	{

		/* Sets initial conditions for fuel values and rotation speed references */
		ContOutput.Wf = Wf0;
		ContOutput.uNk1 = ContOutput.Wf;
		ContOutput.urk1 = ContOutput.Wf;
		ContOutput.ITermNk1 = ContOutput.Wf;
		ContOutput.uTt4k1 = ContOutput.Wf;
		ContOutput.ITermTk1 = ContOutput.Wf;
		ContOutput.eNk1 = 0;
		ContOutput.eTt4k1 = 0;
		ContOutput.RPMRef = RPM;
		ContOutput.MinRef = RPM;
		ContStart.RefInit = RPM;
		ContOutput.Active = 0;
		ContOutput.StartComplete = 1;

        /* Sets initial condition for oil pump rotation speed OPRPM */
        OPRPM = ContConst.OPRPMMax;

        /* Sets initial conditions for bearings temperatures controller */
        /* NOTE: Currently, the idiea is to start the oil pump at its
        maximum rotation speed whenever the simulation is required to
        start from a condition where the engine has already started */
        for (int i = 0; i < ContConst.NumBear; i++)
        {
            ContGenOil.uOut[i] = ContConst.OPRPMMax;
            ContGenOil.uk1[i] = ContConst.OPRPMMax;
            ContGenOil.ITermk1[i] = ContConst.OPRPMMax;
            ContGenOil.ek1[i] = 0;
            ContGenOil.eBk1[i] = 0;
        }

        //OPRPM = ContConst.OPRPMMax;

        /* Sets starting variables */
        ContStart.WfTrigger = ContOutput.Wf;
        ContStart.RefInitStatus = 1;

        /* Sets SkipStart to 0 */
        SkipStart = 0;

        /* Sets StartComplete to 1 */
        StartComplete = 1;

        /* Sets left and right boosters status to ejected */
        BoosterLStatus = 0xAA;
        BoosterRStatus = 0xAA;
        ContInput.statusBooster = 1;
        ContInModCL.statusBooster = 1;

        /* Sets engine status to REGIME */
        EngStatus.EngineStatus = 0;
        EngStatus.EngStatusBist.Regime = 1;
		ContInput.ThrustCommandOn = 1;

        /* Set on off status to 1 */
		EngOnOff.statusOnOff = 1;
		EngOnOff.OnOffCom = 0xAA;

		/* Sets OnOffMessage to its initial value */
		OnOffCom = 0xFF;
        ShutDownCommand = 0;
        EmergencyCommand = 0;
        StartCommand = 1;
		CriticalFailure = 0;

        /* Sets fault analysis flag to initial state */
        StartFaultAnalysis = 0;

        /* Sets flag indicating that model parameters must be started */
        ModelParsStart = 1;

    }

    /*-----------------------------------------------*/
	/* UPDATES REFERENCE FOR CONTROL LAW CALCULATION */
	/*-----------------------------------------------*/

	//Ignition = digital.bits.igniter;
	// RefCAN = (floating)reference;				/* This should be done in the hardware */

	/* -------------------------------------------------- */
	/* UPDATING RefCAN and FNpc - PWLM		              */
	/* (To be usedi in MATLAB (PWLM) simulations only)    */
	/* -------------------------------------------------- */

	// if (EngStatus.EngineStatus == 32 | ContInput.ThrustCommandOn > 0)
	// {
	// 	RefCAN = (floating)reference;
	// }

	/* -------------------------------------------------- */

	//FNpc = RefCAN;

    /* Stores CAN fault bit value */
	// FaultSSys.SysFaults.CAN_0_Fault = CANFault.SysFaults.CAN_0_Fault;
	// FaultSSys.SysFaults.CAN_1_Fault = CANFault.SysFaults.CAN_1_Fault;

    /* Updates FNpc and allows transition from IDLE to REGIME depending no reference value */
	IdleToRegime(&EngStatus, &ContInput, RefCAN, 0, ContConst.FNIdle, &FNpc, LeverMode);

