

%===================================
% FLAG INDICATING GRAPHICS PLOTTING
%===================================

PlotGraphics = 1;

%==========
%INPUT DATA
%==========

%USED SAMPLING TIME
PathTick = [pwd filesep 'SSModelCFunc' filesep 'FADEC_Defines_H'];
FileTick = 'Env_SampTime.h';
TICK = ReadSampleTime(PathTick,FileTick);
% TICK = 200;

%---------------------
%SIMULATION PARAMETERS
%---------------------

%Integration step for model simulation
Tsim = 0.001 * TICK;%20e-3;
%StepTime
%StepTime = 40;
%Simulation Time
DTime = 80;
%Controller sample time
%Tcont = 40e-3;
%Fist array element to be printed in graphics
% 1 -> indicates that the graphics are printed from instant t = 0
% n -> indicates taht the graphics are printed from instnat t = (n-1) * Tsim
FirstInst = 2;

%Maximum number of possible simulated Faults in MATLAB - Must be larger than 
%the number of faults of EngineFaults struct at the file FaultSim_Types.h
NumSimFaults = 52;

%Number of different external engine on-off commands
NumExCom = 3;

%-------------------
%BEARINGS MODEL DATA
%-------------------

%BEARING 1

B1DELTT = [1 100 130];
B1NOOILT = [300 450 573];
B1ERPM = [0 20000 23000];

%BEARING 2

B2DELTT = [1 40 120];
B2NOOILT = [300 400 530];
B2ERPM = [0 20000 23000];

%BEARING 3

B3DELTT = [1 50 110];
B3NOOILT = [300 410 540];
B3ERPM = [0 20000 23000];

%MAXIMUM OIL PUMP RPM
OPRPMMax = 4500;

%BEARING THERMOCOUPLE DYNAMICS

Ad = 0.9048;
Bd = 0.1903;
Cd = -0.5;
Dd = 0;

%INITIAL BEARINGS TEMPERATURES

TBear1Init = 0;
TBear2Init = 0;
TBear3Init = 0;

%----------------------
%ENGINE TO BE SIMULATED
%----------------------

%WhichEngine = 1 -> TJ1200
%WhichEngine = 2 -> TF1200
%WhichEngine = 3 -> GEJ85
%WhichEngine = 4 -> TJ700
%WhichEngine = 5 -> TJ200
%WhichEngine = 6 -> TJ40

WhichEngine = 5;

Mode = 0;           %0 - Automatic; 1 - Manual
LeverMode = 1;      %0 - Manual; 1 - Automatic
HILMode = 1;        %0 - Software in the Loop  1 - Hardware in the Loop
WindMill = 1;       %0 - Direct flight         1 - Windmill simulation
ResetEneable = 0;   %0 - No reset simulation   1 - Eneables reset sim
EngUnits = 1;       %0 - % thrust reference    1 - thurst reference in (N)
ExtFPModel = 0;     %0 - Internal fuel pump model; 1 - External f. p. model
FlightStart = 0;    %0 - Windmill ground start; 1 - Windmill flight start

% %For the fuel pump to be used during HIL mode, the variable HILMode must
% %equal an integer higher than 49
% HILModeMATLAB = 0;
% if HILMode > 0
%     HILModeMATLAB = 50;
% end

%Determines if SIATT flight profile is to be used
UseSIATTProfile = 1; 
%Choses the SIATT xlsx mission name to be used
% Mission_xlsx_name = 'SIATTMissionCol.xlsx'; 

% % Mission_xlsx_name = 'SIATTMission_2.xlsx';
% Mission_xlsx_name = 'SIATTMission_3_WfMatch_ISA_16.xlsx';
% %Choses the considered value of dT for the xlsx mission to be simulated
% dT_xlsx = 16;
% Mission_xlsx_name = 'SIATTMission_3_RPMMatch_ISA_15.xlsx';
%Choses the considered value of dT for the xlsx mission to be simulated
% dT_xlsx = 15;
%Runs response test mission
% Mission_xlsx_name = 'Mission_TJ1000_ResponseTest.xlsx';
% Mission_xlsx_name = 'FlightStartSim.xlsx';
dT_xlsx = 13.41647;

% Mission_xlsx_name = 'SIATTMission_2_RPMMatch.xlsx';
% %Choses the considered value of dT for the xlsx mission to be simulated
% dT_xlsx = 16;

Mission_xlsx_name = 'SIATTMission_3.xlsx'; 
% Mission_xlsx_name = 'SIATTMission_3_RPMMatch.xlsx';


%---------------------------------
% WINDMILL MACH SPEED FOR STARTING
%---------------------------------

Mwm = 0.35;

%----------------------
% USED CONTROL LAW
%----------------------

%For GEJ85
%Min Max with PI and Reference Filter -> 1
%Min Max with QSMC and Reference Filter -> 2
%Min Max with PI and Acceleration Control -> 3

%For TJ1200 - Must be option 2 for now!!
%1 - Old FADEC (research) that must be excluded
%2 - Current FADEC (test bench)

WhichCont = 2;

%-------------------------------------------------------
%INITIATES THE FLAG INDICATING SOFTWARE FAULT SIMULATION
%-------------------------------------------------------

TCFaultSoftSim = 0;

%--------------------------------
%DEFINITION OF SIMULATION VECTORS
%--------------------------------

