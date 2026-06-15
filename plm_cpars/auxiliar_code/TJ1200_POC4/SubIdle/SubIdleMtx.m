
%--------------------------------
%CALCULATION OF SUB-IDLE MATRICES
%--------------------------------

switch SubIdleModel
    
    case 1
        
        %Calculates cold sub-idle (windmill) matrices
        [AwmMtx,BwmMtx,CwmMtx,DwmMtx,RPMwmMtx] = WindMillCalc(MNLinVec);
        %Calculate hot sub-idle (with combustion) matrices
        [AshMtx,BshMtx,Pt3CshMtx,Pt3DshMtx,Tt4CshMtx,Tt4DshMtx,...
         NcFANshMtx,WfshMtx,Tt4shMtx,Pt3shMtx,RPMshMtx] = SubIdleHotCalc;
        
    case 2
        
        %Calculates cold sub-idle (windmill matrices)
        [AwmMtx,BwmMtx,CwmMtx,DwmMtx,RPMwmMtx] = WindMillMtxLoad;
        %Calculates hot sub-idle (with combustion) matrices
        [AshMtx,BshMtx,Pt3CshMtx,Pt3DshMtx,Tt4CshMtx,Tt4DshMtx,...
         NcFANshMtx,WfshMtx,Tt4shMtx,Pt3shMtx,RPMshMtx] = SubIdleMtxLoad;        
end