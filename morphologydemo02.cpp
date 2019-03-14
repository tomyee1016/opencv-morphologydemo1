#include<opencv2/opencv.hpp>
#include<iostream>


using namespace cv;
using namespace std;

//----------------------[全局变量声明部分]------------------
//              描述：全局变量声明
//-----------------------------------------------------------
Mat srcImage, dstImage1,dstImage2;//原始图和效果图


//变量接收的TrackBar位置参数
int OpenCloseNum = 0;

//-----------------------[全局函数声明部分]---------------------
//     描述：全局函数声明
//--------------------------------------------------------------
void on_OpenClose(int, void *);

//-----------------[main()函数]----------------------
//---------------------------------------------------

int main(int argc, char** argv) {
	srcImage = imread("H:/images/duizhang.jpg");
	if (!srcImage.data) {
		cout << "can not load the image" << endl;
		return -1;
	}
	cvtColor(srcImage, dstImage1, CV_RGB2GRAY);
	//显示原始图
	namedWindow("原始图");
	imshow("原始图", dstImage1);

	//创建三个窗口
	namedWindow("开运算/闭运算");

	//参数赋值
	OpenCloseNum = 9;

	//分别为三个窗口创建滚动条
	createTrackbar("迭代值", "开运算/闭运算", &OpenCloseNum, 100, on_OpenClose);
	//执行回调函数
	on_OpenClose(OpenCloseNum, 0);
	
	waitKey(0);
	return 0;
}


//--------------------[on_OpenClose()函数]-------------------
//          描述：[开运算/闭运算]窗口的回调函数
//------------------------------------------------------------
void on_OpenClose(int, void *) {
	Mat element = getStructuringElement(MORPH_RECT, Size(OpenCloseNum*2+1,OpenCloseNum*2+1),Point(-1,-1));
	morphologyEx(dstImage1, dstImage2, CV_MOP_BLACKHAT, element);
	imshow("开运算/闭运算", dstImage2);
}
