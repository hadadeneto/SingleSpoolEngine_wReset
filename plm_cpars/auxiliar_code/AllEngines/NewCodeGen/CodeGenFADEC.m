

%Defines current device
Device = 'FADEC';

%Outisde folders
Level_Sep_Constants = ['..' File_Sep Device '_Constants_H' File_Sep];
Level_Sep_Defines = ['..' File_Sep '..' File_Sep Device '_Defines_H' File_Sep];
Level_Sep = ['..' File_Sep Device '_get_H' File_Sep];

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

%Folder for placing ConstantsXXX.h
hFolderConstName = [EngFoldName File_Sep EngineName File_Sep Device '_Constants_H'];
%Creates corresponding folders
CodeGenMkDir('',hFolderConstName);

%WRITES THE .h FILE CONTAINING ALL getXXXMtx and getXXXVec functions used
%by FADEC only
List = getXXXMtxVecH(hFolderName,EngineName,Device,RetType,ArgType,ArgName,GetFADECMatrices);
%Generates the .c and .h of getXXXFADECMtx for the current engine
CodeGengetXXXMtx(cFolderName, hFolderName, CallsFolderName, File_Sep, EngineName, VarsPerLine, RetType, ArgType, Device, GetFADECMatrices);

%-------------------------------
%COPIES .c FILES TO FADEC FOLDER
%-------------------------------

%Copies FADEC required .c files to 'Mtx' folder
CopyCList(cFolderName,'Mtx',SourceFolder,List);

%----------------------------------------------------------
%PRINTS FUNCTION FOR OBTAINING CONTROLLER CONSTANTS .h FILE
%----------------------------------------------------------

%Prints function for fobtaining controller constants .h file
CodeGengetXXXContConst(hFolderName,cFolderName,EngineName,Device,Level_Sep_Defines,Level_Sep_Constants,ContConstAll);

%-----------------------------------------
%CREATES FUNCTION DEFINING VARIABLES SIZES
%-----------------------------------------

%Creates function defining variables sizes
CodeGenSizeConst(hFolderName,cFolderName,CallsFolderName,RetType,ArgTypeInt,VarsPerLine,EngineName,Device,Level_Sep,Level_Sep_Constants,File_Sep,SizeVarsFADEC,SizeDefsFADEC);
