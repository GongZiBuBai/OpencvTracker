
#include <opencv2/core/utility.hpp>  
#include <opencv2/tracking.hpp>  
#include <opencv2/videoio.hpp>  
#include <opencv2/highgui.hpp>  
#include <vector>  


using namespace cv;
using namespace std;

bool selectObject = false;
Point origin;//���ڱ������ѡ���һ�ε���ʱ���λ��    
Rect selection;//���ڱ������ѡ��ľ��ο�    
int trackObject = 0;
Mat src;
/*-------------------------------

�������� ��ʾ�켣

--------------------------------*/
void displayTrajectory(Mat img, vector<Point> traj, Scalar s)
{
	if (!traj.empty())
	{
		for (size_t i = 0; i < traj.size() - 1; i++)
		{
			line(img, traj[i], traj[i + 1], s, 2, 8, 0);
		}
	}
}
/*-------------------------------

������

--------------------------------*/
void onMouse(int event, int x, int y, int, void*)
{
	if (selectObject)//ֻ�е�����������ȥʱ����Ч��Ȼ��ͨ��if�������Ϳ���ȷ����ѡ��ľ�������selection��    
	{
		selection.x = MIN(x, origin.x);//�������ϽǶ�������    
		selection.y = MIN(y, origin.y);
		selection.width = std::abs(x - origin.x);//���ο�    
		selection.height = std::abs(y - origin.y);//���θ�    

		selection &= Rect(0, 0, src.cols, src.rows);//����ȷ����ѡ�ľ���������ͼƬ��Χ��  
		//rectangle(src,selection,Scalar(0,0,255),2);  

	}
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		origin = Point(x, y);
		selection = Rect(x, y, 0, 0);//���հ���ȥʱ��ʼ����һ����������    
		selectObject = true;
		break;
	case CV_EVENT_LBUTTONUP:
		selectObject = false;
		if (selection.width > 0 && selection.height > 0)
			trackObject = -1;
		break;
	}
}

int main(int argc, char *argv[])
{
	namedWindow("tracker");
	setMouseCallback("tracker", onMouse, 0);
	MultiTracker myTracker("KCF");
	vector<vector<Point>> trajectorys;//�켣��¼  
	int objectCounter = 0;

	VideoCapture cap("F:/1.mp4");//��Ĭ�ϵ�����ͷ    
	if (!cap.isOpened())
	{
		return -1;
	}

	bool stop = false;
	while (!stop)
	{
		cap >> src;
		if (src.rows == 0 || src.cols == 0)
							break;

		if (selectObject)
		{
			rectangle(src, selection, Scalar(0, 0, 255), 2, 8, 0);
		}
		if (trackObject < 0)
		{
			myTracker.add(src, selection);

			Point cen = Point(selection.x + selection.width / 2.0, selection.y + selection.height / 2.0);
			trajectorys.resize(objectCounter + 1);
			trajectorys[objectCounter].push_back(cen);//��[0]��ʼ��ʼ���켣��ʼ��  

			objectCounter++;//������Ŀ�������1  
			trackObject = 1;

		}
		if (trackObject)
		{
			vector<Rect2d> r;
			myTracker.update(src, r);

			size_t s = r.size();
			RNG rng;

			for (size_t i = 0; i < s; i++)
			{
				Scalar scalar = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
				rectangle(src, r[i], scalar, 2, 8, 0);
				Point C = Point(r[i].x + r[i].width / 2.0, r[i].y + r[i].height / 2.0);
				trajectorys[i].push_back(C);
				displayTrajectory(src, trajectorys[i], scalar);
				char name[10];
				sprintf_s(name, "%d", (i + 1));
				putText(src, name, r[i].tl(), 3, 0.8, Scalar(0, 255, 255), 2, 8, false);
			}

		}
		imshow("tracker", src);
		if (waitKey(30) == 27) //Esc���˳�    
		{
			stop = true;
		}
	}
	return 0;
}