% Input Keys for software in the loop simulation (MATLAB bit position)
% 
%   bit 1 = 1 - Igniter		
% 	bit 2 = 1 - Shut_Off	 
% 	bit 3 = 0 - Scaveng		
% 	bit 4 = 1 - Oil Pump	
% 	bit 5 = 0 - AC_Drive	
% 	bit 6 = 1 - Emergency	
% 	bit 7 = 0 - Mode
% 
%   Word: (bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1 | bit 0)
%   Word for MATLAB: (bit 7 | bit 6 | bit 5 | bit 4 | bit 3 | bit 2 | bit 1)

%Digital keys word
DigKeys = bin2dec('0101011');
%DigKeys = bin2dec('0111011');
      
%===============     
% ENGINE SETUP
%===============

if WhichEngine == 1
    
    %     AltVecDyn = 12000*ones(1,6);
    AltVecDyn = 567*ones(1,6);
    %     AltVecDyn = 000*ones(1,12);
    %     AltVecDyn = 000*ones(1,6);
    %     MNVecDyn = 0.75*ones(1,6);
    MNVecDyn = 0*ones(1,6);
    %     %dTVecDyn = 15*ones(1,6);
    %     dTVecDyn = 39*ones(1,6);
    %     dTVecDyn = 0 * ones(1,6);
    %     dTVecDyn = 1.1535e+01 * ones(1,6);
    dTVecDyn = 18 * ones(1,6);
    %     dTVecDyn = (1.1535e+01 - .999665) * ones(1,6);
%         dTVecDyn = 0 * ones(1,6);
    %     dTVecDyn = 000*ones(1,12);
    
    TimeVector = [0 5 5.01 9.99 10.01 15];
    TimeVector = [0 5 5.01 14.99 15.01 25];
    TimeVector = [0 5 5.01 14.99 15.01 80];
    
    
    %     TimeVector = [0 5 5.01 9.99 10.01 15 160 165 165.01 169.99 170.01 175];
    %RefVecDyn = [0.35 0.35 1 1 0.35 0.35];
    RefVecDyn = [0.45 0.45 1 1 0.45 0.45];
    %     RefVecDyn = [0 0 0 0 0 0];
    %     RefVecDyn = [0.45 0.45 1 1 1 1];
    
    if EngUnits
        TimeVector = [0 5 5.01 14.99 15.01 65];
        TimeVector = [0 45 45.01 54.99 55.01 105];
        RefVecDyn = [793 793 1770 1770 793 793];
        RefVecDyn = [0.45 0.45 1 1 0.45 0.45];
        RefVecDyn = [3000 3000 4000 4000 3000 3000]/5;
        RefVecDyn = 1455 * ones(1,6);
        %         RefVecDyn = [3000 3000 3000 3000 3000 3000];
        %         RefVecDyn = [2860 2860 3737 3737 2860 2860];
        %         RefVecDyn = [2000 2000 3780 3780 2000 2000];
        %         RefVecDyn = [0 0 0 0 0 0];
        %         RefVecDyn = [2000 2000 2500 2500 3000 3000];
        RefVecDyn = [0 0 2500 2500 3000 3000];
        RefVecDyn = [0 0 2500 2500 6000 6000];
        
        AltVecDyn = 567 * ones(1,6);
        MNVecDyn = 0 * ones(1,6);
        dTVecDyn = 0 * ones(1,6);
        TimeVector = [0 45 45.01 55 55.02 105];
        RefVecDyn = [1500 1500 1500 1500 4280 4280];
        RefVecDyn = [2000 2000 2000 2000 4500 4500];
%         RefVecDyn = [0 0 0 0 0 0];
        
        if LeverMode == 0
            RefVecDyn = [0.016 0.016 0.016 0.016 0.016 0.016];
        end
%         RefVecDyn = [1500 1500 1500 1500 4000 4000];

%         RefVecDyn = [0 0 1500 1500 1500 1500];
        %RefVecDyn = 3300 * ones(1,6);
        %         RefVecDyn = [1500 1500 1500 1500 1500 1500];
        %         RefVecDyn = [1500 1500 4500 4500 4500 4500];
        %         RefVecDyn = [4000 4000 2212 2212 2212 2212];
        %         RefVecDyn = [0 0 0 0 0 0];
        %         RefVecDyn = [3000 3000 3000 0 0 0];
        %Reads SIATTProfile
        
        %On-Flight Starting mission
%         Mission_xlsx_name = 'TJ1000_In_Flight_Start.xlsx';
%         dT_xlsx = 0;
        
        if UseSIATTProfile == 1
%             SIATTProfile;
            [AltVecDyn,MNVecDyn,RefVecDyn,dTVecDyn,TimeVector] = Read_xlsx_Mission(Mission_xlsx_name,dT_xlsx);
%             dTVecDyn = dTVecDyn + 3;
        end
        
    end
    
    %     TimeVector = [0 5 5.01 9.99 10.01 15 160 165 165.01 169.99 170.01 175];
    
    %Initiates the time vector for faults
    
    %     SensFaultStartTime = (TimeVector(end) + 1) * ones(1,NumSimFaults)';
    %     SensFaultStopTime = (TimeVector(end) + 2) * ones(1,NumSimFaults)';
    %
    %     SysFaultStartTime = (TimeVector(end) + 1) * ones(1,NumSimFaults)';
    %     SysFaultStopTime = (TimeVector(end) + 2) * ones(1,NumSimFaults)';
    %
    %     TimeVecEndInit = TimeVector(end);
    
    %Indicates the instant of each desired fault
    
    
