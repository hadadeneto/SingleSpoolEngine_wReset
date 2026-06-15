function [RPMf,A,B] = WindMillPars(M)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here


Maux = M;
LowM = 0;
HighM = 0;

%Must indicate if M < 0.3
if(M < 0.3)
    M = 0.3;
    LowM = 1;
end

%Must indicate if M > 0.7
if(M > 0.7)
    M = 0.7;
    HighM = 1;
end

%Calculation of final RPM Value
RPMf = 20000 * (M - 0.3) + 2500;

%Calculation of settling time;
Tset = -20 * (M - 0.3) + 12;

%Recalculates RPMf
if(LowM == 1)
    RPMf = 2500 * Maux/0.3;
    Tset = 12 * 0.3 / (Maux + 1e-5);
end

%Recalculates RPMf
if(HighM == 1)
    RPMf = 2500 * Maux/0.7;
    Tset = 12 * 0.7 / (Maux + 1e-5);
end

%Calculation of A coefficient
A = -4/Tset;

%Calculation of B coefficient;
B = -A * RPMf / M;

end

