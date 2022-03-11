%insert your code in Part_2/p2_code.m
%edit the file extension and web template to match your programing language

%insert your code in Part_1/p1_matlab_code.m

% Read in image.
a = imread('../p2_search.png');

% Convert to binary image and invert.
b = im2bw(a, 0.5);
bi = ~b;
%figure; imshow(bi)

% Get size of given image.
[rows, columns] = size(bi);

x_left_offset = -1;
x_right_offset = -1;
y_top_offset = -1;
y_bottom_offset = -1;

% Find offsets for image to crop.
for i = 1:columns
    if bi(rows/2, i) == 1
        x_left_offset = i;
        break
    end
end

for i = columns:-1:1
    if bi(rows/2, i) == 1
        x_right_offset = i;
        break
    end
end

for i = 1:rows
    if bi(i, columns/2) == 1
        y_top_offset = i;
        break
    end
end

for i = rows:-1:1
    if bi(i, columns/2) == 1
        y_bottom_offset = i;
        break
    end
end

% Use image crop function with given offsets and width/height computation
% to generate result.
cropped = imcrop(bi, [x_left_offset, y_top_offset, x_right_offset - x_left_offset, y_bottom_offset - y_top_offset]);
%figure; imshow(cropped)

se_horiz = strel('line', 50, 0)
se_vert = strel('line', 50, 90)

ae0 = imerode(cropped, se_horiz);
ad0 = imdilate(ae0, se_horiz);
%figure; imshow(ad0)

ae1 = imerode(cropped, se_vert);
ad1 = imdilate(ae1, se_vert);
%figure; imshow(ad1)

% Show only grid without symbols.
result_1 = ad0 + ad1;
figure; imshow(result_1)
result_1i = ~result_1;
figure; imshow(result_1i)

% Show only symbols without grid.
result_2 = cropped - result_1;
result_2p = im2bw(result_2, 0.5);
%figure; imshow(result_2p)
result_2i = ~result_2p;
figure; imshow(result_2i)

% Write both to disc.
imwrite(result_1i,'p2_search_final_gridonly.png')
imwrite(result_2i,'p2_search_final_symbolonly.png')
