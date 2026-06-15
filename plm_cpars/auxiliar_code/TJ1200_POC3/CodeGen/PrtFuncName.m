function PrtFuncName(fid,EngineName,MtxName,ArgType,ArgName,RetType)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    
    MtxName = [EngineName MtxName];
    fprintf(fid,'\n');
    word = ['\n/* Gets ' MtxName ' Matrix */'];
    fprintf(fid,word);
    word = ['\n' RetType ' get' MtxName 'Mtx(' ArgType ArgName ');'];
    fprintf(fid,word);

end

