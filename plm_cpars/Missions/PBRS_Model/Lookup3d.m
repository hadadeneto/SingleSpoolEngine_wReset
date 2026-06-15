function [k1H,k1L,f1,k2H,k2L,f2,k3H,k3L,f3] = Lookup3d(AltLinVec,MNLinVec,RPMMtx,Altitude,MN,RPM)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

%----------------
%3D COEFFICIENTS
%----------------

%Finds the index k3H
k3H = FinIndex(Altitude,AltLinVec,length(AltLinVec));

%Calculates the lower index for Altitude
if k3H == 1
    k3L = 1;
    f3 = 0;
else
    k3L = k3H-1;
    %Calculates interpolation coefficient for finding 2D matrice
    f3 = (Altitude - AltLinVec(k3L))/(AltLinVec(k3H) - AltLinVec(k3L));
end


%Calculates 2D Matrix
RPM2D = (RPMMtx(:,:,k3H) - RPMMtx(:,:,k3L))*f3 + RPMMtx(:,:,k3L);

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
end

% %Test Line
% RPMTeste = RPM1D(k1L) + f1*(RPM1D(k1H)-RPM1D(k1L));
% 
% Test =1;






