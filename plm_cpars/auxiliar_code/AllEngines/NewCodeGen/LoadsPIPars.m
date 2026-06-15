
%-------------------
%LOADS PI PARAMETERS
%-------------------

%Loads PI Gains from the .mat file
word = ['cd ' EngFoldName];
eval(word);
load('PI.mat');
load('PIsh.mat');
word = ['cd ' UpperFolder];
eval(word);

N_KpMtx = PIGains.Kp;
N_KiMtx = PIGains.Ki;
FNperContMtx = PIGains.FNper;
NcFANContMtx = PIGains.NcFAN;

N_KpshMtx = PIshGains.Kpsh;
N_KishMtx = PIshGains.Kish;
NcFANshContMtx = PIshGains.NcFANsh;
