#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <cmath>
#include <cstdio>

#include <stdlib.h>


#include <inttypes.h>

void read_signal(double* x,int n,char* filename);

void print_signal(double* x,int n) ;

void save_signal(double* x,int n,char* filename) ;



int ecrit_bmp256(char* fichier, uint32_t largeur, uint32_t hauteur, double* m);

double* charge_bmp256(char* fichier, uint32_t* largeur, uint32_t* hauteur) ;





#endif // UTIL_H
