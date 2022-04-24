// Your code goes in this file.

// Headers
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/text/ocr.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define R_LOW 200
#define R_HIGH 255
#define G_LOW 0
#define G_HIGH 10
#define B_LOW 0
#define B_HIGH 10
const int top_left_corner[2] = { 280, 526 };
const int bottom_right_corner[2] = { 555, 595 };

// compile command
// cl /EHsc part3\p3b_code.cpp /I Y:\CodeLib\opencv\include /link /LIBPATH:Y:\CodeLib\opencv\x64\vc17\lib opencv_world455.lib


// Function Declarations
void show_wait_destroy(const char* winname, cv::Mat img);

int main(int argc, char* argv[]) {

	// Load input video
	//  If your video is in a different source folder than your code, 
	//  make sure you specify the directory correctly!
	VideoCapture input_cap("part3/p3_video2.avi");

	// Check validity of target file
	if (!input_cap.isOpened()) {
		std::cout << "Input video not found." << std::endl;
		return -1;
	}

	// Set up target output video
	/*	usage: VideoWriter(filename, encoding, framerate, Size)
	 *		in our case, cv_cap_prop_* means "get property of capture"
	 *	 	we want our output to have the same properties as the input!
	 */

	VideoWriter output_cap("part3/p3b_video2_final.avi",
		VideoWriter::fourcc('H', '2', '6', '4'),
		input_cap.get(CAP_PROP_FPS),
		Size(input_cap.get(CAP_PROP_FRAME_WIDTH),
			input_cap.get(CAP_PROP_FRAME_HEIGHT)));

	// Again, check validity of target output file
	if (!output_cap.isOpened()) {
		std::cout << "Could not create output file." << std::endl;
		return -1;
	}

	// Loop to read from input one frame at a time, write text on frame, and
	// copy to output video
	Mat frame;
	int count = 0;
	while (input_cap.read(frame)) {
		//cout << "working " << count << "\n";

		Mat gray;
		Mat bgr[3];
		Mat binaryImage;
		Mat binaryImageInverted;

		int thresholdValue = 125;
		int thresholdType = 0;
		int MAX_BINARY = 255;

		cvtColor(frame, gray, COLOR_BGR2GRAY);
		split(frame, bgr);
		//medianBlur(gray, gray, 15);
		//cvtColor(gray, frame, COLOR_GRAY2BGR);

		// Thresholded Image (Binary Image)
		threshold(gray, binaryImage, thresholdValue, MAX_BINARY, thresholdType);



		//show_wait_destroy("Binary Image", binaryImage);
		//imwrite("part3/helper_coord.png", binaryImage);
		int i, j;
		if (binaryImage.at<uint8_t>(top_left_corner[1], top_left_corner[0]) <= 20) {
			for (i = top_left_corner[0]; i < bottom_right_corner[0]; i++) {
				for (j = top_left_corner[1]; j < bottom_right_corner[1]; j++) {

					if (binaryImage.at<uint8_t>(j, i) >= 200) {
						frame.at<Vec3b>(j, i)[0] = 0;
						frame.at<Vec3b>(j, i)[1] = 0;
						frame.at<Vec3b>(j, i)[2] = 255;
						printf("In loop ");
					}
				}
			}
		}

		//show_wait_destroy("Binary Image Edited", binaryImage);

		count++;
		output_cap.write(frame);
	}

	// free the capture objects from memory
	input_cap.release();
	output_cap.release();

	return 1;

}

// Taken from openCV documentation page for quick debug.
void show_wait_destroy(const char* winname, cv::Mat img) {
	imshow(winname, img);
	moveWindow(winname, 500, 0);
	waitKey(0);
	destroyWindow(winname);
}
