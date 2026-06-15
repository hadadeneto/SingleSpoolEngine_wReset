
% Simout = sim('Mission_1','ReturnWorkspaceOutputs','on');
% Simout = sim('Mission_2','ReturnWorkspaceOutputs','on');
% Simout = sim('Mission_Visit_2023_06_19','ReturnWorkspaceOutputs','on');
% Simout = sim('Mission_Visit_2023_08_09','ReturnWorkspaceOutputs','on');
% Simout = sim('Mission_TJ1000_ResponseTest','ReturnWorkspaceOutputs','on');
% Simout = sim('Mission_TJ700_ResponseTest','ReturnWorkspaceOutputs','on');
% Simout = sim('Mission_TJ200_ResponseTest','ReturnWorkspaceOutputs','on');
% Simout = sim('Mission_GEJ85_ResponseTest','ReturnWorkspaceOutputs','on');
Simout = sim('Mission_TJ40_ResponseTest','ReturnWorkspaceOutputs','on');


time = Simout.simout.time;
ThrustRef = Simout.simout.data;
Alt = 567 * ones(1,length(time));
MN = 0 * ones(1,length(time));
EngineCommand = 170 * ones(1,length(time));
EngineCommand(end) = 0;
% MissionName = 'MissionTB_001';
%MissionName = 'MissionTII_001';
% MissionName = 'Mission_Visit_2023_06_19';
% MissionName = 'Mission_Visit_2023_08_09';
% MissionName = 'Mission_TJ1000_ResponseTest';
% MissionName = 'Mission_TJ700_ResponseTest';
% MissionName = 'Mission_TJ200_ResponseTest';
% MissionName = 'Mission_GEJ85_ResponseTest';
MissionName = 'Mission_TJ40_ResponseTest';

MissionGenCols(Alt,MN,ThrustRef,EngineCommand,time,MissionName);