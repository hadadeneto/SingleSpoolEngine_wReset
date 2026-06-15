
%=======================
%LOADS TF1200 PARAMETERS
%=======================

%------------------------------------
%ENGINE DESIGN SPEED AND STALL MARGIN
%------------------------------------

Ndes = 26400;
SMFAN = 10;
SMHPC = 10;

%--------------------------
%LOADING OF COMPONENTS MAPS
%--------------------------

MWS = [];
MWS = GTLPCMap(MWS);
MWS = GTHPCMap(MWS);

%FAN MAP

NcGain = 26400;
WcGain = 0.482062;
PRGain = 0.395551;
EffGain = 1.003058;

NcFANMap = MWS.LPC.NcVec * NcGain / Ndes;
RlineFANMap = MWS.LPC.RlineVec;
WcFANMap = MWS.LPC.WcArray * WcGain * 1/2.2046226;
WcFANStall = MWS.LPC.WcMapSurge * WcGain * 1/2.2046226;
EffFANMap = MWS.LPC.EffArray * EffGain; 
PRFANMap = PRGain * (MWS.LPC.PRArray - 1) + 1;
PRFANStall = PRGain * (MWS.LPC.PRMapSurge - 1) + 1;
SMFAN = SMFAN/100;
PRFANStallMarg = PRFANStall / (1 + SMFAN);

%HPC MAP

NcGain = 24138.179392;
WcGain = 0.561693;
PRGain = 0.843277;
EffGain = 1.022830;

NcHPCMap = MWS.HPC.NcVec * NcGain / Ndes;
RlineHPCMap = MWS.HPC.RlineVec;
WcHPCMap = MWS.HPC.WcArray * WcGain * 1/2.2046226;
WcHPCStall = MWS.HPC.WcMapSurge * WcGain * 1/2.2046226;
EffHPCMap = MWS.HPC.EffArray * EffGain; 
PRHPCMap = PRGain * (MWS.HPC.PRArray - 1) + 1;
PRHPCStall = PRGain * (MWS.HPC.PRMapSurge - 1) + 1;
SMHPC = SMHPC/100;
PRHPCStallMarg = PRHPCStall / (1 + SMHPC);
