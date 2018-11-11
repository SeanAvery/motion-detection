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

int main(int argc, char *argv[])
{
		if (argc != 2)
		{
			  cout << "Not enough parameters" << endl;
			  return -1;
		}
    
    // open video file
		const string videoFileName = argv[1];
    
    // start video capture
		VideoCapture capture(videoFileName);

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

		const char* VID_WIN = "video_window";

    // new named window for output
		namedWindow(VID_WIN, WINDOW_AUTOSIZE);
    
    // frame matrix
		Mat frame;

		int frameNum = -1;
    
    // iterate through frames
		for (;;)
		{
				capture >> frame;

				if (frame.empty())
				{
						cout << " < < < video is over! > > >";
						break;
				}

				++frameNum;
        
        // display frame in named window
				imshow(VID_WIN, frame);
        
        // allow time for frame to render
        waitKey(1);   
		}
    
    // success return value
		return 0;
}

