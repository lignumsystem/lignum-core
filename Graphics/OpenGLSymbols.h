#ifndef OPENGLSYMBOLS_H
#define OPENGLSYMBOLS_H


#define UP 0
#define DOWN 1



enum LIGHT_TYPE { AMBIENT, DIFFUSE, AMBIENT_AND_DIFFUSE, SPECULAR };
enum DRAW_TYPE {stem, wiremodel, waterflow, betula_make_leaves, betula_leaves, betula_ani_leaves, needles, needles_tex, needles_tex_ordered, buds_dead, gliricidia_leaves,buds_alive, year_lines, year_lines_secround};
enum REDRAW_MODE { rd_normal, rd_waterdraw, rd_yearline_gp, rd_yearcircles, rd_manybetulas, rd_cross };
enum CAMERA_MODE { turn_camera, move_camera };


struct LIGHT
{
	LIGHT_TYPE type;
	float value[4];
};

struct LIGHT_VAL 
{
	float LightPosition[4];  
	LIGHT ambient;
	LIGHT specular;
	LIGHT diffuse;
};


const int TREE_BIG = 1;
const int TREE_SMALL = 2;
const int FOLIAGE = 3;
const int NEEDLES = 4;
//const int NEEDLE = 5; ei kaytossa
const int GRP_WIREMODEL = 6;
const int NEEDLES_TEX = 7;
const int ANILEAVE = 8;
const int BUD = 9;
const int BUDS_ALIVE = 10;
const int BUDS_DEAD = 11;
const int YEAR_LINES = 12;
const int CROSS = 13;
const int STEM_CROSS = 14;
const int GRP_TREE = 15;
const int FIRMAMENT_POINTS = 16;
const int ROOT_LIST = 17;
const int LGMFOLIAGE = 18;


const int MANY_TREES = 20;  // yhdelle puulle varattu 3 numeroa
const int FOREST_LIST = 21;

const int CFTREES_LIST = 22;
const int HWTREES_LIST = 23;
const int CFNEEDLES_LIST = 24;
const int HWLEAVES_LIST = 25;
const int FOREST_LIST_STEMS = 26;
const int FOREST_LIST_NEEDLES = 27;

static float NEEDLE_AREA = 0.00015; 
static float NEEDLE_LENGTH = 0.05;      // Needle length

const int NEEDLE_ANGLE0 = 60;        // Needle angle for needles of different ages
const int NEEDLE_ANGLE1 = 50;
const int NEEDLE_ANGLE2 = 40;
const int NEEDLE_ANGLE3 = 30;
const int NEEDLE_ANGLE4 = 20;





#endif
