#include <stdio.h>
#include <stdlib.h>

#include "../include/dyArr.h"
#include "../include/point.h"

typedef struct {
  point *array;
  size_t used;
  size_t size;
}dyArr;

void initArray(dyArr *a, size_t initialSize) {
  a->array = malloc(initialSize * sizeof(point));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(dyArr *a, point element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(point));
  }
  a->array[a->used++] = element;
}

void freeDyArr(dyArr *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}