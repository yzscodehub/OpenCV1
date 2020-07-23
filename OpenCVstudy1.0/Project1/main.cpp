#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int g_slider_position = 0;
int g_run = 1;
int g_dontset = 0;
cv::VideoCapture g_cap;

void onTrackbarSlide(int pos, void *)
{
	g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
	
	if (!g_dontset)
	{
		g_run = 1;
	}
	g_dontset = 0;
}

//播放视频
void showVideoTest()
{
	cv::namedWindow("Video", cv::WINDOW_AUTOSIZE);
	g_cap.open("./res/***.MP4");
	int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT);
	int tmpw = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int tmph = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	cout << "video frames = " << frames << endl;
	cout << "video width = " << tmpw << endl;
	cout << "video height = " << tmpw << endl;

	cv::createTrackbar("Position", "Video", &g_slider_position, frames, onTrackbarSlide);

	cv::Mat frame;
	while (1)
	{
		if (g_run != 0)
		{
			g_cap >> frame;
			if (frame.empty())
				return;
			int current_pos = g_cap.get(cv::CAP_PROP_POS_FRAMES);
			g_dontset = 1;

			cv::setTrackbarPos("Position", "Video", current_pos);
			cv::imshow("Video", frame);

			g_run -= 1;
		}

		char c = (char)cv::waitKey(10);
		if (c == 's')
		{
			g_run = 1;
		}
		else if (c == 'r')
		{
			g_run = -1;
		}
		else if (c == 27)
		{
			break;
		}
	}
	return;
}

//展示图片
void showPictureTest()
{
	String str("./res/iron.jpg");
	Mat img = imread(str, -1);
	if (img.empty())
	{
		cout << "图片资源未读入" << endl;
		return;
	}
	namedWindow("iron", cv::WINDOW_AUTOSIZE);
	imshow("iron", img);
	waitKey(0);
	destroyWindow("iron");
}

//加载图片并且在显示之前平滑处理图像
void GaussianBlurTest()
{
	String str("./res/iron.jpg");
	Mat img = imread(str, -1);
	if (img.empty())
	{
		cout << "图片资源未读入" << endl;
		return;
	}

	cv::String namein("in");
	cv::String nameout("out");

	cv::namedWindow(namein, cv::WINDOW_NORMAL);
	cv::namedWindow(nameout, cv::WINDOW_NORMAL);
	
	cv::imshow(namein, img);

	cv::Mat out;
	cv::GaussianBlur(img, out, cv::Size(5, 5), 3, 3);
	cv::GaussianBlur(out, out, cv::Size(5, 5), 3, 3);
	
	cv::imshow(nameout, out);

	cv::waitKey(0);
}

//将图片的宽高调整为原始图像的一半
void pyrDownTest()
{
	cv::Mat imag1, imag2, imag3, imag4, imag5;

	cv::namedWindow("1111", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("2222", cv::WINDOW_AUTOSIZE);

	imag1 = cv::imread("./res/iron.jpg");
	
	cv::cvtColor(imag1, imag2, cv::COLOR_BGR2GRAY);
	cv::pyrDown(imag2, imag3);
	cv::pyrDown(imag3, imag4);
	cv::Canny(imag4, imag5, 10, 100, 3, true);

	cv::imshow("1111", imag4);
	cv::imshow("2222", imag5);

	int x = 16, y = 32;
	cv::Vec3d intensity = imag1.at<cv::Vec3d >(x, y);
	uchar blue = intensity[0];
	uchar green = intensity[1];
	uchar red = intensity[2];

	cout << "At(x,y) = (" << x << "," << y << ") : (blue, green, red) = (" << (unsigned int)blue 
		 << "," << (unsigned int)green << "," << (unsigned int)red << ")" << endl;

	cout << "Gray pixel there is:" << (unsigned int)

	cv::waitKey(0);
}

int main()
{
	//showPictureTest();
	//showVideoTest();
	//GaussianBlurTest();
	pyrDownTest();

	return 0;
}
