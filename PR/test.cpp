#include "Core_Func.h"
#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;
using namespace PR;

int main()
{
	Mat src = imread("C:/Users/pvt1001/Desktop/PR/PR/image/blue.jpg");
	if (!src.data)
	{
		cerr << "null image!" << endl;
	}
	imshow("imput image", src);
	Mat match;
	colorMatch(src, match, BLUE, false);
	//imshow("match image", match);
	Mat image(200, 200, CV_8UC3, Scalar(0));
	RotatedRect rRect = RotatedRect(Point2f(100, 100), Size2f(100, 50), 30);
	//imshow("rotated rect", rRect);

	Point2f vertices[4];
	rRect.points(vertices);
	for (int i = 0; i < 4; i++)
		line(image, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0));

	Rect brect = rRect.boundingRect();
	rectangle(image, brect, Scalar(255, 0, 0));

	imshow("rectangles", image);
	waitKey(0);
	return 0;
}