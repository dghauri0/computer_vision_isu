% Recorded from Team Fortress 2 game using OBS. Converted stereo audio to 
% mono audio using audacity. 

% Read WAV file
[Y0,fs0]=audioread('../input/Part_5/classic_tf2_sound.wav');
[Y1,fs1]=audioread('../input/Part_5/gloves_tf2.wav');
[Y2,fs2]=audioread('../input/Part_5/hit_tf2.wav'); 

% All values were used based on how they represented frequency components
% for each time stamp (i.e., they were picked so that discrete cutoffs
% could be shown for the frequency components). For Y1, I had to increase
% both the window size and FFT size to better meet this criteria.

% Y0   - audio data samples
% 512 - window size  (in samples)
% 256 - overlap      (in samples)
% 512 - FFT size     (in samples)
% fs0  - sampling frequency (in Hz)
% 'yaxis' - put the frequencies along the y axis
figure; spectrogram(Y0, 512, 256, 512, fs0, 'yaxis'); 
title('Spectrogram for Y0');

% Y1   - audio data samples
% 1024 - window size  (in samples)
% 256 - overlap      (in samples)
% 1024 - FFT size     (in samples)
% fs1  - sampling frequency (in Hz)
% 'yaxis' - put the frequencies along the y axis
figure; spectrogram(Y1, 1024, 256, 1024, fs1, 'yaxis'); 
title('Spectrogram for Y1');

% Y2   - audio data samples
% 512 - window size  (in samples)
% 256 - overlap      (in samples)
% 512 - FFT size     (in samples)
% fs2  - sampling frequency (in Hz)
% 'yaxis' - put the frequencies along the y axis
figure; spectrogram(Y2, 512, 256, 512, fs2, 'yaxis'); 
title('Spectrogram for Y2');

% store the spectrogram data in the complex matrix S
S0 = spectrogram(Y0, 512, 256, 512, fs0, 'yaxis');
S1 = spectrogram(Y1, 512, 256, 512, fs1, 'yaxis');
S2 = spectrogram(Y2, 512, 256, 512, fs2, 'yaxis');

% play it
%sound(Y0, fs0)
%sound(Y1, fs1)
%sound(Y2, fs2)