#ifndef INTERFACE_SWF
#define INTERFACE_SWF

//#include "KDetectMemoryLeak.h"
#include "vol_math_ImageVolume.h"
#include "vol_math_RawImage.h"

#include "vol_math_BilateralFilter.h" //2d bilateralfilter

#include "vol_math_GuassFilter.h"//2d \3d guass filter

#include "vol_math_Anistropic2D.h"
#include "vol_math_2Dtrilateralfilter.h"

extern size_t globalProgressChanged;
extern size_t volatile progressStep;

/**
 \brief	Anisotropic filter interface parameter 
 */

struct  AnistropicII
{
	int time;
	int val; //val=1
	int method; 
	int datatype;
	int threadcount;
	/*
	method:
	1:Perona_Malik();
	2:four_diff
	*/
	AnistropicII(int time,int val,int method,int datatype,int threadcount)
	{
		this->time = time;
		this->val = val;
		this->method = method;
		this->datatype = datatype;
		this->threadcount = threadcount;
	}


};

/**
 \brief	Anistropic i.
 int time;
 int val; //val=1
 int method;
 int threadcount;
 */

struct  AnistropicI
{
	int time;
	int val; //val=1
	int method; 
	int threadcount;
	/*
	method:
	1:Perona_Malik();
	2:four_diff
	*/
	AnistropicI(int time,int val,int method,int threadcount)
	{
		this->time = time;
		this->val = val;
		this->method = method;
		this->threadcount = threadcount;
	}


};
struct  TrilateralfilterI
{
	float sigmaC;//sigmaC=1	spacing domain variance
	float sigmaA;//value  domain variance
	int threadcount;

	TrilateralfilterI(int threadcount,float sigmaC =3)
	{
		this->sigmaC = sigmaC;
		this->threadcount=threadcount;
	}
	TrilateralfilterI(int threadcount,float sigmaC,float sigmaA)
	{
		this->sigmaC = sigmaC;
		this->threadcount=threadcount;
		this->sigmaA;
	}
};

struct BilateralFilterI
{
	double sigmaD;//guass fliter cooper std for space 
	double sigmaR;//guass filter cooper std for pixel
	int threadcount;
	BilateralFilterI(double sigmaD,double sigmaR,int threadcount)
	{
		this->sigmaD=sigmaD;
		this->sigmaR=sigmaR;
		this->threadcount=threadcount;
	}
};

struct GuassFilterI
{
	int halfsize;
	int threadcount;
	GuassFilterI(int halfsize,int threadcount)
	{
		this->halfsize=halfsize;
		this->threadcount=threadcount;
	}
};

struct lowPassI
{
	float threshold;
	lowPassI(float threshold)
	{
		this->threshold =threshold;
	}


};
struct MultiOstuI
{
	int method;
	int classnum; //expexted numbers
	/*
	1\user write the number 
	2\algorithm compute the number
	*/
	MultiOstuI(int method,int classnum)
	{
		this->method=method;
		this->classnum=classnum;
		
	}
};
struct WaterShedsI
{
	int smoothszie;//1.6 neighbor 2. 26 neighbor 3.h no smooth

	int threshold;
	WaterShedsI(int smoothszie,int threshold)
	{
		this->smoothszie=smoothszie;
		this->threshold=threshold;
	}
	WaterShedsI()
	{

	}
};


extern void *doAnistropicI2D_new (Image2D &src,AnistropicI &);

/**
 \brief	Executes the bilateral i 2 d operation.

 \param [in,out]	parameter1	The first parameter.
 \param [in,out]	parameter2	The second parameter.

 \return	null if it fails, else.
 */

extern void *doBilateralI2D_new (Image2D&, BilateralFilterI &);

/**
 \brief	Executes the guass filter i 2 d operation.

 \param [in,out]	parameter1	The first parameter.
 \param [in,out]	parameter2	The second parameter.

 \return	null if it fails, else.
 */

extern void *doGuassFilterI2D_new (Image2D &, GuassFilterI &);

/**
 \brief	Executes the trilateralfilter i 2 d operation.

 \param [in,out]	parameter1	The first parameter.
 \param [in,out]	parameter2	The second parameter.

 \return	null if it fails, else.
 */

extern void *doTrilateralfilterI2D_new ( Image2D &, TrilateralfilterI &);

/**
 \brief	Executes the multi ostu i 2 d operation.

 \param [in,out]	src		  	Source for the.
 \param [in,out]	parameter2	The second parameter.

 \return	null if it fails, else.
 */


#endif
