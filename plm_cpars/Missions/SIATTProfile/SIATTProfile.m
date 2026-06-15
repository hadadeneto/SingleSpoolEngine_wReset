
%ADDS STATIC CALCULATION PATH TO MATLAB
cd ..
word = [pwd filesep, 'TJ1000StaticSIATT'];
addpath(word);
cd SIATTProfile

TICK = 200;
dT = 15;

load 'airdata.mat';
load 'tj_data_TJNetThrust.mat'
load 'alt.mat'

AltVecDyn = v;
AltVecDyn = AltVecDyn';

MNVecDyn = airdata.Mach.v;
MNVecDyn = MNVecDyn';

RefVecDyn = tj_data_TJNetThrust.v;
RefVecDyn = RefVecDyn';

TimeVector = airdata.t.v;
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
        ThrustAux(i) = RefVecDyn(Index);
        AltAux(i) = AltVecDyn(Index);
        MNAux(i) = MNVecDyn(Index);
end

TimeVector = TimeAux(1:(length(TimeAux)-1));
AltVecDyn = AltAux(1:(length(TimeAux)-1));
MNVecDyn = MNAux(1:(length(TimeAux)-1));
RefVecDyn = ThrustAux(1:(length(TimeAux)-1));

TimeVector = [0 TimeVector];
AltVecDyn = [AltVecDyn(1) AltVecDyn];
MNVecDyn = [MNVecDyn(1) MNVecDyn];
RefVecDyn = [RefVecDyn(1) RefVecDyn];
dTVecDyn = dT * ones(1,length(TimeVector));
EngineCommand = 170 * ones(1,length(TimeVector));

MinThrust = 0;%1000;
%Sets REGIME commands to values no lower than MinThrust N
IndSIATT = find((RefVecDyn > 0));
for i = 1:length(RefVecDyn)
    if i > IndSIATT(1)
        if RefVecDyn(i) < MinThrust
            RefVecDyn(i) = MinThrust;
        end
    end
end

%Engine Shut Off command addition
IndSIATT = find((RefVecDyn > 0));
LengthShutOff = length(EngineCommand) - IndSIATT(end) + 1;
EngineCommand(IndSIATT(end):end) = 00 * ones(1,LengthShutOff);

% %ADAPTATION OF MISSION FOR STATIC TEST BENCHG - JACAREI CITY
% 
% %Generating Test Bench Mission for Jacarei city
% AltVecDyn = 567 * ones(1,length(AltVecDyn));
% MNVecDyn = zeros(1,length(MNVecDyn));
% 
% MaxRef = 3000;
% MinRef = 0.1;
% AddRef = 1000;
% 
% for i = 1:length(RefVecDyn)
%     if RefVecDyn(i) >= MinRef
%         RefVecDyn(i) = RefVecDyn(i) + AddRef;
%     end
%     if RefVecDyn(i) >= MaxRef
%         RefVecDyn(i) = MaxRef;
%     end
% end

AltTestBench = 567;
MNTestBench = 0;
dTTestBench = 15;

AltVecMission = AltVecDyn;
MNVecMission = MNVecDyn;
ThrustVecMission = RefVecDyn;
dTMission = 15;

[AltVecTB,MNVecTB,ThrustVecTB_RPMMatch,ThrustVecTB_WfMatch,RPMVecMission,RPMVecTB,WfVecMission,WfVecTB] = TestBenchAdapt(AltTestBench,MNTestBench,dTTestBench,AltVecMission,MNVecMission,ThrustVecMission,dTMission);

%GENERATION OF SHORTER VERSION

% %Generating shorter mission
% IH = 339;
% RefVecDyn = RefVecDyn(1:IH);
% AltVecDyn = AltVecDyn(1:IH);
% MNVecDyn = MNVecDyn(1:IH);
% TimeVector = TimeVector(1:IH);
% EngineCommand = EngineCommand(1:IH);
% EngineCommand(end) = 00;

%Generates SIATT mission to be executed at HIL and TM's test bench
% MissionGen(AltVecDyn,MNVecDyn,RefVecDyn,EngineCommand,TimeVector,'SIATTMission.csv')
MissionName = 'SIATTMission';
MissionGenCols(AltVecMission,MNVecMission,ThrustVecMission,EngineCommand,TimeVector,MissionName)

MissionName = 'SIATTMission_RPMMatch';
MissionGenCols(AltVecTB,MNVecTB,ThrustVecTB_RPMMatch,EngineCommand,TimeVector,MissionName)

MissionName = 'SIATTMission_WfMatch';
MissionGenCols(AltVecTB,MNVecTB,ThrustVecTB_WfMatch,EngineCommand,TimeVector,MissionName)

figure(1)

subplot(4,1,1),plot(TimeVector,AltVecMission,'b','LineWidth',2),hold on,plot(TimeVector,AltVecTB,'r:','LineWidth',2),ylabel('Alt (m)'),title('RPM Match - Flight: Solid Blue; Test Bench: Dotted Red'),grid on
subplot(4,1,2),plot(TimeVector,MNVecMission,'b','LineWidth',2),hold on,plot(TimeVector,MNVecTB,'r:','LineWidth',2),ylabel('MN'),grid on
subplot(4,1,3),plot(TimeVector,ThrustVecMission,'b','LineWidth',2),hold on,plot(TimeVector,ThrustVecTB_RPMMatch,'r:','LineWidth',2),ylabel('Thrust (N)'),grid on
subplot(4,1,4),plot(TimeVector,RPMVecMission,'b','LineWidth',2),hold on,plot(TimeVector,RPMVecTB,'r:','LineWidth',2),ylabel('RPM'),xlabel('Time (s)'),grid on

figure(2)

subplot(4,1,1),plot(TimeVector,AltVecMission,'b','LineWidth',2),hold on,plot(TimeVector,AltVecTB,'r:','LineWidth',2),ylabel('Alt (m)'),title('Fuel Flow Match - Flight: Solid Blue; Test Bench: Dotted Red'),grid on
subplot(4,1,2),plot(TimeVector,MNVecMission,'b','LineWidth',2),hold on,plot(TimeVector,MNVecTB,'r:','LineWidth',2),ylabel('MN'),grid on
subplot(4,1,3),plot(TimeVector,ThrustVecMission,'b','LineWidth',2),hold on,plot(TimeVector,ThrustVecTB_WfMatch,'r:','LineWidth',2),ylabel('Thrust (N)'),grid on
subplot(4,1,4),plot(TimeVector,WfVecMission,'b','LineWidth',2),hold on,plot(TimeVector,WfVecTB,'r:','LineWidth',2),ylabel('Fuel Flow (kg/s)'),xlabel('Time (s)'),grid on



% hold on
% 
% subplot(3,1,1),plot(TimeVector,AltVecTB,'r:','LineWidth',2)
% subplot(3,1,2),plot(TimeVector,MNVecTB,'r:','LineWidth',2)
% subplot(3,1,3),plot(TimeVector,ThrustVecTB,'r:','LineWidth',2)


%REMOVES STATIC CALCULATION PATH FROM MATLAB
cd ..
word = [pwd filesep, 'TJ1000StaticSIATT'];
rmpath(word);
cd SIATTProfile






