% Read WAV file
[Y0,fs0]=audioread('../input/Part_4/ball_bounce_brick_mono.wav');
[Y1,fs1]=audioread('../input/Part_4/ball_bounce_paddle_mono.wav');
[Y2,fs2]=audioread('../input/Part_4/paddle_widening_mono.wav'); 

figure; spectrogram(Y0); 
title('Spectrogram for Y0');

figure; spectrogram(Y1); 
title('Spectrogram for Y1');

figure; spectrogram(Y2); 
title('Spectrogram for Y2');

% store the spectrogram data in the complex matrix S
S0 = spectrogram(Y0, 512, 256, 512, fs0, 'yaxis');
S1 = spectrogram(Y1, 512, 256, 512, fs1, 'yaxis');
S2 = spectrogram(Y2, 512, 256, 512, fs2, 'yaxis');

% play it
%sound(Y0, fs0)
%sound(Y1, fs1)
%sound(Y2, fs2)