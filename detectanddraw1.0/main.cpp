#include<iostream>
#include"haarTraining.h"
#include"classifier.h"
#include"myIntergal.h"
#include"delete.h"
using namespace std;


static MyCascadeClassifier cascade;

const char* cascade_name = "F:\\workplace\\visualstudio\\facesource\\testpic\\jilianre\\cascade.xml";
//人脸检测要用到的分类器  
void detect_and_draw(MyMat *img);
int main(int argc, char* argv[])
{
	

	cascade = readXML(cascade_name, cascade);
	

	cout << cascade.StrongClassifier.size();

	Mat picMat = imread("e:\\5.jpg",0);
	MyMat *tempMat = createMyMat(picMat.rows, picMat.cols, ONE_CHANNEL, UCHAR_TYPE);
	tempMat = transMat(tempMat,"e:\\5.jpg");
	detect_and_draw(tempMat);
	

	return 0;
	
	
}
void detect_and_draw(MyMat *img)
{
	FaceSeq *faces = NULL;
	MyMat *outpic = createMyMat(300, 450, ONE_CHANNEL, UCHAR_TYPE);
	bin_linear_scale(img, outpic, 450, 300);
	//outpic = transMat(outpic,"e:\\2.jpg");
	Mat picMat = imread("e:\\5.jpg", 0);
	Mat smallPic = transCvMat(outpic);
	MySize minSize;
	minSize.width = 19;
	minSize.height = 19;
	MySize maxSize;
	maxSize.width = 300;
	maxSize.height = 300;
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
	faces = myHaarDetectObjectsShrink(outpic, cascade, 1.1, 1, 0, minSize, maxSize);
	
	for (int i = 0; i <faces->count; i++)
	{
		CvPoint center;
		Rect r;
		r.x= faces->rect[i].y;
		r.y = faces->rect[i].x;
		r.width = faces->rect[i].width;
		r.height = faces->rect[i].height;
		rectangle(smallPic,r, Scalar(0, 0, 255));
	}
	imshow("src", picMat);
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