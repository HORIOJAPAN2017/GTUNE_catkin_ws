struct point{
	float x;
	float y;

};

struct range{
	int up;
	int bottom;
	int left;
	int right;
};

struct Detected_object{

	int frg = 0;

	point center_position;

	range range;

};

struct pair_movingobject{

	int arg1;
	int arg2;
	int arg3;

	point pos1;
	point pos2;
	point pos3;

	Detected_object now;

	float Vecx;
	float Vecy;

	float vel;

	int frg = 0;

};



//for_urg
struct xypos {
	long x;
	long y;
};


class URGpoint
{
public:

	/*単位[mm]*/

	//取得した点
	long x[4000];
	long y[4000];

	int num;


	long time_stamp; //取得時間のタイムスタンプ


	
	//移動後の点
	long Xmoved[4000];
	long Ymoved[4000];
	

	int arg[800];
	int arg_num;

	long posX, posY;
	double posth;

	void scanURG5((int num_of_scan,float start_rad,float end_rad,float resolution,float *range ,float urg_max,float urg_min);
	void set_position(double encX, double encY, double encth, long time);
	void move_change(long Xmove, long Ymove, float rad);
	xypos move_pos(xypos&a, xypos&move, float rad);
	void argchange();
	void output();

};
