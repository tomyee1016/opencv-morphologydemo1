#include<opencv2/opencv.hpp>
#include<iostream>


using namespace cv;
using namespace std;


Mat srcImage, dstImage;//原始图和效果图
int TrackbarNumber = 0;//0表示腐蚀erode,1表示膨胀dilate
int StructElementSize = 3;//结构元素(内核矩阵）的尺寸


//-----------------------[全局函数声明部分]------------------
//              描述：全局函数声明
//------------------------------------------------------------
void Process();//膨胀和腐蚀的处理函数
void on_TrackbarNumChange(int, void *);//回调函数
void on_ElementSizeChange(int, void *);//回调函数


//-----------------[main()函数]----------------------
//---------------------------------------------------

int main(int argc, char** argv) {
	srcImage = imread("H:/images/qianmo.png");
	if (!srcImage.data) {
		cout << "can not load the image" << endl;
		return -1;
	}
	//显示原始图
	namedWindow("原始图");
	imshow("原始图", srcImage);

	//进行初次腐蚀操作并显示效果图
	namedWindow("效果图");
	//创建轨迹条
	createTrackbar("腐蚀/膨胀", "效果图", &TrackbarNumber, 1, on_TrackbarNumChange);
	createTrackbar("内核尺寸", "效果图", &StructElementSize,21,on_ElementSizeChange);
	waitKey(0);
	return 0;
}

//---------------------[Process()函数]---------------------
//            描述：进行自定义的腐蚀和膨胀操作
//----------------------------------------------------------
void Process() {
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * StructElementSize + 1, 2 * StructElementSize + 1), Point(StructElementSize, StructElementSize));
	//进行腐蚀或膨胀操作
	if (TrackbarNumber == 0) {
		erode(srcImage, dstImage, element);
	}
	else
	{
		dilate(srcImage, dstImage, element);
	}

	//显示效果图
	imshow("效果图", dstImage);
}

//---------------------[on_TrackbarNumChange()函数]-------------
//               描述：腐蚀和膨胀之间切换开关的回调函数
//---------------------------------------------------------------
void on_TrackbarNumChange(int, void *) {
	//腐蚀和膨胀之间效果已经切换，回调函数体内需调用一次Process函数，使
	//改变后的效果立即生效并显示出来
	Process();
}


//------------------[on_ElementSizeChange()函数]-------------------
//                描述：腐蚀和膨胀操作内核改变时的回调函数
//------------------------------------------------------------------
void on_ElementSizeChange(int, void *)
{
	//内核尺寸已改变，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来
	Process();
}