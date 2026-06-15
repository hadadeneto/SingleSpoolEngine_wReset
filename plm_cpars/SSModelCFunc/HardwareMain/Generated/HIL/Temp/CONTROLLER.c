
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

		/*=====================================================================*/
		/*   START OF SSModelLoop.c AND PIMMRF_TJ1200.c IDENTICAL CODE PIECE   */
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
// HardFAuthorize.FaultBits = 0;
// FaultSensAuthorize.FaultBits = 0;
// FaultSysAuthorize.FaultBits = 0;
// HardFAuthorize.DetFaults.Ts2_0_Fault = 0;
// HardFAuthorize.DetFaults.Ts2_1_Fault = 0;
        /* RESIDUAL CALCULATION AND PROCESSING */

        /* Residuals calculations */
        /* In this case, two options:
		- ModelPars for Open-Loop model
		- ModelParsCL for Closed-Loop model
		*/
        ResidualsCalc(&ContConst,
             &ModelParsChosen, &Sensors,
             &Ts2Res, &Pt3Res, &Tt4Res,
             &RPMRes, &POilRes, &PFuelRes,
             &VibrationRes, &TBearRes);

        /* Sensors residuals processing */
        /* In this case, two options:
		- ModelPars for Open-Loop model
		- ModelParsCL for Closed-Loop model
		*/
        ResProcSens(&ContConst, &ModelParsChosen, &Sensors,
            &Ts2Res, &Pt3Res, &Tt4Res,
            &RPMRes, &POilRes, &PFuelRes,
            &VibrationRes, &TBearRes,
            &FaultSSens, &FaultWSens, &FaultSensAuthorize);

        /* Systems residuals processing */
        /* In this case, two options:
		- ModelPars for Open-Loop model
		- ModelParsCL for Closed-Loop model
		*/
		ResProcSys(&ContConst, &ModelParsChosen,
				   &BlowOutPars, &Sensors,
				   &Ts2Res, &Pt3Res, &Tt4Res,
				   &RPMRes, &POilRes, &PFuelRes,
				   &VibrationRes, &TBearRes,
				   &FaultSSys, &FaultWSys, &FaultSysAuthorize,
				   &CANFault, &ContStart);

        /* Sensor bias residuals processing */
        /* In this case, two options:
		- ModelPars for Open-Loop model
		- ModelParsCL for Closed-Loop model
		*/
        ResProcBias(&ContConst, &ModelParsChosen,
             &Ts2Res, &Pt3Res, &Tt4Res,
             &RPMRes, &POilRes, &PFuelRes,
             &VibrationRes, &HardFStatus, &HardFWarning, &HardFAuthorize);

        /* FAULT ANALYSIS */

        /* Initiates trusted sens with 0xFFFF for possible overtemp and overspeed verification,
        and initial calculation of medium value */
        TrustSens.FaultBits = 0x7FF;
        TrustHard.FaultBits = 0x7FF;

        /* As soon as a complete start is dectedtec, an extra time period must be accounted for
		before fault analysis is carried on in order for the FADEC internal model to start matchin
		sensor measurements */
		if (StartComplete == 1 && StartFaultAnalysis == 0)
		{
			/* code */
			WaitTime = ContStart.WaitTime;
			StatusDelay(&WaitTime, Ts, ContConst.TimeFaultAnaylsis, &StartFaultAnalysis, 1);
			ContStart.WaitTime = WaitTime;

		}

        /* SENSOR FAULTS ISOLATED AT EACH SENSOR */

        /* Updates sensor isolated faults - Warnings */
        SensFaultUpdt(&FaultWarning, &FaultWSens, &FaultSensAuthorize);
        /* Updates sensor isolated faults - Status */
        SensFaultUpdt(&FaultStatus, &FaultSSens, &FaultSensAuthorize);

        /* ANALYSES OF SENSOR TRUSTWORTHINES */

        /* Sensors thrustworthiness analysis - checks if isolated sensor faults have occurred */
        SensorTrust(&TrustSens, &FaultSSens, &FaultWSens);


        /* SYSTEM FAULTS ISOLATED AT EACH SENSOR */

        /* Updates sensor faults - Warnings */
        SysFaultUpdt(&FaultWarning, &FaultWSys, &FaultSysAuthorize);
        /* Updates sensor faults - Status */
        SysFaultUpdt(&FaultStatus, &FaultSSys, &FaultSysAuthorize);

        /* HARD FAULTS - HIGH BIAS - AT EACH SENSOR */

        /* Updates sensor hard faults - Warnings */
        HardFaultUpdt(&FaultWarning, &HardFWarning, &HardFAuthorize);
        /* Updates sensor hard faults - Status */
        HardFaultUpdt(&FaultStatus, &HardFStatus, &HardFAuthorize);

        /* ANALYSES OF SENSOR TRUSTWORTHINES */

        /* Sensors thrustworthiness analysis - checks if high bias has occurred */
        HardTrust(&TrustHard, &HardFStatus, &HardFWarning);

        /* ISOLATION OF SYSTEMS FAULTS */

        /* Identification and isolation engine blow out */
        BlowOut(&TrustSens, &FaultSSys, &FaultStatus);

        /* Identification and isolation engine blow out */
        MecLock(&TrustSens, &FaultSSys, &FaultStatus);

        /* Verificatin of overtemp */
        OverTemp(&ContConst, &TrustSens, &FaultSSys, &Sensors, &FaultStatus);

        /* Verification of overspeed */
        OverSpeed(&TrustSens, &FaultSSys, &Sensors, &FaultStatus);

        /* Verification of ignition failure */
        FaultStatus.Faults.Ignition = FaultSSys.SysFaults.Ignition;//ContStart.IgnitionFail;

        /* IDENTIFICATION OF ENGINE STATUS */

        /* Identifies initial or windmilling status */
        EngStatusDeff(&EngStatus, &ModPFault, &ContInput,
                    &ContStart, &ContConst,
                    0, 6,
                    StartCommand, 1, ContInput.ThrustCommandOn,
                    ShutDownCommand, 1, EmergencyCommand, 1,
                    CriticalFailure, 1, Ts);

        /* CALCULATION OF MEDIUM VALUES */

        /* In this case, two options:
		- ModelPars for Open-Loop model
		- ModelParsCL for Closed-Loop model
		*/

        /*The variable TrustAll indicates if either any sensor short/open or any sensor bias has occurred*/
        TrustAll.FaultBits = TrustHard.FaultBits & TrustSens.FaultBits;

        /* Below, the ModPFault struct indicates which modeled parameters has any fault at each of its sensors, indicating
        that, for this particular parameter, only the model estimation is being used */

        /* Calculates the medium value of Ts2 - The last indicates the minimum number of trusted sensors before
        untrusted sensors are replaced by model calculated values */
        Ts2MediumValue(&ModPFault, &Ts2MedVal, ContConst.NumTs2Sens, &TrustAll, &Sensors, ModelParsChosen.Ts2,ContConst.NumTs2SensTrust);
        /* Calculates the medium value of Pt3 - The last indicates the minimum number of trusted sensors before
        untrusted sensors are replaced by model calculated values */
        Pt3MediumValue(&ModPFault, &Pt3MedVal, ContConst.NumPs3Sens, &TrustAll, &Sensors, ModelParsChosen.Pt3,ContConst.NumPs3SensTrust);
        /* Calculates the medium value of Tt4 - The last indicates the minimum number of trusted sensors before
        untrusted sensors are replaced by model calculated values */
        Tt4MediumValue(&ModPFault, &Tt4MedVal, ContConst.NumTt4Sens, &TrustAll, &Sensors, ModelParsChosen.Tt4,ContConst.NumTt4SensTrust);
        /* Calculates the medium value of RPM - The last indicates the minimum number of trusted sensors before
        untrusted sensors are replaced by model calculated values */
        RPMMediumValue(&ModPFault, &RPMMedVal, ContConst.NumRPMSens, &TrustAll, &Sensors, ModelParsChosen.RPM,ContConst.NumRPMSensTrust);

        /* Updates variables with calculated medium values */
        Ts2 = Ts2MedVal;
        Pt3 = Pt3MedVal;
        Tt4 = Tt4MedVal;
        RPM = RPMMedVal;

        /*------------------------------*/
        /* BEARINGS TEMPERATURE CONTROL */
        /*------------------------------*/

		/* Performs oil control as soon as Windmill is reached */
        TBearControl(&ContGenOil, &ContGenEmpty, &EngStatus, &ContConst, &Sensors, OPRPMManual, RPM, !Mode, Ts);

        /* ESTIMATION OF BACKGROUND STANDARD TEMPERATURE BASED ON ALTITUDE AND MN */

        /* In this case, the structure ModelPars must be used - Open-Loop model */

		Ambient.Alt = Altitude;
		Ambient.MN = MN;
		Ambient.dT = 0;
		Ambient_TMATS(&Ambient);

        /* Loads parameters fo Tt2 Calculations */
		ModelPars.gamma_air = GAMMA_AIR;
    	ModelPars.MN = MN;
    	ModelPars.Ts2Std = Ambient.Ts;

        /* Calculation of total temperature */
        Tt2Calc(Ts2, &ModelPars);

        /* Updates Tt2 and dT values */
        Tt2 = ModelPars.Tt2;
        dT = ModelPars.dT;

        /* UPDATES CLOSED-LOOP MODEL AMBIENT PARAMETERS FROM OPEN-LOOP MODEL */

        /* Updates closed loop model parameters */
        ModelParsCL.gamma_air = ModelPars.gamma_air;
        ModelParsCL.MN = MN;
        ModelParsCL.Ts2Std = ModelPars.Ts2Std;
        ModelParsCL.Tt2 = ModelPars.Tt2;
        ModelParsCL.dT = ModelPars.dT;
        ModelParsCL.Ts2StdSL = ModelPars.Ts2StdSL;

        PrintFaults(&FaultWarning,0,1);
        PrintFaults(&FaultStatus,1,0);
        PrintEngStatus(&EngStatus,1);

        /*-----------------------------------------------------*/
        /* VERIFIES EMERGENCY SHUT DOWN DUE TO ENGINE FAILURE  */
        /*-----------------------------------------------------*/

        FailureShutDown(&FaultStatus, &CriticalFailure);

		/*-------------------------------------------------------------*/
		/* CALCULATION OF REFERENCE IN CASE ENGINEERING UNITS ARE USED */
		/*-------------------------------------------------------------*/

		/* CALCULATION OF AMBIENT CONTIDIONS BASED ON ALTITUDE AND MACH NUMBER INFORMATION */
		Ambient.Alt = Altitude;
		Ambient.MN = MN;
		Ambient.dT = dT;

		Ambient_TMATS(&Ambient);
		Delta = Ambient.Pt / PSTD;

		/* CALCULATION OF MAXIMUM CORRECTED THRUST AT GIVEN FLIGHT MACH NUMBER IN CASE ENGINEERING UNITS ARE USED */

		/* Finds indexes from a dummy percentual value of Fnpc for obtaining the Mach number indexes */
        InterpInd3DRPM(0, MN, 0.95, AltLinVec, MNLinVec, FNperContMtx, Mtx2D, Mtx2DH, Mtx1D, Mtx1DH, 1, MN_Elem, Fn_Elem, &Index3D);

        /* Shifts the indexes of Index3D for finding a 1D element */
		Index3D.kRPM = Index3D.kMN;
		Index3D.kRPMH = Index3D.kMNH;
		Index3D.fRPM = Index3D.fMN;
		Index3D.kMN = 0;
		Index3D.kMNH = 0;
		Index3D.fMN = 0;
		Index3D.kA = 0;
		Index3D.kAH = 0;
		Index3D.fA = 0;

		/* Finds the corrected value for maximum thrust at given flight Mach number */
		FNcMax = InterpValue(&Index3D, FNcMaxContMtx, Mtx1D, Mtx1DH, Mtx1D, Mtx1DH, MN_Elem, MN_Elem);

		/* Verifies if engineering units are to be used */
		if (EngUnits == 1)
		{
			/* Corrects FNpc in case engineering units are used */
			FNpc = FNpc / FNcMax / Delta;
		}

        /*--------------------*/
        /* ENGINE CONTROL LAW */
        /*--------------------*/

        /* Updates Controller Inputs */
        ContInput.Old_key_start = Old_key_start;
        ContInput.Current_key_start = Current_key_start;
        ContInput.bits_inverter = digital.bits.inverter;
        ContInput.Mode = Mode;
        ContInput.LeverMode = LeverMode;
        ContInput.EngUnits = EngUnits;
        ContInput.Altitude = Altitude;
        ContInput.MN = MN;
        ContInput.Tt2 = Tt2;
        ContInput.Pt3 = Pt3;
        ContInput.Tt4 = Tt4;
        ContInput.FNpc = FNpc;
        ContInput.RPM = RPM;
        ContInput.POil = POil;
        ContInput.SkipStart = SkipStart;
        ContInput.Wf0 = Wf0;
        keysWord = keys.in;
        digitalWord = digital.out;

        /* NOMINAL SHUT DWON REFERENCE */

        /* If nominal shut down has been requested, controller reference must be set to minimum */
        ShutDownRef(ShutDownCommand, &ContInput, &ContOutput, &ContConst, Ts);

        /* BOOSTER PHASE PROTECTION */

		/* If booster is connected, measured value of Pt3 must not be considered and blow out protection must be deactivated */
		BoosterProtect(&ContConst, &ContInput, Delta, BoosterLStatus, BoosterRStatus, Ts);
