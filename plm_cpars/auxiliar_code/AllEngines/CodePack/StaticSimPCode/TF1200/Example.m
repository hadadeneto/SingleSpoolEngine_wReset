
%This script shows an example on how to use the TJ1000 static model. The
%required inputs are Altitude, flight Mach number (MN), the day
%temperature increase dT (being the day temperature 
%represented as ISA + dT) and one of the following: Net Thrust (ThrustIn),
%entine core rotation speed (RPMIn), engine fuel flow (WfIn), or 
%combustion chamber total temperature (Tt4In). The outputs are the thrust, 
%the core rotation speed, the fuel flow and the combustion chamber total
%temperature considering the specified inputs. Whenever an input value is
%located outside the engine mapped region, the maximum or minimum mapped 
%input is considered. For instance, if one requires the input net thrust
%as being 7000 N and the maximum mapped value for the specified flight 
%conditions is 4500 N, then the value of 4500 N is considered as the 
%thrust input. For choosing which input to be used, the variable 
%WhichInput must be set as follows:

%WhichInput = 1 - sets net thrust as input;
%WhichInput = 2 - sets rotation speed as input;
%WhichInput = 3 - sets fuel flow as input;
%WhichInput = 4 - sets burner temperature as input;
%WhichInput = 5 - sets exhaust temperature as input;
%WhichInput = 6 - sets air inlet mass flow as input;

%For runing the example written below, just type 'Example' 
%in the MATLAB command window.

% %Input flight conditions
% Altitude = 567;
% MN = 0;
% dT = 13.6287;

Altitude = 0;
MN = 0.95;
dT = 0;

%Inlet pressure ratio
InletPR = 0.94;

%Input flight conditions
% Altitude = 1247;
% MN = 0.48;
% dT = 0;

%Input required variable
ThrustIn = 0;
% % RPMIn = 23042;
% RPMIn = 22000;
% WfIn = .12805;
% Tt4In = 1159;
% Tt5In = 992;
% W2In = 6.8;

RPMIn = 34200;
WfIn = .09;
Tt4In = 1150;
Tt5In = 992;
W2In = 5;

%Maximum allowed burner temperature
Tt4Max = 1150;
%Maximum additional rotation speed value allowed (percent value of design
%rotation speed)
RPMMax = 10; 

%Activation of Blow Out protection
ActiveBOut = 0;
ActiveOvertemp = 0;
ActiveOverspeed = 0;

%Chooses input
%WhichInput = 1 - sets net thrust as input;
%WhichInput = 2 - sets rotation speed as input;
%WhichInput = 3 - sets fuel flow as input;
%WhichInput = 4 - sets burner temperature as input;
%WhichInput = 5 - sets exhaust temperature as input;
%WhichInput = 6 - sets air inlet mass flow as input;
WhichInput = 2;

%Input computation
switch WhichInput
    case 1
        Input = ThrustIn;
        InputWord = ['Net Thrust     = ' num2str(Input) ' N'];
    case 2
        Input = RPMIn;
        InputWord = ['Rotation Speed = ' num2str(Input) ' RPM'];
    case 3
        Input = WfIn;
        InputWord = ['Fuel Flow      = ' num2str(Input) ' kg/s'];
    case 4
        Input = Tt4In;
        InputWord = ['Burner Temp    = ' num2str(Input) ' K'];
    case 5
        Input = Tt5In;
        InputWord = ['Exhaust Temp    = ' num2str(Input) ' K'];
    case 6
        Input = W2In;
        InputWord = ['Air Mass Flow   = ' num2str(Input) ' kg/s'];
end


%Loads Matrices - must be executed before model calculations
getCorMtx;

%Writes text with engine name and software version
EngVersionText;

%Calculates maximum rotation speed
RPMMax = (RPMMax + 100) * NDes / 100;
%Calculates steady model outputs
[Thrust,FNc,RPM,N2c,W2,W2c,Wf,Wfc,Pt3,Tt4,Tt5,Pt5,Tt4c,Tt5c,Tt2,Pt2] = EngineSteadyModel(Altitude, MN, dT, Input, InletPR, FNcMtx, N2cMtx, W2cMtx, WfcMtx, Pt3cMtx, Tt4cMtx, Tt5cMtx, Pt5cMtx, AltVec, MNVec, P0Vec, T0Vec, NDes, RU, Tt4Max, RPMMax, ActiveBOut, ActiveOvertemp, ActiveOverspeed, WhichInput);


disp(' ')
disp('------------------------------')
disp('         Inputs')
disp('------------------------------')
disp(['Altitude       = ' num2str(Altitude) ' m'])
disp(['Mach Number    = ' num2str(MN) ])
disp(['Day Temp       = ISA + ' num2str(dT)])
disp(InputWord)
disp('------------------------------')
disp(' ')
disp('------------------------------')
disp('           Outputs')
disp('------------------------------')
disp(['Thrust           = ' num2str(Thrust) ' N'])
disp(['Rotation Speed   = ' num2str(RPM) ' RPM'])
disp(['Fuel Flow        = ' num2str(Wf) ' kg/s'])
disp(['Burner Temp      = ' num2str(Tt4) ' K'])
disp(['Exhaust Temp     = ' num2str(Tt5) ' K'])
disp(['Air mass flow    = ' num2str(W2) ' kg/s'])
disp(['Total mass flow  = ' num2str(W2 + Wf) ' kg/s'])
disp('------------------------------')

