
%CALCULATES CORRECTED MATRICES

for j = 1:length(MNVectorPT)
    
    %Sea level parameters
    DeltaSL = DeltaMtx(1,j);
    ThetaSL = ThetaMtx(1,j);
    sqrThetaSL = sqrThetaMtx(1,j);
        
    %State-Space Matrices for state variable
    AcMtx(j,:,1) = AMtx(j,:,1) * sqrThetaSL / DeltaSL;
    BcMtx(j,:,1) = BMtx(j,:,1) * sqrThetaSL;
    
    %Station 21
    Pt21cMtx(j,:,1) = Pt21Mtx(j,:,1) / DeltaSL;
    Pt21CcMtx(j,:,1) = Pt21CMtx(j,:,1) * sqrThetaSL / DeltaSL;
    Pt21DcMtx(j,:,1) = Pt21DMtx(j,:,1) * DeltaSL;
    Tt21cMtx(j,:,1) = Tt21Mtx(j,:,1) / ThetaSL;    
    Tt21CcMtx(j,:,1) = Tt21CMtx(j,:,1) / sqrThetaSL;
    Tt21DcMtx(j,:,1) = Tt21DMtx(j,:,1) * DeltaSL / sqrThetaSL;
    
    %Station 3
    Pt3cMtx(j,:,1) = Pt3Mtx(j,:,1) / DeltaSL;
    Pt3CcMtx(j,:,1) = Pt3CMtx(j,:,1) * sqrThetaSL / DeltaSL;
    Pt3DcMtx(j,:,1) = Pt3DMtx(j,:,1) * DeltaSL;
    Tt3cMtx(j,:,1) = Tt3Mtx(j,:,1) / ThetaSL;    
    Tt3CcMtx(j,:,1) = Tt3CMtx(j,:,1) / sqrThetaSL;
    Tt3DcMtx(j,:,1) = Tt3DMtx(j,:,1) * DeltaSL / sqrThetaSL;
    
    %Station 4
    Tt4cMtx(j,:,1) = Tt4Mtx(j,:,1) / ThetaSL;    
    Tt4CcMtx(j,:,1) = Tt4CMtx(j,:,1) / sqrThetaSL;
    Tt4DcMtx(j,:,1) = Tt4DMtx(j,:,1) * DeltaSL / sqrThetaSL;
    WfcMtx(j,:,1) = WfMtx(j,:,1) / DeltaSL / sqrThetaSL;
    
    %Station 5
    Pt5cMtx(j,:,1) = Pt5Mtx(j,:,1) / DeltaSL;
    Pt5CcMtx(j,:,1) = Pt5CMtx(j,:,1) * sqrThetaSL / DeltaSL;
    Pt5DcMtx(j,:,1) = Pt5DMtx(j,:,1) * DeltaSL;
    Tt5cMtx(j,:,1) = Tt5Mtx(j,:,1) / ThetaSL;    
    Tt5CcMtx(j,:,1) = Tt5CMtx(j,:,1) / sqrThetaSL;
    Tt5DcMtx(j,:,1) = Tt5DMtx(j,:,1) * DeltaSL / sqrThetaSL;
    
    %Station 6
    Pt6cMtx(j,:,1) = Pt6Mtx(j,:,1) / DeltaSL;
    Pt6CcMtx(j,:,1) = Pt6CMtx(j,:,1) * sqrThetaSL / DeltaSL;
    Pt6DcMtx(j,:,1) = Pt6DMtx(j,:,1) * DeltaSL;
    Tt6cMtx(j,:,1) = Tt6Mtx(j,:,1) / ThetaSL;    
    Tt6CcMtx(j,:,1) = Tt6CMtx(j,:,1) / sqrThetaSL;
    Tt6DcMtx(j,:,1) = Tt6DMtx(j,:,1) * DeltaSL / sqrThetaSL;
    
    %Station 8
    FNcMtx(j,:,1) = FNMtx(j,:,1) / DeltaSL;

end


%LOADS MATRICES WITH CORRECTED VALUES

%State variable
AMtx = AcMtx;
BMtx = BcMtx;

%Station 21
Tt21Mtx = Tt21cMtx;
Tt21CMtx = Tt21CcMtx;
Tt21DMtx = Tt21DcMtx;
Pt21Mtx = Pt21cMtx;
Pt21CMtx = Pt21CcMtx;
Pt21DMtx = Pt21DcMtx;

%Station 3
Tt3Mtx = Tt3cMtx;
Tt3CMtx = Tt3CcMtx;
Tt3DMtx = Tt3DcMtx;
Pt3Mtx = Pt3cMtx;
Pt3CMtx = Pt3CcMtx;
Pt3DMtx = Pt3DcMtx;

%Station 4
Tt4Mtx = Tt4cMtx;
Tt4CMtx = Tt4CcMtx;
Tt4DMtx = Tt4DcMtx;
WfMtx = WfcMtx;

%Station 5
Tt5Mtx = Tt5cMtx;
Tt5CMtx = Tt5CcMtx;
Tt5DMtx = Tt5DcMtx;
Pt5Mtx = Pt5cMtx;
Pt5CMtx = Pt5CcMtx;
Pt5DMtx = Pt5DcMtx;

%Station 6
Tt6Mtx = Tt6cMtx;
Tt6CMtx = Tt6CcMtx;
Tt6DMtx = Tt6DcMtx;
Pt6Mtx = Pt6cMtx;
Pt6CMtx = Pt6CcMtx;
Pt6DMtx = Pt6DcMtx;
