#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp> 
#include <opencv2/opencv.hpp>
#include <iostream>

#include "MovingObj.h"

#include "sensor_msgs/LaserScan.h"

#define PI 3.14159265359


using namespace std;


struct setup{

	int window_width = 600;
	int window_height = 600;

	int grid_width = 20;

	int depth_renge = 600;

	int side_renge = 300;

	float ang = 20 * 3.1415 / 180;

	float d_dist = 50;

	int gridnum_x = 30;
  int gridnum_y = 30;
};

setup set;

void URGpoint::set_position(double encX, double encY, double encth, long time){

	posX = (long)(encX*1000);
	posY = (long)(encY*1000);

	posth = encth;
	
	time_stamp = time;
	
}


void URGpoint::move_change(long Xmove, long Ymove, float rad){

	xypos pos, move, nowpos;
	move.x = Xmove;
	move.y = Ymove;


	for (int i = 0; i < num; i++){
		pos.x = x[i];
		pos.y = y[i];
		nowpos = move_pos(pos, move, rad);
		Xmoved[i] = nowpos.x;
		Ymoved[i] = nowpos.y;
	}
}


xypos URGpoint::move_pos(xypos&a, xypos&move, float rad){

	xypos nowpos;

	nowpos.x = a.x*cos(rad) - a.y*sin(rad) - move.x;
	nowpos.y = a.x*sin(rad) + a.y*cos(rad) - move.y;

	return nowpos;

}

void URGpoint::argchange(){

	int *p_data;
	int i, j;
	arg_num = 0;

	p_data = (int*)malloc(set.gridnum_x*set.gridnum_y*sizeof(int));

	for (i = 0; i < set.gridnum_y; i++) {
		for (j = 0; j < set.gridnum_x; j++) {
			p_data[i*set.gridnum_y+j] = 0;
		}
	}

	for (i = 0; i < num; i++){
		

		int p_x = set.gridnum_x-(Xmoved[i] / (set.grid_width*10));
		int p_y = set.gridnum_y - ((y[i] + (set.side_renge*10)) / set.grid_width);
		
		if (p_x < set.gridnum_x && p_y> 0&& p_y< set.gridnum_y){
			p_data[p_x*set.gridnum_x+p_y] += 1;
			//printf("p_data,%d,%d,%d\n", p_x, p_y, p_data[p_x][p_y]);
		}
	}
	for (i = 0; i<(set.gridnum_x*set.gridnum_y); i++){
		//printf("p_data,%d,%d\n", i, j);
		if (p_data[i] > 4) {
			//printf("p_data,%d,%d\n", i, j-20);
			arg[arg_num] = 1;
			arg_num++;
		}
		else {
			arg[arg_num] = 0;
			arg_num++;
		}	
	}
}

cv::Mat showImg(cv::Size(set.window_width, set.window_height), CV_8UC3, cv::Scalar(255, 255, 255));

int checkEdgh(int grid_x, int grid_y, range r, int *arg){


	if (r.up != 0 && r.left%grid_x != 0){
		if (arg[grid_x * (r.up - 1) + (r.left - 1)] == 1){
			arg[grid_x * (r.up - 1) + (r.left - 1)] = 2;
			return 1;
		}
	}

	if (r.up != 0){
		for (int i = r.left; i <= r.right; i++){
			if (arg[grid_x * (r.up - 1) + i] == 1){
				arg[grid_x * (r.up - 1) + i] = 2;
				return 2;
			}
		}
	}

	if (r.up != 0 && r.right%grid_x != (grid_x - 1)){
		if (arg[grid_x * (r.up - 1) + (r.right + 1)] == 1){
			arg[grid_x * (r.up - 1) + (r.right + 1)] = 2;
			return 3;
		}
	}

	if (r.left%grid_x != 0){
		for (int i = r.up; i <= r.bottom; i++){
			if (arg[grid_x * i + (r.left - 1)] == 1){
				arg[grid_x * i + (r.left - 1)] = 2;
				return 4;
			}
		}
	}

	if (r.right%grid_x != (grid_x - 1)){
		for (int i = r.up; i <= r.bottom; i++){
			if (arg[grid_x * i + (r.right + 1)] == 1){
				arg[grid_x * i + (r.right + 1)] = 2;
				return 5;
			}
		}
	}

	if (r.bottom != (grid_y - 1) && r.left%grid_x != 0){
		if (arg[grid_x * (r.bottom + 1) + (r.left - 1)] == 1){
			arg[grid_x * (r.bottom + 1) + (r.left - 1)] = 2;
			return 6;
		}
	}

	if (r.bottom != (grid_y - 1)){
		for (int i = r.left; i <= r.right; i++){
			if (arg[grid_x * (r.bottom + 1) + i] == 1){
				arg[grid_x * (r.bottom + 1) + i] = 2;
				return 7;
			}
		}
	}

	if (r.bottom != (grid_y - 1) && r.right%grid_x != (grid_x - 1)){
		if (arg[grid_x * (r.bottom + 1) + (r.right + 1)] == 1){
			arg[grid_x * (r.bottom + 1) + (r.right + 1)] = 2;
			return 8;
		}
	}

	return 0;

}


