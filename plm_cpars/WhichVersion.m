function Vyear = WhichVersion
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

%Reads the MATLAB version
Vyear = version;

%Finds which index contains the letter R
LI = find(Vyear == 'R');
%Computes the index containing the last year number
HI = LI + 4;
%Computes the version with the year
Vyear = Vyear(LI+1:HI);
%Transforms ouptut into a number
Vyear = str2double(Vyear);


end

