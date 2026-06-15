

%Loads PI parameters
LoadsPIPars

%Defines dummy matrix
[~,column,~] = size(NcFANMtx);
Dummy = zeros(1,column);
VarsPerLine = 5;

%Defines all matrices that can be printed in code - taken from LinPars and
%added with DummyMtx
AllMatrices = [{'Ts0'},{'DeltaMtx'},{'ThetaMtx'},{'AMtx'},{'BMtx'}, ...
    {'Pt21CMtx'}, {'Pt21DMtx'}, {'Tt21CMtx'}, {'Tt21DMtx'}, ...
    {'Pt3CMtx'}, {'Pt3DMtx'}, {'Tt3CMtx'}, {'Tt3DMtx'}, ...
    {'Tt4CMtx'}, {'Tt4DMtx'}, ...
    {'Pt5CMtx'}, {'Pt5DMtx'}, {'Tt5CMtx'}, {'Tt5DMtx'}, ...
    {'Pt6CMtx'}, {'Pt6DMtx'}, {'Tt6CMtx'}, {'Tt6DMtx'}, ...
    {'N_KpMtx'}, {'N_KiMtx'}, {'Pt3_KpMtx'}, {'Pt3_KiMtx'}, ...
    {'Tt4_KpMtx'}, {'Tt4_KiMtx'}, {'Tt5_KpMtx'}, {'Tt5_KiMtx'}, ...
    {'NcFANMtx'}, ...
    {'Pt21Mtx'}, {'Tt21Mtx'}, ...
    {'Pt3Mtx'}, {'Tt3Mtx'}, ...
    {'WfMtx'}, {'Tt4Mtx'}, ...
    {'Pt5Mtx'}, {'Tt5Mtx'}, {'Pt6Mtx'}, {'Tt6Mtx'}, ...
    {'FNMtx'}, {'FNperMtx'}, ...
    {'NcFANMap'}, {'WcFANMap'}, {'EffFANMap'}, {'PRFANMap'}, ...
    {'NcHPCMap'}, {'WcHPCMap'}, {'EffHPCMap'}, {'PRHPCMap'}, ...
    {'NcHPTMap'}, {'WcHPTMap'}, {'EffHPTMap'}, {'PRHPTMap'}, ...
    {'PRFANStall'}, {'WcFANStall'}, {'PRHPCStall'}, {'WcHPCStall'}, ...
    {'FNperContMtx'}, {'FNcMaxContMtx'}, {'NcFANContMtx'}, ...
    {'MNLinVec'}, {'AltLinVec'}, ...
    {'AwmMtx'}, {'BwmMtx'}, {'CwmMtx'}, {'DwmMtx'}, {'RPMwmMtx'}, {'WfwmMtx'} ...
    {'AshMtx'}, {'BshMtx'}, {'Pt3CshMtx'}, {'Pt3DshMtx'}, {'Tt4CshMtx'}, {'Tt4DshMtx'}, ...
    {'NcFANshMtx'}, {'WfshMtx'}, {'Tt4shMtx'}, {'Pt3shMtx'}, {'RPMshMtx'}, ...
    {'ASVec'}, {'DSVec'}, {'NcVec'}, {'Dummy'}];

