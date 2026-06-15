
% function PritToFile(Delta,Theta,A,B,...
%     Pt21C, Pt21D, Tt21C, Tt21D,...
%     Pt3C, Pt3D, Tt3C, Tt3D,...
%     Tt4C, Tt4D,...
%     Pt5C, Pt5D, Tt5C, Tt5D,...
%     Pt6C, Pt6D, Tt6C, Tt6D,...
%     N_Kp, N_Ki, Pt3_Kp, Pt3_Ki,...
%     Tt4_Kp, Tt4_Ki, Tt5_Kp, Tt5_Ki,...
%     NcFAN,...
%     Pt21, Tt21,...
%     Pt3, Tt3,...
%     Wf, Tt4,...
%     Pt5, Tt5, Pt6, Tt6,...
%     FN, FNper, ...
%     NcFANMap, WcFANMap, EffFANMap, PRFANMap, ...
%     NcHPCMap, WcHPCMap, EffHPCMap, PRHPCMap, ...
%     NcHPTMap, WcHPTMap, EffHPTMap, PRHPTMap, ...
%     PRFANStall, WcFANStall,PRHPCStall, WcHPCStall, ...
%     FNperCont,NcFANCont,EngineName,...
%     MNLinPoints,AltLinVec)

function PritToFile(Delta,Theta,A,B,...
    Pt21C, Pt21D, Tt21C, Tt21D,...
    Pt3C, Pt3D, Tt3C, Tt3D,...
    Tt4C, Tt4D,...
    Pt5C, Pt5D, Tt5C, Tt5D,...
    Pt6C, Pt6D, Tt6C, Tt6D,...
    N_Kp, N_Ki, Pt3_Kp, Pt3_Ki,...
    Tt4_Kp, Tt4_Ki, Tt5_Kp, Tt5_Ki,...
    NcFAN,...
    Pt21, Tt21,...
    Pt3, Tt3,...
    Wf, Tt4,...
    Pt5, Tt5, Pt6, Tt6,...
    FN, FNper, ...
    NcFANMap, WcFANMap, EffFANMap, PRFANMap, ...
    NcHPCMap, WcHPCMap, EffHPCMap, PRHPCMap, ...
    NcHPTMap, WcHPTMap, EffHPTMap, PRHPTMap, ...
    PRFANStall, WcFANStall,PRHPCStall, WcHPCStall, ...
    FNperCont,NcFANCont,EngineName,...
    MNLinPoints,AltLinVec,Ps3Min)

           
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

    %-------------------
    %BREAKPOINT VECTORS
    %-------------------

    %Type of function argument
    ArgType = 'double';
    %Name of function argument
    ArgName = '*Pointer';
    %Type of returned variable
    RetType = 'void';
    
    %Creates a folders for organizing files
    mkdir h_Files
    mkdir c_Files
    
    cFolderName = 'c_Files';
    hFolderName = 'h_Files';
    
    %Opens a .h document for defining the function that acquires matrices
    %word = 'LinMtxFunctions.h';
    word = [hFolderName '/' EngineName 'LinMtxFunctions.h'];
    fileword = ['FILE ' word ' GENERATED'];
    fid = fopen(word,'w');
    
    %Prints the altitude value in first line and jumps two lines
    word = '#ifndef LINMTXFUNCTIONS_H';
    fprintf(fid,word);
    fprintf(fid,'\n');
    word = '#define LINMTXFUNCTIONS_H';
    fprintf(fid,word);
    
    %Ptints the desire comment above the printed C code line
    fprintf(fid,'\n\n');
    word = '/* FUNCTIONS FOR LOADING MATRICES CONTAINING LINEARIZATION POINTS */';
    fprintf(fid,word);
    %Prints the MN Linearization Vector - Points of MN where linear
    %models were obtained

    %Include Type for State-Space Matrices