end

if WhichEngine == 2
    
    AltVecDyn = 000*ones(1,6);
    MNVecDyn = 000*ones(1,6);
    dTVecDyn = 000*ones(1,6);
    TimeVector = [0 45 45.01 54.99 55.01 65] - 40 * (1 - WindMill);
    RefVecDyn = [0.45 0.45 1 1 0.45 0.45];
    RefVecDyn = [0.5 0.5 1 1 0.5 0.5];
    RefVecDyn = [2000 2000 3000 3000 2000 2000];
%     RefVecDyn = [3000 3000 3000 3000 3000 3000];
    
    
    %Reads SIATTProfile
    if UseSIATTProfile == 1
        %             SIATTProfile;
        [AltVecDyn,MNVecDyn,RefVecDyn,dTVecDyn,TimeVector] = Read_xlsx_Mission(Mission_xlsx_name,dT_xlsx);
        %             dTVecDyn = dTVecDyn + 3;
    end
    %     RefVecDyn = [0.057487658299191 0.057487658299191 0.089996843373837 0.089996843373837 0.057487658299191 0.057487658299191];
    
    %Initiates the time vector for faults
        
%     SensFaultStartTime = (TimeVector(end) + 1) * ones(1,NumSimFaults)';
%     SensFaultStopTime = (TimeVector(end) + 2) * ones(1,NumSimFaults)';
%     
%     SysFaultStartTime = (TimeVector(end) + 1) * ones(1,NumSimFaults)';
%     SysFaultStopTime = (TimeVector(end) + 2) * ones(1,NumSimFaults)';
%    
%     TimeVecEndInit = TimeVector(end);
    
    %Indicates the instant of each desired fault
    
end

if WhichEngine == 3
    
    AltVecDyn = 2000*ones(1,6);
    MNVecDyn = .65000*ones(1,6);
    AltVecDyn = 0000*ones(1,6);
    MNVecDyn = 000*ones(1,6);
    dTVecDyn = 000*ones(1,6);
    TimeVector = [0 5 5.01 9.99 10.01 15];
    RefVecDyn = [0.43 0.43 1 1 0.43 0.43];
    RefVecDyn = [9000 9000 12000 12000 9000 9000];
    %     RefVecDyn = ones(1,6);
    %     TimeVector = [0 0.1 0.2 0.3 0.32 20];
    %
    
    %TEST FOR OBTAINING Nc VECTOR
    
    %     AltVecDyn = 00*ones(1,4);
    %     MNVecDyn = 000*ones(1,4);
    %     AltVecDyn = 0000*ones(1,4);
    %     MNVecDyn = 000*ones(1,4);
    %     dTVecDyn = 000*ones(1,4);
    %     TimeVector = [0 5 5.01 9.99];
    %     RefVecDyn = [2.4417e-01*ones(1,2) .39*ones(1,2)];
    
    %Initiates the time vector for faults
    
%     SensFaultStartTime = (TimeVector(end) + 1) * ones(1,NumSimFaults)';
%     SensFaultStopTime = (TimeVector(end) + 2) * ones(1,NumSimFaults)';
%     
%     SysFaultStartTime = (TimeVector(end) + 1) * ones(1,NumSimFaults)';
%     SysFaultStopTime = (TimeVector(end) + 2) * ones(1,NumSimFaults)';
%    
%     TimeVecEndInit = TimeVector(end);
    
    %Indicates the instant of each desired fault
    
        %Reads SIATTProfile
    if UseSIATTProfile == 1
        
        Mission_xlsx_name = 'Mission_GEJ85_ResponseTest.xlsx';
        %             dT_xlsx = 13.41647;
        dT_xlsx = 0;
        %             SIATTProfile;
        [AltVecDyn,MNVecDyn,RefVecDyn,dTVecDyn,TimeVector] = Read_xlsx_Mission(Mission_xlsx_name,dT_xlsx);
        %             dTVecDyn = dTVecDyn + 3;
    end
    
end

%TJ700 ENGINE

if WhichEngine == 4
    
    %     AltVecDyn = 12000*ones(1,6);
    AltVecDyn = 567*ones(1,6);
    %     AltVecDyn = 000*ones(1,12);
    %     AltVecDyn = 000*ones(1,6);
    %     MNVecDyn = 0.75*ones(1,6);
    MNVecDyn = 0*ones(1,6);
    %     %dTVecDyn = 15*ones(1,6);
    %     dTVecDyn = 39*ones(1,6);
    %     dTVecDyn = 0 * ones(1,6);
    %     dTVecDyn = 1.1535e+01 * ones(1,6);
    dTVecDyn = 18 * ones(1,6);
    %     dTVecDyn = (1.1535e+01 - .999665) * ones(1,6);
