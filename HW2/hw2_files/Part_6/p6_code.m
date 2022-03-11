%insert your code in Part_6/p6_code.m
%edit the file extension and web template to match your programing language

% Read in image.
main = imread('../p6_search.png');

% Split multi-channeled (color) image into separate discrete channels.
[R,G,B] = imsplit(main);
se_horiz = strel('line', 50, 0);
se_vert = strel('line', 50, 90);
ae0 = imerode(~im2bw(main, 0.5), se_horiz);
ad0 = imdilate(ae0, se_horiz);
ae1 = imerode(~im2bw(main, 0.5), se_vert);
ad1 = imdilate(ae1, se_vert);
result_1 = ad0 + ad1;
result_1i = ~result_1;


% Setup channels for modification (binarize and invert).
R_bw = im2bw(R, 0.5);
G_bw = im2bw(G, 0.5);
B_bw = im2bw(B, 0.5);
R_bw_i = ~R_bw;
G_bw_i = ~G_bw;
B_bw_i = ~B_bw;

% Read in symbols.
cross = imread('../../Symbol_Cutouts/X.png');
O = imread('../../Symbol_Cutouts/O.png');
solid_dot = imread('../../Symbol_Cutouts/dot.png');
plus = imread('../../Symbol_Cutouts/plus.png');
forward_slash = imread('../../Symbol_Cutouts/slash.png');
back_slash = imread('../../Symbol_Cutouts/backslash.png');
vertical = imread('../../Symbol_Cutouts/vertical.png');
horizontal = imread('../../Symbol_Cutouts/horizontal.png');

% Binarize and invert.
cross_b = im2bw(cross);
cross_bi = ~cross_b;
O_b = im2bw(O);
O_bi = ~O_b;
solid_dot_b = im2bw(solid_dot);
solid_dot_bi = ~solid_dot_b;
plus_b = im2bw(plus);
plus_bi = ~plus_b;
forward_slash_b = im2bw(forward_slash);
forward_slash_bi = ~forward_slash_b;
back_slash_b = im2bw(back_slash);
back_slash_bi = ~back_slash_b;
vertical_b = im2bw(vertical);
vertical_bi = ~vertical_b;
horizontal_b = im2bw(horizontal);
horizontal_bi = ~horizontal_b;
%figure; imshow(back_slash_bi)
%figure; imshow(forward_slash_bi)
se_temp = strel('line', 30, 0);

% Erode with a subsequent dilate to pull out symbols (this is extremely
% inefficient -- I know -- I'm just trying to get this done and
% not overthink it). Also, couldn't get my pluses to look right half the 
% time... The horizontal symbol kept interfering so I'm just taking an L here
% honestly. 

% ERODE
ae_cross_R = imerode(R_bw_i, cross_bi);
ae_cross_G = imerode(G_bw_i, cross_bi);
ae_cross_B = imerode(B_bw_i, cross_bi);
ae_O_R = imerode(R_bw_i, O_bi);
ae_O_G = imerode(G_bw_i, O_bi);
ae_O_B = imerode(B_bw_i, O_bi);
ae_solid_dot_R = imerode(R_bw_i, solid_dot_bi);
ae_solid_dot_G = imerode(G_bw_i, solid_dot_bi);
ae_solid_dot_B = imerode(B_bw_i, solid_dot_bi);
ae_plus_R = imerode(R_bw_i, plus_bi);
ae_plus_G = imerode(G_bw_i, plus_bi);
ae_plus_B = imerode(B_bw_i, plus_bi);
ae_forward_slash_R = imerode(R_bw_i, forward_slash_bi);
ae_forward_slash_G = imerode(G_bw_i, forward_slash_bi);
ae_forward_slash_B = imerode(B_bw_i, forward_slash_bi);
ae_back_slash_R = imerode(R_bw_i, back_slash_bi);
ae_back_slash_G = imerode(G_bw_i, back_slash_bi);
ae_back_slash_B = imerode(B_bw_i, back_slash_bi);
ae_vertical_R = imerode(R_bw_i, vertical_bi);
ae_vertical_G = imerode(G_bw_i, vertical_bi);
ae_vertical_B = imerode(B_bw_i, vertical_bi);
ae_horizontal_R = imerode(R_bw_i, horizontal_bi);
ae_horizontal_G = imerode(G_bw_i, horizontal_bi);
ae_horizontal_B = imerode(B_bw_i, horizontal_bi);

