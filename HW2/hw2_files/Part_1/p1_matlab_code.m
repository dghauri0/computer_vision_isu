%insert your code in Part_1/p1_matlab_code.m

% Read in image.
a = imread('../p1_search.png');

% Convert to binary image and invert.
b = im2bw(a, 0.5);
bi = ~b;
figure; imshow(bi)

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
result = imcrop(bi, [x_left_offset, y_top_offset, x_right_offset - x_left_offset, y_bottom_offset - y_top_offset])
figure; imshow(result)

% Invert back.
resulti = ~result;
figure; imshow(resulti)

% Write final answer to disk.
imwrite(resulti,'p1_search_final_matlab.png')