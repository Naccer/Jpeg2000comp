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




void convolve(double* Signal, size_t SignalLen,const double Kernel[/* KernelLen */],
              size_t KernelLen
              )
{

  double Result[ SignalLen + KernelLen-1 ];
  size_t n;

  for (n = 0; n < SignalLen+KernelLen-1; n++)
  {
    size_t kmin, kmax, k;

    Result[n] = 0;

    kmin = (n >= KernelLen - 1) ? n - (KernelLen - 1) : 0;
    kmax = (n < SignalLen - 1) ? n : SignalLen - 1;

    for (k = kmin; k <= kmax; k++)
    {
      Result[n] += Signal[k] * Kernel[n - k];

    }


  }

  for (int k = 0; k <= SignalLen; k++)
    {

       Signal[k]=Result[k];

    }



}



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

    //print_signal(x,p);

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

    interpolation2(xhi,p);

    convolve(xbi,p,_g0,3);
    convolve(xhi,p,_g1,3);

 //print_signal(xbi,p);

 //print_signal(xhi,p);

     for(int i=0;i<p;i++){
        x[i]=xbi[i]+xhi[i];

    }

   // print_signal(x,p);

}


