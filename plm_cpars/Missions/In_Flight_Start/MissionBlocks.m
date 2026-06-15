
%Simulates the simulink model gnerating simulation inputs
Simout = sim('TJ1000_In_Flight_Start','ReturnWorkspaceOutputs','on');


time = Simout.simout.Altitude.Time;
ThrustRef = Simout.simout.ThrustRef.Data;
Alt = Simout.simout.Altitude.Data;
MN = Simout.simout.MN.Data;
EngineCommand = Simout.simout.EngCommand.Data;

MissionName = 'TJ1000_In_Flight_Start';

MissionGenCols(Alt,MN,ThrustRef,EngineCommand,time,MissionName);