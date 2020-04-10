#include <iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat dstMat;
	cv::Mat srcMat = cv::imread("D:\\Files\\lena.jpg");//读取图像
	//检测是否读取成功
	if (srcMat.empty())
	{
		return -1;
	}
	cv::Point2f center(srcMat.cols / 2.0, srcMat.rows / 2.0);
	//旋转-10℃，缩放尺度为
	float angle = -10, scale = 1;
	cv::Mat rot = cv::getRotationMatrix2D(center, angle, scale);
	//获取外界四边形
	cv::Rect bbox = RotatedRect(center, srcMat.size(), angle).boundingRect();
	//调整仿射矩形参数
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	//仿射变换
	cv::warpAffine(srcMat, dstMat, rot, bbox.size());
	//显示结果
	cv::imshow("src", srcMat);
	cv::imshow("dst", dstMat);
	waitKey(0);
}