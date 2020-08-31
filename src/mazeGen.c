#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/mazeGen.h"
#include "../include/point.h"
#include "../include/dyArr.h"

int mW = 10;
int mH = 10;

point pickDir(int maze[mW][mH], point pnt){

    int northPos = 1,
        eastPos  = 1,
        southPos = 1,
        westPos  = 1;

	//Debug prints
	// printf("\npnt.x: %d, pnt.y: %d\n\n", pnt.x, pnt.y);

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
	// printf("northPos: %d\n", northPos);
	// printf("southPos: %d\n", southPos);
	// printf("westPos: %d\n", westPos);
	// printf("eastPos: %d\n\n", eastPos);

	// printf("North, pnt.x: %d, pnt.y: %d\n", pnt.x, pnt.y-1);
	// printf("South, pnt.x: %d, pnt.y: %d\n", pnt.x, pnt.y+1);
	// printf("West, pnt.x: %d, pnt.y: %d\n", pnt.x-1, pnt.y);
	// printf("East, pnt.x: %d, pnt.y: %d\n\n", pnt.x+1, pnt.y);

	// If the index exists, assign a point to it
    point n,e,s,w;
    if(northPos != 0){
		n = (point){ pnt.x, pnt.y-1 };
	}else{
		n = (point){ -1, -1};
	}
	if(eastPos != 0){
        e = (point){ pnt.x+1, pnt.y };
    }else{
		e = (point){ -1, -1};
	}
	if(southPos != 0){
        s = (point){ pnt.x, pnt.y+1 };
    }else{
		s = (point){ -1, -1};
	}
	if(westPos != 0){
        w = (point){ pnt.x-1, pnt.y };
    }else{
		w = (point){ -1, -1};
	}

	// Debug prints
	// printf("n.x: %d, n.y: %d\n", n.x, n.y);
	// printf("s.x: %d, s.y: %d\n", s.x, s.y);
	// printf("w.x: %d, w.y: %d\n", w.x, w.y);
	// printf("e.x: %d, e.y: %d\n\n", e.x, e.y);

	// If the spot is not filled already

    if( maze[n.x][n.y] == 1 && northPos != 0 ){
        northPos = 0;
    }
	if( maze[s.x][s.y] == 1 && southPos != 0 ){
        southPos = 0;
    }
	if( maze[e.x][e.y] == 1 && eastPos != 0 ){
        eastPos = 0;
    }
	if( maze[w.x][w.y] == 1 && westPos != 0 ){
        westPos = 0;
    }

	// Debug prints
	// printf("northPos: %d\n", northPos);
	// printf("southPos: %d\n", southPos);
	// printf("westPos: %d\n", westPos);
	// printf("eastPos: %d\n\n", eastPos);

    int sum = northPos + eastPos + southPos + westPos;

	// If none available, stop
	if(sum == 0){
		return errNoDir;
	}

	int count = 0;
	point arr[sum];

    if(northPos == 1){
		arr[count] = n;
		count++;
    }
	if(eastPos == 1){
        arr[count] = e;
		count++;
    }
	if(southPos == 1){
        arr[count] = s;
		count++;
    }
	if(westPos == 1){
        arr[count] = w;
		count++;
    }

	int pick = rand() % sum;

	if(sum >= pick){
	    return arr[pick];
	}

	return errNoDir;
}

point traverse(int maze[mW][mH], point pnt){
	point dir = pickDir(maze, pnt);

	if(dir.x == -1){
		return errNoDir;
	}

	maze[pnt.x][pnt.y] = 1;

	printf("Move to: ");
	printPoint(dir, "dir");


	return dir;
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

int main(){
    srand(time(0));
    int maze[mW][mH];
	point history[mW*mH];

    mazeInit(maze);

	for(int i = 0; i < 1000; i++){
    	origin = traverse(maze, origin);
		if(origin.x == -1){
			getPointError(origin);
			break;
		}
	}

	printMaze(maze);

	return 0;
}
