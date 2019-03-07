#include<opencv2/opencv.hpp>
#include<iostream>


using namespace cv;
using namespace std;
Mat src, dst;
char OUTPUT_WIN[] = "output image";
int main(int argc, char** argv) {
	src = imread("E:/cat.jpg");
	if (!src.data) {
		cout << "could not load image..." << endl;
		return -1;
	}
	namedWindow("input image", CV_WINDOW_AUTOSIZE);
	imshow("input image", src);

	Mat structure_element = getStructuringElement(MORPH_RECT,Size2i(3,3));//设置膨胀/腐蚀的核为矩形，大小为3*3
	//dilate(src, dst, structure_element);
	erode(src, dst, structure_element);
	namedWindow(OUTPUT_WIN, CV_WINDOW_AUTOSIZE);
	imshow(OUTPUT_WIN, dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}