word = 'AllMatrices';
VecConc = [{'Pt21wmMtx'},{'Pt21CwmMtx'},{'Pt21DwmMtx'},{'Pt3wmMtx'},{'Pt3CwmMtx'},{'Pt3DwmMtx'},{'Pt5wmMtx'},{'Pt5CwmMtx'},{'Pt5DwmMtx'},{'Pt6wmMtx'},{'Pt6CwmMtx'},{'Pt6DwmMtx'}];
AllMatrices = ConcatNoRepeat(AllMatrices,VecConc,word);
VecConc = [{'Tt21wmMtx'},{'Tt21CwmMtx'},{'Tt21DwmMtx'},{'Tt3wmMtx'},{'Tt3CwmMtx'},{'Tt3DwmMtx'},{'Tt4wmMtx'},{'Tt4CwmMtx'},{'Tt4DwmMtx'},{'Tt5wmMtx'},{'Tt5CwmMtx'},{'Tt5DwmMtx'},{'Tt6wmMtx'},{'Tt6CwmMtx'},{'Tt6DwmMtx'}];
AllMatrices = ConcatNoRepeat(AllMatrices,VecConc,word);
VecConc = [{'N_KpshMtx'},{'N_KishMtx'},{'NcFANshContMtx'}];
AllMatrices = ConcatNoRepeat(AllMatrices,VecConc,word);
% VecConc = [{'Pt21shMtx'},{'Pt21CshMtx'},{'Pt21DshMtx'},{'Pt5shMtx'},{'Pt5CshMtx'},{'Pt5DshMtx'},{'Pt6shMtx'},{'Pt6CshMtx'},{'Pt6DshMtx'}];
% AllMatrices = ConcatNoRepeat(AllMatrices,VecConc,word);
% VecConc = [{'Tt21shMtx'},{'Tt21CshMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3CshMtx'},{'Tt3DshMtx'},{'Tt5shMtx'},{'Tt5CshMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6CshMtx'},{'Tt6DshMtx'}];
% AllMatrices = ConcatNoRepeat(AllMatrices,VecConc,word);
VecConc = [{'Pt21shMtx'},{'Pt21CshMtx'},{'Pt21DshMtx'},{'Pt3shMtx'},{'Pt3CshMtx'},{'Pt3DshMtx'},{'Pt5shMtx'},{'Pt5CshMtx'},{'Pt5DshMtx'},{'Pt6shMtx'},{'Pt6CshMtx'},{'Pt6DshMtx'}];
AllMatrices = ConcatNoRepeat(AllMatrices,VecConc,word);
VecConc = [{'Tt21shMtx'},{'Tt21CshMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3CshMtx'},{'Tt3DshMtx'},{'Tt4shMtx'},{'Tt4CshMtx'},{'Tt4DshMtx'},{'Tt5shMtx'},{'Tt5CshMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6CshMtx'},{'Tt6DshMtx'}];
AllMatrices = ConcatNoRepeat(AllMatrices,VecConc,word);

% AllMatrices = [AllMatrices {'Pt21wmMtx'},{'Pt21CwmMtx'},{'Pt21DwmMtx'},{'Pt3wmMtx'},{'Pt3CwmMtx'},{'Pt3DwmMtx'},{'Pt5wmMtx'},{'Pt5CwmMtx'},{'Pt5DwmMtx'},{'Pt6wmMtx'},{'Pt6CwmMtx'},{'Pt6DwmMtx'}];
% AllMatrices = [AllMatrices {'Tt21wmMtx'},{'Tt21CwmMtx'},{'Tt21DwmMtx'},{'Tt3wmMtx'},{'Tt3CwmMtx'},{'Tt3DwmMtx'},{'Tt4wmMtx'},{'Tt4CwmMtx'},{'Tt4DwmMtx'},{'Tt5wmMtx'},{'Tt5CwmMtx'},{'Tt5DwmMtx'},{'Tt6wmMtx'},{'Tt6CwmMtx'},{'Tt6DwmMtx'}];
% 
% AllMatrices = [AllMatrices {'Pt21shMtx'},{'Pt21CshMtx'},{'Pt21DshMtx'},{'Pt5shMtx'},{'Pt5CshMtx'},{'Pt5DshMtx'},{'Pt6shMtx'},{'Pt6CshMtx'},{'Pt6DshMtx'}];
% AllMatrices = [AllMatrices {'Tt21shMtx'},{'Tt21CshMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3CshMtx'},{'Tt3DshMtx'},{'Tt5shMtx'},{'Tt5CshMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6CshMtx'},{'Tt6DshMtx'}];
% % AllMatrices = [AllMatrices {'Pt21shMtx'},{'Pt21CshMtx'},{'Pt21DshMtx'},{'Pt3shMtx'},{'Pt3CshMtx'},{'Pt3DshMtx'},{'Pt5shMtx'},{'Pt5CshMtx'},{'Pt5DshMtx'},{'Pt6shMtx'},{'Pt6CshMtx'},{'Pt6DshMtx'}];
% % AllMatrices = [AllMatrices {'Tt21shMtx'},{'Tt21CshMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3CshMtx'},{'Tt3DshMtx'},{'Tt4shMtx'},{'Tt4CshMtx'},{'Tt4DshMtx'},{'Tt5shMtx'},{'Tt5CshMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6CshMtx'},{'Tt6DshMtx'}];
% 

%The NcMtx is added for being in accordance with the current code. However,
%in the real code, the NcMtx shall be replaced by NcFANMtx in a near
%future, since this is only called by EngineModel
NcMtx = NcFANMtx;
AllMatrices = [AllMatrices {'NcMtx'}];

