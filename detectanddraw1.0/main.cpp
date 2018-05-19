#include<iostream>
#include<fstream>
#include"haarTraining.h"
#include"classifier.h"
#include"myIntergal.h"
#include"delete.h"

using namespace std;


static MyCascadeClassifier cascade;

const char* cascade_name = "F:\\workplace\\visualstudio\\facesource\\testpic\\jilianre\\cascade.xml";
//�������Ҫ�õ��ķ�����  
void detect_and_draw(MyMat *img);
int main(int argc, char* argv[])
{
	

	cascade = readXML(cascade_name, cascade);
	

	cout << cascade.StrongClassifier.size();

	Mat picMat = imread("e:\\6.png",0);
	MyMat *tempMat = createMyMat(picMat.rows, picMat.cols, ONE_CHANNEL, UCHAR_TYPE);
	tempMat = transMat(tempMat,"e:\\6.png");
	detect_and_draw(tempMat);
	

	return 0;
	
	
}
void detect_and_draw(MyMat *img)
{
	ofstream filePic;
	FaceSeq *faces = NULL;
	Mat picMat = imread("e:\\6.png", 0);
	MyMat *outpic = createMyMat(picMat.rows, picMat.cols, ONE_CHANNEL, UCHAR_TYPE);
	//bin_linear_scale(img, outpic, 450, 300);
	outpic = transMat(outpic,"e:\\6.png");	
	if (outpic == nullptr)
	{
		cout << "ͼƬ������" << endl;
		return;
	}
	Mat smallPic = transCvMat(outpic);
	MySize minSize;
	minSize.width = 19;
	minSize.height = 19;
	MySize maxSize;
	maxSize.width = 100;
	maxSize.height = 100;

	faces = myHaarDetectObjectsShrink(outpic, cascade, 1.2, 1, 0, minSize, maxSize);
	
	filePic.open("E://faces.txt", ios::out);
	
	for (int i = 0; i <faces->count; i++)
	{
		CvPoint center;
		Rect r;
		filePic << i << ": ";
		r.x= faces->rect[i].y;
		filePic << "x:"<<r.x;
		r.y = faces->rect[i].x;
		filePic <<",y:" <<r.y;
		r.width = faces->rect[i].width;
		filePic << ",width:" << r.width;
		r.height = faces->rect[i].height;
		filePic << ",height:" << r.height;
		rectangle(smallPic,r, Scalar(0, 0, 255));
		//imshow("src", smallPic);
		waitKey();
		filePic << endl;
	}
	
	filePic.close();

	imshow("2", smallPic);
	waitKey();
	free(faces);
	releaseMyMat(outpic);
	
}
/*
void detect_and_draw(IplImage* img)
{
	static CvScalar colors[] =
	{
		{ { 0,0,255 } },
		{ { 0,128,255 } },
		{ { 0,255,255 } },
		{ { 0,255,0 } },
		{ { 255,128,0 } },
		{ { 255,255,0 } },
		{ { 255,0,0 } },
		{ { 255,0,255 } }
	};
	double scale = 1.3;
	IplImage* gray = cvCreateImage(cvSize(img->width, img->height), 8, 1);

	IplImage* small_img = cvCreateImage(cvSize(
		cvRound(img->width / scale), cvRound(img->height / scale)), 8, 1);

	cvCvtColor(img, gray, CV_BGR2GRAY);
	cvResize(gray, small_img, CV_INTER_LINEAR);
	cvEqualizeHist(small_img, small_img);
	cvClearMemStorage(storage);

	if (cascade)
	{        
		
		CvSeq* faces = cvHaarDetectObjects(
			small_img, cascade, storage, 1.1, 2, 0, cvSize(
				20, 20));

		for (int i = 0; i < (faces ? faces->total : 0); i++)
		{
			CvRect* r = (CvRect*)cvGetSeqElem(faces, i);
			CvPoint center;
			int radius;
			center.x = cvRound((r->x + r->width*0.5)*scale);
			center.y = cvRound((r->y + r->height*0.5)*scale);
			radius = cvRound((r->width + r->height)*0.25*scale);
			cvCircle(img, center, radius, colors[i % 8], 3, 8, 0);
		}
	}
	cvShowImage("result", img);
	cvReleaseImage(&gray);
	cvReleaseImage(&small_img);
}
*/