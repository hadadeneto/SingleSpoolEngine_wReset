function [AshMtx,BshMtx,Pt3CshMtx,Pt3DshMtx,Tt4CshMtx,Tt4DshMtx,...
          NcFANshMtx,WfshMtx,Tt4shMtx,Pt3shMtx,RPMshMtx,...
          Pt21shMtx,Pt21CshMtx,Pt21DshMtx,...
          Pt5shMtx,Pt5CshMtx,Pt5DshMtx,...
          Pt6shMtx,Pt6CshMtx,Pt6DshMtx,...
          Tt21shMtx,Tt21CshMtx,Tt21DshMtx,...
          Tt3shMtx,Tt3CshMtx,Tt3DshMtx,...
          Tt5shMtx,Tt5CshMtx,Tt5DshMtx,...
          Tt6shMtx,Tt6CshMtx,Tt6DshMtx] = SubIdleMtxLoad(EngFoldName,UpperFolder)

word = ['cd ' EngFoldName];
eval(word);
%Loads windmill matrices
Mtcs = load('SubIdleMtx.mat');
word = ['cd ' UpperFolder];
eval(word);

%Loads windmill matrices
AshMtx = Mtcs.SubIdleMtx.AshMtx;
BshMtx = Mtcs.SubIdleMtx.BshMtx;

Pt21shMtx = Mtcs.SubIdleMtx.Pt21shMtx;
Pt21CshMtx = Mtcs.SubIdleMtx.Pt21CshMtx;
Pt21DshMtx = Mtcs.SubIdleMtx.Pt21DshMtx;
Pt3shMtx = Mtcs.SubIdleMtx.Pt3shMtx;
Pt3CshMtx = Mtcs.SubIdleMtx.Pt3CshMtx;
Pt3DshMtx = Mtcs.SubIdleMtx.Pt3DshMtx;
Pt5shMtx = Mtcs.SubIdleMtx.Pt5shMtx;
Pt5CshMtx = Mtcs.SubIdleMtx.Pt5CshMtx;
Pt5DshMtx = Mtcs.SubIdleMtx.Pt5DshMtx;
Pt6shMtx = Mtcs.SubIdleMtx.Pt6shMtx;
Pt6CshMtx = Mtcs.SubIdleMtx.Pt6CshMtx;
Pt6DshMtx = Mtcs.SubIdleMtx.Pt6DshMtx;

Tt21shMtx = Mtcs.SubIdleMtx.Tt21shMtx;
Tt21CshMtx = Mtcs.SubIdleMtx.Tt21shMtx;
Tt21DshMtx = Mtcs.SubIdleMtx.Tt21shMtx;
Tt3shMtx = Mtcs.SubIdleMtx.Tt3shMtx;
Tt3CshMtx = Mtcs.SubIdleMtx.Tt3shMtx;
Tt3DshMtx = Mtcs.SubIdleMtx.Tt3shMtx;
Tt4shMtx = Mtcs.SubIdleMtx.Tt4shMtx;
Tt4CshMtx = Mtcs.SubIdleMtx.Tt4CshMtx;
Tt4DshMtx = Mtcs.SubIdleMtx.Tt4DshMtx;
Tt5shMtx = Mtcs.SubIdleMtx.Tt5shMtx;
Tt5CshMtx = Mtcs.SubIdleMtx.Tt5shMtx;
Tt5DshMtx = Mtcs.SubIdleMtx.Tt5shMtx;
Tt6shMtx = Mtcs.SubIdleMtx.Tt6shMtx;
Tt6CshMtx = Mtcs.SubIdleMtx.Tt6shMtx;
Tt6DshMtx = Mtcs.SubIdleMtx.Tt6shMtx;

NcFANshMtx = Mtcs.SubIdleMtx.NcFANshMtx;
WfshMtx = Mtcs.SubIdleMtx.WfshMtx;

RPMshMtx = 0;

end