#pragma once
#include"MyMat.h"
void myIntegral(MyMat *src, MyMat *sum, MyMat *sqsum, MyMat *tilted);
void GetGrayIntegralImage(unsigned char *Src, int *Integral, int Width, int Height, int Stride); //求解积分图
void GetGraySqImage(unsigned char *Src, int *Integral, int Width, int Height, int Stride); //求解平方积分图
void bubbleSort(int* pData, int *idx, int length);
/*
*图像缩放函数
*/
uchar get_scale_value(MyMat* input_img, float raw_i, float raw_j);
MyMat* scale(MyMat* input_img, MyMat* output_img, int width, int height);  //最邻近算法
MyMat* bin_linear_scale(MyMat* input_img, MyMat* output_img, int width, int height);  //双线性插值