#include<opencv2/opencv.hpp>
#include<iostream>


using namespace cv;
using namespace std;


Mat srcImage, dstImage;//ԭʼͼ��Ч��ͼ
int TrackbarNumber = 0;//0��ʾ��ʴerode,1��ʾ����dilate
int StructElementSize = 3;//�ṹԪ��(�ں˾��󣩵ĳߴ�


//-----------------------[ȫ�ֺ�����������]------------------
//              ������ȫ�ֺ�������
//------------------------------------------------------------
void Process();//���ͺ͸�ʴ�Ĵ�����
void on_TrackbarNumChange(int, void *);//�ص�����
void on_ElementSizeChange(int, void *);//�ص�����


//-----------------[main()����]----------------------
//---------------------------------------------------

int main(int argc, char** argv) {
	srcImage = imread("H:/images/qianmo.png");
	if (!srcImage.data) {
		cout << "can not load the image" << endl;
		return -1;
	}
	//��ʾԭʼͼ
	namedWindow("ԭʼͼ");
	imshow("ԭʼͼ", srcImage);

	//���г��θ�ʴ��������ʾЧ��ͼ
	namedWindow("Ч��ͼ");
	//�����켣��
	createTrackbar("��ʴ/����", "Ч��ͼ", &TrackbarNumber, 1, on_TrackbarNumChange);
	createTrackbar("�ں˳ߴ�", "Ч��ͼ", &StructElementSize,21,on_ElementSizeChange);
	waitKey(0);
	return 0;
}

//---------------------[Process()����]---------------------
//            �����������Զ���ĸ�ʴ�����Ͳ���
//----------------------------------------------------------
void Process() {
	//��ȡ�Զ����
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * StructElementSize + 1, 2 * StructElementSize + 1), Point(StructElementSize, StructElementSize));
	//���и�ʴ�����Ͳ���
	if (TrackbarNumber == 0) {
		erode(srcImage, dstImage, element);
	}
	else
	{
		dilate(srcImage, dstImage, element);
	}

	//��ʾЧ��ͼ
	imshow("Ч��ͼ", dstImage);
}

//---------------------[on_TrackbarNumChange()����]-------------
//               ��������ʴ������֮���л����صĻص�����
//---------------------------------------------------------------
void on_TrackbarNumChange(int, void *) {
	//��ʴ������֮��Ч���Ѿ��л����ص��������������һ��Process������ʹ
	//�ı���Ч��������Ч����ʾ����
	Process();
}


//------------------[on_ElementSizeChange()����]-------------------
//                ��������ʴ�����Ͳ����ں˸ı�ʱ�Ļص�����
//------------------------------------------------------------------
void on_ElementSizeChange(int, void *)
{
	//�ں˳ߴ��Ѹı䣬�ص��������������һ��Process������ʹ�ı���Ч��������Ч����ʾ����
	Process();
}