%         dTVecDyn = 0 * ones(1,6);
    %     dTVecDyn = 000*ones(1,12);
    
    TimeVector = [0 5 5.01 9.99 10.01 15];
    TimeVector = [0 5 5.01 14.99 15.01 25];
    TimeVector = [0 5 5.01 14.99 15.01 80];
    
    
    %     TimeVector = [0 5 5.01 9.99 10.01 15 160 165 165.01 169.99 170.01 175];
    %RefVecDyn = [0.35 0.35 1 1 0.35 0.35];
    RefVecDyn = [0.45 0.45 1 1 0.45 0.45];
    %     RefVecDyn = [0 0 0 0 0 0];
    %     RefVecDyn = [0.45 0.45 1 1 1 1];
    
    if EngUnits
        TimeVector = [0 5 5.01 14.99 15.01 65];
        TimeVector = [0 45 45.01 54.99 55.01 105];
        RefVecDyn = [793 793 1770 1770 793 793];
        RefVecDyn = [0.45 0.45 1 1 0.45 0.45];
        RefVecDyn = [3000 3000 4000 4000 3000 3000]/5;
        RefVecDyn = 1455 * ones(1,6);
        %         RefVecDyn = [3000 3000 3000 3000 3000 3000];
        %         RefVecDyn = [2860 2860 3737 3737 2860 2860];
        %         RefVecDyn = [2000 2000 3780 3780 2000 2000];
        %         RefVecDyn = [0 0 0 0 0 0];
        %         RefVecDyn = [2000 2000 2500 2500 3000 3000];
        RefVecDyn = [0 0 2500 2500 3000 3000];
        RefVecDyn = [0 0 2500 2500 6000 6000];
        
        AltVecDyn = 0 * ones(1,6);
        MNVecDyn = 0 * ones(1,6);
        dTVecDyn = 0 * ones(1,6);
        TimeVector = [0 45 45.01 55 55.02 105];
        RefVecDyn = [1500 1500 1500 1500 4280 4280];
        
        if LeverMode == 0
            RefVecDyn = [0.016 0.016 0.016 0.016 0.016 0.016];
        end
%         RefVecDyn = [1500 1500 1500 1500 4000 4000];

%         RefVecDyn = [0 0 1500 1500 1500 1500];
        %RefVecDyn = 3300 * ones(1,6);
        %         RefVecDyn = [1500 1500 1500 1500 1500 1500];
        %         RefVecDyn = [1500 1500 4500 4500 4500 4500];
        %         RefVecDyn = [4000 4000 2212 2212 2212 2212];
        %         RefVecDyn = [0 0 0 0 0 0];
        %         RefVecDyn = [3000 3000 3000 0 0 0];
        %Reads SIATTProfile
        if UseSIATTProfile == 1
%             SIATTProfile;
            [AltVecDyn,MNVecDyn,RefVecDyn,dTVecDyn,TimeVector] = Read_xlsx_Mission(Mission_xlsx_name,dT_xlsx);
%             dTVecDyn = dTVecDyn + 3;
        end
        
    end
     
end

%TJ700 ENGINE

if WhichEngine == 5
    
    %     AltVecDyn = 12000*ones(1,6);
    AltVecDyn = 567*ones(1,6);
    %     AltVecDyn = 000*ones(1,12);
    %     AltVecDyn = 000*ones(1,6);
    %     MNVecDyn = 0.75*ones(1,6);
    MNVecDyn = 0*ones(1,6);
    %     %dTVecDyn = 15*ones(1,6);
    %     dTVecDyn = 39*ones(1,6);
    %     dTVecDyn = 0 * ones(1,6);
    %     dTVecDyn = 1.1535e+01 * ones(1,6);
    dTVecDyn = 18 * ones(1,6);
    %     dTVecDyn = (1.1535e+01 - .999665) * ones(1,6);
%         dTVecDyn = 0 * ones(1,6);
    %     dTVecDyn = 000*ones(1,12);
    
    TimeVector = [0 5 5.01 9.99 10.01 15];
    TimeVector = [0 5 5.01 14.99 15.01 25];
    TimeVector = [0 5 5.01 14.99 15.01 80];
    
    
    %     TimeVector = [0 5 5.01 9.99 10.01 15 160 165 165.01 169.99 170.01 175];
    %RefVecDyn = [0.35 0.35 1 1 0.35 0.35];
    RefVecDyn = [0.45 0.45 1 1 0.45 0.45];
    %     RefVecDyn = [0 0 0 0 0 0];
    %     RefVecDyn = [0.45 0.45 1 1 1 1];
    
    if EngUnits
        TimeVector = [0 5 5.01 14.99 15.01 65];
        TimeVector = [0 45 45.01 54.99 55.01 105];
        RefVecDyn = [793 793 1770 1770 793 793];
        RefVecDyn = [0.45 0.45 1 1 0.45 0.45];
        RefVecDyn = [3000 3000 4000 4000 3000 3000]/5;
        RefVecDyn = 1455 * ones(1,6);
        %         RefVecDyn = [3000 3000 3000 3000 3000 3000];
        %         RefVecDyn = [2860 2860 3737 3737 2860 2860];
        %         RefVecDyn = [2000 2000 3780 3780 2000 2000];
        %         RefVecDyn = [0 0 0 0 0 0];
        %         RefVecDyn = [2000 2000 2500 2500 3000 3000];
        RefVecDyn = [0 0 2500 2500 3000 3000];
        RefVecDyn = [0 0 2500 2500 6000 6000];
        
        AltVecDyn = 0 * ones(1,6);
        MNVecDyn = 0 * ones(1,6);
        dTVecDyn = 0 * ones(1,6);
        TimeVector = [0 45 45.01 55 55.02 105];
        RefVecDyn = [1500 1500 1500 1500 4280 4280];
        
        if LeverMode == 0
            RefVecDyn = [0.016 0.016 0.016 0.016 0.016 0.016];
        end
%         RefVecDyn = [1500 1500 1500 1500 4000 4000];

