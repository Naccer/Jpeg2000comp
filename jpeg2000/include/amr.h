#ifndef AMR_H
#define AMR_H

#include <iostream>
#include <cmath>
#include <inttypes.h>

#include "lifiting.h"
#include "util.h";

void amr(double* x,int p,int niveau);
void iamr(double* x,int p,int niveau);
void min_max_moyenne(int _i,int _j,double* x);
void _min_max_amr(double* x,int p,int niveau);
void analyse2D_97(double* m,uint32_t width,uint32_t length);
void amr2D_97(double* m,int p,int l);
 void iamr2D_97(double* m,int p,int l);
 double moyenne_band2D(double* x,int p);
  double variance_band2D(double* x,int p);
 void moyenne_variance_amr2D(double* m,int p,int l);



#endif // AMR_H
