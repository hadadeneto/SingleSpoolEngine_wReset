
% function [MNLinVec,A,B,C,D,...
% Pt3C, Pt3D, Tt3C, Tt3D,...
% Tt4C, Tt4D,...
% Pt5C, Pt5D, Tt5C, Tt5D,...
% N_Kp, N_Ki, Pt3_Kp, Pt3_Ki,...
% Tt4_Kp, Tt4_Ki, Tt5_Kp, Tt5_Ki,...
% NcFAN,...
% Pt3, Tt3,...
% Wf, Tt4,...
% Pt5, Tt5,...
% FN, FNper] = SetLinPars(AltLinPoints, MNLinVec,...
% A,B,C,D,...
% N_Kp, N_Ki, Pt3_Kp, Pt3_Ki,...
% Tt4_Kp, Tt4_Ki, Tt5_Kp, Tt5_Ki,...
% NcFAN,...
% Pt3,Tt3,...
% Wf, Tt4,...
% Pt5, Tt5,...
% FN, FNper)

function [MNLinVec,A,B,C,D,...
    Pt21C, Pt21D, Tt21C, Tt21D,...
    Pt3C, Pt3D, Tt3C, Tt3D,...
    Tt4C, Tt4D,...
    Pt5C, Pt5D, Tt5C, Tt5D,...
    Pt6C, Pt6D, Tt6C, Tt6D,...
    N_Kp, N_Ki, Pt3_Kp, Pt3_Ki,...
    Tt4_Kp, Tt4_Ki, Tt5_Kp, Tt5_Ki,...
    NcFAN,...
    Pt21, Tt21,...
    Pt3, Tt3,...
    Wf, Tt4,...
    Pt5, Tt5, Pt6, Tt6,...
    FN, FNper] = SetLinParsLR(AltLinPoints, MNLinVec,...
    A,B,C,D,...
    N_Kp, N_Ki, Pt3_Kp, Pt3_Ki,...
    Tt4_Kp, Tt4_Ki, Tt5_Kp, Tt5_Ki,...
    NcFAN,...
    Pt21, Tt21,...
    Pt3,Tt3,...
    Wf, Tt4,...
    Pt5, Tt5, Pt6, Tt6,...
    FN, FNper,...
    SSFan)

%global NY_Lin

%Sets the number of observed variables for a single spool pure jet
DimY = 6;

%The number of observed variables of a single spool fan is 10
if(SSFan)
    DimY = 10;
end

% [A(:,:,i),B(:,:,i),C(:,:,i),D(:,:,i),...
% Pt21C(:,:,i), Pt21D(:,:,i), Tt21C(:,:,i), Tt21D(:,:,i),...
% Pt3C(:,:,i), Pt3D(:,:,i), Tt3C(:,:,i), Tt3D(:,:,i),...
% Tt4C(:,:,i), Tt4D(:,:,i),...
% Pt5C(:,:,i), Pt5D(:,:,i), Tt5C(:,:,i), Tt5D(:,:,i),...
% Pt6C(:,:,i), Pt6D(:,:,i), Tt6C(:,:,i), Tt6D(:,:,i),...
% N_Kp(:,:,i), N_Ki(:,:,i), Pt3_Kp(:,:,i), Pt3_Ki(:,:,i),...
% Tt4_Kp(:,:,i), Tt4_Ki(:,:,i), Tt5_Kp(:,:,i), Tt5_Ki(:,:,i),...
% NcFAN(:,:,i),...
% Pt21(:,:,i), Tt21(:,:,i), Wf(:,:,i), Tt4(:,:,i),...
% Pt5(:,:,i), Tt5(:,:,i), Pt6(:,:,i), Tt6(:,:,i),...
% FN(:,:,i), FNper(:,:,i)] = Alt0dT0;

%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

for i = 1:length(AltLinPoints)
    %Save Altitude Values in vectors
    if AltLinPoints(i) < 00010
        
        [MNLinVec,A(:,:,i),B(:,:,i),C(:,:,i),D(:,:,i),...
            N_Kp(:,:,i), N_Ki(:,:,i), Pt3_Kp(:,:,i), Pt3_Ki(:,:,i),...
            Tt4_Kp(:,:,i), Tt4_Ki(:,:,i), Tt5_Kp(:,:,i), Tt5_Ki(:,:,i),...
            NcFAN(:,:,i),...
            Pt21(:,:,i), Tt21(:,:,i),...
            Pt3(:,:,i), Tt3(:,:,i),...
            Tt4(:,:,i), Wf(:,:,i),...
            Pt5(:,:,i), Tt5(:,:,i),...
            Pt6(:,:,i), Tt6(:,:,i),...
            FN(:,:,i), FNper(:,:,i)] = Alt0dTLR;
        
        %         [MNLinVec,A(:,:,i),B(:,:,i),C(:,:,i),D(:,:,i),...
        %             N_Kp(:,:,i), N_Ki(:,:,i), Pt3_Kp(:,:,i), Pt3_Ki(:,:,i),...
        %             Tt4_Kp(:,:,i), Tt4_Ki(:,:,i), Tt5_Kp(:,:,i), Tt5_Ki(:,:,i),...
        %             NcFAN(:,:,i),...
        %             Pt3(:,:,i), Tt3(:,:,i),...
        %             Tt4(:,:,i), Wf(:,:,i),...
        %             Pt5(:,:,i), Tt5(:,:,i),...
        %             FN(:,:,i), FNper(:,:,i)] = Alt0dT0;
        
    end
    
    