%     IncludeType = 'Interpolation_Types';
%     IncludeTypePI = 'Control_Types';
    
    PrtFuncName(fid,EngineName,'Delta',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Theta',ArgType,ArgName,RetType);

    PrtFuncName(fid,EngineName,'A',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'B',ArgType,ArgName,RetType);
    
    PrtFuncName(fid,EngineName,'Pt21C',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Pt21D',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt21C',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt21D',ArgType,ArgName,RetType);
    
    PrtFuncName(fid,EngineName,'Pt3C',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Pt3D',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt3C',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt3D',ArgType,ArgName,RetType);
    
    PrtFuncName(fid,EngineName,'Tt4C',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt4D',ArgType,ArgName,RetType);
    
    PrtFuncName(fid,EngineName,'Pt5C',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Pt5D',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt5C',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt5D',ArgType,ArgName,RetType);

    PrtFuncName(fid,EngineName,'Pt6C',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Pt6D',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt6C',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt6D',ArgType,ArgName,RetType);
   
    %CONTROLLER GAINS
    
    PrtFuncName(fid,EngineName,'N_Kp',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'N_Ki',ArgType,ArgName,RetType);
    
    PrtFuncName(fid,EngineName,'Pt3_Kp',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Pt3_Ki',ArgType,ArgName,RetType);
    
    PrtFuncName(fid,EngineName,'Tt4_Kp',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt4_Ki',ArgType,ArgName,RetType);
    
    PrtFuncName(fid,EngineName,'Tt5_Kp',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt5_Ki',ArgType,ArgName,RetType);
    
    %ENGINE STATIONS
    %Station 2
    PrtFuncName(fid,EngineName,'NcFAN',ArgType,ArgName,RetType);
    %Station 21
    PrtFuncName(fid,EngineName,'Pt21',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt21',ArgType,ArgName,RetType);
    %Station 3
    PrtFuncName(fid,EngineName,'Pt3',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt3',ArgType,ArgName,RetType);
    %Station 4
    PrtFuncName(fid,EngineName,'Pt4',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Wf',ArgType,ArgName,RetType);
    %Station 5
    PrtFuncName(fid,EngineName,'Pt5',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt5',ArgType,ArgName,RetType);
    %Station 6
    PrtFuncName(fid,EngineName,'Pt6',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Tt6',ArgType,ArgName,RetType);
    
    %COMPONENTS MAPS
    %Fan
    PrtFuncName(fid,EngineName,'NcFANMap',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'WcFANMap',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'WcFANStall',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'EffFANMap',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'PRFANMap',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'PRFANStall',ArgType,ArgName,RetType);
    %Compressor
    PrtFuncName(fid,EngineName,'NcHPCMap',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'WcHPCMap',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'WcHPCStall',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'EffHPCMap',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'PRHPCMap',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'PRHPCStall',ArgType,ArgName,RetType);
    %Turbine
    PrtFuncName(fid,EngineName,'NcHPTMap',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'WcHPTMap',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'EffHPTMap',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'PRHPTMap',ArgType,ArgName,RetType);
    
    %Engine parameters to be used by controller
    PrtFuncName(fid,EngineName,'FNperCont',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'NcFANCont',ArgType,ArgName,RetType);
    PrtFuncName(fid,EngineName,'Ps3Min',ArgType,ArgName,RetType);    

    %Altitude and Number Linearizing Vector
    PrtFuncName(fid,EngineName,'AltLinVec',ArgType,ArgName,RetType);    
    PrtFuncName(fid,EngineName,'MNLinVec',ArgType,ArgName,RetType);

    
    %Prints the endif command of .h files
    word = '\n\n#endif';
    fprintf(fid,word);
    
    %closes the generated .txt file
    fclose(fid);
    disp(' ')
    disp(fileword)
    

    %AMBIENT MATRICES
    
    %Calculates the elements of the Ambient Matrices
    [rows, columns,pages] = size(Delta);
    Ambient_Elem_Word = num2str(rows*columns*pages);
    %Ptints Delta Matrix in a separate file
    Prt3DCMtx(EngineName,'DeltaMtx',Delta,Ambient_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints Theta Matrix in a separate file
    Prt3DCMtx(EngineName,'ThetaMtx',Theta,Ambient_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    
    %STATE-SPACE MATRICES
    
    %Defines the number of elements of the state-space matrices A, B and C,
    %D for all observed variables
    [rows,columns,pages] = size(A);
    %SteadyOp_Elem = rows*columns*pages;
    SteadyOp_Elem_Word = num2str(rows*columns*pages);
    %NumElWord = 'TOTAL_ELEM';
    
    %Ptints the A matrix in a separate file    
    Prt3DCMtx(EngineName,'AMtx',A,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prt3DCMtx(EngineName,'AMtx',A,'TOTAL_ELEM',ArgType,ArgName,RetType,cFolderName);
    %Prints the B matrix in a separate file
    Prt3DCMtx(EngineName,'BMtx',B,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    
    %Prints the Pt21C matrix in a separate file
    Prt3DCMtx(EngineName,'Pt21CMtx',Pt21C,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Pt21D matrix in a separate file
    Prt3DCMtx(EngineName,'Pt21DMtx',Pt21D,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt21C matrix in a separate file
    Prt3DCMtx(EngineName,'Tt21CMtx',Tt21C,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt21D matrix in a separate file
    Prt3DCMtx(EngineName,'Tt21DMtx',Tt21D,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName); 
    
    %Prints the Pt3C matrix in a separate file
    Prt3DCMtx(EngineName,'Pt3CMtx',Pt3C,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Pt3D matrix in a separate file
    Prt3DCMtx(EngineName,'Pt3DMtx',Pt3D,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt3C matrix in a separate file
    Prt3DCMtx(EngineName,'Tt3CMtx',Tt3C,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt3D matrix in a separate file
    Prt3DCMtx(EngineName,'Tt3DMtx',Tt3D,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);

    %Prints the Tt4C matrix in a separate file
    Prt3DCMtx(EngineName,'Tt4CMtx',Tt4C,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt4D matrix in a separate file
    Prt3DCMtx(EngineName,'Tt4DMtx',Tt4D,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    
    %Prints the Pt5C matrix in a separate file
    Prt3DCMtx(EngineName,'Pt5CMtx',Pt5C,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Pt5D matrix in a separate file
    Prt3DCMtx(EngineName,'Pt5DMtx',Pt5D,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt5C matrix in a separate file
    Prt3DCMtx(EngineName,'Tt5CMtx',Tt5C,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt5D matrix in a separate file
    Prt3DCMtx(EngineName,'Tt5DMtx',Tt5D,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    
    %Prints the Pt6C matrix in a separate file
    Prt3DCMtx(EngineName,'Pt6CMtx',Pt6C,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Pt6D matrix in a separate file
    Prt3DCMtx(EngineName,'Pt6DMtx',Pt6D,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt6C matrix in a separate file
    Prt3DCMtx(EngineName,'Tt6CMtx',Tt6C,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt6D matrix in a separate file
    Prt3DCMtx(EngineName,'Tt6DMtx',Tt6D,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    
    %GAIN MATRICES
    
    %The rotation speed Kp and Ki matrices must be larger in the case every
    %steady operating point is considered - different altitudes as well -
    %in the control case. The Power Management Controller is the only one
    %to use gain scheduling.
    [rows,columns,pages] = size(N_Kp);
    %PowerMan_Elem =  rows * columns * pages;
    PowerMan_Elem_Word = num2str(rows * columns * pages);
   
    %Prints the N_KpMtx matrix in a separate file
    Prt3DCMtx(EngineName,'N_KpMtx',N_Kp,PowerMan_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the N_KiMtx matrix in a separate file
    Prt3DCMtx(EngineName,'N_KiMtx',N_Ki,PowerMan_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    
    %Prints the Pt3_KpMtx matrix in a separate file
    Prt3DCMtx(EngineName,'Pt3_KpMtx',Pt3_Kp,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Pt3_KiMtx matrix in a separate file
    Prt3DCMtx(EngineName,'Pt3_KiMtx',Pt3_Ki,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    
    %Prints the Tt4_KpMtx matrix in a separate file
    Prt3DCMtx(EngineName,'Tt4_KpMtx',Tt4_Kp,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt4_KiMtx matrix in a separate file
    Prt3DCMtx(EngineName,'Tt4_KiMtx',Tt4_Ki,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt5_KpMtx matrix in a separate file
    Prt3DCMtx(EngineName,'Tt5_KpMtx',Tt5_Kp,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt5_KiMtx matrix in a separate file
    Prt3DCMtx(EngineName,'Tt5_KiMtx',Tt5_Ki,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    
    %STEADY-STATE OPRATING POINTS
    
    %Station 2
    %Prints the NcFAN matrix in a separate file
    Prt3DCMtx(EngineName,'NcFANMtx',NcFAN,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Station 21
    %Prints the Pt21 matrix in a separate file
    Prt3DCMtx(EngineName,'Pt21Mtx',Pt21,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt21 matrix in a separate file
    Prt3DCMtx(EngineName,'Tt21Mtx',Tt21,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Station 3
    %Prints the Pt3 matrix in a separate file
    Prt3DCMtx(EngineName,'Pt3Mtx',Pt3,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt3 matrix in a separate file
    Prt3DCMtx(EngineName,'Tt3Mtx',Tt3,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Station 4
    %Prints the Tt4 matrix in a separate file
    Prt3DCMtx(EngineName,'Tt4Mtx',Tt4,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Wf matrix in a separate file
    Prt3DCMtx(EngineName,'WfMtx',Wf,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Station 5
    %Prints the Pt5 matrix in a separate file
    Prt3DCMtx(EngineName,'Pt5Mtx',Pt5,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt5 matrix in a separate file
    Prt3DCMtx(EngineName,'Tt5Mtx',Tt5,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Station 6
    %Prints the Pt6 matrix in a separate file
    Prt3DCMtx(EngineName,'Pt6Mtx',Pt6,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt6 matrix in a separate file
    Prt3DCMtx(EngineName,'Tt6Mtx',Tt6,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Station 8
    %Prints the FN matrix in a separate file
    Prt3DCMtx(EngineName,'FNMtx',FN,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    %Prints the Tt6 matrix in a separate file
    Prt3DCMtx(EngineName,'FNperMtx',FNper,SteadyOp_Elem_Word,ArgType,ArgName,RetType,cFolderName);    
    
    [~,column,~] = size(NcFAN);
    
    %
    Dummy = zeros(1,column);
    %Prints the KiTt4 matrix in a separate file
    Prt3DCMtx(EngineName,'DummyMtx',Dummy,num2str(column),ArgType,ArgName,RetType,cFolderName);
    
    %COMPONENTS MAPS
    
    %Fan
    
    [rows,columns,pages] = size(NcFANMap);
    NcFANMap_Elem_Word = num2str(rows*columns*pages);
    [rows,columns,pages] = size(WcFANMap);
    WcFANMap_Elem_Word = num2str(rows*columns*pages);
%     [rows,columns,pages] = size(NcFANMap);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'NcFANMapMtx',NcFANMap,NcFANMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
%     [rows,columns,pages] = size(WcFANMap);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'WcFANMapMtx',WcFANMap,WcFANMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
%     [rows,columns,pages] = size(WcFANStall);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'WcFANStallMtx',WcFANStall,NcFANMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
%     [rows,columns,pages] = size(EffFANMap);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'EffFANMapMtx',EffFANMap,WcFANMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
%     [rows,columns,pages] = size(PRFANMap);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'PRFANMapMtx',PRFANMap,WcFANMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
%     [rows,columns,pages] = size(PRFANStall);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'PRFANStallMtx',PRFANStall,NcFANMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);

    %Compressor
    [rows,columns,pages] = size(NcHPCMap);
    NcHPCMap_Elem_Word = num2str(rows*columns*pages);
    [rows,columns,pages] = size(WcHPCMap);
    WcHPCMap_Elem_Word = num2str(rows*columns*pages);
    
%     [rows,columns,pages] = size(NcHPCMap);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'NcHPCMapMtx',NcHPCMap,NcHPCMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
%     [rows,columns,pages] = size(WcHPCMap);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'WcHPCMapMtx',WcHPCMap,WcHPCMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
%     [rows,columns,pages] = size(WcHPCStall);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'WcHPCStallMtx',WcHPCStall,NcHPCMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
%     [rows,columns,pages] = size(EffHPCMap);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'EffHPCMapMtx',EffHPCMap,WcHPCMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
%     [rows,columns,pages] = size(PRHPCMap);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'PRHPCMapMtx',PRHPCMap,WcHPCMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
%     [rows,columns,pages] = size(PRHPCStall);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'PRHPCStallMtx',PRHPCStall,NcHPCMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    
    %Turbine
    [rows,columns,pages] = size(NcHPTMap);
    NcHPTMap_Elem_Word = num2str(rows*columns*pages);
    [rows,columns,pages] = size(PRHPTMap);
    PRHPTMap_Elem_Word = num2str(rows*columns*pages);
    [rows,columns,pages] = size(WcHPTMap);
    WcHPTMap_Elem_Word = num2str(rows*columns*pages);
    
%     [rows,columns,pages] = size(NcHPTMap);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'NcHPTMapMtx',NcHPTMap,NcHPTMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
%     [rows,columns,pages] = size(WcHPTMap);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'WcHPTMapMtx',WcHPTMap,WcHPTMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
%     [rows,columns,pages] = size(EffHPTMap);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'EffHPTMapMtx',EffHPTMap,WcHPTMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
%     [rows,columns,pages] = size(PRHPTMap);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'PRHPTMapMtx',PRHPTMap,PRHPTMap_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    
    %Engine parameters matrices to be used by the controller
%     [rows,columns,pages] = size(NcFANCont);
%     NumElWord = num2str(rows*columns*pages);
    
    %The matrices below are used by the Power Management Controller for
    %finding the matrix indexes required for calculating the Power
    %Management compensator gains. Therefore, their sizes must be the same
    %as the Ki and Kp matrices
    Prt3DCMtx(EngineName,'NcFANContMtx',NcFANCont,PowerMan_Elem_Word,ArgType,ArgName,RetType,cFolderName);
%     [rows,columns,pages] = size(FNperCont);
%     NumElWord = num2str(rows*columns*pages);
    Prt3DCMtx(EngineName,'FNperContMtx',FNperCont,PowerMan_Elem_Word,ArgType,ArgName,RetType,cFolderName);

    %Reads size of Ps3Min
    [rows,columns] = size(Ps3Min);
    Ps3Min_Elem_Word = num2str(rows * columns);
    %Prints the matrix with Ps3 minimum values
    Prt3DCMtx(EngineName,'Ps3MinMtx',Ps3Min,Ps3Min_Elem_Word,ArgType,ArgName,RetType,cFolderName);
    
    %Altitude and Mach Number Linearization Vector
    Prt3DCMtx(EngineName,'AltLinVec',MNLinPoints,num2str(length(AltLinVec)),ArgType,ArgName,RetType,cFolderName);
    Prt3DCMtx(EngineName,'MNLinVec',MNLinPoints,num2str(length(MNLinPoints)),ArgType,ArgName,RetType,cFolderName);
    
    
    % -------------------------------------------------------------- %
    % GENERATION OF PIECES OF CODE TO BE DIRECTLY INSERTED IN Main.c %
    % -------------------------------------------------------------- %
    
    % PRINTS THE VALUE OF MATRICES SIZES
    
    %
    word = 'MtxSizes.txt';
    fileword = ['FILE ' word ' GENERATED'];
    fid = fopen(word,'w');
    
    word = ['\n\n' '/* Number of steady operating points used for linearization at Sea Level */'];
    fprintf(fid,word);
    word = ['\n' 'SteadyOp_Elem = ' SteadyOp_Elem_Word ';'];
    fprintf(fid,word);

    word = ['\n\n' '/* Number of total steady operating points used for Power Management Controller - all altitudes */'];
    fprintf(fid,word);
    word = ['\n' 'PowerMan_Elem = ' PowerMan_Elem_Word ';'];
    fprintf(fid,word);
    
    word = ['\n\n' '/* Fan map size */'];
    fprintf(fid,word);
    word = ['\n' 'NcFANMap_Elem = ' NcFANMap_Elem_Word ';'];
    fprintf(fid,word); 
    word = ['\n' 'WcFANMap_Elem = ' WcFANMap_Elem_Word ';'];
    fprintf(fid,word);
        
    word = ['\n\n' '/* Compressor map size */'];
    fprintf(fid,word);
    word = ['\n' 'NcHPCMap_Elem = ' NcHPCMap_Elem_Word ';'];
    fprintf(fid,word); 
    word = ['\n' 'WcHPCMap_Elem = ' WcHPCMap_Elem_Word ';'];
    fprintf(fid,word);
    
    word = ['\n\n' '/* Turbine map size */'];
    fprintf(fid,word);
    word = ['\n' 'NcHPTMap_Elem = ' NcHPTMap_Elem_Word ';'];
    fprintf(fid,word);
    word = ['\n' 'PRHPTMap_Elem = ' PRHPTMap_Elem_Word ';'];
    fprintf(fid,word);
    word = ['\n' 'WcHPTMap_Elem = ' WcHPTMap_Elem_Word ';'];
    fprintf(fid,word);
    
    %closes the generated .txt file
    fclose(fid);
    disp(' ')
    disp(fileword)
    
    
    
end

