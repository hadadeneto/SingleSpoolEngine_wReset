function [AwmMtx,BwmMtx,CwmMtx,DwmMtx,RPMwmMtx] = WindMillCalc(MNLinVec)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

% Initiates the matrices containing windmill parameters
AwmMtx = zeros(1,length(MNLinVec));
BwmMtx = zeros(1,length(MNLinVec));
RPMwmMtx = zeros(1,length(MNLinVec));
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
    
    %Parameters calculation
    [RPMwmMtx(i),AwmMtx(i),BwmMtx(i)] = WindMillPars(M);
    
end

end

