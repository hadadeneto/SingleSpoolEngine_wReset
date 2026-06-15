function WfMin = FindWfMin(MNVec,MN,RU,Delta,Theta,Pt3cMtx,WfcMtx)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

%Gets the vector or correced Pt3 values corresponding to current MN
Pt3c1d = get2Dfrom3D(MNVec,Pt3cMtx,MN);
%Gets the vector or correced Wf values corresponding to current MN
Wfc1d = get2Dfrom3D(MNVec,WfcMtx,MN);
%Calculates values of Pt3 vector from Delta and Theta values
Pt31d = Pt3c1d * Delta;
%Finds the minimum fuel flow vector from Pt31d and RU
WfMin1d = Pt31d * RU;
%Finds the fuel flow vector from Wfc1d, Theta and Delta
Wf1d = Wfc1d * sqrt(Theta) * Delta;

%Finds which index indicates the value of Wf is larger or equal the
%WfMin
Indexes = find(Wf1d >= WfMin1d);
IH = Indexes(1);
IL = IH - 1;

%CALCULATES THE POINT OF EQUAL VALUES OF Wf AND WfMin

%Calculates abciss values for calculation of angular coefficients
xH = Pt31d(IH);
xL = Pt31d(IL);
%Calculates y values for calculation of angular coefficients
y1H = WfMin1d(IH);
y1L = WfMin1d(IL);
y2H = Wf1d(IH);
y2L = Wf1d(IL);
%Calculates angular coefficients
m1 = (y1H - y1L)/(xH - xL);
m2 = (y2H - y2L)/(xH - xL);
%Calculates bias values
C1 = y1H - m1 * xH;
C2 = y2H - m2 * xH;

%Calculates the minimum value of Wf
WfMin = (m2 * C1 - m1 * C2)/(m2 - m1);


end