%         RefVecDyn = [0 0 1500 1500 1500 1500];
        %RefVecDyn = 3300 * ones(1,6);
        %         RefVecDyn = [1500 1500 1500 1500 1500 1500];
        %         RefVecDyn = [1500 1500 4500 4500 4500 4500];
        %         RefVecDyn = [4000 4000 2212 2212 2212 2212];
        %         RefVecDyn = [0 0 0 0 0 0];
        %         RefVecDyn = [3000 3000 3000 0 0 0];
        %Reads SIATTProfile
        if UseSIATTProfile == 1
            Mission_xlsx_name = 'Mission_TJ200_ResponseTest.xlsx';
%             dT_xlsx = 13.41647;
            dT_xlsx = 14;
%             SIATTProfile;
            [AltVecDyn,MNVecDyn,RefVecDyn,dTVecDyn,TimeVector] = Read_xlsx_Mission(Mission_xlsx_name,dT_xlsx);
%             dTVecDyn = dTVecDyn + 3;
        end
        
    end
     
end

%TJ40 ENGINE

if WhichEngine == 6
    
    %     AltVecDyn = 12000*ones(1,6);
    AltVecDyn = 567*ones(1,6);
    %     AltVecDyn = 000*ones(1,12);
    %     AltVecDyn = 000*ones(1,6);
    %     MNVecDyn = 0.75*ones(1,6);
    MNVecDyn = 0*ones(1,6);
    %     %dTVecDyn = 15*ones(1,6);
    %     dTVecDyn = 39*ones(1,6);
    %     dTVecDyn = 0 * ones(1,6);
    %     dTVecDyn = 1.1535e+01 * ones(1,6);
    dTVecDyn = 18 * ones(1,6);
    %     dTVecDyn = (1.1535e+01 - .999665) * ones(1,6);
%         dTVecDyn = 0 * ones(1,6);
    %     dTVecDyn = 000*ones(1,12);
    
    TimeVector = [0 5 5.01 9.99 10.01 15];
    TimeVector = [0 5 5.01 14.99 15.01 25];
    TimeVector = [0 5 5.01 14.99 15.01 80];
    
    
    %     TimeVector = [0 5 5.01 9.99 10.01 15 160 165 165.01 169.99 170.01 175];
    %RefVecDyn = [0.35 0.35 1 1 0.35 0.35];
    RefVecDyn = [0.45 0.45 1 1 0.45 0.45];
    %     RefVecDyn = [0 0 0 0 0 0];
    %     RefVecDyn = [0.45 0.45 1 1 1 1];
    
    if EngUnits
        
        AltVecDyn = 0 * ones(1,6);
        MNVecDyn = 0 * ones(1,6);
        dTVecDyn = 0 * ones(1,6);
        TimeVector = [0 45 45.01 55 55.02 105];
        RefVecDyn = [150 150 150 150 400 400];
        
        if LeverMode == 0
            RefVecDyn = [0.016 0.016 0.016 0.016 0.016 0.016];
        end
%         RefVecDyn = [1500 1500 1500 1500 4000 4000];

%         RefVecDyn = [0 0 1500 1500 1500 1500];
        %RefVecDyn = 3300 * ones(1,6);
        %         RefVecDyn = [1500 1500 1500 1500 1500 1500];
        %         RefVecDyn = [1500 1500 4500 4500 4500 4500];
        %         RefVecDyn = [4000 4000 2212 2212 2212 2212];
        %         RefVecDyn = [0 0 0 0 0 0];
        %         RefVecDyn = [3000 3000 3000 0 0 0];
        %Reads SIATTProfile
        if UseSIATTProfile == 1
            Mission_xlsx_name = 'Mission_TJ40_ResponseTest.xlsx';
%             dT_xlsx = 13.41647;
            dT_xlsx = 0;
%             SIATTProfile;
            [AltVecDyn,MNVecDyn,RefVecDyn,dTVecDyn,TimeVector] = Read_xlsx_Mission(Mission_xlsx_name,dT_xlsx);
%             dTVecDyn = dTVecDyn + 3;
        end
        
    end
     
end

%==================
% FAULT SIMULATION
%==================

%Initiates the time vector for faults

SensFaultStartTime = (TimeVector(end) + 1) * ones(1,NumSimFaults)';
SensFaultStopTime = (TimeVector(end) + 2) * ones(1,NumSimFaults)';

SysFaultStartTime = (TimeVector(end) + 1) * ones(1,NumSimFaults)';
SysFaultStopTime = (TimeVector(end) + 2) * ones(1,NumSimFaults)';

ExComTime = (TimeVector(end) + 1) * ones(1,NumExCom)';

TimeVecEndInit = TimeVector(end);

% Below, the tables and vectors setup for fault simulations

%---------------------
% SENSOR FAULTS TABLE
%---------------------

%MATLAB Bit - Fault

%Ts2                             %RPM

%  1 - Ts2_0 SCV                 %18 - RPM_0 Short
%  2 - Ts2_0 SCG                 %19 - RPM_0 Open
%  3 - Ts2_0 Open                %20 - RPM_0 1 Pulse Loss
                                 %21 - RPM_0 2 Pulse Loss
%  4 - Ts2_1 SCV
%  5 - Ts2_1 SCG
%  6 - Ts2_1 Open                %22 - RPM_1 Short
                                 %23 - RPM_1 Open
