
% COPIES FROM c_Files TO FADE_c_CFiles

%Goes to folder where c files have been created
cd c_Files

%Creates folder for saving single-spool jet engine FADEC .c files
mkdir SingleSpoolFan_FADEC_c_Files
Destination = 'SingleSpoolFan_FADEC_c_Files';

%COPIES ALL .c FILES TO CREATED FOLDER

Source = ['get' EngineName 'AltLinVec.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'AMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'ASVec.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'BMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'DeltaMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'DSVec.c'];
copyfile(Source, Destination)
% Source = ['get' EngineName 'FPInVec.c'];
% copyfile(Source, Destination)
% Source = ['get' EngineName 'FPOutVec.c'];
% copyfile(Source, Destination)
Source = ['get' EngineName 'FNcMaxContMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'FNperContMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'MNLinVec.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'N_KiMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'N_KpMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'NcFANContMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'NcFANMapMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'NcHPCMapMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'NcVec.c'];
copyfile(Source, Destination)
% Source = ['get' EngineName 'OPInVec.c'];
% copyfile(Source, Destination)
% Source = ['get' EngineName 'OPOutVec.c'];
% copyfile(Source, Destination)
Source = ['get' EngineName 'PRHPCMapMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'Pt3DMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'Pt3Mtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'Pt5DMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'Pt5Mtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'Ts0Mtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'Tt4DMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'Tt4Mtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'Tt5DMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'Tt5Mtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'WcFANMapMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'WcHPCMapMtx.c'];
copyfile(Source, Destination)
Source = ['get' EngineName 'WfMtx.c'];
copyfile(Source, Destination)

%Returns to engine folder
cd ..

