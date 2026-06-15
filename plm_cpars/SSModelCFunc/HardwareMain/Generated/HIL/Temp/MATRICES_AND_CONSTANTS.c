
	/*-----------------------------------------------------------*/
	/* DEFINES MATRICES AND CONSTANTS DEPENDING ON CHOSEN ENGINE */
	/*-----------------------------------------------------------*/

	/* ENGINES TO BE SIMULATED */
	/*	WhichEngine == 1 -> TJ1200
		WhichEngine == 2 -> TF1200
		WhichEngine == 3 -> GEJ85
		WhichEngine == 4 -> TJ700
		WhichEngine == 5 -> TJ200
		WhichEngine == 6 -> TJ40
									*/
	if (WhichEngine == 1)
	{

		/* Loads the constants of chosen engine used by FADEC */
		getTJ1200FADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
							   &PowerMan_Elem, &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC);

		/* Loads the constants of chosen engine used by HIL */
		getTJ1200HILSizeConst(&NcFANMap_Elem, &WcFANMap_Elem, &Wc_per_Nc_FAN, &NcHPTMap_Elem, &PRHPTMap_Elem,
							 &WcHPTMap_Elem);

		/* Loads the constants of chosen engine */
		getTJ1200HILEngConst(&EngPars, &WfMax_Pump);

		/*Loads the controller starting parameters*/
		getTJ1200HILStartPars(&ContStart);
	}

	if (WhichEngine == 2)
	{

		/* Loads the constants of chosen engine used by FADEC */
		getTF1200FADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
							   &PowerMan_Elem, &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC);

		/* Loads the constants of chosen engine used by HIL */
		getTF1200HILSizeConst(&NcFANMap_Elem, &WcFANMap_Elem, &Wc_per_Nc_FAN, &NcHPTMap_Elem, &PRHPTMap_Elem,
							 &WcHPTMap_Elem);

		/* Loads the constants of chosen engine */
		getTF1200HILEngConst(&EngPars, &WfMax_Pump);

		/*Loads the controller starting parameters*/
		getTF1200HILStartPars(&ContStart);
	}

	if (WhichEngine == 3)
	{

		/* Loads the constants of chosen engine used by FADEC */
		getGEJ85FADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
							   &PowerMan_Elem, &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC);

		/* Loads the constants of chosen engine used by HIL */
		getGEJ85HILSizeConst(&NcFANMap_Elem, &WcFANMap_Elem, &Wc_per_Nc_FAN, &NcHPTMap_Elem, &PRHPTMap_Elem,
							 &WcHPTMap_Elem);

		/* Loads the constants of chosen engine */
		getGEJ85HILEngConst(&EngPars, &WfMax_Pump);

		/*Loads the controller starting parameters*/
		getGEJ85HILStartPars(&ContStart);
	}

	if (WhichEngine == 4)
	{

		/* Loads the constants of chosen engine used by FADEC */
		getTJ700FADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
							   &PowerMan_Elem, &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC);

		/* Loads the constants of chosen engine used by HIL */
		getTJ700HILSizeConst(&NcFANMap_Elem, &WcFANMap_Elem, &Wc_per_Nc_FAN, &NcHPTMap_Elem, &PRHPTMap_Elem,
							 &WcHPTMap_Elem);

		/* Loads the constants of chosen engine */
		getTJ700HILEngConst(&EngPars, &WfMax_Pump);

		/*Loads the controller starting parameters*/
		getTJ700HILStartPars(&ContStart);
	}

	if (WhichEngine == 5)
	{

		/* Loads the constants of chosen engine used by FADEC */
		getTJ200FADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
							   &PowerMan_Elem, &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC);

		/* Loads the constants of chosen engine used by HIL */
		getTJ200HILSizeConst(&NcFANMap_Elem, &WcFANMap_Elem, &Wc_per_Nc_FAN, &NcHPTMap_Elem, &PRHPTMap_Elem,
							 &WcHPTMap_Elem);

		/* Loads the constants of chosen engine */
		getTJ200HILEngConst(&EngPars, &WfMax_Pump);

		/*Loads the controller starting parameters*/
		getTJ200HILStartPars(&ContStart);
	}

	if (WhichEngine == 6)
	{

		/* Loads the constants of chosen engine used by FADEC */
		getTJ40FADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
							   &PowerMan_Elem, &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC);

		/* Loads the constants of chosen engine used by HIL */
		getTJ40HILSizeConst(&NcFANMap_Elem, &WcFANMap_Elem, &Wc_per_Nc_FAN, &NcHPTMap_Elem, &PRHPTMap_Elem,
							 &WcHPTMap_Elem);

		/* Loads the constants of chosen engine */
		getTJ40HILEngConst(&EngPars, &WfMax_Pump);

		/*Loads the controller starting parameters*/
		getTJ40HILStartPars(&ContStart);
	}

	/* Loads number of elements of engine matrices into struct to be used by EngineModel */
	EngPars.Alt_Elem = Alt_Elem;
	EngPars.MN_Elem = MN_Elem;
	EngPars.Fn_Elem = Fn_Elem;
	EngPars.NcFANMap_Elem = NcFANMap_Elem;
	EngPars.NcHPCMap_Elem = NcHPCMap_Elem;
	EngPars.NcHPTMap_Elem = NcHPTMap_Elem;
	EngPars.PowerMan_Elem = PowerMan_Elem;
	EngPars.PRHPTMap_Elem = PRHPTMap_Elem;
	EngPars.SteadyOp_Elem = SteadyOp_Elem;
	EngPars.WcFANMap_Elem = WcFANMap_Elem;
	EngPars.WcHPCMap_Elem = WcHPCMap_Elem;
	EngPars.WcHPTMap_Elem = WcHPTMap_Elem;

	/*----------------------------------------*/
	/* ALLOCATES MEMORY FOR ENGINE SIMULATION */
	/*----------------------------------------*/

	/* Veryfies if reset has not been requested and it is the first software run so malloc is not used more than once in a row */
	if (Reset == 0)
	{

		/* Matrices used for reference and gain calculations */
		N_KiMtx = 		 FADECMalloc(PowerMan_Elem, &MemSize);
		N_KishMtx = 	 FADECMalloc(PowerMan_Elem, &MemSize);
		N_KpMtx = 		 FADECMalloc(PowerMan_Elem, &MemSize);
		N_KpshMtx =      FADECMalloc(PowerMan_Elem, &MemSize);
		NcFANContMtx =   FADECMalloc(PowerMan_Elem, &MemSize);
		NcFANshContMtx = FADECMalloc(PowerMan_Elem, &MemSize);
		FNperContMtx =   FADECMalloc(PowerMan_Elem, &MemSize);
        FNcMaxContMtx =  FADECMalloc(MN_Elem, &MemSize);

		/* Matrices used for model calculations */
		NcMtx =          FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21Mtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21Mtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		WfMtx =          FADECMalloc(SteadyOp_Elem, &MemSize);
		AMtx =           FADECMalloc(SteadyOp_Elem, &MemSize);
		BMtx = 	         FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21DMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21DMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);

    	/* Matrices used for sub-idle calculations */
        AwmMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		AshMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
        BwmMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		BshMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
        RPMshMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		RPMwmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		NcFANshMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21shMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21wmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21DshMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21DwmMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21shMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21wmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21DshMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21DwmMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4CshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
    	Tt5shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
	    WfshMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		WfwmMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);

		/* Low Pressure Compressor or Fan */
		NcFANMapMtx =    FADECMalloc(NcFANMap_Elem, &MemSize);
		WcFANStallMtx =  FADECMalloc(NcFANMap_Elem, &MemSize);
		PRFANStallMtx =  FADECMalloc(NcFANMap_Elem, &MemSize);
		WcFANMapMtx =    FADECMalloc(WcFANMap_Elem, &MemSize);
		PRFANMapMtx =    FADECMalloc(WcFANMap_Elem, &MemSize);
		EffFANMapMtx =   FADECMalloc(WcFANMap_Elem, &MemSize);

		/* High Pressure Compressor */
		NcHPCMapMtx =    FADECMalloc(NcHPCMap_Elem, &MemSize);
		WcHPCStallMtx =  FADECMalloc(NcHPCMap_Elem, &MemSize);
		PRHPCStallMtx =  FADECMalloc(NcHPCMap_Elem, &MemSize);
		WcHPCMapMtx =    FADECMalloc(WcHPCMap_Elem, &MemSize);
		PRHPCMapMtx =    FADECMalloc(WcHPCMap_Elem, &MemSize);
		EffHPCMapMtx =   FADECMalloc(WcHPCMap_Elem, &MemSize);

		/* Turbine */
		NcHPTMapMtx =    FADECMalloc(NcHPTMap_Elem, &MemSize);
		WcHPTMapMtx =    FADECMalloc(WcHPTMap_Elem, &MemSize);
		EffHPTMapMtx =   FADECMalloc(WcHPTMap_Elem, &MemSize);
		PRHPTMapMtx =    FADECMalloc(PRHPTMap_Elem, &MemSize);

		/* Auxiliar matrices */
		Mtx2D = 		 FADECMalloc(MN_Elem * Fn_Elem, &MemSize);
		Mtx2DH = 		 FADECMalloc(MN_Elem * Fn_Elem, &MemSize);
		Mtx1D = 		 FADECMalloc(Fn_Elem, &MemSize);
		Mtx1DH = 		 FADECMalloc(Fn_Elem, &MemSize);

        DeltaMtx2D =     FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
		DeltaMtx2DH =    FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
		DeltaMtx1D =     FADECMalloc(MN_Elem, &MemSize);
		DeltaMtx1DH =    FADECMalloc(MN_Elem, &MemSize);

		Ts0Mtx2D =       FADECMalloc(Fn_Elem, &MemSize);
		Ts0Mtx2DH = 	 FADECMalloc(Fn_Elem, &MemSize);
		Ts0Mtx1D = 		 FADECMalloc(Alt_Elem, &MemSize);
		Ts0Mtx1DH = 	 FADECMalloc(Alt_Elem, &MemSize);

		MapFAN2D = 		 FADECMalloc(WcFANMap_Elem, &MemSize);
		MapFAN2DH = 	 FADECMalloc(WcFANMap_Elem, &MemSize);
		MapFAN1D = 		 FADECMalloc(Wc_per_Nc_FAN, &MemSize);
		MapFAN1DH = 	 FADECMalloc(Wc_per_Nc_FAN, &MemSize);

		MapHPC2D = 		 FADECMalloc(WcHPCMap_Elem, &MemSize);
		MapHPC2DH = 	 FADECMalloc(WcHPCMap_Elem, &MemSize);
		MapHPC1D = 		 FADECMalloc(Wc_per_Nc_HPC, &MemSize);
		MapHPC1DH = 	 FADECMalloc(Wc_per_Nc_HPC, &MemSize);

		/* MN linerizing vector */
		MNLinVec = 		 FADECMalloc(MN_Elem, &MemSize);
        AltLinVec = 	 FADECMalloc(Alt_Elem, &MemSize);
        DeltaMtx = 		 FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
		Ts0Mtx = 		 FADECMalloc(Alt_Elem * MN_Elem, &MemSize);

		/* Reference filter vectors */
		ASVec = 		 FADECMalloc(AS_Elem, &MemSize);
		DSVec = 		 FADECMalloc(AS_Elem, &MemSize);
		NcVec = 		 FADECMalloc(AS_Elem, &MemSize);

	}
	else
	{
		/* HARDWARE */
/******** UNCOMMENT START ********/
		// /* Matrices used for reference and gain calculations */
		// N_KiMtx = 	     FADECRealloc(N_KiMtx, PowerMan_Elem);
		// N_KishMtx = 	 FADECRealloc(N_KishMtx, PowerMan_Elem);
		// N_KpMtx = 	     FADECRealloc(N_KpMtx, PowerMan_Elem);
		// N_KpshMtx =      FADECRealloc(N_KpshMtx, PowerMan_Elem);
		// NcFANContMtx =   FADECRealloc(NcFANContMtx, PowerMan_Elem);
		// NcFANshContMtx = FADECRealloc(NcFANshContMtx, PowerMan_Elem);
		// FNperContMtx =   FADECRealloc(FNperContMtx, PowerMan_Elem);
		// FNcMaxContMtx =  FADECRealloc(FNcMaxContMtx, MN_Elem);

		// /* Matrices used for model calculations */
		// NcMtx = 		 FADECRealloc(NcMtx, SteadyOp_Elem);
		// Pt21Mtx = 	     FADECRealloc(Pt21Mtx, SteadyOp_Elem);
		// Pt3Mtx = 		 FADECRealloc(Pt3Mtx, SteadyOp_Elem);
		// Pt5Mtx = 		 FADECRealloc(Pt5Mtx, SteadyOp_Elem);
		// Pt6Mtx = 		 FADECRealloc(Pt6Mtx, SteadyOp_Elem);
		// Tt21Mtx = 	     FADECRealloc(Tt21Mtx, SteadyOp_Elem);
		// Tt3Mtx = 	     FADECRealloc(Tt3Mtx, SteadyOp_Elem);
		// Tt4Mtx = 	     FADECRealloc(Tt4Mtx, SteadyOp_Elem);
		// Tt5Mtx = 	     FADECRealloc(Tt5Mtx, SteadyOp_Elem);
		// Tt6Mtx = 	     FADECRealloc(Tt6Mtx, SteadyOp_Elem);
		// WfMtx = 	     FADECRealloc(WfMtx, SteadyOp_Elem);
		// AMtx = 		     FADECRealloc(AMtx, SteadyOp_Elem);
		// BMtx = 		     FADECRealloc(BMtx, SteadyOp_Elem);
		// Pt21DMtx = 	     FADECRealloc(Pt21DMtx, SteadyOp_Elem);
		// Pt3DMtx = 	     FADECRealloc(Pt3DMtx, SteadyOp_Elem);
		// Pt5DMtx = 	     FADECRealloc(Pt5DMtx, SteadyOp_Elem);
		// Pt6DMtx = 	     FADECRealloc(Pt6DMtx, SteadyOp_Elem);
		// Tt21DMtx = 	     FADECRealloc(Tt21DMtx, SteadyOp_Elem);
		// Tt3DMtx = 	     FADECRealloc(Tt3DMtx, SteadyOp_Elem);
		// Tt4DMtx = 	     FADECRealloc(Tt4DMtx, SteadyOp_Elem);
		// Tt5DMtx = 	     FADECRealloc(Tt5DMtx, SteadyOp_Elem);
		// Tt6DMtx = 	     FADECRealloc(Tt6DMtx, SteadyOp_Elem);

		// /* Matrices used for sub-idle calculations */
        // AwmMtx = 		 FADECRealloc(AwmMtx, SteadyOp_Elem);
		// AshMtx = 		 FADECRealloc(AshMtx, SteadyOp_Elem);
        // BwmMtx = 		 FADECRealloc(BwmMtx, SteadyOp_Elem);
		// BshMtx = 		 FADECRealloc(BshMtx, SteadyOp_Elem);
        // RPMshMtx = 	     FADECRealloc(RPMshMtx, SteadyOp_Elem);
		// RPMwmMtx = 	     FADECRealloc(RPMwmMtx, SteadyOp_Elem);
		// NcFANshMtx = 	 FADECRealloc(NcFANshMtx, SteadyOp_Elem);
		// Pt21shMtx = 	 FADECRealloc(Pt21shMtx, SteadyOp_Elem);
		// Pt21wmMtx = 	 FADECRealloc(Pt21wmMtx, SteadyOp_Elem);
		// Pt21DshMtx = 	 FADECRealloc(Pt21DshMtx, SteadyOp_Elem);
		// Pt21DwmMtx = 	 FADECRealloc(Pt21DwmMtx, SteadyOp_Elem);
		// Pt3shMtx = 	     FADECRealloc(Pt3shMtx, SteadyOp_Elem);
		// Pt3wmMtx = 	     FADECRealloc(Pt3wmMtx, SteadyOp_Elem);
		// Pt3DshMtx = 	 FADECRealloc(Pt3DshMtx, SteadyOp_Elem);
		// Pt3DwmMtx = 	 FADECRealloc(Pt3DwmMtx, SteadyOp_Elem);
		// Pt5shMtx = 	     FADECRealloc(Pt5shMtx, SteadyOp_Elem);
		// Pt5wmMtx = 	     FADECRealloc(Pt5wmMtx, SteadyOp_Elem);
		// Pt5DshMtx = 	 FADECRealloc(Pt5DshMtx, SteadyOp_Elem);
		// Pt5DwmMtx = 	 FADECRealloc(Pt5DwmMtx, SteadyOp_Elem);
		// Pt6shMtx = 	     FADECRealloc(Pt6shMtx, SteadyOp_Elem);
		// Pt6wmMtx = 	     FADECRealloc(Pt6wmMtx, SteadyOp_Elem);
		// Pt6DshMtx = 	 FADECRealloc(Pt6DshMtx, SteadyOp_Elem);
		// Pt6DwmMtx = 	 FADECRealloc(Pt6DwmMtx, SteadyOp_Elem);
		// Tt21shMtx = 	 FADECRealloc(Tt21shMtx, SteadyOp_Elem);
		// Tt21wmMtx = 	 FADECRealloc(Tt21wmMtx, SteadyOp_Elem);
		// Tt21DshMtx = 	 FADECRealloc(Tt21DshMtx, SteadyOp_Elem);
		// Tt21DwmMtx = 	 FADECRealloc(Tt21DwmMtx, SteadyOp_Elem);
		// Tt3shMtx = 	     FADECRealloc(Tt3shMtx, SteadyOp_Elem);
		// Tt3wmMtx = 	     FADECRealloc(Tt3wmMtx, SteadyOp_Elem);
		// Tt3DshMtx = 	 FADECRealloc(Tt3DshMtx, SteadyOp_Elem);
		// Tt3DwmMtx = 	 FADECRealloc(Tt3DwmMtx, SteadyOp_Elem);
		// Tt4shMtx = 	     FADECRealloc(Tt4shMtx, SteadyOp_Elem);
		// Tt4wmMtx = 	     FADECRealloc(Tt4wmMtx, SteadyOp_Elem);
		// Tt4CshMtx = 	 FADECRealloc(Tt4CshMtx, SteadyOp_Elem);
		// Tt4DshMtx = 	 FADECRealloc(Tt4DshMtx, SteadyOp_Elem);
		// Tt4DwmMtx = 	 FADECRealloc(Tt4DwmMtx, SteadyOp_Elem);
    	// Tt5shMtx = 	     FADECRealloc(Tt5shMtx, SteadyOp_Elem);
		// Tt5wmMtx = 	     FADECRealloc(Tt5wmMtx, SteadyOp_Elem);
		// Tt5DshMtx = 	 FADECRealloc(Tt5DshMtx, SteadyOp_Elem);
		// Tt5DwmMtx = 	 FADECRealloc(Tt5DwmMtx, SteadyOp_Elem);
		// Tt6shMtx = 	     FADECRealloc(Tt6shMtx, SteadyOp_Elem);
		// Tt6wmMtx = 	     FADECRealloc(Tt6wmMtx, SteadyOp_Elem);
		// Tt6DshMtx = 	 FADECRealloc(Tt6DshMtx, SteadyOp_Elem);
		// Tt6DwmMtx = 	 FADECRealloc(Tt6DwmMtx, SteadyOp_Elem);
	    // WfshMtx = 	     FADECRealloc(WfshMtx, SteadyOp_Elem);
		// WfwmMtx = 	     FADECRealloc(WfwmMtx, SteadyOp_Elem);

		// /* Low Pressure Compressor or Fan */
		// NcFANMapMtx =    FADECRealloc(NcFANMapMtx, NcFANMap_Elem);
		// WcFANStallMtx =  FADECRealloc(WcFANStallMtx, NcFANMap_Elem);
		// PRFANStallMtx =  FADECRealloc(PRFANStallMtx, NcFANMap_Elem);
		// WcFANMapMtx =    FADECRealloc(WcFANMapMtx, WcFANMap_Elem);
		// PRFANMapMtx =    FADECRealloc(PRFANMapMtx, WcFANMap_Elem);
		// EffFANMapMtx =   FADECRealloc(EffFANMapMtx, WcFANMap_Elem);

		// /* High Pressure Compressor */
		// NcHPCMapMtx =    FADECRealloc(NcHPCMapMtx, NcHPCMap_Elem);
		// WcHPCStallMtx =  FADECRealloc(WcHPCStallMtx, NcHPCMap_Elem);
		// PRHPCStallMtx =  FADECRealloc(PRHPCStallMtx, NcHPCMap_Elem);
		// WcHPCMapMtx =    FADECRealloc(WcHPCMapMtx, WcHPCMap_Elem);
		// PRHPCMapMtx =    FADECRealloc(PRHPCMapMtx, WcHPCMap_Elem);
		// EffHPCMapMtx =   FADECRealloc(EffHPCMapMtx, WcHPCMap_Elem);

		// /* Turbine */
		// NcHPTMapMtx =    FADECRealloc(NcHPTMapMtx, NcHPTMap_Elem);
		// WcHPTMapMtx =    FADECRealloc(WcHPTMapMtx, WcHPTMap_Elem);
		// EffHPTMapMtx =   FADECRealloc(EffHPTMapMtx, WcHPTMap_Elem);
		// PRHPTMapMtx =    FADECRealloc(PRHPTMapMtx, PRHPTMap_Elem);

	   	// /* Auxiliar matrices */
		// Mtx2D = 		 FADECRealloc(Mtx2D, MN_Elem * Fn_Elem);
		// Mtx2DH = 		 FADECRealloc(Mtx2DH, MN_Elem * Fn_Elem);
		// Mtx1D = 		 FADECRealloc(Mtx1D, Fn_Elem);
		// Mtx1DH = 		 FADECRealloc(Mtx1DH, Fn_Elem);

	    // DeltaMtx2D = 	 FADECRealloc(DeltaMtx2D, Alt_Elem * MN_Elem);
		// DeltaMtx2DH =    FADECRealloc(DeltaMtx2DH, Alt_Elem * MN_Elem);
		// DeltaMtx1D = 	 FADECRealloc(DeltaMtx1D, MN_Elem);
		// DeltaMtx1DH =    FADECRealloc(DeltaMtx1DH, MN_Elem);

		// Ts0Mtx2D = 	     FADECRealloc(Ts0Mtx2D, Fn_Elem);
		// Ts0Mtx2DH = 	 FADECRealloc(Ts0Mtx2DH, Fn_Elem);
		// Ts0Mtx1D = 	     FADECRealloc(Ts0Mtx1D, Alt_Elem);
		// Ts0Mtx1DH = 	 FADECRealloc(Ts0Mtx1DH, Alt_Elem);

		// MapFAN2D = 	     FADECRealloc(MapFAN2D, WcFANMap_Elem);
		// MapFAN2DH = 	 FADECRealloc(MapFAN2DH, WcFANMap_Elem);
		// MapFAN1D = 	     FADECRealloc(MapFAN1D, Wc_per_Nc_FAN);
		// MapFAN1DH = 	 FADECRealloc(MapFAN1DH, Wc_per_Nc_FAN);

		// MapHPC2D = 	     FADECRealloc(MapHPC2D, WcHPCMap_Elem);
		// MapHPC2DH = 	 FADECRealloc(MapHPC2DH, WcHPCMap_Elem);
		// MapHPC1D = 	     FADECRealloc(MapHPC1D, Wc_per_Nc_HPC);
		// MapHPC1DH = 	 FADECRealloc(MapHPC1DH, Wc_per_Nc_HPC);

		// /* MN linerizing vector */
		// MNLinVec = 	     FADECRealloc(MNLinVec, MN_Elem);
        // AltLinVec = 	 FADECRealloc(AltLinVec, Alt_Elem);
        // DeltaMtx = 	     FADECRealloc(DeltaMtx, Alt_Elem * MN_Elem);
		// Ts0Mtx = 		 FADECRealloc(Ts0Mtx, Alt_Elem * MN_Elem);

		// /* Reference filter vectors */
		// ASVec = 		 FADECRealloc(ASVec, AS_Elem);
		// DSVec = 		 FADECRealloc(DSVec, AS_Elem);
		// NcVec = 		 FADECRealloc(NcVec, AS_Elem);

/******** UNCOMMENT END ********/

/******** EXCLUDE START ********/
		///* Matrices used for reference and gain calculations */
		//N_KiMtx = 	   (floating *)realloc(N_KiMtx,PowerMan_Elem * sizeof(floating));
		//N_KishMtx = 	   (floating *)realloc(N_KiMtx,PowerMan_Elem * sizeof(floating));
		//N_KpMtx = 	   (floating *)realloc(N_KpMtx,PowerMan_Elem * sizeof(floating));
		//N_KpshMtx =      (floating *)realloc(N_KpMtx,PowerMan_Elem * sizeof(floating));
		//NcFANContMtx =   (floating *)realloc(NcFANContMtx,PowerMan_Elem * sizeof(floating));
		//NcFANshContMtx = (floating *)realloc(NcFANContMtx,PowerMan_Elem * sizeof(floating));
		//FNperContMtx =   (floating *)realloc(FNperContMtx,PowerMan_Elem * sizeof(floating));
        //FNcMaxContMtx =  (floating *)realloc(FNcMaxContMtx,MN_Elem * sizeof(floating));

		///* Matrices used for model calculations */
		//NcMtx = 		   (floating *)realloc(NcMtx,SteadyOp_Elem * sizeof(floating));
		//Pt21Mtx = 	   (floating *)realloc(Pt21Mtx,SteadyOp_Elem * sizeof(floating));
		//Pt3Mtx = 		   (floating *)realloc(Pt3Mtx,SteadyOp_Elem * sizeof(floating));
		//Pt5Mtx = 		   (floating *)realloc(Pt5Mtx,SteadyOp_Elem * sizeof(floating));
		//Pt6Mtx = 		   (floating *)realloc(Pt6Mtx,SteadyOp_Elem * sizeof(floating));
		//Tt21Mtx = 	   (floating *)realloc(Tt21Mtx,SteadyOp_Elem * sizeof(floating));
		//Tt3Mtx = 		   (floating *)realloc(Tt3Mtx,SteadyOp_Elem * sizeof(floating));
		//Tt4Mtx = 		   (floating *)realloc(Tt4Mtx,SteadyOp_Elem * sizeof(floating));
		//Tt5Mtx = 		   (floating *)realloc(Tt5Mtx,SteadyOp_Elem * sizeof(floating));
		//Tt6Mtx = 		   (floating *)realloc(Tt6Mtx,SteadyOp_Elem * sizeof(floating));
		//WfMtx = 		   (floating *)realloc(WfMtx,SteadyOp_Elem * sizeof(floating));
		//AMtx = 		   (floating *)realloc(AMtx,SteadyOp_Elem * sizeof(floating));
		//BMtx = 		   (floating *)realloc(BMtx,SteadyOp_Elem * sizeof(floating));
		//Pt21DMtx = 	   (floating *)realloc(Pt21DMtx,SteadyOp_Elem * sizeof(floating));
		//Pt3DMtx = 	   (floating *)realloc(Pt3DMtx,SteadyOp_Elem * sizeof(floating));
		//Pt5DMtx = 	   (floating *)realloc(Pt5DMtx,SteadyOp_Elem * sizeof(floating));
		//Pt6DMtx = 	   (floating *)realloc(Pt6DMtx,SteadyOp_Elem * sizeof(floating));
		//Tt21DMtx = 	   (floating *)realloc(Tt21DMtx,SteadyOp_Elem * sizeof(floating));
		//Tt3DMtx = 	   (floating *)realloc(Tt3DMtx,SteadyOp_Elem * sizeof(floating));
		//Tt4DMtx = 	   (floating *)realloc(Tt4DMtx,SteadyOp_Elem * sizeof(floating));
		//Tt5DMtx = 	   (floating *)realloc(Tt5DMtx,SteadyOp_Elem * sizeof(floating));
		//Tt6DMtx = 	   (floating *)realloc(Tt6DMtx,SteadyOp_Elem * sizeof(floating));

		///* Matrices used for sub-idle calculations */
        //AwmMtx = 		   (floating *)realloc(AwmMtx,SteadyOp_Elem * sizeof(floating));
		//AshMtx = 		   (floating *)realloc(AshMtx,SteadyOp_Elem * sizeof(floating));
        //BwmMtx = 		   (floating *)realloc(BwmMtx,SteadyOp_Elem * sizeof(floating));
		//BshMtx = 		   (floating *)realloc(BshMtx,SteadyOp_Elem * sizeof(floating));
        //RPMshMtx = 	   (floating *)realloc(RPMshMtx,SteadyOp_Elem * sizeof(floating));
		//RPMwmMtx = 	   (floating *)realloc(RPMwmMtx,SteadyOp_Elem * sizeof(floating));
		//NcFANshMtx = 	   (floating *)realloc(NcFANshMtx,SteadyOp_Elem * sizeof(floating));
		//Pt21shMtx = 	   (floating *)realloc(Pt21shMtx,SteadyOp_Elem * sizeof(floating));
		//Pt21wmMtx = 	   (floating *)realloc(Pt21wmMtx,SteadyOp_Elem * sizeof(floating));
		//Pt21DshMtx = 	   (floating *)realloc(Pt21DshMtx,SteadyOp_Elem * sizeof(floating));
		//Pt21DwmMtx = 	   (floating *)realloc(Pt21DwmMtx,SteadyOp_Elem * sizeof(floating));
		//Pt3shMtx = 	   (floating *)realloc(Pt3shMtx,SteadyOp_Elem * sizeof(floating));
		//Pt3wmMtx = 	   (floating *)realloc(Pt3wmMtx,SteadyOp_Elem * sizeof(floating));
		//Pt3DshMtx = 	   (floating *)realloc(Pt3DshMtx,SteadyOp_Elem * sizeof(floating));
		//Pt3DwmMtx = 	   (floating *)realloc(Pt3DwmMtx,SteadyOp_Elem * sizeof(floating));
		//Pt5shMtx = 	   (floating *)realloc(Pt5shMtx,SteadyOp_Elem * sizeof(floating));
		//Pt5wmMtx = 	   (floating *)realloc(Pt5wmMtx,SteadyOp_Elem * sizeof(floating));
		//Pt5DshMtx = 	   (floating *)realloc(Pt5DshMtx,SteadyOp_Elem * sizeof(floating));
		//Pt5DwmMtx = 	   (floating *)realloc(Pt5DwmMtx,SteadyOp_Elem * sizeof(floating));
		//Pt6shMtx = 	   (floating *)realloc(Pt6shMtx,SteadyOp_Elem * sizeof(floating));
		//Pt6wmMtx = 	   (floating *)realloc(Pt6wmMtx,SteadyOp_Elem * sizeof(floating));
		//Pt6DshMtx = 	   (floating *)realloc(Pt6DshMtx,SteadyOp_Elem * sizeof(floating));
		//Pt6DwmMtx = 	   (floating *)realloc(Pt6DwmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt21shMtx = 	   (floating *)realloc(Tt21shMtx,SteadyOp_Elem * sizeof(floating));
		//Tt21wmMtx = 	   (floating *)realloc(Tt21wmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt21DshMtx = 	   (floating *)realloc(Tt21DshMtx,SteadyOp_Elem * sizeof(floating));
		//Tt21DwmMtx = 	   (floating *)realloc(Tt21DwmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt3shMtx = 	   (floating *)realloc(Tt3shMtx,SteadyOp_Elem * sizeof(floating));
		//Tt3wmMtx = 	   (floating *)realloc(Tt3wmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt3DshMtx = 	   (floating *)realloc(Tt3DshMtx,SteadyOp_Elem * sizeof(floating));
		//Tt3DwmMtx = 	   (floating *)realloc(Tt3DwmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt4shMtx = 	   (floating *)realloc(Tt4shMtx,SteadyOp_Elem * sizeof(floating));
		//Tt4wmMtx = 	   (floating *)realloc(Tt4wmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt4CshMtx = 	   (floating *)realloc(Tt4CshMtx,SteadyOp_Elem * sizeof(floating));
		//Tt4DshMtx = 	   (floating *)realloc(Tt4DshMtx,SteadyOp_Elem * sizeof(floating));
		//Tt4DwmMtx = 	   (floating *)realloc(Tt4DwmMtx,SteadyOp_Elem * sizeof(floating));
    	//Tt5shMtx = 	   (floating *)realloc(Tt5shMtx,SteadyOp_Elem * sizeof(floating));
		//Tt5wmMtx = 	   (floating *)realloc(Tt5wmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt5DshMtx = 	   (floating *)realloc(Tt5DshMtx,SteadyOp_Elem * sizeof(floating));
		//Tt5DwmMtx = 	   (floating *)realloc(Tt5DwmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt6shMtx = 	   (floating *)realloc(Tt6shMtx,SteadyOp_Elem * sizeof(floating));
		//Tt6wmMtx = 	   (floating *)realloc(Tt6wmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt6DshMtx = 	   (floating *)realloc(Tt6DshMtx,SteadyOp_Elem * sizeof(floating));
		//Tt6DwmMtx = 	   (floating *)realloc(Tt6DwmMtx,SteadyOp_Elem * sizeof(floating));
	    //WfshMtx = 	   (floating *)realloc(WfshMtx,SteadyOp_Elem * sizeof(floating));
		//WfwmMtx = 	   (floating *)realloc(WfwmMtx,SteadyOp_Elem * sizeof(floating));


		///* Low Pressure Compressor or Fan */
		//NcFANMapMtx =    (floating *)realloc(NcFANMapMtx,NcFANMap_Elem * sizeof(floating));
		//WcFANStallMtx =  (floating *)realloc(WcFANStallMtx,NcFANMap_Elem * sizeof(floating));
		//PRFANStallMtx =  (floating *)realloc(PRFANStallMtx,NcFANMap_Elem * sizeof(floating));
		//WcFANMapMtx =    (floating *)realloc(WcFANMapMtx,WcFANMap_Elem * sizeof(floating));
		//PRFANMapMtx =    (floating *)realloc(PRFANMapMtx,WcFANMap_Elem * sizeof(floating));
		//EffFANMapMtx =   (floating *)realloc(EffFANMapMtx,WcFANMap_Elem * sizeof(floating));

		///* High Pressure Compressor */
		//NcHPCMapMtx =    (floating *)realloc(NcHPCMapMtx,NcHPCMap_Elem * sizeof(floating));
		//WcHPCStallMtx =  (floating *)realloc(WcHPCStallMtx,NcHPCMap_Elem * sizeof(floating));
		//PRHPCStallMtx =  (floating *)realloc(PRHPCStallMtx,NcHPCMap_Elem * sizeof(floating));
		//WcHPCMapMtx =    (floating *)realloc(WcHPCMapMtx,WcHPCMap_Elem * sizeof(floating));
		//PRHPCMapMtx =    (floating *)realloc(PRHPCMapMtx,WcHPCMap_Elem * sizeof(floating));
		//EffHPCMapMtx =   (floating *)realloc(EffHPCMapMtx,WcHPCMap_Elem * sizeof(floating));

		///* Turbine */
		//NcHPTMapMtx =    (floating *)realloc(NcHPTMapMtx,NcHPTMap_Elem * sizeof(floating));
		//WcHPTMapMtx =    (floating *)realloc(WcHPTMapMtx,WcHPTMap_Elem * sizeof(floating));
		//EffHPTMapMtx =   (floating *)realloc(EffHPTMapMtx,WcHPTMap_Elem * sizeof(floating));
		//PRHPTMapMtx =    (floating *)realloc(PRHPTMapMtx,PRHPTMap_Elem * sizeof(floating));

	   	///* Auxiliar matrices */
		//Mtx2D = 		   (floating *)realloc(Mtx2D,MN_Elem * Fn_Elem * sizeof(floating));
		//Mtx2DH = 		   (floating *)realloc(Mtx2DH,MN_Elem * Fn_Elem * sizeof(floating));
		//Mtx1D = 		   (floating *)realloc(Mtx1D,Fn_Elem * sizeof(floating));
		//Mtx1DH = 		   (floating *)realloc(Mtx1DH,Fn_Elem * sizeof(floating));

	    //DeltaMtx2D = 	   (floating *)realloc(DeltaMtx2D,Alt_Elem * MN_Elem * sizeof(floating));
		//DeltaMtx2DH =    (floating *)realloc(DeltaMtx2DH,Alt_Elem * MN_Elem * sizeof(floating));
		//DeltaMtx1D = 	   (floating *)realloc(DeltaMtx1D,MN_Elem * sizeof(floating));
		//DeltaMtx1DH =    (floating *)realloc(DeltaMtx1DH,MN_Elem * sizeof(floating));

		//Ts0Mtx2D = 	   (floating *)realloc(Ts0Mtx2D,Fn_Elem * sizeof(floating));
		//Ts0Mtx2DH = 	   (floating *)realloc(Ts0Mtx2DH,Fn_Elem * sizeof(floating));
		//Ts0Mtx1D = 	   (floating *)realloc(Ts0Mtx1D,Alt_Elem * sizeof(floating));
		//Ts0Mtx1DH = 	   (floating *)realloc(Ts0Mtx1DH,Alt_Elem * sizeof(floating));

		//MapFAN2D = 	   (floating *)realloc(MapFAN2D,WcFANMap_Elem * sizeof(floating));
		//MapFAN2DH = 	   (floating *)realloc(MapFAN2DH,WcFANMap_Elem * sizeof(floating));
		//MapFAN1D = 	   (floating *)realloc(MapFAN1D,Wc_per_Nc_FAN * sizeof(floating));
		//MapFAN1DH = 	   (floating *)realloc(MapFAN1DH,Wc_per_Nc_FAN * sizeof(floating));

		//MapHPC2D = 	   (floating *)realloc(MapHPC2D,WcHPCMap_Elem * sizeof(floating));
		//MapHPC2DH = 	   (floating *)realloc(MapHPC2DH,WcHPCMap_Elem * sizeof(floating));
		//MapHPC1D = 	   (floating *)realloc(MapHPC1D,Wc_per_Nc_HPC * sizeof(floating));
		//MapHPC1DH = 	   (floating *)realloc(MapHPC1DH,Wc_per_Nc_HPC * sizeof(floating));

		///* MN linerizing vector */
		//MNLinVec = 	   (floating *)realloc(MNLinVec,MN_Elem * sizeof(floating));
        //AltLinVec = 	   (floating *)realloc(AltLinVec,Alt_Elem * sizeof(floating));
        //DeltaMtx = 	   (floating *)realloc(DeltaMtx,Alt_Elem * MN_Elem * sizeof(floating));
		//Ts0Mtx = 		   (floating *)realloc(Ts0Mtx,Alt_Elem * MN_Elem * sizeof(floating));

		///* Reference filter vectors */
		//ASVec = 		   (floating *)realloc(ASVec,AS_Elem * sizeof(floating));
		//DSVec = 		   (floating *)realloc(DSVec,AS_Elem * sizeof(floating));
		//NcVec = 		   (floating *)realloc(NcVec,AS_Elem * sizeof(floating));

/******** EXCLUDE END ********/

/******** EXCLUDE START ********/
		/* -------------------------------------------------- */
        /* REALLOCKING MEMORY - PWLM                          */
        /* (To be usedi in MATLAB (PWLM) simulations only)    */
        /* -------------------------------------------------- */

		/* Matrices used for reference and gain calculations */
		N_KiMtx = 		 FADECMalloc(PowerMan_Elem, &MemSize);
		N_KishMtx = 	 FADECMalloc(PowerMan_Elem, &MemSize);
		N_KpMtx = 		 FADECMalloc(PowerMan_Elem, &MemSize);
		N_KpshMtx =      FADECMalloc(PowerMan_Elem, &MemSize);
		NcFANContMtx =   FADECMalloc(PowerMan_Elem, &MemSize);
		NcFANshContMtx = FADECMalloc(PowerMan_Elem, &MemSize);
		FNperContMtx =   FADECMalloc(PowerMan_Elem, &MemSize);
        FNcMaxContMtx =  FADECMalloc(MN_Elem, &MemSize);

		/* Matrices used for model calculations */
		NcMtx =          FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21Mtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21Mtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		WfMtx =          FADECMalloc(SteadyOp_Elem, &MemSize);
		AMtx =           FADECMalloc(SteadyOp_Elem, &MemSize);
		BMtx = 	         FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21DMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21DMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);

    	/* Matrices used for sub-idle calculations */
        AwmMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		AshMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
        BwmMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		BshMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
        RPMshMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		RPMwmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		NcFANshMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21shMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21wmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21DshMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21DwmMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21shMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21wmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21DshMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21DwmMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4CshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
    	Tt5shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
	    WfshMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		WfwmMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);

		/* Low Pressure Compressor or Fan */
		NcFANMapMtx =    FADECMalloc(NcFANMap_Elem, &MemSize);
		WcFANStallMtx =  FADECMalloc(NcFANMap_Elem, &MemSize);
		PRFANStallMtx =  FADECMalloc(NcFANMap_Elem, &MemSize);
		WcFANMapMtx =    FADECMalloc(WcFANMap_Elem, &MemSize);
		PRFANMapMtx =    FADECMalloc(WcFANMap_Elem, &MemSize);
		EffFANMapMtx =   FADECMalloc(WcFANMap_Elem, &MemSize);

		/* High Pressure Compressor */
		NcHPCMapMtx =    FADECMalloc(NcHPCMap_Elem, &MemSize);
		WcHPCStallMtx =  FADECMalloc(NcHPCMap_Elem, &MemSize);
		PRHPCStallMtx =  FADECMalloc(NcHPCMap_Elem, &MemSize);
		WcHPCMapMtx =    FADECMalloc(WcHPCMap_Elem, &MemSize);
		PRHPCMapMtx =    FADECMalloc(WcHPCMap_Elem, &MemSize);
		EffHPCMapMtx =   FADECMalloc(WcHPCMap_Elem, &MemSize);

		/* Turbine */
		NcHPTMapMtx =    FADECMalloc(NcHPTMap_Elem, &MemSize);
		WcHPTMapMtx =    FADECMalloc(WcHPTMap_Elem, &MemSize);
		EffHPTMapMtx =   FADECMalloc(WcHPTMap_Elem, &MemSize);
		PRHPTMapMtx =    FADECMalloc(PRHPTMap_Elem, &MemSize);

		/* Auxiliar matrices */
		Mtx2D = 		 FADECMalloc(MN_Elem * Fn_Elem, &MemSize);
		Mtx2DH = 		 FADECMalloc(MN_Elem * Fn_Elem, &MemSize);
		Mtx1D = 		 FADECMalloc(Fn_Elem, &MemSize);
		Mtx1DH = 		 FADECMalloc(Fn_Elem, &MemSize);

        DeltaMtx2D =     FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
		DeltaMtx2DH =    FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
		DeltaMtx1D =     FADECMalloc(MN_Elem, &MemSize);
		DeltaMtx1DH =    FADECMalloc(MN_Elem, &MemSize);

		Ts0Mtx2D =       FADECMalloc(Fn_Elem, &MemSize);
		Ts0Mtx2DH = 	 FADECMalloc(Fn_Elem, &MemSize);
		Ts0Mtx1D = 		 FADECMalloc(Alt_Elem, &MemSize);
		Ts0Mtx1DH = 	 FADECMalloc(Alt_Elem, &MemSize);

		MapFAN2D = 		 FADECMalloc(WcFANMap_Elem, &MemSize);
		MapFAN2DH = 	 FADECMalloc(WcFANMap_Elem, &MemSize);
		MapFAN1D = 		 FADECMalloc(Wc_per_Nc_FAN, &MemSize);
		MapFAN1DH = 	 FADECMalloc(Wc_per_Nc_FAN, &MemSize);

		MapHPC2D = 		 FADECMalloc(WcHPCMap_Elem, &MemSize);
		MapHPC2DH = 	 FADECMalloc(WcHPCMap_Elem, &MemSize);
		MapHPC1D = 		 FADECMalloc(Wc_per_Nc_HPC, &MemSize);
		MapHPC1DH = 	 FADECMalloc(Wc_per_Nc_HPC, &MemSize);

		/* MN linerizing vector */
		MNLinVec = 		 FADECMalloc(MN_Elem, &MemSize);
        AltLinVec = 	 FADECMalloc(Alt_Elem, &MemSize);
        DeltaMtx = 		 FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
		Ts0Mtx = 		 FADECMalloc(Alt_Elem * MN_Elem, &MemSize);

		/* Reference filter vectors */
		ASVec = 		 FADECMalloc(AS_Elem, &MemSize);
		DSVec = 		 FADECMalloc(AS_Elem, &MemSize);
		NcVec = 		 FADECMalloc(AS_Elem, &MemSize);

        /* -------------------------------------------------- */
