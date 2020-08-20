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

int checkOOB(struct point pnt){
	if(pnt.y-1 < 0 || pnt.y+1 > mH || pnt.x-1 < 0 || pnt.x+1 > mW){
		return 1;
	}
	return 0;
}

struct point pickDir(int maze[mW][mH], struct point pnt){
	
	struct point failure = {-1, -1};

	if(checkOOB(pnt) != 0){
		return failure;
	}

	struct point n = { pnt.x, pnt.y-1 },
				 e = { pnt.x+1, pnt.y },
				 s = { pnt.x, pnt.y+1 },
				 w = { pnt.x-1, pnt.y};

	int northPossible,
		eastPossible,
		southPossible,
		westPossible;

	if(&maze[n.x][n.y] == 0){
	    northPossible = 1;
	}else{
		northPossible = 0;
	}
	if(&maze[e.x][e.y] == 0){
	    eastPossible = 1;
	}else{
		eastPossible = 0;
	}
	if(&maze[s.x][s.y] == 0){
	    southPossible = 1;
	}else{
		southPossible = 0;
	}
	if(&maze[w.x][w.y] == 0){
	    westPossible = 1;
	}else{
		westPossible = 0;
	}

    int sum = (northPossible + eastPossible + southPossible + westPossible) - 1;

	int num =  getNum(0, sum);

	if(num == 0){
	    return n;
	}else if(num == 1){
		return e;
	}else if(num == 2){
		return s;
	}else if(num == 3){
		return w;
	}else{
		return failure;
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
	//int maze[mW][mH];
	
	//mazeInit(maze);

	//printMaze(maze);

	struct point pnt = {0,0};

	struct dirInfo info = {
        pnt.x, pnt.y - 1,
        pnt.x + 1, pnt.y,
        pnt.x, pnt.y + 1,
        pnt.x - 1, pnt.y,

	        /*
	    &maze[ pnt.x] [ pnt.y - 1],
		&maze[ pnt.x + 1 ] [ pnt.y ],
		&maze[ pnt.x ] [ pnt.y + 1 ],
		&maze[ pnt.x - 1 ] [ pnt.y ],
	         */
	};

	return 0;
}