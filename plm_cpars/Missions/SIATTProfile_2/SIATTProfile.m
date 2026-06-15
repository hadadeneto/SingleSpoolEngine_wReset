
%ADDS STATIC CALCULATION PATH TO MATLAB
cd ..
word = [pwd filesep, 'TJ1000StaticSIATT'];
addpath(word);
cd SIATTProfile_2

% CREATES FOLDERS AND SUBFOLDERS FOR SAVING MISSION FILES

%Name of each separate folder
MainFolder = 'MissionsISAdT';
FilesFolder = 'Missions';
RPMMatchFolder = 'RPMMatch';
WfMatchFolder = 'WfMatch';
OriginalFolder = 'Original';
XLSXFolder = 'XLSX';
CSVFolder = 'CSV';
FigureFolder = 'FigsPNG';

% Names the folders
Originalword = [pwd filesep MainFolder filesep FilesFolder filesep OriginalFolder];

RPMMatchXLSXword = [pwd filesep MainFolder filesep FilesFolder filesep RPMMatchFolder...
                    filesep XLSXFolder];
RPMMatchCSVword = [pwd filesep MainFolder filesep FilesFolder filesep RPMMatchFolder...
                    filesep CSVFolder];
                
WfMatchXLSXword = [pwd filesep MainFolder filesep FilesFolder filesep WfMatchFolder...
                    filesep XLSXFolder];

WfMatchCSVword = [pwd filesep MainFolder filesep FilesFolder filesep WfMatchFolder...
                    filesep CSVFolder];                
                
FigureFolderword = [pwd filesep MainFolder filesep FigureFolder];

% Creates each file of the structure if they do not exist
if(exist(RPMMatchXLSXword, 'dir') == 0)
    mkdir(RPMMatchXLSXword)
end
if(exist(RPMMatchCSVword, 'dir') == 0)
    mkdir(RPMMatchCSVword)
end
if(exist(WfMatchXLSXword, 'dir') == 0)
    mkdir(WfMatchXLSXword)
end
if(exist(WfMatchCSVword, 'dir') == 0)
    mkdir(WfMatchCSVword)
end
if(exist(FigureFolderword, 'dir') == 0)
    mkdir(FigureFolderword)
end
if(exist(Originalword, 'dir') == 0)
    mkdir(Originalword)
end



TICK = 200;
dT = 15;

% load 'airdata.mat';
% load 'tj_data_TJNetThrust.mat'
% load 'alt.mat'

load 'tjData_FlightPlan_2'

AltVecDyn = alte.v;
AltVecDyn = AltVecDyn';

MNVecDyn = mache.v;
MNVecDyn = MNVecDyn';

RefVecDyn = netThrustCmd.v;
RefVecDyn = RefVecDyn';

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
dTTestBench = 25;

AltVecMission = AltVecDyn;
MNVecMission = MNVecDyn;
ThrustVecMission = RefVecDyn;
dTMission = 15;

SaveFigs = 1;

[AltVecTB,MNVecTB,ThrustVecTB_RPMMatch,ThrustVecTB_WfMatch,RPMVecMission,RPMVecTB,WfVecMission,WfVecTB,RPMVecNoMatch,WfVecNoMatch] = TestBenchAdapt(AltTestBench,MNTestBench,dTTestBench,AltVecMission,MNVecMission,ThrustVecMission,dTMission);

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
MissionName = ['SIATTMission_2_ISA_' num2str(dTMission)];
MissionNameCSV = [Originalword filesep MissionName '.csv'];
MissionNameExcel = [Originalword filesep MissionName '.xlsx'];
MissionGenCols(AltVecMission,MNVecMission,ThrustVecMission,EngineCommand,TimeVector,MissionNameCSV,MissionNameExcel)

MissionName = [ 'SIATTMission_2_RPMMatch_ISA_' num2str(dTTestBench)];
MissionNameCSV = [RPMMatchCSVword filesep MissionName '.csv'];
MissionNameExcel = [RPMMatchXLSXword filesep MissionName '.xlsx'];
MissionGenCols(AltVecTB,MNVecTB,ThrustVecTB_RPMMatch,EngineCommand,TimeVector,MissionNameCSV,MissionNameExcel)

