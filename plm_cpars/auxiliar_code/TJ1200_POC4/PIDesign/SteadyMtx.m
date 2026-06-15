

%CALCULATES THE ENGINE MATRICES AT ALTITUDE LEVELS DIFFERENT FROM SL
load('Ambient.mat');
PAmb = Ambient.Pamb;
TAmb = Ambient.Tamb;
DeltaMtx = PAmb / 101325;
ThetaMtx = TAmb / 288.15;
sqrThetaMtx = sqrt(ThetaMtx);

%Calculates the static temperature matrix at different altitudes
Ts0 = TAmb(:,1)';

%Calculates the corrected parameters of thrust and N controller gains for
%sea level and different mach numbers
for j = 1:length(MNVectorPT)
    
    %Sea level parameters
    DeltaSL = DeltaMtx(1,j);
    ThetaSL = ThetaMtx(1,j);
    sqrThetaSL = sqrThetaMtx(1,j);
    
    FNcMtx(j,:,1) = FNMtx(j,:,1) / DeltaSL;
    WfcMtx(j,:,1) = WfMtx(j,:,1) / DeltaSL / sqrThetaSL;
    Tt4cMtx(j,:,1) = Tt4Mtx(j,:,1) / ThetaSL;
    Pt3cMtx(j,:,1) = Pt3Mtx(j,:,1) / DeltaSL;
    Tt5cMtx(j,:,1) = Tt5Mtx(j,:,1) / ThetaSL;
    Pt5cMtx(j,:,1) = Pt5Mtx(j,:,1) / DeltaSL;
    AcMtx(j,:,1) = AMtx(j,:,1) * sqrThetaSL / DeltaSL;
    BcMtx(j,:,1) = BMtx(j,:,1) * sqrThetaSL;
   %     N_KpcMtx = N_KpcMtx(j,:) / DeltaSL;
%     N_KipcMtx = N_KiMtx(j,:) / DeltaSL;

    %CALCULATES Wc AT FAN INPUT
    
    %Obs.: In the case of pure jets, the fan and the compressor are the
    %same component. Therefore, Pt3 and Pt21 correspond to the same
    %parameter

    PRFANMtx(j,:,1) = Pt21Mtx(j,:,1) ./ DeltaSL / PAmb(1,j);
%     [k1H,k1L,f1,k2H,k2L,f2] = Lookup2d(MNLinVec,RPM2D,MN,RPM)
    for k = 1:length(NcFANMtx(j,:,1))
        [k1H,k1L,f1,k2H,k2L,f2] = Lookup2d(NcFANMap,PRFANMap,NcFANMtx(j,k,1),PRFANMtx(j,k,1));
        WcFANMtx(j,k,1) = LookupValue(k1H,k1L,f1,k2H,k2L,f2,1,1,1,WcFANMap);
    end
    
end

%Saves the values of maximum corrected thrust value at sea level and for
%the different values of Mach number
FNcMaxContMtx = FNcMtx(:,end)';

%Initializes NcMtx for building a complete matrix to be used by controller
NcMtx = NcFANMtx;

%Generates engine parameters to be saved in Engine.mat
EngineParsGen;

%Saves the matrices of thrust and fuel flow in a struct
% Parameter.FuelFlow = WfMtx;
% Parameter.NetThrust = FNMtx;
% Parameter.Altitude = AltLinVectorPT;
% Parameter.MN = MNVectorPT;
Parameter.FuelFlow = WfMtxPars;
Parameter.NetThrust = FNMtxPars;
Parameter.Altitude = AltLinVectorPT;
Parameter.MN = MNVectorPT;

save Engine.mat Parameter;

%Saves the corrected parameters matrices in a struct

CorrPar.FuelFlow = WfcMtx;
CorrPar.W2 = WcFANMtx;
CorrPar.Tt4 = Tt4cMtx;
CorrPar.Pt3 = Pt3cMtx;
CorrPar.Tt5 = Tt5cMtx;
CorrPar.Pt5 = Pt5cMtx;
CorrPar.RPM = NcMtx;
CorrPar.NetThrust = FNcMtx;
CorrPar.Delta = DeltaMtx;
CorrPar.Theta = ThetaMtx;
CorrPar.sqrTheta = sqrThetaMtx;
CorrPar.Altitude = AltLinVectorPT;
CorrPar.MN = MNVectorPT;

save CorrectedPars.mat CorrPar;
