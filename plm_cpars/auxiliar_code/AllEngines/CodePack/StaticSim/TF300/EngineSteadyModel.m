function [Thrust,FNc,RPM,N2c,W2,W2c,Wf,Wfc,Pt3,Tt4,Tt5,Pt5,Tt4c,Tt5c,Tt2,Pt2] = EngineSteadyModel(Altitude, MN, dT, Input, InletPR, FNcMtx, N2cMtx, W2cMtx, WfcMtx, Pt3cMtx, Tt4cMtx, Tt5cMtx, Pt5cMtx, AltVec, MNVec, P0Vec, T0Vec, NDes, RU, Tt4Max, RPMMax, ActiveBOut, ActiveOvertemp, ActiveOverspeed, WhichInput)
%EngineSteadyModel calculates the values of RPM and Wf from required thrust
%   Detailed explanation goes here

%Defines the vaule of gamma air
gamma = 1.4;

%Calculates the values of P0 and T0 according to altitude
[k1H,k1L,f1,~] = Lookup1d(Altitude,AltVec);
Ps2 = LookupValue(k1H,k1L,f1,1,1,1,1,1,1,P0Vec);
Ts2 = LookupValue(k1H,k1L,f1,1,1,1,1,1,1,T0Vec);

%Updates the value of Ts2 by adding dT value
Ts2 = Ts2 + dT;

%Calculates the basic relation for obtaining total pressure and temperature
funcMN = (1 + MN^2 * (gamma-1)/2);

%Calculates total values of temperature and pressure
Tt2 = Ts2 * funcMN;
Pt2 = Ps2 * funcMN^(gamma/(gamma-1));

%Takes into account inlet pressure ratio
Pt2 = Pt2 * InletPR;

%Calculates values of theta and delta
Theta = Tt2/288.15;
Delta = Pt2/101325;

%Initiates Mtx3D and Input
[row,col] = size(FNcMtx);
Mtx2D = zeros(row,col);
InputC = Input;

%Initializatoin of protection texts
Space      = '';
Lineup     = '';
Text       = '';
LineBottom = '';

%While Loop flag
RoutineOn = 1;

while RoutineOn == 1
    
    %Updates RoutineOn flag
    RoutineOn = 0;
    %Next protection flag
    NextProtection = 1;
    
    %Calculates the value of corrected input
    switch WhichInput
        case 1
            InputC = Input / Delta;
            Mtx2D = FNcMtx;
        case 2
            InputC = Input / sqrt(Theta) / NDes;
            Mtx2D = N2cMtx;
        case 3
            InputC = Input / sqrt(Theta) / Delta;
            Mtx2D = WfcMtx;
        case 4
            InputC = Input / Theta;
            Mtx2D = Tt4cMtx;
        case 5
            InputC = Input / Theta;
            Mtx2D = Tt5cMtx;
        case 6
            InputC = Input * sqrt(Theta) / Delta;
            Mtx2D = W2cMtx;
        case 7
            InputC = Input;
            Mtx2D = N2cMtx;
    end
    
    %Finds the position of FNc within FNcMtx
    [k1H,k1L,f1,k2H,k2L,f2] = Lookup2d(MNVec,Mtx2D,MN,InputC);
    k3H = 1;
    k3L = 1;
    f3 = 0;
    
    %Calculates the value corrected ouptuts
    FNc = LookupValue(k1H,k1L,f1,k2H,k2L,f2,k3H,k3L,f3,FNcMtx);
    N2c = LookupValue(k1H,k1L,f1,k2H,k2L,f2,k3H,k3L,f3,N2cMtx);
    W2c = LookupValue(k1H,k1L,f1,k2H,k2L,f2,k3H,k3L,f3,W2cMtx);
    Wfc = LookupValue(k1H,k1L,f1,k2H,k2L,f2,k3H,k3L,f3,WfcMtx);
    Tt4c = LookupValue(k1H,k1L,f1,k2H,k2L,f2,k3H,k3L,f3,Tt4cMtx);
    Pt3c = LookupValue(k1H,k1L,f1,k2H,k2L,f2,k3H,k3L,f3,Pt3cMtx);
    Tt5c = LookupValue(k1H,k1L,f1,k2H,k2L,f2,k3H,k3L,f3,Tt5cMtx);
    Pt5c = LookupValue(k1H,k1L,f1,k2H,k2L,f2,k3H,k3L,f3,Pt5cMtx);
       
    %Calculates the values of outputs
    Thrust = FNc * Delta;
    RPM = N2c * sqrt(Theta) * NDes;
    W2 = W2c * Delta / sqrt(Theta);
    Wf = Wfc * sqrt(Theta) * Delta;
    Tt4 = Tt4c * Theta;
    Pt3 = Pt3c * Delta;
    Tt5 = Tt5c * Theta;
    Pt5 = Pt5c * Delta;
    
    %Calculates the minimum fuel flow
    WfMin = Pt3 * RU;

%Verifies if blow out protection is required and determinies conditions
%for a next calculation
if ((ActiveBOut == 1)&&(WfMin > Wf)&&(NextProtection == 1))
    
    Input = FindWfMin(MNVec,MN,RU,Delta,Theta,Pt3cMtx,WfcMtx);
    WhichInput = 3;
    RoutineOn = 1;
    ActiveBOut = 0;
    NextProtection = 0;
    
    %Message lines
    Space      = ' ';
    Lineup     = '============================';
    Text       = 'BLOW OUT PROTECION IS ACTIVE';
    LineBottom = '============================';
end


%Verifies if temperature protection is required and determinies conditions
%for a next calculation
if ((ActiveOvertemp == 1)&&(Tt4 > Tt4Max)&&(NextProtection == 1))
    
    Input = Tt4Max;
    WhichInput = 4;
    RoutineOn = 1;
    ActiveOvertemp = 0;
    NextProtection = 0;
    
    %Message lines
    Space      = ' ';
    Lineup     = '======================================';
    Text       = 'BURNER TEMPERATURE PROTECION IS ACTIVE';
    LineBottom = '======================================';
    
end

%Verifies if temperature protection is required and determinies conditions
%for a next calculation
if ((ActiveOverspeed == 1)&&(RPM > RPMMax)&&(NextProtection == 1))
    
    Input = RPMMax;
    WhichInput = 2;
    RoutineOn = 1;
    ActiveOverspeed = 0;
    NextProtection = 0;
    
    %Message lines
    Space      = ' ';
    Lineup     = '=============================';
    Text       = 'OVERSPEED PROTECION IS ACTIVE';
    LineBottom = '=============================';
end
    
end

%Displays protection test
disp(Space);
disp(Lineup);
disp(Text);
disp(LineBottom);

end

