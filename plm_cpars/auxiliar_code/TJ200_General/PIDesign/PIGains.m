function [Kp,Ki,PM] = PIGains(G,wc,PM)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

%Obtains the frequency response of G for wg and wh
Gwc = evalfr(G,1j*wc);

%Compute the pahse and gain at the chosen freuency
PhaseGwc = phase(Gwc)*180/pi;
AbsGwc = abs(Gwc);

%Grants that the phase margin is appropriate
if (PM < 90 + PhaseGwc) || (PM > 180 + PhaseGwc)
    PM = PhaseGwc + 90 + eps;
end

%Calculates Kp
%Kp = -(cosd(PM)*cosd(PhaseGwc) + sind(PM)*sind(PhaseGwc))/AbsGwc;
Kp = -1/AbsGwc*cosd(PM-PhaseGwc);

%Calculates D for future calculation of Ki
%Ki = wc*(sind(PM)*cosd(PhaseGwc) - cosd(PM)*sind(PhaseGwc))/AbsGwc;
Ki = wc/AbsGwc*sind(PM-PhaseGwc);

%Calculates Ki
%Ki = -wc*D;


end

