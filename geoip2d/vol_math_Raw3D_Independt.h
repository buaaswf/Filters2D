#ifndef _VOL_MATH_RAW3D_INDEPENDT_H_
#define _VOL_MATH_RAW3D_INDEPENDT_H_
#ifndef Raw2D_H
#define Raw2D_H
#include <iostream>
#include <string.h>

using namespace std;
#define PIXTYPE float
//typedef unsigned char PIXTYPE;
class Raw2DArray;
class Raw2D
{
private:   			//-----------------DATA----------------- 
	int xsize;		// # of pixels per scanline,
	int ysize;		// # of scanlines in this Raw2D.
	PIXTYPE *data;		// 1D array of PIXTYPE that are accessed as a 2D array.

	void putData(const PIXTYPE *res)
	{
		if (data != NULL)
			delete [] data;
		memcpy(data, res, xsize*ysize);
	}

public:			
	const static int MAXPIXEL = 255;
	const static int  MINPIXEL = 0;
    //qym 2013-12-4
    bool CreateSpace;

	Raw2D(int, int, PIXTYPE*);
	Raw2D(int, int);
	Raw2D(Raw2D* r);
	Raw2D(const Raw2D& r);
	Raw2D(void);		// constructor for 'empty' Raw2Ds
	~Raw2D(void);		// destructor; releases memory

	int size() const { return xsize*ysize; }
	PIXTYPE * getdata()
	{
		return data;	
	}
	/// \brief Swap data with img
	Raw2D& swap(Raw2D& img)
	{
		std::swap(this->xsize, img.xsize);
		std::swap(this->ysize, img.ysize);
		std::swap(this->data, img.data);
		return img;
	}

	Raw2D& operator=(Raw2D img)
	{
		img.swap(*this);
		return *this;
	}

	Raw2D& operator+=(const Raw2D &img)
	{
		for (int i = 0; i < size(); ++i)
			this->data[i] += img.data[i];
		return *this;
	}

	Raw2D & operator+=(const PIXTYPE val)
	{
		for (int i = 0; i < size(); ++i)
		{
			this->data[i] += val;
		}
		return *this;
	}

	Raw2D operator+(const Raw2D &img)
	{
		return Raw2D(*this) += img;
	}

	Raw2D operator+(const PIXTYPE val)
	{
		return Raw2D(*this) += val;
	}

	Raw2D & operator-=( const Raw2D &img)
	{
		for (int i = 0; i<size();++i)
			this->data[i] -= img.data[i];
		return *this;
	}

	Raw2D & operator -= ( const PIXTYPE val)
	{
		for (int i=0;i<size();i++)
			this->data[i]-=val;
		return *this;
	}

	Raw2D operator -(const Raw2D &img)
	{
		return Raw2D(*this)-=img;
	}

	Raw2D operator - (const PIXTYPE val)
	{
		return Raw2D(*this) -= val;
	}

	Raw2D& operator*=(const Raw2D& img)
	{
		for (int i = 0; i < size(); ++i)
			this->data[i] *= img.data[i];
		return *this;
	}

	Raw2D& operator*=(const PIXTYPE val)
	{
		for (int i = 0; i < size(); ++i)
			this->data[i] *= val;
		return *this;
	}

	Raw2D operator*(const Raw2D& img)
	{
		return  Raw2D(*this) *= img;
	}

	Raw2D operator*(const PIXTYPE val)
	{
		return Raw2D(*this) *= val;
	}

	Raw2D& operator/=(const Raw2D& img)
	{
		for (int i = 0; i < size(); ++i)
			this->data[i] /= img.data[i];
		return *this;
	}

	Raw2D& operator/=(const PIXTYPE val)
	{
		for (int i = 0; i < size(); ++i)
			this->data[i] /= val;
		return *this;
	}

	Raw2D operator/(const Raw2D& img)
	{
		return Raw2D(*this) /= img;
	}

	Raw2D operator/(const PIXTYPE val)
	{
		return Raw2D(*this) /= val;
	}

	friend Raw2D operator/(const PIXTYPE val, const Raw2D& img);

	void sizer(int ixsize, int iysize);	// get mem for rectangle of pixels
	void sizer(Raw2D* src);					// get same amt. of mem as 'src'
	int getXsize(void) const {return xsize;}		// get # pixels per scanline
	int getYsize(void) const {return ysize;}		// get # of scanlines.

