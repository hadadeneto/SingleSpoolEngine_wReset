

%Defines current device
Device = 'HIL';

%-------------------
%BREAKPOINT VECTORS
%-------------------

%Type of function argument
ArgType = 'double';
%Name of function argument
ArgName = ' *Pointer';
%Type of returned variable
RetType = 'void';

%.c folder and .h folder names
cFolderName = ['c_Files_' Device];
hFolderName = ['h_Files_' Device];
%Creates corresponding folders
CodeGenMkDir(cFolderName,hFolderName);

%Folders level separation
Level_Sep = ['../' hFolderName '/'];

%WRITES THE .h FILE CONTAINING ALL getXXXMtx and getXXXVec functions used
%by HIL only
List = getXXXMtxVecH(hFolderName,EngineName,Device,RetType,ArgType,ArgName,GetHILMatrices);
%Generates the .c and .h of getXXXMtx for the current engine
CodeGengetXXXMtx(cFolderName, hFolderName, EngineName, VarsPerLine, RetType, ArgType, Device, GetHILMatrices);

%-------------------------------
%COPIES .c FILES TO FADEC FOLDER
%-------------------------------

%Copies HIL required .c files to 'Mtx' folder
CopyCList(cFolderName,'Mtx',SourceFolder,List);

%---------------------------------------
%GENERATES FUNCTIONS INHERENT TO HIL ONL
%---------------------------------------

%Generates the .h of getXXXStartPars
CodeGengetXXXStartPars(hFolderName,cFolderName,EngineName,Device,Level_Sep,StartAll);

CodeGenSizeConst(hFolderName,cFolderName,RetType,ArgType,VarsPerLine,EngineName,Device,Level_Sep,SizeVars,SizeDefs);

CodeGengetXXXEngConst(hFolderName,cFolderName,ArgType,EngineName,Device,Level_Sep,EngConstAll);
