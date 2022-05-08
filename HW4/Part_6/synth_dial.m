fs = 44100;  % sampling frequency

% Uses given class functions for dial_digit and dial_number

% dial area code 515
dialAreaCode_0 = dial_number('515', 0.5, 0.2, fs);  
sound(dialAreaCode_0, fs);
audiowrite('touch-tone-515.wav', dialAreaCode_0, fs);
pause(5)

% dial area code 515
dialAreaCode_1 = dial_number('563', 0.5, 0.2, fs);  
sound(dialAreaCode_1, fs);
audiowrite('touch-tone-563.wav', dialAreaCode_1, fs);
pause(5)

% dial area code 309
dialAreaCode_2 = dial_number('309', 0.5, 0.2, fs);  
sound(dialAreaCode_2, fs);
audiowrite('touch-tone-309.wav', dialAreaCode_2, fs);
pause(5)


% Y0   - audio data samples
% 512 - window size  (in samples)
% 256 - overlap      (in samples)
% 512 - FFT size     (in samples)
% fs  - sampling frequency (in Hz)
% 'yaxis' - put the frequencies along the y axis
figure; spectrogram(dialAreaCode_0, 512, 256, 512, fs, 'yaxis'); 
title('Spectrogram for Y0');

% Y1   - audio data samples
% 512 - window size  (in samples)
% 256 - overlap      (in samples)
% 512 - FFT size     (in samples)
% fs  - sampling frequency (in Hz)
% 'yaxis' - put the frequencies along the y axis
figure; spectrogram(dialAreaCode_1, 512, 256, 512, fs, 'yaxis'); 
title('Spectrogram for Y1');

% Y2   - audio data samples
% 512 - window size  (in samples)
% 256 - overlap      (in samples)
% 512 - FFT size     (in samples)
% fs  - sampling frequency (in Hz)
% 'yaxis' - put the frequencies along the y axis
figure; spectrogram(dialAreaCode_2, 512, 256, 512, fs, 'yaxis'); 
title('Spectrogram for Y2');

% store the spectrogram data in the complex matrix S
S0 = spectrogram(dialAreaCode_0, 512, 256, 512, fs, 'yaxis');
S1 = spectrogram(dialAreaCode_1, 512, 256, 512, fs, 'yaxis');
S2 = spectrogram(dialAreaCode_2, 512, 256, 512, fs, 'yaxis');

% play it
%sound(Y0, fs0)
%sound(Y1, fs1)
%sound(Y2, fs2)