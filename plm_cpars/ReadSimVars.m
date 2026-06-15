
%------------------------
%READS SIMULINK VARIABLES
%------------------------

%Time vector
t = SimOut.get('tout');

%External
Altitude = SimOut.get('Altitude');
MN = SimOut.get('MN');
dT = SimOut.get('dT');
Ref = SimOut.get('Ref');

%Station 2
W2_HIL = SimOut.get('W2_HIL');
Pt2_HIL = SimOut.get('Pt2_HIL');
Tt2_HIL = SimOut.get('Tt2_HIL');
NcFAN_HIL = SimOut.get('NcFAN_HIL');
WcFAN_HIL = SimOut.get('WcFAN_HIL');
PRFAN_HIL = SimOut.get('PRFAN_HIL');
SMFAN_HIL = SimOut.get('SMFAN_HIL');
BPFAN_HIL = SimOut.get('_HIL');

%Station 21
W21_HIL = SimOut.get('W21_HIL');
Pt21_HIL = SimOut.get('Pt21_HIL');
Tt21_HIL = SimOut.get('Tt21_HIL');
NcHPC_HIL = SimOut.get('NcHPC_HIL');
WcHPC_HIL = SimOut.get('WcHPC_HIL');
PRHPC_HIL = SimOut.get('PRHPC_HIL');
SMHPC_HIL = SimOut.get('SMHPC_HIL');

%Station 3
Pt3_HIL = SimOut.get('Pt3_HIL');
Tt3_HIL = SimOut.get('Tt3_HIL');

%Station 4
Tt4_HIL = SimOut.get('Tt4_HIL');
Wf_HIL = SimOut.get('Wf_HIL');
RU_HIL = SimOut.get('RU_HIL');

%Station 5
Pt5_HIL = SimOut.get('Pt5_HIL');
Tt5_HIL = SimOut.get('Tt5_HIL');

%Station 6
Pt6_HIL = SimOut.get('Pt6_HIL');
Tt6_HIL = SimOut.get('Tt6_HIL');

%Station 8
W8_HIL = SimOut.get('W8_HIL');
V8_HIL = SimOut.get('V8_HIL');
Fn_HIL = SimOut.get('Fn_HIL');
Fg_HIL = SimOut.get('Fg_HIL');

%Shaft
N_HIL = SimOut.get('N_HIL');

%References
RPMRef_HIL = SimOut.get('RPMRef_HIL');
FiltRef_HIL = SimOut.get('FiltRef_HIL');

%Active Controller
Active_HIL = SimOut.get('Active_HIL');

%QSMC Disturbances and Control Signals
QSMCdx_HIL = SimOut.get('QSMCdx_HIL');
QSMCdy_HIL = SimOut.get('QSMCdy_HIL');
QSMCux_HIL = SimOut.get('QSMCux_HIL');
QSMCuy_HIL = SimOut.get('QSMCuy_HIL');

