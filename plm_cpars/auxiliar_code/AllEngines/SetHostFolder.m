%Folder hosting software-in-the-loop simulation content
HostFolder = 'SSModelCFunc';
%Set TMATS data folder name
TMATSFolder = 'TMATSData';
%Sets TMATS folder for storing FADEC code pack
TMATSFADECPack = 'TMATSFADEC';
%Sets Bacup folder
BackupFolder = 'Backups';
%Folder for saving MATLAB compile code files
CompCalFold = 'CompileCall';
%Filder for saving MATLAB compile code without host folder - for use in
%TMATS, for example
NoHostCompCalFold = 'CompileCallNoHost';
%Folder where last used C/C++ code is saved
MainBase = ['HardwareMain' filesep 'BaseCode'];
%Folder where last used main C++ HIL code is saved
MainHILBase = ['HardwareMain' filesep 'BaseCode' filesep 'HIL'];
%Folder where last used main C++ FADEC code is saved
MainFADECBase = ['HardwareMain' filesep 'BaseCode' filesep 'FADEC'];
%Folder where gernerated C++ code is stored
MainGen = ['HardwareMain' filesep 'Generated'];
%Folder where generated main C++ HIL code is saved
MainHILGen = ['HardwareMain' filesep 'Generated' filesep 'HIL'];
%Folder where generated main C++ FADEC code is saved
MainFADECGen = ['HardwareMain' filesep 'Generated' filesep 'FADEC'];