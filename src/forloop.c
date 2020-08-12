#include "stdio.h"
#include "forloop.h"

void doForLoop(){
	int arr[5];

	for(int i = 0; i < 5; i++){
		arr[i] = i;
	}

	for(int i = 0; i < 5; i++){
		printf("Index %d, value %d\n",i,arr[i]);
	}
}