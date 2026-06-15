

%CALCULATES THE VALUES OF Fn AND Wf TO BE STORED IN Engine.mat

[~,PowerNum] = size(FNcMtx);
[AltNum,MNum] = size(DeltaMtx);
FNMtxPars = zeros(MNum,PowerNum,AltNum);
WfMtxPars = zeros(MNum,PowerNum,AltNum);

%Performs calculations for each value of altitude
for i = 1:length(AltLinVectorPT)
    %Performs calculation for each value of Mach number
    for j = 1:length(MNVectorPT)
        
        %Sea level parameters
        Delta = DeltaMtx(i,j);
        Theta = ThetaMtx(i,j);
        sqrTheta = sqrThetaMtx(i,j);
        
        FNMtxPars(j,:,i) = FNcMtx(j,:,1) * DeltaMtx(i,j);
        WfMtxPars(j,:,i) = WfcMtx(j,:,1) * DeltaMtx(i,j) * sqrThetaMtx(i,j);
        
    end
end