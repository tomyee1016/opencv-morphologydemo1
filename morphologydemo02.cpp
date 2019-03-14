#include<opencv2/opencv.hpp>
#include<iostream>


using namespace cv;
using namespace std;

//----------------------[ȫ�ֱ�����������]------------------
//              ������ȫ�ֱ�������
//-----------------------------------------------------------
Mat srcImage, dstImage1,dstImage2;//ԭʼͼ��Ч��ͼ


//�������յ�TrackBarλ�ò���
int OpenCloseNum = 0;

//-----------------------[ȫ�ֺ�����������]---------------------
//     ������ȫ�ֺ�������
//--------------------------------------------------------------
void on_OpenClose(int, void *);

//-----------------[main()����]----------------------
//---------------------------------------------------

int main(int argc, char** argv) {
	srcImage = imread("H:/images/duizhang.jpg");
	if (!srcImage.data) {
		cout << "can not load the image" << endl;
		return -1;
	}
	cvtColor(srcImage, dstImage1, CV_RGB2GRAY);
	//��ʾԭʼͼ
	namedWindow("ԭʼͼ");
	imshow("ԭʼͼ", dstImage1);

	//������������
	namedWindow("������/������");

	//������ֵ
	OpenCloseNum = 9;

	//�ֱ�Ϊ�������ڴ���������
	createTrackbar("����ֵ", "������/������", &OpenCloseNum, 100, on_OpenClose);
	//ִ�лص�����
	on_OpenClose(OpenCloseNum, 0);
	
	waitKey(0);
	return 0;
}


//--------------------[on_OpenClose()����]-------------------
//          ������[������/������]���ڵĻص�����
//------------------------------------------------------------
void on_OpenClose(int, void *) {
	Mat element = getStructuringElement(MORPH_RECT, Size(OpenCloseNum*2+1,OpenCloseNum*2+1),Point(-1,-1));
	morphologyEx(dstImage1, dstImage2, CV_MOP_BLACKHAT, element);
	imshow("������/������", dstImage2);
}
