%% Your code goes in this file. 

% Read images.
main0 = imread('p2_image1.png');
main1 = imread('p2_image2.png');
main2 = imread('p2_image3.png');
imshow(main0)

d = drawline;
%pos = d.Position;
%diffPos = diff(pos);
%diameter = hypot(diffPos(1),diffPos(2))
%gray_image = rgb2gray(main0);
%imshow(gray_image); figure;

% Identify circles.
%[centers,radii] = imfindcircles(main,[45 50],'ObjectPolarity','dark','Sensitivity',0.96, 'Method', 'twostage')
[centers0,radii0] = imfindcircles(main0,[45 50],'ObjectPolarity','dark','Sensitivity',0.95, 'Method', 'twostage','EdgeThreshold',0.099);
[centers1,radii1] = imfindcircles(main1,[45 50],'ObjectPolarity','dark','Sensitivity',0.93, 'Method', 'twostage','EdgeThreshold',0.084);
[centers2,radii2] = imfindcircles(main2,[45 50],'ObjectPolarity','dark','Sensitivity',0.94, 'Method', 'twostage','EdgeThreshold',0.089);

pause

close all
clc
clear



