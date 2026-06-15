function [Kp,Ki,PM,Overshoot] = PIOSwc(PMMin,wc,G,MaxOSToll,MinOSToll,MaxIter)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

%Sets Options
% Options = pidtuneOptions('PhaseMargin',PM,'NumUnstablePoles',UnstP,...
%                          'DesignFocus',Focus);

%Initial wc
%[Info,InfoCL,~,Kp,Ki] = PIDesign(G,PM,7,1);
%[Info,InfoCL,~,Kp,Ki,Kd] = PIDesign(G,7,Struc,Options,1);

%Calculates OS
%OS = (MinOSToll + MaxOSToll)/2;

%Estimates the desired phase margin
PM = PMMin;%FreqRespCalc(OS);
PMHigh = 90;
PMLow = PMMin;
Iter = 0;

%Calculates Kp and Ki, granting a PM value for Kp > 0
[Kp,Ki,PM] = PIGains(G,wc,PM);

%Updates Controller
C = tf([Kp Ki],[1 0]);

%Tests the controller response
Gcl = G*C/(1 + G*C);
InfoCL = stepinfo(Gcl);

%Reads Initial Overshoot
Overshoot = InfoCL.Overshoot;

%Initializes flags
Decrease = 0;
Increase = 0;

%Verifies if the current design is close enought to the critical damped
%behavior
if (Overshoot <= MaxOSToll) && (Overshoot > MinOSToll)
    return;
end

%Analizes if should increase or decrease
if Overshoot > MaxOSToll
    Increase = 1;
else
    Decrease = 1;
end
% 
% %Initiates wcMax and wcMin
% wcMax = wc;
% wcMin = wc;

%Increases or decreases untill condition of overshoot is changed
while (Iter<MaxIter)&&(Overshoot <= MinOSToll || Overshoot > MaxOSToll)
    
    %Doubles wc untill the overshoot condition is changed
    if Increase
        PMLow = PM;
    elseif Decrease
        PMHigh = PM;
    end
    
    %Updates PM
    PM = (PMLow + PMHigh)/2;
    
    %Calculates a new controller
    %     [Info,InfoCL,~,Kp,Ki,Kd] = PIDesign(G,wc,Struc,Options,0);
    %Calculates Kp and Ki, granting a PM value for Kp > 0
    [Kp,Ki,PMout] = PIGains(G,wc,PM);
    
    %If Phase Margin can be decreased to a value smaller than the minimum
    %required for Kp >= 0, the miminum required is kept and calculation
    %ends
    if PMout > PM;
        PM = PMout;
        return;
    else
        PM = PMout;
    end
    
    %Updates Controller
    C = tf([Kp Ki],[1 0]);
    
    %Tests the controller response
    Gcl = G*C/(1 + G*C);
    InfoCL = stepinfo(Gcl);
    
%     %Reads Initial Overshoot
%     Overshoot = InfoCL.Overshoot;
    
    %Reads Overshoot
    Overshoot = InfoCL.Overshoot;
    
    %Verifies if the current design is close enought to the critical damped
    %behavior
    if (Overshoot <= MaxOSToll) && (Overshoot > MinOSToll)
        return;
    end
    
    %Analizes if should increase or decrease
    if Overshoot > MaxOSToll
        Decrease = 0;
        Increase = 1;
%         wc = Info.CrossoverFrequency;
%         wcMax = wc;
    elseif Overshoot <= MinOSToll
        Increase = 0;
        Decrease = 1;
        %         wc = Info.CrossoverFrequency;
        %         wcMin = wc;
    end
    
    %If current wc exceeds the maximum allowed value and the overshoot
    %value lies below the maximum permited, wcMax is addopted as the final
    %value for wc
    %     if wc > wcMaxVal
    %         %Calculates a new controller
    %         %[Info,InfoCL,~,Kp,Ki] = PIDesign(G,PM,wc,0);
    %         wc = wcMaxVal;
    %         [Info,InfoCL,~,Kp,Ki,Kd] = PIDesign(G,wc,Struc,Options,0);
    %         return;
    %
    %     end
    
    Iter = Iter + 1;
    
end

%Starts at the minimum frequency towards the maximum at a smaller step rate
%in order for the overshoot to lie within the established limit

% Iter = 0;
% %Updates the Value to
% Dwc = abs(wcMax - wcMin)/2;
% wc = wcMin;
% 
% %Updates flags for new interaction 
% Increase = 1;
%Decrease = 0;

% %Searches for a wc with an overshoot withing the specified interval
% while (Iter<MaxIter)&&(Overshoot <= MinOSToll || Overshoot > MaxOSToll)
%     
%     %Updates wc acconding to what should be the next step: increase or
%     %decrease frequency
%     if Increase
%         wc = wc + Dwc;
%     else
%         wc = wc - Dwc;
%     end
%     
%     %Calculates a new Controller
%     %[Info,InfoCL,~,Kp,Ki] = PIDesign(G,PM,wc,0);
%     [Info,InfoCL,~,Kp,Ki,Kd] = PIDesign(G,wc,Struc,Options,0);
%     
%     %Reads the Overshoot
%     Overshoot = InfoCL.Overshoot;
%     
%     %Verifies if the next step is increasing or decreasing
%     if Overshoot > MaxOSToll
%         Increase = 0;
%         wcMax = wc;
%     elseif Overshoot <= MinOSToll
%         Increase = 1;
%         wcMin = wc;
%     end
%     
%     %Updates Delta
%     Dwc = abs(wcMax - wcMin)/2;
%     
%     %Updates Iteraction
%     Iter = Iter + 1;
%     
% end

%teste = 1;



% for i=1:MaxIter
% [Info,InfoCL,C,Kp,Ki] = PIDesign(G,PM,wc);
% 
% end

