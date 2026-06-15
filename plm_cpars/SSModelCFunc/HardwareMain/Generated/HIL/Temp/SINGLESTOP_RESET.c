
	/* ============================================================================================================= */
	/* THE FOLLOWIN CODE MUST BE EXECUTED DIRECTLY IN THE MAIN MAIN FUNCTION RIGHT BEFORE THE INFINITE LOOP while(1) */
	/* ============================================================================================================= */

	/*-------------*/
	/* SINGLE STOP */
	/*-------------*/

	if (SingleStop == 0)
	{

        /*-----------------*/
        /* FADEC AND MODEL */
        /*-----------------*/

        /* STRUCTS INITIALIZATION */

        Ambient = AmbientEmpty;
        BlowOutPars = EstParsEmpty;
        ContConst = ContConstEmpty;
        ContGenOil = ContGenEmpty;
        ContInModCL = ContInputEmpty;
        ContInput = ContInputEmpty;
        ContOutModCL = ContOutputEmpty;
        ContOutput = ContOutputEmpty;
        ContStart = ContStartEmpty;
        ContStModCL = ContStartEmpty;
        EngOnOff = EngOnOffEmpty;
        Index3D = Index3DEmpty;
        ModelPars = EstParsEmpty;
        ModelParsChosen = EstParsEmpty;
        ModelParsCL = EstParsEmpty;
        PFuelRes = DefaultRes;
        POilRes = DefaultRes;
        Pt3Res = DefaultRes;
        RPMRes = DefaultRes;
        Sensors = SensorsEmpty;
        TBearRes = DefaultRes;
        Ts2Res = DefaultRes;
        Tt4Res = DefaultRes;
        VibrationRes = DefaultRes;

        /* UNIONS INITIALIZATION */

		CANFault = FaultDetectEmpty;
        digital = digitalEmpty;
        digModCL = digitalEmpty;
        EngStatus = EngStatusEmpty;
        ExistFStatus = FaultDetectEmpty;
        ExistFWarning = FaultDetectEmpty;
        FaultSensAuthorize = FaultSensEmpty;
        FaultSSens = FaultSensEmpty;
        FaultSSys = FaultSysEmpty;
        FaultStatus = FaultEmpty;
        FaultSysAuthorize = FaultSysEmpty;
        FaultWarning = FaultEmpty;
        FaultWSens = FaultSensEmpty;
        FaultWSys = FaultSysEmpty;
        HardFAuthorize = FaultDetectEmpty;
        HardFStatus = FaultDetectEmpty;
        HardFWarning = FaultDetectEmpty;
        keys = keysEmpty;
        ModPFault.ModParsBits = 0;
        SoftFStatus = FaultDetectEmpty;
        SoftFWarning = FaultDetectEmpty;
        SoftSimFaults = FaultSensEmpty;
        TB_0.TCFaultBits = 0;
        TB_1.TCFaultBits = 0;
        TB_2.TCFaultBits = 0;
        TrustAll = FaultDetectEmpty;
        TrustHard = FaultDetectEmpty;
        TrustSens = FaultDetectEmpty;
        Ts2_0.TCFaultBits = 0;
        Ts2_1.TCFaultBits = 0;
        Tt4_0.TCFaultBits = 0;
        Tt4_1.TCFaultBits = 0;
        Tt4_2.TCFaultBits = 0;

        /* static int TYPE */

        SingleStop = 1;

		/*------------*/
		/* MODEL ONLY */
		/*------------*/

		/* STRUCTS INITIALIZATION */

		Bear0 = BearEmpty;
		Bear1 = BearEmpty;
		Bear2 = BearEmpty;
        EngPars = EngParsEmpty;
        SensorBias = SensorsEmpty;
        Starting = StartingEmpty;

		/* UNIONS INITIALIZATION */

        Faults = FaultEmpty;
        SensFaults = FaultSensEmpty;
        SysFaults = FaultDetectEmpty;

	}

	/*----------------*/
	/* RESET FUNCTION */
	/*----------------*/

	if (Reset == 1)
	{

		/*-----------------*/
        /* FADEC AND MODEL */
        /*-----------------*/

        /* RESETS STRUCTS */

        Ambient = AmbientEmpty;
        BlowOutPars = EstParsEmpty;
        ContConst = ContConstEmpty;
        ContGenOil = ContGenEmpty;
        ContInModCL = ContInputEmpty;
        ContInput = ContInputEmpty;
        ContInput.Reset = 1;
        ContOutModCL = ContOutputEmpty;
        ContOutput = ContOutputEmpty;
        ContStart = ContStartEmpty;
        ContStModCL = ContStartEmpty;
        EngOnOff = EngOnOffEmpty;
        Index3D = Index3DEmpty;
        ModelPars = EstParsEmpty;
        ModelParsChosen = EstParsEmpty;
        ModelParsCL = EstParsEmpty;
        PFuelRes = DefaultRes;
        POilRes = DefaultRes;
        Pt3Res = DefaultRes;
        RPMRes = DefaultRes;
        Sensors = SensorsEmpty;
        TBearRes = DefaultRes;
        Ts2Res = DefaultRes;
        Tt4Res = DefaultRes;
        VibrationRes = DefaultRes;

        /* RESETS UNIONS */

		CANFault = FaultDetectEmpty;
        digital = digitalEmpty;
        digModCL = digitalEmpty;
        EngStatus = EngStatusEmpty;
        ExistFStatus = FaultDetectEmpty;
        ExistFWarning = FaultDetectEmpty;
        FaultSensAuthorize = FaultSensEmpty;
        FaultSSens = FaultSensEmpty;
        FaultSSys = FaultSysEmpty;
        FaultStatus = FaultEmpty;
        FaultSysAuthorize = FaultSysEmpty;
        FaultWarning = FaultEmpty;
        FaultWSens = FaultSensEmpty;
        FaultWSys = FaultSysEmpty;
        HardFAuthorize = FaultDetectEmpty;
        HardFStatus = FaultDetectEmpty;
        HardFWarning = FaultDetectEmpty;
        keys = keysEmpty;
        ModPFault.ModParsBits = 0;
        SoftFStatus = FaultDetectEmpty;
        SoftFWarning = FaultDetectEmpty;
        SoftSimFaults = FaultSensEmpty;
        TB_0.TCFaultBits = 0;
        TB_1.TCFaultBits = 0;
        TB_2.TCFaultBits = 0;
        TrustAll = FaultDetectEmpty;
        TrustHard = FaultDetectEmpty;
        TrustSens = FaultDetectEmpty;
        Ts2_0.TCFaultBits = 0;
        Ts2_1.TCFaultBits = 0;
        Tt4_0.TCFaultBits = 0;
        Tt4_1.TCFaultBits = 0;
        Tt4_2.TCFaultBits = 0;

        /* RESETS static int TYPE */

        CriticalFailure = 0;
        Current_key_start = 0;
        EmergencyCommand = 0;
        Old_key_start = 0;
        Reset = 0;
        ShutDownCommand = 0;
        StartCommand = 0;
        StartComplete = 0;
        StartFaultAnalysis = 0;

		/* RESETS floating TYPE */

		OPRPMManual = 0;

        /* RESETS static floating TYPE */

        Wf = 0;

		/*------------*/
		/* MODEL ONLY */
		/*------------*/

		/* RESETS STRUCTS */

        Bear0 = BearEmpty;
        Bear1 = BearEmpty;
        Bear2 = BearEmpty;
        EngOutput = EngOutputEmpty;
        EngPars = EngParsEmpty;
        SensorBias = SensorsEmpty;
        Starting = StartingEmpty;

		/* RESETS UNIONS */

        Faults = FaultEmpty;
        SensFaults = FaultSensEmpty;
        SysFaults = FaultDetectEmpty;

		/* RESETS int TYPE */

		digitalWord = 0;
		Ignition = 0;
		keysWord = 0;

		/* RESETS static int TYPE */

		bit_start = 0;
		Current_key_start = 0;
		OnOffCom= 0xFF;
		SkipStart = 0;

		/* RESETS floating TYPE*/

        Altitude = 0;
        BPFAN = 0;
        dT = 0;
        Fg = 0;
        Fn = 0;
        FNpc = 0;
        FNpc0 = 0;
        MN = 0;
        NcFAN = 0;
        NcHPC = 0;
        P0 = 101325;
        POil = 0;
        PRFAN = 0;
        PRHPC = 0;
        Pt2 = 101325;
        Pt21 = 0;
        Pt3 = 0;
        Pt4 = 0;
        Pt5 = 0;
        Pt6 = 0;
        RefCAN = 0;
        //reference = 0;
        RPM = 0;
        SMFAN = 0;
        SMHPC = 0;
        Tt2 = 288.25;
        Tt21 = 0;
        Tt3 = 0;
        Tt4 = 0;
        Tt5 = 0;
        Tt6 = 0;
        V8 = 0;
        W2 = 0;
        W21 = 0;
        W8 = 0;
        WcFAN = 0;
        WcHPC = 0;
        Wf0 = 0;

		/* RESETS static floating TYPE */

		fValue = 0;

/******** COMMENT START ********/
		/* -------------------------------------------------- */
        /* T-MATS & PWLM  RESETS                          */
        /* (To be usedi in MATLAB and TMATS simulations only) */
        /* -------------------------------------------------- */

		/* int TYPE */

		IgniterIn = 0;

		/* floating TYPE */

		FuelIn = 0;


        /* -------------------------------------------------- */
/******** COMMENT END ********/

	}