%Pt3                             %24 - RPM_1 1 Pulse Loss
                                 %25 - RPM_1 2 Pulse Loss
%  7 - Pt3_0 Short
%  8 - Pt3_0 Open
                                 %POil
%Tt4
                                 %26 - POil_0 Short
%  9 - Tt4_0 SCV                 %27 - POil_0 Open
% 10 - Tt4_0 SCG
% 11 - Tt4_0 Open                %PFuel

% 12 - Tt4_1 SCV                 %28 - PFuel_0 Short
% 13 - Tt4_1 SCG                 %29 - PFuel_0 Open
% 14 - Tt4_1 Open
                                %Vibration
% 15 - Tt4_2 SCV
% 16 - Tt4_2 SCG                %30 - Vibration_0 Short
% 17 - Tt4_2 Open               %31 - Vibration_0 Open

                                %Bearings
                                
                                %32 - TBear_0 Open
                                %33 - TBear_1 Open
                                %34 - TBear_2_Open

%------------
% BIAS TABLE
%------------

%Ts2                            %RPM

%1 - Ts2 0 bias                %7 - RPM 0 bias
%2 - Ts2 1 bias                %8 - RPM 1 bias

%Ps3                            %POil

%3 - Pt3 0 bias                %9 - POil bias

%Tt4                            %PFuel

%4 - Tt4 0 bias                %10 - PFuel bias
%5 - Tt4 1 bias
%6 - Tt4 2 bias                %Vibration

                               %11 - Vib bias
                               
                               %Bearings
                               
                               %12 - TB0 bias
                               %13 - TB1 bias
                               %14 - TB2 bias

%--------------------
% SYSTEM FAULT TABLE
%--------------------

%MATLAB Bit - Fault

%Lub System                     %Mec System

%15 - POil High                 %19 - Blow Out
%16 - POil Low                  %20 - Vibration High
                                %21 - Shaft Lock
%Fuel System                    %22 - OverTemp
                                %23 - OverSpeed
%17 - PFuel High                %24 - Ignition
%18 - PFuel Low                 %25 - TB0 High
                                %26 - TB1 High
                                %27 - TB2 High
                                %28 - CAN 0 Fault
                                %29 - CAN 1 Communication
                                %30 - Emergency Shut Down
                                %31 - Nominal Shut Down

%-----------------
%VECTOR INDICATION
%-----------------

%For simulating system fault, the position of the array FaultStartTime
%corresponding to the fault bit must be set to the value of the instant
%where the fault occurs.
%For the fault to stop happeining in the simulator, the position of
%the array FaultStopTime corresponding to the fault bit must be set to
%the value where the fault needs to stop occuring.
%Also, the variable TCFaultSoftSim must be set to 1 in order for
%thermocouple fault to be simulated via software in the FADEC

%Eneables simulation of TC fauts via software
TCFaultSoftSim = 1;

%---------------
% SENSOR FAULTS
%---------------

%     SensFaultStartTime(1) = 20;             %SensFaultStopTime(1) = 24;
%     SensFaultStartTime(2) = 20;             %SensFaultStopTime(2) = 24;
%     SensFaultStartTime(3) = 20;             %SensFaultStopTime(3) = 24;
%     SensFaultStartTime(4) = 20;             %SensFaultStopTime(4) = 24;
%     SensFaultStartTime(5) = 20;             %SensFaultStopTime(5) = 24;
%     SensFaultStartTime(6) = 20;             %SensFaultStopTime(6) = 24;
%     SensFaultStartTime(7) = 20;             %SensFaultStopTime(7) = 24;
%     SensFaultStartTime(8) = 20;             %SensFaultStopTime(8) = 24;
%     SensFaultStartTime(9) = 20;             %SensFaultStopTime(9) = 24;
%     SensFaultStartTime(10) = 20;            %SensFaultStopTime(10) = 24;
%     SensFaultStartTime(11) = 20;            %SensFaultStopTime(11) = 24;
%     SensFaultStartTime(12) = 20;            %SensFaultStopTime(12) = 24;
%     SensFaultStartTime(13) = 20;            %SensFaultStopTime(13) = 24;
%     SensFaultStartTime(14) = 20;            %SensFaultStopTime(14) = 24;
%     SensFaultStartTime(15) = 20;            %SensFaultStopTime(15) = 24;
%     SensFaultStartTime(16) = 20;            %SensFaultStopTime(16) = 24;
%     SensFaultStartTime(17) = 20;            %SensFaultStopTime(17) = 24;
%     SensFaultStartTime(18) = 20;            %SensFaultStopTime(18) = 24;
%     SensFaultStartTime(19) = 20;            %SensFaultStopTime(19) = 24;
%     SensFaultStartTime(20) = 20;            %SensFaultStopTime(20) = 24;
%     SensFaultStartTime(21) = 20;            %SensFaultStopTime(21) = 24;
%     SensFaultStartTime(22) = 20;            %SensFaultStopTime(22) = 24;
%     SensFaultStartTime(23) = 20;            %SensFaultStopTime(23) = 24;
%     SensFaultStartTime(24) = 20;            %SensFaultStopTime(24) = 24;
%     SensFaultStartTime(25) = 20;            %SensFaultStopTime(25) = 24;
%     SensFaultStartTime(26) = 20;            %SensFaultStopTime(26) = 24;
%     SensFaultStartTime(27) = 20;            %SensFaultStopTime(27) = 24;
%     SensFaultStartTime(28) = 20;            %SensFaultStopTime(28) = 24;
%     SensFaultStartTime(29) = 20;            %SensFaultStopTime(29) = 26;
%     SensFaultStartTime(30) = 20;            %SensFaultStopTime(30) = 24;
%     SensFaultStartTime(31) = 20;            %SensFaultStopTime(31) = 24;
%     SensFaultStartTime(32) = 20;            %SensFaultStopTime(29) = 26;
%     SensFaultStartTime(33) = 20;            %SensFaultStopTime(30) = 24;
%     SensFaultStartTime(34) = 20;            %SensFaultStopTime(31) = 24;