end

%Reads the size of A
[numMN,numFN,numAlt] = size(A);

%Initiats each matrix for individual variables
NC = zeros(numMN,numFN,numAlt);
ND = zeros(numMN,numFN,numAlt);

Pt21C = zeros(numMN,numFN,numAlt);
Pt21D = zeros(numMN,numFN,numAlt);
Tt21C = zeros(numMN,numFN,numAlt);
Tt21D = zeros(numMN,numFN,numAlt);

Pt3C = zeros(numMN,numFN,numAlt);
Pt3D = zeros(numMN,numFN,numAlt);
Tt3C = zeros(numMN,numFN,numAlt);
Tt3D = zeros(numMN,numFN,numAlt);

Tt4C = zeros(numMN,numFN,numAlt);
Tt4D = zeros(numMN,numFN,numAlt);

Pt5C = zeros(numMN,numFN,numAlt);
Pt5D = zeros(numMN,numFN,numAlt);
Tt5C = zeros(numMN,numFN,numAlt);
Tt5D = zeros(numMN,numFN,numAlt);

Pt6C = zeros(numMN,numFN,numAlt);
Pt6D = zeros(numMN,numFN,numAlt);
Tt6C = zeros(numMN,numFN,numAlt);
Tt6D = zeros(numMN,numFN,numAlt);

%Checks which configuration is being used and defines variables accordingly
if(SSFan)
    
    %Variable 1 -> N
    NumVar = 1;
    NC(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
    ND(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
    %Variable 2 -> Pt21
    NumVar = 2;
    Pt21C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
    Pt21D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
    %Variable 3 -> Tt21
    NumVar = 3;
    Tt21C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
    Tt21D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
    %Variable 4 -> Pt3
    NumVar = 4;
    Pt3C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
    Pt3D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
    %Variable 5 -> Tt3
    NumVar = 5;
    Tt3C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
    Tt3D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
    %Variable 6 -> Tt4
    NumVar = 6;
    Tt4C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
    Tt4D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
    %Variable 7 -> Pt5
    NumVar = 7;
    Pt5C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
    Pt5D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
    %Variable 8 -> Tt5
    NumVar = 8;
    Tt5C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
    Tt5D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
    %Variable 9 -> Pt6
    NumVar = 9;
    Pt6C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
    Pt6D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
    %Variable 10 -> Tt6
    NumVar = 10;
    Tt6C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
    Tt6D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
    
else
    
    %Stores the matrices values
    for i = 1:numMN
        %Variable 1 -> N
        NumVar = 1;
        NC(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        ND(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        %Variable 2 -> Pt3
        NumVar = 2;
        Pt3C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        Pt3D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        %Variable 3 -> Tt3
        NumVar = 3;
        Tt3C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        Tt3D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        %Variable 4 -> Tt4
        NumVar = 4;
        Tt4C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        Tt4D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        %Variable 5 -> Pt5
        NumVar = 5;
        Pt5C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        Pt5D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        %Variable 6 -> Tt5
        NumVar = 6;
        Tt5C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        Tt5D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        
        %     %Variable 1 -> N
        %     NumVar = 1;
        %     NC(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        %     ND(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        %     %Variable 2 -> Pt21
        %     NumVar = 2;
        %     Pt21C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        %     Pt21D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        %     %Variable 3 -> Tt21
        %     NumVar = 3;
        %     Tt21C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        %     Tt21D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        %     %Variable 4 -> Pt3
        %     NumVar = 4;
        %     Pt3C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        %     Pt3D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        %     %Variable 5 -> Tt3
        %     NumVar = 5;
        %     Tt3C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        %     Tt3D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        %     %Variable 6 -> Tt4
        %     NumVar = 6;
        %     Tt4C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        %     Tt4D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        %     %Variable 7 -> Pt5
        %     NumVar = 7;
        %     Pt5C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        %     Pt5D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        %     %Variable 8 -> Tt5
        %     NumVar = 8;
        %     Tt5C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        %     Tt5D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        %     %Variable 9 -> Pt6
        %     NumVar = 9;
        %     Pt6C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        %     Pt6D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        %     %Variable 10 -> Tt6
        %     NumVar = 10;
        %     Tt6C(i,:,:) = C(DimY*i-(DimY-NumVar),:,:);
        %     Tt6D(i,:,:) = D(DimY*i-(DimY-NumVar),:,:);
        
        
        
    end
    
    %For the unified model
    Pt21C = Pt3C;
    Pt21D = Pt3D;
    Tt21C = Tt3C;
    Tt21D = Tt3D;
    
    Pt6C = Pt5C;
    Pt6D = Pt5D;
    Tt6C = Tt5C;
    Tt6D = Tt5D;
    
end







% %For the unified model
% Pt21C = Pt3C;
% Pt21D = Pt3D;
% Tt21C = Tt3C;
% Tt21D = Tt3D;
%
% Pt6C = Pt5C;
% Pt6D = Pt5D;
% Tt6C = Tt5C;
% Tt6D = Tt5D;

disp(' ')
disp('LOW RPM GAINS AND MTX SUCCESSFULLY LOADED')

end