% DILATE
ad_cross_R = imdilate(ae_cross_R, cross_bi);
ad_cross_G = imdilate(ae_cross_G, cross_bi);
ad_cross_B = imdilate(ae_cross_B, cross_bi);
ad_O_R = imdilate(ae_O_R, O_bi);
ad_O_G = imdilate(ae_O_G, O_bi);
ad_O_B = imdilate(ae_O_B, O_bi);
ad_solid_dot_R = imdilate(ae_solid_dot_R, solid_dot_bi);
ad_solid_dot_G = imdilate(ae_solid_dot_G, solid_dot_bi);
ad_solid_dot_B = imdilate(ae_solid_dot_B, solid_dot_bi);
ad_plus_R = imdilate(ae_plus_R, plus_bi) - result_1;
ad_plus_G = imdilate(ae_plus_G, plus_bi) - result_1;
ad_plus_B = imdilate(ae_plus_B, plus_bi) - result_1;
ad_forward_slash_R = imdilate(ae_forward_slash_R, forward_slash_bi);
ad_forward_slash_G = imdilate(ae_forward_slash_G, forward_slash_bi);
ad_forward_slash_B = imdilate(ae_forward_slash_B, forward_slash_bi);
ad_back_slash_R = imdilate(ae_back_slash_R, back_slash_bi);
ad_back_slash_G = imdilate(ae_back_slash_G, back_slash_bi);
ad_back_slash_B = imdilate(ae_back_slash_B, back_slash_bi);
ad_vertical_R = imdilate(ae_vertical_R, vertical_bi) - result_1;
ad_vertical_G = imdilate(ae_vertical_G, vertical_bi) - result_1;
ad_vertical_B = imdilate(ae_vertical_B, vertical_bi) - result_1;
ad_horizontal_R = imdilate(ae_horizontal_R, horizontal_bi) - result_1;
ad_horizontal_G = imdilate(ae_horizontal_G, horizontal_bi) - result_1;
ad_horizontal_B = imdilate(ae_horizontal_B, horizontal_bi) - result_1;

% Subtract each respective symbol from channels and multiply by rand
% value for each matrix element. 

% Horizontal 
horizontal_sub_R = cast(255 .* (R_bw_i - ad_plus_R - ad_horizontal_R), 'uint8');
horizontal_colored_R = cast((ad_horizontal_R + ad_plus_R) .* randi([0 255], 1, 1), 'uint8');
%figure; imshow(R_bw_i - ad_plus_R - ad_horizontal_R)
horizontal_done_R = imcomplement(horizontal_sub_R + horizontal_colored_R);

horizontal_sub_G = cast(255 .* (G_bw_i - ad_plus_G - ad_horizontal_G), 'uint8');
horizontal_colored_G = cast((ad_horizontal_R + ad_plus_R) .* randi([0 255], 1, 1), 'uint8');
horizontal_done_G = imcomplement(horizontal_sub_G + horizontal_colored_G);

horizontal_sub_B = cast(255 .* (B_bw_i - ad_plus_B - ad_horizontal_B), 'uint8');
horizontal_colored_B = cast((ad_horizontal_R + ad_plus_R) .* randi([0 255], 1, 1), 'uint8');
horizontal_done_B = imcomplement(horizontal_sub_B + horizontal_colored_B);

horizontal_done = cat(3, horizontal_done_R, horizontal_done_G, horizontal_done_B);
%figure; imshow(horizontal_done)
% ---------------------

% Crosses 
crosses_sub_R = cast(255 .* (R_bw_i - ad_cross_R), 'uint8');
crosses_colored_R = cast(ad_cross_R .* randi([0 255], 1, 1), 'uint8');
crosses_done_R = imcomplement(crosses_sub_R + crosses_colored_R);

crosses_sub_G = cast(255 .* (G_bw_i - ad_cross_G), 'uint8');
crosses_colored_G = cast(ad_cross_G .* randi([0 255], 1, 1), 'uint8');
crosses_done_G = imcomplement(crosses_sub_G + crosses_colored_G);

crosses_sub_B = cast(255 .* (B_bw_i - ad_cross_B), 'uint8');
crosses_colored_B = cast(ad_cross_B .* randi([0 255], 1, 1), 'uint8');
crosses_done_B = imcomplement(crosses_sub_B + crosses_colored_B);

crosses_done = cat(3, crosses_done_R, crosses_done_G, crosses_done_B);
% ---------------------

% O's
O_sub_R = cast(255 .* (R_bw_i - ad_O_R), 'uint8');
O_colored_R = cast(ad_O_R .* randi([0 255], 1, 1), 'uint8');
O_done_R = imcomplement(O_sub_R + O_colored_R);

O_sub_G = cast(255 .* (G_bw_i - ad_O_G), 'uint8');
O_colored_G = cast(ad_O_G .* randi([0 255], 1, 1), 'uint8');
O_done_G = imcomplement(O_sub_G + O_colored_G);

O_sub_B = cast(255 .* (B_bw_i - ad_O_B), 'uint8');
O_colored_B = cast(ad_O_B .* randi([0 255], 1, 1), 'uint8');
O_done_B = imcomplement(O_sub_B + O_colored_B);

O_done = cat(3, O_done_R, O_done_G, O_done_B);
% ---------------------

% Solid Dots
solid_dot_sub_R = cast(255 .* (R_bw_i - ad_solid_dot_R), 'uint8');
solid_dot_colored_R = cast(ad_solid_dot_R .* randi([0 255], 1, 1), 'uint8');
solid_dot_done_R = imcomplement(solid_dot_sub_R + solid_dot_colored_R);