%-------------
% BIAS FAULTS
%-------------

%     SysFaultStartTime(1) = 90;            %SysFaultStopTime(1) = 24;
%     SysFaultStartTime(2) = 100;%-200;            %SysFaultStopTime(2) = 24;
%     SysFaultStartTime(3) = 20;            %SysFaultStopTime(3) = 24;
%     SysFaultStartTime(4) = -65;            SysFaultStopTime(4) = -57;
%     SysFaultStartTime(5) = -65;            SysFaultStopTime(5) = -57;
%     SysFaultStartTime(6) = -65;            SysFaultStopTime(6) = -57;
%     SysFaultStartTime(7) = 20;            %SysFaultStopTime(7) = 24;
%     SysFaultStartTime(8) = 20;            %SysFaultStopTime(8) = 24;
%     SysFaultStartTime(9) = 20;            %SysFaultStopTime(9) = 24;
%     SysFaultStartTime(10) = 20;           %SysFaultStopTime(10) = 24;
%     SysFaultStartTime(11) = 20;           %SysFaultStopTime(11) = 24;
%     SysFaultStartTime(12) = 20;            %SysFaultStopTime(12) = 24;
%     SysFaultStartTime(13) = 20;            %SysFaultStopTime(13) = 24;
%     SysFaultStartTime(14) = 20;            %SysFaultStopTime(14) = 24;

%---------------
% SYSTEM FAULTS
%---------------

%     SysFaultStartTime(15) = 90;            %SysFaultStopTime(15) = 24;
%     SysFaultStartTime(16) = 40;            %SysFaultStopTime(16) = 24;
%     SysFaultStartTime(17) = 20;            %SysFaultStopTime(17) = 24;
%     SysFaultStartTime(18) = 20;            %SysFaultStopTime(18) = 24;
%     SysFaultStartTime(19) = 40;            %SysFaultStopTime(19) = 24;
%     SysFaultStartTime(20) = 20;            %SysFaultStopTime(20) = 24;
%     SysFaultStartTime(21) = -79;            %SysFaultStopTime(21) = 24;
%     SysFaultStartTime(22) = -70;            SysFaultStopTime(22) = -68;
%     SysFaultStartTime(23) = 20;            %SysFaultStopTime(23) = 21;
%     SysFaultStartTime(24) = -200;            %SysFaultStopTime(24) = 24;
%     SysFaultStartTime(25) = 20;            %SysFaultStopTime(25) = 24;
%     SysFaultStartTime(26) = 20;            %SysFaultStopTime(26) = 24;
%     SysFaultStartTime(27) = 20;            %SysFaultStopTime(27) = 24;
%     SysFaultStartTime(28) = 21;            %SysFaultStopTime(28) = 42;
%     SysFaultStartTime(29) = 20;            %SysFaultStopTime(29) = 21;
%     SysFaultStartTime(30) = 20;            %SysFaultStopTime(30) = 21;
%     SysFaultStartTime(31) = 20;            %SysFaultStopTime(31) = 21;

%Bias levels

%1 - Ts2 0       2 - Ts2 1        3 - Pt3 0
%4 - Tt4 0       5 - Tt4 1        6 - Tt4 2
%7 - RPM 0       8 - RPM 1        9 - POil 0
%10 - PFuel 0       11 - Vib 0

BiasSens(1) = 0;%60;
BiasSens(2) = 40;%1;%40;
BiasSens(3) = 3 * 100000;
BiasSens(4) = -450;
BiasSens(5) = -450;
BiasSens(6) = -450;
BiasSens(7) = 3000;
BiasSens(8) = 3000;
BiasSens(9) = 1.5 * 100000;
BiasSens(10) = 30 * 100000;
BiasSens(11) = 2;
BiasSens(12) = 100;
BiasSens(13) = 150;
BiasSens(14) = 150;
       
%==================     
% EXTERNAL COMMAND
%==================

% EXTERNAL COMMAND VALUES

% 0X00 = Emergency
% 0XAA = Engine Start
% 0XCC = Engine Nominal Shut Down

% BIT POSITION

% 1 = Engine Start
% 2 = Engine Nominal Shut Down
% 3 = Emergency

% EXTERNAL COMMAND TIME VECTOR

ExComTime(1) = -40;%-200;%-10;%-200; %Engine Start
% ExComTime(1) = 10000; %For testing of windmillig new model
% ExComTime(2) = 70; %Engine Nominal Shut Down
% ExComTime(3) = 20; %Emergency

%External command vector
ExComVec = [hex2dec('AA'), hex2dec('00'), hex2dec('CC')];

% BOOSTERS STATUS

BoosterLStatusTime(1) = -200;%-10;%-200; %Engaged
BoosterLStatusTime(2) = 110; %Released
BoosterLStatusTime(3) = 200;%-10;%-200; %No action

