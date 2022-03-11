%insert your code in Part_3/p3_code.m
%edit the file extension and web template to match your programing language
% Read in image.
main = imread('../p3_search.png');

% Convert to binary image and invert.
b = im2bw(main, 0.5);
bi = ~b;

% Get size of given image.
[rows, columns] = size(bi);

x_left_offset = -1;
x_right_offset = -1;
y_top_offset = -1;
y_bottom_offset = -1;

% Find offsets for image to crop.
for i = 1:columns
    if bi(round(rows/2), i) == 1
        x_left_offset = i;
        break
    end
end

for i = columns:-1:1
    if bi(round(rows/2), i) == 1
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
cropped = imcrop(main, [x_left_offset, y_top_offset, x_right_offset - x_left_offset, y_bottom_offset - y_top_offset]);
cropped_b = imcrop(b, [x_left_offset, y_top_offset, x_right_offset - x_left_offset, y_bottom_offset - y_top_offset]);

%figure; imshow(cropped)
%figure; imshow(cropped_b)

% Convert to binary image and invert.
[R, G, B] = imsplit(cropped);

%figure; imshow(R)
%figure; imshow(G)
%figure; imshow(B)

% Generate single square
flag_row = 0;
flag_column = 0;
by_offset = -1;
bx_offset = -1;
for i = 32:columns
    if(cropped_b(32, i) == 0)
        flag_column = flag_column + 1;
    end
    
    if(flag_column == 4)
        by_offset = i;
        break
    end
end

for i = 32:rows
    if(cropped_b(i, 32) == 0)
        flag_row = flag_row + 1;
    end
    
    if(flag_row == 4)
        bx_offset = i;
        break
    end
end

square_bw = imcrop(cropped_b, [1, 1, by_offset - 1, bx_offset - 1]);

square_bw_gray = square_bw .* 255;
%figure; imshow(square_bw)

[square_rows, square_columns] = size(square_bw);
[cropped_rows, cropped_columns] = size(cropped_b);

% Sweep single square across grid and color based on rand generation.
for i = 1:square_rows-4:rows
    for j = 1:square_columns-4:columns
        R_rand_value = randi([0 255], 1, 1);
        G_rand_value = randi([0 255], 1, 1);
        B_rand_value = randi([0 255], 1, 1);
        for k = i:i+square_rows
            for l = j:j+square_columns
                if (k < cropped_rows && l < cropped_columns)
                    if(R(k,l) ~= 0)
                        R(k,l) = R_rand_value;
                        G(k,l) = G_rand_value;
                        B(k,l) = B_rand_value;
                    end
                end
            end
        end
    end
end

% Combine each R, G, B channel into single image.
colored_image = cat(3, R, G, B);

figure; imshow(R)
figure; imshow(G)
figure; imshow(B)
figure; imshow(colored_image)


imwrite(colored_image,'p3_search_final.png')