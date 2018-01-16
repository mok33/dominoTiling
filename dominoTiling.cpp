#include <iostream>
#include "stdlib.h"
#include "dominoTiling.hpp"
#include <cmath>

//grid dimensions N x M
int N = 0;
int M = 0;

//dominos dimensions N_D x M_D 
int N_D = 0;
int M_D = 0;

//number of dominos N_T
int N_T = 0;

int** grid = NULL;
int ID = 0;

using namespace std;

bool placeDomino(int type, int & x, int & y, int val, domino* & tiling){	
	int condition = N_D;
	int i = 1;
	int x_0 = x;
	int y_0 = y;
	
	bool ok;
	
	tiling[val].x = y;
	tiling[val].y = x;
	tiling[val].spin = type;
	
	//cout << "place @(" << y << ", " << x << ") " << type << endl;
	
	if(type == VERTICALE){
		condition = M_D;
	}
	
	while(x < M && y < N && grid[y][x] == EMPTY && i <= N_D * M_D){
		grid[y][x] = val;
	

		if(i % condition == 0){
			x = x_0;
			y++;
		}
		else{
			x++;
		}
		
		i++;

		
	}
	ok = i > N_D * M_D;
	
	if(ok){
		/*
		for(int p = 0; p < N; p++){
			for(int m = 0; m < M; m++){
				cout << grid[p][m] << " ";
				if(grid[p][m] < 10){
					cout << " " ;
				}
				 
			}
			cout << endl;
		}
		*/
		
		//cout << "before rep @(" << y << ", " << x << ") " << endl;

		y = y_0;
		if(x == M && y < N){
			x = 0;
			y++;
		}
		//place cursor in a empty slot
		while(y < N && x < M && grid[y][x] != EMPTY){			
			x++;
			if(x == M && y < N){
				x = 0;
				y++;
			}
			
			//cout << "(" << y << ", " << x << ") ";
		}
		//cout << "place ok @(" << y << ", " << x << ") " << endl;
		
	}
	else{
		//cout << "place error @(" << y << ", " << x << ") " << type << endl;
	}
	return i > N_D * M_D;
}

void removeDomino(int type, int x , int y){
	
	//cout << "remove @(" << y << ", " << x << ") " << type << endl;
	int id = 0;
	
	if(x < M && y < N){
		id = grid[y][x];
	}
	int condition = N_D;
	int i = 1;
	int x_0 = x;
	
	if(type == VERTICALE){
		condition = M_D;
	}
	
	while(x < M && y < N && grid[y][x] == id && i <= N_D * M_D){
		grid[y][x] = EMPTY;
		
		if(i % condition == 0){
			x = x_0;
			y++;
		}
		else{
			x++;
		}
		i++;
	}
	/*
	for(int p = 0; p < N; p++){
			for(int m = 0; m < M; m++){
				cout << grid[p][m] << " ";
				if(grid[p][m] < 10){
					cout << " " ;
				}
				 
			}
			cout << endl;
		}
	*/
	//cout << "remove ok" << endl;

}


int dominoTiling_r(int i, int & x, int & y, domino* & tiling, int occupied){
	int T = 0;

	if(ID < 0 && tiling != NULL){
		return 0;
	}
	if(occupied == N * M){
		
		ID--;
		T = 1;
		
		if(ID == 0){
			/*
			for(int h = 0; h < (N*M)/(N_D*M_D); h++){
				cout << "(" << tiling[h].x << ", " << tiling[h].y << ")" << tiling[h].spin << " ";
			}
			cout << endl;

			for(int p = 0; p < N; p++){
				for(int m = 0; m < M; m++){
					cout << grid[p][m] << " ";
					if(grid[p][m] < 10){
						cout << " " ;
					}		 
				}
				cout << endl;
			}
			*/
			ID--;
		}
	}
	else{
		int x_0 = x;
		int y_0 = y;
		int spin = VERTICALE;
		
		if(placeDomino(spin, x, y, i, tiling)){
			T += dominoTiling_r(i+1, x, y, tiling, occupied + N_D * M_D);
			
		}
		removeDomino(spin, x_0, y_0);
		if(ID > 0){
			x = x_0;
			y = y_0;
			
			spin = HORIZONTALE;
			
			if(placeDomino(spin, x, y, i, tiling)){
				T += dominoTiling_r(i+1, x, y, tiling, occupied + N_D * M_D);
			}
			removeDomino(spin, x_0, y_0);	
		}
		
	}
	
	return T;

}

int dominoTiling(int n, int m, int d_n, int d_m, int id_tex, domino* & tiling){
	N = n;
	M = m;
	
	N_D = d_n;
	M_D = d_m;
	
	N_T = (n * m);
	grid = new int*[N];
	
	ID = id_tex;
	
	tiling = new domino[(n*m)/(d_n*d_m)];
	 
	for(int i = 0; i < N; i++){
		grid[i] = new int[M];
		for(int j = 0; j < M; j++){
			grid[i][j] = EMPTY;
		}
	}
	
	int x = 0;
	int y = 0;

	int cpt = dominoTiling_r(0, x, y, tiling, 0);

	for(int i = 0; i < N; i++){
		delete[] grid[i];
	}
	
	delete[] grid;
	return cpt;
}
/*
int main(){
	domino* t = NULL;
	cout << dominoTiling(6, 7, 1, 2, 11000, t) << endl;
	return 0;
}
*/
