function [AshMtx,BshMtx,Pt3CshMtx,Pt3DshMtx,Tt4CshMtx,Tt4DshMtx,...
                  NcFANshMtx,WfshMtx,Tt4shMtx,Pt3shMtx,RPMshMtx] = SubIdleHotCalc
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

% Initiates the matrices containing windmill parameters
AshMtx = -0.5;
BshMtx = 80000;
Tt4CshMtx = -0.06;
Tt4DshMtx = 4000;
RPMshMtx = 4000;
Tt4shMtx = 800;
WfshMtx = 0.017;

Pt3CshMtx = 0;
Pt3DshMtx = 0;
NcFANshMtx = 0;
Pt3shMtx = 0;

end

