#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int mW = 10;
int mH = 10;

int getNum(int lower, int upper){
    int num = (rand() % (upper - lower + 1)) + lower;
    return(num);
}

struct dirInfo{ 
	int *north;
	int *east;
	int *south;
	int *west;

	bool northPossible;
	bool eastPossible;
	bool southPossible;
	bool westPossible;
};

struct point{
	int x;
	int y;
};

int checkOOB(struct point pnt){
	if(pnt.y-1 < 0 || pnt.y+1 > mH || pnt.x-1 < 0 || pnt.x+1 > mW){
		return 1;
	}
	return 0;
}

int pickDir(int maze[mW][mH], struct point pnt){
	
	if(checkOOB(pnt) != 0){
		return 1;
	}

	struct dirInfo info = {
		// TODO: Check if index out of bounds
		&maze[ pnt.x ] [ pnt.y - 1 ],
		&maze[ pnt.x + 1 ] [ pnt.y ],
		&maze[ pnt.x ] [ pnt.y + 1 ],
		&maze[ pnt.x - 1 ] [ pnt.y ],
	};

	if(info.north == 0){
	    info.northPossible = true;
	}else{
		info.northPossible = false;
	}
	if(info.east == 0){
	    info.eastPossible = true;
	}else{
		info.eastPossible = false;
	}
	if(info.south == 0){
	    info.southPossible = true;
	}else{
		info.southPossible = false;
	}
	if(info.west == 0){
	    info.westPossible = true;
	}else{
		info.westPossible = false;
	}



	return 0;
}

void mazeInit(int maze[mW][mH]){
	for(int i = 0; i < mW; i++){
		for(int v = 0; v < mH; v++){
			maze[i][v] = 0;
		}
	}
}

void printMaze(int maze[mW][mH]){
	for(int i = 0; i < mW; i++){
		for(int v = 0; v < mH; v++){
			printf("%d ",maze[i][v]);
		}
		printf("\n");
	}
}

int main(){
	int maze[mW][mH];
	
	mazeInit(maze);
	printMaze(maze);

	return 0;
}