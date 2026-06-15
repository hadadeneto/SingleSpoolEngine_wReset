function [AwmMtx,BwmMtx,CwmMtx,DwmMtx,RPMwmMtx,WfwmMtx,...
          Pt21wmMtx,Pt21CwmMtx,Pt21DwmMtx,...
          Pt3wmMtx,Pt3CwmMtx,Pt3DwmMtx,...
          Pt5wmMtx,Pt5CwmMtx,Pt5DwmMtx,...
          Pt6wmMtx,Pt6CwmMtx,Pt6DwmMtx,...
          Tt21wmMtx,Tt21CwmMtx,Tt21DwmMtx,...
          Tt3wmMtx,Tt3CwmMtx,Tt3DwmMtx,...
          Tt4wmMtx,Tt4CwmMtx,Tt4DwmMtx,...
          Tt5wmMtx,Tt5CwmMtx,Tt5DwmMtx,...
          Tt6wmMtx,Tt6CwmMtx,Tt6DwmMtx] = WindMillMtxLoad(EngFoldName,UpperFolder)

word = ['cd ' EngFoldName];
eval(word);
%Loads windmill matrices
Mtcs = load('WindMillMtx.mat');
word = ['cd ' UpperFolder];
eval(word);

%Loads windmill matrices
AwmMtx = Mtcs.WindMillMtx.AwmMtx;
BwmMtx = Mtcs.WindMillMtx.BwmMtx;
CwmMtx = Mtcs.WindMillMtx.CwmMtx;
DwmMtx = Mtcs.WindMillMtx.DwmMtx;
RPMwmMtx = Mtcs.WindMillMtx.RPMwmMtx;
WfwmMtx = Mtcs.WindMillMtx.WfwmMtx;

Pt21wmMtx = Mtcs.WindMillMtx.Pt21wmMtx;
Pt21CwmMtx = Mtcs.WindMillMtx.Pt21CwmMtx;
Pt21DwmMtx = Mtcs.WindMillMtx.Pt21DwmMtx;
Pt3wmMtx = Mtcs.WindMillMtx.Pt3wmMtx;
Pt3CwmMtx = Mtcs.WindMillMtx.Pt3CwmMtx;
Pt3DwmMtx = Mtcs.WindMillMtx.Pt3DwmMtx;
Pt5wmMtx = Mtcs.WindMillMtx.Pt5wmMtx;
Pt5CwmMtx = Mtcs.WindMillMtx.Pt5CwmMtx;
Pt5DwmMtx = Mtcs.WindMillMtx.Pt5DwmMtx;
Pt6wmMtx = Mtcs.WindMillMtx.Pt6wmMtx;
Pt6CwmMtx = Mtcs.WindMillMtx.Pt6CwmMtx;
Pt6DwmMtx = Mtcs.WindMillMtx.Pt6DwmMtx;

Tt21wmMtx = Mtcs.WindMillMtx.Tt21wmMtx;
Tt21CwmMtx = Mtcs.WindMillMtx.Tt21wmMtx;
Tt21DwmMtx = Mtcs.WindMillMtx.Tt21wmMtx;
Tt3wmMtx = Mtcs.WindMillMtx.Tt3wmMtx;
Tt3CwmMtx = Mtcs.WindMillMtx.Tt3wmMtx;
Tt3DwmMtx = Mtcs.WindMillMtx.Tt3wmMtx;
Tt4wmMtx = Mtcs.WindMillMtx.Tt4wmMtx;
Tt4CwmMtx = Mtcs.WindMillMtx.Tt4CwmMtx;
Tt4DwmMtx = Mtcs.WindMillMtx.Tt4DwmMtx;
Tt5wmMtx = Mtcs.WindMillMtx.Tt5wmMtx;
Tt5CwmMtx = Mtcs.WindMillMtx.Tt5wmMtx;
Tt5DwmMtx = Mtcs.WindMillMtx.Tt5wmMtx;
Tt6wmMtx = Mtcs.WindMillMtx.Tt6wmMtx;
Tt6CwmMtx = Mtcs.WindMillMtx.Tt6wmMtx;
Tt6DwmMtx = Mtcs.WindMillMtx.Tt6wmMtx;
