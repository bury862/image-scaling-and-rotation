
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>//
#include <opencv2/imgproc/imgproc.hpp>//

using namespace cv;

void scaling(const char* src_file, int parameter, const char* option, const char* dst_file);//缩放函数
void rotating(const char* src_file, int parameter, const char* dst_file);//旋转函数
void mirroring(const char* src_file, const char* option, const char* dst_file);//镜像函数

int main(int argc,char* argv[])
{
	for (int i = 1; i < argc; i++)//遍历所有命令行输入
	{
		if (strcmp(argv[i], "--help") == 0)//帮助，输出所有命令行参数意义
		{
			printf("--help: Get list of available commands.\nimgproc -z -m method some.bmp xxx somenew.bmp 图像放缩操作method 取值为 n，l，c，分别表示最临近插值、双线性插值和三次立方插值 xxx 为 1-999 的百分比数值\nimgproc -r some.bmp xxx somenew.bmp 图像旋转操作 xxx 为 0，90，180,270 四个角度之一\nimgproc -m some.bmp -v/-h somenew.bmp 图像镜像操作 水平（-h）或垂直镜像（-v）\n");
		}
	}
	
	if (strcmp(argv[1], "-z") == 0)//缩放
	{
		scaling(argv[4], atoi(argv[5]), argv[3], argv[6]);
	}
	else if (strcmp(argv[1], "-r") == 0)//旋转
	{
		rotating(argv[2], atoi(argv[3]), argv[4]);
	}
	else if (strcmp(argv[1], "-m") == 0)//镜像
	{
		mirroring(argv[2], argv[3], argv[4]);
	}

	return 0;
}
void scaling(const char* src_file, int parameter,const char* option,const char* dst_file)//缩放函数 
{
	//读取源图片
	Mat tempimage = imread(src_file);
	if (!tempimage.data)   //判断正确读取图片
	{
		printf("Could not open or find the image");
		return ;
	}
	//建立目标图片
	Mat desimage;
	
	//计算新参数
	double new_width = tempimage.cols * parameter / 100.0;
	double new_height = tempimage.rows * parameter / 100.0;

	if (strcmp(option,"n")==0)//最邻近插值算法
	{
		resize(tempimage, desimage, Size(new_width, new_height), 0, 0, INTER_NEAREST);
	}
	else if (strcmp(option, "l") == 0)//双线性插值算法
	{
		resize(tempimage, desimage, Size(new_width, new_height), 0, 0, INTER_LINEAR);
	}
	else if (strcmp(option, "c") == 0)//三次方插值算法
	{
		resize(tempimage, desimage, Size(new_width, new_height), 0, 0, INTER_CUBIC);
	}
	//保存目标图片
	imwrite(dst_file, desimage);

}
void rotating(const char* src_file, int parameter, const char* dst_file)//旋转函数
{
	//读取源图片
	Mat tempimage = imread(src_file);
	if (!tempimage.data)   //判断正确读取图片
	{
		printf("Could not open or find the image");
		return;
	}
	//建立目标图片
	Mat desimage;

	// 旋转中心
	Point2f center(tempimage.cols / 2.0, tempimage.rows / 2.0);
	// 旋转角度
	double angle = parameter;
	// 缩放因子
	double scale = 1.0;
	// 获取旋转矩阵
	Mat rotation_matrix = getRotationMatrix2D(center, angle, scale);
	
	// 进行图像旋转
	warpAffine(tempimage, desimage, rotation_matrix, tempimage.size());

	// 保存目标图片
	imwrite(dst_file, desimage);
}
void mirroring(const char* src_file, const char* option, const char* dst_file)//镜像函数
{
	//读取源图片
	Mat tempimage = imread(src_file);
	if (!tempimage.data)   //判断正确读取图片
	{
		printf("Could not open or find the image");
		return;
	}
	//建立目标图片
	Mat desimage;

	//镜像算法
	if (strcmp(option, "-h"))//水平镜像
	{
		flip(tempimage, desimage, 1);
	}
	else if (strcmp(option, "-v"))//垂直镜像
	{
		flip(tempimage, desimage, 0);
	}

	// 保存目标图片
	imwrite(dst_file, desimage);
}