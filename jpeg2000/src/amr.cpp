#include "amr.h"
#include "BancDeFiltre.h"

using namespace std;


void amr(double* x,int p,int niveau){


    for(int level=0;level<niveau;level++){

        int taille=p/pow(2,level);
        analyse_97(x,taille);


    }
}


void iamr(double* x,int p,int niveau){


    for(int level=niveau-1;level>= 0;level--){

        int taille=p/pow(2,level);
        synthese_97(x,taille);
    }
}


double maximum(int _i,int _j,double* x){

    double minimum=x[_i];
    double maximum=x[_i];
    double moyenne=x[_i];

    double sum=0;

    for(int i=_i;i<_j;i++){
        if(x[i]<minimum)
        {
            minimum=x[i];

        }

        if(x[i]>maximum)
        {
            maximum=x[i];
        }

        sum+=x[i];
    }

    moyenne=sum/(_j-_i);

    return maximum;
    cout<<endl;

 }



void min_max_moyenne(int _i,int _j,double* x){

    double minimum=x[_i];
    double maximum=x[_i];
    double moyenne=x[_i];

    double sum=0;

    for(int i=_i;i<_j;i++){
        if(x[i]<minimum)
        {
            minimum=x[i];

        }

        if(x[i]>maximum)
        {
            maximum=x[i];
        }

        sum+=x[i];
    }

    moyenne=sum/(_j-_i);

    cout<<minimum<<endl;
    cout<<maximum<<endl;
    cout<<moyenne<<endl;
    cout<<endl;

 }


 void _min_max_amr(double* x,int p,int niveau){

    int _i=0;
    int _j=p/pow(2,niveau);
   min_max_moyenne(_i,_j,x);
   for(int level=niveau;level> 0;level--){



    int taille=p/pow(2,level);
    _i=_j;
    _j=_j+taille;


    min_max_moyenne(_i,_j,x);

    }


 }

 void analyse2D_97(double* m,uint32_t width,uint32_t length){


    double temp[width];

    for(int i=0;i<length;i++){
        for(int j=0;j<width;j++)
        {
            temp[j]=m[i+width*j];

        }
int v=5;
double a[v];

        analyse_97(temp,width);


        for(int j=0;j<width;j++)
        {

             m[i+width*j]=temp[j];
        }
    }


     for(int i=0;i<length;i++){
        for(int j=0;j<width;j++)
        {
            temp[j]=m[i*width+j];

        }

        int v=5;
double a[v];

        analyse_97(temp,width);

        for(int j=0;j<width;j++)
        {

             m[i*width+j]=temp[j];
        }
    }


 }


  void synthese2D_97(double* m,uint32_t width,uint32_t length){


    double temp[width];

    for(int i=0;i<length;i++){
        for(int j=0;j<width;j++)
        {
            temp[j]=m[i+width*j];

        }


        synthese_97(temp,width);


        for(int j=0;j<width;j++)
        {

             m[i+width*j]=temp[j];
        }
    }


     for(int i=0;i<length;i++){
        for(int j=0;j<width;j++)
        {
            temp[j]=m[i*width+j];

        }

        synthese_97(temp,width);

        for(int j=0;j<width;j++)
        {

             m[i*width+j]=temp[j];
        }
    }


 }


