#pragma once
#include "vol_math_ImageVolume.h"
#include "vol_math_Raw3D_Independt.h"
#include "vol_math_GuassFilter.h"

class Anistropic2D
{
private:
	Raw2D src;
	int time;
	int val;
	int method;
public:
	Anistropic2D(void);
	Anistropic2D(Raw2D &src,int time,PIXTYPE value, int method);
	~Anistropic2D(void);
	void Perona_Malik(Raw2D &src);
	Raw2D FourPDiff (Raw2D &src);
	void  FourPDiff_v2(Raw2D &src);
	double funcg(PIXTYPE *array,int dy,int dx);
};

