//#include <opencv2/core/utility.hpp>  
//#include <opencv2/tracking.hpp>  
//#include <opencv2/videoio.hpp>  
//#include <opencv2/highgui.hpp>  
//#include <iostream>  
//#include <cstring>  
//
//using namespace std;
//using namespace cv;
//
//Mat image;   //视频流  
//Mat imageCopy; //绘制矩形框时用来拷贝原图的图像  
//Mat rectImage;  //子图像  
//bool leftButtonDownFlag = false; //左键单击后视频暂停播放的标志位  
//Point originalPoint; //矩形框起点  
//Point processPoint; //矩形框终点  
//Rect2d roi;
//bool bTrack = false;
//bool bFrist = true;
//Ptr<Tracker> tracker;
//void onMouse(int event, int x, int y, int flags, void* ustc); //鼠标回调函数  
//// Instead of MIL,you can also use  BOOSTING, KCF,TLD, MEDIANFLOW or GOTURN  
//const char* TrackMod = "KCF";
//int main() {
//
//	namedWindow("tracker", 0);
//	setMouseCallback("tracker", onMouse);
//	// create a tracker object  
//	 
//	tracker = Tracker::create(TrackMod);
//	// set input video  
//	//! [setvideo]  
//	std::string video = "F:/1.mp4";
//
//	//std::string video = "rtsp://admin:slw@123456@192.168.0.73:554/Streaming/Channels/101?transportmode=unicast&profile=Profile_1";
//	VideoCapture cap(video);
//	
//	printf("Start the tracking process\n");
//	for (;;) {
//		// get frame from the video  
//		cap >> image;
//		cap >> image;
//		cap >> image;
//		
//		//stop the program if no more images
//			if (image.rows == 0 || image.cols == 0)
//				break;
//		if (bTrack)
//		{
//			if (bFrist)
//			{
//				//quit if ROI was not selected  
//				if (roi.width == 0 || roi.height == 0)
//					return 0;
//				if (tracker->init(image, roi))
//				{
//					cout << "tracker init" << endl;
//				}
//				bFrist = false;
//			}
//			if (!(tracker->update(image, roi)))
//			{
//				cout << "******************" << endl;
//				break;
//			}
//			cout << " x:" << roi.x << " y:" << roi.y << " width:" << roi.width << " height:" << roi.height << endl;
//			rectangle(image, roi, Scalar(255, 0, 0), 2, 1);
//			Mat roiImage = image(roi);
//			imshow("Roi", roiImage);
//		}
//
//		// show image with the tracked object
//
//		imshow("tracker", image);
//		//! [visualization]  
//		//quit on ESC button  
//		if (waitKey(30) == 27)
//			break;
//	}
//
//	return 0;
//}
//
////*******************************************************************//    
////鼠标回调函数    
//void onMouse(int event, int x, int y, int flags, void *ustc)
//{
//	if (event == CV_EVENT_LBUTTONDOWN)
//	{
//		bTrack = false;
//		tracker->clear();
//		tracker = Tracker::create(TrackMod);
//		leftButtonDownFlag = true; //标志位  
//		originalPoint = Point(x, y);  //设置左键按下点的矩形起点  
//		processPoint = originalPoint;
//	}
//	if (event == CV_EVENT_MOUSEMOVE&&leftButtonDownFlag)
//	{
//		imageCopy = image.clone();
//		processPoint = Point(x, y);
//		if (originalPoint != processPoint)
//		{
//			//在复制的图像上绘制矩形  
//			rectangle(imageCopy, originalPoint, processPoint, Scalar(0, 0, 255), 2);
//		}
//		imshow("tracker", imageCopy);
//	}
//	if (event == CV_EVENT_LBUTTONUP)
//	{
//		leftButtonDownFlag = false;
//		Mat subImage = image(Rect(originalPoint, processPoint)); //子图像  
//		rectImage = subImage.clone();
//
//		roi.x = originalPoint.x;
//		roi.y = originalPoint.y;
//		roi.width = Rect(originalPoint, processPoint).width;
//		roi.height = Rect(originalPoint, processPoint).height;
//		bTrack = true;
//		bFrist = true;
//	}
//}