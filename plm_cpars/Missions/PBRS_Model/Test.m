
%Input levels of fuel flow
% Wf = [0.01335 0.01669 0.02 0.025 0.03 0.0334 0.04172 0.05 0.05841 0.06676];
% WfMtx = [3.35319e-03, 4.47091e-03, 7.87431e-03, 1.14579e-02, 1.66929e-02, 2.16627e-02, 2.55503e-02, 2.86499e-02, 3.21360e-02, 3.58686e-02, 4.06799e-02, 4.63335e-02];
% Wf = WfMtx(1);
%Number of samples per switch
Samp_Switch = 1000;
%Number of switches
Num_Switch = 1;
%Percent of oscilation
Percent = 0.1;
%Sammples at start of level
Samp_start = 100;
%Samples at end of level
Samp_end = 2;
%Sampling time
Ts = 0.2;

%MATRICES

WfMtx = [3.35319e-03, 4.47091e-03, 7.87431e-03, 1.14579e-02, 1.66929e-02, 2.16627e-02, 2.55503e-02, 2.86499e-02, 3.21360e-02, 3.58686e-02, 4.06799e-02, 4.63335e-02];
NMtx = 23042*[2.16995e-02, 4.33990e-02, 1.08498e-01, 1.73596e-01, 2.38695e-01, 3.03793e-01, 3.68892e-01, 4.33990e-01, 4.99089e-01, 5.64187e-01, 6.29286e-01, 6.94384e-01];

AMtx = [-8.08083e-02, -1.00674e-01, -1.60269e-01, -2.19865e-01, -2.79461e-01, -3.39057e-01, -3.98653e-01, -4.58249e-01, -5.17844e-01, -5.77440e-01, -6.37036e-01, -6.96632e-01];
BMtx = [1.54238e+05, 1.56531e+05, 1.63413e+05, 1.70294e+05, 1.77175e+05, 1.84056e+05, 1.90937e+05, 1.97818e+05, 2.04700e+05, 2.11581e+05, 2.18462e+05, 2.25343e+05];
NCMtx = ones(1,length(AMtx));
NDMtx = 0 * ones(1,length(AMtx));
% Tt4CMtx = [4.31403e+04, 4.22294e+04, 3.94965e+04, 3.67636e+04, 3.40308e+04, 3.12979e+04, 2.85651e+04, 2.58322e+04, 2.30993e+04, 2.03665e+04, 1.76336e+04, 1.49008e+04];
% Tt4DMtx = [4.31403e+04, 4.22294e+04, 3.94965e+04, 3.67636e+04, 3.40308e+04, 3.12979e+04, 2.85651e+04, 2.58322e+04, 2.30993e+04, 2.03665e+04, 1.76336e+04, 1.49008e+04];
Wf = WfMtx(2);
RPM = NMtx(2);


% % WfMtx = 0;
% % NMtx = 0;
% % AMtx = -4;
% % BMtx = 4;
% % NCMtx = 1;
% % NDMtx = 0;
% 
% WfMtx = 0;
% NMtx = 0;
% AMtx = AMtx(2);
% BMtx = BMtx(2);
% NCMtx = 1;
% NDMtx = 0;

% 
% 
% Wf = 1;

% %NOTE: The total time for prbs operatin in a level is given by:
% %Time = Samp_Switch * Ts * Num_Switch, where Ts = 0.2
% 
% %Calculates mission time
% TSim = (Samp_start + Samp_end + Samp_Switch * Num_Switch) * 0.2 * length(Wf) + 5;
% 
% %Simulation of model
% Simout = sim('PRBS_Gen','ReturnWorkspaceOutputs','on');
% 
% %Definition of parameters for mission generation
% time = Simout.simout.time;
% ThrustRef = Simout.simout.data;
% Alt = 567 * ones(1,length(time));
% MN = 0 * ones(1,length(time));
% EngineCommand = 170 * ones(1,length(time));
% EngineCommand(end) = 0;
% 
% %Definition of mission name
% MissionName = 'PRBS_TJ1000';
% 
% MissionGenCols(Alt,MN,ThrustRef,EngineCommand,time,MissionName);