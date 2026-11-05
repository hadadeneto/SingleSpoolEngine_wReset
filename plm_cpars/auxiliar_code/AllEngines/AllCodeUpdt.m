
%Sets the engine lists
SetEngineList;

%Flag indicating that only C code must be aquired
getCCodeOnly = 1;

%EXECUTION OF DESCODE FOR ALL PROJECTS AND GETTING C CODE ONLY

%Loop for updating C code for all projects in list
for i = 1:length(ProjectList)
    %Sets the folder name
    EngFoldName = ProjectList{i};
    %ProjectName variable is used by backup routine
    Project = EngFoldName;
    %Sets file separator
    File_Sep = '/';
    %Sets the host folder
    SetHostFolder
    %Complements folder name
    EngFoldName = ['Engines' File_Sep EngFoldName];
    %Calls script to perform above actions
    MainScript
    %Sets software in the loop simulation for code compilation and testing
    SetSIL
    %Clear all vars except ProjectList and i
    clearvars -except getCCodeOnly ProjectList i
end

disp(' ')
disp('CODE UPDATED FOR ALL PROJECTS!!')
disp(' ')

% %Goes two levels up for compilig updated code
% cd ..
% cd ..
% %Executes compilatoin command
% CompileCSFun