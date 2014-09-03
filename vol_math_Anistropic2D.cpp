#include "vol_math_Anistropic2D.h"

Anistropic2D::Anistropic2D(Raw2D &data,int time,PIXTYPE value, int method)
{
	this->src=data;
	this->time=time;
	val=value;
	this->method=method;
	if (method==0)
	{
		Perona_Malik(src);
	} 
	else
	{
		FourPDiff_v2(src);
		data = src;
	}
}


Anistropic2D::~Anistropic2D(void)
{
}

void  Anistropic2D::Perona_Malik(Raw2D &data)
{
	//P-M function  2nd-order PDE denoise
	PIXTYPE a=1,sum;
	int z,y,x,K,j,i;
	Raw2D d(data);//create new space 
	Raw2D s(data);//create new space 
	PIXTYPE *around=new PIXTYPE[6];
	for (i = 0; i < time; i++)
	{

			for (y=1;y<src.getYsize()-1;y++)
			{
				for (x=1;x<src.getXsize()-1;x++)
				{
					around[0]=d.get(x-1,y)-d.get(x,y);
					around[1]=d.get(x,y-1)-d.get(x,y);
					around[2]=d.get(x,y+1)-d.get(x,y);
					around[3]=d.get(x+1,y)-d.get(x,y);

					sum=0;
					for (i=0;i<4;i++)
					{
						//implementation sum(g(i)*f(i))
						sum+=around[i]/(1+around[i]*around[i]/(val*val));

					}
					s.put(x,y,d.get(x,y)+a*sum/double(4));
				}
			}
	
		d=s;
	}
	src = d;
	delete &d;
	delete &s;
}
Raw2D* gradientlaplace(Raw2D &src)
{
	Raw2D *val=new Raw2D(src);
	for (int i=2;i<src.getXsize()-2;i++)
	{
		for (int j=2;j<src.getYsize()-2;j++)
		{
			PIXTYPE temp = src.get(i + 1, j) + src.get(i - 1, j) + src.get(i, j + 1) + src.get(i, j - 1) - 4 * src.get(i, j);
				
				temp = temp / (1 + temp*temp);
				val->put(i, j,  (temp * 5));
		}
	}

	return val;
}

Raw2D Anistropic2D::FourPDiff(Raw2D &src)			//based on Y-K model
{
	PIXTYPE sum;
	int x,y,z,j;
	Raw2D s;
	Raw2D d(src);
	for (int j=0;j<time;j++)
	{
		s=gradientlaplace(src);
		s=s/(s*s+1);
		s=gradientlaplace(s);
		s=d-s/double(4);
	}
	return s;

}
void Anistropic2D::FourPDiff_v2(Raw2D &src)			//based on Y-K model
{
	Raw2D *ret = new Raw2D(src);
	bool flag = false;

	int x, y, z, j;

	Raw2D *d = new Raw2D(src); 
 	for (int ii = 0; ii < time; ii++)
	{
		Raw2D *_ret=NULL;
		_ret = gradientlaplace(*d);
		Raw2D *sum = new Raw2D(src);

		for (int i = 1; i < _ret->getXsize() - 1; i++)
		{
			for (int j = 1; j < _ret->getYsize() - 1; j++)
			{

				PIXTYPE var1 = _ret->get(i + 1, j) + _ret->get(i - 1, j) +
					_ret->get(i, j + 1) + _ret->get(i, j - 1);
				PIXTYPE var2 = _ret->get(i, j) * 4;
				PIXTYPE var = var2 - var1;
				sum->put(i, j, var/4);

			}
		}

		for (int i = 0; i < ret->size(); i++)
		{
			float t = 0;
			if ((t = d->getXY(i) - sum->getXY(i) / 4) <= 0)
			{
				sum->putXY(i, 0);
			}
			else if ((t = d->getXY(i) - sum->getXY(i) / 4) < 255)
			{
				sum->putXY(i, floor(t + 0.5));
			}
			else
			{
				sum->putXY(i, 255);
			}

		}
		
		if (ii == time - 1)
		{
			//for (int i = 0; i < src.getXsize(); i++)
			//{
			//	for (int j = 0; j < src.getYsize(); j++)
			//	{

			//		if (!(i> 2 && i < src.getXsize() - 3 && j>2 && j < src.getYsize() - 3)	 )
			//		{
			//			sum->put(i, j,  src.get(i, j));
			//		}

			//	}
			//}
			
			Filter *gauss = new Filter();
			gauss->guassFilter(sum, 3);
			memcpy(ret->getdata(), sum->getdata(), d->size() * 4);
			delete gauss;
		}//end.. if

		
		*d = *sum;
		delete _ret;
		delete sum;

	}//....end for 
	
	memcpy(src.getdata(), ret->getdata(), src.size() * 4);




}