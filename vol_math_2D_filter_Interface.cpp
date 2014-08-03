#include "vol_math_2D_filter_Interface.h"

//qym
#include "vol_math_RawImage.h"
using namespace std;
//extern size_t  globalProgressChanged = 0;
//extern size_t volatile progressStep = 0;



 void *doAnistropicI2D_new (Image2D &src,AnistropicI & para)
{
#if 1
    //qym non-const must be an lvalue
	//Raw2D &indata=Image2D2Raw2D(src);//to be test
	Raw2D indata=Image2D2Raw2D(src);//to be test
	Anistropic2D * pde=new Anistropic2D(indata,para.time,para.val,para.method);//to be ask
	delete pde;
	return Raw2D2Image2D(indata,src.PixelType);;
#else  //qym new way
	Raw2D indata=Image2D2Raw2D(src,false);//qym src use shared memory
	Anistropic2D * pde=new Anistropic2D(indata,para.time,para.val,para.method);//to be ask
    return (void *)ret->getdata();

#endif


}
extern void *doBilateralI2D_new (Image2D & src, BilateralFilterI &para)
{
    //qym non-const must be an lvalue
	//Raw2D &indata=Image2D2Raw2D(src);
	Raw2D indata=Image2D2Raw2D(src);
	BilateralFilter *b=new BilateralFilter(&indata,6,3);
	b->apply(indata);
	return Raw2D2Image2D(indata,src.PixelType);
	//return indata.getdata();
}
extern void * doGuassFilterI2D_new (Image2D &src, GuassFilterI &para)
{
    //qym non-const must be an lvalue
	//Raw2D &indata = Image2D2Raw2D(src);
	Raw2D indata = Image2D2Raw2D(src,true);//qym src use shared memory 	, Image2D2Raw2D	change data 2 float ,which is needed in filter process 
	Filter *guass = new Filter(); 
	Raw2D *ret=guass->guassFilter(&indata,para.halfsize);//qym this will create new space in ret

    //qym do not use following function
	//return Raw2D2Image2D(*ret,src.PixelType);
    return (void *)ret->getdata();
}
extern void * doTrilateralfilterI2D_new ( Image2D &src, TrilateralfilterI &para)
{
    //qym non-const must be an lvalue
	//Raw2D &indata = Image2D2Raw2D(src);
	Raw2D indata = Image2D2Raw2D(src);
	Trilateralfilter2D * tf=new Trilateralfilter2D();
	Raw2D *ret=tf->TrilateralFilter2D(&indata,para.sigmaC);
	//return Raw2D2Image2D(*ret,src.PixelType);
	return ret->getdata();
}
