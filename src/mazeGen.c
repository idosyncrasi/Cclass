#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int mW = 10;
int mH = 10;

int getNum(int lower, int upper){
    int num = (rand() % (upper - lower + 1)) + lower;
    return(num);
}

struct point{
	int x, y;
};
struct point origin   = { 0,  0},
             errGen   = {-1, 0},
             errOOB   = {-1, 1},
             errNoDir = {-1, 2};

struct point pickDir(int maze[mW][mH], struct point pnt){

    int northPos,
        eastPos,
        southPos,
        westPos;

    // North
    if(pnt.y-1 < 0 ){
        northPos = 0;
    }
    // South
    if(pnt.y+1 > mH){
        southPos = 0;
    }
    // West
    if(pnt.x-1 < 0){
        westPos = 0;
    }
    // East
    if(pnt.x+1 > mW){
        eastPos = 0;
    }

    struct point n,e,s,w;

    if(northPos != 0){
        n = { pnt.x, pnt.y-1 };
    }else if(eastPos != 0){
        e = { pnt.x+1, pnt.y };
    }else if(southPos != 0){
        s = { pnt.x, pnt.y+1 }
    }else if(westPos != 0){
        w = { pnt.x-1, pnt.y };
    }

    /*
	struct point n = { pnt.x, pnt.y-1 },
				 e = { pnt.x+1, pnt.y },
				 s = { pnt.x, pnt.y+1 },
				 w = { pnt.x-1, pnt.y };
     */

	if(&maze[n.x][n.y] == 0 && northPos != 0){
	    northPos = 1;
	}else{
		northPos = 0;
	}
	if(&maze[e.x][e.y] == 0 && eastPos != 0){
	    eastPos = 1;
	}else{
		eastPos = 0;
	}
	if(&maze[s.x][s.y] == 0 && southPos != 0){
	    southPos = 1;
	}else{
		southPos = 0;
	}
	if(&maze[w.x][w.y] == 0 && westPos != 0){
	    westPos = 1;
	}else{
		westPos = 0;
	}

	int num =  getNum(0, 3);

	// TODO: Fix; doesnt pick correct directions based on available directions && test
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

void printMaze(int maze[mW][mH]){
	for(int i = 0; i < mW; i++){
		for(int v = 0; v < mH; v++){
			printf("%d ",maze[i][v]);
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

int main(){
	int maze[mW][mH];

	mazeInit(maze);

	printMaze(maze);

	struct point res = pickDir(maze, origin);

	if(equalTo(res, errGen)){
	    printf("Error");
	    return 1;
	}else if(equalTo(res, errOOB)){
	    printf("Index out of bounds");
	    return 2;
	}else if(equalTo(res, errNoDir)){
	    printf("No direction found");
	    return 3;
	}else{

	}

	return 0;
}
