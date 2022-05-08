function [ wave ] = dial_numberRandomPause( dialedNumber, samplingFreq )
% The duration of each digit sound is selected at random.
% The pause time between the digits is also selected at random.	

	wave = 0;
	for i = 1 : length(dialedNumber)
		dialLength = randi(10) * .1;
		wave = [wave dial_digit(dialedNumber(i), dialLength, samplingFreq)];
		pauseLength = randi(10) * .1;
		pauseTime = 0 : 1/samplingFreq : pauseLength;
		pauseWave = sin(pauseTime);
		wave = [wave pauseWave];
	end
end

