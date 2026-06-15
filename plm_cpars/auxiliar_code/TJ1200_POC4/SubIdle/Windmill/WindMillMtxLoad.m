function [AwmMtx,BwmMtx,CwmMtx,DwmMtx,RPMwmMtx] = WindMillMtxLoad

%Loads windmill matrices
Mtcs = load('WindMillMtx.mat');

%Loads windmill matrices
AwmMtx = Mtcs.WindMillMtx.AwmMtx;
BwmMtx = Mtcs.WindMillMtx.BwmMtx;
CwmMtx = Mtcs.WindMillMtx.CwmMtx;
DwmMtx = Mtcs.WindMillMtx.DwmMtx;
RPMwmMtx = Mtcs.WindMillMtx.RPMwmMtx;
