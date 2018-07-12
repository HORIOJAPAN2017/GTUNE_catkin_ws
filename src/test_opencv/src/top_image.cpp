#include "ros/ros.h"

#include <stdio.h>
#include <iostream>
#include <math.h>
#include "opencv2/opencv.hpp"
#include <fstream>

using namespace std;
using namespace cv;

//#define IMGWIDTH 640
//#define IMGHEIGHT 480
//#define ORGWIDTH 1920
//#define ORGHEIGHT 1080
//#define MAPWIDTH 500
//#define MAPHEIGHT 500
//#define Start_x 214
//#define Start_y 320
//#define IMGFAR	600		//[cm]	
//#define IMGNEAR	15		//
//#define IMGWIDTHR 600	//



void UrgLine(const Mat &img_roi, const int CUTWIDTH, const int urg_pix_x, const int urg_pix_y, const double urg_radian){
	if (urg_pix_x > CUTWIDTH / 2){
		if ((CUTWIDTH - urg_pix_x) / cos(urg_radian) <= urg_pix_y / sin(urg_radian)){
			line(img_roi, Point(urg_pix_x, urg_pix_y), Point(CUTWIDTH, urg_pix_y - int((CUTWIDTH - urg_pix_x)*tan(urg_radian))), Scalar(0, 0, 0), 2, CV_AA);
		}
		else{
			line(img_roi, Point(urg_pix_x, urg_pix_y), Point(urg_pix_x + int(urg_pix_y  * tan((CV_PI / 2) - urg_radian)), 0), Scalar(0, 0, 0), 2, CV_AA);

		}
	}
	else if (urg_pix_x < CUTWIDTH / 2){
		if ((CUTWIDTH - urg_pix_x) / (-cos(urg_radian)) <= urg_pix_y / sin(urg_radian)){
			line(img_roi, Point(urg_pix_x, urg_pix_y), Point(1, urg_pix_y - int((0 - urg_pix_x)*(tan(urg_radian)))), Scalar(0, 0, 0), 2, CV_AA);
		}
		else{
			line(img_roi, Point(urg_pix_x, urg_pix_y), Point(urg_pix_x + int(urg_pix_y  * (tan((CV_PI / 2) - urg_radian))), 0), Scalar(0, 0, 0), 2, CV_AA);

		}
	}
	else if (urg_pix_x == CUTWIDTH / 2){
		line(img_roi, Point(urg_pix_x, urg_pix_y), Point(urg_pix_x, 0), Scalar(0, 0, 0), 3, CV_AA);
	}
}


void TopViewKami(int point[4][2], const Mat &capImage, const Mat &grayImage, const Mat &topImageGray, const Mat &topImage, const int IMGWIDTH, const int IMGHEIGHT, const double Hvc, const double Hc, const double Angle,const double Dvc, const double f){
	//double Hvc = 3.85;
	//double Hc = 0.603;
	//double Angle=40;
	//double Dvc = 3;
	//double f = 289;
	double theta = (Angle / 180.0) * 3.14;
	double fp = f;
	double s = sin(theta);
	double c = cos(theta);
	int cx = IMGWIDTH / 2;
	int cy = IMGHEIGHT / 2;
	int cxp = IMGWIDTH / 2;
	int cyp = IMGHEIGHT / 2 ;

	for (int y = 0; y < topImage.rows; y++) {
		for (int x = 0; x < topImage.cols; x++) {
			int xOrg = x - cx;
			int yOrg = -y + cy;



			int newX = fp / Hvc * Hc * xOrg / (f * s - yOrg * c);
			int newY = fp / Hvc * (Hc * (f * c + yOrg * s) / (f * s - yOrg * c) - Dvc);

			newX = newX + cx;
			newY = -newY + cyp;

			if (x == 0 && y == 0) { //printf(" x = %d , y = %d \n", newX, newY);
				point[0][0] = newX;
				point[0][1] = newY;
			}
			if (x == topImage.cols - 1 && y == 0) { //printf(" x = %d , y = %d \n", newX, newY);
				point[1][0] = newX;
				point[1][1] = newY;
			}
			if (x == 0 && y == topImage.rows - 1) { //printf(" x = %d , y = %d \n", newX, newY);
				point[2][0] = newX;
				point[2][1] = newY;
			}
			if (x == topImage.cols - 1 && y == topImage.rows - 1) { //printf(" x = %d , y = %d \n", newX, newY);
				point[3][0] = newX;
				point[3][1] = newY;
			}

			if (newX < 0 || topImage.cols - 1 < newX || newY < 0 || topImage.rows - 1 < newY) {
				continue;
			}

			topImageGray.data[newY * topImageGray.cols + newX] = grayImage.data[y * grayImage.cols + x];

			topImage.data[(newY * topImage.cols + newX) * topImage.channels()] = /*undistort*/capImage.data[(y * topImage.cols + x) * topImage.channels()];
			topImage.data[(newY * topImage.cols + newX) * topImage.channels() + 1] = /*undistort*/capImage.data[(y * topImage.cols + x) * topImage.channels() + 1];
			topImage.data[(newY * topImage.cols + newX) * topImage.channels() + 2] = /*undistort*/capImage.data[(y * topImage.cols + x) * topImage.channels() + 2];
		}
	}

}
void Resize(Mat *src, Mat *dst) {

	vector<Point2f> src_p, dst_p;
	src_p.push_back(Point2f(0, 0));
	src_p.push_back(Point2f((*src).cols, 0));
	src_p.push_back(Point2f((*src).cols, (*src).rows));

	dst_p.push_back(Point2f(0, 0));
	dst_p.push_back(Point2f((*dst).cols, 0));
	dst_p.push_back(Point2f((*dst).cols, (*dst).rows));

	Mat affine2 = getAffineTransform(src_p, dst_p);
	warpAffine(*src, *dst, affine2, (*dst).size(), CV_INTER_LINEAR);

	//imshow("func", *dst);
}






