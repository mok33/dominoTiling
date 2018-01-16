#include <iostream>
#include "stdlib.h"
#include <cmath>

int const HORIZONTALE = 1;
int const VERTICALE = 2;
int const EMPTY = 0;
//grid dimension N x M
int N = 0;
int M = 0;
//domino dimension N_D x M_D 
int N_D = 0;
int M_D = 0;
//grid
int** grid = NULL;

using namespace std;

bool placeDomino(int type, int & x, int & y, int val){
	cout << "place @(" << y << ", " << x << ") " << type << endl;
	
	
	int condition = M_D;
	int i = 1;
	int x_0 = x;
	int y_0 = y;
	
	bool ok;
		
	if(type == VERTICALE){
		condition = N_D;

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
		
		for(int p = 0; p < N; p++){
			for(int m = 0; m < M; m++){
				cout << grid[p][m] << " ";
				if(grid[p][m] < 10){
					cout << " " ;
				}
				 
			}
			cout << endl;
		}
		
		
		cout << "after place @(" << y << ", " << x << ") " << endl;
		
		y = y_0;
		if(x == M && y < N){
			x = 0;
			y++;
		}
		cout << "after rep @(" << y << ", " << x << ") " << endl;

		//place cursor in a empty slot
		while(y < N && grid[y][x] != EMPTY){			
			x++;
			if(x == M && y < N){
				x = 0;
				y++;
			}
		}		
			cout << "place ok @(" << y << ", " << x << ") " << endl;
		
	}
	else{
		cout << "place error @(" << y << ", " << x << ") " << type << endl;
	}
	return i > N_D * M_D;
}
void removeDomino(int type, int x , int y){
	//cout << "remove @(" << y << ", " << x << ") " << type << endl;
	int id = 0;
	
	if(x < M && y < N){
		id = grid[y][x];
	}

	int condition = M_D;
	int i = 1;
	int x_0 = x;
	
	if(type == VERTICALE){
		condition = N_D;
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
	cout << endl;
	*/
}
int dominoTiling_r(int i, int & x, int & y, int occupied=0){
	int T = 0;
	int spin;
	
	if(occupied == N * M){
		T = 1;
		/*
		 //* uncomment to see each solution
		for(int z = 0; z < N; z++){
			for(int w = 0; w < M; w++){
				
				cout << grid[z][w] << " ";
				if(grid[z][w] < 10){
					cout << " " ;
				}
				 
			}
			cout << endl;
		}
		cout << endl;
		*/
	}
	else{
			
		int x_0 = x;
		int y_0 = y;
		
		spin = VERTICALE;
		
		if(placeDomino(spin, x, y, i+1)){
			T += dominoTiling_r(i+1, x, y, occupied + N_D * M_D);
		}
		removeDomino(spin, x_0, y_0);

		x = x_0;
		y = y_0;
		
		spin = HORIZONTALE;
		if(placeDomino(spin, x, y, i+1)){
			T += dominoTiling_r(i+1, x, y, occupied + N_D * M_D);
		}
		removeDomino(spin, x_0, y_0);	
	}
	
	return T;

}
int dominoTiling(int n, int m, int d_n = 1, int d_m = 2){
	N = n;
	M = m;
	
	N_D = d_n;
	M_D = d_m;
	
	grid = new int*[N];
	
	for(int i = 0; i < N; i++){
		grid[i] = new int[M];
		for(int j = 0; j < M; j++){
			grid[i][j] = EMPTY;
		}
	}
	
	int x = 0;
	int y = 0;

	int cpt = dominoTiling_r(0, x, y);

	for(int i = 0; i < N; i++){
		delete[] grid[i];
	}
	
	delete[] grid;

	return cpt;
}

int main(int argc, char* argv[]){
	cout << dominoTiling(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4])) << endl;
	return 0;
}
