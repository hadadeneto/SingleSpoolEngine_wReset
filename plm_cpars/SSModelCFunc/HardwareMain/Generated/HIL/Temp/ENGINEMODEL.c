
	/* Updates FNpc and allows transition from IDLE to REGIME depending no reference value */
	IdleToRegime(&EngStatus, &ContInput, RefCAN, 0, ContConst.FNIdle, &FNpc, LeverMode);

	// mexPrintf("Outside PIMMRF.c: FNpc = %f\n", FNpc);
	/* Bearing 0 Model Inputs */
    Bear0.A = -0.1;//-0.5;
    Bear0.B = 1;
    Bear0.C = -0.1;//-0.5;
    Bear0.DelTExt = 0;
    Bear0.ElNumRPME = 3;
    Bear0.MaxRPMP = 4500;
    Bear0.Ts = TsamModel;

	/* Bearing 1 Model Inputs */
    Bear1.A = -0.1;//-0.5;
    Bear1.B = 1;
    Bear1.C = -0.1;//-0.5;
    Bear1.DelTExt = 0;
    Bear1.ElNumRPME = 3;
    Bear1.MaxRPMP = 4500;
    Bear1.Ts = TsamModel;

	/* Bearing 2 Model Inputs */
    Bear2.A = -0.1;//-0.5;
    Bear2.B = 1;
    Bear2.C = -0.1;//-0.5;
    Bear2.DelTExt = 0;
    Bear2.ElNumRPME = 3;
    Bear2.MaxRPMP = 4500;
    Bear2.Ts = TsamModel;

    /* Smulation of Engine BlowOut */
	BlowOutSim(&SysFaults, &Wf);

	/* Smulation of Ignition Fault */
	IgnitionFault(&SysFaults, &Ignition);
//mexPrintf("Executing Engine Model Loop\n");
// mexPrintf("Wf=%f FuelIn=%f\n",Wf,FuelIn);
    for(i = 1; i < TsampDiv + 1; i++)
    {

	/* Calculates model outputs */
	EngineModel(&Ambient, &EngOutput, Wf,
		Altitude, MN, dT, Mwm, Ignition, NcMtx, Pt21Mtx, Pt3Mtx, Pt5Mtx, Pt6Mtx,
		Tt21Mtx, Tt3Mtx, Tt4Mtx, Tt5Mtx, Tt6Mtx, WfMtx, AMtx, BMtx,
		Pt21DMtx, Pt3DMtx, Pt5DMtx, Pt6DMtx, Tt21DMtx, Tt3DMtx, Tt4DMtx, Tt5DMtx, Tt6DMtx,
		NcFANMapMtx, WcFANMapMtx, WcFANStallMtx, PRFANMapMtx, PRFANStallMtx, EffFANMapMtx,
		NcHPCMapMtx, WcHPCMapMtx, WcHPCStallMtx, PRHPCMapMtx, PRHPCStallMtx, EffHPCMapMtx,
		NcHPTMapMtx, WcHPTMapMtx, PRHPTMapMtx, EffHPTMapMtx, &EngPars,
		Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
		MapFAN2D, MapFAN2DH, MapFAN1D, MapFAN1DH, MNLinVec,
		MapHPC2D, MapHPC2DH, MapHPC1D, MapHPC1DH,
        AwmMtx, AshMtx, BwmMtx, BshMtx, RPMwmMtx, RPMshMtx,
        NcFANshMtx, Pt21shMtx, Pt21wmMtx,
		Pt21DshMtx, Pt21DwmMtx, Pt3shMtx, Pt3wmMtx,
		Pt3DshMtx, Pt3DwmMtx, Pt5shMtx, Pt5wmMtx, Pt5DshMtx, Pt5DwmMtx, Pt6shMtx, Pt6wmMtx,
		Pt6DshMtx, Pt6DwmMtx, Tt21shMtx, Tt21wmMtx, Tt21DshMtx, Tt21DwmMtx,
		Tt3shMtx, Tt3wmMtx, Tt3DshMtx, Tt3DwmMtx, Tt4shMtx, Tt4wmMtx, Tt4CshMtx, Tt4DshMtx, Tt4DwmMtx,
		Tt5shMtx, Tt5wmMtx, Tt5DshMtx, Tt5DwmMtx, Tt6shMtx, Tt6wmMtx, Tt6DshMtx, Tt6DwmMtx, WfshMtx, WfwmMtx,
        &Faults, &Sensors,
        TsamModel, ExtFPModel, FlightStart);

        /* Loads bearing varying data */
        Bear0.RPME = EngOutput.RPM;
        Bear0.RPMP = OPRPM;
        Bear0.RPMPss = 0;
        Bear0.Tss = 0;

        /* Loads bearing varying data */
        Bear1.RPME = EngOutput.RPM;
        Bear1.RPMP = OPRPM;
        Bear1.RPMPss = 0;
        Bear1.Tss = 0;

        /* Loads bearing varying data */
        Bear2.RPME = EngOutput.RPM;
        Bear2.RPMP = OPRPM;
        Bear2.RPMPss = 0;
        Bear2.Tss = 0;

		/* Correction of RPMEVec for adaptation to engines */
		RPMEVec[1] = ContConst.NDes * 20000 / 23000;
		RPMEVec[2] = ContConst.NDes;
		/* Bearings calculations */
		BearingModel(&Bear0, &RPMEVec[0], &TNOil_Bear0[0], &DelT_Bear0[0]);
	    BearingModel(&Bear1, &RPMEVec[0], &TNOil_Bear1[0], &DelT_Bear1[0]);
	    BearingModel(&Bear2, &RPMEVec[0], &TNOil_Bear2[0], &DelT_Bear2[0]);

		/* Updates engine outputs - should be done inside EnginModel in the future!! */
		EngOutput.TBear[0] = Bear0.Tout;
		EngOutput.TBear[1] = Bear1.Tout;
		EngOutput.TBear[2] = Bear2.Tout;

		/* FUEL PRESSURE AND OIL PRESSURE MODELS - Must be updated EngineModel in the future!! */

		/* The following fuel pressure equation is to be used whenever Wf < 0.5 * WfInit (Wf init is the value of the lower fuel pulse during ignitions) */
		if (Wf < 0.5 * ContConst.WfInit)
		{
			EngOutput.PFuel = ContConst.PFuelLow / 0.005 * Wf;
		}
		else
		{
			/* Updates PFuell model value, which becomes proportional to the fuel flow */
			EngOutput.PFuel = (ContConst.PFuelHigh - ContConst.PFuelLow) / (1.5 * ContConst.WfMax - 0.5 * ContConst.WfInit) * (Wf - 1.5 * ContConst.WfMax) + ContConst.PFuelHigh;
		}

		/* Updates POil model value, which becomes proportional to OPRPM */
		EngOutput.POil = ContConst.POilHigh * OPRPM / ContConst.OPRPMMax * 0.95;

		/* Limits the maximum oil pressure to 4 bar for avoiding DAC saturation during simulation with non-null initial conditions */
		EngOutput.POil = Min(EngOutput.POil,4*100000);

    }
