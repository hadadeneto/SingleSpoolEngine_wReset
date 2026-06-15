function [AwmMtx,BwmMtx,CwmMtx,DwmMtx,RPMwmMtx,WfwmMtx,...
          Pt21wmMtx,Pt21CwmMtx,Pt21DwmMtx,...
          Pt3wmMtx,Pt3CwmMtx,Pt3DwmMtx,...
          Pt5wmMtx,Pt5CwmMtx,Pt5DwmMtx,...
          Pt6wmMtx,Pt6CwmMtx,Pt6DwmMtx,...
          Tt21wmMtx,Tt21CwmMtx,Tt21DwmMtx,...
          Tt3wmMtx,Tt3CwmMtx,Tt3DwmMtx,...
          Tt4wmMtx,Tt4CwmMtx,Tt4DwmMtx,...
          Tt5wmMtx,Tt5CwmMtx,Tt5DwmMtx,...
          Tt6wmMtx,Tt6CwmMtx,Tt6DwmMtx] = WindMillCalc(MNLinVec)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

% Initiates the matrices containing windmill parameters
AwmMtx = zeros(1,length(MNLinVec));
BwmMtx = zeros(1,length(MNLinVec));
RPMwmMtx = zeros(1,length(MNLinVec));
WfwmMtx = zeros(1,length(MNLinVec));
CwmMtx = 0;
DwmMtx = 0;

% Calculates matrices elements for each Mach number value
for i = 1:length(MNLinVec)
    
    %The current model is only valid between Mach number values of 0.3 and
    %0.7. Whenever this model is extended, the filter below is to be
    %disconsidered
%     M = max(0.3,MNLinVec(i));
%     M = min(0.7,M);
    M = MNLinVec(i);
    WfwmMtx(i) = M;
    
    %Parameters calculation
    [RPMwmMtx(i),AwmMtx(i),BwmMtx(i)] = WindMillPars(M);
    
end

%Pressures and temperatures
Pt21wmMtx = 0;
Pt21CwmMtx = 0;
Pt21DwmMtx = 0;
Pt3wmMtx = 0;
Pt3CwmMtx = 0;
Pt3DwmMtx = 0;
Pt5wmMtx = 0;
Pt5CwmMtx = 0;
Pt5DwmMtx = 0;
Pt6wmMtx = 0;
Pt6CwmMtx = 0;
Pt6DwmMtx = 0;

Tt21wmMtx = 0;
Tt21CwmMtx = 0;
Tt21DwmMtx = 0;
Tt3wmMtx = 0;
Tt3CwmMtx = 0;
Tt3DwmMtx = 0;
Tt4wmMtx = 0;
Tt4CwmMtx = 0;
Tt4DwmMtx = 0;
Tt5wmMtx = 0;
Tt5CwmMtx = 0;
Tt5DwmMtx = 0;
Tt6wmMtx = 0;
Tt6CwmMtx = 0;
Tt6DwmMtx = 0;

end

