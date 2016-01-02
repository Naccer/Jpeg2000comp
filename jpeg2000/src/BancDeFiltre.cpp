#include "BancDeFiltre.h"

#include <iostream>

using namespace std;


//fonction d'interpolation du signal

void interpolation2(double* x,int taille){

    for(int i(taille/2);i>=0;i--){

        x[2*i]=x[i];

    }

    for(int i(0);i<taille/2;i++){

        x[2*i+1]=0;
    }

}


void decimation2(double* x,int taille){

    for(int i(0);i<taille/2;i++){

        x[i]=x[2*i];

    }

     for(int i(4);i<taille;i++){

         x[i]=0;

    }


}