%HIL command for matrices loading
GetFuncMatrices = [{'NcFANContMtx'}, {'N_KpMtx'}, {'N_KiMtx'}, {'FNperContMtx'}, {'FNcMaxContMtx'}, {'NcMtx'}, {'Pt21Mtx'}, {'Pt3Mtx'}, {'Pt5Mtx'}, {'Pt6Mtx'},...
	{'Tt21Mtx'}, {'Tt3Mtx'}, {'Tt4Mtx'}, {'Tt5Mtx'}, {'Tt6Mtx'}, {'WfMtx'}, {'AMtx'}, {'BMtx'}, {'Pt21DMtx'}, {'Pt3DMtx'}, {'Pt5DMtx'}, {'Pt6DMtx'},...
	{'Tt21DMtx'}, {'Tt3DMtx'}, {'Tt4DMtx'}, {'Tt5DMtx'}, {'Tt6DMtx'}, {'NcFANMapMtx'}, {'WcFANMapMtx'}, {'WcFANStallMtx'}, {'PRFANMapMtx'},...
	{'PRFANStallMtx'}, {'EffFANMapMtx'}, {'NcHPTMapMtx'}, {'WcHPTMapMtx'}, {'PRHPTMapMtx'}, {'EffHPTMapMtx'},...
	{'NcHPCMapMtx'}, {'WcHPCMapMtx'}, {'WcHPCStallMtx'}, {'PRHPCMapMtx'}, {'PRHPCStallMtx'}, {'EffHPCMapMtx'}, {'MNLinVec'}, {'AltLinVec'}, {'DeltaMtx'}, {'Ts0Mtx'},...
    {'AwmMtx'}, {'AshMtx'}, {'BwmMtx'}, {'BshMtx'}, {'RPMwmMtx'}, {'RPMshMtx'}, {'Tt4CshMtx'}, {'Tt4DshMtx'}, {'Tt4shMtx'}, {'WfshMtx'},...
	{'ASVec'}, {'DSVec'}, {'NcVec'}];
GetFuncMatrices = [GetFuncMatrices {'NcFANshMtx'},{'WfwmMtx'},{'Pt3shMtx'},{'Pt3DshMtx'}];

word = 'GetFuncMatrices';
VecConc = [{'Pt21wmMtx'},{'Pt21DwmMtx'},{'Pt3wmMtx'},{'Pt3DwmMtx'},{'Pt5wmMtx'},{'Pt5DwmMtx'},{'Pt6wmMtx'},{'Pt6DwmMtx'}];
GetFuncMatrices = ConcatNoRepeat(GetFuncMatrices,VecConc,word);
VecConc = [{'Tt21wmMtx'},{'Tt21DwmMtx'},{'Tt3wmMtx'},{'Tt3DwmMtx'},{'Tt4wmMtx'},{'Tt4DwmMtx'},{'Tt5wmMtx'},{'Tt5DwmMtx'},{'Tt6wmMtx'},{'Tt6DwmMtx'}];
GetFuncMatrices = ConcatNoRepeat(GetFuncMatrices,VecConc,word);
% VecConc = [{'Pt21shMtx'},{'Pt21DshMtx'},{'Pt5shMtx'},{'Pt5DshMtx'},{'Pt6shMtx'},{'Pt6DshMtx'}];
% GetFuncMatrices = ConcatNoRepeat(GetFuncMatrices,VecConc,word);
% VecConc = [{'Tt21shMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3DshMtx'},{'Tt5shMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6DshMtx'}];
% GetFuncMatrices = ConcatNoRepeat(GetFuncMatrices,VecConc,word);
VecConc = [{'Pt21shMtx'},{'Pt21DshMtx'},{'Pt3shMtx'},{'Pt3DshMtx'},{'Pt5shMtx'},{'Pt5DshMtx'},{'Pt6shMtx'},{'Pt6DshMtx'}];
GetFuncMatrices = ConcatNoRepeat(GetFuncMatrices,VecConc,word);
VecConc = [{'Tt21shMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3DshMtx'},{'Tt4shMtx'},{'Tt4CshMtx'},{'Tt4DshMtx'},{'Tt5shMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6DshMtx'}];
GetFuncMatrices = ConcatNoRepeat(GetFuncMatrices,VecConc,word);

%Adds C matrices
% VecConc = [{'Pt21CwmMtx'},{'Pt3CwmMtx'},{'Pt5DwmMtx'},{'Pt6DwmMtx'}];
% GetFuncMatrices = ConcatNoRepeat(GetFuncMatrices,VecConc,word);
% VecConc = [{'Tt21CwmMtx'},{'Tt3CwmMtx'},{'Tt5CwmMtx'},{'Tt6CwmMtx'}];
% GetFuncMatrices = ConcatNoRepeat(GetFuncMatrices,VecConc,word);
% VecConc = [{'Pt21CshMtx'},{'Pt3CshMtx'},{'Pt5CshMtx'},{'Pt6CshMtx'}];
% GetFuncMatrices = ConcatNoRepeat(GetFuncMatrices,VecConc,word);
% VecConc = [{'Tt21CshMtx'},{'Tt3CshMtx'},{'Tt5CshMtx'},{'Tt6CshMtx'}];
% GetFuncMatrices = ConcatNoRepeat(GetFuncMatrices,VecConc,word);

