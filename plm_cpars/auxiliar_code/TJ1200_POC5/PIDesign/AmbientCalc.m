%-------------------------------------------------------------------
%THE FOLLOWING GAINS ARE USED IN THE SIMULINK MODEL WHICH CALCULATES
%AMBIENT CONDITIONS
%-------------------------------------------------------------------

%CONVERSION CONSTANTS FROM AMERICAN UNITS TO SI UNITS

Alt_AU2SI = 1/3.28084;
Area_AU2SI = 0.00064516;
h_AU2SI = 746*2.2046226;
P_AU2SI = 6894.7528;
T_AU2SI = 1/1.8;
Thrust_AU2SI = 1/2.2046226*9.8;
Vel_AU2SI = 0.3048;
W_AU2SI = 1/2.2046226;

%CONVERSION CONSTANTS FORM SI UNITS TO AMERICAN UNITS

Alt_SI2AU = 3.28084;
Area_SI2AU = 1/0.00064516;
h_SI2AU = 1/746/2.2046226;
P_SI2AU = 1/6892.92;
T_SI2AU = 1.8;
Thrust_SI2AU = 2.2046226/9.8;
Vel_SI2AU = 1/0.3048;
W_SI2AU = 2.2046226;

%DEFINITION OF INPUT AND OUTPUT GAINS FOR UNIT CORRECTION

Alt_GOut = Alt_AU2SI;
Area_GOut = Area_AU2SI;
h_GOut = h_AU2SI;
P_GOut = P_AU2SI;
T_GOut = T_AU2SI;
Thrust_GOut = Thrust_AU2SI;
Vel_GOut = Vel_AU2SI;
W_GOut = W_AU2SI;

Alt_GIn = Alt_SI2AU;
Area_GIn = Area_SI2AU;
h_GIn = h_SI2AU;
P_GIn = P_SI2AU;
T_GIn = T_SI2AU;
Thrust_GIn = Thrust_SI2AU;
Vel_GIn = Vel_SI2AU;
W_GIn = W_SI2AU;

%-----------------------------------------------------------------------
%CALCULATION OF AMBIENT TEMPERATURE AND PRESSUR FOR CORRECTED PARAMETERS
%-----------------------------------------------------------------------

TsimPT = 1;
% MNVectorPT = [0:0.1:0.9 0.95];
% AltLinVectorPT = 0:1000:12000;

TAmb = zeros(length(AltLinVectorPT),length(MNVectorPT));
PAmb = zeros(length(AltLinVectorPT),length(MNVectorPT));

open_system('PTCalcModel');

for i=1:length(AltLinVectorPT)
    
    AltVectorPT = AltLinVectorPT(i)*ones(1,length(MNVectorPT));
    dTVectorPT = 0*ones(1,length(MNVectorPT));
    TimeVectorPT = 0:TsimPT:(length(MNVectorPT)-1);
    
    %Simulation
    SimOut = sim('PTCalcModel','ReturnWorkspaceOutputs','on');
    
    Pt2Row = SimOut.get('Pt2Row');
    Tt2Row = SimOut.get('Tt2Row');
    
    TAmb(i,:) = Tt2Row';
    PAmb(i,:) = Pt2Row';
    
end

%Saves ambient conditions
Ambient.Tamb = TAmb;
Ambient.Pamb = PAmb;
save Ambient.mat Ambient;

