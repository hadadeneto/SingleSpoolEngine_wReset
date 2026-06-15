
%Loads parameters
load('CorrectedPars.mat');

%Loadas Matrices
FNcMtx = CorrPar.NetThrust;
WfcMtx = CorrPar.FuelFlow;
N2cMtx = CorrPar.RPM;
AltVec = CorrPar.Altitude;
MNVec = CorrPar.MN;
ThetaMtx = CorrPar.Theta;
DeltaMtx = CorrPar.Delta;
NDes = 24000;

P0Vec = DeltaMtx(:,1)' * 101325;
T0Vec = ThetaMtx(:,1)' * 288.15;

dlmwrite('FNcMtxDummy.m',FNcMtx,' ')
dlmwrite('WfcMtxDummy.m',WfcMtx,' ')
dlmwrite('N2cMtxDummy.m',N2cMtx,' ')
dlmwrite('AltVecDummy.m',AltVec,' ')
dlmwrite('MNVecDummy.m',MNVec,' ')
dlmwrite('T0VecDummy.m',T0Vec,' ')
dlmwrite('P0VecDummy.m',P0Vec,' ')