int DetectObject(int *arg, Detected_object *ob, int *status, int j1, int j2, int j3){

	int k = 0;
	int objectnum = 0;

	for (int i = 0; i < set.gridnum_y; i++){
		for (int j = 0; j < set.gridnum_x; j++){
			if ((status[k] == j1 || status[k] == j2 || status[k] == j3) && arg[k] != 2){
				arg[k] = 2;

				objectnum++;
				ob[objectnum - 1].frg = 1;

				ob[objectnum - 1].range.bottom = ob[objectnum - 1].range.up = i;
				ob[objectnum - 1].range.left = ob[objectnum - 1].range.right = j;

				int range_status;
				range_status = checkEdgh(set.gridnum_x, set.gridnum_y, ob[objectnum - 1].range, arg);
				//cout << range_status << endl;

				while (range_status != 0){
					if (range_status == 1 || range_status == 2 || range_status == 3){
						ob[objectnum - 1].range.up = ob[objectnum - 1].range.up - 1;
					}
					if (range_status == 1 || range_status == 4 || range_status == 6){
						ob[objectnum - 1].range.left = ob[objectnum - 1].range.left - 1;
					}
					if (range_status == 3 || range_status == 5 || range_status == 8){
						ob[objectnum - 1].range.right = ob[objectnum - 1].range.right + 1;
					}
					if (range_status == 6 || range_status == 7 || range_status == 8){
						ob[objectnum - 1].range.bottom = ob[objectnum - 1].range.bottom + 1;
					}

					range_status = checkEdgh(set.gridnum_x, set.gridnum_y, ob[objectnum - 1].range, arg);
					//cout << range_status << endl;
				}

				ob[objectnum - 1].center_position.x = ((float)(ob[objectnum - 1].range.right) / 2 + float(ob[objectnum - 1].range.left) / 2) + 0.5;
				ob[objectnum - 1].center_position.y = ((float)(ob[objectnum - 1].range.bottom) / 2 + float(ob[objectnum - 1].range.up) / 2) + 0.5;

			}
			k++;
		}
	}



	/*	for (int i = 0; i < 30; i++){
	if (ob[i].frg == 0){
	break;
	}


	cout <<i<<"  :"<< (int)(ob[i].center_position.x) << " , " << (int)(ob[i].center_position.y) << endl;
	cout << endl;
	}
	*/

	return objectnum;


}


