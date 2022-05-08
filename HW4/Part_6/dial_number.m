function [wave] = dial_number(dialedNumber, dialLength, pauseLength, samplingFreq)
	
    % Setup Pause Time
	pauseTime = 0 : 1/samplingFreq : pauseLength;
	pauseWave = sin(pauseTime);
	
	wave = 0;
	for i = 1 : length(dialedNumber)
		wave = [wave dial_digit(dialedNumber(i), dialLength, samplingFreq)];
		wave = [wave pauseWave];
	end
end

