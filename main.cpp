#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#define PI 3.1415

using namespace cv;
Mat hough;

void AddAccumulator(Point center, int radius)
{
	for (int alpha = 0; alpha < 360; alpha++)
	{
		Point point(0, 0);
		Point prev(0, 0);

		point.x = (int)(center.x + radius * cos(alpha * PI / 180));
		point.y = (int)(center.y + radius * sin(alpha * PI / 180));

		if (!(point.x == prev.x) && !(point.y == prev.y))
		{
			if (!(hough.at<uchar>(point) == 0))
			{
				hough.at<uchar>(point) = (int)(hough.at<uchar>(point)) - 5;
			}
			prev.x = point.x;
			prev.y = point.y;
		}	
	}
}

int main(int argc, char** argv)
{
	string path = "test3.bmp";
	Mat src = imread(path, 1);
	imshow("test", src);

	Mat gray = src.clone();
	cvtColor(src, gray, CV_BGR2GRAY);

	hough = Mat(gray.rows, gray.cols, gray.type());
	hough = Mat::zeros(gray.rows, gray.cols, gray.type());
	hough.setTo(Scalar(255));

	int radius = 100;

	for (int i = 0; i < gray.cols; i++)
	{
		for (int j = 0; j < gray.rows; j++)
		{
			if ((int)gray.at<uchar>(Point(i, j)) == 255)
			{
				AddAccumulator(Point(i, j), radius);
			}		
		}
	}

	imshow("hough", hough);

	//equalizeHist(hough, hough);
	//normalize(hough, hough, 0, 255);

	waitKey(0);

	return 0;
}