	inline void put(int ix, int iy, PIXTYPE val)	// write 'val' at location ix,iy.
	{
#ifdef _DEBUG  //only check under debug mode
		if (ix + xsize*iy < size())
		{
#endif
			data[ix + xsize*iy] = val;
#ifdef _DEBUG
		}
		else 
			cout<<"out of size put"<<endl;
#endif
	}

	inline PIXTYPE get(int ix, int iy) {	// read the value at ix,iy.
#ifdef _DEBUG
		if(ix + xsize*iy<=size())
		{
#endif
			return data[ix + xsize*iy]; 
#ifdef _DEBUG
		}
		else 
		{
			cout<<"out of size get"<<endl;
		}
#endif
	}

	PIXTYPE getXY(int ixy)
	{		// read value at 1D address ixy
		if(ixy<xsize*ysize)
		{
			return data[ixy];
		}
		else 
		{
			cout<<"out of size get "<<endl;
			return false;
		}
	}

	void putXY(int ixy,PIXTYPE val){// write value at 1D address ixy
		if (ixy<xsize*ysize)
		{
			data[ixy] = val;
		}
		else cout<<"out of size putxy"<<endl;

	}

	//---------------Trilateral Filter fcns-------------

	//Trilateral filter consisting of gradient filter, adaptive neighborhood
	//computation and detail filter
	void TrilateralFilter(Raw2D* srcImg, PIXTYPE sigmaC); 

	//Computes X and Y gradients of the input image
	void ComputeGradients(Raw2D* pX, Raw2D* pY); 

	//Bilaterally filters  gradients pX and pY 
	void BilateralGradientFilter(Raw2D* pX, Raw2D* pY, Raw2D* pSmoothX, 
		Raw2D* pSmoothY, float sigmaC, float sigmaS, int filterSize); 

	//Builds the stack of min-max image gradients; returns the range variance
	PIXTYPE buildMinMaxImageStack(Raw2D* pX, Raw2D* pY, Raw2DArray* pMinStack,
		Raw2DArray* pMaxStack , int levelMax, float beta); 

	//Finds the adaptive neighborhood size (stack level) 
	//from the min-max gradient stack
	void findAdaptiveRegion(Raw2DArray* pMinStack, Raw2DArray* pMaxStack, PIXTYPE R, int levelMax); 

	//Filters the detail signal and computes the final output image	
	void DetailBilateralFilter(Raw2D* srcImg, Raw2D* pSmoothX, Raw2D* pSmoothY, 
		Raw2D* fTheta, PIXTYPE sigmaCTheta, PIXTYPE sigmaRTheta); 
	bool wipecopy(Raw2D* src);

};

#endif  //Raw2D_H




#ifndef Raw3D_H
#define Raw3D_H

class Raw2DArray {
public:
	Raw2D *z;	// dynam. allocated space for a set of Raw2D objects.
	int zsize;	// # of Raw2D objects stored.

public:							
	Raw2DArray(void);// 'empty' Raw2DArray constructor.
	Raw2DArray(int zsize,Raw2D *src);//swf add for read data 
	~Raw2DArray(void);	// destructor.
	void sizer(int ixsize, int iysize, int izsize); // reserve memory
	void sizer(Raw2DArray* src);			// get same amt. of mem as 'src
	int getZsize(void) {				// return # of Raw2D's we hold;
		return(zsize); 
	};
	int getYsize() {					// # of Raw1D's in zval-th Raw2D;
		return(z[0].getYsize()); 
	};
	int getXsize(){						// # of pixels on yval,zval-th line
		return(z[0].getXsize()); 
	};
	PIXTYPE get(int ix, int iy, int iz) {
		return(z[iz].get(ix,iy));	// write 'val' at location ix,iy,iz. 
	};
	void put(int ix, int iy, int iz, PIXTYPE val) { 
		z[iz].put(ix,iy,val);		//write 'val' at location ix,iy,iz.
	};
	void wipecopy(Raw2DArray& src);			// copy, resize as needed.
};





#endif

#ifndef Raw3D_Independt_H
#define Raw3D_Independt_H
class Raw3D_Independt
{
public:
	Raw3D_Independt(void);
	~Raw3D_Independt(void);
};
#endif

#endif //_VOL_MATH_RAW3D_INDEPENDT_H_
