#ifndef OPENGL_H
#define OPENGL_H



//#include "ScotsPineVisual.h"
#include <Tree.h>
#include "OpenGLSymbols.h"

#define TABLESIZE 100
#define MY_EDGES 36
#define MY_EDGES_BIG 100
#define MY_EDGES_MIN 16


using namespace Lignum;

static float last_texY = 0;


struct NEEDLE_PLANE
{
	LGMdouble x;
	LGMdouble y;
	LGMdouble z;
	int number;
	LGMdouble dist;
};

struct YEAR_GROWTH
{
	float rad;
	float height;
};




struct year_point
{
	std::vector<METER> rads;
	float height;
	float lenght;
};

struct year_line
{
	std::vector<year_point> points;
};








float GetAngle(PositionVector p);


static float odd_table[TABLESIZE];


static Point mapping[6][6];  //Yksikkonelio on jaettu 6*6 pisteisiin ja jokaisen arvona mapattupiste toruksen pinnalta

void InitDrawing();

void outPut(float x, float y, char *string);

void MakeCylinder(float radius, float rad_top, float length, float rad_limit, float xx=0, float yy=0);

void MakeCylinderWithTop(float radius, float rad_top, float length, float rad_limit, std::vector<METER> &an_rings, int age, float odd);

void MakeYearLines(float radius, float rad_top, float length, std::vector<METER> &an_rings);
void MakeYearLines(std::list<year_point> l);


void MakeWireModel(float radius, float length);

//void draw_foliage_planes(float lenght, float radius, float fol_mas, int age);

void draw_texfoliage_planes(float lenght, float radius, float fol_mas, int age);

int make_texfoliage_planes_lists(Point position, float rot_angle, float rot_x, float rot_y, int number, float lenght, float radius, float fol_mas, int age);

//void DrawCone(branch_in &bri);

void MakeCone(float length, float radius, float max_radius);

void Make3DLeave(float xodd, float yodd, float rad);

void MakeLeave(float x, float y, float rad);

void MakeLeaveTable();

void make_bud();

METER GetMeter(int n, std::vector<METER> l);

Point GetPoint(float x, float y);

float MyGetValue(char *line, int index);

void CrossCylinder(float length, float radius, float rad_top, float ang, float ang_top);

void make_leave(Point petiole_begin, Point petiole_end, PositionVector leaf_normal, double major, double minor);

void make_leave(void);

Point normalize_xy(Point point);

void make_leaflet();

void DrawOrderedNeedles();

#endif
