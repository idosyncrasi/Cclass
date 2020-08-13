#include <stdio.h>
#include "include/functions.h"

int add(int x,int y){
	return x + y;
}

void doAdd(){
	printf("%d\n",add(5,4));
	printf("%d\n",add(6,14));
}