function [Theta,Delta] = ThetaDelta(Altitude,AltVec,MN,dT,P0Vec,T0Vec)
%ThetaDelta - Calculates the values of Theta and Delta
%   Recieves the values of Altitude, Mach Number and Altitude Vector and
%   calculates the values of Theta and Delta considering ISA + 0

%Defines the vaule of gamma air
gamma = 1.4;

%Calculates the values of P0 and T0 according to altitude
[k1H,k1L,f1,~] = Lookup1d(Altitude,AltVec);
Ps2 = LookupValue(k1H,k1L,f1,1,1,1,1,1,1,P0Vec);
Ts2 = LookupValue(k1H,k1L,f1,1,1,1,1,1,1,T0Vec);

%Updates the value of Ts2 by adding dT value
Ts2 = Ts2 + dT;

%Calculates the basic relation for obtaining total pressure and temperature
funcMN = (1 + MN^2 * (gamma-1)/2);

%Calculates total values of temperature and pressure
Tt2 = Ts2 * funcMN;
Pt2 = Ps2 * funcMN^(gamma/(gamma-1));

%Calculates values of theta and delta
Theta = Tt2/288.15;
Delta = Pt2/101325;

end

