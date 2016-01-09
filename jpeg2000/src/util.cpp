#include "util.h"


using namespace std;
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



// function receving a signal x and origninal signal y of the same size p and returns the least square error between them
double moindre_carre(double*x,double* y, int p)
{

    double sum;



    for(int i=0;i<p;i++){
        sum+=pow(x[i]-y[i],2);

    }

    return sum;
}


double* charge_bmp256(char* fichier, uint32_t* largeur, uint32_t* hauteur) {
	FILE* fp;
	uint16_t bfType;
	uint32_t bfOffBits;
	uint32_t biWidth;
	uint32_t biHeight;
	uint16_t biBitCount;
	uint32_t biCompression;
	uint8_t *pixels;
	uint32_t pixelsSize;
	uint32_t x, y;
	double* m;

	fp = fopen(fichier, "rb");
	if (fp == NULL) {
		printf("charge_bmp256: impossible d'ouvrir le fichier %s en lecture !\n",
				fichier);
		return NULL;
	}

	// BMP specifications : http://members.fortunecity.com/shetzl/bmpffrmt.html
	// Lecture de l'entÃªte
	fread(&bfType, sizeof(uint16_t), 1, fp);
	if (bfType != 19778) {
		printf("charge_bmp256: le fichier %s n'est pas un fichier BMP !\n",
				fichier);
		fclose(fp);
		return NULL;
	}

	// Lecture de l'offset du debut du bitmap
	fseek(fp, 10, SEEK_SET);
	fread(&bfOffBits, sizeof(uint32_t), 1, fp);

	// Lecture de la largeur et de la hauteur
	fseek(fp, 18, SEEK_SET);
	fread(&biWidth, sizeof(uint32_t), 1, fp);
	*largeur = (int) biWidth;
	fread(&biHeight, sizeof(uint32_t), 1, fp);
	*hauteur = (int) biHeight;

	// Verification que l'image est bien en mode 256 couleurs
	fseek(fp, 28, SEEK_SET);
	fread(&biBitCount, sizeof(uint16_t), 1, fp);
	if (biBitCount != 8) {
		printf(
				"charge_bmp256: le fichier BMP %s n'est pas en mode 256 couleurs !\n",
				fichier);
		fclose(fp);
		return NULL;
	}

	// Verification que l'image n'est pas compressÃ©e
	fseek(fp, 30, SEEK_SET);
	fread(&biCompression, sizeof(uint32_t), 1, fp);
	if (biCompression != 0) {
		printf("charge_bmp256: le fichier BMP %s est en mode compressÃ© !\n",
				fichier);
		fclose(fp);
		return NULL;
	}

	// Allocation d'un bloc memoire pour lire les pixels et lecture de ceux-ci
	pixelsSize = (*largeur) * (*hauteur);
	pixels = (uint8_t *) malloc(pixelsSize);
	fseek(fp, bfOffBits, SEEK_SET);
	fread(pixels, pixelsSize, 1, fp);

	// Copie dans un buffer de double et transposition des lignes
	m = (double *) calloc(pixelsSize, sizeof(double));
	for (y = 0; y < *hauteur; y++) {
		for (x = 0; x < *largeur; x++) {
			m[x + *largeur * (*hauteur - 1 - y)] = (double) pixels[x + *largeur
					* y];
		}
	}
	free(pixels);

	fclose(fp);

	return m;
}

int ecrit_bmp256(char* fichier, uint32_t largeur, uint32_t hauteur, double* m) {
	FILE* fp;
	uint16_t us;
	uint32_t ul;
	uint8_t uc;
	uint32_t i;
	uint32_t pixelsSize;
	uint32_t x, y;
	uint8_t* pixels;

	fp = fopen(fichier, "wb");
	if (fp == NULL) {
		printf("ecrit_bmp256: impossible d'ouvrir le fichier %s en Ã©criture !\n",
				fichier);
		return 0;
	}

	pixelsSize = largeur * hauteur;

	// Conversion double => uint8_t
	pixels = (uint8_t *) malloc(pixelsSize);
	for (y = 0; y < hauteur; y++) {
		for (x = 0; x < largeur; x++) {
			double d;
			uint8_t c;
			d = m[x + largeur * y];
			if (d < 0.0)
				c = 0;
			else if (d > 255.0)
				c = 255;
			else
				c = (uint8_t) d;

			pixels[x + largeur * (hauteur - 1 - y)] = c;
		}
	}

	// Ecriture de l'entÃªte standard
	// bfType
	us = 19778;
	fwrite(&us, sizeof(uint16_t), 1, fp);

	// bfSize
	// taille image + taille BITMAPFILEHEADER + taille BITMAPINFOHEADER + taille palette
	ul = pixelsSize + 14 + 40 + 256 * 4;
	fwrite(&ul, sizeof(uint32_t), 1, fp);

	// bfReserved
	ul = 0;
	fwrite(&ul, sizeof(uint32_t), 1, fp);

	// bfOffBits
	// taille BITMAPFILEHEADER + taille BITMAPINFOHEADER + taille palette
	ul = 14 + 40 + 256 * 4;
	fwrite(&ul, sizeof(uint32_t), 1, fp);

	// biSize
	ul = 40;
	fwrite(&ul, sizeof(uint32_t), 1, fp);

	// biWidth
	ul = largeur;
	fwrite(&ul, sizeof(uint32_t), 1, fp);

	// biHeight
	ul = hauteur;
	fwrite(&ul, sizeof(uint32_t), 1, fp);

	// biPlanes
	us = 1;
	fwrite(&us, sizeof(uint16_t), 1, fp);

	// biBitCount
	us = 8;
	fwrite(&us, sizeof(uint16_t), 1, fp);

	// biCompression
	ul = 0;
	fwrite(&ul, sizeof(uint32_t), 1, fp);

	// biSizeImage
	ul = pixelsSize;
	fwrite(&ul, sizeof(uint32_t), 1, fp);

	// biXPelsPerMeter
	ul = 0;
	fwrite(&ul, sizeof(uint32_t), 1, fp);

	// biYPelsPerMeter
	ul = 0;
	fwrite(&ul, sizeof(uint32_t), 1, fp);

	// biClrUsed
	ul = 0;
	fwrite(&ul, sizeof(uint32_t), 1, fp);

	// biClrImportant
	ul = 0;
	fwrite(&ul, sizeof(uint32_t), 1, fp);

	// Ecriture de la palette en niveaux de gris
	for (i = 0; i < 256; i++) {
		uc = i;
		fwrite(&uc, sizeof(uint8_t), 1, fp);

		uc = i;
		fwrite(&uc, sizeof(uint8_t), 1, fp);

		uc = i;
		fwrite(&uc, sizeof(uint8_t), 1, fp);

		uc = 0;
		fwrite(&uc, sizeof(uint8_t), 1, fp);
	}

	// Ecriture de l'image
	fwrite(pixels, largeur * hauteur, 1, fp);

	free(pixels);

	fclose(fp);
	return 1;
}
