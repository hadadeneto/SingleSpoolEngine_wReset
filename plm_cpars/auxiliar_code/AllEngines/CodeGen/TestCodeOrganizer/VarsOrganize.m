
%Finds defined variables in .h files
DefVars = FindDefVars(EngineName);
%Finds which defined variables are used by ContConst function
FileName = ['get' EngineName 'ContConst.c'];
[CCMatchDefVars,CCPointVars] = FindMatchingVars(EngineName,FileName,DefVars);
%Finds which defined variables are used by ContConst function
FileName = 'getStartPars.c';
[SPMatchDefVars,SPPointVars] = FindMatchingVars(EngineName,FileName,DefVars);
%Finds which defined variables are used by ContConst function
FileName = 'getEngConst.c';
[ECMatchDefVars,ECPointVars] = FindMatchingVars(EngineName,FileName,DefVars);