/******** EXCLUDE END ********/

	}

	/*----------------------------------*/
	/* UPDATES ENGINE MATRICES ELEMENTS */
	/*----------------------------------*/

	if (WhichEngine == 1)
	{

		/* Loads FADEC matrices */
		getTJ1200FADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
						  DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
						  N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
						  Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
						  Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
						  WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);

		/* Loads HIL matrices */
		getTJ1200HILMtx(AshMtx, AwmMtx, BshMtx, BwmMtx, EffFANMapMtx,
						EffHPCMapMtx, EffHPTMapMtx, NcFANMapMtx, NcHPTMapMtx, NcMtx,
						PRFANMapMtx, PRFANStallMtx, PRHPCStallMtx, PRHPTMapMtx, Pt21DMtx,
						Pt21Mtx, Pt6DMtx, Pt6Mtx, RPMshMtx, RPMwmMtx,
						Tt21DMtx, Tt21Mtx, Tt3DMtx, Tt3Mtx, Tt4CshMtx,
						Tt4DshMtx, Tt4shMtx, Tt6DMtx, Tt6Mtx, WcFANMapMtx,
						WcFANStallMtx, WcHPCStallMtx, WcHPTMapMtx, WfshMtx, NcFANshMtx,
						WfwmMtx, Pt3shMtx, Pt3DshMtx, Pt21wmMtx, Pt21DwmMtx,
						Pt3wmMtx, Pt3DwmMtx, Pt5wmMtx, Pt5DwmMtx, Pt6wmMtx,
						Pt6DwmMtx, Tt21wmMtx, Tt21DwmMtx, Tt3wmMtx, Tt3DwmMtx,
						Tt4wmMtx, Tt4DwmMtx, Tt5wmMtx, Tt5DwmMtx, Tt6wmMtx,
						Tt6DwmMtx, Pt21shMtx, Pt21DshMtx, Pt5shMtx, Pt5DshMtx,
						Pt6shMtx, Pt6DshMtx, Tt21shMtx, Tt21DshMtx, Tt3shMtx,
						Tt3DshMtx, Tt5shMtx, Tt5DshMtx, Tt6shMtx, Tt6DshMtx);

		/* Loads controller constants */
    	getTJ1200FADECContConst(&ContConst);

	}

	if (WhichEngine == 2)
	{

		/* Loads FADEC matrices */
		getTF1200FADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
						  DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
						  N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
						  Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
						  Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
						  WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);


		/* Loads HIL matrices */
		getTF1200HILMtx(AshMtx, AwmMtx, BshMtx, BwmMtx, EffFANMapMtx,
						EffHPCMapMtx, EffHPTMapMtx, NcFANMapMtx, NcHPTMapMtx, NcMtx,
						PRFANMapMtx, PRFANStallMtx, PRHPCStallMtx, PRHPTMapMtx, Pt21DMtx,
						Pt21Mtx, Pt6DMtx, Pt6Mtx, RPMshMtx, RPMwmMtx,
						Tt21DMtx, Tt21Mtx, Tt3DMtx, Tt3Mtx, Tt4CshMtx,
						Tt4DshMtx, Tt4shMtx, Tt6DMtx, Tt6Mtx, WcFANMapMtx,
						WcFANStallMtx, WcHPCStallMtx, WcHPTMapMtx, WfshMtx, NcFANshMtx,
						WfwmMtx, Pt3shMtx, Pt3DshMtx, Pt21wmMtx, Pt21DwmMtx,
						Pt3wmMtx, Pt3DwmMtx, Pt5wmMtx, Pt5DwmMtx, Pt6wmMtx,
						Pt6DwmMtx, Tt21wmMtx, Tt21DwmMtx, Tt3wmMtx, Tt3DwmMtx,
						Tt4wmMtx, Tt4DwmMtx, Tt5wmMtx, Tt5DwmMtx, Tt6wmMtx,
						Tt6DwmMtx, Pt21shMtx, Pt21DshMtx, Pt5shMtx, Pt5DshMtx,
						Pt6shMtx, Pt6DshMtx, Tt21shMtx, Tt21DshMtx, Tt3shMtx,
						Tt3DshMtx, Tt5shMtx, Tt5DshMtx, Tt6shMtx, Tt6DshMtx);

		/* Loads controller constants */
		getTF1200FADECContConst(&ContConst);

    }

	if (WhichEngine == 3)
	{

		/* Loads FADEC matrices */
		getGEJ85FADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
						  DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
						  N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
						  Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
						  Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
						  WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);

		/* Loads HIL matrices */
		getGEJ85HILMtx(AshMtx, AwmMtx, BshMtx, BwmMtx, EffFANMapMtx,
					   EffHPCMapMtx, EffHPTMapMtx, NcFANMapMtx, NcHPTMapMtx, NcMtx,
					   PRFANMapMtx, PRFANStallMtx, PRHPCStallMtx, PRHPTMapMtx, Pt21DMtx,
					   Pt21Mtx, Pt6DMtx, Pt6Mtx, RPMshMtx, RPMwmMtx,
					   Tt21DMtx, Tt21Mtx, Tt3DMtx, Tt3Mtx, Tt4CshMtx,
					   Tt4DshMtx, Tt4shMtx, Tt6DMtx, Tt6Mtx, WcFANMapMtx,
					   WcFANStallMtx, WcHPCStallMtx, WcHPTMapMtx, WfshMtx, NcFANshMtx,
					   WfwmMtx, Pt3shMtx, Pt3DshMtx, Pt21wmMtx, Pt21DwmMtx,
					   Pt3wmMtx, Pt3DwmMtx, Pt5wmMtx, Pt5DwmMtx, Pt6wmMtx,
					   Pt6DwmMtx, Tt21wmMtx, Tt21DwmMtx, Tt3wmMtx, Tt3DwmMtx,
					   Tt4wmMtx, Tt4DwmMtx, Tt5wmMtx, Tt5DwmMtx, Tt6wmMtx,
					   Tt6DwmMtx, Pt21shMtx, Pt21DshMtx, Pt5shMtx, Pt5DshMtx,
					   Pt6shMtx, Pt6DshMtx, Tt21shMtx, Tt21DshMtx, Tt3shMtx,
					   Tt3DshMtx, Tt5shMtx, Tt5DshMtx, Tt6shMtx, Tt6DshMtx);

		/* Loads controller constants */
		getGEJ85FADECContConst(&ContConst);
    }

	if (WhichEngine == 4)
	{

		/* Loads FADEC matrices */
		getTJ700FADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
						  DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
						  N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
						  Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
						  Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
						  WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);

		/* Loads HIL matrices */
		getTJ700HILMtx(AshMtx, AwmMtx, BshMtx, BwmMtx, EffFANMapMtx,
					   EffHPCMapMtx, EffHPTMapMtx, NcFANMapMtx, NcHPTMapMtx, NcMtx,
					   PRFANMapMtx, PRFANStallMtx, PRHPCStallMtx, PRHPTMapMtx, Pt21DMtx,
					   Pt21Mtx, Pt6DMtx, Pt6Mtx, RPMshMtx, RPMwmMtx,
					   Tt21DMtx, Tt21Mtx, Tt3DMtx, Tt3Mtx, Tt4CshMtx,
					   Tt4DshMtx, Tt4shMtx, Tt6DMtx, Tt6Mtx, WcFANMapMtx,
					   WcFANStallMtx, WcHPCStallMtx, WcHPTMapMtx, WfshMtx, NcFANshMtx,
					   WfwmMtx, Pt3shMtx, Pt3DshMtx, Pt21wmMtx, Pt21DwmMtx,
					   Pt3wmMtx, Pt3DwmMtx, Pt5wmMtx, Pt5DwmMtx, Pt6wmMtx,
					   Pt6DwmMtx, Tt21wmMtx, Tt21DwmMtx, Tt3wmMtx, Tt3DwmMtx,
					   Tt4wmMtx, Tt4DwmMtx, Tt5wmMtx, Tt5DwmMtx, Tt6wmMtx,
					   Tt6DwmMtx, Pt21shMtx, Pt21DshMtx, Pt5shMtx, Pt5DshMtx,
					   Pt6shMtx, Pt6DshMtx, Tt21shMtx, Tt21DshMtx, Tt3shMtx,
					   Tt3DshMtx, Tt5shMtx, Tt5DshMtx, Tt6shMtx, Tt6DshMtx);

		/* Loads controller constants */
		getTJ700FADECContConst(&ContConst);
    }

	if (WhichEngine == 5)
	{

		/* Loads FADEC matrices */
		getTJ200FADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
						 DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
						 N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
						 Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
						 Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
						 WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);

		/* Loads HIL matrices */
		getTJ200HILMtx(AshMtx, AwmMtx, BshMtx, BwmMtx, EffFANMapMtx,
					   EffHPCMapMtx, EffHPTMapMtx, NcFANMapMtx, NcHPTMapMtx, NcMtx,
					   PRFANMapMtx, PRFANStallMtx, PRHPCStallMtx, PRHPTMapMtx, Pt21DMtx,
					   Pt21Mtx, Pt6DMtx, Pt6Mtx, RPMshMtx, RPMwmMtx,
					   Tt21DMtx, Tt21Mtx, Tt3DMtx, Tt3Mtx, Tt4CshMtx,
					   Tt4DshMtx, Tt4shMtx, Tt6DMtx, Tt6Mtx, WcFANMapMtx,
					   WcFANStallMtx, WcHPCStallMtx, WcHPTMapMtx, WfshMtx, NcFANshMtx,
					   WfwmMtx, Pt3shMtx, Pt3DshMtx, Pt21wmMtx, Pt21DwmMtx,
					   Pt3wmMtx, Pt3DwmMtx, Pt5wmMtx, Pt5DwmMtx, Pt6wmMtx,
					   Pt6DwmMtx, Tt21wmMtx, Tt21DwmMtx, Tt3wmMtx, Tt3DwmMtx,
					   Tt4wmMtx, Tt4DwmMtx, Tt5wmMtx, Tt5DwmMtx, Tt6wmMtx,
					   Tt6DwmMtx, Pt21shMtx, Pt21DshMtx, Pt5shMtx, Pt5DshMtx,
					   Pt6shMtx, Pt6DshMtx, Tt21shMtx, Tt21DshMtx, Tt3shMtx,
					   Tt3DshMtx, Tt5shMtx, Tt5DshMtx, Tt6shMtx, Tt6DshMtx);

		/* Loads controller constants */
		getTJ200FADECContConst(&ContConst);
    }

	if (WhichEngine == 6)
	{

		/* Loads FADEC matrices */
		getTJ40FADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
						  DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
						  N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
						  Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
						  Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
						  WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);

		/* Loads HIL matrices */
		getTJ40HILMtx(AshMtx, AwmMtx, BshMtx, BwmMtx, EffFANMapMtx,
					   EffHPCMapMtx, EffHPTMapMtx, NcFANMapMtx, NcHPTMapMtx, NcMtx,
					   PRFANMapMtx, PRFANStallMtx, PRHPCStallMtx, PRHPTMapMtx, Pt21DMtx,
					   Pt21Mtx, Pt6DMtx, Pt6Mtx, RPMshMtx, RPMwmMtx,
					   Tt21DMtx, Tt21Mtx, Tt3DMtx, Tt3Mtx, Tt4CshMtx,
					   Tt4DshMtx, Tt4shMtx, Tt6DMtx, Tt6Mtx, WcFANMapMtx,
					   WcFANStallMtx, WcHPCStallMtx, WcHPTMapMtx, WfshMtx, NcFANshMtx,
					   WfwmMtx, Pt3shMtx, Pt3DshMtx, Pt21wmMtx, Pt21DwmMtx,
					   Pt3wmMtx, Pt3DwmMtx, Pt5wmMtx, Pt5DwmMtx, Pt6wmMtx,
					   Pt6DwmMtx, Tt21wmMtx, Tt21DwmMtx, Tt3wmMtx, Tt3DwmMtx,
					   Tt4wmMtx, Tt4DwmMtx, Tt5wmMtx, Tt5DwmMtx, Tt6wmMtx,
					   Tt6DwmMtx, Pt21shMtx, Pt21DshMtx, Pt5shMtx, Pt5DshMtx,
					   Pt6shMtx, Pt6DshMtx, Tt21shMtx, Tt21DshMtx, Tt3shMtx,
					   Tt3DshMtx, Tt5shMtx, Tt5DshMtx, Tt6shMtx, Tt6DshMtx);

		/* Loads controller constants */
		getTJ40FADECContConst(&ContConst);
    }

	/*------------------------------------------*/
	/* CALCULATION OF ENGINE INITIAL CONDITIONS */
	/*------------------------------------------*/

	if (EngOutput.ICCalc == 0)
	{
mexPrintf("EngUnits=%d, RefCAN=%f\n",EngUnits,RefCAN);
		/* Reads Altitude, MN and dT for calculating initial conditions */
		InitCond(&SkipStart, SteadyOp_Elem, MN_Elem, Fn_Elem, Altitude, MN, dT, EngPars.NDes, RefCAN, &Ambient, MNLinVec, FNperContMtx,
			NcFANContMtx, FNcMaxContMtx, WfMtx, Mtx2D, Mtx2DH, Mtx1D, Mtx1DH, &EngOutput, EngUnits);

		/* Calculates initial conditions */
		Wf0 = EngOutput.Wf;
		fValue = Wf0;

		/* Sets initial conditions for oil pump rotation speed - bearings model must be validated!! */
		OPRPM = ContConst.OPRPMMax;

		/*If Wf0 is zero, OPRPM must start with zero*/
		if (Wf0 <= 0.000001)
		{
			OPRPM = 0;
		}
mexPrintf("Wf0 = %f\n\n",Wf0);
	}

