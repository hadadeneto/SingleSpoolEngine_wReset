
%=======================
%LOADS TJ1200 PARAMETERS
%=======================

%------------------------------------
%ENGINE DESIGN SPEED AND STALL MARGIN
%------------------------------------

Ndes = 98000;%22972;
SM = 0.25;

%--------------------------
%LOADING OF COMPONENTS MAPS
%--------------------------

%FAN MAP

MWS.HPC = [];
MWS.HPC = HPC_PBSTJ100(MWS.HPC);

% NcGainFAN = 23116.775324;%23947.053525;
% WcGainFAN = 1.137547;%1.278796;
% PRGainFAN = 1.047403;%1.024266;
% EffGainFAN = 0.955923;%0.945597;
% 
% NcGainFAN = 30199.999579;
% WcGainFAN = 1.023930;
% PRGainFAN = 1.071130;
% EffGainFAN = 1.030564;
% 
% NcGainFAN = 56521.738343;
% WcGainFAN = 0.018475;
% PRGainFAN = 0.924183;
% EffGainFAN = 1.040000;

NcGainFAN = 97999.998634;
WcGainFAN = 0.009051;
PRGainFAN = 1.460640;
EffGainFAN = 1.040000;

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

NcGainHPC = 30199.999579;
WcGainHPC = 1.023930;
PRGainHPC = 1.071130;
EffGainHPC = 1.030564;

NcGainHPC = 56521.738343;
WcGainHPC = 0.018475;
PRGainHPC = 0.924183;
EffGainHPC = 1.040000;

NcGainHPC = 97999.998634;
WcGainHPC = 0.009051;
PRGainHPC = 1.460640;
EffGainHPC = 1.040000;

SM = 0.25;

NcHPCMap = MWS.HPC.NcVec * NcGainHPC / Ndes;
RlineHPCMap = MWS.HPC.RlineVec;
WcHPCMap = MWS.HPC.WcArray * WcGainHPC * 1/2.2046226;
WcHPCStall = MWS.HPC.WcMapSurge * WcGainHPC * 1/2.2046226;
EffHPCMap = MWS.HPC.EffArray * EffGainHPC; 
PRHPCMap = PRGainHPC * (MWS.HPC.PRArray - 1) + 1;
PRHPCStall = PRGainHPC * (MWS.HPC.PRMapSurge - 1) + 1;
PRHPCStallMarg = PRHPCStall / (1 + SM);