int DetectMovingobject(int *arg1, int *arg2, int *arg3, double time1, double time2, pair_movingobject *moving_obj)
{

	int gridstep_x, gridstep_y;
	//int gridnum_x, gridnum_y;

	int *arg_status;


	gridstep_x = set.window_height / set.gridnum_x;
	gridstep_y = set.window_width / set.gridnum_y;

	arg_status = (int*)malloc(set.gridnum_x*set.gridnum_y*sizeof(int));


	showImg = cv::Scalar::all(255);

	cv::rectangle(showImg, cv::Point((set.window_width / 2) - (gridstep_x * 7), set.window_height - (gridstep_y * 14)), cv::Point((set.window_width / 2) + (gridstep_x * 7), set.window_height - (gridstep_y * 10)), cv::Scalar(150, 250, 0), -1, CV_AA);
	cv::rectangle(showImg, cv::Point((set.window_width / 2) - (gridstep_x * 7), set.window_height - (gridstep_y * 10)), cv::Point((set.window_width / 2) + (gridstep_x * 7), set.window_height), cv::Scalar(200, 255, 255), -1, CV_AA);
	cv::rectangle(showImg, cv::Point((set.window_width / 2) - (gridstep_x * 2), set.window_height - (gridstep_y * 5)), cv::Point((set.window_width / 2) + (gridstep_x * 2), set.window_height), cv::Scalar(100, 100, 255), -1, CV_AA);



	int k = 0;
	for (int i = 0; i < (set.window_height / gridstep_y); i++){
		for (int j = 0; j < (set.window_width / gridstep_x); j++){

			//cv::rectangle(showImg, cv::Point(1 + (i*gridstep_x), 1 + (j*gridstep_y), cv::Point(1 + (i*gridstep_x), 1 + (j*gridstep_y), cv::Scalar(0, 0, 255), 3, 3);
			//cv::rectangle(showImg, cv::Point(0, 0), cv::Point(200, 200), cv::Scalar(200, 0, 0), 5, 4);
			cv::rectangle(showImg, cv::Point((j*gridstep_x), (i*gridstep_y)), cv::Point((j*gridstep_x) + gridstep_x, (i*gridstep_y) + gridstep_y), cv::Scalar(0, 0, 0), 2, 3);

			if (arg1[k] == 0 && arg2[k] == 0 && arg3[k] == 0){
				cv::rectangle(showImg, cv::Point((j*gridstep_x), (i*gridstep_y)), cv::Point((j*gridstep_x) + gridstep_x + 1, (i*gridstep_y) + gridstep_y + 1), cv::Scalar(0, 0, 0), 2, 3);
				arg_status[k] = 0;
			}
			else if (arg1[k] == 1 && arg2[k] == 1 && arg3[k] == 1){
				cv::rectangle(showImg, cv::Point((j*gridstep_x) + 1, (i*gridstep_y) + 1), cv::Point((j*gridstep_x) + gridstep_x + 1, (i*gridstep_y) + gridstep_y + 1), cv::Scalar(0, 0, 0), -1, CV_AA);
				arg_status[k] = -1;
			}
			else if (arg1[k] == 1 && arg2[k] == 0 && arg3[k] == 0){
				cv::rectangle(showImg, cv::Point((j*gridstep_x) + 1, (i*gridstep_y) + 1), cv::Point((j*gridstep_x) + gridstep_x + 1, (i*gridstep_y) + gridstep_y + 1), cv::Scalar(255, 0, 0), -1, CV_AA);
				arg_status[k] = 1;
			}
			else if (arg1[k] == 0 && arg2[k] == 1 && arg3[k] == 0){
				cv::rectangle(showImg, cv::Point((j*gridstep_x) + 1, (i*gridstep_y) + 1), cv::Point((j*gridstep_x) + gridstep_x + 1, (i*gridstep_y) + gridstep_y + 1), cv::Scalar(0, 150, 0), -1, CV_AA);
				arg_status[k] = 2;
			}
			else if (arg1[k] == 0 && arg2[k] == 0 && arg3[k] == 1){
				cv::rectangle(showImg, cv::Point((j*gridstep_x) + 1, (i*gridstep_y) + 1), cv::Point((j*gridstep_x) + gridstep_x + 1, (i*gridstep_y) + gridstep_y + 1), cv::Scalar(0, 150, 0), -1, CV_AA);
				arg_status[k] = 3;
			}
			else if (arg1[k] == 1 && arg2[k] == 1 && arg3[k] == 0){
				cv::rectangle(showImg, cv::Point((j*gridstep_x) + 1, (i*gridstep_y) + 1), cv::Point((j*gridstep_x) + gridstep_x + 1, (i*gridstep_y) + gridstep_y + 1), cv::Scalar(100, 100, 0), -1, CV_AA);
				arg_status[k] = 4;
			}
			else if (arg1[k] == 0 && arg2[k] == 1 && arg3[k] == 1){
				cv::rectangle(showImg, cv::Point((j*gridstep_x) + 1, (i*gridstep_y) + 1), cv::Point((j*gridstep_x) + gridstep_x + 1, (i*gridstep_y) + gridstep_y + 1), cv::Scalar(100, 100, 0), -1, CV_AA);
				arg_status[k] = 5;
			}
			else if (arg1[k] == 1 && arg2[k] == 0 && arg3[k] == 1){
				cv::rectangle(showImg, cv::Point((j*gridstep_x) + 1, (i*gridstep_y) + 1), cv::Point((j*gridstep_x) + gridstep_x + 1, (i*gridstep_y) + gridstep_y + 1), cv::Scalar(100, 100, 0), -1, CV_AA);
				arg_status[k] = 6;
			}
			k++;
		}
	}

	cv::circle(showImg, cv::Point(set.window_width / 2, set.window_height), 15, cv::Scalar(0, 0, 0), -1, CV_AA);


	Detected_object o1[30], o2[30], o3[30];
	DetectObject(arg1, o1, arg_status, 1, 4, 6);
	DetectObject(arg2, o2, arg_status, 2, 4, 5);
	DetectObject(arg3, o3, arg_status, 5, 3, 6);



	//pair_movingobject moving_obj[10];

	float vec1x, vec1y, vec2x, vec2y;
	float min_dist = 600.0, dist;
	float min_ang = 4.0, ang;
	float min_d_dist = 600.0, d_dist;
	int min_num[3];

	int num = 0;


	for (int i = 0; i < 30; i++){
		min_dist = 600.0;
		min_ang = 4.0;
		min_d_dist = 600.0;

		if (o1[i].frg == 0){
			break;
		}
		for (int j = 0; j < 30; j++){
			if (o2[j].frg == 0){
				break;
			}
			vec1x = o1[i].center_position.x - o2[j].center_position.x;
			vec1y = o1[i].center_position.y - o2[j].center_position.y;

			for (int k = 0; k < 30; k++){
				//cout << i << j << k << endl;
				if (o3[k].frg == 0){
					break;
				}
				vec2x = o2[j].center_position.x - o3[k].center_position.x;
				vec2y = o2[j].center_position.y - o3[k].center_position.y;

				ang = acos((vec1x*vec2x + vec1y*vec2y) / (sqrt(vec1x*vec1x + vec1y*vec1y)*sqrt(vec2x*vec2x + vec2y*vec2y)));
				dist = sqrt((vec1x + vec2x)*(vec1x + vec2x) + (vec1y*vec2y)*(vec1y*vec2y))*set.grid_width;
				d_dist = abs(sqrt(vec1x*vec1x) - sqrt(vec1y*vec2y))*set.grid_width;

				if (ang < min_ang){
					if (min_ang < set.ang){
						if (d_dist < min_d_dist){
							if (dist < min_dist){
								//cout << "‹——£" << endl;
								min_ang = ang;
								min_dist = dist;
								min_d_dist = d_dist;
								min_num[0] = i;
								min_num[1] = j;
								min_num[2] = k;
							}
						}
						else{
							//cout << "‹——£‚Ì‚³" << endl;
							min_ang = ang;
							min_dist = dist;
							min_d_dist = d_dist;
							min_num[0] = i;
							min_num[1] = j;
							min_num[2] = k;
						}
					}
					else{
						//cout << "Šp“x" << endl;
						min_ang = ang;
						min_dist = dist;
						min_d_dist = d_dist;
						min_num[0] = i;
						min_num[1] = j;
						min_num[2] = k;
					}
				}
			}	//end k
		}	//end j
		if (min_ang < set.ang){
			moving_obj[num].frg = 1;
			moving_obj[num].arg1 = min_num[0];
			moving_obj[num].arg2 = min_num[1];
			moving_obj[num].arg3 = min_num[2];

			moving_obj[num].pos1 = o1[min_num[0]].center_position;
			moving_obj[num].pos2 = o2[min_num[1]].center_position;
			moving_obj[num].pos3 = o3[min_num[2]].center_position;

			moving_obj[num].Vecx = o1[min_num[0]].center_position.x - o3[min_num[2]].center_position.x;
			moving_obj[num].Vecy = o1[min_num[0]].center_position.y - o3[min_num[2]].center_position.y;

			float Vecsize;
			Vecsize = sqrt((moving_obj[num].Vecx*moving_obj[num].Vecx) + (moving_obj[num].Vecy*moving_obj[num].Vecy));

			moving_obj[num].Vecx = moving_obj[num].Vecx / Vecsize;
			moving_obj[num].Vecy = moving_obj[num].Vecy / Vecsize;

			moving_obj[num].vel = (Vecsize*set.grid_width / 100) / (time2);

			moving_obj[num].now = o1[min_num[0]];

			num++;
		}

	}	//end i

	for (int unko = 0; unko < num; unko++){

		cv::rectangle(showImg, cv::Point((o1[moving_obj[unko].arg1].range.left*gridstep_x), (o1[moving_obj[unko].arg1].range.up*gridstep_y)),
			cv::Point((o1[moving_obj[unko].arg1].range.right*gridstep_x) + gridstep_x + 1, (o1[moving_obj[unko].arg1].range.bottom*gridstep_y) + gridstep_y + 1), cv::Scalar(0, 0, 255), 2, CV_AA);

		cv::circle(showImg, cv::Point((int)(moving_obj[unko].pos1.x * (float)gridstep_x), (int)(moving_obj[unko].pos1.y * (float)gridstep_y)), 5, cv::Scalar(0, 0, 255), -1, CV_AA);

		cv::line(showImg, cv::Point((int)(moving_obj[unko].pos1.x * (float)gridstep_x), (int)(moving_obj[unko].pos1.y * (float)gridstep_y)),
			cv::Point((int)((moving_obj[unko].pos1.x + moving_obj[unko].Vecx*moving_obj[unko].vel * 20) * (float)gridstep_x), (int)((moving_obj[unko].pos1.y + moving_obj[unko].Vecy*moving_obj[unko].vel * 20) * (float)gridstep_y)), cv::Scalar(0, 0, 255), 2, CV_AA);

		cv::putText(showImg, to_string(unko), cv::Point((int)((moving_obj[unko].pos1.x + moving_obj[unko].Vecx * 5) * (float)gridstep_x), (int)((moving_obj[unko].pos1.y + moving_obj[unko].Vecy * 5) * (float)gridstep_y)), cv::FONT_HERSHEY_SIMPLEX, 1.2, cv::Scalar(0, 0, 200), 2, CV_AA);

		cout << unko << " , " << moving_obj[unko].vel;
		cout << endl;
	}
	cv::imshow("red", showImg);


	int status=0;
	for (int i=set.gridnum_y-10; i < set.gridnum_x*set.gridnum_y; i++){
		int raw, column;
		raw = (int)((double)i / (double)set.gridnum_x);
		column = i%set.gridnum_x;

		if ((arg_status[i] == -1) || (arg_status[i] == 1) || (arg_status[i] == 4) || (arg_status[i] == 6)){
			if ((raw >= set.gridnum_y - 14) && (raw <= set.gridnum_y - 10) && (column >= (set.gridnum_x / 2) - 7) && (column <= (set.gridnum_x / 2) + 6)){
				return -1;
			}
			else if ((raw >= set.gridnum_y - 10) && (raw < set.gridnum_y-5) && (column >= (set.gridnum_x / 2) - 7) && (column <= (set.gridnum_x / 2) + 6)){
				if (status != 2 && status != 3){
					status = 1;
				}
				else if (status == 2){
					status = 4;
				}
				else if (status == 3){
					status = 5;
				}
			}
			else if ((raw >= set.gridnum_y - 5) && (raw < set.gridnum_y) && (column >= (set.gridnum_x / 2) - 7) && (column <= (set.gridnum_x / 2) - 3)){
				if (status != 1 && status != 3){
					status = 2;
				}
				else if (status == 1){
					status = 4;
				}
				else if (status == 3){
					status = 6;
				}

			}
			else if ((raw >= set.gridnum_y - 5) && (raw < set.gridnum_y) && (column >= (set.gridnum_x / 2) + 2) && (column <= (set.gridnum_x / 2) + 6)){
				if (status != 1 && status != 2){
					status = 3;
				}
				else if (status == 1){
					status = 5;
				}
				else if (status == 2){
					status = 6;
				}
			}
			else if ((raw>=set.gridnum_y - 14) && (raw<=set.gridnum_y - 10) && (column>=(set.gridnum_x / 2) - 7) && (column <= (set.gridnum_x / 2) + 6)){
				status = 10;
			}
		}
	}
	if (status != 10){
		return (status);
	}
	

	for (int i = 0; i < 10; i++){
		if (moving_obj[i].frg == 0){
			break;
		}
		if ((moving_obj[i].now.range.bottom>15) && (moving_obj[i].now.range.left > 7) && (moving_obj[i].now.range.right < 22)){
			if (moving_obj[i].Vecy < 0){
				status = 7;
				return(7);
			}
		}
	}

	return(10);




	cv::waitKey(100);

	

}


