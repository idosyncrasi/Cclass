#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mW = 10;
int mH = 10;

int getNum(int lower, int upper){
    int num = (rand() % (upper - lower + 1)) + lower;
    return(num);
}

struct point{
	int x, y;
};

struct dirInfo{
    struct point *north, *east, *south, *west;

    int northPossible, eastPossible, southPossible, westPossible;
};

int checkOOB(struct point pnt){
	if(pnt.y-1 < 0 || pnt.y+1 > mH || pnt.x-1 < 0 || pnt.x+1 > mW){
		return 1;
	}
	return 0;
}

int pickDir(int maze[mW][mH], struct point pnt){
	
	if(checkOOB(pnt) != 0){
		return -1;
	}

	struct dirInfo info = {
        {pnt.x, pnt.y - 1}
        {pnt.x + 1, pnt.y}
        {pnt.x, pnt.y + 1}
        {pnt.x - 1, pnt.y}

	        /*
	    &maze[ pnt.x] [ pnt.y - 1],
		&maze[ pnt.x + 1 ] [ pnt.y ],
		&maze[ pnt.x ] [ pnt.y + 1 ],
		&maze[ pnt.x - 1 ] [ pnt.y ],
	         */
	};

	if(info.north == 0){
	    info.northPossible = 1;
	}else{
		info.northPossible = 0;
	}
	if(info.east == 0){
	    info.eastPossible = 1;
	}else{
		info.eastPossible = 0;
	}
	if(info.south == 0){
	    info.southPossible = 1;
	}else{
		info.southPossible = 0;
	}
	if(info.west == 0){
	    info.westPossible = 1;
	}else{
		info.westPossible = 0;
	}

    int sum = info.northPossible + info.eastPossible + info.southPossible + info.westPossible;

	int num =  getNum(0, sum);

	if(num == 0){
	    return &north;
	}
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