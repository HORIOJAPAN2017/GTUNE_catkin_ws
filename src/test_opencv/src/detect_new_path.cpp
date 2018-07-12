
#define rob_width 70// /100
#define rob_length 50// /100
#define rob_center_y 9.2// /100
#define margin 50// /100
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

//ベクトル計算関数(長さ、角度、単位ベクトル)
/*
**float vec_x     入力:ベクトルx
**float vec_y     入力:ベクトルy
**float *vec_len  入力:ベクトル長さポインタ
**float *vec_dig  入力:ベクトル角度ポインタ
**float *u_vec_x  入力:単位ベクトルxポインタ
**float *u_vec_y  入力:単位ベクトルyポインタ
*/
void vector_cal_unit(float vec_x, float vec_y, float*vec_len, float*vec_dig, float *u_vec_x, float *u_vec_y)
{
	*vec_len = sqrtf(powf(vec_x, 2) + powf(vec_y, 2));
	*vec_dig = atanf(vec_x / vec_y) / M_PI * 180;
	*u_vec_x = vec_x / *vec_len;
	*u_vec_y = vec_y / *vec_len;
}
//ベクトル計算関数(長さ、角度)
/*
**float vec_x     入力:ベクトルx
**float vec_y     入力:ベクトルy
**float*vec_len   入力:ベクトル長さポインタ
**float*vec_dig   入力:ベクトル角度ポインタ
*/
void vector_cal(float vec_x, float vec_y, float*vec_len, float*vec_dig)
{
	*vec_len = sqrtf(powf(vec_x, 2) + powf(vec_y, 2));
	*vec_dig = atanf(vec_y / vec_x) / M_PI  * 180;
}

