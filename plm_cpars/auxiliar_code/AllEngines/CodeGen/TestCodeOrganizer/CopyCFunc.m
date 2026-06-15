

%

%Opens file list
load('HILFuncList.mat')
TotalFiles = length(HILFuncList);

%Specifies source and sink files, and makes sink files
SourceFile = 'SSModelCFunc';
SinkFile = 'ModelCFunc';
mkdir(SinkFile);

%Copy every file specified in the list an present in the source file to the
%sink file
for i = 1:TotalFiles
    SourceWord = [SourceFile filesep HILFuncList{i}];
    SinkWord = SinkFile;
    copyfile(SourceWord,SinkWord);
end

%NOTE:

%The followint 3 folders have been compared with WinMerge:
%       - SSModelCFunc\TJ1200\Mtx
%       - CodeGen_Model
%       - ModelCFunc\TJ1200\Mtx

%It turns out that the function getTJ1200Mtx.c is not present only on
%CodeGen_Model and should be created by it. This file is present in the
%remainig folders
%The functions that are present on the CodeGen_Model and not on the
%remaining folders are the additional windmill and sub-idle modle functions
%which will be shortly added.
