
%=======================
%LOADS GE J85 PARAMETERS
%=======================

%------------------------------------
%ENGINE DESIGN SPEED AND STALL MARGIN
%------------------------------------

Ndes = 16540;
SM = 0.15;

%--------------------------
%LOADING OF COMPONENTS MAPS
%--------------------------

%FAN MAP

MWS = [];
MWS = J85HPCMap(MWS);

NcGainFAN = 16539.999769;
WcGainFAN = 1.016177;
PRGainFAN = 0.984641;
EffGainFAN = 0.947717;

NcFANMap = MWS.HPC.NcVec * NcGainFAN / Ndes;
RlineFANMap = MWS.HPC.RlineVec;
WcFANMap = MWS.HPC.WcArray * WcGainFAN * 1/2.2046226;
WcFANStall = MWS.HPC.WcMapSurge * WcGainFAN * 1/2.2046226;
EffFANMap = MWS.HPC.EffArray * EffGainFAN; 
PRFANMap = PRGainFAN * (MWS.HPC.PRArray - 1) + 1;
PRFANStall = PRGainFAN * (MWS.HPC.PRMapSurge - 1) + 1;
PRFANStallMarg = PRFANStall / (1 + SM);

%HPC MAP

NcGainHPC = 16539.999769;
WcGainHPC = 1.016177;
PRGainHPC = 0.984641;
EffGainHPC = 0.947717;

NcHPCMap = MWS.HPC.NcVec * NcGainHPC / Ndes;
RlineHPCMap = MWS.HPC.RlineVec;
WcHPCMap = MWS.HPC.WcArray * WcGainHPC * 1/2.2046226;
WcHPCStall = MWS.HPC.WcMapSurge * WcGainHPC * 1/2.2046226;
EffHPCMap = MWS.HPC.EffArray * EffGainHPC; 
PRHPCMap = PRGainHPC * (MWS.HPC.PRArray - 1) + 1;
PRHPCStall = PRGainHPC * (MWS.HPC.PRMapSurge - 1) + 1;
PRHPCStallMarg = PRHPCStall / (1 + SM);
