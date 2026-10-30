%Computes the Matrices obtained form linearization and saved as C code for
%FADEC and HIL use

%COMPUTES THE MATRICES OBTAINED FROM LINEARIZATION - USED BY HIL AND FADEC

 load('CorrectedPars.mat');
 load('NDesRU.mat')
 
 MNVec = CorrPar.MN;
 AltVec = CorrPar.Altitude;
 FNcMtx = CorrPar.NetThrust;
 W2cMtx = CorrPar.W2;
 WfcMtx = CorrPar.FuelFlow;
 Tt4cMtx = CorrPar.Tt4;
 Tt5cMtx = CorrPar.Tt5;
 N2cMtx = CorrPar.RPM;
 Pt3cMtx = CorrPar.Pt3;
 Pt5cMtx = CorrPar.Pt5;
 
 %Inverts matrix case necessary
 if N2cMtx(1,1) > N2cMtx(1,end)
     FNcMtx = fliplr(CorrPar.NetThrust);
     W2cMtx = fliplr(CorrPar.W2);
     WfcMtx = fliplr(CorrPar.FuelFlow);
     Tt4cMtx = fliplr(CorrPar.Tt4);
     Tt5cMtx = fliplr(CorrPar.Tt5);
     N2cMtx = fliplr(CorrPar.RPM);
     Pt3cMtx = fliplr(CorrPar.Pt3);
     Pt5cMtx = fliplr(CorrPar.Pt5);
 end

 
%Static pressure vector
P0Vec = [1.0133e+05 90160 79744 70146 61883 54228 47270 41293 35782 30860 26646 22803 19464];

%Static temperature vector
T0Vec = [288.15 281.65 275.15 268.66 262.16 255.68 249.18 242.7 236.21 229.73 223.25 218.43 216.94];

%Design point rotation speed value
NDes = NDesRU.NDes;

%Coefficient for minimum fuel flow calculation
RU = NDesRU.RU;

