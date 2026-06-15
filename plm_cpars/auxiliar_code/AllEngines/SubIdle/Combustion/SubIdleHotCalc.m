function [AshMtx,BshMtx,Pt3CshMtx,Pt3DshMtx,Tt4CshMtx,Tt4DshMtx,...
                  NcFANshMtx,WfshMtx,Tt4shMtx,Pt3shMtx,RPMshMtx,...
                  Pt21shMtx,Pt21CshMtx,Pt21DshMtx,...
                  Pt5shMtx,Pt5CshMtx,Pt5DshMtx,...
                  Pt6shMtx,Pt6CshMtx,Pt6DshMtx,...
                  Tt21shMtx,Tt21CshMtx,Tt21DshMtx,...
                  Tt3shMtx,Tt3CshMtx,Tt3DshMtx,...
                  Tt5shMtx,Tt5CshMtx,Tt5DshMtx,...
                  Tt6shMtx,Tt6CshMtx,Tt6DshMtx] = SubIdleHotCalc
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

% Initiates the matrices containing windmill parameters
AshMtx = -0.5;
BshMtx = 80000;

Pt21shMtx = 0;
Pt21CshMtx = 0;
Pt21DshMtx = 0;
Pt3shMtx = 0;
Pt3CshMtx = 0;
Pt3DshMtx = 0;
Pt5shMtx = 0;
Pt5CshMtx = 0;
Pt5DshMtx = 0;
Pt6shMtx = 0;
Pt6CshMtx = 0;
Pt6DshMtx = 0;

Tt21shMtx = 0;
Tt21CshMtx = 0;
Tt21DshMtx = 0;
Tt3shMtx = 0;
Tt3CshMtx = 0;
Tt3DshMtx = 0;
Tt4shMtx = 800;
Tt4CshMtx = -0.06;
Tt4DshMtx = 4000;
Tt5shMtx = 0;
Tt5CshMtx = 0;
Tt5DshMtx = 0;
Tt6shMtx = 0;
Tt6CshMtx = 0;
Tt6DshMtx = 0;

RPMshMtx = 4000;
NcFANshMtx = 0;

WfshMtx = 0.017;




end

