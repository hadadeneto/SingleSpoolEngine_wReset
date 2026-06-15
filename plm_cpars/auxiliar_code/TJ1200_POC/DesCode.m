


%Ambient calculations are to be performed only if getAmbient = 1
getAmbient = 1;

%PI calculations are to be performed only if getAmbient = 1
getPIGains = 1;

%Choses between new or older sub-idle and windmill model
%1 - Older Model
%2 - Newer Model
SubIdleModel = 1;

%Transfer function for zoh with sampler
%1 - Adds Padé approach G(s) = (1 - T/2*s)/(1 + T/2*s)
%2 - Adds actual transfer function G(s) = (1 - exp(T*s))/T*s
AddZOH = 2;

%first order model of the pump is considered if AddPump = 1
AddPump = 1;

%C code is to be generated only if getAmbient = 1
getCCode = 1;

%Calls script to perform above actions
MainScript
