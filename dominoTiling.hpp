#ifndef _DOMINO_TILING_H
#define _DOMINO_TILING_H
int const HORIZONTALE = 2;
int const VERTICALE = 1;
int const EMPTY = -1;

typedef struct domino{
	int x, y;
	int spin;
} domino;

bool placeDomino(int type, int & x, int & y, int val, domino*& tiling);
void removeDomino(int type, int x , int y);
int dominoTiling_r(int i, int & x, int & y, domino*& tiling, int occupied);
int dominoTiling(int n, int m, int d_n, int d_m, int id_tex, domino*& tiling);

#endif
