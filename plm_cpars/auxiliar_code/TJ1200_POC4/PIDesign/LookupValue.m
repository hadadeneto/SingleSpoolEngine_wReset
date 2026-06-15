function [Value] = LookupValue(k1H,k1L,f1,k2H,k2L,f2,k3H,k3L,f3,Mtx3D)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%k3 - page
%k2 - row
%k1 - column

%Calculation of 2D Matrix
Mtx2D = (Mtx3D(:,:,k3H) - Mtx3D(:,:,k3L))*f3 + Mtx3D(:,:,k3L);

%Calculation of 1D Matrix
Mtx1D = (Mtx2D(k2H,:) - Mtx2D(k2L,:))*f2 + Mtx2D(k2L,:);

%Calculates Value
Value = Mtx1D(k1L) + f1*(Mtx1D(k1H)-Mtx1D(k1L));


end

