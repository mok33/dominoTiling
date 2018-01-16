#include "dominoTiling.hpp"
#include "lib/imagepng.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

ImagePNG domino_H;
ImagePNG domino_V;

int const border_thiccness = 4;

bool isBorder(int x, int y, int L, int H){
	return (x >= 0 && x <= border_thiccness) || (x <= L && x >= L - border_thiccness) || ((y >= 0 && y <= border_thiccness) || (y <= H && y >= H - border_thiccness));
}


void drawDominos(ImagePNG& image, domino d){
	int x = d.x;
	int y = d.y;
	
	int H = domino_H.hauteur();
	int L = domino_H.largeur();
	Couleur c;
	
	int cond = L;
	if(d.spin == VERTICALE){
		cond = H;
		//cout << "V" << endl;
	}
	else{
		//cout << "H" << endl;
	}
	
	int i = 1;
	
	while(i <= H * L && x < image.largeur() && y < image.hauteur()){
		
		if(d.spin == VERTICALE){
			c = domino_V.lirePixel(x - d.x, y - d.y);
		}
		else if(d.spin == HORIZONTALE){

			c = domino_H.lirePixel(x - d.x, y - d.y);
		}

		image.ecrirePixel(x, y, c);
		
		if(i % cond == 0){
			y++;
			x = d.x;
		}
		else
		{
			x++;
		}
		i++;
	}
	//cout << "." << endl;
}

int main(int argc, char* argv[]){
	if(argc < 6){
		cout << "missing args." << endl;
		return 0;
		
	}
	
	srand(time(NULL));
	domino* tiling = NULL;

	int id = atoi(argv[3]);
	
	domino_H = ImagePNG();
	domino_H.charger(argv[4]);
	
	domino_V = ImagePNG(domino_H.hauteur(), domino_H.largeur());
	
	int n_d = domino_H.hauteur();
	int m_d = domino_H.largeur();
	
	int n = atoi(argv[2]) * n_d;
	int m = atoi(argv[1]) * m_d;
	
	int nb_tiles = atoi(argv[2]) * atoi(argv[1]);

	for(int x = 0; x < domino_H.largeur(); x++){
		for(int y = 0; y < domino_H.hauteur(); y++){
			domino_V.ecrirePixel(y, x, domino_H.lirePixel(x, y));
		}
	}
	
	dominoTiling(m, n, n_d, m_d, id, tiling);

	ImagePNG image(m, n);
	for(int k = 0; k < nb_tiles; k++)
	{
		cout << tiling[k].spin << " ";
		drawDominos(image, tiling[k]);
	}
	image.sauver(argv[5]);
	
	exit(EXIT_SUCCESS);
	
}
