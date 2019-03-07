#include<opencv2/opencv.hpp>
#include<iostream>


using namespace cv;
using namespace std;
Mat src, dst;
char OUTPUT_WIN[] = "output image";
int element_size = 1;
int max_size = 10;
void CallBack_Demo(int, void*);
int main(int argc, char** argv) {
	src = imread("E:/cat.jpg");
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);


	namedWindow(OUTPUT_WIN, CV_WINDOW_AUTOSIZE);//不加此句代码Trackbar无法显示
	//生成一个滑动条，参数：Trackbar名字，放到哪个窗口，Trackbar初始值，Trackbar最大值，回调函数
	createTrackbar("Element Size:", OUTPUT_WIN, &element_size, max_size, CallBack_Demo);
	CallBack_Demo(0, 0);

	waitKey(0);
	return 0;
}

void CallBack_Demo(int, void*) {
	cout << "element_size:" << element_size << endl;
	int s = element_size * 2 + 1;
	//获取元素结构，参数：形状，大小，锚点 默认是Point(-1,-1)中心点
	Mat structureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
	//dilate(src, dst, structureElement);//膨胀
	erode(src, dst, structureElement);
	imshow(OUTPUT_WIN, dst);
	return;
}