function [AltVecDyn,MNVecDyn,RefVecDyn,dTVecDyn,TimeVector] = Read_xlsx_Mission(filename,dT)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

%Reads the mission in xlsx format
AllVecDyn = xlsread(filename);

%Updates all input vectors
AltVecDyn = AllVecDyn(:,1)';
MNVecDyn = AllVecDyn(:,2)';
RefVecDyn = AllVecDyn(:,3)';
TimeVector = AllVecDyn(:,5)';
dTVecDyn = dT * ones(1,length(TimeVector));

end

