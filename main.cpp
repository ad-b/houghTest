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
			if (!(hough.at<uchar>(point) == 1))
			{
				hough.at<uchar>(point) = (int)(hough.at<uchar>(point)) - 2;
			}
			prev.x = point.x;
			prev.y = point.y;
		}	
	}
}

int main(int argc, char** argv)
{
	string path = "test5.bmp";
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
			if ((int)gray.at<uchar>(Point(i, j)) == 0)
			{
				AddAccumulator(Point(i, j), radius);
			}		
		}
	}

	//equalizeHist(hough, hough);
	//normalize(hough, hough, 0, 255);

	imshow("hough", hough);
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
	compression_params.push_back(3);
	imwrite("output.png", hough, compression_params);

	waitKey(0);

	return 0;
}