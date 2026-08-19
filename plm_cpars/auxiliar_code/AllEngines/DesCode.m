
%Engine Folder Name Options - must match the corresponding engine folder
%   'TJ1200_POC6_Boosted - TJ1200 with additional linearizatoin points'
%   'TF1200'             - Single Spool Turbofan
%   'GEJ85'              - GE-J85 13 Engine

clear %all

%Chosen project
EngFoldName = 'TJ1200_POC6_Boosted';
% EngFoldName = 'TF1200';
% EngFoldName = 'GEJ85';
% EngFoldName = 'TJ700';
% EngFoldName = 'TJ200';
% EngFoldName = 'TJ40';
% EngFoldName = 'GET700_Turboshaft';
% EngFoldName = 'TG200_Turboshaft';
% EngFoldName = 'TJ300_AxRad';
EngFoldName = 'TJ300_Radial';

%ProjectName variable is used by backup routine
Project = EngFoldName;


File_Sep = '/';

%Sets the host folder
SetHostFolder

%Complements folder name
EngFoldName = ['Engines' File_Sep EngFoldName];

%Calls script to perform above actions
MainScript
