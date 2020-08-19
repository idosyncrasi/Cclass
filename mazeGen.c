#include <stdlib.h>
#include <stdbool.h>

int getNum(int lower, int upper){
    int num = (rand() % (upper - lower + 1)) + lower;
    return(num);
}

int main(){

    // TODO: Get input for height and width

	int mW = 10; // TEST NUMS
	int mH = 10; // TEST NUMS

	// Make maze array
	int maze[mW][mH];

	// Fill array with free space
	for(int i = 0; i < mW; i++){
		for(int v = 0; v < mH; v++){
			maze[i][v] = 0;
		}
	}

	// Start gen from corner
    int curSpot[2] = {0,0};

	// TODO: Check if index out of bounds
	int north; //= maze[curSpot[0]][curSpot[1]-1];
	int east ; // = maze[curSpot[0]+1][curSpot[1]];
	int south; // = maze[curSpot[0]][curSpot[1]+1];
	int west ; //= maze[curSpot[0]-1][curSpot[1]];

	if(north == 0){
	    bool northPossible = true;
	}

	return 0;
}