template < typename T > std::string to_string(const T& n){
  std::ostringstream stm;
  stm <<n;
  return stm.str();
}

void Alpha(Mat &alpha_image){
	for (int y = 0; y < alpha_image.cols; y++) {
		for (int x = 0; x < alpha_image.rows; x++) {
			Vec4b px = alpha_image.at<cv::Vec4b>(x, y);
			if (px[0] + px[1] + px[2] == 0) {
				px[3] = 0;
				alpha_image.at<cv::Vec4b>(x, y) = px;
			}
		}
	}
}

void Grand(Mat &grand_image, Mat &alpha_image){
	for (int y = 0; y < alpha_image.cols; y++) {
		for (int x = 0; x < alpha_image.rows; x++) {
			Vec4b px = alpha_image.at<cv::Vec4b>(x, y);
			Vec4b gx = grand_image.at<cv::Vec4b>(x, y);
			if (px[3] == 0) {
				px[0] = gx[0];
				px[1] = gx[1];
				px[2] = gx[2];
				px[3] = 255;
				alpha_image.at<cv::Vec4b>(x, y) = px;
			}
		}

	}
}
void PinP(const Mat &mapImg, const Mat &smallImg, const double angle, const double tx, const double ty)
{

	Mat dstImg;
	mapImg.copyTo(dstImg);

	Point2d ctr(smallImg.cols / 2, smallImg.rows + 12);
	Mat mat = getRotationMatrix2D(ctr, angle, 1.0);

	mat.at<double>(0, 2) += tx;

	mat.at<double>(1, 2) += ty;

	warpAffine(smallImg, mapImg, mat, mapImg.size(), CV_INTER_LINEAR, BORDER_TRANSPARENT);

}

//image parameter
	int IMGWIDTH, IMGHEIGHT, ORGWIDTH, ORGHEIGHT, MAPWIDTH, MAPHEIGHT, Start_x, Start_y;
	int IMGFAR, IMGNEAR, IMGWIDTHR;
	double Hvc, Hc, Angle, Dvc, f;
  //urg
  double urg_radian[720];
	int urg_pix_x[720];
	int urg_pix_y[720];
	int urg_size = 0;
//encoder
  int enc_x = 0; 
	int enc_y = 0;
	double enc_radian = 0;//0~3.14
	int Grid_x = 0;
	int Grid_y = 0;
  //map create
		int Map_x; 
	int Map_y;
	double Map_r = enc_radian * 180 / CV_PI;
	int Total_x;
	int Total_y;

  