% %The complements below do not include the C matrices, except for Tt4, which
% %is commented
% GetFuncMatrices = [GetFuncMatrices {'Pt21wmMtx'},{'Pt21DwmMtx'},{'Pt3wmMtx'},{'Pt3DwmMtx'},{'Pt5wmMtx'},{'Pt5DwmMtx'},{'Pt6wmMtx'},{'Pt6DwmMtx'}];
% GetFuncMatrices = [GetFuncMatrices {'Tt21wmMtx'},{'Tt21DwmMtx'},{'Tt3wmMtx'},{'Tt3DwmMtx'},{'Tt4wmMtx'},{'Tt4DwmMtx'},{'Tt5wmMtx'},{'Tt5DwmMtx'},{'Tt6wmMtx'},{'Tt6DwmMtx'}];
% GetFuncMatrices = [GetFuncMatrices {'Pt21shMtx'},{'Pt21DshMtx'},{'Pt5shMtx'},{'Pt5DshMtx'},{'Pt6shMtx'},{'Pt6DshMtx'}];
% GetFuncMatrices = [GetFuncMatrices {'Tt21shMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3DshMtx'},{'Tt5shMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6DshMtx'}];
% % GetFuncMatrices = [GetFuncMatrices {'Pt21shMtx'},{'Pt21DshMtx'},{'Pt3shMtx'},{'Pt3DshMtx'},{'Pt5shMtx'},{'Pt5DshMtx'},{'Pt6shMtx'},{'Pt6DshMtx'}];
% % GetFuncMatrices = [GetFuncMatrices {'Tt21shMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3DshMtx'},{'Tt4shMtx'},{'Tt4CshMtx'},{'Tt4DshMtx'},{'Tt5shMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6DshMtx'}];

%The complements below include the C matrices
% GetFuncMatrices = [GetFuncMatrices {'Pt21wmMtx'},{'Pt21CwmMtx'},{'Pt21DwmMtx'},{'Pt3wmMtx'},{'Pt3CwmMtx'},{'Pt3DwmMtx'},{'Pt5wmMtx'},{'Pt5CwmMtx'},{'Pt5DwmMtx'},{'Pt6wmMtx'},{'Pt6CwmMtx'},{'Pt6DwmMtx'}];
% GetFuncMatrices = [GetFuncMatrices {'Tt21wmMtx'},{'Tt21CwmMtx'},{'Tt21DwmMtx'},{'Tt3wmMtx'},{'Tt3CwmMtx'},{'Tt3DwmMtx'},{'Tt4wmMtx'},{'Tt4CwmMtx'},{'Tt4DwmMtx'},{'Tt5wmMtx'},{'Tt5CwmMtx'},{'Tt5DwmMtx'},{'Tt6wmMtx'},{'Tt6CwmMtx'},{'Tt6DwmMtx'}];
% GetFuncMatrices = [GetFuncMatrices {'Pt21shMtx'},{'Pt21CshMtx'},{'Pt21DshMtx'},{'Pt3CshMtx'},{'Pt5shMtx'},{'Pt5CshMtx'},{'Pt5DshMtx'},{'Pt6shMtx'},{'Pt6CshMtx'},{'Pt6DshMtx'}];
% GetFuncMatrices = [GetFuncMatrices {'Tt21shMtx'},{'Tt21CshMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3CshMtx'},{'Tt3DshMtx'},{'Tt5shMtx'},{'Tt5CshMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6CshMtx'},{'Tt6DshMtx'}];
% % GetFuncMatrices = [GetFuncMatrices {'Pt21shMtx'},{'Pt21CshMtx'},{'Pt21DshMtx'},{'Pt3shMtx'},{'Pt3CshMtx'},{'Pt3DshMtx'},{'Pt5shMtx'},{'Pt5CshMtx'},{'Pt5DshMtx'},{'Pt6shMtx'},{'Pt6CshMtx'},{'Pt6DshMtx'}];
% % GetFuncMatrices = [GetFuncMatrices {'Tt21shMtx'},{'Tt21CshMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3CshMtx'},{'Tt3DshMtx'},{'Tt4shMtx'},{'Tt4CshMtx'},{'Tt4DshMtx'},{'Tt5shMtx'},{'Tt5CshMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6CshMtx'},{'Tt6DshMtx'}];

