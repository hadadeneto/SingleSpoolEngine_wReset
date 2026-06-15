
%-----------
%REAL FLIGHT
%-----------

%VECTORS FOR REAL FLIGHT MISSION SIMULATION

time          = [0      60      60.2      80      80.2      130      130.2      180      180.2      205      205.2      480      480.2      680      680.2      705      705.2      880      880.2];
ThrustRef     = [0      0       2500      2500    2900      2900     1800       1800     1800       1800     1700       1700     1300       1700     0          0        0          0        0];
Alt           = [930    930     930       930     930       1300     1300       1800     1800       2000     2000       2000     2000       2000     2000       2000     2000       930      930];
MN            = [0      0       0         0       0.23      0.52     0.52       0.53     0.53       0.53     0.53       0.53     0.47       0.47     0.47       0.26     0          0        0];
EngineCommand = [170    170     170       170     170       170      170        170      170        170      170        170      170        170      0          0        0          0        0];

%VECTORS PLOTING

subplot(4,1,1),plot(time,Alt,'b','linewidth',2),ylabel('Alt (m)'),grid on
subplot(4,1,2),plot(time,MN,'b','linewidth',2),ylabel('MN'),grid on
subplot(4,1,3),plot(time,ThrustRef,'b','linewidth',2),ylabel('Thrust (N)'),grid on
subplot(4,1,4),plot(time,EngineCommand,'b','linewidth',2),ylabel('Command'),xlabel('Time (s)'),grid on

%MISSION GENERATION

MissionName = 'SebastienMission';
MissionGenCols(Alt,MN,ThrustRef,EngineCommand,time,MissionName);