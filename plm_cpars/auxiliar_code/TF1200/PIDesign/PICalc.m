
%--------------------------------------------------------------
%GAINS TO BE USED IN CASE T-MATS BLOCKS ARE ADDED TO THE MODEL
%--------------------------------------------------------------

%Reads the size of AMts
[line,column,page] = size(AMtx);

%Saves sea-level matrices
FNMtxSL = FNMtx;
WfMtxSL = WfMtx;
AMtxSL = AMtx;
BMtxSL = BMtx;
FNperMtxSL = FNperMtx;
NcMtxSL = NcMtx;

%Recalculates for Sea Level if pump model is considered
FirstIndex = 2 - AddPump;

%Calculates the absolute parametes for other altitudes
% for i = 2:length(AltLinVectorPT)
for i = FirstIndex:length(AltLinVectorPT)
    for j=1:length(MNVectorPT)
        FNMtx(j,:,i) = FNcMtx(j,:,1) * DeltaMtx(i,j);
        WfMtx(j,:,i) = WfcMtx(j,:,1) * DeltaMtx(i,j) * sqrThetaMtx(i,j);
        AMtx(j,:,i) = AcMtx(j,:,1) * DeltaMtx(i,j) / sqrThetaMtx(i,j);
        BMtx(j,:,i) = BcMtx(j,:,1) / sqrThetaMtx(i,j);
        FNperMtx(j,:,i) = FNMtx(j,:,i) / FNMtx(j,end,i);
        NcMtx(j,:,i) = NcFANMtx(j,:,1);
        
        N_KpMtx(j,:,i) = zeros(1,column);
        N_KiMtx(j,:,i) = zeros(1,column);
        
        for k = 1:column
            
            clc
            WORD = ['Calculating for: '];
            WORD = [WORD 'Alt = ' num2str(AltLinVectorPT(i)) '; '];
            WORD = [WORD 'MN = ' num2str(MNVectorPT(j)) '; '];
            WORD = [WORD 'Element = ' num2str(k) '; '];
            disp(' ')
            disp(WORD)
                        
            numtf = BMtx(j,k,i);
            dentf = [1 -AMtx(j,k,i)];
            
            %Creates Local Transfer Function
            G = tf(numtf,dentf);
            
            %Initiates Zero-Order Holder transfer function
            Gzoh = 1;
            
            %Additon of Pandé approach for Zoh
            if AddZOH == 1
                Gzoh = tf(1,[Tsamp/2 1]);
            end
            %Addition of Zoh actual tranfer function
            if AddZOH == 2
                s = zpk('s');
                Gzoh = (1 - exp(-s*Tsamp))/s/Tsamp;
            end
            
            %Multiplies Jet engine transfer function for zero order holder
            G = G * Gzoh;
            
            %Addition of pump model;
            if AddPump
                G = G * Gp;
            end
                        
            %Defines the cut off frequency
            wcMaxIn = wcMax;
            wcMinIn = wcMin;
            
            %Redefines wcMax and wcMin if required, according to wcDefMode
            
            %In Mode 1, the WcMax is defined as the value of A at the
            %maximum power of the current altitude and current Mach number,
            %while Wc Min is defined as 0.15 * WcMin            
            if(wcDefMode == 1)
                wcMaxIn = abs(AMtx(j,1,i));
                wcMinIn = max(wcMin,wcMaxIn * 0.15);
            end
            %In Mode 2, the WcMax is defined as the value of A at the
            %maximum power of the current altitude and current Mach number,
            %while Wc Min is defined as the value of A at minimum power of
            %the current altitude and current Mach number
            if(wcDefMode == 2)
                wcMaxIn = max(abs(AMtx(j,1,i)),wcMax);
                wcMinIn = max(abs(AMtx(j,end,i)),wcMin);
            end
            %In Mode 3, the WcMax is defined as the value of A at the
            %maximum power of the current altitude and static conditions,
            %while Wc Min is defined as WcMax * 0.15
            if(wcDefMode == 3)
                wcMaxIn = abs(AMtx(1,end,i));
                wcMinIn = 0.15 * wcMaxIn;
            end
            
            %Designs PI to grant desired overshoot limits
            [Kp,Ki,PMout,~] = PIOSLim(PM,wcMinIn,wcMaxIn,G,...
                MinOSPM,MaxOSPM,MinOSwc,MaxOSwc,MaxIterPM,MaxIterwc);
            
            if (Ki <= 0)
                disp(' ')
                disp('FAIL -> Ki <= 0')
                break;
            end
            if (Kp < 0)
                disp(' ')
                disp('FAIL -> Kp < 0')
                break;
            end
            
            N_KpMtx(j,k,i) = Kp;
            N_KiMtx(j,k,i) = Ki;
            
            disp(' ')
            disp(['Kp = ' num2str(N_KpMtx(j,k,i))])
            disp(' ')
            disp(['Ki = ' num2str(N_KiMtx(j,k,i))])
            
        end
        
    end
    
end

%Saves gains in PIGains structure
PIGains.Ki = N_KiMtx;
PIGains.Kp = N_KpMtx;
PIGains.NcFAN = NcMtx;
PIGains.FNper = FNperMtx;

save PI.mat PIGains;

AMtxAll = AMtx;
BMtxAll = BMtx;

%Updates Matrices with Sea-Level matrices for generating C code
FNMtx = FNMtxSL;
WfMtx = WfMtxSL;
AMtx = AMtxSL;
BMtx = BMtxSL;
FNperMtx = FNperMtxSL;
NcMtx = NcMtxSL;
