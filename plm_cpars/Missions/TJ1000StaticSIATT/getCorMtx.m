%Computes the Matrices obtained form linearization and saved as C code for
%FADEC and HIL use

%COMPUTES THE MATRICES OBTAINED FROM LINEARIZATION - USED BY HIL AND FADEC

 load('CorrectedPars.mat');
 
 MNVec = CorrPar.MN;
 AltVec = CorrPar.Altitude;
 FNcMtx = CorrPar.NetThrust;
 WfcMtx = CorrPar.FuelFlow;
 Tt4cMtx = CorrPar.Tt4;
 N2cMtx = CorrPar.RPM;
 Pt3cMtx = CorrPar.Pt3;

 
%Static pressure vector
P0Vec = [1.0133e+05 90160 79744 70146 61883 54228 47270 41293 35782 30860 26646 22803 19464];

%Static temperature vector
T0Vec = [288.15 281.65 275.15 268.66 262.16 255.68 249.18 242.7 236.21 229.73 223.25 218.43 216.94];

%Design point rotation speed value
NDes = 22972;

%Coefficient for minimum fuel flow calculation
RU = 1.6e-7;

