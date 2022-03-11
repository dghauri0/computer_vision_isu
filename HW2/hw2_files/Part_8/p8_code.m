%insert your code in Part_8/p8_code.m
%edit the file extension and web template to match your programing language

% Read in main image.
main = imread('../p8_search.png');

% Read in symbol images.
O = imread('../../Symbol_Cutouts/O.png');
plus = imread('../../Symbol_Cutouts/plus.png');
cross = imread('../../Symbol_Cutouts/X.png');
dot = imread('../../Symbol_Cutouts/dot.png');
backslash = imread('../../Symbol_Cutouts/backslash.png');
forward_slash = imread('../../Symbol_Cutouts/slash.png');
horizontal = imread('../../Symbol_Cutouts/horizontal.png');
vertical = imread('../../Symbol_Cutouts/vertical.png');

% Some strel definitions (for grid)
se_horiz = strel('line', 50, 0);
se_vert = strel('line', 50, 90);

% Binarize and invert. 
main_bw = im2bw(main, 0.5);
main_bw_i = ~main_bw;
O_bw = im2bw(O, 0.5);
O_bw_i = ~O_bw;
plus_bw = im2bw(plus, 0.5);
plus_bw_i = ~plus_bw;
cross_bw = im2bw(cross, 0.5);
cross_bw_i = ~cross_bw;
dot_bw = im2bw(dot, 0.5);
dot_bw_i = ~dot_bw;
backslash_bw = im2bw(backslash, 0.5);
backslash_bw_i = ~backslash_bw;
forward_slash_bw = im2bw(forward_slash, 0.5);
forward_slash_bw_i = ~forward_slash_bw;
horizontal_bw = im2bw(horizontal, 0.5);
horizontal_bw_i = ~horizontal_bw;
vertical_bw = im2bw(vertical, 0.5);
vertical_bw_i = ~vertical_bw;

% Pull out grid lines.
e_vert = imerode(main_bw_i, se_vert);
d_vert = imdilate(e_vert, se_vert);
e_horiz = imerode(main_bw_i, se_horiz);
d_horiz = imdilate(e_horiz, se_horiz);

grid_only = d_vert + d_horiz;
symbols_only = main_bw_i - grid_only;

% Switch symbols
% O -> +
% + -> .
% . -> /
% / -> \
% \ -> x
% x -> -
% - -> |
% | -> O

% O -> +
e0 = imerode(symbols_only, O_bw_i);
d0 = imdilate(e0, plus_bw_i);
d0_orig = imdilate(e0, O_bw_i);
%figure; imshow(d0)

% + -> .
e1 = imerode(symbols_only, plus_bw_i);
d1 = imdilate(e1, dot_bw_i);
d1_orig = imdilate(e1, plus_bw_i);
%figure; imshow(d1)

% . -> /
e2 = imerode(symbols_only, dot_bw_i);
d2 = imdilate(e2, forward_slash_bw_i);
d2_orig = imdilate(e2, dot_bw_i);
%figure; imshow(d2)

% / -> \
e3 = imerode(symbols_only, forward_slash_bw_i);
d3 = imdilate(e3, backslash_bw_i);
d3_orig = imdilate(e3, forward_slash_bw_i);
%figure; imshow(d3)

% \ -> x
e4 = imerode(symbols_only, backslash_bw_i);
d4 = imdilate(e4, cross_bw_i);
d4_orig = imdilate(e4, backslash_bw_i);
%figure; imshow(d4)

% x -> -
e5 = imerode(symbols_only, cross_bw_i);
d5 = imdilate(e5, horizontal_bw_i);
d5_orig = imdilate(e5, cross_bw_i);
%figure; imshow(d5)

% - -> |
e6 = imerode(symbols_only - d1_orig, horizontal_bw_i);
d6 = imdilate(e6, vertical_bw_i);
d6_orig = imdilate(e6, horizontal_bw_i);

[rows, columns] = size(d6);

% Some weird behavior happening with infinite values.
for i = 1:rows
    for j = 1:columns
        if d6(i, j) == Inf
            d6(i, j) = 0;
        end
    end
end

% | -> O
e7 = imerode(symbols_only, vertical_bw_i);
d7 = imdilate(e7, O_bw_i);
d7_orig = imdilate(e7, vertical_bw_i);
%figure; imshow(d7)

new_symbols_only = d0 + d1 + d2 + d3 + d4 + d5 + d6 + d7;
grid_added = new_symbols_only + grid_only;

% Again...
for i = 1:rows
    for j = 1:columns
        if grid_added(i, j) == -Inf
            grid_added(i, j) = 0;
        end
    end
end

final = ~grid_added;
figure; imshow(final)
imwrite(final,'p8_search_final.png')
