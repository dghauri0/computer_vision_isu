%insert your code in Part_5/p5_code.m
%edit the file extension and web template to match your programing language

% Read in image.
main = imread('../p5_search.png');

% Split multi-channeled (color) image into separate discrete channels.
[R,G,B] = imsplit(main);

% Setup channels for modification (binarize and invert).
R_bw = im2bw(R, 0.5);
G_bw = im2bw(G, 0.5);
B_bw = im2bw(B, 0.5);
R_bw_i = ~R_bw;
G_bw_i = ~G_bw;
B_bw_i = ~B_bw;

% Read in symbols, binarize, and invert.
cross = imread('../../Symbol_Cutouts/X.png');
O = imread('../../Symbol_Cutouts/O.png');
solid_dot = imread('../../Symbol_Cutouts/dot.png')
cross_b = im2bw(cross);
cross_bi = ~cross_b;
O_b = im2bw(O);
O_bi = ~O_b;
solid_dot_b = im2bw(solid_dot);
solid_dot_bi = ~solid_dot_b;
%figure; imshow(cross_bi)

% Erode with a subsequent dilate to pull out symbols.
ae_R = imerode(R_bw_i, cross_bi);
ae_G = imerode(G_bw_i, O_bi);
ae_B = imerode(B_bw_i, solid_dot_bi);

ad_R = imdilate(ae_R, cross_bi);
ad_G = imdilate(ae_G, O_bi);
ad_B = imdilate(ae_B, solid_dot_bi);

% Subtract each respective symbol from channels and multiply by 255 (I 
% decided to keep it simple and just do 255 for each symbol in each
% respective channel to give the symbols Red, Green, and Blue colors). 
crosses_sub_R = R_bw_i - ad_R;
crosses_sub_Ri = ~crosses_sub_R;
crosses_sub_Ri_gray = crosses_sub_Ri .* 255;

O_sub_G = G_bw_i - ad_G;
O_sub_Gi = ~O_sub_G;
O_sub_Gi_gray = O_sub_Gi .* 255;

solid_dot_sub_B = B_bw_i - ad_B;
solid_dot_sub_Bi = ~solid_dot_sub_B;
solid_dot_sub_Bi_gray = solid_dot_sub_Bi .* 255;


% Show final figures and write to disk. 
%figure; imshow(crosses_sub_Ri_gray)
%figure; imshow(O_sub_Gi_gray)
%figure; imshow(solid_dot_sub_Bi_gray)
final = cat(3, crosses_sub_Ri_gray, O_sub_Gi_gray, solid_dot_sub_Bi_gray);
figure; imshow(final)
imwrite(final,'p5_search_final.png')

