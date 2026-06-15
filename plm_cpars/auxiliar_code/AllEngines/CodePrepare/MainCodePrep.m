function MainCodePrep(MLFile,MLFilePath,HardBaseFile,HardBaseFold,HardBaseGen,FinalCodeFileName)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

% %Saves current path
% CurPath = pwd;
CurPath = pwd;

%Goes to hardware base file folder
cd([MLFilePath filesep HardBaseFold]);
%Opens Hardware file
fidHard = fopen(HardBaseFile,'r');
%Copies lines from the base main code
HardFileLines = ReadLines(fidHard);
%Closes file
fclose(fidHard);

%Goes to Matlab file path
cd(MLFilePath);
%Opens C file 
fidML = fopen(MLFile,'r');
%Copies lines from the base main code
MLFileLines = ReadLines(fidML);
%Closes file
fclose(fidML);

%Goes to 
cd(HardBaseGen);
%Creates temporary folder
TempFolder = 'Temp';
CodeGenMkDir(TempFolder,[]);
%Executes the separation of 
SaveCodePiece(MLFileLines,TempFolder);
%
CopyFromCodePiece(HardFileLines,[pwd filesep TempFolder],FinalCodeFileName);
%Comes back to previous path
cd(CurPath);


end

