function [AshMtx,BshMtx,Pt3CshMtx,Pt3DshMtx,Tt4CshMtx,Tt4DshMtx,...
          NcFANshMtx,WfshMtx,Tt4shMtx,Pt3shMtx,RPMshMtx] = SubIdleMtxLoad


%Loads windmill matrices
Mtcs = load('SubIdleMtx.mat');

%Loads windmill matrices
AshMtx = Mtcs.SubIdleMtx.AshMtx;
BshMtx = Mtcs.SubIdleMtx.BshMtx;
Pt3CshMtx = Mtcs.SubIdleMtx.Pt3CshMtx;
Pt3DshMtx = Mtcs.SubIdleMtx.Pt3DshMtx;
Tt4CshMtx = Mtcs.SubIdleMtx.Tt4CshMtx;
Tt4DshMtx = Mtcs.SubIdleMtx.Tt4DshMtx;
NcFANshMtx = Mtcs.SubIdleMtx.NcFANshMtx;
WfshMtx = Mtcs.SubIdleMtx.WfshMtx;
Tt4shMtx = Mtcs.SubIdleMtx.Tt4shMtx;
Pt3shMtx = Mtcs.SubIdleMtx.Pt3shMtx;
RPMshMtx = 0;

end