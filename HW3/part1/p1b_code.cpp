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
	Mat originalImage0 = imread("part1/p1_image1.png");
	Mat originalImage1 = imread("part1/p1_image2.png");
	Mat originalImage2 = imread("part1/p1_image3.png");

	// Check for failure on original image.
	if (originalImage0.empty() || originalImage1.empty() || originalImage2.empty())
	{
		cout << "Could not open or find the image" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	Mat grayImage0;
	cvtColor(originalImage0, grayImage0, COLOR_BGR2GRAY);
	medianBlur(grayImage0, grayImage0, 5);
	vector<Vec3f> circles0;
	HoughCircles(grayImage0, circles0, HOUGH_GRADIENT, 1, grayImage0.rows / 20, 100, 25, 45, 50);

	Mat grayImage1;
	cvtColor(originalImage1, grayImage1, COLOR_BGR2GRAY);
	medianBlur(grayImage1, grayImage1, 5);
	vector<Vec3f> circles1;
	HoughCircles(grayImage1, circles1, HOUGH_GRADIENT, 1, grayImage1.rows / 20, 100, 25, 45, 50);

	Mat grayImage2;
	cvtColor(originalImage2, grayImage2, COLOR_BGR2GRAY);
	medianBlur(grayImage2, grayImage2, 5);
	vector<Vec3f> circles2;
	HoughCircles(grayImage2, circles2, HOUGH_GRADIENT, 1, grayImage2.rows / 20, 100, 25, 45, 50);

	
	for (size_t i = 0; i < circles0.size(); i++)
	{
		Vec3i c = circles0[i];
		Point center = Point(c[0], c[1]);
		// circle center
		//circle(originalImage, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
		// circle outline
		int radius = c[2];
		circle(originalImage0, center, radius, Scalar(255, 0, 255), 3, LINE_AA);
	}

	for (size_t i = 0; i < circles1.size(); i++)
	{
		Vec3i c = circles1[i];
		Point center = Point(c[0], c[1]);
		// circle center
		//circle(originalImage, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
		// circle outline
		int radius = c[2];
		circle(originalImage1, center, radius, Scalar(255, 0, 255), 3, LINE_AA);
	}

	for (size_t i = 0; i < circles2.size(); i++)
	{
		Vec3i c = circles2[i];
		Point center = Point(c[0], c[1]);
		// circle center
		//circle(originalImage, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
		// circle outline
		int radius = c[2];
		circle(originalImage2, center, radius, Scalar(255, 0, 255), 3, LINE_AA);
	}
	

	//imshow("Detected circles", originalImage);
	//waitKey();

	// Window names
	String finalImageWindow0 = "Final Image Window 0";
	String finalImageWindow1 = "Final Image Window 1";
	String finalImageWindow2 = "Final Image Window 2";

	// Create Windows
	namedWindow(finalImageWindow0);
	namedWindow(finalImageWindow1);
	namedWindow(finalImageWindow2);

	// Show images inside created windows
	imshow(finalImageWindow0, originalImage0);
	imshow(finalImageWindow1, originalImage1);
	imshow(finalImageWindow2, originalImage2);

	waitKey(0); // Wait for any keystroke in the window

	imwrite("part1/p1_image1_final_c++.png", originalImage0);
	imwrite("part1/p1_image2_final_c++.png", originalImage1);
	imwrite("part1/p1_image3_final_c++.png", originalImage2);

	// Destroy the created window
	destroyWindow(finalImageWindow0);
	destroyWindow(finalImageWindow1);
	destroyWindow(finalImageWindow2);

	return 0;
}



// Taken from openCV documentation page for quick debug.
void show_wait_destroy(const char* winname, cv::Mat img) {
	imshow(winname, img);
	moveWindow(winname, 500, 0);
	waitKey(0);
	destroyWindow(winname);
}