
%Adds paths
word = [pwd filesep, 'NewCodeGen'];
addpath(word);
word = [pwd filesep 'FADECUpdt'];
addpath(word);

%Sets lists
SetHostFolder
SetEngineList

%Updates FADEC basic core code file
FADECCoreUpdt
%Updates FADEC base files
Jet_dimX1_Updt = FADECBaseUpdt('FADEC_XXX_Jet','.c','FADEC_CoreCode.h','//<FADECCore>',HostFolder,FADECMLBase);
Shaft_dimX2_Updt = FADECBaseUpdt('FADEC_XXX_Shaft','.c','FADEC_CoreCode.h','//<FADECCore>',HostFolder,FADECMLBase);
%Updstes FADEC Lite base files
Jet_dimX1_Updt_Lite = FADECBaseUpdt('ControlFADECLite_Base_Jet','.c','FADEC_CoreCode.h','//<FADECCore>',HostFolder,FADECMLBase);
Shaft_dimX1_Updt_Lite = FADECBaseUpdt('ControlFADECLite_Base_Shaft','.c','FADEC_CoreCode.h','//<FADECCore>',HostFolder,FADECMLBase);
%Updates the MATLAB FADEC main files
FADECMainUpdt

%Removes paths
word = [pwd filesep, 'NewCodeGen'];
rmpath(word);
word = [pwd filesep 'FADECUpdt'];
rmpath(word);