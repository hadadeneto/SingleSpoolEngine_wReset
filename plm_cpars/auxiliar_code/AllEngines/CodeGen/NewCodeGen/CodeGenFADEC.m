

%Defines current device
Device = 'FADEC';

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
cFolderName = [Device '_get_C'];
hFolderName = [Device '_get_H'];
%Creates corresponding folders
CodeGenMkDir(cFolderName,hFolderName);

%Folders level separation
Level_Sep = ['../' hFolderName '/'];

%WRITES THE .h FILE CONTAINING ALL getXXXMtx and getXXXVec functions used
%by FADEC only
List = getXXXMtxVecH(hFolderName,EngineName,Device,RetType,ArgType,ArgName,GetFADECMatrices);
%Generates the .c and .h of getXXXFADECMtx for the current engine
CodeGengetXXXMtx(cFolderName, hFolderName, EngineName, VarsPerLine, RetType, ArgType, Device, GetFADECMatrices);

%-------------------------------
%COPIES .c FILES TO FADEC FOLDER
%-------------------------------

%Copies FADEC required .c files to 'Mtx' folder
CopyCList(cFolderName,'Mtx',SourceFolder,List);

%----------------------------------------------------------
%PRINTS FUNCTION FOR OBTAINING CONTROLLER CONSTANTS .h FILE
%----------------------------------------------------------

%Prints function for fobtaining controller constants .h file
CodeGengetXXXContConst(hFolderName,cFolderName,EngineName,Device,Level_Sep,ContConstAll);

