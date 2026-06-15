
Simout = sim('Mission_1','ReturnWorkspaceOutputs','on');


time = Simout.Alt.time;
Alt = Simout.Alt.data;
MN = Simout.MN.data;
EngineCommand = 0 * ones(1,length(time));
EngineCommand(end) = 0;
ThrustRef = 0 * ones(1,length(Alt));

MissionName = 'FlightStartSim';

MissionGenCols(Alt,MN,ThrustRef,EngineCommand,time,MissionName);