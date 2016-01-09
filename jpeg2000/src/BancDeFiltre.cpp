#include "BancDeFiltre.h"
#include "util.h"
#include <iostream>
#include <cmath>

using namespace std;


//Interpolation of signal
void interpolation2(double* x,int taille){

    for(int i(taille/2);i>=0;i--){

        x[2*i]=x[i];
    }

    for(int i(0);i<taille/2;i++){

        x[2*i+1]=0.0;

    }
}

/*decimation of the signal , we get a signal of half size but because we make change
on the same signal so we put values of the second half to zeros
*/

void decimation2(double* x,int taille){

    for(int i(0);i<taille/2;i++){

        x[i]=x[2*i];
    }

     for(int i(taille/2);i<taille;i++){

         x[i]=0.0;
    }
}


void convolve(double *x,int size_x, double *h, int size_h)
{
	double *f = new double[size_x];
	for (int n = 0; n<size_x; n++)
	{
		f[n] = 0;

		for (int k = -(size_h/2); k <= (size_h/2); k++)
		{
			int pos = n - k;
			if (pos < 0)
				pos = -pos;
			if (pos >= size_x)
				pos = size_x- 1 - (pos - (size_x - 1));
			f[n] = f[n] + h[k + size_h/2] * x[pos];
		}


	}

	for (int i = 0; i < size_x; i++)
	{
			x[i] = f[i];
	}

}

//void convolve(double* Signal, size_t SignalLen,const double Kernel[/* KernelLen */],
//              size_t KernelLen
//              )
//{
//
//  double Result[ SignalLen + KernelLen-1 ];
//  size_t n;
//
//  for (n = 0; n < SignalLen+KernelLen-1; n++)
//  {
//    size_t kmin, kmax, k;
//
//    Result[n] = 0;
//
//    kmin = (n >= KernelLen - 1) ? n - (KernelLen - 1) : 0;
//    kmax = (n < SignalLen - 1) ? n : SignalLen - 1;
//
//    for (k = kmin; k <= kmax; k++)
//    {
//      Result[n] += Signal[k] * Kernel[n - k];
//
//    }
//
//
//  }
//
//  for (int k = 0; k <= SignalLen; k++)
//    {
//
//       Signal[k]=Result[k];
//
//    }
//
//
//
//}



void analyse_haar(double* x,int p){

    double _h0 []={1/sqrt(2) , 1/sqrt(2) , 0};
    double _h1 []={1/sqrt(2) , -1/sqrt(2) , 0};

    double xb[p];
    double xh[p];


    for(int i=0;i<p;i++){
        xb[i]=x[i];
        xh[i]=x[i];
    }

    convolve(xb,p,_h0,3);
  //  print_signal(xb,p);

    convolve(xh,p,_h1,3);
   // print_signal(xh,p);

    decimation2(xb,p);
 // print_signal(xb,p);

    decimation2(xh,p);
  //print_signal(xh,p);

    for(int i=0;i<p/2;i++){
        x[i]=xb[i];
        x[i+p/2]=xh[i];

    }

   // print_signal(x,p);

}



void synthese_haar(double* x,int p){

    double _g0[] = {0 , 1/sqrt(2) , 1/sqrt(2)};
    double _g1[] = {0 , -1/sqrt(2) , 1/sqrt(2)};


    double xbi[p];
    double xhi[p];

    for(int i=0;i<p/2;i++)
    {
        xbi[i]=x[i];
        xbi[i+p/2]=0;

        xhi[i]=x[i+p/2];
        xhi[i+p/2]=0;
    }


    interpolation2(xbi,p);

    //print_signal(xbi,p);

    interpolation2(xhi,p);

   //   print_signal(xhi,p);

    convolve(xbi,p,_g0,3);

 //     print_signal(xbi,p);
    convolve(xhi,p,_g1,3);

//   print_signal(xhi,p);

 //print_signal(xbi,p);

 //print_signal(xhi,p);

     for(int i=0;i<p;i++){
        x[i]=xbi[i]+xhi[i];

    }

      print_signal(x,p);

   // print_signal(x,p);

}


void analyse_97(double* x,int p){

double _h0 [9];
double _h1 [9];



// Filtre biorthogonal 9/7 _h0 (longueur 9)
_h0[0]=0.037828455507     ;
_h0[1]=-0.023849465019;
_h0[2]=-0.110624404418;
_h0[3]=0.377402855613;
_h0[4]=0.852698679009;
_h0[5]=0.377402855613;
_h0[6]=-0.110624404418;
_h0[7]=-0.023849465019;
_h0[8]=0.037828455507;



// Filtre biorthogonal 9/7 _h1 (longueur 9)
_h1[0]=0.064538882629;
_h1[1]=-0.040689417610;
_h1[2]=-0.418092273222;
_h1[3]=0.788485616406;
_h1[4]=-0.418092273222;
_h1[5]=-0.040689417610;
_h1[6]=0.064538882629;
_h1[7]=0.000000000000;
_h1[8]=-0.000000000000;




    double xb[p];
    double xh[p];


    for(int i=0;i<p;i++){
        xb[i]=x[i];
        xh[i]=x[i];
    }

    convolve(xb,p,_h0,9);
  //  print_signal(xb,p);

    convolve(xh,p,_h1,9);
   // print_signal(xh,p);

    decimation2(xb,p);
 // print_signal(xb,p);

    decimation2(xh,p);
  //print_signal(xh,p);

    for(int i=0;i<p/2;i++){
        x[i]=xb[i];
        x[i+p/2]=xh[i];

    }

    //print_signal(x,p);

}



void synthese_97(double* x,int p){

    double _g0[7];
    double _g1[11];
// Filtre biorthogonal 9/7 _g0 (longueur 7)
_g0[0]=-0.064538882629;
_g0[1]=-0.040689417610;
_g0[2]=0.418092273222;
_g0[3]=0.788485616406;
_g0[4]=0.418092273222;
_g0[5]=-0.040689417610;
_g0[6]=-0.064538882629;

// Filtre biorthogonal 9/7 _g1 (longueur 11)
_g1[0]=0.000000000000;
_g1[1]=-0.000000000000;
_g1[2]=0.037828455507;
_g1[3]=0.023849465019;
_g1[4]=-0.110624404418;
_g1[5]=-0.377402855613;
_g1[6]=0.852698679009;
_g1[7]=-0.377402855613;
_g1[8]=-0.110624404418;
_g1[9]=0.023849465019;
_g1[10]=0.037828455507;

    double xbi[p];
    double xhi[p];

    for(int i=0;i<p/2;i++)
    {
        xbi[i]=x[i];
        xbi[i+p/2]=0;

        xhi[i]=x[i+p/2];
        xhi[i+p/2]=0;
    }


    interpolation2(xbi,p);

    interpolation2(xhi,p);

    convolve(xbi,p,_g0,7);
    convolve(xhi,p,_g1,11);

 //print_signal(xbi,p);

 //print_signal(xhi,p);

     for(int i=0;i<p;i++){
        x[i]=xbi[i]+xhi[i];

    }

   // print_signal(x,p);

}


