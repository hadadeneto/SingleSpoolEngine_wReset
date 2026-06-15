

X = NcFANMtx(1,:);
Y = AMtx(1,:);
Xadd = [0.8 0.75 0.7 0.65 0.6 0.55 0.5];
Yadd = PolyExpand(X,Y,Xadd,2);

plot(X,Y)
hold on
plot(Xadd,Yadd)