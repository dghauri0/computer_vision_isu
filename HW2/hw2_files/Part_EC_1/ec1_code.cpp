//insert your code in Part_EC_1/ec1_code.cpp
//edit the file extension and web template to match your programing language
// 
// Headers
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <inttypes.h>

using namespace cv;
using namespace std;

// Define a pixel
typedef Point3_<uint8_t> Pixel;

Mat symbols[8];
Mat symbols_rgb[8][3];
Mat symbols_bi[8];
Mat symbols_bi_inv[8];
Size symbol_size[8];

// compile command
// cl /EHsc hw2_files\Part_EC_1\ec1_code.cpp /I Y:\opencv\build\include /link /LIBPATH:Y:\opencv\build\x64\vc15\lib opencv_world455.lib

// Function Declarations
void OperateOnRow(int top_row_index, int bottom_row_index, Mat& binaryImage, Mat& binaryImageInverted, Mat& r, Mat& g, Mat& b, int cropped_rows, int cropped_columns);
void show_wait_destroy(const char* winname, cv::Mat img);

int main(int argc, char** argv)
{
	// Read the image file
	Mat originalImage = imread("hw2_files/ec1_search.png");
	symbols[0] = imread("Symbol_Cutouts/backslash.png");
	symbols[1] = imread("Symbol_Cutouts/dot.png");
	symbols[2] = imread("Symbol_Cutouts/horizontal.png");
	symbols[3] = imread("Symbol_Cutouts/O.png");
	symbols[4] = imread("Symbol_Cutouts/plus.png");
	symbols[5] = imread("Symbol_Cutouts/slash.png");
	symbols[6] = imread("Symbol_Cutouts/vertical.png");
	symbols[7] = imread("Symbol_Cutouts/X.png");


	// Intiial property definitions
	int thresholdValue = 0;

	/**
	 * 0: binary
	 * 1: binary-inverted
	 * 2: truncate
	 * 3: to-zero
	 * 4: to-zero-inverted
	 */
	int thresholdType = 0;

	int i, j;
	Mat rgb[3];
	Mat greyImage;
	Mat binaryImage;
	Mat binaryImageInverted;
	int const MAX_TYPE = 4;
	int const MAX_BINARY = 255;
	int const BORDER_THICKNESS = 4;

	// Check for failure on original image.
	if (originalImage.empty())
	{
		cout << "Could not open or find the image" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	for (i = 0; i < sizeof(symbols) / sizeof(symbols[0]); i++) {
		// Check for failure on symbols.
		if (symbols[i].empty())
		{
			cout << "Could not open or find the symbol image" << endl;
			cin.get(); //wait for any key press
			return -1;
		}
	}

	// Split symbols into their respective RGB channels. Also create a binary equivalent and get sizes.
	for (i = 0; i < 8; i++) {
		split(symbols[i], symbols_rgb[i]);
		Mat temp;
		cvtColor(symbols[i], temp, COLOR_BGR2GRAY);
		threshold(temp, symbols_bi[i], thresholdValue, MAX_BINARY, thresholdType);
		threshold(temp, symbols_bi_inv[i], thresholdValue, MAX_BINARY, 1);
		symbol_size[i] = symbols_bi[i].size();
	}


	// Greyscale image
	cvtColor(originalImage, greyImage, COLOR_BGR2GRAY);

	// Thresholded Image (Binary Image)
	threshold(greyImage, binaryImage, thresholdValue, MAX_BINARY, thresholdType);

	// Thresholded Image (Binary Image Inverted)
	threshold(greyImage, binaryImageInverted, thresholdValue, MAX_BINARY, 1);

	// Split original image into channels
	split(originalImage, rgb);

	Size sizeThresh = rgb[0].size();
	int rows = sizeThresh.height;
	int columns = sizeThresh.width;
	cout << "Size of thresholded image: " << sizeThresh << endl;
	cout << "  Height: " << rows << endl;
	cout << "  Width: " << columns << endl;

	int x_left_offset = -1;
	int x_right_offset = -1;
	int y_top_offset = -1;
	int y_bottom_offset = -1;

	// Get offsets.
	for (i = 0; i < columns; i++) {
		if (binaryImage.at<uint8_t>(rows / 2, i) == 0) {
			x_left_offset = i;
			break;
		}
	}

	for (i = columns - 1; i >= 0; i--) {
		if (binaryImage.at<uint8_t>(rows / 2, i) == 0) {
			x_right_offset = i;
			break;
		}
	}

	for (i = 0; i < rows; i++) {
		if (binaryImage.at<uint8_t>(i, columns / 2) == 0) {
			y_top_offset = i;
			break;
		}
	}

	for (i = rows - 1; i >= 0; i--) {
		if (binaryImage.at<uint8_t>(i, columns / 2) == 0) {
			y_bottom_offset = i;
			break;
		}
	}


	// Debug
	printf("Matrix: %s %dx%d \n", typeToString(binaryImage.type()).c_str(), binaryImage.cols, binaryImage.rows);

	// Create a region of interest and crop based on the offsets found above.
	Rect myROI(x_left_offset, y_top_offset, x_right_offset - x_left_offset, y_bottom_offset - y_top_offset);
	binaryImage = binaryImage(myROI);
	binaryImageInverted = binaryImageInverted(myROI);
	rgb[0] = rgb[0](myROI);
	rgb[1] = rgb[1](myROI);
	rgb[2] = rgb[2](myROI);

	// Create structure element for extracting horizontal lines
	Mat horizontalStructure = getStructuringElement(MORPH_RECT, Size(50, 1));

	// Create structure element for extracting vertical lines
	Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, 50));

	Mat horizontalGridLines;
	Mat verticalGridLines;

	// Apply morphology operations - horizontal
	erode(binaryImageInverted, horizontalGridLines, horizontalStructure, Point(-1, -1));
	dilate(horizontalGridLines, horizontalGridLines, horizontalStructure, Point(-1, -1));

	// Apply morphology operations - vertical
	erode(binaryImageInverted, verticalGridLines, verticalStructure, Point(-1, -1));
	dilate(verticalGridLines, verticalGridLines, verticalStructure, Point(-1, -1));

	// Show extracted horizontal lines
	//show_wait_destroy("Lines Abstracted - Horizontal", horizontalGridLines);
	//show_wait_destroy("Lines Abstracted - Vertical", verticalGridLines);

	Mat gridLinesOnly = horizontalGridLines + verticalGridLines; // Can I do this? YES THANK YOU C++ FOR NOT BEING STUPID
	//show_wait_destroy("Grid Only", gridLinesOnly);

	// Only keep symbols
	binaryImageInverted = binaryImageInverted - gridLinesOnly;
	//show_wait_destroy("Symbols Only", binaryImageInverted);

	// Get rid of grid lines in rgb channels (temp) so it's easy to color in pixels later.
	bitwise_xor(rgb[0], gridLinesOnly, rgb[0]);
	bitwise_xor(rgb[1], gridLinesOnly, rgb[1]);
	bitwise_xor(rgb[2], gridLinesOnly, rgb[2]);

	printf("Cropped Matrix: %s %dx%d \n", typeToString(binaryImage.type()).c_str(), binaryImage.cols, binaryImage.rows);
	Size sizeBI = binaryImage.size();
	int cropped_rows = sizeBI.height;
	int cropped_columns = sizeBI.width;

	int temp = 0;
	int top_of_row = 0;
	int bottom_of_row = -1;
	for (i = 0; i < cropped_rows + 1; i++) {
		if (binaryImage.at<uint8_t>(i, cropped_columns - 12) == 0) {
			temp++;
		}

		//cout << "cropped_rows: " << cropped_rows << endl;
		//cout << "cropped_columns: " << cropped_columns << endl;
		//cout << "temp: " << temp << endl;

		if (temp % 4 == 0 && binaryImage.at<uint8_t>(i, cropped_columns - 12) == 0 && i != 3) {
			bottom_of_row = i;
			OperateOnRow(top_of_row, bottom_of_row, binaryImage, binaryImageInverted, rgb[2], rgb[1], rgb[0], cropped_rows, cropped_columns);
			cout << "top of row: " << top_of_row << ", bottom of row: " << bottom_of_row << ", i: " << i << ", temp: " << temp << endl;
			top_of_row = bottom_of_row;
			bottom_of_row = -1;
			temp = 0;
		}

	}

	// Add back grid lines.
	bitwise_xor(rgb[0], gridLinesOnly, rgb[0]);
	bitwise_xor(rgb[1], gridLinesOnly, rgb[1]);
	bitwise_xor(rgb[2], gridLinesOnly, rgb[2]);
	bitwise_xor(binaryImageInverted, gridLinesOnly, binaryImageInverted);

	// Debug
	//printf("%u\n", croppedImage.at<uint8_t>(0, 0));
	//printf("%u\n", croppedImage.at<uint8_t>(12, 12));
	Mat final_image;
	bitwise_not(binaryImageInverted, final_image);

	// Window names
	String binaryImageWindow = "Binary Image Window";
	String binaryImageInvertedWindow = "Binary Image Inverted Window";

	/*
	String redChannelWindow = "Red Channel Window";
	String greenChannelWindow = "Blue Channel Window";
	String blueChannelWindow = "Green Channel Window";
	*/
	String finalImageWindow = "Final Image Window";



	// Create Windows
	namedWindow(binaryImageWindow);
	namedWindow(binaryImageInvertedWindow);

	/*
	namedWindow(redChannelWindow);
	namedWindow(greenChannelWindow);
	namedWindow(blueChannelWindow);
	*/
	namedWindow(finalImageWindow);



	// Show images inside created windows
	imshow(binaryImageWindow, binaryImage);
	imshow(binaryImageInvertedWindow, binaryImageInverted);

	/*
	imshow(redChannelWindow, rgb[2]);
	imshow(greenChannelWindow, rgb[1]);
	imshow(blueChannelWindow, rgb[0]);
	*/
	imshow(finalImageWindow, final_image);


	imwrite("hw2_files/Part_EC_1/ec1_search_final.png", final_image);

	printf("Here\n");

	waitKey(0); // Wait for any keystroke in the window

	// Destroy the created window
	destroyWindow(binaryImageWindow);
	destroyWindow(binaryImageInvertedWindow);

	/*
	destroyWindow(redChannelWindow);
	destroyWindow(greenChannelWindow);
	destroyWindow(blueChannelWindow);
	*/
	destroyWindow(finalImageWindow);

	return 0;
}


