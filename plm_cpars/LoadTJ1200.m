
%=======================
%LOADS TJ1200 PARAMETERS
%=======================

%------------------------------------
%ENGINE DESIGN SPEED AND STALL MARGIN
%------------------------------------

Ndes = 23042;%22972;
SM = 0.25;

%--------------------------
%LOADING OF COMPONENTS MAPS
%--------------------------

%FAN MAP

MWS = [];
MWS = GTLPCMap(MWS);
MWS = GTHPCMap(MWS);

NcGainFAN = 23116.775324;%23947.053525;
WcGainFAN = 1.137547;%1.278796;
PRGainFAN = 1.047403;%1.024266;
EffGainFAN = 0.955923;%0.945597;

NcFANMap = MWS.HPC.NcVec * NcGainFAN / Ndes;
RlineFANMap = MWS.HPC.RlineVec;
WcFANMap = MWS.HPC.WcArray * WcGainFAN * 1/2.2046226;
WcFANStall = MWS.HPC.WcMapSurge * WcGainFAN * 1/2.2046226;
EffFANMap = MWS.HPC.EffArray * EffGainFAN; 
PRFANMap = PRGainFAN * (MWS.HPC.PRArray - 1) + 1;
PRFANStall = PRGainFAN * (MWS.HPC.PRMapSurge - 1) + 1;
PRFANStallMarg = PRFANStall / (1 + SM);

%HPC MAP

NcGainHPC = 23116.775324;%23947.053525;
WcGainHPC = 1.137547;%1.278796;
PRGainHPC = 1.047403;%1.024266;
EffGainHPC = 0.955923;%0.945597;

SM = 0.25;

NcHPCMap = MWS.HPC.NcVec * NcGainHPC / Ndes;
RlineHPCMap = MWS.HPC.RlineVec;
WcHPCMap = MWS.HPC.WcArray * WcGainHPC * 1/2.2046226;
WcHPCStall = MWS.HPC.WcMapSurge * WcGainHPC * 1/2.2046226;
EffHPCMap = MWS.HPC.EffArray * EffGainHPC; 
PRHPCMap = PRGainHPC * (MWS.HPC.PRArray - 1) + 1;
PRHPCStall = PRGainHPC * (MWS.HPC.PRMapSurge - 1) + 1;
PRHPCStallMarg = PRHPCStall / (1 + SM);
