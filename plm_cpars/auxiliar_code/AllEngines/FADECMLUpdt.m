
%Adds paths
word = [pwd filesep, 'NewCodeGen'];
addpath(word);
word = [pwd filesep 'FADECUpdt'];
addpath(word);

%Sets lists
SetHostFolder
SetEngineList


% %Updates FADEC basic core code file
% FADECCoreUpdt
% %Updates FADEC base files
% dimX1Updt = FADECBaseUpdt('FADEC_XXX_Jet','.c','FADEC_CoreCode.h','//<FADECCore>',HostFolder,FADECMLBase);
% dimX2Updt = FADECBaseUpdt('FADEC_XXX_Shaft','.c','FADEC_CoreCode.h','//<FADECCore>',HostFolder,FADECMLBase);
%Updates the MATLAB FADEC main files
FADECMainUpdt


%Removes paths
word = [pwd filesep, 'NewCodeGen'];
rmpath(word);
word = [pwd filesep 'FADECUpdt'];
rmpath(word);