//mexPrintf("RealCont: BoostL=%d BoostR=%d Time=%f status=%d Delta=%f Pt3=%f\n",BoosterLStatus, BoosterRStatus, ContInput.TimerBoost, ContInput.statusBooster, Delta, ContInput.Pt3);

		/* CALCULATES THE CONTROL LAW */

        /* Calculates fuel flow from control law */
		PIMinMaxRF(AltLinVec, MNLinVec, NcVec, ASVec, DSVec,
				   Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
				   DeltaMtx2D, DeltaMtx2DH, DeltaMtx1D, DeltaMtx1DH,
				   &ContConst, &ContStart, &ContInput, &ContOutput, &digitalWord, &keysWord,
				   DeltaMtx, NcFANContMtx, FNcMaxContMtx, FNperContMtx,
				   N_KpMtx, N_KpshMtx, N_KiMtx, N_KishMtx, Ts);

        /* Updates digital outputs and fuel flow value */
        digital.out = digitalWord;

        /* EXECUTES NOMINAL SHUT DOWN RAMP */

        ShutDownRamp(&ContInput, &ContInputEmpty,
                     &ContOutput, &ContOutputEmpty,
                     &ContStart, &ContStartEmpty,
                     &ContGenOil, &ContGenEmpty,
                     &digital, &ContConst, Ts);

        /* EXECUTES EMERGENCY SHUT DOWN ROUTINE IF EMERGENCY HAS OCCURRED */

        /* Engine must execute emergency shut down either through external command of
        Emergency or through detection of critical failure */
        EmergShutDwn = EmergencyCommand || CriticalFailure;

        EmergencyShutDown(&ContInput, &ContInputEmpty,
						  &ContOutput, &ContOutputEmpty,
						  &ContStart, &ContStartEmpty,
                          &ContGenOil, &ContGenEmpty,
                          &digital, EmergShutDwn);

        /* Updates fuel flow value */
        Wf = ContOutput.Wf;

        /* Updates control signal - must be done after shut down analysis */
        OPRPM = ContGenOil.uOut[0];

        /* Updates starting phase outputs */
        StartComplete = ContOutput.StartComplete;
        IgnitionFail = ContOutput.IgnitionFail;
        ControlPhase = ContOutput.ControlPhase;

        /*--------------------*/
        /* MODEL CALCULATIONS */
        /*--------------------*/

        /* Verifies if model parameters are to be started */
        if (ModelParsStart == 1)
        {

             /* Sets initial values of filtered parameters */
            ModelPars.WfOutfp = Wf0;
            ModelPars.Ts2Sensed = Ts2;
            ModelPars.Pt3Sensed = Pt3;
            ModelPars.Tt4Sensed = Tt4;

            /* Sets initial values of filtered parameters */
            BlowOutPars.WfOutfp = Wf0;
            BlowOutPars.Ts2Sensed = Ts2;
            BlowOutPars.Pt3Sensed = Pt3;
            BlowOutPars.Tt4Sensed = Tt4;

            /* Sets initial values of closed loop parameters */
            ModelParsCL.WfOutfp = Wf0;
            ModelParsCL.Ts2Sensed = Ts2;
            ModelParsCL.Pt3Sensed = Pt3;
            ModelParsCL.Tt4Sensed = Tt4;

            /* Sets flag indicating starting of model parameters to zero */
            ModelParsStart = 0;
        }

        /* Updates model inputs */
        ModelPars.Altitude = Altitude;
        ModelPars.MN = MN;
        ModelPars.FNpc = FNpc;
        ModelPars.gamma_air = GAMMA_AIR;
        ModelPars.Pt3 = Pt3;
        ModelPars.Tt4 = Tt4;
        ModelPars.Wf = Wf;
        ModelPars.RPM = RPM;
        ModelPars.POil = ContConst.POilModel;
        ModelPars.PFuel = ContConst.PFUelModel;
        ModelPars.Vibration = ContConst.VibModel;
        ModelPars.Ts = 0.001 * TICK;
        ModelPars.NumSteps = ContConst.NumSteps;
        ModelPars.MaxInter = ContConst.MaxInterFault;

        /* Updates fuel lack model inputs */
        BlowOutPars = ModelPars;
        /* Sets fuel value to 0 for simulating fuel lack situation */
        BlowOutPars.Wf = 0;

        /* Calculates model for normal functioning */
        ModelCalc(&ModelPars, DeltaMtx,
                  AltLinVec, MNLinVec, &ContConst,
                  Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
                  DeltaMtx2D, DeltaMtx2DH, DeltaMtx1D, DeltaMtx1DH,
                  NcFANContMtx, Tt4Mtx, Pt3Mtx,
                  AMtx, BMtx, Tt4DMtx, Pt3DMtx,
                  WfMtx, Ts0Mtx,
                  Pt5Mtx, Pt5DMtx, Tt5Mtx, Tt5DMtx,
                  NcHPCMapMtx, WcHPCMapMtx, PRHPCMapMtx,
                  MapHPC1D, MapHPC1DH, MapHPC2D, MapHPC2DH);

        /* Calculates model for fuel lack */
		ModelCalc(&BlowOutPars, DeltaMtx,
				  AltLinVec, MNLinVec, &ContConst,
				  Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
				  DeltaMtx2D, DeltaMtx2DH, DeltaMtx1D, DeltaMtx1DH,
				  NcFANContMtx, Tt4Mtx, Pt3Mtx,
				  AMtx, BMtx, Tt4DMtx, Pt3DMtx,
				  WfMtx, Ts0Mtx,
				  Pt5Mtx, Pt5DMtx, Tt5Mtx, Tt5DMtx,
				  NcHPCMapMtx, WcHPCMapMtx, PRHPCMapMtx,
				  MapHPC1D, MapHPC1DH, MapHPC2D, MapHPC2DH);

        /* CLOSED-LOOP INTERNAL MODEL */

        /* Checks if fault analysis has started. If not, the closed-loop model must match exactly
        the open-loop model and simulation controller must match the real one */
        if (EngStatus.EngineStatus <= 8 | StartFaultAnalysis == 0)
        {
            /* Sets input  simulation controller  and real controller parameters as equal,
            and close-loop and opem-loop models as equal */
            ContStModCL = ContStart;
            ContInModCL = ContInput;
            ContOutModCL = ContOutput;
            ModelParsCL = ModelPars;
        }
        else
        {
            /* Updates Controller Inputs */
            // ContInModCL.Old_key_start = Old_key_start;
            // ContInModCL.Current_key_start = Current_key_start;
            // ContInModCL.bits_inverter = digital.bits.inverter;
            /* Externally defined parameters */
            ContInModCL.Mode = Mode;
            ContInModCL.LeverMode = LeverMode;
            ContInModCL.EngUnits = EngUnits;
            ContInModCL.Altitude = Altitude;
            ContInModCL.MN = MN;
            ContInModCL.FNpc = FNpc;

            /* Parameters calculated by model */
            ContInModCL.Tt2 = ModelParsCL.Tt2;
            ContInModCL.Pt3 = ModelParsCL.Pt3;
            ContInModCL.Tt4 = ModelParsCL.Tt4;
            ContInModCL.RPM = ModelParsCL.RPM;
            //ContInModCL.POil = POil;
            //ContInModCL.SkipStart = SkipStart;
            //ContInModCL.Wf0 = Wf0;
            //keysWord = keys.in;
            //digitalWord = digital.out;

			/* NOMINAL SHUT DWON REFERENCE */

            /* If nominal shut down has been requested, controller reference must be set to minimum */
            ShutDownRef(ShutDownCommand, &ContInModCL, &ContOutModCL, &ContConst, Ts);

            /* BOOSTER PHASE PROTECTION */

			/* If booster is connected, measured value of Pt3 must not be considered and blow out protection must be deactivated
			The same situation is reproduced in the model in order for more accureate reproduction of the real situation */
			BoosterProtect(&ContConst, &ContInModCL, Delta, BoosterLStatus, BoosterRStatus, Ts);
//mexPrintf("Model: BoostL=%d BoostR=%d Time=%f status=%d Delta=%f Pt3=%f\n",BoosterLStatus, BoosterRStatus, ContInModCL.TimerBoost, ContInModCL.statusBooster, Delta, ContInModCL.Pt3);
			/* CALCULATES THE CONTROL LAW */

            /* Calculates fuel flow from control law for closed-loop model */
			PIMinMaxRF(AltLinVec, MNLinVec, NcVec, ASVec, DSVec,
					   Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
					   DeltaMtx2D, DeltaMtx2DH, DeltaMtx1D, DeltaMtx1DH,
					   &ContConst, &ContStModCL, &ContInModCL, &ContOutModCL, &digitalWord, &keysWord,
					   DeltaMtx, NcFANContMtx, FNcMaxContMtx, FNperContMtx,
					   N_KpMtx, N_KpshMtx, N_KiMtx, N_KishMtx, Ts);

            /* EXECUTES NOMINAL SHUT DOWN RAMP */

            /* The same situation during shut down is reproduced in the closed-loop model
            for more accurate reproduction of the real situation */
            ShutDownRamp(&ContInModCL, &ContInputEmpty,
                         &ContOutModCL, &ContOutputEmpty,
                         &ContStModCL, &ContStartEmpty,
                         &ContGenOilCL, &ContGenEmpty,
                         &digModCL, &ContConst, Ts);

			/* EXECUTES EMERGENCY SHUT DOWN ROUTINE IF EMERGENCY HAS OCCURRED */

            /* The same situation during emergency shut down is reproduced in the closed-loop model
            for more accurate reproduction of the real situation */
            EmergencyShutDown(&ContInModCL, &ContInputEmpty,
                              &ContOutModCL, &ContOutputEmpty,
                              &ContStModCL, &ContStartEmpty,
                              &ContGenOilCL, &ContGenEmpty,
                              &digModCL, EmergShutDwn);
        }

        /* Updates closed-loop model inputs */
        ModelParsCL.Altitude = Altitude;
        ModelParsCL.MN = MN;
        ModelParsCL.FNpc = FNpc;
        ModelParsCL.gamma_air = GAMMA_AIR;
        // ModelParsCL.Pt3 = Pt3;
        // ModelParsCL.Tt4 = Tt4;
        ModelParsCL.Wf = ContOutModCL.Wf;
        // ModelParsCL.RPM = RPM;
        // ModelParsCL.POil = ContConst.POilModel;
        // ModelParsCL.PFuel = ContConst.PFUelModel;
        // ModelParsCL.Vibration = ContConst.VibModel;
        ModelParsCL.Ts = 0.001 * TICK;
        ModelParsCL.NumSteps = ContConst.NumSteps;
        ModelParsCL.MaxInter = ContConst.MaxInterFault;

        /* Performs closed-loop model calculation */
		ModelCalc(&ModelParsCL, DeltaMtx,
				  AltLinVec, MNLinVec, &ContConst,
				  Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
				  DeltaMtx2D, DeltaMtx2DH, DeltaMtx1D, DeltaMtx1DH,
				  NcFANContMtx, Tt4Mtx, Pt3Mtx,
				  AMtx, BMtx, Tt4DMtx, Pt3DMtx,
				  WfMtx, Ts0Mtx,
				  Pt5Mtx, Pt5DMtx, Tt5Mtx, Tt5DMtx,
				  NcHPCMapMtx, WcHPCMapMtx, PRHPCMapMtx,
				  MapHPC1D, MapHPC1DH, MapHPC2D, MapHPC2DH);

        /*===============================================================*/
        /* END OF SSModelLoop.c AND PIMMRF_TJ1200.c IDENTICAL CODE PIECE */
        /*                                                               */
        /* NOTE: The codes are to be identical except for the considera- */
        /*       tions mentioned at the note above                       */
        /*===============================================================*/

		/*---------------------------------------*/
		/* UPDATES PRESENT ONLY ON MODEL (MATLAB)*/
		/*---------------------------------------*/

		/* UPDATES Wf AND fValue - THE VARIABLE fValue MUST BE REPLACED BY Wf IN FUTURE VERSIONS*/
		ContOutput.fValue = Wf;
		ContOutput.FiltRef = ContOutput.MinRef;
		/* Updates digital outputs and fuel flow value */
		digital.out = digitalWord;
		fValue = ContOutput.fValue;
	}

