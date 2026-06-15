
TICK = 200;
dT = 15;

% load 'airdata.mat';
% load 'tj_data_TJNetThrust.mat'
% load 'alt.mat'

load 'tjData_FlightPlan_2.mat'

AltVecDyn = alte.v;
AltVecDyn = AltVecDyn';

MNVecDyn = mache.v;
MNVecDyn = MNVecDyn';

RefVecDyn = netThrustCmd.v;
RefVecDyn = RefVecDyn';

TimeVector = t.v;
TimeVector = TimeVector';

IMax = TimeVector(end)/TICK * 1000;
IMax = int32(IMax);
ISum = length(TimeVector)/IMax;
ISum = int32(ISum);
%IMax = int32(length(TimeVector));
% 
% TimeVector(ISum)

% TimeVector(ISum)

for i = 1:IMax
        Index = min(length(TimeVector),i * ISum + 1);
        %TimeVector(Index)
        TimeAux(i) = TimeVector(Index);
        ThrustAux(i) = RefVecDyn(Index);
        AltAux(i) = AltVecDyn(Index);
        MNAux(i) = MNVecDyn(Index);
end

TimeVector = TimeAux(1:(length(TimeAux)-1));
AltVecDyn = AltAux(1:(length(TimeAux)-1));
MNVecDyn = MNAux(1:(length(TimeAux)-1));
RefVecDyn = ThrustAux(1:(length(TimeAux)-1));

TimeVector = [0 TimeVector];
AltVecDyn = [AltVecDyn(1) AltVecDyn];
MNVecDyn = [MNVecDyn(1) MNVecDyn];
RefVecDyn = [RefVecDyn(1) RefVecDyn];
dTVecDyn = dT * ones(1,length(TimeVector));

MinThrust = 0;%1000;
%Sets REGIME commands to values no lower than MinThrust N
IndSIATT = find((RefVecDyn > 0));
for i = 1:length(RefVecDyn)
    if i > IndSIATT(1)
        if RefVecDyn(i) < MinThrust
            RefVecDyn(i) = MinThrust;
        end
    end
end




