function [k1H,k1L,f1,k2H,k2L,f2] = Lookup2d(MNLinVec,RPM2D,MN,RPM)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

%----------------
%2D COEFFICIENTS
%----------------

%Finds the index k2H
k2H = FinIndex(MN,MNLinVec,length(MNLinVec));

%Calculates the lower index for Altitude
if k2H == 1
    k2L = 1;
    f2 = 0;
else
    k2L = k2H-1;
    %Calculates interpolation coefficient for finding 2D matrice
    f2 = (MN - MNLinVec(k2L))/(MNLinVec(k2H) - MNLinVec(k2L));
end

%Calculates 2D Matrix
RPM1D = (RPM2D(k2H,:) - RPM2D(k2L,:))*f2 + RPM2D(k2L,:);

%----------------
%1D COEFFICIENTS
%----------------

%Finds the index k1H
k1H = FinIndex(RPM,RPM1D,length(RPM1D));

%Calculates the lower index for Altitude
if k1H == 1
    k1L = 1;
    f1 = 0;
else
    k1L = k1H-1;
    %Calculates interpolation coefficient for finding 2D matrice
    f1 = (RPM - RPM1D(k1L))/(RPM1D(k1H) - RPM1D(k1L));
    %The value of f1 must not exceed 1 in order for model linear
    %extrapolation not to happen
    f1 = min(f1,1);
end








