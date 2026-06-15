function [Kp,Ki,PM,wc] = PIOSLim(PMMin,wcMin,wcMax,G,MinOSTollPM,MaxOSTollPM,MinOSTollwc,MaxOSTollwc,MaxIterPM,MaxIterwc)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%Stores the value of wc to be worked
wc = wcMax;
%Calculates a first set of Kp,Ki
[Kp,Ki,PM,Overshoot] = PIOSwc(PMMin,wc,G,MaxOSTollPM,MinOSTollPM,MaxIterPM);

%Initiates iteraction number
Iter = 0;
%Loop to guarantee the desired overshoot value
while ((Overshoot > MaxOSTollwc)||(Overshoot < MinOSTollwc)) && (Iter < MaxIterwc) 
    
    if Overshoot > MaxOSTollwc
        wcMax = wc;
        wc = (wc + wcMin)/2;
    elseif Overshoot < MinOSTollwc
        wcMin = wc;
        wc = (wc + wcMax)/2; 
        %If it is alredy at its maximum cut off frequency but still can be
        %increase, leave like that
        if wc >= wcMax
            return;
        end
    end
    
    %Tries to reach the desired overshoot interval
    [Kp,Ki,PM,Overshoot] = PIOSwc(PMMin,wc,G,MaxOSTollPM,MinOSTollPM,MaxIterPM);
    
    Iter = Iter + 1;
  
end




end

