
	/*----------------------*/
	/* SOFTWARE IN THE LOOP */
	/*----------------------*/

	/* Verifies if software in the loop is required */
    if(HILMode == 0 && bit_start == 1){

        /* CONTROL LOGIC - SOFTWARE IN THE LOOP */

        /* Simulates reading from each GPIO pin */
        GPIOIn = (KeyBit6 << 6) | (KeyBit5 << 5) | (KeyBit4 << 4) | (KeyBit3 << 3) | (KeyBit2 << 2) | (KeyBit1 << 1) | (KeyBit0 << 0);
        keys.in = GPIOIn & 0x7FF;

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

		/*------------------------*/
		/* CONTROL AND MONITORING */
        /*------------------------*/

		/* Reads word containing faults simulated by siftware */
    	SoftSimFaults.FaultBits = SensFaults.FaultBits;

		/* -------------------------------------------------- */
	    /* SIMULATION OF GPIO PINES - TMATS & PWLM            */
	    /* (To be usedi in MATLAB and TMATS simulations only) */
	    /* -------------------------------------------------- */

        /* Simulates reading from each GPIO pin */
        keys.in = GPIOIn & 0x7FF;

		/* CAN 1 Misscommunication treatment */
		CAN1MissComm(&FaultStatus, &EngStatus, &OnOffCom, ContConst.EmergencyCom, ContConst.ShutDownCom);

		/* LOADS EngOnOff PARAMETERS */

		EngOnOff.CurrentKey = Current_key_start;
		EngOnOff.EmergencyKey = !keys.bits.emergency_key;
		EngOnOff.EmergencyWait = ContConst.EmergencyWait;
		EngOnOff.OldKey = Old_key_start;
		EngOnOff.OnOffCom = OnOffCom;
		EngOnOff.ShutDownKey = keys.bits.ac_drive_key;
		EngOnOff.ShutDownWait = ContConst.ShutDownWait;
		EngOnOff.StartKey = 0;
		EngOnOff.StartWait = ContConst.StartWait;
		EngOnOff.Emergency = EmergencyCommand;
		EngOnOff.Start = StartCommand;
		EngOnOff.ShutDown = ShutDownCommand;
		EngOnOff.StartCom = ContConst.StartCom;
		EngOnOff.ShutDownCom = ContConst.ShutDownCom;
		EngOnOff.EmergencyCom = ContConst.EmergencyCom;

		OnOffLogicSR(&EngOnOff, Ts);

		/* Updates starting keys */
		Old_key_start = EngOnOff.OldKey;
		Current_key_start = EngOnOff.CurrentKey;

		/* Updates commands */
		StartCommand = EngOnOff.Start;
		EmergencyCommand = EngOnOff.Emergency;
		ShutDownCommand = EngOnOff.ShutDown;

//<FADECCore>
		/*=====================================================================*/
		/*   START OF SSModelLoop.c AND PIMMRF_XXX.c IDENTICAL CODE PIECE   */
		/*																       */
		/*   NOTE: The following procedures must be accomplished for the       */
		/*         current versions of FADEC and HIL					       */
		/*			- The matrices in the FADEC are stored in strings, being   */
		/*        directly declared as so, i.e., floating Matrix(Size);    	   */
		/*			- The matrices in the HIL are stored with "alloc" command  */
		/*        and each matrix variable is a poiter for floating, i.e.,       */
		/*        floating *Matrix; 											   */
		/*			- The sample time in the FADEC is defined as Ts, while the */
		/*		  sample time in the HIL is defined as Tsample				   */
		/*		  															   */
		/*	Taking into account the above considerations, the following steps  */
		/*	must be accomplished:											   */
		/*   - Whenever a matrix pointer is passed as a function argument in   */
		/*     the FADEC, it should be called as function(..., &Matrix, ...)   */
		/*   - Whenever a matrix pointer is passed as a function argument in   */
		/*     the HIL, it should be called as function(..., Matrix, ...)      */
		/*   - The sample time is passed as function(..., Ts, ...) in the 	   */
		/*     FADEC and as function (..., Tsample, ...) in the HIL	           */
		/*     			  													   */
		/*=====================================================================*/

		/*----------------------------------------------------*/
		/* CONVERTS Tt2 INTO Ts2 IF Tt2 WAS DIRECTLY MEASURED */
		/*----------------------------------------------------*/

		/* Converts from total temperature to static temperature for further claculations if total temperature has been directly measured */
		Tt2toTs2(&Sensors, ContConst.NumTs2Sens, MN, GAMMA_AIR, ContConst.T2Type);

        /*--------------------------------------------*/
        /* THERMOCOUPLE FAULT SIMULATION VIA SOFTWARE */
        /*--------------------------------------------*/

        /* Thermocouple fault simulation */
        TCFault(&Sensors, &SoftSimFaults, &FaultSensAuthorize, &Ts2_0, &Ts2_1, &Tt4_0, &Tt4_1, &Tt4_2, &TB_0, &TB_1, &TB_2, ContConst.TCOpen);

        /*----------------*/
        /* FAULT ANALYSIS */
        /*----------------*/

        /* Calculates thermocouple residuals according to identified faults */
        TCResCalc(&Ts2_0, &Ts2_1, &Tt4_0, &Tt4_1, &Tt4_2, &TB_0, &TB_1, &TB_2,
                  &Ts2Res, &Tt4Res, &TBearRes);

        /* Estimation of indexes using current Altitude, MN and FNpc values */
        /* In this case, the structure ModelPars must be used - Open-Loop model */
		EstIndex(&ModelPars, AltLinVec, MNLinVec,
				 Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
				 FNperContMtx, &ContConst, &Index3D);
        /* CALCULATION OF ENGINE MODEL Ts2 */

        /* Calculation of model ambient temperature */
        /* In this case, the structure ModelPars must be used - Open-Loop model */
		Ts2ModelCalc(Ts0Mtx, &ContConst,
					 Ts0Mtx2D, Ts0Mtx2DH, Ts0Mtx1D, Ts0Mtx1DH,
					 &ModelPars, &Index3D);

        /* Updates closed loop model ambient parameters from open-loop model */
        ModelParsCL.Ts2StdSL = ModelPars.Ts2StdSL;
        ModelParsCL.Ts2 = ModelPars.Ts2;
        ModelParsCL.Ts2Std = ModelPars.Ts2Std;

        /* CHOSES WHICH MODEL TO BE USED FOR RESIDUAL CALCULATIONS */
        /* ModelParsP - Open-Loop model */
        // ModelParsChosen = ModelPars;
        /* ModelParsP - Closed-Loop model */
        ModelParsChosen = ModelParsCL;

        /* INITIALIZATION OF AUTORIZING VARIABLES FOR FAULT ANALYSIS */
        // FaultSensAuthorize.FaultBits = 0xFFFFFFFFFFFFFFFF;
        // FaultSysAuthorize.FaultBits = 0xFFFFFFFFFFFFFFFF;
        // HardFAuthorize.FaultBits = 0xFFFFFFFFFFFFFFFF;

        /* ANALYSIS AUTHORIZING */

        SensAnalisysAuthorize(&FaultSensAuthorize, &ContStart, &ContInput, &EngStatus, StartFaultAnalysis);

        SysAnalisysAuthorize(&FaultSysAuthorize, &ContStart, &ContInput, &EngStatus, StartFaultAnalysis);

        BiasAnalisysAuthorize(&HardFAuthorize, &ContStart, &ContInput, &EngStatus, StartFaultAnalysis);

