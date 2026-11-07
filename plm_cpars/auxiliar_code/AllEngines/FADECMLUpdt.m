
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
Output = FADECBaseUpdt('FADEC_XXX_Jet','.c','FADEC_CoreCode.h','//<FADECCore>',HostFolder,FADECMLBase);

%Removes paths
word = [pwd filesep, 'NewCodeGen'];
rmpath(word);
word = [pwd filesep 'FADECUpdt'];
rmpath(word);