% GetFuncMatrices = [GetFuncMatrices {'Dummy'}];

%Specifies matrices clled by FADEC and Model (for HIL simulation)              
GetFADECMatrices =  [{'AMtx'}, {'ASVec'}, {'AltLinVec'}, {'BMtx'}, {'DSVec'}, {'DeltaMtx'},...
                     {'FNcMaxContMtx'}, {'FNperContMtx'}, {'MNLinVec'}, {'N_KiMtx'}, {'N_KpMtx'},...
                     {'NcFANContMtx'}, {'NcHPCMapMtx'}, {'NcVec'}, {'PRHPCMapMtx'}, {'Pt3DMtx'}, {'Pt3Mtx'},...
                     {'Pt5DMtx'}, {'Pt5Mtx'}, {'Ts0Mtx'}, {'Tt4DMtx'}, {'Tt4Mtx'}, {'Tt5DMtx'}, {'Tt5Mtx'},...
                     {'WcHPCMapMtx'}, {'WfMtx'}];
if SubIdleModel == 2
    %VecConc = [{'N_KpshMtx'},{'N_KishMtx'},{'NcFANshContMtx'}];
    GetFADECMatrices = [GetFADECMatrices {'N_KpshMtx'},{'N_KishMtx'},{'NcFANshContMtx'}];
end
%Specifies matrices only called by Model               
GetHILMatrices = [{'AshMtx'}, {'AwmMtx'}, {'BshMtx'}, {'BwmMtx'}, {'EffFANMapMtx'}, {'EffHPCMapMtx'},...
                    {'EffHPTMapMtx'}, {'NcFANMapMtx'}, {'NcHPTMapMtx'}, {'NcMtx'}, {'PRFANMapMtx'},...
                    {'PRFANStallMtx'}, {'PRHPCStallMtx'}, {'PRHPTMapMtx'}, {'Pt21DMtx'}, {'Pt21Mtx'},...
                    {'Pt6DMtx'}, {'Pt6Mtx'}, {'RPMshMtx'}, {'RPMwmMtx'}, {'Tt21DMtx'}, {'Tt21Mtx'},...
                    {'Tt3DMtx'}, {'Tt3Mtx'}, {'Tt4CshMtx'}, {'Tt4DshMtx'}, {'Tt4shMtx'}, {'Tt6DMtx'},...
                    {'Tt6Mtx'}, {'WcFANMapMtx'}, {'WcFANStallMtx'}, {'WcHPCStallMtx'}, {'WcHPTMapMtx'},...
                    {'WfshMtx'}];
GetHILMatrices = [GetHILMatrices {'NcFANshMtx'},{'WfwmMtx'},{'Pt3shMtx'},{'Pt3DshMtx'}];

word = 'GetHILMatrices';
VecConc = [{'Pt21wmMtx'},{'Pt21DwmMtx'},{'Pt3wmMtx'},{'Pt3DwmMtx'},{'Pt5wmMtx'},{'Pt5DwmMtx'},{'Pt6wmMtx'},{'Pt6DwmMtx'}];
GetHILMatrices = ConcatNoRepeat(GetHILMatrices,VecConc,word);
VecConc = [{'Tt21wmMtx'},{'Tt21DwmMtx'},{'Tt3wmMtx'},{'Tt3DwmMtx'},{'Tt4wmMtx'},{'Tt4DwmMtx'},{'Tt5wmMtx'},{'Tt5DwmMtx'},{'Tt6wmMtx'},{'Tt6DwmMtx'}];
GetHILMatrices = ConcatNoRepeat(GetHILMatrices,VecConc,word);
% VecConc = [{'Pt21shMtx'},{'Pt21DshMtx'},{'Pt5shMtx'},{'Pt5DshMtx'},{'Pt6shMtx'},{'Pt6DshMtx'}];
% GetHILMatrices = ConcatNoRepeat(GetHILMatrices,VecConc,word);
% VecConc = [{'Tt21shMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3DshMtx'},{'Tt5shMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6DshMtx'}];
% GetHILMatrices = ConcatNoRepeat(GetHILMatrices,VecConc,word);
VecConc = [{'Pt21shMtx'},{'Pt21DshMtx'},{'Pt3shMtx'},{'Pt3DshMtx'},{'Pt5shMtx'},{'Pt5DshMtx'},{'Pt6shMtx'},{'Pt6DshMtx'}];
GetHILMatrices = ConcatNoRepeat(GetHILMatrices,VecConc,word);
VecConc = [{'Tt21shMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3DshMtx'},{'Tt4shMtx'},{'Tt4CshMtx'},{'Tt4DshMtx'},{'Tt5shMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6DshMtx'}];
GetHILMatrices = ConcatNoRepeat(GetHILMatrices,VecConc,word);

