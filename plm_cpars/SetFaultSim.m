%=====================
    % SENSOR FAULTS TABLE
    %=====================
    
    %MATLAB Bit - Fault 
    
    %Ts2                             %RPM
                                
    %  1 - Ts2_0 SCV                 %18 - RPM_0 Short
    %  2 - Ts2_0 SCG                 %19 - RPM_0 Open
    %  3 - Ts2_0 Open                %20 - RPM_0 1 Pulse Loss
                                     %21 - RPM_0 2 Pulse Loss
    %  4 - Ts2_1 SCV                 %22 - RPM_0 3 Pulse Loss
    %  5 - Ts2_1 SCG
    %  6 - Ts2_1 Open                %23 - RPM_0 Short
                                     %24 - RPM_0 Open
    %Pt3                             %25 - RPM_0 1 Pulse Loss
                                     %26 - RPM_0 2 Pulse Loss
    %  7 - Pt3_0 Short               %27 - RPM_0 3 Pulse Loss
    %  8 - Pt3_0 Open      
                                     %POil
    %Tt4
                                     %28 - POil_0 Short
    %  9 - Tt4_0 SCV                 %29 - POil_0 Open
    % 10 - Tt4_0 SCG
    % 11 - Tt4_0 Open                %PFuel
    
    % 12 - Tt4_1 SCV                 %30 - PFuel_0 Short
    % 13 - Tt4_1 SCG                 %31 - PFuel_0 Open
    % 14 - Tt4_1 Open
                                    %Vibration
    % 15 - Tt4_2 SCV
    % 16 - Tt4_2 SCG                %32 - Vibration_0 Short
    % 17 - Tt4_2 Open               %33 - Vibration_0 Open
    
    %====================
    % SYSTEM FAULT TABLE
    %====================
                       
    %MATLAB Bit - Fault
    
    %Lub System                     %Mec System
                                    
    %34 - Oil choke                 %38 - Blade loss
    %35 - Oil lack                  %39 - Shaft lock
                                    
    %Fuel System
                                    
    %36 - Fuel choke
    %37 - Fuel lack
                      
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
    
    %FaultStartTime(1) = 20;             %FaultStopTime(1) = 0;             
    %FaultStartTime(2) = 0;             %FaultStopTime(2) = 0;             
    %FaultStartTime(3) = 0;             %FaultStopTime(3) = 0;             
    %FaultStartTime(4) = 0;             %FaultStopTime(4) = 0;             
    %FaultStartTime(5) = 0;             %FaultStopTime(5) = 0;             
    %FaultStartTime(6) = 0;             %FaultStopTime(6) = 0;             
    %FaultStartTime(7) = 0;             %FaultStopTime(7) = 0;             
    %FaultStartTime(8) = 0;             %FaultStopTime(8) = 0;             
    %FaultStartTime(9) = 0;             %FaultStopTime(9) = 0;             
    %FaultStartTime(10) = 0;            %FaultStopTime(10) = 0;             
    %FaultStartTime(11) = 0;            %FaultStopTime(11) = 0;             
    %FaultStartTime(12) = 0;            %FaultStopTime(12) = 0;             
    %FaultStartTime(13) = 0;            %FaultStopTime(13) = 0;             
    %FaultStartTime(14) = 0;            %FaultStopTime(14) = 0;             
    %FaultStartTime(15) = 0;            %FaultStopTime(15) = 0;             
    %FaultStartTime(16) = 0;            %FaultStopTime(16) = 0;             
    %FaultStartTime(17) = 0;            %FaultStopTime(17) = 0;             
    %FaultStartTime(18) = 0;            %FaultStopTime(18) = 0;             
    %FaultStartTime(19) = 0;            %FaultStopTime(19) = 0;             
    %FaultStartTime(20) = 0;            %FaultStopTime(20) = 0;             
    %FaultStartTime(21) = 0;            %FaultStopTime(21) = 0;             
    %FaultStartTime(22) = 0;            %FaultStopTime(22) = 0;             
    %FaultStartTime(23) = 0;            %FaultStopTime(23) = 0;             
    %FaultStartTime(24) = 0;            %FaultStopTime(24) = 0;             
    %FaultStartTime(25) = 0;            %FaultStopTime(25) = 0;             
    %FaultStartTime(26) = 0;            %FaultStopTime(26) = 0;             
    %FaultStartTime(27) = 0;            %FaultStopTime(27) = 0;             
    %FaultStartTime(28) = 0;            %FaultStopTime(28) = 0;             
    %FaultStartTime(29) = 0;            %FaultStopTime(29) = 0;             
    %FaultStartTime(30) = 0;            %FaultStopTime(30) = 0;             
    %FaultStartTime(31) = 0;            %FaultStopTime(31) = 0;             
    %FaultStartTime(32) = 0;            %FaultStopTime(32) = 0;             
    %FaultStartTime(33) = 0;            %FaultStopTime(33) = 0;             
    %FaultStartTime(34) = 0;            %FaultStopTime(34) = 0;             
    %FaultStartTime(35) = 0;            %FaultStopTime(35) = 0;             
    %FaultStartTime(36) = 0;            %FaultStopTime(36) = 0;             
    %FaultStartTime(37) = 0;            %FaultStopTime(37) = 0;             
    %FaultStartTime(38) = 0;            %FaultStopTime(38) = 0;             
    %FaultStartTime(39) = 0;            %FaultStopTime(39) = 0;  