//mexPrintf("\n");
    /* Simulation of mechanical failures */
	SysFaultSim(&SysFaults, &EngPars, &EngOutput);

	/* Updates outputs */
	W2 = EngOutput.W2;
	Pt2 = EngOutput.Pt2;
    Ts2 = EngOutput.Ts2;
	Tt2 = EngOutput.Tt2;
	NcFAN = EngOutput.N2c;
	WcFAN = EngOutput.W2c;
	PRFAN = EngOutput.PRFAN;
	SMFAN = EngOutput.SMFAN;
	W21 = EngOutput.W21;
	Pt21 = EngOutput.Pt21;
	Tt21 = EngOutput.Tt21;
	NcHPC = EngOutput.N21c;
	WcHPC = EngOutput.W21c;
	PRHPC = EngOutput.PRHPC;
	SMHPC = EngOutput.SMHPC;
	Pt3 = EngOutput.Pt3;
	Tt3 = EngOutput.Tt3;
	Tt4 = EngOutput.Tt4;
	Wf = EngOutput.Wf;
	Pt5 = EngOutput.Pt5;
	Tt5 = EngOutput.Tt5;
	Pt6 = EngOutput.Pt6;
	Tt6 = EngOutput.Tt6;
	W8 = EngOutput.W8;
	V8 = EngOutput.V8;
	MN8 = EngOutput.MN8;
	Fn = EngOutput.Fn;
	Fg = EngOutput.Fg;
	RPM = EngOutput.RPM;
	POil = EngOutput.POil;

    /* Updates sensor values */
    SensorsUpdt(&Sensors, &EngOutput);

	/* Simulation of sensors faults */
    SensFaultSim(&SensFaults, &Sensors, &EngPars);

	/* Simulation of sensor bias */
	BiasFaultSim(&SysFaults, &SensorBias, &Sensors);

