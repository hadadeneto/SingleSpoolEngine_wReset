function FuncName = PrtFuncName(fid,EngineName,MtxName,ArgType,ArgName,RetType)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
    
    MtxName = [EngineName MtxName];
    fprintf(fid,'\n');
    word = ['\n/* Gets ' MtxName ' Matrix */'];
    fprintf(fid,word);
    word = ['\n' RetType ' get' MtxName 'Mtx(' ArgType ArgName ');'];
    %If the matrix name already finishes with Mtx or Vec, the additin of
    %Mtx at the end of the name is not necessary
    if length(MtxName)>= 3
        if strcmp(MtxName(length(MtxName)-2:end),'Mtx') || strcmp(MtxName(length(MtxName)-2:end),'Vec')
            word = ['\n' RetType ' get' MtxName '(' ArgType ArgName ');'];
            FuncName = ['get' MtxName '.c' ];
        end
    end
    fprintf(fid,word);

end

