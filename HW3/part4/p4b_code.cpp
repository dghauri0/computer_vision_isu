// Your code goes in this file.

// Headers
#include <opencv2/core/core.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

/*
Retrieved rough mappings of coordinates for triangle clusters from matlab. Duplicated many for simplicity in iteration.
 */

const int tri_x[24][2] = { {54, 202}, {202, 351}, {351, 492}, {492, 634}, {634, 778}, {778, 930},
						   {1030, 1187}, {1187, 1328}, {1328, 1472}, {1472, 1613}, {1613, 1757}, {1757, 1912},
						   {54, 202}, {202, 351}, {351, 492}, {492, 634}, {634, 778}, {778, 930},
						   {1030, 1187}, {1187, 1328}, {1328, 1472}, {1472, 1613}, {1613, 1757}, {1757, 1912} };

const int tri_y[24][2] = { {0, 456}, {0, 456}, {0, 456}, {0, 456}, {0, 456}, {0, 456},
						   {0, 456}, {0, 456}, {0, 456}, {0, 456}, {0, 456}, {0, 456},
						   {651, 1088}, {651, 1088}, {651, 1088}, {651, 1088}, {651, 1088}, {651, 1088},
						   {651, 1088}, {651, 1088}, {651, 1088}, {651, 1088}, {651, 1088}, {651, 1088} };

// compile command
// cl /EHsc part4\p4b_code.cpp /I Y:\CodeLib\opencv\include /link /LIBPATH:Y:\CodeLib\opencv\x64\vc17\lib opencv_world455.lib

void show_wait_destroy(const char* winname, cv::Mat img);

int main(int argc, char* argv[]) {

	// Load input video
	//  If your video is in a different source folder than your code, 
	//  make sure you specify the directory correctly!
	VideoCapture input_cap("part4/p4_video1.avi");

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

	VideoWriter output_cap("part4/p4b_video1_final.avi",
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
		const int triangles = 24;
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		medianBlur(gray, gray, 5);
		vector<Vec3f> circles[triangles];

		//Rect myROI(x_left_offset, y_top_offset, x_right_offset - x_left_offset, y_bottom_offset - y_top_offset);

		//show_wait_destroy("test", gray(myROI));
		int i, j;
		for (i = 0; i < triangles; i++) {
			Rect myROI(tri_x[i][0], tri_y[i][0], tri_x[i][1] - tri_x[i][0], tri_y[i][1] - tri_y[i][0]);

			Mat triUnderAnalysis = gray(myROI);

			HoughCircles(triUnderAnalysis, circles[i], HOUGH_GRADIENT, 1,
				32,
				100, 30, 25, 40
			);

			/*
			HoughCircles(gray, circles, HOUGH_GRADIENT_ALT, 1.5,
				gray.rows / 32,
				300, 0.9, 25, 40
			);
			*/

			//imwrite("part4/p4_helper.png", frame);

			printf("Circles found in frame for triangle %d: %d\n", i, (int)circles[i].size());
			//show_wait_destroy("test", triUnderAnalysis);


			for (size_t num = 0; num < circles[i].size(); num++) {
				Vec3i c = circles[i][num];
				Point center = Point(c[0] + tri_x[i][0], c[1] + tri_y[i][0]);


				//circle(frame, center, 1, Scalar(255, 0, 0), 3, LINE_AA);
				int radius = c[2];

				int x_coord = c[0] + tri_x[i][0];
				int y_coord = c[1] + tri_y[i][0];
				//printf("Here");

				circle(frame, center, radius + 7, Scalar(0, 0, 0), 3, LINE_AA);

				// rgb[0] is blue, rgb[1] is green, and rgb[2] is red
				if (frame.at<Vec3b>(y_coord, x_coord)[0] >= 0 && frame.at<Vec3b>(y_coord, x_coord)[0] <= 20) {
					if (frame.at<Vec3b>(y_coord, x_coord)[1] >= 0 && frame.at<Vec3b>(y_coord, x_coord)[1] <= 20) {
						if (frame.at<Vec3b>(y_coord, x_coord)[2] >= 200 && frame.at<Vec3b>(y_coord, x_coord)[2] <= 255) {

							// Draw circle around red piece.
							//printf("Wow a red circle");
							//circle(frame, center, radius + 7, Scalar(0, 0, 0), 3, LINE_AA);
						}
					}
				}

				if (frame.at<Vec3b>(y_coord, x_coord)[0] >= 230 && frame.at<Vec3b>(y_coord, x_coord)[0] <= 255) {
					if (frame.at<Vec3b>(y_coord, x_coord)[1] >= 230 && frame.at<Vec3b>(y_coord, x_coord)[1] <= 255) {
						if (frame.at<Vec3b>(y_coord, x_coord)[2] >= 230 && frame.at<Vec3b>(y_coord, x_coord)[2] <= 255) {

							// Draw circle around white piece.
							//printf("Wow a white circle");
							//circle(frame, center, radius + 7, Scalar(0, 0, 0), 3, LINE_AA);
						}
					}
				}

			}
		}
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