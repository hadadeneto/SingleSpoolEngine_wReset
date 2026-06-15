
%--------------------------------------------------------------
%GAINS TO BE USED IN CASE T-MATS BLOCKS ARE ADDED TO THE MODEL
%--------------------------------------------------------------

%Reads the size of AMts
[line,column,page] = size(AshMtx);

%Saves sea-level matrices
% FNMtxSL = FNMtx;
% WfMtxSL = WfMtx;
AshMtxSL = AshMtx;
BshMtxSL = BshMtx;
% FNperMtxSL = FNperMtx;
NcFANshMtxSL = NcFANshMtx;

%Recalculates for Sea Level if pump model is considered
% FirstIndex = 2 - AddPump;
FirstIndex = 1;

%Calculates the absolute parametes for other altitudes
% for i = 2:length(AltLinVectorPT)
for i = FirstIndex:length(AltLinVectorPT)
    for j=1:length(MNVectorPT)
        %         FNMtx(j,:,i) = FNcMtx(j,:,1) * DeltaMtx(i,j);
        %         WfMtx(j,:,i) = WfcMtx(j,:,1) * DeltaMtx(i,j) * sqrThetaMtx(i,j);
        
        %         for j = 1:length(MNVectorPT)
        %
        %             %Sea level parameters
        DeltaSL = DeltaMtx(1,j);
        ThetaSL = ThetaMtx(1,j);
        %             sqrThetaSL = sqrThetaMtx(1,j);
        %             AshcMtx(j,:,1) = AMtx(j,:,1) * sqrThetaSL / DeltaSL;
        %             BshcMtx(j,:,1) = BMtx(j,:,1) * sqrThetaSL;
        %         end
        
        Ashc = AshMtx(j,:,1) * sqrThetaSL / DeltaSL;
        Bshc = BshMtx(j,:,1) * sqrThetaSL;
        AshMtx(j,:,i) = Ashc * DeltaMtx(i,j) / sqrThetaMtx(i,j);
        BshMtx(j,:,i) = Bshc / sqrThetaMtx(i,j);
        %         FNperMtx(j,:,i) = FNMtx(j,:,i) / FNMtx(j,end,i);
        NcshMtx(j,:,i) = NcFANshMtx(j,:,1);
        
        N_KpshMtx(j,:,i) = zeros(1,column);
        N_KishMtx(j,:,i) = zeros(1,column);
        
        for k = 1:column
            
            clc
            WORD = ['Sub-Idle Region - Calculating for: '];
            WORD = [WORD 'Alt = ' num2str(AltLinVectorPT(i)) '; '];
            WORD = [WORD 'MN = ' num2str(MNVectorPT(j)) '; '];
            WORD = [WORD 'Element = ' num2str(k) '; '];
            disp(' ')
            disp(WORD)
            
            numtf = BshMtx(j,k,i);
            dentf = [1 -AshMtx(j,k,i)];
            
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
            wcshMaxIn = wcshMax;
            wcshMinIn = wcshMin;
            
            %Redefines wcMax and wcMin if required, according to wcDefMode
            
            %In Mode 1, the WcMax is defined as the value of A at the
            %maximum power of the current altitude and current Mach number,
            %while Wc Min is defined as 0.15 * WcMin
            if(wcshDefMode == 1)
                wcshMaxIn = abs(AshMtx(j,1,i));
                wcshMinIn = max(wcshMin,wcshMaxIn * 0.15);
            end
            %In Mode 2, the WcMax is defined as the value of A at the
            %maximum power of the current altitude and current Mach number,
            %while Wc Min is defined as the value of A at minimum power of
            %the current altitude and current Mach number
            if(wcshDefMode == 2)
                wcshMaxIn = max(abs(AshMtx(j,1,i)),wcshMax);
                wcshMinIn = max(abs(AshMtx(j,end,i)),wcshMin);
            end
            %In Mode 3, the WcMax is defined as the value of A at the
            %maximum power of the current altitude and static conditions,
            %while Wc Min is defined as WcMax * 0.15
            if(wcshDefMode == 3)
                wcshMaxIn = abs(AshMtx(1,end,i));
                wcshMinIn = 0.15 * wcshMaxIn;
            end
            
            %Designs PI to grant desired overshoot limits
            [Kp,Ki,PMout,~] = PIOSLim(PM,wcshMinIn,wcshMaxIn,G,...
                MinshOSPM,MaxshOSPM,MinshOSwc,MaxshOSwc,MaxshIterPM,MaxshIterwc);
            
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
            
            N_KpshMtx(j,k,i) = Kp;
            N_KishMtx(j,k,i) = Ki;
            
            disp(' ')
            disp(['Kp = ' num2str(N_KpshMtx(j,k,i))])
            disp(' ')
            disp(['Ki = ' num2str(N_KishMtx(j,k,i))])
            
        end
        
    end
    
end

%Saves gains in PIGains structure
PIshGains.Kish = N_KishMtx;
PIshGains.Kpsh = N_KpshMtx;
PIshGains.NcFANsh = NcshMtx;
% PIshGains.FNper = FNperMtx;

word = ['cd ' EngFoldName];
eval(word);
save PIsh.mat PIshGains;
word = ['cd ' UpperFolder];
eval(word);

% AMtxAll = AMtx;
% BMtxAll = BMtx;
%
% %Updates Matrices with Sea-Level matrices for generating C code
% FNMtx = FNMtxSL;
% WfMtx = WfMtxSL;
AshMtx = AshMtxSL;
BshMtx = BshMtxSL;
% FNperMtx = FNperMtxSL;
NcFANshMtx = NcFANshMtxSL;
