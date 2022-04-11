// Your code goes in this file.

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
// cl /EHsc part1\p1b_code.cpp /I Y:\CodeLib\opencv\build\include /link /LIBPATH:Y:\CodeLib\opencv\build\x64\vc15\lib opencv_world455.lib

// Function Declarations
void OperateOnRow(int top_row_index, int bottom_row_index, Mat& binaryImage, Mat& binaryImageInverted, Mat& r, Mat& g, Mat& b, int cropped_rows, int cropped_columns);
void show_wait_destroy(const char* winname, cv::Mat img);

int main(int argc, char** argv)
{
	// Read the image file
	Mat originalImage = imread("part1/p1_image1.png");

	// Check for failure on original image.
	if (originalImage.empty())
	{
		cout << "Could not open or find the image" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	Mat grayImage;
	cvtColor(originalImage, grayImage, COLOR_BGR2GRAY);
	medianBlur(grayImage, grayImage, 5);
	vector<Vec3f> circles;
	HoughCircles(grayImage, circles, HOUGH_GRADIENT, 1, grayImage.rows / 20, 100, 25, 45, 50);

	
	for (size_t i = 0; i < circles.size(); i++)
	{
		Vec3i c = circles[i];
		Point center = Point(c[0], c[1]);
		// circle center
		//circle(originalImage, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
		// circle outline
		int radius = c[2];
		circle(originalImage, center, radius, Scalar(255, 0, 255), 3, LINE_AA);
	}
	

	//imshow("Detected circles", originalImage);
	//waitKey();

	// Window names
	String finalImageWindow = "Final Image Window";

	// Create Windows
	namedWindow(finalImageWindow);

	// Show images inside created windows
	imshow(finalImageWindow, originalImage);

	waitKey(0); // Wait for any keystroke in the window

	imwrite("part1/p1_image1_final_c++.png", originalImage);

	// Destroy the created window
	destroyWindow(finalImageWindow);

	return 0;
}



// Taken from openCV documentation page for quick debug.
void show_wait_destroy(const char* winname, cv::Mat img) {
	imshow(winname, img);
	moveWindow(winname, 500, 0);
	waitKey(0);
	destroyWindow(winname);
}