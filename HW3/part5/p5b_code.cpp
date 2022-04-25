// Your code goes in this file.

// Headers
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define R_LOW 200
#define R_HIGH 255
#define G_LOW 0
#define G_HIGH 10
#define B_LOW 0
#define B_HIGH 10

// compile command
// cl /EHsc part5\p5b_code.cpp /I Y:\CodeLib\opencv\include /link /LIBPATH:Y:\CodeLib\opencv\x64\vc17\lib opencv_world455.lib

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

	VideoWriter output_cap("part5/p5b_video3_final.avi",
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
	Mat zerosArrPrev;
	input_cap.read(zerosArrPrev);
	zerosArrPrev = Scalar::all(0);
	int count = 0;
	while (input_cap.read(frame)) {
		//cout << "working " << count << "\n";

		Mat gray;
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		medianBlur(gray, gray, 5);
		vector<Vec3f> circles;

		HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
			gray.rows / 32,
			100, 30, 25, 40
		);

		Mat zerosArr = frame.clone();
		zerosArr = Scalar::all(0);
		
		//show_wait_destroy("temp", zerosArr);

		/*
		HoughCircles(gray, circles, HOUGH_GRADIENT_ALT, 1.5,
			gray.rows / 32,
			300, 0.9, 25, 40
		);
		*/

		//imwrite("part4/p4_helper.png", frame);


		for (size_t num = 0; num < circles.size(); num++) {
			Vec3i c = circles[num];
			Point center = Point(c[0], c[1]);

			//circle(frame, center, 1, Scalar(255, 0, 0), 3, LINE_AA);
			int radius = c[2];

			int x_coord = c[0];
			int y_coord = c[1];
			//printf("Here");

			// I'm a bit limited by the framerate of the video. So we see a dotted line instead.

			// rgb[0] is blue, rgb[1] is green, and rgb[2] is red
			if (frame.at<Vec3b>(y_coord, x_coord)[0] >= 0 && frame.at<Vec3b>(y_coord, x_coord)[0] <= 20) {
				if (frame.at<Vec3b>(y_coord, x_coord)[1] >= 0 && frame.at<Vec3b>(y_coord, x_coord)[1] <= 20) {
					if (frame.at<Vec3b>(y_coord, x_coord)[2] >= 200 && frame.at<Vec3b>(y_coord, x_coord)[2] <= 255) {

						// Red piece trace.
						line(zerosArr, center, center, Scalar(0, 0, 255), 10, LINE_8);
					}
				}
			}

			if (frame.at<Vec3b>(y_coord, x_coord)[0] >= 230 && frame.at<Vec3b>(y_coord, x_coord)[0] <= 255) {
				if (frame.at<Vec3b>(y_coord, x_coord)[1] >= 230 && frame.at<Vec3b>(y_coord, x_coord)[1] <= 255) {
					if (frame.at<Vec3b>(y_coord, x_coord)[2] >= 230 && frame.at<Vec3b>(y_coord, x_coord)[2] <= 255) {

						// White piece trace.
						line(zerosArr, center, center, Scalar(255, 255, 255), 10, LINE_8);
					}
				}
			}
			//circle(frame, center, radius + 7, Scalar(255, 255, 255), 3, LINE_AA);
			
			//show_wait_destroy("temp", zerosArr);
			//bitwise_or(frame, zerosArr, frame);

			
		}
		Mat xor_ed;
		bitwise_xor(zerosArr, zerosArrPrev, xor_ed);
		bitwise_or(xor_ed, zerosArr, zerosArr);
		bitwise_or(zerosArr, frame, frame);

		count++;
		output_cap.write(frame);
		zerosArrPrev = zerosArr;
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