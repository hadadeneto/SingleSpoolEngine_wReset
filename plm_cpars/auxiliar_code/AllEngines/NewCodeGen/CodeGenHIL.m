
%FADEC Folders
Device = 'FADEC';
Level_Sep_Constants = ['..' File_Sep Device '_Constants_H' File_Sep];
Level_Sep_Defines = ['..' File_Sep '..' File_Sep Device '_Defines_H' File_Sep];


%Defines current device
Device = 'HIL';

%-------------------
%BREAKPOINT VECTORS
%-------------------

%Type of function argument
% ArgType = 'double';
ArgType = 'floating';
ArgTypeInt = 'int';
%Name of function argument
ArgName = ' *Pointer';
%Type of returned variable
RetType = 'void';

%.c folder and .h folder names
cFolderName = [EngFoldName File_Sep EngineName File_Sep Device '_get_C'];
hFolderName = [EngFoldName File_Sep EngineName File_Sep Device '_get_H'];
%Creates corresponding folders
CodeGenMkDir(cFolderName,hFolderName);

%Folders level separation
Level_Sep = ['..' File_Sep Device '_get_H' File_Sep];

%WRITES THE .h FILE CONTAINING ALL getXXXMtx and getXXXVec functions used
%by HIL only
List = getXXXMtxVecH(hFolderName,EngineName,Device,RetType,ArgType,ArgName,GetHILMatrices);
%Generates the .c and .h of getXXXMtx for the current engine
CodeGengetXXXMtx(cFolderName, hFolderName, CallsFolderName, File_Sep, EngineName, VarsPerLine, RetType, ArgType, Device, GetHILMatrices);

%-------------------------------
%COPIES .c FILES TO FADEC FOLDER
%-------------------------------

%Copies HIL required .c files to 'Mtx' folder
CopyCList(cFolderName,'Mtx',SourceFolder,List);

%---------------------------------------
%GENERATES FUNCTIONS INHERENT TO HIL ONL
%---------------------------------------

%Generates the .h of getXXXStartPars
CodeGengetXXXStartPars(hFolderName,cFolderName,EngineName,Device,Level_Sep_Constants,Level_Sep_Defines,StartAll);

CodeGenSizeConst(hFolderName,cFolderName,CallsFolderName,RetType,ArgTypeInt,VarsPerLine,EngineName,Device,Level_Sep,Level_Sep_Constants,File_Sep,SizeVarsHIL,SizeDefsHIL);

CodeGengetXXXEngConst(hFolderName,cFolderName,ArgType,EngineName,Device,Level_Sep_Constants,Level_Sep_Defines,EngConstAll);
