#ifndef BANCDEFILTRE_H
#define BANCDEFILTRE_H

#include <iostream>
using namespace std;


void interpolation2(double* x,int taille);
void decimation2(double* x,int taille);

void convolve( double Signal[/* SignalLen */], size_t SignalLen,const double Kernel[/* KernelLen */],
              size_t KernelLen
              );

void analyse_haar(double* x,int p);

void synthese_haar(double* x,int p);


#endif // BANCDEFILTRE_H
