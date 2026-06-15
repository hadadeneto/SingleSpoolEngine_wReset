
%Input flight conditions
Altitude = 4000;
MN = 0;
dT = 0;

%Input required variable
ThrustIn = 1700;
RPMIn = 20000;
WfIn = 0;

%Chose input
WhichInput = 3;

%Input computation
switch WhichInput
    case 1
        Input = ThrustIn;
    case 2
        Input = RPMIn;
    case 3
        Input = WfIn;
end


%Loads Matrices
[FNcMtx,N2cMtx,WfcMtx,MNVec,AltVec,P0Vec,T0Vec,NDes] = getMtx;

%Calculates steady model outputs
[Thrust,RPM,Wf] = TJ1000SteadyModel(Altitude, MN, dT, Input, FNcMtx, N2cMtx, WfcMtx, AltVec, MNVec, P0Vec, T0Vec, NDes, WhichInput);

disp('Results:')
disp(['Thrust         = ' num2str(Thrust) ' N'])
disp(['Rotation Speed = ' num2str(RPM) ' RPM'])
disp(['Fuel Flow      = ' num2str(Wf) ' kg/s'])