%Adds C matrices
% VecConc = [{'Pt21CwmMtx'},{'Pt3CwmMtx'},{'Pt5CwmMtx'},{'Pt6CwmMtx'}];
% GetHILMatrices = ConcatNoRepeat(GetHILMatrices,VecConc,word);
% VecConc = [{'Tt21CwmMtx'},{'Tt3CwmMtx'},{'Tt5CwmMtx'},{'Tt6CwmMtx'}];
% GetHILMatrices = ConcatNoRepeat(GetHILMatrices,VecConc,word);
% VecConc = [{'Pt21CshMtx'},{'Pt3CshMtx'},{'Pt5CshMtx'},{'Pt6CshMtx'}];
% GetHILMatrices = ConcatNoRepeat(GetHILMatrices,VecConc,word);
% VecConc = [{'Tt21CshMtx'},{'Tt3CshMtx'},{'Tt5CshMtx'},{'Tt6CshMtx'}];
% GetHILMatrices = ConcatNoRepeat(GetHILMatrices,VecConc,word);

% %The complements below do not include the C matrices, except for Tt4, which
% %is commented
% GetHILMatrices = [GetHILMatrices {'Pt21wmMtx'},{'Pt21DwmMtx'},{'Pt3wmMtx'},{'Pt3DwmMtx'},{'Pt5wmMtx'},{'Pt5DwmMtx'},{'Pt6wmMtx'},{'Pt6DwmMtx'}];
% GetHILMatrices = [GetHILMatrices {'Tt21wmMtx'},{'Tt21DwmMtx'},{'Tt3wmMtx'},{'Tt3DwmMtx'},{'Tt4wmMtx'},{'Tt4DwmMtx'},{'Tt5wmMtx'},{'Tt5DwmMtx'},{'Tt6wmMtx'},{'Tt6DwmMtx'}];
% GetHILMatrices = [GetHILMatrices {'Pt21shMtx'},{'Pt21DshMtx'},{'Pt3shMtx'},{'Pt3DshMtx'},{'Pt5shMtx'},{'Pt5DshMtx'},{'Pt6shMtx'},{'Pt6DshMtx'}];
% GetHILMatrices = [GetHILMatrices {'Tt21shMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3DshMtx'},{'Tt5shMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6DshMtx'}];
% % GetHILMatrices = [GetHILMatrices {'Tt21shMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3DshMtx'},{'Tt4shMtx'},{'Tt4CshMtx'},{'Tt4DshMtx'},{'Tt5shMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6DshMtx'}];

%The complements below include the C matrices
% GetHILMatrices = [GetHILMatrices {'Pt21wmMtx'},{'Pt21CwmMtx'},{'Pt21DwmMtx'},{'Pt3wmMtx'},{'Pt3CwmMtx'},{'Pt3DwmMtx'},{'Pt5wmMtx'},{'Pt5CwmMtx'},{'Pt5DwmMtx'},{'Pt6wmMtx'},{'Pt6CwmMtx'},{'Pt6DwmMtx'}];
% GetHILMatrices = [GetHILMatrices {'Tt21wmMtx'},{'Tt21CwmMtx'},{'Tt21DwmMtx'},{'Tt3wmMtx'},{'Tt3CwmMtx'},{'Tt3DwmMtx'},{'Tt4wmMtx'},{'Tt4CwmMtx'},{'Tt4DwmMtx'},{'Tt5wmMtx'},{'Tt5CwmMtx'},{'Tt5DwmMtx'},{'Tt6wmMtx'},{'Tt6CwmMtx'},{'Tt6DwmMtx'}];
% GetHILMatrices = [GetHILMatrices {'Pt21shMtx'},{'Pt21CshMtx'},{'Pt21DshMtx'},{'Pt3shMtx'},{'Pt3CshMtx'},{'Pt3DshMtx'},{'Pt5shMtx'},{'Pt5CshMtx'},{'Pt5DshMtx'},{'Pt6shMtx'},{'Pt6CshMtx'},{'Pt6DshMtx'}];
% GetHILMatrices = [GetHILMatrices {'Tt21shMtx'},{'Tt21CshMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3CshMtx'},{'Tt3DshMtx'},{'Tt5shMtx'},{'Tt5CshMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6CshMtx'},{'Tt6DshMtx'}];
% % GetHILMatrices = [GetHILMatrices {'Tt21shMtx'},{'Tt21CshMtx'},{'Tt21DshMtx'},{'Tt3shMtx'},{'Tt3CshMtx'},{'Tt3DshMtx'},{'Tt4shMtx'},{'Tt4CshMtx'},{'Tt4DshMtx'},{'Tt5shMtx'},{'Tt5CshMtx'},{'Tt5DshMtx'},{'Tt6shMtx'},{'Tt6CshMtx'},{'Tt6DshMtx'}];

