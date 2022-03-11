//insert your code in Part_1/p1_opencv_code.cpp
//edit the file extension and web template to match your programing language
// Headers
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


// compile command
// cl /EHsc hw2_files\Part_1\p1_opencv_code.cpp /I Y:\opencv\build\include /link /LIBPATH:Y:\opencv\build\x64\vc15\lib opencv_world455.lib



int main(int argc, char** argv)
{
	// Read the image file
	Mat originalImage = imread("hw2_files/p1_search.png");

	// Intiial property definitions
	int thresholdValue = 0;

	/**
	 * 0: binary
	 * 1: binary-inverted
	 * 2: truncate
	 * 3: to-zero
	 * 4: to-zero-inverted
	 */
	int thresholdType = 1;

	Mat greyImage;
	Mat threshImage;
	Mat croppedImage;
	Mat finalResultImage;
	int const MAX_TYPE = 4;
	int const MAX_BINARY = 255;

	// Check for failure
	if (originalImage.empty())
	{
		cout << "Could not open or find the image" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	// Greyscale image
	cvtColor(originalImage, greyImage, COLOR_BGR2GRAY);

	// Thresholded Image
	threshold(greyImage, threshImage, thresholdValue, MAX_BINARY, thresholdType);

	Size sizeThresh = threshImage.size();
	int rows = sizeThresh.height;
	int columns = sizeThresh.width;
	cout << "Size of thresholded image: " << sizeThresh << endl;
	cout << "  Height: " << rows << endl;
	cout << "  Width: " << columns << endl;

	int i, j;
	int x_left_offset = -1;
	int x_right_offset = -1;
	int y_top_offset = -1;
	int y_bottom_offset = -1;

	/*
	// Debug
	cout << threshImage << endl;


	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			printf("[%d, %d] = %f\n", i, j,threshData[i, j]);
		}

	*/

	// Get offsets.

	for (i = 0; i < columns; i++) {
		if (threshImage.at<uint8_t>(rows/2, i) == 255) {
			x_left_offset = i;
			break;
		}
	}

	for (i = columns - 1; i >= 0; i--) {
		if (threshImage.at<uint8_t>(rows / 2, i) == 255) {
			x_right_offset = i;
			break;
		}
	}

	for (i = 0; i < rows; i++) {
		if (threshImage.at<uint8_t>(i, columns / 2) == 255) {
			y_top_offset = i;
			break;
		}
	}

	for (i = rows - 1; i >= 0; i--) {
		if (threshImage.at<uint8_t>(i, columns / 2) == 255) {
			y_bottom_offset = i;
			break;
		}
	}

	// Debug
	printf("Matrix: %s %dx%d \n", typeToString(threshImage.type()).c_str(), threshImage.cols, threshImage.rows);

	// Create a region of interest and crop based on the offsets found above.
	Rect myROI(x_left_offset, y_top_offset, x_right_offset - x_left_offset, y_bottom_offset - y_top_offset);
	croppedImage = threshImage(myROI);

	bitwise_not(croppedImage, finalResultImage);

	// Window names
	String originalImageWindow = "Original Image";
	String greyImageWindow = "BW Image";
	String threshImageWindow = "Thresholded Image";
	String croppedImageWindow = "Cropped Image";
	String finalImageWindow = "Final Result Image";

	// Create Windows
	namedWindow(originalImageWindow);
	namedWindow(greyImageWindow);
	namedWindow(threshImageWindow);
	namedWindow(croppedImageWindow);
	namedWindow(finalImageWindow);

	// Show images inside created windows
	imshow(originalImageWindow, originalImage);
	imshow(greyImageWindow, greyImage);
	imshow(threshImageWindow, threshImage);
	imshow(croppedImageWindow, croppedImage);
	imshow(finalImageWindow, finalResultImage);

	// Write to disk
	imwrite("hw2_files/Part_1/p1_search_final_c++.png", finalResultImage);

	waitKey(0); // Wait for any keystroke in the window

	// Destroy the created window
	destroyWindow(originalImageWindow);
	destroyWindow(greyImageWindow);
	destroyWindow(threshImageWindow);
	destroyWindow(croppedImageWindow);
	destroyWindow(finalImageWindow);

	return 0;
}

