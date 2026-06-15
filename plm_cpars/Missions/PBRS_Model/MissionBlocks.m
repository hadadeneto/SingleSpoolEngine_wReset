
%Input levels of fuel flow
Wf = [0.01335 0.01669 0.02 0.025 0.03 0.0334 0.04172 0.05 0.05841 0.06676];
%Number of samples per switch
Samp_Switch = 2;
%Number of switches
Num_Switch = 50;
%Percent of oscilation
Percent = 0.1;
%Sammples at start of level
Samp_start = 100;
%Samples at end of level
Samp_end = 2;
%Sampling time
Ts = 0.2;

%NOTE: The total time for prbs operatin in a level is given by:
%Time = Samp_Switch * Ts * Num_Switch, where Ts = 0.2

%Calculates mission time
TSim = (Samp_start + Samp_end + Samp_Switch * Num_Switch) * 0.2 * length(Wf) + 5;

%Simulation of model
Simout = sim('PRBS_Gen','ReturnWorkspaceOutputs','on');

%Definition of parameters for mission generation
time = Simout.simout.time;
ThrustRef = Simout.simout.data;
Alt = 567 * ones(1,length(time));
MN = 0 * ones(1,length(time));
EngineCommand = 170 * ones(1,length(time));
EngineCommand(end) = 0;

%Definition of mission name
MissionName = 'PRBS_TJ1000';

MissionGenCols(Alt,MN,ThrustRef,EngineCommand,time,MissionName);