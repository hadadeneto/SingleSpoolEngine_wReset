

%-----------------------
%PLOTING OF HIL GRAPHICS
%-----------------------

%Plots the graphics of variables of interest
figure(1)
hold on
plot(t(FirstInst:end),N_HIL(FirstInst:end),'linewidth',2)

% % Plots the Rotation Speed on top of reference if closed-loop
% if (Mode == 2) || (Mode == 4)  
%     plot(t(FirstInst:end),Ref,':','linewidth',1)
%     plot(t(FirstInst:end),FiltRef,'-','linewidth',1)
% end

%Plots the Rotation Speed on top of reference if closed-loop
plot(t(FirstInst:end),RPMRef_HIL(FirstInst:end),':','linewidth',1)
plot(t(FirstInst:end),FiltRef_HIL(FirstInst:end),'-','linewidth',1)

ylabel('N (RPM)','FontSize',24);
xlabel('Time (s)', 'FontSize', 24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off

%Plots the graphics of variables of interest
figure(2)
hold on
plot(t(FirstInst:end),Wf_HIL(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('W_{f} (kg/s)','FontSize',24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off

%Plots the graphics of variables of interest
figure(3)
hold on
plot(t(FirstInst:end),Pt21_HIL(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('P_{t21} (Pa)','FontSize',24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off

% %Plots the graphics of variables of interest
% figure(3)
% hold on
% plot(t(FirstInst:end),Fg_HIL(FirstInst:end),'linewidth',2)
% xlabel('Time (s)', 'FontSize', 24);
% ylabel('F_{g} (N)','FontSize',24);
% grid on
% %text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
% hold off

%Plots the graphics of variables of interest
figure(4)
hold on
plot(t(FirstInst:end),Tt4_HIL(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('T_{t4} (K)','FontSize',24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off

%Plots the graphics of variables of interest
figure(5)
hold on
plot(t(FirstInst:end),Pt3_HIL(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('Pt3 (N/m)','FontSize',24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off


%Plots the graphics of variables of interest
figure(6)
hold on
plot(t(FirstInst:end),WcFAN_HIL(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('W_{cFAN} (kg/s)','FontSize',24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off


    
figure(7)
hold on
for i = 1:length(NcFANMap)
    plot(WcFANMap(i,:),PRFANMap(i,:),'k','linewidth',1)
end
plot(WcFANStall,PRFANStall,'r:','linewidth',1)
plot(WcFANStall,PRFANStallMarg,'y:','linewidth',1)
plot(WcFAN_HIL,PRFAN_HIL,'linewidth',2)
xlabel('W_{2c} (s)', 'FontSize', 24);
ylabel('PR_{Fan} (kg/s)','FontSize',24);
grid on
hold off
    

if(WhichEngine == 2)
    
    figure(8)
    hold on
    for i = 1:length(NcFANMap)
        plot(WcHPCMap(i,:),PRHPCMap(i,:),'k','linewidth',1)
    end
    plot(WcHPCStall,PRHPCStall,'r:','linewidth',1)
    plot(WcHPCStall,PRHPCStallMarg,'y:','linewidth',1)
    plot(WcHPC_HIL,PRHPC_HIL,'linewidth',2)
    xlabel('W_{2c} (s)', 'FontSize', 24);
    ylabel('PR_{HPC} (kg/s)','FontSize',24);
    grid on
    hold off
    
end

%Plots the graphics of variables of interest
figure(9)
hold on
if(EngUnits == 1)
    plot(t(FirstInst:end),Ref(FirstInst:end),'--','linewidth',1)
end
plot(t(FirstInst:end),Fn_HIL(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('F_{n} (N)','FontSize',24);


grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off


%Plots the graphics of variables of interest
figure(10)
hold on
plot(t(FirstInst:end),Pt6_HIL(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('Pt6 (K)','FontSize',24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off

%Plots the graphics of variables of interest
figure(11)
hold on
plot(t(FirstInst:end),Tt5_HIL(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('Tt5 (K)','FontSize',24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off

%Plots the graphics of variables of interest
figure(12)
hold on
plot(t(FirstInst:end),Pt5_HIL(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('Pt5 (Pa)','FontSize',24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off

%Plots the graphics of variables of interest
figure(13)
hold on
plot(t(FirstInst:end),WcHPC_HIL(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('W_{cHPC} (kg/s)','FontSize',24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off

if WhichCont == 2 && WhichEngine == 3
    
    %Plots the graphics of variables of interest
    figure(14)
    hold on
    plot(t(FirstInst:end),QSMCdx_HIL(FirstInst:end),'linewidth',2)
    xlabel('Time (s)', 'FontSize', 24);
    ylabel('d_{x}(k-1) (RPM)','FontSize',24);
    grid on
    %text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
    hold off
    
    %Plots the graphics of variables of interest
    figure(15)
    hold on
    plot(t(FirstInst:end),QSMCdy_HIL(FirstInst:end),'linewidth',2)
    xlabel('Time (s)', 'FontSize', 24);
    ylabel('d_{y}(k) (K)','FontSize',24);
    grid on
    %text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
    hold off
    
        %Plots the graphics of variables of interest
    figure(16)
    hold on
    plot(t(FirstInst:end),QSMCux_HIL(FirstInst:end),'linewidth',2)
    xlabel('Time (s)', 'FontSize', 24);
    ylabel('u_{x}(k) (kg/s)','FontSize',24);
    grid on
    %text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
    hold off
    
    %Plots the graphics of variables of interest
    figure(17)
    hold on
    plot(t(FirstInst:end),QSMCuy_HIL(FirstInst:end),'linewidth',2)
    xlabel('Time (s)', 'FontSize', 24);
    ylabel('u_{y}(k) (kg/s)','FontSize',24);
    grid on
    %text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
    hold off
    
end

%Plots the graphics of variables of interest
figure(18)
hold on
plot(t(FirstInst:end),Active_HIL(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('Active Controller','FontSize',24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off

%Plots the graphics of variables of interest
figure(19)
hold on
plot(t(FirstInst:end),Altitude(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('Altitude (m)','FontSize',24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off

%Plots the graphics of variables of interest
figure(20)
hold on
plot(t(FirstInst:end),MN(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('Mach Number','FontSize',24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off

%Plots the graphics of variables of interest
figure(21)
hold on
plot(t(FirstInst:end),dT(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('dT (K)','FontSize',24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off

%Plots the graphics of variables of interest
figure(22)
hold on
plot(t(FirstInst:end),RU_HIL(FirstInst:end),'linewidth',2)
xlabel('Time (s)', 'FontSize', 24);
ylabel('RU (kg/s/Pa)','FontSize',24);
grid on
%text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
hold off

% %Plots the graphics of variables of interest
% figure(21)
% hold on
% plot(t(FirstInst:end),Ref(FirstInst:end),'linewidth',2)
% xlabel('Time (s)', 'FontSize', 24);
% ylabel('Reference','FontSize',24);
% grid on
% %text(t(FirstInst:end),x, 'Hey, look at this', 'FontSize', 24);
% hold off