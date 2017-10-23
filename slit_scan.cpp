#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/video/video.hpp"

#include <string>
#include <iostream>
using namespace std;

void slit_scan(cv::String vid_filename, cv::String img_filename, int slit_pos, bool horizontal){
	cv::VideoCapture vid(vid_filename);

	cv::Mat image;
	cv::Mat slit;

	cv::Mat out_image;
	if(horizontal){
		out_image.create(vid.get(CV_CAP_PROP_FRAME_WIDTH), vid.get(CV_CAP_PROP_FRAME_COUNT), CV_8UC3);
	}
	else{
		out_image.create(vid.get(CV_CAP_PROP_FRAME_HEIGHT), vid.get(CV_CAP_PROP_FRAME_COUNT), CV_8UC3);
	}

	bool frame;

	for (int i=0; i < vid.get(CV_CAP_PROP_FRAME_COUNT); i++) {
		frame = vid.read(image);
		if (!frame){
			break;
		}
		if (horizontal == true){
			image = image.t();
		}
		// add slit to out_image
		slit = out_image.col(i);
		image.col(slit_pos).copyTo(slit);
	}

	cv::imwrite(img_filename, out_image);
}

int main(int argc, char const *argv[])
{
	/* code */
	if (argc != 5){
		cerr << "Required Arguments:"  <<endl
		<< "\tVideo File In" <<endl
		<< "\tImage File Out" <<endl
		<< "\tLine Number" <<endl
		<< "\tHorizontal (0 or 1)" <<endl;
		return 1;
	}
	int line = atoi(argv[3]);
	bool horizontal = atoi(argv[4]);

	slit_scan(cv::String(argv[1]), cv::String(argv[2]), line, horizontal);

	return 0;
}