void ajuster_image(double* m,int p){



}





 void amr2D_97(double* m,int p,int l){



    for(int level=0;level<l;level++)
    {

        int taille=p/pow(2,level);
        double tmp[taille*taille];

        for(int i=0;i<taille;i++)
        {

            for(int j=0;j<taille;j++)
            {
                tmp[i+j*taille]=m[i+j*p];
            }
        }



       analyse2D_97(tmp,taille,taille);

//       if(level==l-1){
//
//       double maxi=maximum(0,taille,tmp);
//
//
//
//
//
//            for(int i=0;i<taille;i++)
//            {
//
//                for(int j=0;j<taille;j++)
//                {
//                    tmp[i+j*taille]/=maxi;
//                    tmp[i+j*taille]*=255;
//                }
//            }
//
//       }

        for(int i=0;i<taille;i++)
        {
            for(int j=0;j<taille;j++)
            {
                m[i+j*p] = tmp[i+j*taille];
            }
        }
    }

//    for(int i=0;i<p;i++){
//    for(int j=0;j<p;j++)
//
//        if(m[i+j*p]>5) m[i+j*p]+=127;
//    }
}

 void iamr2D_97(double* m,int p,int l){


  for(int level=l-1;level>= 0;level--){

        int taille=p/pow(2,level);
        double tmp[taille*taille];

        for(int i=0;i<taille;i++)
        {

            for(int j=0;j<taille;j++)
            {
                tmp[i+j*taille]=m[i+j*p];
            }
        }

        synthese2D_97(tmp,taille,taille);

        for(int i=0;i<taille;i++)
        {
            for(int j=0;j<taille;j++)
            {
                m[i+j*p] = tmp[i+j*taille];
            }
        }


    }
}





double moyenne_band2D(double* x,int p){


    double moyenne;

    double sum=0;

    for(int i=0;i<p;i++){

        sum+=x[i];
    }

    moyenne=sum/p;

    return moyenne;

//    cout<<minimum<<endl;
//    cout<<maximum<<endl;
//    cout<<moyenne<<endl;
//    cout<<endl;

 }


double variance_band2D(double* x,int p){


    double sum=0;

    double moy=moyenne_band2D(x,p);

    double sigma=0;

    for(int i=0;i<p;i++){

        sum+=pow(x[i]-moy,2);
    }

    sigma=sum/p;

    return sigma;

 }


void moyenne_variance_amr2D(double* m,int p,int l){


int taille=p/pow(2,l);
double tmp[taille*taille];


for(int i=0;i<taille;i++)
    {
        for(int j=0;j<taille;j++)
        {

            tmp[i+taille*j]=m[i+j*p];
           // cout<<m[i+j*p]<<" *";




        }


    }



   cout<<moyenne_band2D(tmp,taille*taille)<<"  "<<variance_band2D(tmp,taille*taille)<<endl;

for(int level=l;level>0;level--){

    int taille=p/pow(2,level);
    double tmp[taille*taille];





    for(int i=0;i<taille;i++)
    {
        for(int j=taille;j<2*taille;j++)
        {

            tmp[i+taille*(j-taille)]=m[i+j*p];
           //cout<<m[i+j*p]<<" ";




        }


    }



      cout<<moyenne_band2D(tmp,taille*taille)<<"  "<<variance_band2D(tmp,taille*taille)<<endl;


    for(int i=taille;i<2*taille;i++)
    {


        for(int j=0;j<taille;j++)
        {

            tmp[i-taille+taille*j]=m[i+j*p];
           // cout<<m[i+j*p]<<" ";


        }


    }
      cout<<moyenne_band2D(tmp,taille*taille)<<"  "<<variance_band2D(tmp,taille*taille)<<endl;

    for(int i=taille;i<2*taille;i++)
    {


        for(int j=taille;j<2*taille;j++)
        {

            tmp[i-taille+taille*(j-taille)]=m[i+j*p];
         //   cout<<m[i+j*p]<<" ";

        }


    }

     cout<<moyenne_band2D(tmp,taille*taille)<<"  "<<variance_band2D(tmp,taille*taille)<<endl;


 }



//
//    int taille = p/pow(2,l);
//
//
//    double tmp[taille*taille];
//   for(int i=0;i<taille;i++)
//    {
//
//        for(int j=0;j<taille;j++)
//        {
//            tmp[i+j*taille]=m[i+j*p];
//        }
//    }
//
//    cout<<moyenne_band2D(tmp,taille)<<endl;
//
//
//    for(int level=l-1;level>= 0;level--){
//
//        int taille=p/pow(2,level);
//        double tmp[taille*taille];
//
//        for(int i=0;i<taille;i++)
//        {
//
//            for(int j=0;j<taille;j++)
//            {
//                tmp[i+j*taille]=m[i+j*p];
//            }
//        }
//
//        cout<<moyenne_band2D(tmp,taille)<<endl;
//    }

}

