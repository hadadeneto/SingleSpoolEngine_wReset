function [k1H,k1L,f1,Empty] = Lookup1d(RPM,RPM1D)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

% %----------------
% %3D COEFFICIENTS
% %----------------
% 
% %Finds the indexes for findint the 2D Matrices
% k3H = find(Altitude <= AltLinVec,1);
% 
% %If the Altitude value is too high, the highest mapped value will be
% %considered
% if isempty(k3H)
%     k3H = length(AltLinVec);
% end
% %Calculates the lower index for Altitude
% if k3H == 1
%     k3L = 1;
%     f3 = 0;
% else
%     k3L = k3H-1;
%     %Calculates interpolation coefficient for finding 2D matrice
%     f3 = (Altitude - AltLinVec(k3L))/(AltLinVec(k3H) - AltLinVec(k3L));
% end
% 
% 
% %Calculates 2D Matrix
% RPM2D = (RPMMtx(:,:,k3H) - RPMMtx(:,:,k3L))*f3 + RPMMtx(:,:,k3L);
% 
% %----------------
% %2D COEFFICIENTS
% %----------------
% 
% %Finds the indexes for findint the 2D Matrices
% k2H = find(MN <= MNLinVec,1);
% 
% %If the Altitude value is too high, the highest mapped value will be
% %considered
% if isempty(k2H)
%     k2H = length(AltLinVec);
% end
% %Calculates the lower index for Altitude
% if k2H == 1
%     k2L = 1;
%     f2 = 0;
% else
%     k2L = k2H-1;
%     %Calculates interpolation coefficient for finding 2D matrice
%     f2 = (MN - MNLinVec(k2L))/(MNLinVec(k2H) - MNLinVec(k2L));
% end
% 
% %Calculates 2D Matrix
% RPM1D = (RPM2D(k2H,:) - RPM2D(k2L,:))*f2 + RPM2D(k2L,:);

%----------------
%1D COEFFICIENTS
%----------------

%At first, indicates that a value has been found
Empty = 0;

%Finds the indexes for findint the 2D Matrices
k1H = find(RPM <= RPM1D,1);

%If the Altitude value is too high, the highest mapped value will be
%considered
if isempty(k1H)
    k1H = length(RPM1D);
    Empty = 1;
end
%Calculates the lower index for Altitude
if k1H == 1
    k1L = 1;
    f1 = 0;
else
    k1L = k1H-1;
    %Calculates interpolation coefficient for finding 2D matrice
    f1 = (RPM - RPM1D(k1L))/(RPM1D(k1H) - RPM1D(k1L));
end







