#include <iostream>
#include "stdlib.h"
#include <string>

/* https://brilliant.org/problems/domino-tiling-3/
 * Started on 08/08/2017 14:50, number of solvers 17
 * 
	How many ways are there to tile a 5 x 6 rectangle with dominoes?
	
	dominoes size: 1 x 2 or 2 x 1
 * 
 * 
 */ 
int const EMPTY = -1;
int const UP = 1;
int const DOWN = 2;

typedef struct point{
	int x,y;
} point;

bool IsInGrid(int x, int y, int n, int m, int grid[][]){
	return (x >= 0 && x < n) && (y >= 0 && y < m);
}

bool noCollision(int x, int y, int xf, int yf, int grid[][]){
	
	for(i = x; i <= xf; i++){
		for(j = y; j <= yf; j++){
			
			if(grid[i][j] != EMPTY){
				
			}
		}
	}
	return true;
}

bool placeDomino(int x, int y, int n, int m, int grid[][], int spin, int id){
	
	bool ok = false;
	int xf = 0;
	int yf = 1;
	
	if(spin == UP){
		xf = 1;
		yf = 0; 
	}
	
	if(IsInGrid(x + xf, y + yf, n, m, grid) && (id == EMPTY || noCollision(x, y, xf, yf, grid))){
		ok = true;
		
		for(int i = x; i <= x + xf; i++){
			for(int j = y; i <= y + yf; j++){
				grid[i][j] = id;
			}
		}	
	}
	
	return ok;
}
void removeDomino(int x, int y, int n, int m, int grid[][], int spin, point empty[]){
	placeDomino(x, y, n, m, grid, spin, EMPTY);
	
	int xf = x + 1;
	int yf = y;
	
	if(spin == DOWN){
		xf = x;
		yf = y + 1;
	}
	
	
}

void empty_adjacent_slot(int x, int y, int n, int m, int grid[][], int spin){
	for(){
	}
}

int dominoTiling(int n, int m, int grid[][], int x, int y, gridIsFull){
	int N = 0;
	point empty_adjacent_slot[6];
	int size_eas = 0;
	
	if(gridIsFull){
		N = 1;
	}
	else{
		
		if(placeDomino(x, y, n, m, grid, UP, 1)){
			
			for(int i = 0; i < size_eas; i++){
				N += dominoTiling(n, m, grid, empty_slot[i].x, empty_slot[i].y);	
			}
		}
		removeDomino(x, y, n, m, grid, UP);
		
		if(placeDomino(x, y, n, m, grid, DOWN, 1)){
			for every empty adjacent slot:
				N += dominoTiling(n, m, grid, empty_slot[i].x, empty_slot[i].y);
		}
		
		removeDomino(x, y, n, m, grid, UP);
		

	}
	
	return N;
	
}

using namespace std;


int main(){
	int n = 5;
	int m = 6;
	
	int grid[n][m];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			grid[n][m] = EMPTY;
		}
	}
	
	cout << dominoTiling(n, m, grid, 0, 0, false) << endl;


	return 0;
}