/*衝突判定関数(移動時)
**  float coord_x     初期位置(x座標)
**  float coord_y     初期位置(y座標)
**  float dis         移動距離
**  float rot_deg     回転角度
*/
bool route_bounce( float **urg_data, int count, float coord_x, float coord_y, float dis, float rot_deg)
{
	float **p_vec;
	int bounce = 0, judge[2] = { 0, 0 }, i, j;
	float corner[4][2], base_vec[2][2], vec_len[2];
	/*vv*/
	float dis1, dis2, rad1, rad2;

	p_vec = (float **)malloc(sizeof(float *) *count);
	for (i = 0; i < count; i++)
	{
		p_vec[i] = (float *)malloc(sizeof(float *) * 2);
	}

	vector_cal(rob_width / 2 + margin, rob_center_y + margin, &dis1, &rad1);
	vector_cal(rob_width / 2 + margin, rob_length - rob_center_y + margin, &dis2, &rad2);
	dis1 = sqrtf(powf(rob_center_y + margin, 2) + powf(rob_width / 2 + margin, 2));
	dis2 = sqrtf(powf(rob_length - rob_center_y + margin, 2) + powf(rob_width / 2 + margin, 2));
	rad1 = acosf((rob_width / 2 + margin) / dis1);
	rad2 = acosf((rob_width / 2 + margin) / dis2);
	corner[1][0] = -coord_x  - dis1*cosf(rad1 - (rot_deg*M_PI / 180)) - dis*sinf((rot_deg*M_PI / 180));
	corner[1][1] = -coord_y  - dis1*sinf(rad1 - (rot_deg*M_PI / 180)) - dis*cosf((rot_deg*M_PI / 180));


	vec_len[0] = rob_width + margin * 2;
	vec_len[1] = rob_length + margin * 2+dis;
	base_vec[0][0] = -vec_len[0] * sinf((rot_deg - 90)*M_PI / 180);
	base_vec[0][1] = -vec_len[0] * cosf((rot_deg - 90)*M_PI / 180);
	base_vec[1][0] = -vec_len[1] * sinf((rot_deg - 180)*M_PI / 180);
	base_vec[1][1] = -vec_len[1] * cosf((rot_deg - 180)*M_PI / 180);
	for (i = 0; i < count; i++)
	{

		p_vec[i][0] =  + urg_data[i][0] - (-coord_x - dis1*cosf(rad1 - (rot_deg*M_PI / 180)))+dis*sinf((rot_deg*M_PI / 180));
		p_vec[i][1] =  - urg_data[i][1] - (-coord_y - dis1*sinf(rad1 - (rot_deg*M_PI / 180))) + dis*cosf((rot_deg*M_PI / 180));
	}

	
	
	for (j = 0; j < count; j++)
	{
		for (i = 0; i < 2; i++)
		{
			judge[i] = (0 <= (base_vec[i][0] * p_vec[j][0] + base_vec[i][1] * p_vec[j][1]) / powf(vec_len[i], 2) && (base_vec[i][0] * p_vec[j][0] + base_vec[i][1] * p_vec[j][1]) / powf(vec_len[i], 2) <= 1);
		}
		if ((judge[0] + judge[1]) > 1)
		{
			return 1;
		}
	}
	return 0;

}
/*
**引数リスト(URGデータfloat URGdata[count][2]、カウント数int count、現在位置float coord[2]、中継float relay[2]、新しい点の配列のポインタfloat *new_relay)
**
**URGデータfloat URGdata[count][2]
**カウント数int count
**現在位置float coord[2]
**中継点 float relay[2]
**新しい点の配列のポインタfloat *add_relay_point
**
*/
int route_point_check(float **urg_data, int count, float coord[2], float relay_point[2], float add_relay_point[2])
{
	int i = 0;
	float local_y = 5, local_x = 5, search_dis_deg[2], route_search_dis_deg[2];
	float  relay_dis_rad[3], relay_unit_vec[2];
	vector_cal_unit(relay_point[0], relay_point[1], &relay_dis_rad[0], &relay_dis_rad[1], &relay_unit_vec[0], &relay_unit_vec[1]);
	if (0 == route_bounce(urg_data, count, coord[0], coord[1], relay_dis_rad[0], relay_dis_rad[1]))
	{
		return 1;
	}
	while (local_y<relay_dis_rad[0])
	{
		local_x = 5;
		while (abs(local_x) <= 200)
		{
			
			if (local_x > 0)
			{
				local_x += 5;
			}
			vector_cal(local_y, local_x, &search_dis_deg[0], &search_dis_deg[1]);
			if (0 == route_bounce( urg_data, count, coord[0], coord[1], search_dis_deg[0], search_dis_deg[1] - relay_dis_rad[1]))
			{

				vector_cal(relay_dis_rad[0] - local_y, local_x, &route_search_dis_deg[0], &route_search_dis_deg[1]);
				if (0 == route_bounce( urg_data, count, coord[0] + (local_y*relay_unit_vec[0] + local_x*relay_unit_vec[1]), coord[1] + (local_y*relay_unit_vec[1] + local_x*relay_unit_vec[0]), route_search_dis_deg[0], -route_search_dis_deg[1] + relay_dis_rad[1]))
				{
					add_relay_point[0] = coord[0] - (local_y*relay_unit_vec[0] + local_x*relay_unit_vec[1]);
					add_relay_point[1] = coord[1] + (local_y*relay_unit_vec[1] + local_x*relay_unit_vec[0]);
					return 2;
				}

			}

			local_x = -local_x;
		}
		local_y += 5;
	}
	return 0;
}

void main()
{
	int count = 0, i;
	float relay_point[2], add_relay_point[2];
	relay_point[0] = 0; // /100
	relay_point[1] = 250;// /100
	float x, y,rad;

	float **urg_data;

	float coord[2] = { 0, 0 };



	FILE *fp;
	char *fname = "grid4.csv";
	if ((fp = fopen(fname, "r")) == NULL)
	{
		printf("%sのオープンに失敗しました.\n", fname);
		return;
	}
	
	//点数カウント
	while (fscanf(fp, "%f,%f,%f", &x, &y, &rad) != EOF)
	{
		count++;
	}
	fclose(fp);
	
	urg_data = (float **)malloc(sizeof(float *) * count);
	for (i = 0; i < count; i++)
	{
		urg_data[i] = (float *)malloc(sizeof(float *)*3);
	}

	
	if ((fp = fopen(fname, "r")) == NULL)
	{
		printf("%sのオープンに失敗しました.\n", fname);
		return;
	}
	i = 0;
	while (fscanf(fp, "%f,%f,%f", &x, &y, &rad) != EOF)
	{
		urg_data[i][0] = x;// /100
		urg_data[i][1] = y;
		urg_data[i][2] = rad;
		i++;
	}
	fclose(fp);
	
	if (2 == route_point_check(urg_data, count, coord, relay_point, add_relay_point))
	{
		printf("%f,%f", add_relay_point[0], add_relay_point[1]);
	}
}
