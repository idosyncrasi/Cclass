#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/point.h"

typedef struct {
    int x, y;
}point;

point origin   = {0,  0}, errGen   = {-1, 0}, errOOB   = {-1, 1}, errNoDir = {-1, 2};

void printPoint(point pnt, char* name){
	printf("%s.x: %d, %s.y: %d\n", name, pnt.x, name, pnt.y);
}

bool equalTo(point pnt1, point pnt2){
    if(pnt1.x == pnt2.x && pnt1.y == pnt2.y){
        return true;
    }else{
        return false;
    }
}

int getPointError(point res){
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
		return 0;
	}
}