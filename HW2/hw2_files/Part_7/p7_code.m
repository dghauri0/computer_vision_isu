%insert your code in Part_7/p7_code.m
%edit the file extension and web template to match your programing language

% Read in image.
main = imread('../p7_search.png');
Y = imread('../../Symbol_Cutouts/Y.png');  % Created Y in GIMP.
cross = imread('../../Symbol_Cutouts/X.png');

main_bw = im2bw(main, 0.5);
main_bw_i = ~main_bw;
cross_bw = im2bw(cross, 0.5);
cross_bw_i = ~cross_bw;
Y_bw = im2bw(Y, 0.5);
Y_bw_i = ~Y_bw;

% Identify crosses and also erode/dilate crosses with the Y.
% This is my understanding of "changing the font" because instead
% of having the Y look like it does here as typed, it has a slanted tail.
e0 = imerode(main_bw_i, cross_bw_i);
d0 = imdilate(e0, cross_bw_i);
e1 = imerode(d0, Y_bw_i);
d1 = imdilate(e1, Y_bw_i);

cross_removed = main_bw_i - d0;
Y_added = cross_removed + d1;

final = ~Y_added;
figure; imshow(final)

imwrite(final,'p7_search_final.png')


