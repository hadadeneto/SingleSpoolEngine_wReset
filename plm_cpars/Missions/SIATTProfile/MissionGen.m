function MissionGen(Alt,MN,ThrustRef,EngineCommand,time,MissionName)
%                KpPt3P,KiPt3P,KpTt4P,KiTt4P,KpEPRP,KiEPRP,...
%                RPM,EPR,Pt3,Tt4,FN,FNper)

%     function PritToFile(A,B,...
%     Pt3C, Pt3D, Tt3C, Tt3D,...
%     Tt4C, Tt4D,...
%     Pt5C, Pt5D, Tt5C, Tt5D,...
%     N_Kp, N_Ki, Pt3_Kp, Pt3_Ki,...
%     Tt4_Kp, Tt4_Ki, Tt5_Kp, Tt5_Ki,...
%     NcFAN,...
%     Pt3, Tt3,...
%     Wf, Tt4,...
%     Pt5, Tt5,...
%     FN, FNper, ...
%     NcHPCMap, WcHPCMap, EffHPCMap, PRHPCMap, ...
%     NcHPTMap, WcHPTMap, EffHPTMap, PRHPTMap, ...
%     PRHPCStall, WcHPCStall, ...
%     FNperCont,NcFANCont,EngineName)

%     function MissionGen()

%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%-------------------
%BREAKPOINT VECTORS
%-------------------

%     %Type of function argument
%     ArgType = 'double';
%     %Name of function argument
%     ArgName = '*Pointer';
%     %Type of returned variable
%     RetType = 'void';
%
%Creates a folders for organizing files
%     mkdir Missions
%     mkdir c_Files
%
%     cFolderName = 'c_Files';
%     hFolderName = 'h_Files';

%     MissionFolderName = 'MyMission';
% MissionName = 'MyMission.csv';
% ThrustRef = [1000 2000 3000 4000 5000];
% Alt = [0 10 20 30 40];
% MN = [0.3 0.4 0.5 0.6 0.7];
% time = [0 1 2 3 4];


%Opens a .h document for defining the function that acquires matrices
fid = fopen(MissionName,'w');

%Prints each command line of the mission to be accomplished
PrintRow(fid,Alt);
PrintRow(fid,MN);
PrintRow(fid,ThrustRef);
PrintRow(fid,EngineCommand);
PrintRow(fid,time);

%closes the generated .txt file
fclose(fid);
disp(' ')
word = ['FILE ' MissionName ' GENERATED'];
disp(word)
disp(' ') 

end