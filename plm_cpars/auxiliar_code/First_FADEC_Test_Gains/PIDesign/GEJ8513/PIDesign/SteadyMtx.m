

%CALCULATES THE ENGINE MATRICES AT ALTITUDE LEVELS DIFFERENT FROM SL
load('Ambient.mat');
PAmb = Ambient.Pamb;
TAmb = Ambient.Tamb;
DeltaMtx = PAmb / 101325;
ThetaMtx = TAmb / 288.15;
sqrThetaMtx = sqrt(ThetaMtx);

%Calculates the corrected parameters of thrust and N controller gains for
%sea level and different mach numbers
for j = 1:length(MNVectorPT)
    
    %Sea level parameters
    DeltaSL = DeltaMtx(1,j);
    ThetaSL = ThetaMtx(1,j);
    sqrThetaSL = sqrThetaMtx(1,j);
    
    FNcMtx(j,:,1) = FNMtx(j,:,1) / DeltaSL;
    WfcMtx(j,:,1) = WfMtx(j,:,1) / DeltaSL / sqrThetaSL;
    AcMtx(j,:,1) = AMtx(j,:,1) * sqrThetaSL / DeltaSL;
    BcMtx(j,:,1) = BMtx(j,:,1) * sqrThetaSL;
%     N_KpcMtx = N_KpcMtx(j,:) / DeltaSL;
%     N_KipcMtx = N_KiMtx(j,:) / DeltaSL;
    
end

%Initializes NcMtx for building a complete matrix to be used by controller
NcMtx = NcFANMtx;

%Saves the matrices of thrust and fuel flow in a struct
Parameter.FuelFlow = WfMtx;
Parameter.NetThrust = FNMtx;
Parameter.Altitude = AltLinVectorPT;
Parameter.MN = MNVectorPT;

save Engine.mat Parameter;