void OperateOnRow(int top_row_index, int bottom_row_index, Mat& binaryImage, Mat& binaryImageInverted, Mat& r, Mat& g, Mat& b, int cropped_rows, int cropped_columns) {

	//show_wait_destroy("Referenced Binary Image Inverted", binaryImageInverted);

	// Create a region of interest focused on the specific row to operate on.
	Rect myROI(0, top_row_index, cropped_columns, bottom_row_index - top_row_index);
	Mat rowFocused = binaryImageInverted(myROI);
	Mat rowFocusedOrig = binaryImage(myROI);
	cout << "Row ROI: " << myROI << endl;

	// Debug
	/*
	String rowCheckWindow = "rowCheck Window";
	namedWindow(rowCheckWindow);
	imshow(rowCheckWindow, rowFocused);
	waitKey(0);
	destroyWindow(rowCheckWindow);

	// Debug
	String rowCheckWindowOrig = "rowCheck Orig Window";
	namedWindow(rowCheckWindowOrig);
	imshow(rowCheckWindowOrig, rowFocusedOrig);
	waitKey(0);
	destroyWindow(rowCheckWindowOrig);
	*/

	int i, j, k, l, m, n, o;

	// Retrieved from MATLAB because I am so far behind it's not even funny.
	int cell_width_x0[] = { 0,  64,  127, 190, 253, 316, 379, 442, 505, 568, 630, 693, 756, 819, 882 };
	int cell_width_x1[] = { 67, 130, 193, 256, 319, 382, 445, 508, 571, 633, 696, 759, 822, 885, 947 }; // 948 - Discrepancy

	/*
	Index: Symbol
	0: backslash
	1: dot
	2: horizontal
	3: O
	4: plus
	5: slash
	6: vertical
	7: X
	*/

	// Count of symbols found.
	int symbol_found[] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	// Sequence of symbols in row.
	int symbol_sequence[] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

	// Try catch block for debugging.
	try {

		// Look at each cell within the row.
		for (i = 0; i < (sizeof(cell_width_x0) / sizeof(cell_width_x0[0])); i++) {

			// Grab cell.
			Rect cellROI(cell_width_x0[i], top_row_index, cell_width_x1[i] - cell_width_x0[i], bottom_row_index - top_row_index);
			Mat cellFocused = binaryImageInverted(cellROI);
			cout << "Cell ROI: " << cellROI << endl;

			// Debug
			//String cellCheckWindow = "cellCheck Window";
			//namedWindow(cellCheckWindow);
			//imshow(cellCheckWindow, cellFocused);
			//waitKey(0);
			//destroyWindow(cellCheckWindow);

			int symbol_horizontal_flag = 0;
			// Go through each symbol with erosion and dilation and see if there is a match.
			for (j = 0; j < (sizeof(symbol_found) / sizeof(symbol_found[0])); j++) {

				Mat temp;
				erode(cellFocused, temp, symbols_bi_inv[j]);
				dilate(temp, temp, symbols_bi_inv[j]);
				Size sizeTemp = temp.size();


				// Debug
				//String dilateCheckWindow = "dilateCheck Window";
				//namedWindow(dilateCheckWindow);
				//imshow(dilateCheckWindow, temp);
				//waitKey(0);
				//destroyWindow(dilateCheckWindow);

				//cout << "Height: " << sizeTemp.height << endl;
				//cout << "Width: " << sizeTemp.width << endl;

				int flag = 0;
				int identified_symbol = -1;
				for (k = 0; k < sizeTemp.height; k++) {
					//cout << "Here k" << endl;

					for (l = 0; l < sizeTemp.width; l++) {
						//cout << "Here k" << endl;

						// Make sure all pixels are not black.
						if (temp.at<uint8_t>(k, l) != 0) {
							symbol_found[j]++;
							flag = 1;

							// Deal with if horizontal gets falsely identified with plus.
							if (j == 2) {
								symbol_horizontal_flag = 1;
							}

							if (j == 4 && symbol_horizontal_flag == 1) {
								symbol_found[2]--;
							}

							identified_symbol = j;
							symbol_sequence[i] = j;
							break;
						}
					}

					if (flag == 1) {
						break;
					}
				}
			}
		}
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << endl;
	}

	int symbolCountWithoutNegatives = 0;
	for (i = 0; i < (sizeof(symbol_sequence) / sizeof(symbol_sequence[0])); i++) {
		if (symbol_sequence[i] != -1) {
			symbolCountWithoutNegatives++;
		}
	}

	bool four_pattern = true;
	for (i = 0; i < symbolCountWithoutNegatives / 2; i++) {
		if (symbol_sequence[i] != symbol_sequence[i + 4]) {
			four_pattern = false;
		}
	}

	bool three_pattern = true;
	for (i = 0; i < symbolCountWithoutNegatives / 2; i++) {
		if (symbol_sequence[i] != symbol_sequence[i + 3]) {
			three_pattern = false;
		}
	}

	bool two_pattern = true;
	for (i = 0; i < symbolCountWithoutNegatives / 2; i++) {
		if (symbol_sequence[i] != symbol_sequence[i + 2]) {
			two_pattern = false;
		}
	}

	cout << "Non-Negative Count: " << symbolCountWithoutNegatives << endl;
	if (four_pattern) {
		cout << "Pattern Type: Four" << endl;
	}
	else if (three_pattern) {
		cout << "Pattern Type: Three" << endl;
	}
	else {
		cout << "Pattern Type: Two" << endl;
	}

	try {
		cout << "Cells in Row: " << (sizeof(symbol_sequence) / sizeof(symbol_sequence[0])) << endl;
		int test_count = 0;

		if (three_pattern) {
			i = 0;
			for (j = 6; j < 15; j++) {

				// Grab cell.
				Rect cellROI(cell_width_x0[i], top_row_index, cell_width_x1[i] - cell_width_x0[i], bottom_row_index - top_row_index);
				Mat cellFocused = binaryImageInverted(cellROI);
				cout << "Cell ROI: " << cellROI << endl;

				//show_wait_destroy("Cell", cellFocused);

				printf("Cell: %s %dx%d \n", typeToString(cellFocused.type()).c_str(), cellFocused.cols, cellFocused.rows);

				int cellPixelCount = (bottom_row_index - top_row_index) * (cell_width_x1[i] - cell_width_x0[i]);
				printf("cell pixel count: %d", cellPixelCount);

				// Copy i symbol to j
				for (m = top_row_index + 4; m < bottom_row_index - 4; m++) {
					for (n = cell_width_x0[j] + 4; n < cell_width_x1[j] - 4; n++) {
						binaryImageInverted.at<uchar>(m, n) = binaryImageInverted.at<uchar>(m, n - cell_width_x0[j] + cell_width_x0[i]);
					}
				}

				// Increment base symbol index.
				i++;

				// If we're greater than the base symbols, reset to 0. 
				if (i > 2) {
					i = 0;
				}
			}

		}
		else if (two_pattern) {
			i = 0;
			for (j = 4; j < 15; j++) {

				// Grab cell.
				Rect cellROI(cell_width_x0[i], top_row_index, cell_width_x1[i] - cell_width_x0[i], bottom_row_index - top_row_index);
				Mat cellFocused = binaryImageInverted(cellROI);
				cout << "Cell ROI: " << cellROI << endl;

				//show_wait_destroy("Cell", cellFocused);

				printf("Cell: %s %dx%d \n", typeToString(cellFocused.type()).c_str(), cellFocused.cols, cellFocused.rows);

				int cellPixelCount = (bottom_row_index - top_row_index) * (cell_width_x1[i] - cell_width_x0[i]);
				printf("cell pixel count: %d", cellPixelCount);

				// Copy i symbol to j
				for (m = top_row_index + 4; m < bottom_row_index - 4; m++) {
					for (n = cell_width_x0[j] + 4; n < cell_width_x1[j] - 4; n++) {
						binaryImageInverted.at<uchar>(m, n) = binaryImageInverted.at<uchar>(m, n - cell_width_x0[j] + cell_width_x0[i]);
					}
				}

				// Increment base symbol index.
				i++;

				// If we're greater than the base symbols, reset to 0. 
				if (i > 1) {
					i = 0;
				}
			}
		}
		else {
			i = 0;
			for (j = 8; j < 15; j++) {

				// Grab cell.
				Rect cellROI(cell_width_x0[i], top_row_index, cell_width_x1[i] - cell_width_x0[i], bottom_row_index - top_row_index);
				Mat cellFocused = binaryImageInverted(cellROI);
				cout << "Cell ROI: " << cellROI << endl;

				//show_wait_destroy("Cell", cellFocused);

				printf("Cell: %s %dx%d \n", typeToString(cellFocused.type()).c_str(), cellFocused.cols, cellFocused.rows);

				int cellPixelCount = (bottom_row_index - top_row_index) * (cell_width_x1[i] - cell_width_x0[i]);
				printf("cell pixel count: %d", cellPixelCount);

				// Copy i symbol to j
				for (m = top_row_index + 4; m < bottom_row_index - 4; m++) {
					for (n = cell_width_x0[j] + 4; n < cell_width_x1[j] - 4; n++) {
						binaryImageInverted.at<uchar>(m, n) = binaryImageInverted.at<uchar>(m, n - cell_width_x0[j] + cell_width_x0[i]);
					}
				}

				// Increment base symbol index.
				i++;

				// If we're greater than the base symbols, reset to 0. 
				if (i > 3) {
					i = 0;
				}
			}
		}

		cout << "Test_Count: " << test_count << endl;
	}
	catch (exception& e) {
		cout << "Exception: " << e.what() << endl;
	}

	// Debug
	for (i = 0; i < (sizeof(symbol_found) / sizeof(symbol_found[0])); i++) {
		cout << "Symbol " << i << " Found: " << symbol_found[i] << endl;

	}

	// Debug
	cout << "Symbol Sequence for Row: " << endl;
	for (i = 0; i < (sizeof(symbol_sequence) / sizeof(symbol_sequence[0])); i++) {
		cout << "Symbol: " << symbol_sequence[i] << endl;

	}

	waitKey(0);


	/*
	String testImageWindow = "Test Image Window";
	namedWindow(testImageWindow);
	imshow(testImageWindow, r);
	waitKey(0);
	destroyWindow(testImageWindow);
	*/

}

// Taken from openCV documentation page for quick debug.
void show_wait_destroy(const char* winname, cv::Mat img) {
	imshow(winname, img);
	moveWindow(winname, 500, 0);
	waitKey(0);
	destroyWindow(winname);
}