
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

%Desired temperature step
dTVec = -55 : 5 : 40;

%Definition of standard parameters in SI units
PSTD = 101325;
TSTD = 288.15;
gamma = 1.4;

%TISA static temperature as a function of altitude
TISAMtx = TSTD * ThetaMtx(:,1)';
PISAMtx = PSTD * DeltaMtx(:,1);

%lengths for matrices
lenAlt = length(AltVec);
lenMN = length(MNVec);
lendT = length(dTVec);
[~,lenN2c] = size(N2cMtx);

%Declaracion of 3D matrices
FN3D = zeros(lenMN,lenN2c,lenAlt);
RPM3D = zeros(lenMN,lenN2c,lenAlt);
Wf3D = zeros(lenMN,lenN2c,lenAlt);
%Declaration of 4D matrices
FN4D = zeros(lenMN,lenN2c,lenAlt,lendT);
RPM4D = zeros(lenMN,lenN2c,lenAlt,lendT);
Wf4D = zeros(lenMN,lenN2c,lenAlt,lendT);

%i - dT
%j - Altitude
%k - MN
%l - Power
%Order of elements: (k,l,j,i)
for i = 1:lendT
    
    dT = dTVec(i);
    
    %
    for j = 1:lenAlt
        
        %Calcualtes static temperature taking into account dT
        Ts2 = TISAMtx(j) + dT;
        
        %
        for k = 1:lenMN
            
            %Calculation of total temperature and Theta
            MN = MNVec(k);
            Tt2 = Ts2 * (1 + MN^2 * (gamma-1) / 2);
            Theta = Tt2 / TSTD;
            Delta = DeltaMtx(j,k);
            
            %Computes 3D matrices 
            for l = 1:lenN2c
                
                if(k == 1 && l == 16 && j == 1 && i == 20)
                    stophere = 1;
                end
%                 WORD = ['i = ' num2str(i) ';' 'j = ' num2str(j) ';' 'k = ' num2str(k) ';' 'l = ' num2str(l) ';' ];
%                 disp(WORD)
                RPM3D(k,l,j) = N2cMtx(k,l,1) * sqrt(Theta);
                FN3D(k,l,j) = FNcMtx(k,l,1) * sqrt(Theta);
                Wf3D(k,l,j) = WfcMtx(k,l,1) * sqrt(Theta) * DeltaMtx(j,k);
            end
        end
    end
    
    %Computes 4D matrices
    FN4D(:,:,:,i) = FN3D;
    RPM4D(:,:,:,i) = RPM3D * NDes;
    Wf4D(:,:,:,i) = Wf3D;
    
end

Parameter.RPM = RPM4D;
Parameter.NetThrust = FN4D;
Parameter.FuelFlow = Wf4D;
Parameter.Altitude = AltVec;
Parameter.M = MNVec;
Parameter.dT = dTVec;

save 'StaticModel' Parameter;

%Example of 4D matrix - B
% A(:,:,1) = [1 1 1;1 1 1];
% A(:,:,2) = [2 2 2;2 2 2];
% B(:,:,:,1) = A;
% B(:,:,:,2) = 10 * A;
% B