%Concatenates both sets of matrices for checking
GetFADECModel = [GetFADECMatrices GetHILMatrices];

%Checks if concatenation of FADEC and Model matrices are missing any of the
%total functions present on previous get command
Missing = [];
for i = 1:length(GetFuncMatrices)
    if ~ismember(GetFuncMatrices(i),GetFADECModel)
        Missing = [Missing GetFuncMatrices(i)];
    end
end

GetFuncConst = cellstr(['void get' EngineName 'ContConst(struct ControllerConstants *ContConst);']);

%Finds difference between matrices in get functions and the total of
%matrices
DiffMatrices = [];
for i = 1:length(AllMatrices)
    if ~ismember(AllMatrices(i),GetFuncMatrices)
        DiffMatrices = [DiffMatrices AllMatrices(i)];
    end
end

%Defines a vector with the number of different corrected rotation speeds
%used
NcFANMtx_FirstRow = NcFANMtx(1,:);
PRFANMap_FirstRow = PRFANMap(1,:);

%Defines matrices from which element numbers are aquired
% SizeMatrices = [{'AltLinVec'},{'MNLinVec'},{'NcFANMtx_FirstRow'},{'AMtx'},...
%                 {'N_KiMtx'},{'NcFANMap'},{'WcFANMap'},{'NcHPCMap'},...
%                 {'WcHPCMap'},{'NcHPTMap'}, {'WcHPTMap'},{'PRHPTMap'}];

% SizeMsgs = [{'/*Number of altitude points used for gain calculation */'},...
%             {'/* Number of Mach number points used for gains calculation */'},...
%             {'/* Number of different corrected rotation speeds used in linearization */'},...
%             {'/* Number of steady operating points used for linearization at Sea Level */'},...
%             {'/* Number of total steady operating points used for Power Management Controller - all altitudes */'},...
%             {'/* Number of Nc point in Fan map */'},...
%             {'/* Number of Wc points in Fan map */'},...
%             {'/* Number of Nc point in HPC map */'},...
%             {'/* Number of Wc points in HPC map */'},...
%             {'/* Number of Nc points in Fan map */'},...
%             {'/* Number of Wc point in HPC map */'},...
%             {'/* Number of PR points in HPC map */'}];

%----------------------------
%DEFINITION OF SIZE CONSTANTS
%----------------------------

%List of all size constants
SizeVars = [{'Alt_Elem'},{'MN_Elem'},{'Fn_Elem'}, {'AS_Elem'},{'SteadyOp_Elem'},...
            {'PowerMan_Elem'},{'NcFANMap_Elem'},{'WcFANMap_Elem'},{'Wc_per_Nc_FAN'},... 
            {'NcHPCMap_Elem'},{'WcHPCMap_Elem'},{'Wc_per_Nc_HPC'},{'NcHPTMap_Elem'},... 
            {'PRHPTMap_Elem'},{'WcHPTMap_Elem'}];
        
SizeDefs = [cellstr([EngineName '_ALT_ELEM']), cellstr([EngineName '_MN_ELEM']),...
            cellstr([EngineName '_FN_ELEM']), cellstr([EngineName '_AS_ELEM']),...
            cellstr([EngineName '_FN_ELEM *' EngineName '_MN_ELEM']),...
            cellstr([EngineName '_TOTAL_ELEM']),cellstr([EngineName '_FAN_NC']),...
            cellstr([EngineName '_FAN_NC * ' EngineName '_FAN_PR;']), cellstr([EngineName '_FAN_PR']),...
            cellstr([EngineName '_FAN_NC']), cellstr([EngineName '_FAN_NC * ' EngineName '_FAN_PR']),...
            cellstr([EngineName '_FAN_PR']), cellstr([EngineName '_HPT_NC']),...
            cellstr([EngineName '_HPT_PR']), cellstr([EngineName '_HPT_NC * ' EngineName '_HPT_PR'])];
        
 %List of size constants used by FADEC
 SizeVarsFADEC = [{'Alt_Elem'},{'MN_Elem'},{'Fn_Elem'}, {'AS_Elem'},{'SteadyOp_Elem'},...
                  {'PowerMan_Elem'},... 
                  {'NcHPCMap_Elem'},{'WcHPCMap_Elem'},{'Wc_per_Nc_HPC'}];
              
 SizeDefsFADEC = [];
 SizeVarsHIL = [];
 SizeDefsHIL = [];
  
 %Defines lists of size constants used by FADEC and HIL
 for i = 1:length(SizeVars)
     if ismember(SizeVars(i),SizeVarsFADEC)
         SizeDefsFADEC = [SizeDefsFADEC SizeDefs(i)];
     else
         SizeVarsHIL = [SizeVarsHIL SizeVars(i)];
         SizeDefsHIL = [SizeDefsHIL SizeDefs(i)];
     end
 end

