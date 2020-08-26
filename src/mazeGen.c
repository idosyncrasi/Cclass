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

    point n,e,s,w;

    if(northPos != 0){
        n = (point){ pnt.x, pnt.y-1 };
    }else if(eastPos != 0){
        e = (point){ pnt.x+1, pnt.y };
    }else if(southPos != 0){
        s = (point){ pnt.x, pnt.y+1 };
    }else if(westPos != 0){
        w = (point){ pnt.x-1, pnt.y };
    }

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

    // TODO(#2): Fails, find a way to get it to output something
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
