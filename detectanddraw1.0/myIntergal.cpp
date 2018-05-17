#pragma once
#include"myIntergal.h"
#include"basic.h"
#include"basicStruct.h"


/*
*������ͼ
*/
void GetGrayIntegralImage(unsigned char *Src, int *Integral, int Width, int Height, int Stride)
{
	int *ColSum = (int *)calloc(Width, sizeof(int));        //    �õ�calloc����Ŷ���Զ��ڴ���0
	memset(Integral, 0, (Width + 1) * sizeof(int));
	for (int Y = 0; Y < Height; Y++)
	{
		unsigned char *LinePS = Src + Y * Stride;
		int *LinePL = Integral + Y * (Width + 1) + 1;
		int *LinePD = Integral + (Y + 1) * (Width + 1) + 1;
		LinePD[-1] = 0;
		for (int X = 0; X < Width; X++)
		{
			ColSum[X] += LinePS[X];
			LinePD[X] = LinePD[X - 1] + ColSum[X];
		}
	}
	free(ColSum);
}
//���ƽ������ͼ
void GetGraySqImage(unsigned char *Src, int *Integral, int Width, int Height, int Stride)
{
	uchar *copy = new uchar[Width*Height];
	for (int i = 0;i < Width;i++)
	{
		for (int j = 0;j < Height;j++)
		{
			copy[j + i * Width] = Src[j + i * Width] * Src[j + i * Width];
		}
	}
	GetGrayIntegralImage(copy,Integral,Width,Height,Stride);
	delete []copy;
}
/*
*ð������
*idx ��������
*data_array ��������
*/
void bubbleSort(int* pData, int *idx, int length)
{
	int temp, idxt;
	for (int i = 0;i != length;++i)
	{
		for (int j = 0; j != length; ++j)
		{
			if (pData[i] < pData[j])
			{
				temp = pData[i];
				idxt = idx[i];
				pData[i] = pData[j];
				idx[i] = idx[j];
				pData[j] = temp;
				idx[j] = idxt;
			}
		}
	}
}
//������ڲ��㷨
MyMat* scale(MyMat* input_img, MyMat* output_img, int width, int height)
{

	float h_scale_rate = (float)input_img->rows / height;  //�ߵı���
	float w_scale_rate = (float)input_img->cols / width;  //��ı���
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int i_scale = h_scale_rate * i;   //���ոߵı�������ԭͼ��Ӧ�����е�x��������õ�������ȡ������Ȼ��������Ҳ����
			int j_scale = w_scale_rate * j;  //���տ�ı�������ԭͼ��Ӧ�����е�y
											 //cout << "i_scale: " << i_scale <<" j_scale: "<< j_scale << endl;

			output_img->data.ptr[i * width + j] = input_img->data.ptr[i_scale*input_img->width + j_scale];
		}
	}

	return output_img;
}
//˫���Բ�ֵ
//f(i+u,j+v) = (1-u)(1-v)f(i,j) + (1-u)vf(i,j+1) + u(1-v)f(i+1,j) + uvf(i+1,j+1)  
uchar get_scale_value(MyMat* input_img, float raw_i, float raw_j)
{
	int i = raw_i;
	int j = raw_j;
	float u = raw_i - i;
	float v = raw_j - j;
	int width = input_img->width;
	int height = input_img->height;
	//ע�⴦��߽����⣬����Խ��
	if (i + 1 >= input_img->rows || j + 1 >= input_img->cols)
	{
		uchar p = input_img->data.ptr[i * input_img->width + j];
		return p;
	}

	uchar x1 = input_img->data.ptr[i*width + j];  //f(i,j)
	uchar x2 = input_img->data.ptr[i*width + j + 1];  //f(i,j+1)
	uchar x3 = input_img->data.ptr[(i + 1) * width + j];   //(i+1,j)
	uchar x4 = input_img->data.ptr[(i + 1) * width + (j + 1)];  //f(i+1,j+1) 
																// printf("%d %d\n", i, j);
	return ((1 - u)*(1 - v)*x1 + (1 - u)*v*x2 + u*(1 - v)*x3 + u*v*x4);
}
//˫���Բ�ֵ
MyMat* bin_linear_scale(MyMat* input_img, MyMat* output_img, int width, int height)
{

	float h_scale_rate = (float)input_img->rows / height;  //�ߵı���
	float w_scale_rate = (float)input_img->cols / width;  //��ı���
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			float i_scale = h_scale_rate * i;   //���ոߵı�������ԭͼ��Ӧ�����е�x��������õ�������ȡ������Ȼ��������Ҳ����
			float j_scale = w_scale_rate * j;  //���տ�ı�������ԭͼ��Ӧ�����е�y
											   //cout << "i_scale: " << i_scale <<" j_scale: "<< j_scale << endl;

			output_img->data.ptr[i * width + j] = get_scale_value(input_img, i_scale, j_scale);
		}
	}

	return output_img;
}