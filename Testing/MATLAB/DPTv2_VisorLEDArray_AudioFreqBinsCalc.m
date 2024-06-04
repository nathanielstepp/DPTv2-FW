clear;clc;

binCount = 20;

ee= 2^(1/4.5);
upper_bin = cumsum(round(ee.^(2:(binCount+1))))-1;
lower_bin = [0 upper_bin(1:end-1)+1];

disp(lower_bin);
disp(upper_bin);

round([lower_bin;upper_bin]*44100/1024);


fileID = fopen('Stepp_DPTv2_VisorLEDArray_AudioFreqBins.txt','w');
fprintf(fileID,'const unsigned int freqUpperBin[spectrumWidth] = {');
for i = 1:length(upper_bin)
    if i < length(upper_bin)
        fprintf(fileID,[num2str(upper_bin(i)) ',']);
    else
        fprintf(fileID,num2str(upper_bin(i)));
    end
end
fprintf(fileID,'};');

fprintf(fileID,'\n');

fprintf(fileID,'const unsigned int freqLowerBin[spectrumWidth] = {');
for i = 1:length(lower_bin)
    if i < length(lower_bin)
        fprintf(fileID,[num2str(lower_bin(i)) ',']);
    else
        fprintf(fileID,num2str(lower_bin(i)));
    end
end
fprintf(fileID,'};');

fclose(fileID);