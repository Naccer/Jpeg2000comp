#include <iostream>
#include <string>

#include "BancDeFiltre.h"
#include "util.h"
#include "lifiting.h"
#include "amr.h"
#include <cmath>
#include <inttypes.h>

using namespace std;

int main()
{

//-------------------------Banc de filtre tests

//
//    const unsigned int TAILLE=4096;
//    const unsigned int TAILLE_H=3;
//    double signal[4096];
//
//    double original_signal[4096];
//
//    read_signal(signal,TAILLE,"leleccum.txt");
//    read_signal(original_signal,TAILLE,"leleccum.txt");
//
//
//  //  print_signal(signal,TAILLE);
//
//    analyse_97_lifting(signal,TAILLE);
//
//   synthese_97_lifting(signal,TAILLE);
//
//    save_signal(signal,TAILLE,"./signal.txt");
//
//    cout << moindre_carre(signal,original_signal,TAILLE);
//
//








//    const unsigned int TAILLE=256;
//    const unsigned int TAILLE_H=3;
//    double signal[256];
//
//    double original_signal[256];
//
//
//
//    for(int i=0;i<256;i++){
//        signal[i]=i;
//        original_signal[i]=i;
//    }
//    analyse_haar(signal,TAILLE);
//
//    //synthese_haar(signal,TAILLE);
//
//
//    save_signal(signal,TAILLE,"./signal.txt");
//   cout<<moindre_carre(signal,original_signal,TAILLE);






//    const unsigned int TAILLE=10;
//
//    double signal[]={55,34,54,11,55,0,0,0,0,0};
//    double original_signal[]={55,34,54,11,55,0,0,0,0,0};
//
//    double h[]={1/sqrt(2) , 1/sqrt(2) , 0};
//
//
//    analyse_haar(signal,TAILLE);
//
//    synthese_haar(signal,TAILLE);
//
//
//    print_signal(signal,TAILLE);
//
//
//
//   cout<<moindre_carre(signal,original_signal,TAILLE);



// --------------------Lifting tests


//    const unsigned int TAILLE=10;
//
//    double signal[]={55,34,54,11,55,0,0,0,0,0};
//    double original_signal[]={55,34,54,11,55,0,0,0,0,0};
//
//
//
//
//   analyse_97_lifting(signal,TAILLE/2);
//
//
//   print_signal(signal,TAILLE);
//
//
//
//   cout<<moindre_carre(signal,original_signal,TAILLE);
//



//    const unsigned int TAILLE=256;
//    const unsigned int TAILLE_H=3;
//    double signal[256];
//
//    double original_signal[256];
//
//
//
//    for(int i=0;i<256;i++){
//        signal[i]=i;
//        original_signal[i]=i;
//    }
//
////    analyse_97(signal,TAILLE);
////
////
////   synthese_97(signal,TAILLE);
//
//
//    save_signal(signal,TAILLE,"./signal.txt");
//    cout<<moindre_carre(signal,original_signal,TAILLE);
//








//    const unsigned int TAILLE=4096;
//    const unsigned int TAILLE_H=3;
//    double signal[4096];
//
//    double original_signal[4096];
//
//    read_signal(signal,TAILLE,"leleccum.txt");
//    read_signal(original_signal,TAILLE,"leleccum.txt");
//
//    analyse_haar(signal,TAILLE);
//
//
//   synthese_haar(signal,TAILLE);
//
//
//    print_signal(signal,TAILLE);
//
//    save_signal(signal,TAILLE,"./signal.txt");
//
//    cout << moindre_carre(signal,original_signal,TAILLE);




//------------------------------------------AMR tests


//
//    const unsigned int TAILLE=256;
//    const unsigned int LEVEL=2;
//    double signal[256];
//
//    double original_signal[256];
//
//
//
//    for(int i=0;i<256;i++){
//        signal[i]=i;
//        original_signal[i]=i;
//    }
//
//
//    amr(signal,TAILLE,LEVEL);
//  //  iamr(signal,TAILLE,LEVEL);
//
//    ecrit_bmp256("signale256_2",256,1,signal);
//
//
//    print_signal(signal,TAILLE);
//
//    save_signal(signal,TAILLE,"./signal.txt");
//
//    cout << moindre_carre(signal,original_signal,TAILLE);




//  const unsigned int TAILLE=256;
//    const unsigned int LEVEL=4;
//    double signal[TAILLE];
//
//    double original_signal[TAILLE];
//
//
//
//    for(int i=0;i<TAILLE;i++){
//        signal[i]=i;
//        original_signal[i]=i;
//    }
//
//    _min_max_amr(signal,TAILLE,LEVEL);




//    int p=512;
//
//    const unsigned int TAILLE=p;
//    const unsigned int LEVEL=4;
//    double signal[TAILLE];
//
//
//    double original_signal[TAILLE];
//
//    read_signal(signal,TAILLE,"test.txt");
//    read_signal(original_signal,TAILLE,"test.txt");
//
//    amr(signal,TAILLE,LEVEL);
//   // synthese_97_lifting(signal,TAILLE);
//
////    amr(signal,p,LEVEL);
//   // iamr(signal,p,LEVEL);
//
//    print_signal(signal,TAILLE);
//
//    save_signal(signal,TAILLE,"./signal.txt");
//
//    //cout << moindre_carre(signal,original_signal,TAILLE);
//
//    _min_max_amr(signal,TAILLE,LEVEL);
//
//




    uint32_t length=0;
    uint32_t width=0;
    const int LEVEL=3;

    double* m = charge_bmp256("lena.bmp",&length,&width);
    double* original_signal=charge_bmp256("lena.bmp",&length,&width);
  //  analyse2D_97(m,length,width);
    amr2D_97(m,length,LEVEL);
   iamr2D_97(m,length,LEVEL);
  //save_signal(m,length*length,"signal2d.txt");

  //   moyenne_variance_amr2D(m,length,LEVEL);
    ecrit_bmp256("lensdfadecomposed.bmp",length,width,m);

    cout << moindre_carre( m,original_signal,length);



    return 0;
}