void ReadSampleCSV(char filename[], int *arg){

	FILE *fp;
	char buf[256];
	int i;

	fopen_s(&fp, filename, "r");
	i = 0;

	while (fgets(buf, 256, fp) != NULL){

		sscanf_s(buf, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", arg + (i * 30), arg + 1 + (i * 30), arg + 2 + (i * 30), arg + 3 + (i * 30), arg + 4 + (i * 30),
			arg + 5 + (i * 30), arg + 6 + (i * 30), arg + 7 + (i * 30), arg + 8 + (i * 30), arg + 9 + (i * 30),
			arg + 10 + (i * 30), arg + 11 + (i * 30), arg + 12 + (i * 30), arg + 13 + (i * 30), arg + 14 + (i * 30),
			arg + 15 + (i * 30), arg + 16 + (i * 30), arg + 17 + (i * 30), arg + 18 + (i * 30), arg + 19 + (i * 30),
			arg + 20 + (i * 30), arg + 21 + (i * 30), arg + 22 + (i * 30), arg + 23 + (i * 30), arg + 24 + (i * 30),
			arg + 25 + (i * 30), arg + 26 + (i * 30), arg + 27 + (i * 30), arg + 28 + (i * 30), arg + 29 + (i * 30));
		i++;

	}
	fclose(fp);

	for (int i = 0; i < 30; i++){
		for (int j = 0; j < 30; j++){
			cout << arg[i * 30 + j] << ",";
		}
		cout << endl;
	}

	cout << endl;
	cout << endl;
	cout << endl;

}


