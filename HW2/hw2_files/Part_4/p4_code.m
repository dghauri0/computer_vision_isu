%insert your code in Part_4/p4_code.m
%edit the file extension and web template to match your programing language

% Read in image.
main = imread('../p4_search.png');

% Split multi-channeled (color) image into separate discrete channels.
[R,G,B] = imsplit(main);

% Setup channels for modification (binarize and invert).
R_bw = im2bw(R, 0.5);
G_bw = im2bw(G, 0.5);
B_bw = im2bw(B, 0.5);
R_bw_i = ~R_bw;
G_bw_i = ~G_bw;
B_bw_i = ~B_bw;

% Read in cross, binarize, and invert.
cross = imread('../../Symbol_Cutouts/X.png');
cross_b = im2bw(cross);
cross_bi = ~cross_b;
%figure; imshow(cross_bi)

% Erode with a subsequent dilate to pull out crosses (we really only care
% to work on G and B channels as those are the one's we'll set to 0
% for the crosses).
ae_R = imerode(R_bw_i, cross_bi);
ae_G = imerode(G_bw_i, cross_bi);
ae_B = imerode(B_bw_i, cross_bi);

ad_R = imdilate(ae_R, cross_bi);
ad_G = imdilate(ae_G, cross_bi);
ad_B = imdilate(ae_B, cross_bi);

% Subtract crosses from the red channel (we want to make them 255 to make
% it so the end RGB values are 255, 0, 0 respectively for red). 
crosses_sub_R = R_bw_i - ad_R;
crosses_sub_Ri = ~crosses_sub_R;
crosses_sub_Ri_gray = crosses_sub_Ri .* 255;

% Show final figures and write to disk. 
figure; imshow(crosses_sub_Ri)
final = cat(3, crosses_sub_Ri_gray, G, B);
figure; imshow(final)
imwrite(final,'p4_search_final.png')