%-------------------------------------------------------------------------
%ELABOARION OF SIZE ELEMENTS IN xxxConstants.h - For copying to final file
%-------------------------------------------------------------------------
           
SizeMsgs = [{'/* Steady Operating Points Elements Numbers */'},...
            {''},{''},{''},{''},...
            {'/* Components Maps Element Numbers */'},...
            {''},{''},{''},...
            {'/* Engine Design Point Constants */'},...
            {''}];
DividingIndex = [0 0 0 0 0 6 0 0 0 10 0];

%Different definitions for the single spool turbofan engines and turbojet
%engines
SizeMatrices = [{'AltLinVec'},{'MNLinVec'},{'NcFANMtx_FirstRow'},{'N_KiMtx'},...
    {'ASVec'},{'NcFANMap'},{'PRFANMap_FirstRow'},...
    {'NcHPTMap'},{'PRHPTMap'},{'NDes'},{'AthDes'}];

SizeDefines = [{'_ALT_ELEM				       '},...
    {'_MN_ELEM 				       '},...
    {'_FN_ELEM				       '},...
    {'_TOTAL_ELEM			       '},...
    {'_AS_ELEM				       '},...
    {'_FAN_NC                      '},...
    {'_FAN_PR                      '},...
    {'_HPT_NC				       '},...
    {'_HPT_PR				       '},...
    {'_NDES                        '},...
    {'_Ath_NOZZLE                  '}];
           
%--------------------
%CONTROLLER CONSTANTS
%--------------------

ContConstPars

%------------------
%STARTING CONSTANTS
%------------------

StartPars

%----------------
%ENGINE CONSTANTS
%----------------

EngConst
                        
%-------------------------------------
%GENERATION OF C CODE FOR ALL MATRICES
%-------------------------------------

CallCodeGenAllMtx

%--------------------------------------
%GENERATION OF C CODE FOR FADEC AND HIL
%--------------------------------------

%Definition of folder for copying the C
%code
SourceFolder = AllgetCSource;
%Definition of folder containing engine functions calls for easier code
%writing
CallsFolderName = [EngFoldName File_Sep 'FunctionCalls'];
CodeGenMkDir(CallsFolderName,'');
%Generation of FADEC codes
CodeGenFADEC;
%Generation of HIL codes
CodeGenHIL;

%-------------------------------------------
%GENERATION FILE CONTAINING ELEMENTS NUMBERS
%-------------------------------------------

%Function name
FuncName = 'MtxSizes';
%Word do be used as function inputs
cellsword = [{'SizeMsgs'},{'DividingIndex'},{'SizeDefines'},{'GetFuncMatrices'},{'VarsPerLine'},{'EngineName'},{'EngFoldName'}];
cellsword = [cellsword SizeMatrices];
%Initiates auxiliar word
word = [];

%Loop for generating function callilng with the required arguments
for i = 1:length(cellsword)
    if i == 1
        word = [word FuncName '('];
    end
    if i == length(cellsword)
        word = [word char(cellsword(i)) ');'];
    else
        word = [word char(cellsword(i)) ','];
    end
end

%Executes function for generating C code
eval(word);

%
CodeOrganizer

%WARNING IN CASE ANY MATRICES OR VECTORS ARE MISSING IN EITHER FADEC OR
%MODEL MATRICES

%Verifies if relation of missing matrices is empty
if ~isempty(Missing)
    %Prints begining of warning
    disp(' ')
    disp('WARNING!!')
    disp(' ')
    word = ['Matrix or Vectors:' ];
    disp(word)
    wordMiss = [];
    %Constructs missing list for printing
    for i = 1:length(Missing)
        wordMiss = [wordMiss Missing{i} ' '];
    end
    %Prints missing list and rest of warining
    disp(wordMiss)
    word = ['are missing in either FADEC or Model matrices!!'];
    disp(word)
    disp(' ')
end
