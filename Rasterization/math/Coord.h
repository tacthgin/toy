#ifndef __COORD_H__
#define __COORD_H__

class Polar2D
{
public:
	Polar2D(float r, float t);
	float radis;
	float theta;
};

class Cylindrical3D
{
public:
	Cylindrical3D(float r, float t, float zz);
	float radis;
	float theta;
	float z;
};

class Spherical3D
{
public:
	Spherical3D(float r, float t, float p);
	float radis;
	float theta;//与z轴夹角
	float phi;//与x轴夹角
};

#endif //__COORD_H__