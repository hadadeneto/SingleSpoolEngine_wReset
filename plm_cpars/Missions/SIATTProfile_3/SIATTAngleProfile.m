

TICK = 200;
dT = 15;

% load 'airdata.mat';
% load 'tj_data_TJNetThrust.mat'
% load 'alt.mat'

load 'tjData_FlightPlan_2'

PhiVecDyn = nav_phi.v;
PhiVecDyn = PhiVecDyn';

ThetaVecDyn = nav_theta.v;
ThetaVecDyn = ThetaVecDyn';

TimeVector = t.v;
TimeVector = TimeVector';



IMax = TimeVector(end)/TICK * 1000;
IMax = int32(IMax);
ISum = length(TimeVector)/IMax;
ISum = int32(ISum);
%IMax = int32(length(TimeVector));
% 
% TimeVector(ISum)

% TimeVector(ISum)

for i = 1:IMax
        Index = min(length(TimeVector),i * ISum + 1);
        %TimeVector(Index)
        TimeAux(i) = TimeVector(Index);
        PhiAux(i) = PhiVecDyn(Index);
        ThetaAux(i) = ThetaVecDyn(Index);
end

TimeVector = TimeAux(1:(length(TimeAux)-1));
PhiVecDyn = PhiAux(1:(length(TimeAux)-1));
ThetaVecDyn = ThetaAux(1:(length(TimeAux)-1));

TimeVector = [0 TimeVector];
PhiVecDyn = [PhiVecDyn(1) PhiVecDyn];
ThetaVecDyn = [ThetaVecDyn(1) ThetaVecDyn];

%Converts to degrees 
PhiVecDyn = PhiVecDyn * 180 / pi;
ThetaVecDyn = ThetaVecDyn * 180 / pi;

figure(1)

subplot(2,1,1),plot(TimeVector,ThetaVecDyn,'b','LineWidth',2),ylabel('Theta (deg)'),title('Mission Angles'),grid on
subplot(2,1,2),plot(TimeVector,PhiVecDyn,'b','LineWidth',2),ylabel('Phi (deg)'),xlabel('Time (s)'),grid on

MissionName = 'SIATTAngles_2';
AngleGenCols(ThetaVecDyn,PhiVecDyn,TimeVector,MissionName)
