#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int mW = 10;
int mH = 10;

int getNum(int lower, int upper){
    int num = (rand() % (upper - lower + 1)) + lower;
    return(num);
}

typedef struct point{
    int x, y;
}point;
point origin   = {0,  0},
             errGen   = {-1, 0},
             errOOB   = {-1, 1},
             errNoDir = {-1, 2};

point pickDir(int maze[mW][mH], struct point pnt){

    int northPos = 1,
        eastPos  = 1,
        southPos = 1,
        westPos  = 1;

	//Debug prints
	printf("pnt.x: %d, pnt.y: %d\n\n", pnt.x, pnt.y);

    // Check if index doesn't exist
    if(pnt.y-1 < 0 ){
        northPos = 0;
    }
    if(pnt.y+1 > mH){
        southPos = 0;
    }
    if(pnt.x-1 < 0){
        westPos = 0;
    }
    if(pnt.x+1 > mW){
        eastPos = 0;
    }

	// Debug prints
	printf("northPos: %d\n", northPos);
	printf("southPos: %d\n", southPos);
	printf("westPos: %d\n", westPos);
	printf("eastPos: %d\n\n", eastPos);

	printf("pnt.x: %d, pnt.y: %d\n", pnt.x, pnt.y-1);
	printf("s.x: %d, s.y: %d\n", pnt.x, pnt.y+1);
	printf("w.x: %d, w.y: %d\n", pnt.x-1, pnt.y);
	printf("e.x: %d, e.y: %d\n\n", pnt.x+1, pnt.y);

	// If the index exists, assign a point to it
    point n,e,s,w;
    if(northPos != 0){
		n = (point){ pnt.x, pnt.y-1 };
	}
	if(eastPos != 0){
        e = (point){ pnt.x+1, pnt.y };
    }
	if(southPos != 0){
        s = (point){ pnt.x, pnt.y+1 };
    }
	if(westPos != 0){
        w = (point){ pnt.x-1, pnt.y };
    }

	// Debug prints
	printf("n.x: %d, n.y: %d\n", n.x, n.y);
	printf("s.x: %d, s.y: %d\n", s.x, s.y);
	printf("w.x: %d, w.y: %d\n", w.x, w.y);
	printf("e.x: %d, e.y: %d\n\n", e.x, e.y);

	// If the spot is not filled already
    if( !(&maze[n.x][n.y] == 0 && northPos != 0) ){
        northPos = 0;
    }
	if( !(&maze[n.x][n.y] == 0 && southPos != 0) ){
        southPos = 0;
    }
	if( !(&maze[n.x][n.y] == 0 && eastPos != 0) ){
        eastPos = 0;
    }
	if( !(&maze[n.x][n.y] == 0 && westPos != 0) ){
        westPos = 0;
    }

	// Get random number to find direction
    int num =  getNum(0, 3);

	// Debug prints
	printf("num: %d\n", num);
	printf("northPos: %d\n", northPos);
	printf("southPos: %d\n", southPos);
	printf("westPos: %d\n", westPos);
	printf("eastPos: %d\n\n", eastPos);


    // TODO(#2): Fails, find a way to get it to output something
	// If the test fails once, it will not return a pointer
	// Loop or increment in order to get a value, note that not randomizing the values creates tendancy
    if(num == 0 && northPos == 1){
        return n;
    }else if(num == 1 && eastPos == 1){
        return e;
    }else if(num == 2 && southPos == 1){
        return s;
    }else if(num == 3 && westPos == 1){
        return w;
    }else{
        return errNoDir;
    }
}

void mazeInit(int maze[mW][mH]){
    for(int i = 0; i < mW; i++){
        for(int v = 0; v < mH; v++){
            maze[i][v] = 0;
        }
    }
}

void printMazeColor(int maze[mW][mH]){
    for(int i = 0; i < mW; i++){
        for(int v = 0; v < mH; v++){
            if(maze[i][v] == 0){
	    	printf("\033[1;47m \033[0m");
	    	}else{
	    		printf(" ");
	    	}
        }
        printf("\n");
    }
}

void printMaze(int maze[mW][mH]){
    for(int i = 0; i < mW; i++){
        for(int v = 0; v < mH; v++){
	    	printf("%d ", maze[i][v]);
        }
        printf("\n");
    }
}

bool equalTo(struct point pnt1, struct point pnt2){
    if(pnt1.x == pnt2.x && pnt1.y == pnt2.y){
        return true;
    }else{
        return false;
    }
}

int getError(struct point res){
    if(equalTo(res, errGen)){
        printf("\033[31mError\n\n\033[0m");
        return 1;
    }else if(equalTo(res, errOOB)){
        printf("\033[31mIndex out of bounds\n\n\033[0m");
        return 2;
    }else if(equalTo(res, errNoDir)){
        printf("\033[31mNo direction found\n\n\033[0m");
        return 3;
    }else{
		printf("\n");
		return 0;
	}
}

int main(){
    int maze[mW][mH];

    mazeInit(maze);

    printMaze(maze);

    point res = pickDir(maze, origin);

	return getError(res);
}
