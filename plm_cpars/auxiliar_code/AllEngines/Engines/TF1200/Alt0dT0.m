function [MN,A, B, C, D,...
    N_Kp, N_Ki, Pt3_Kp, Pt3_Ki,...
    Tt4_Kp, Tt4_Ki, Tt5_Kp, Tt5_Ki,...
    NcFAN,...
    Pt21, Tt21,...
    Pt3, Tt3,...
    Tt4, Wf,...
    Pt5, Tt5,...
    Pt6, Tt6,...
    FN, FNper] = Alt0dT0

%Loads linearization matrices data
TMATSLinMtx

%Reads the size of the FNper Matrix
[~,col] = size(FNper);

%Corrects vector order if thrust vector is backwards
if FNper(1,col) < FNper(1,1)
    
    A  =  fliplr(A);
    B  =  fliplr(B);
    C  =  fliplr(C);
    D  =  fliplr(D);
    
    N_Kp  =  fliplr(N_Kp);
    N_Ki  =  fliplr(N_Ki);
    Pt3_Kp  =  fliplr(Pt3_Kp);
    Pt3_Ki  =  fliplr(Pt3_Ki);
    Tt4_Kp  =  fliplr(Tt4_Kp);
    Tt4_Ki  =  fliplr(Tt4_Ki);
    Tt5_Kp  =  fliplr(Tt5_Kp);
    Tt5_Ki  =  fliplr(Tt5_Ki);
    
    NcFAN  =  fliplr(NcFAN);
    
    Pt21  =  fliplr(Pt21);
    Tt21  =  fliplr(Tt21);
    Pt3   =  fliplr(Pt3);
    Tt3   = fliplr(Tt3);
    Tt4   =  fliplr(Tt4);
    Pt5   =  fliplr(Pt5);
    Tt5   = fliplr(Tt5);
    Pt6   =  fliplr(Pt6);
    Tt6   = fliplr(Tt6);
    FN    =  fliplr(FN);
    FNper =  fliplr(FNper);
    Wf = fliplr(Wf);
    
end

end

