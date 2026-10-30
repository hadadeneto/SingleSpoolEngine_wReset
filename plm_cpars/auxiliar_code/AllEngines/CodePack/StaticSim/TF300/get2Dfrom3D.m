function RPM1D = get2Dfrom3D(MNLinVec,RPM2D,MN)
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
end

