
%The code below loads components gains and maps, in case of any compressor
%or turbine, or area, in case of nozzle


%-------------------------------------
%LOADING OF COMPONENTS GAINS AND AREAS
%-------------------------------------

for i = 1:length(CompNames)-1
    if str2double(char(CompNames(end))) == 4
        %Loads gains for component map
        if exist([char(CompNames(i)) '_Gains'],'var')
            %Corrected speed gain
            word = ['NcGain = ' char(CompNames(i)) '_Gains(1);'];
            eval(word);
            %Corrected air mass flow gain
            word = ['WcGain = ' char(CompNames(i)) '_Gains(2);'];
            eval(word);
            %Corrected pressure ratio gain
            word = ['PRGain = ' char(CompNames(i)) '_Gains(3);'];
            eval(word);
            %Efficiency gain
            word = ['EffGain = ' char(CompNames(i)) '_Gains(4);'];
            eval(word);
            break;
        end
    end
    %In case a nozzle is detected
    if str2double(char(CompNames(end))) == 2
        %Loads throat and exhaust area values
        if exist([char(CompNames(i)) '_Gains'],'var')
            %Loads throat area value
            word = ['AthroatDes = ' char(CompNames(i)) '_Gains(1);'];
            evalin('base',word);
            %Loads exhaust area value
            word = ['AexhaustDes = ' char(CompNames(i)) '_Gains(2);'];
            eval('base',word);
            break;
        end
    end
end

%------------------------------------------
%LOADING OF COMPONENTS MAPS AND NOZZLE AREA
%------------------------------------------

for i = 1:length(CompNames)
    %Verifies if an underscore is present, indicating either Core nozzle or
    %FAN nozzle
    if ~isempty((find(ismember(char(CompNames(1)),'_') == 1,1)))
        CompVarList = [cellstr('AthDes');...
            cellstr('AexhDes')];
        %Verifies if an 'F' is present, indicating fan nozzle
        if ~isempty((find(ismember(char(CompNames(1)),'F') == 1,1)))
            CompVarList = [cellstr('AthDesFAN');...
                cellstr('AexhDesFAN')];
        end
        %Loads throat design area corrected to international units
        word = [char(CompVarList(1)) '=AthroatDes * DesPoint.Area_AU2SI;' ];
        evalin('base',word);
        %Loads exhaust design area corrected to international units
        word = [char(CompVarList(2)) '=AexhaustDes * DesPoint.Area_AU2SI;' ];
        evalin('base',word);
        
        break;        
    end
    
    %Verifies if any member of CompNames has a 'C' or an 'F', indicating
    %FAN or compressor
    if ~isempty((find(ismember(char(CompNames(1)),'C') == 1,1))) || ~isempty(find(ismember(char(CompNames(1)),'F') == 1,1))
        CompVarList = [cellstr(['Nc' char(CompNames(1)) 'Map']); cellstr(['Rline' char(CompNames(1)) 'Map']);...
            cellstr(['Wc' char(CompNames(1)) 'Map']); cellstr(['Wc' char(CompNames(1)) 'Stall']);...
            cellstr(['Eff' char(CompNames(1)) 'Map']); cellstr(['PR' char(CompNames(1)) 'Map']);...
            cellstr(['PR' char(CompNames(1)) 'Stall'])];
        
        
        %LOADS COMPRESSOR MAP MATRICES AND VECTORS
        
        for j = 1:length(CompNames)
            if ~isempty((find(ismember(MWSFields,CompNames(i)) == 1,1)))
                %Loads corrected speed array
                word = [char(CompVarList(1)) '=' 'MWS.' char(CompNames(i)) '.NcVec * NcGain / NDes;'];
                evalin('base',word);
                %Loads R-line vector
                word = [char(CompVarList(2)) '=' 'MWS.' char(CompNames(i)) '.RlineVec;'];
                evalin('base',word);
                %Loads corrected air mass flow matrix
                word = [char(CompVarList(3)) '=' 'MWS.' char(CompNames(i)) '.WcArray * WcGain / 2.2046226;',...
                    char(CompVarList(3)) '=' 'fliplr(' char(CompVarList(3)) ');'];
                evalin('base',word);
                %Loads corrected air mass flow stall vector
                word = [char(CompVarList(4)) '=' 'MWS.' char(CompNames(i)) '.WcMapSurge * WcGain / 2.2046226;',...
                    char(CompVarList(4)) '=' 'fliplr(' char(CompVarList(4)) ');'];
                evalin('base',word);
                %Loads efficiency matrix
                word = [char(CompVarList(5)) '=' 'MWS.' char(CompNames(i)) '.EffArray * EffGain;',...
                    char(CompVarList(5)) '=' 'fliplr(' char(CompVarList(5)) ');'];
                evalin('base',word);
                %Loads pressure ratio matrix
                word = [char(CompVarList(6)) '=' 'PRGain * (MWS.' char(CompNames(i)) '.PRArray - 1) + 1;',...
                    char(CompVarList(6)) '=' 'fliplr(' char(CompVarList(6)) ');'];
                evalin('base',word);
                %Loads pressure ratio stall vector
                word = [char(CompVarList(7)) '=' 'PRGain * (MWS.' char(CompNames(i)) '.PRMapSurge - 1) + 1;',...
                    char(CompVarList(7)) '=' 'fliplr(' char(CompVarList(7)) ');'];
                evalin('base',word);
                break;
            end
        end
        
        break;
    end
    
    if ~isempty((find(ismember(char(CompNames(1)),'T') == 1,1)))
        CompVarList = [cellstr(['Nc' char(CompNames(1)) 'Map']);...
            cellstr(['Wc' char(CompNames(1)) 'Map']);...
            cellstr(['Eff' char(CompNames(1)) 'Map']);...
            cellstr(['PR' char(CompNames(1)) 'Map'])];
        
        for j = 1:length(CompNames)
            if ~isempty((find(ismember(MWSFields,CompNames(i)) == 1,1)))
                %Loads corrected speed array
                word = [char(CompVarList(1)) '=' 'MWS.' char(CompNames(i)) '.NcVec * NcGain / NDes;'];
                evalin('base',word);
                %Loads corrected gas mass flow matrix
                word = [char(CompVarList(2)) '=' 'MWS.' char(CompNames(i)) '.WcArray * WcGain / 2.2046226;'];
                evalin('base',word);
                %Loads efficiency matrix
                word = [char(CompVarList(3)) '=' 'MWS.' char(CompNames(i)) '.EffArray * EffGain;'];
                evalin('base',word);
                %Loads pressure ratio vector
                word = [char(CompVarList(4)) '=' 'PRGain * (MWS.' char(CompNames(i)) '.PRVec - 1) + 1;'];
                evalin('base',word);
                break;
            end
        end
    end
    
end


