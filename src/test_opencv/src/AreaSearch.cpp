#include <iostream>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d.hpp>

using namespace std;
using namespace cv;

#define MAPSIZE 500

static int flag = 0;
static int gX = 0;
static int gY = 0;
static Mat Map(Size(1500, 1500), CV_8UC3, Scalar::all(0));

int sgn(int a) {
	if (a >= 0)	return 0;
	else return -1;
}

void Calcgrid(int wx, int wy, int *gx, int *gy){

	*gx = (wx + (MAPSIZE / 2)) / MAPSIZE;
	*gy = wy / MAPSIZE;

	if (*gx == 0) *gx = sgn(wx + 250);
	if (*gy == 0) *gy = sgn(wy);
}

void Calclocal(int wx, int wy, int *lx, int *ly){

	int x, y;
	x = (wx + 250) % MAPSIZE;
	y = wy % MAPSIZE;

	*lx = MAPSIZE + x;
	*ly = (2 * MAPSIZE - 1) - y;

	printf("lx = %d, ly = %d \n", *lx, *ly);
}

void MapResize(Mat *src, Mat *dst) {

	vector<Point2f> src_p, dst_p;
	src_p.push_back(Point2f(0, 0));
	src_p.push_back(Point2f((*src).cols, 0));
	src_p.push_back(Point2f((*src).cols, (*src).rows));

	dst_p.push_back(Point2f(0, 0));
	dst_p.push_back(Point2f((*dst).cols, 0));
	dst_p.push_back(Point2f((*dst).cols, (*dst).rows));

	Mat affine2 = getAffineTransform(src_p, dst_p);
	warpAffine(*src, *dst, affine2, (*dst).size(), CV_INTER_LINEAR);

}

void AreaSearch(const int wx, const int wy, const float deg) {

	int gx, gy;
	Calcgrid(wx, wy, &gx, &gy);

	if (flag == 0 || gX != gx || gY != gy) {
		char str[64];
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				sprintf(str, "./map/map_%d_%d.png", (gx - 1) + j, (gy + 1) - i);
				Mat piece(MAPSIZE, MAPSIZE, CV_8UC1);
				piece = imread(str, CV_LOAD_IMAGE_COLOR);
				if (piece.empty()) {
					piece.setTo(Scalar(0));
				}
				Mat roi(Map, Rect(MAPSIZE * j, MAPSIZE * i, MAPSIZE, MAPSIZE));
				piece.copyTo(roi);
			}
		}
		if(flag == 0)	flag = 1;
	}
	//imshow("map", Map);

	Mat smallmap(Size(600, 600), CV_8UC3, Scalar::all(0));
	MapResize(&Map, &smallmap);
	imshow("smallmap", smallmap);

	int lx, ly;
	Calclocal(wx, wy, &lx, &ly);

	Mat mapping(Map, Rect(lx - (MAPSIZE / 2), ly - (MAPSIZE / 2), MAPSIZE, MAPSIZE));
	imshow("mapping", mapping);

	Point2d ctr(lx, ly);
	Mat affine = getRotationMatrix2D(ctr, deg, 1.0);
	Mat rotate; 
	Map.copyTo(rotate);
	warpAffine(Map, rotate, affine, rotate.size(), CV_INTER_LINEAR);
	//imshow("rotated", rotate);
	
	Mat area(rotate, Rect(lx - 8, ly - 159, 17, 160));
	imshow("area", area);
	
	for (int i = 0; i < 10; i++) {
		
		int b_p = 0;	

		for (int y = 0; y < area.rows/10; y++) {//srcImg.rows

			cv::Vec3b* ptr = area.ptr<cv::Vec3b>(y + (i * area.rows / 10));//ポインタの取得（(y + (i * area.rows / 10))行目の先頭画素のポインタを取得）

			for (int x = 0; x < area.cols; x++) {
				cv::Vec3b bgr = ptr[x];//値の取得
				if (bgr[0] == 0 && bgr[1] == 0 && bgr[2] == 0) b_p++;
			}

		}

		int wariai = b_p * 100 / ((area.rows/10) * area.cols);
		printf("wariai%d = %d\n%d\n", i, wariai, b_p);
	}
	

	
	printf("gx = %d, gy = %d \n", gx, gy);

	return;
}