int main(void){

	URGpoint now_input;
	URGpoint buf[2];

	buf[1].scanURG5();
	buf[1].set_position(0.0, 0.0, 0.1, 50000);
	Sleep(5000);

	buf[0].scanURG5();
	buf[0].set_position(0.0, 0.0, 0.1, 50000);
	Sleep(5000);
	

	while (1){
		
		now_input.scanURG5();
		now_input.set_position(0.0, 0.0, 0.1, 50000);
		
		now_input.move_change(0, 0, 0.0);
		buf[0].move_change(now_input.posX - buf[0].posX, now_input.posY - buf[0].posY, now_input.posth - buf[0].posth);
		buf[1].move_change(now_input.posX - buf[1].posX, now_input.posY - buf[1].posY, now_input.posth - buf[1].posth);

		now_input.argchange();
		buf[0].argchange();
		buf[1].argchange();
		
		pair_movingobject mv_obj[10];
		int status;
		status = DetectMovingobject(now_input.arg, buf[0].arg, buf[1].arg, (double)(now_input.time_stamp - buf[0].time_stamp) / 1000, (double)(now_input.time_stamp - buf[1].time_stamp) / 1000, mv_obj);

		buf[1] = buf[0];
		buf[0] = now_input;

		Sleep(5000);
		
	}

}
