#ifndef dyArr.h
#define dyArr.h

typedef struct dyArr;

void initArray(dyArr *a, size_t initialSize);

void insertArray(dyArr *a, point element);

void freeDyArr(dyArr *a);

#endif