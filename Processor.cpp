#include <iostream>
#include <string>
#include <iomanip>  // for controlling float print precision
#include <sstream>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int MAX_KERNEL_LENGTH = 20;

int main(int argc, char *argv[]) {
    // check to make sure file_name is passed into arguments
    // looks @ ./videos/<file_name>
		if (argc != 2)
		{
			  cout << "Not enough parameters" << endl;
			  return -1;
		}

    // open video file
    const string videoDirName = "videos/";
		const string videoFileName = argv[1];

    // start video capture
		VideoCapture capture(videoDirName + videoFileName);

    // check to make sure capture has been opened
		if (!capture.isOpened())
		{
				cout << "Could not open movie file" << videoFileName << endl;
				return -1;
		}

    // get size of frame in video
		Size videoFrame = Size(
				(int) capture.get(CAP_PROP_FRAME_WIDTH),
				(int) capture.get(CAP_PROP_FRAME_HEIGHT));

		cout << "vidoeFrame" << videoFrame << endl;

    // raw video window
 		const char* VID_WIN = "video_window";
		namedWindow(VID_WIN, WINDOW_AUTOSIZE);

    // processed video window
    const char* PROC_WIN = "processed_window";
    namedWindow(PROC_WIN, WINDOW_AUTOSIZE);

    // threshold window
    const char* THRESH_WIN = "threshold_window";
    namedWindow(THRESH_WIN, WINDOW_AUTOSIZE);

    // frame matrix
		Mat frame, grayFrame, blurFrame, prevFrame, diffFrame, threshFrame, hsvFrame;
    int frameNum = -1;

    // iterate through frames
		for (;;)
		{
        // pipe next frame into Mat
				capture >> frame;

        // check to see if video has ended
        // if so, break from loop
				if (frame.empty())
				{
						cout << " < < < video is over! > > >";
						break;
				}

        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

        for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2) {
            bilateralFilter ( grayFrame, blurFrame, i, i * 2, i / 2);
        }

        if (!prevFrame.empty())
        {
            // take the absolute difference between current frame and previous frame
            // NOTE: not currently using blurred images
            absdiff(frame, prevFrame, diffFrame);
            imshow(PROC_WIN, diffFrame);

            // convert from rgb to hsv
            // it is easeir to filter in hsv
            cvtColor(diffFrame, hsvFrame, COLOR_BGR2HSV);

            // compute threshold
            // only taking high hsv vlaue pixels (65 to 100)
            inRange(hsvFrame, Scalar(0, 0, 64), Scalar(255, 255, 255), threshFrame);

            imshow(THRESH_WIN, threshFrame);
        }

        // frame counter increment
				++frameNum;

        // display frame in named window
				//imshow(PROC_WIN, blurFrame);
        imshow(VID_WIN, frame);
        // allow time for frame to render
        waitKey(1);

        // set previous frame
        capture >> prevFrame;
		}

    // success return value
		return 0;
}

Mat extractFirstFrame(VideoCapture capture) {
    // make sure video catpure is open!
    if (!capture.isOpened()) {
      cout << "capture is not opened.";
    }

    // frame Mat holder
    Mat firstFrame;

    // open first frame of video capture
    capture.read(firstFrame);

    // return first frame
    return firstFrame;
}