BoosterRStatusTime(1) = -200;%-10;%-200; %Engaged
BoosterRStatusTime(2) = 120; %Released
BoosterRStatusTime(3) = 200;%-10;%-200; %No action


%External command vector
BoosterVec = [hex2dec('55'), hex2dec('AA') hex2dec('FF')];



% % FuelVecDyn = [0.0646 0.0646 0.09 0.09 0.0646 0.0646];%[0.31999 0.31999 0.32 0.32 0.31999 0.31999];
% FuelVecDyn = [0.0646 0.0646 0.09 0.09 0.0646 0.0646 0.0646 0.0646 0.09 0.09 0.0646 0.0646];
% %FuelVecDyn = [0.0374 0.0374 0.07 0.07 0.0374 0.0374];
% % FuelVecDyn = [0.008 0.008 0.013 0.013 0.008 0.008];


%====================================================
%PARAMETERS LOADING, SIMULATION AND GRAPHICS PLOTTING
%====================================================


%--------------------------
%CORRECTION OF TIME VECTORS
%--------------------------

%Adjusts the value of simulation final time
% DTime = FinalTime - TimeVector(end);
% TimeVector = TimeVector + DTime;

%Adjusts the input vectors case windmill starting simulation is required
if WindMill
    TimeVector = TimeVector + DTime;
    TimeVector = [0 Tsim 2*Tsim 3*Tsim TimeVector];
    RefVecDyn = [0 0 RefVecDyn(1) RefVecDyn(1) RefVecDyn];
    AltVecDyn = [AltVecDyn(1) * ones(1,4) AltVecDyn];
    MNVecDyn = [MNVecDyn(1) * ones(1,4) MNVecDyn];
    dTVecDyn = [dTVecDyn(1) * ones(1,4) dTVecDyn];
end

%Reset input vector
ResetInput = zeros(1,length(TimeVector));
ResetTime = TimeVector(end) + Tsim;

if ResetEneable
    
    DTime = TimeVector(end) + Tsim;
    
    %Computes second part of vectors
    TimeVectorSec = TimeVector + DTime + Tsim;
    RefVecSec = RefVecDyn;
    AltVecSec = AltVecDyn;
    MNVecSec = MNVecDyn;
    dTVecSec = dTVecDyn;
    ResetSec = ones(1,length(RefVecDyn));
    
    %Adds extra element to input vectors
    RefVecDyn = [RefVecDyn RefVecDyn(1)];
    AltVecDyn = [AltVecDyn AltVecDyn(1)];
    MNVecDyn = [MNVecDyn MNVecDyn(1)];
    dTVecDyn = [dTVecDyn dTVecDyn(1)];
    TimeVector = [TimeVector DTime];
    ResetInput = [ResetInput 0];
    
    %Completes input vectors with the respective original vectors
    RefVecDyn = [RefVecDyn RefVecSec];
    AltVecDyn = [AltVecDyn AltVecSec];
    MNVecDyn = [MNVecDyn MNVecSec];
    dTVecDyn = [dTVecDyn dTVecSec];
    TimeVector = [TimeVector TimeVectorSec];
    ResetInput = [ResetInput ResetSec];
    
    %Adds correction to start command in order for a reset to be properly
    %simlated
%     ExComTime(1) = ExComTime(1) - DeltaTimeEnd;
    
    
end

%Correction of Fault Time Vector
DeltaTimeEnd = TimeVector(end) - TimeVecEndInit;
% FaultStartTime = FaultStartTime + DeltaTimeEnd;
% FaultStopTime = FaultStopTime + DeltaTimeEnd;

SensFaultStartTime = SensFaultStartTime + DeltaTimeEnd;
SensFaultStopTime = SensFaultStopTime + DeltaTimeEnd;

SysFaultStartTime = SysFaultStartTime + DeltaTimeEnd;
SysFaultStopTime = SysFaultStopTime + DeltaTimeEnd;

ExComTime = ExComTime + DeltaTimeEnd;

% BiasFaultStartTime = BiasFaultStartTime + DeltaTimeEnd;
% BiasFaultStopTime = BiasFaultStopTime + DeltaTimeEnd;

%Shut Off command by SIATT Profile
if UseSIATTProfile == 1
    SIATTShutOff;
end

%----------------------------
%LOADING OF ENGINE PARAMETERS
%----------------------------

%Loads TJ1200 Parameters
switch WhichEngine
    case 1
        LoadTJ1200
    case 2
        LoadTF1200
    case 3
        LoadGEJ85
    case 4
        LoadTJ700
    case 5
        LoadTJ200
    case 6
        LoadTJ40
end

%----------
%SIMULATON
%----------

%Compiles C code for PI controller
%CompileCSFun

%Executes clear mex command for debugging in external tool
clear mex

%Verifies the MATLAB version running
VYear = WhichVersion;

%Opens the model according to MATLAB version
if(VYear >= 2019)
    %Simulation
    open_system('DRPLDM');
    SimOut = sim('DRPLDM','ReturnWorkspaceOutputs','on');
else
    %Simulation
    open_system('DRPLDM');
    SimOut = sim('DRPLDM','ReturnWorkspaceOutputs','on');
end

%--------------------------
%READS SIMULATION VARIABLES
%--------------------------

ReadSimVars

%-----------------------
%PLOTING OF HIL GRAPHICS
%-----------------------

if PlotGraphics == 1
 PlotHILGraphs   
end