int main(int argc, char** argv) {
	
	//640,480,1920,1080,500,500(11/1)
	FILE *fi;
	fi = fopen("/home/user/catkin_ws/src/test_opencv/tsukuba/Img.csv", "r");
	if (fi != NULL){
		while (fscanf(fi, "%d,%d,%d,%d,%d,%d,%d,%d", &IMGWIDTH, &IMGHEIGHT, &ORGWIDTH, &ORGHEIGHT, &MAPWIDTH, &MAPHEIGHT, &Start_x, &Start_y) != EOF){
			printf("IMGWIDTH:%d IMGHEIGHT:%d ORGWIDTH:%d ORGHEIGHT:%d\nMAPWIDTH:%d MAPHEIGHT:%d Start_x:%d Start_y:%d\n", IMGWIDTH, IMGHEIGHT, ORGWIDTH, ORGHEIGHT, MAPWIDTH, MAPHEIGHT,Start_x, Start_y);
		}
		fclose(fi);
	}

	//600,15,600(11/1)
	FILE *fr;
	fr = fopen("/home/user/catkin_ws/src/test_opencv/tsukuba/Resize.csv", "r");
	if (fr != NULL){
		while (fscanf(fr, "%d,%d,%d",&IMGFAR,&IMGNEAR,&IMGWIDTHR) != EOF){
			printf("IMGFAR:%d IMGNEAR:%d IMGWIDTHR:%d\n", IMGFAR, IMGNEAR, IMGWIDTHR);
		}
		fclose(fr);
	}

	//3.85,0.62,40,3,289(11/1)
	FILE *ft;
	ft = fopen("/home/user/catkin_ws/src/test_opencv/tsukuba/Top.csv", "r");
	if (ft != NULL){
		while (fscanf(ft, "%lf,%lf,%lf,%lf,%lf", &Hvc, &Hc, &Angle, &Dvc, &f) != EOF){
			printf("Hvc:%lf Hc:%lf\nAngle:%lf Dvc:%lf f:%lf\n", Hvc, Hc, Angle, Dvc, f);
		}
		fclose(ft);
	}

	
	//double urg_radian[720] int urg_pix_x[720] int urg_pix_y[720]
	FILE *fu;
	fu = fopen("/home/user/catkin_ws/src/test_opencv/tsukuba/grid.csv", "r");
	if (fu != NULL){
		while (fscanf(fu, "%d,%d,%lf", &urg_pix_x[urg_size], &urg_pix_y[urg_size], &urg_radian[urg_size]) != EOF){
			printf("%d,%d,%lf\n", urg_pix_x[urg_size], urg_pix_y[urg_size], urg_radian[urg_size]);
			urg_size++;
		}
		fclose(fu);
	}


	////////////////////////////////////////////////////////////////////////
	//int enc_x,int enc_y,double enc_radian,int Grid_x,int Grid_y
	///////////////////////////////////////////////////////////////////////





	
  int point[4][2];

	Mat camera = (Mat_<double>(3, 3) << 656.88224769690828, 0, 895.69654864028951,
		0, 651.32162740877448, 565.29102950436300,
		0, 0, 1);
	Mat distCoeffs = (Mat_<double>(1, 5) << -0.0013803092701364925, -0.030357817044642622,
		0.0013587349848218459, -0.0021188966756608076, 0.0064651827514648000);


	VideoCapture cap(1);
	if (!cap.isOpened()) {
		printf("cannot openc\n");
		return 1;
	}


	Size org_size(ORGWIDTH, ORGHEIGHT);
	Mat orgImage(Size(ORGWIDTH, ORGHEIGHT), CV_8UC3, Scalar::all(0));
	cap.set(CV_CAP_PROP_FRAME_WIDTH, org_size.width);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, org_size.height);

	Mat clbImage(Size(ORGWIDTH, ORGHEIGHT), CV_8UC3);
	Mat capImage(Size(IMGWIDTH, IMGHEIGHT), CV_8UC3, Scalar::all(0));

	vector<Point2f> src, dst;
	src.push_back(Point2f(0, 0));
	src.push_back(Point2f(orgImage.cols, 0));
	src.push_back(Point2f(orgImage.cols, orgImage.rows));

	dst.push_back(Point2f(0, 0));
	dst.push_back(Point2f(capImage.cols, 0));
	dst.push_back(Point2f(capImage.cols, capImage.rows));

	Mat affine = getAffineTransform(src, dst);
	

	while (1){

		cap >> orgImage;//1920*1080
		//imshow("raw", orgImage);

		clbImage = orgImage.clone();
		undistort(orgImage, clbImage, camera, distCoeffs);

		warpAffine(clbImage, capImage, affine, capImage.size(), CV_INTER_LINEAR);
		imshow("capImage", capImage);//640*480

		Mat grayImage(capImage.rows, capImage.cols, CV_8UC1);
		cvtColor(capImage, grayImage, COLOR_RGB2GRAY);
		
		Mat topImage(capImage.rows, capImage.cols, CV_8UC3);
		topImage.setTo(Scalar(0));

		Mat topImageGray(capImage.rows, capImage.cols, CV_8UC1);
		TopViewKami(point, capImage, grayImage, topImageGray, topImage, IMGWIDTH, IMGHEIGHT, Hvc, Hc, Angle, Dvc, f);
    line(topImage,Point(310,454),Point(330,454),Scalar(0,0,0),5,CV_AA);
		imshow("Top Image", topImage);
		
		Mat cut(Size(342, point[2][1]), CV_8UC3);
		Mat roi(topImage, Rect(topImage.cols / 2 - 171, 0, 342, point[2][1]));
		roi.copyTo(cut);
		//imshow("cut", cut);
		
		int CutWidth = IMGWIDTHR / 5;
		int CutHeight = (IMGFAR - IMGNEAR) / 5;
		Mat resize(Size(CutWidth, CutHeight), CV_8UC3, Scalar::all(0));
		Resize(&cut, &resize);
		//imshow("resize", resize);
		////////////////////////////

				for (int u = 0; u < urg_size; u++){
			UrgLine(resize, resize.cols, urg_pix_x[u] + resize.cols / 2, resize.rows - urg_pix_y[u] + 10 - 1, urg_radian[u]);
		}












    Map_x = enc_x + (MAPWIDTH / 2) - (resize.cols / 2);
		Map_y = enc_y + MAPHEIGHT - resize.rows - 10;
    int k = 0;
    int i = 1;


    Mat map(Size(MAPWIDTH, MAPHEIGHT), CV_8UC3, Scalar(0, 0, 0));
    Mat alphaMap = Mat(map.size(), CV_8UC3);
    Mat grandMap = Mat(map.size(), CV_8UC3, Scalar(0, 0, 0));
    cvtColor(map, alphaMap, CV_RGB2RGBA);
    cvtColor(map, grandMap, CV_RGB2RGBA);

    int MapHst[1000][2];
    string MapName;
    int OldGrid[2] = { 0, 0 };
    Map_r = enc_radian * 180 / CV_PI;
    char IMG[256], IMG2[256], IMG3[256];
		Mat alphaImage = Mat(resize.size(), CV_8UC3);
		cvtColor(resize, alphaImage, CV_RGB2RGBA);
		Alpha(alphaImage);


		if (OldGrid[0] != Grid_x || OldGrid[1] != Grid_y){
			sprintf(IMG3, "/home/user/catkin_ws/src/test_opencv/Image/Grid/Grid%d_%d.png", OldGrid[0], OldGrid[1]);
			imwrite(IMG3, grandMap);
			MapHst[k][0] = OldGrid[0];
			MapHst[k][1] = OldGrid[1];
			for (int m = 0; m <= k; m++){
				if (MapHst[m][0] == Grid_x && MapHst[m][1] == Grid_y){
					MapName = "/home/user/catkin_ws/src/test_opencv/Image/Grid/Grid" + to_string(MapHst[m][0]) + "_" + to_string(MapHst[m][1]) + ".png";
					map = imread(MapName, 1);
					//imshow("map", map);
					cvtColor(map, grandMap, CV_RGB2RGBA);
					alphaImage = Scalar::all(0);
					alphaMap = Scalar::all(0);
					break;
				}
				map = Scalar::all(0);
				cvtColor(map, grandMap, CV_RGB2RGBA);
				alphaImage = Scalar::all(0);
				alphaMap = Scalar::all(0);
			}
			k++;
			OldGrid[0] = Grid_x;
			OldGrid[1] = Grid_y;
		}

		Alpha(alphaMap);
		PinP(alphaMap, alphaImage, Map_r, Map_x, Map_y);
		Grand(grandMap, alphaMap);
		grandMap = alphaMap.clone();
		//imshow("alpha", alphaMap);
		imshow("grand", grandMap);

		if (i%5==0){
			sprintf(IMG, "/home/user/catkin_ws/src/test_opencv/Image/Cap/Cap%03d_%d_%d.jpg", i/5, Total_x, Total_y);
			if(imwrite(IMG, capImage))
        printf("done_capImage\n");
      else
        printf("cannot_write_capImage");

			sprintf(IMG2, "/home/user/catkin_ws/src/test_opencv/Image/Top/Top%03d_%d_%d.jpg", i/5, Total_x, Total_y);
			if(imwrite(IMG2, topImage))
        printf("done_topImage\n");
      else
        printf("cannot_write_topImage");


			sprintf(IMG3, "/home/user/catkin_ws/src/test_opencv/Image/Grid/Grid%d_%d.jpg", Grid_x, Grid_y);
			if(imwrite(IMG3, alphaMap))
        printf("done_alphaMap");
      else
        printf("cannot_write_alphaMap");
		}

		Total_x = enc_x + MAPWIDTH * Grid_x;
		Total_y = enc_y + MAPHEIGHT * Grid_y;
		printf("COUNT:%d_enc:(%d,%d)_Map:(%d,%d,%d)_Grid:(%d,%d)_Global:(%d,%d)\r", i, enc_x, enc_y, Map_x, Map_y, Map_r, Grid_x, Grid_y, Total_x, Total_y);
		i++;
		waitKey(1);
	}
	return 0;
}