solid_dot_sub_G = cast(255 .* (G_bw_i - ad_solid_dot_G), 'uint8');
solid_dot_colored_G = cast(ad_solid_dot_G .* randi([0 255], 1, 1), 'uint8');
solid_dot_done_G = imcomplement(solid_dot_sub_G + solid_dot_colored_G);

solid_dot_sub_B = cast(255 .* (B_bw_i - ad_solid_dot_B), 'uint8');
solid_dot_colored_B = cast(ad_solid_dot_B .* randi([0 255], 1, 1), 'uint8');
solid_dot_done_B = imcomplement(solid_dot_sub_B + solid_dot_colored_B);

solid_dot_done = cat(3, solid_dot_done_R, solid_dot_done_G, solid_dot_done_B);
% ---------------------

% Pluses
plus_sub_R = cast(255 .* (R_bw_i - ad_plus_R), 'uint8');
plus_colored_R = cast(ad_plus_R .* randi([0 255], 1, 1), 'uint8');
plus_done_R = imcomplement(plus_sub_R + plus_colored_R);
%figure; imshow(R_bw_i - ad_plus_R);

plus_sub_G = cast(255 .* (G_bw_i - ad_plus_G), 'uint8');
plus_colored_G = cast(ad_plus_G .* randi([0 255], 1, 1), 'uint8');
plus_done_G = imcomplement(plus_sub_G + plus_colored_G);

plus_sub_B = cast(255 .* (B_bw_i - ad_plus_B), 'uint8');
plus_colored_B = cast(ad_plus_B .* randi([0 255], 1, 1), 'uint8');
plus_done_B = imcomplement(plus_sub_B + plus_colored_B);

plus_done = cat(3, plus_done_R, plus_done_G, plus_done_B);
%figure; imshow(plus_done)
% ---------------------

% Forward Slashes
forward_slash_sub_R = cast(255 .* (R_bw_i - ad_forward_slash_R), 'uint8');
forward_slash_colored_R = cast(ad_forward_slash_R .* randi([0 255], 1, 1), 'uint8');
forward_slash_done_R = imcomplement(forward_slash_sub_R + forward_slash_colored_R);

forward_slash_sub_G = cast(255 .* (G_bw_i - ad_forward_slash_G), 'uint8');
forward_slash_colored_G = cast(ad_forward_slash_G .* randi([0 255], 1, 1), 'uint8');
forward_slash_done_G = imcomplement(forward_slash_sub_G + forward_slash_colored_G);

forward_slash_sub_B = cast(255 .* (B_bw_i - ad_forward_slash_B), 'uint8');
forward_slash_colored_B = cast(ad_forward_slash_B .* randi([0 255], 1, 1), 'uint8');
forward_slash_done_B = imcomplement(forward_slash_sub_B + forward_slash_colored_B);

forward_slash_done = cat(3, forward_slash_done_R, forward_slash_done_G, forward_slash_done_B);
% ---------------------

% Back Slashes
back_slash_sub_R = cast(255 .* (R_bw_i - ad_back_slash_R), 'uint8');
back_slash_colored_R = cast(ad_back_slash_R .* randi([0 255], 1, 1), 'uint8');
back_slash_done_R = imcomplement(back_slash_sub_R + back_slash_colored_R);

back_slash_sub_G = cast(255 .* (G_bw_i - ad_back_slash_G), 'uint8');
back_slash_colored_G = cast(ad_back_slash_G .* randi([0 255], 1, 1), 'uint8');
back_slash_done_G = imcomplement(back_slash_sub_G + back_slash_colored_G);

back_slash_sub_B = cast(255 .* (B_bw_i - ad_back_slash_B), 'uint8');
back_slash_colored_B = cast(ad_back_slash_B .* randi([0 255], 1, 1), 'uint8');
back_slash_done_B = imcomplement(back_slash_sub_B + back_slash_colored_B);

back_slash_done = cat(3, back_slash_done_R, back_slash_done_G, back_slash_done_B);
% ---------------------

% Vertical 
vertical_sub_R = cast(255 .* (R_bw_i - ad_vertical_R), 'uint8');
vertical_colored_R = cast(ad_vertical_R .* randi([0 255], 1, 1), 'uint8');
vertical_done_R = imcomplement(vertical_sub_R + vertical_colored_R);

vertical_sub_G = cast(255 .* (G_bw_i - ad_vertical_G), 'uint8');
vertical_colored_G = cast(ad_vertical_G .* randi([0 255], 1, 1), 'uint8');
vertical_done_G = imcomplement(vertical_sub_G + vertical_colored_G);

vertical_sub_B = cast(255 .* (B_bw_i - ad_vertical_B), 'uint8');
vertical_colored_B = cast(ad_vertical_B .* randi([0 255], 1, 1), 'uint8');
vertical_done_B = imcomplement(vertical_sub_B + vertical_colored_B);

vertical_done = cat(3, vertical_done_R, vertical_done_G, vertical_done_B);
% ---------------------

final_image = crosses_done + O_done + solid_dot_done + plus_done + forward_slash_done + back_slash_done + horizontal_done + vertical_done;
figure; imshow(final_image)
imwrite(final_image,'p6_search_final.png')
