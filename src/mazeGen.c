#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int mw = 10;
int mh = 10;

typedef struct point{int x, y;}point;

typedef struct pointId {int id;struct point pnt;}pointId;

pointId history[5000];

point origin   = {0,  0}, errGen   = {-1, 0}, errOOB   = {-1, 1}, errNoDir = {-1, 2};

void printPoint(struct point pnt, char* name){
    printf("%s.x: %d, %s.y: %d\n", name, pnt.x, name, pnt.y);
}
void printHistPoint(struct pointId pnt, char* name){
    printf("%s%d.x: %d, %s%d.y: %d\n",
        name, pnt.id, pnt.pnt.x, name, pnt.id, pnt.pnt.y);
}

int sizeofHist(){return sizeof(history)/sizeof(history[0]);}

point pickDir(int maze[mw][mh], struct point pnt, bool debug){

    // I suspect TODO#1 to be somewhere in this funciton

    int northPos = 1,
        eastPos  = 1,
        southPos = 1,
        westPos  = 1;

	if(debug){
	   printf("\npnt.x: %d, pnt.y: %d\n\n", pnt.x, pnt.y);
    }
    

    // Check if index doesn't exist
    if(pnt.y-1 < 0 ){
        northPos = 0;
    }
    if(pnt.y+1 >= mh){
        southPos = 0;
    }
    if(pnt.x-1 < 0){
        westPos = 0;
    }
    if(pnt.x+1 >= mw){
        eastPos = 0;
    }

	if(debug){
    	printf("northPos: %d\n", northPos);
    	printf("southPos: %d\n", southPos);
    	printf("westPos: %d\n", westPos);
    	printf("eastPos: %d\n\n", eastPos);

    	printf("North, pnt.x: %d, pnt.y: %d\n", pnt.x, pnt.y-1);
    	printf("South, pnt.x: %d, pnt.y: %d\n", pnt.x, pnt.y+1);
    	printf("West, pnt.x: %d, pnt.y: %d\n", pnt.x-1, pnt.y);
    	printf("East, pnt.x: %d, pnt.y: %d\n\n", pnt.x+1, pnt.y);
    }

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

	if(debug){
    	printf("n.x: %d, n.y: %d\n", n.x, n.y);
    	printf("s.x: %d, s.y: %d\n", s.x, s.y);
    	printf("w.x: %d, w.y: %d\n", w.x, w.y);
    	printf("e.x: %d, e.y: %d\n\n", e.x, e.y);
    }

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

    if(debug){
        printf("n filled: %d\n"  , maze[n.x][n.y] == 1);
        printf("s filled: %d\n"  , maze[s.x][s.y] == 1);
        printf("e filled: %d\n"  , maze[e.x][e.y] == 1);
        printf("w filled: %d\n\n", maze[w.x][w.y] == 1);

    	printf("northPos: %d\n", northPos);
    	printf("southPos: %d\n", southPos);
    	printf("westPos: %d\n", westPos);
    	printf("eastPos: %d\n\n", eastPos);
    }

    int sum = northPos + eastPos + southPos + westPos;

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

bool equalTo(struct point pnt1, struct point pnt2){
    if(pnt1.x == pnt2.x && pnt1.y == pnt2.y){
        return true;
    }else{
        return false;
    }
}

int getPointError(struct point res){
    if(equalTo(res, errGen)){
        return 1;
    }else if(equalTo(res, errOOB)){
        return 2;
    }else if(equalTo(res, errNoDir)){
        return 3;
    }else{
        return 0;
    }
}

void printPointError(struct point res){
    if(getPointError(res) == 1){
        printf("\033[31mError\n\033[0m");
    }else if(getPointError(res) == 2){
        printf("\033[31mIndex out of bounds\n\033[0m");
    }else if(getPointError(res) == 3){
        printf("\033[31mNo direction found\n\033[0m");
    }else{
        printf("No error\n");
    }
}

point traverse(int maze[mw][mh], struct point pnt, bool debug){
	point dir = pickDir(maze, pnt, debug);

    for(int i = 0; i < sizeofHist(); i++){
        if(history[i].id == -1 && !(equalTo(dir, history[i].pnt))){
            history[i].pnt = dir;
            history[i].id = i;
            break;
        }
    }

	maze[pnt.x][pnt.y] = 1;

	return dir;
}

void mazeInit(int maze[mw][mh]){
    for(int i = 0; i < mw; i++){
        for(int v = 0; v < mh; v++){
            maze[i][v] = 0;
        }
    }
    for(int i = 0; i < sizeofHist(); i++){
        history[i].id = -1;
    }
}

void printMazeColor(int maze[mw][mh]){
    for(int i = 0; i < mw; i++){
        for(int v = 0; v < mh; v++){
            if(maze[i][v] == 0){
	    	printf("\033[1;47m \033[0m");
	    	}else{
	    		printf(" ");
	    	}
        }
        printf("\n");
    }
}

void printMaze(int maze[mw][mh]){
    for(int i = 0; i < mw; i++){
        for(int v = 0; v < mh; v++){
	    	if(maze[i][v] == 1){
                printf("\033[31m%d\033[0m ", maze[i][v]);
            }else{
                printf("%d ", maze[i][v]);
            }
        }
        printf("\n");
    }
}

void writeHist(){
    for(int i = 0; i < sizeofHist(); i++){
        if(history[i].id != -1){
            if(getPointError(history[i].pnt) == 0){
                printHistPoint(history[i], "hist");
            }else{
                printPointError(history[i].pnt);
            }
        }
    }
}

int gen(bool debug){
    srand(time(0));
    int maze[mw][mh];

    mazeInit(maze);

    for(int i = 0; i < 100; i++){
        origin = traverse(maze, origin, debug);

        if(getPointError(origin) != 0 && debug){
            printPointError(origin);
            break;
            // If break, backtrack until open space, re traverse, repeat until full
        }
    }

    printMaze(maze);

    if(debug){
        writeHist();
    }

    return 0;
}

int dbgGen(){
    int ret = gen(true);
    return ret;
}

int main(){
    return dbgGen();
}

// TODO#1: Somewhere returns a point with a y value of 10, it should be 9. 
//         This is becuase array indexes go from 0-9 for a 10 index array, not 1-10.
//         It causes the array to overflow, leaving visited points that are not
//         connected to the rest of the maze.