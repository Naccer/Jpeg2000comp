#include "util.h"

//Lecture d'un signal provenant d'un fichier ASCII
//Lit le signal x de longueur n , dont les valeurs flottantes sont stockées sous forme ASCII dans le fichier de nom filename :
void read_signal(double* x,int n,char* filename) {
  int i;
  FILE *fp=fopen(filename,"rt");
  for (i=0;i<n;i++) {
   float t;
   fscanf(fp,"%f\n",&t);
   x[i]=(double)t;
  }
  fclose(fp);
}


//Affichage d'un signal sur la console
//Affiche le signal x de longueur n sur la console :
void print_signal(double* x,int n) {
  int i;
  for (i=0;i<n;i++) {
    printf("x[%d]=%f\n",i,x[i]);
  }
  printf("\n");
}


//Ecriture d'un signal provenant d'un fichier ASCII
//Ecrit le signal x de longueur n , sous forme de valeurs flottantes double précision ASCII dans le fichier de nom filename :
void save_signal(double* x,int n,char* filename) {
  int i;
  FILE *fp=fopen(filename,"wt");
  for (i=0;i<n;i++) {
   fprintf(fp,"%f\n",x[i]);
  }
  fclose(fp);
}