MissionName = ['SIATTMission_2_WfMatch_ISA_' num2str(dTTestBench)];
MissionNameCSV = [WfMatchCSVword filesep MissionName '.csv'];
MissionNameExcel = [WfMatchXLSXword filesep MissionName '.xlsx'];
MissionGenCols(AltVecTB,MNVecTB,ThrustVecTB_WfMatch,EngineCommand,TimeVector,MissionNameCSV,MissionNameExcel)

fig = figure(1);
TitleCell = {['RPM Match'],['Blue Solid: Flight ISA + ' num2str(dTMission)],['Red Dot: Test Bench ISA + ' num2str(dTTestBench)]};
subplot(5,1,1),plot(TimeVector,AltVecMission,'b','LineWidth',2),hold on,plot(TimeVector,AltVecTB,'r:','LineWidth',2),ylabel('Alt (m)'),title(TitleCell),grid on
subplot(5,1,2),plot(TimeVector,MNVecMission,'b','LineWidth',2),hold on,plot(TimeVector,MNVecTB,'r:','LineWidth',2),ylabel('MN'),grid on
subplot(5,1,3),plot(TimeVector,ThrustVecMission,'b','LineWidth',2),hold on,plot(TimeVector,ThrustVecTB_RPMMatch,'r:','LineWidth',2),ylabel('Thrust (N)'),grid on
subplot(5,1,4),plot(TimeVector,RPMVecMission,'b','LineWidth',2),hold on,plot(TimeVector,RPMVecTB,'r:','LineWidth',2),ylabel('RPM'),grid on
subplot(5,1,5),plot(TimeVector,WfVecMission,'b','LineWidth',2),hold on,plot(TimeVector,WfVecNoMatch,'r:','LineWidth',2),ylabel('Fuel Flow (kg/s)'),xlabel('Time (s)'),grid on

if SaveFigs == 1
    Namefig = [FigureFolderword filesep 'M2_RPM_ISA_' num2str(dTTestBench) '.png'];
    FigAutoSave(Namefig,fig)
end

fig = figure(2);
TitleCell = {['Fuel Flow Match'],['Blue Solid: Flight ISA + ' num2str(dTMission)],['Red Dot: Test Bench ISA + ' num2str(dTTestBench)]};
subplot(5,1,1),plot(TimeVector,AltVecMission,'b','LineWidth',2),hold on,plot(TimeVector,AltVecTB,'r:','LineWidth',2),ylabel('Alt (m)'),title(TitleCell),grid on
subplot(5,1,2),plot(TimeVector,MNVecMission,'b','LineWidth',2),hold on,plot(TimeVector,MNVecTB,'r:','LineWidth',2),ylabel('MN'),grid on
subplot(5,1,3),plot(TimeVector,ThrustVecMission,'b','LineWidth',2),hold on,plot(TimeVector,ThrustVecTB_WfMatch,'r:','LineWidth',2),ylabel('Thrust (N)'),grid on
subplot(5,1,4),plot(TimeVector,RPMVecMission,'b','LineWidth',2),hold on,plot(TimeVector,RPMVecNoMatch,'r:','LineWidth',2),ylabel('RPM'),grid on
subplot(5,1,5),plot(TimeVector,WfVecMission,'b','LineWidth',2),hold on,plot(TimeVector,WfVecTB,'r:','LineWidth',2),ylabel('Fuel Flow (kg/s)'),xlabel('Time (s)'),grid on

if SaveFigs == 1
    Namefig = [FigureFolderword filesep 'M2_FF_ISA_' num2str(dTTestBench) '.png'];
    FigAutoSave(Namefig,fig)
end

% hold on
% 
% subplot(3,1,1),plot(TimeVector,AltVecTB,'r:','LineWidth',2)
% subplot(3,1,2),plot(TimeVector,MNVecTB,'r:','LineWidth',2)
% subplot(3,1,3),plot(TimeVector,ThrustVecTB,'r:','LineWidth',2)


%REMOVES STATIC CALCULATION PATH FROM MATLAB
cd ..
word = [pwd filesep, 'TJ1000StaticSIATT'];
rmpath(word);
cd SIATTProfile_2






