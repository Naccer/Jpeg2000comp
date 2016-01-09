#include "lifiting.h"


void prediction1(double*  x,int p, int a){


    for(int i=0;i<p;i++){

        int index0 = getIndex(2*i-1,p);
        int index1 = getIndex(2*i,p);
        int index2 = getIndex(2*i+1,p) ;
        int index3 = getIndex(2*i+2,p);


        x[index2]=a*x[index1]+x[index2]+a*x[index3];

    }



}


void mise_a_jour1(double*  x,int p, int a){


    for(int i=0;i<p;i++){

        int index0 = getIndex(2*i-1,p);
        int index1 = getIndex(2*i,p);
        int index2 = getIndex(2*i+1,p) ;
        int index3 = getIndex(2*i+2,p);


        x[index1] = a*x[index0]+x[index1]+a*x[index2] ;

    }

}

void prediction2(double*  x,int p, int a){


    for(int i=0;i<p;i++){

        int index0 = getIndex(2*i-1,p);
        int index1 = getIndex(2*i,p);
        int index2 = getIndex(2*i+1,p) ;
        int index3 = getIndex(2*i+2,p);


        x[index2]=a*x[index1]+x[index2]+a*x[index3];

    }



}

void mise_a_jour2(double*  x,int p, int a){


    for(int i=0;i<p;i++){

        int index0 = getIndex(2*i-1,p);
        int index1 = getIndex(2*i,p);
        int index2 = getIndex(2*i+1,p) ;
        int index3 = getIndex(2*i+2,p);


       x[index1] = a*x[index0]+x[index1]+a*x[index2];

    }



}


void mise_a_lechelle(double*  x,int p, double a){


    for(int i=0;i<p;i++){

        int index0 = getIndex(2*i-1,p);
        int index1 = getIndex(2*i,p);
        int index2 = getIndex(2*i+1,p) ;
        int index3 = getIndex(2*i+2,p);


       x[index1] = x[index1]/a ;
       x[index2] = a*x[index2];
    }



}

void mise_en_forme(double* x,int p){

    double xtemp[p];

    int ipaire=0;
    int iimpaire=0;

    for(int i=0;i<p;i++){
        if(i%2 == 0){
            xtemp[ipaire]=x[i];
            ipaire++;

        }else{
            xtemp[p/2 + iimpaire]=x[i];
            iimpaire++;

        }

    }

    for(int i=0;i<p;i++){
        x[i]=xtemp[i];

    }

}


void mise_en_forme_recon(double* x,int p){

    double xtemp[p];

    for(int i=0;i<p/2;i++){
       xtemp[2*i]=x[i];
       xtemp[2*i+ 1]=x[p/2+i];

    }

    for(int i=0;i<p;i++){
        x[i]=xtemp[i];

    }

}







void analyse_97_lifting(double* x,int p){

    double a = -1.586134342;
    prediction1(x,p,a);

    a=-0.05298011854;
    mise_a_jour1(x,p,a);

    a=0.8829110762;
    prediction2(x,p,a);



    a=0.4435068522;
    mise_a_jour2(x,p,a);

    a=1/1.149604398;
    mise_a_lechelle(x,p,a);

  mise_en_forme(x,p);



}

void synthese_97_lifting(double* x,int p){

    mise_en_forme_recon(x,p);


    double a=1.149604398;
    mise_a_lechelle(x,p,a);

    a=-0.4435068522;
    mise_a_jour2(x,p,a);

    a=-0.8829110762;
    prediction2(x,p,a);

    a=0.05298011854;
    mise_a_jour1(x,p,a);

    a=1.586134342;
    prediction1(x,p,a);

}



 int getIndex(int index,int p){

    if(index<0)
        index=-index;
    if(index>=p)
        index= p-1 -(index-(p-1));

    return index;


}


