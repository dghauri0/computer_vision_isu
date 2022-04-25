// Your code goes in this file.

// Headers
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


// compile command
// cl /EHsc part5\p5a_code.cpp /I Y:\CodeLib\opencv\include /link /LIBPATH:Y:\CodeLib\opencv\x64\vc17\lib opencv_world455.lib

void show_wait_destroy(const char* winname, cv::Mat img);

int main(int argc, char* argv[]) {

	// Load input video
	//  If your video is in a different source folder than your code, 
	//  make sure you specify the directory correctly!
	VideoCapture input_cap("part5/p5_video3.avi");

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

	VideoWriter output_cap("part5/p5a_video3_final.avi",
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
	Mat previousFrame;				// This is binary inverted!
	int thresholdValue = 130;
	int thresholdType = 1;
	int MAX_BINARY = 255;
	input_cap.read(previousFrame);
	cvtColor(previousFrame, previousFrame, COLOR_BGR2GRAY);
	//threshold(previousFrame, previousFrame, thresholdValue, MAX_BINARY, thresholdType);

	int count = 0;
	while (input_cap.read(frame)) {
		//cout << "working " << count << "\n";

		Mat gray;
		Mat binaryImageInverted;

		cvtColor(frame, gray, COLOR_BGR2GRAY);
		
		threshold(gray, binaryImageInverted, thresholdValue, MAX_BINARY, thresholdType);
		//medianBlur(gray, gray, 5);
		Mat xor_ed;
		bitwise_xor(gray, previousFrame, xor_ed);
		int i, j;
		for (i = 0; i < xor_ed.size().height; i++) {
			for (j = 0; j < xor_ed.size().width; j++) {
				if (xor_ed.at<uint8_t>(i, j) <= 255 && xor_ed.at<uint8_t>(i, j) >= 100) {
					xor_ed.at<uint8_t>(i, j) -= 5;
				}
			}
		}
		bitwise_or(xor_ed, gray, gray);

		cvtColor(gray, frame, COLOR_GRAY2BGR);

		
		count++;
		output_cap.write(frame);
		previousFrame = gray;

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