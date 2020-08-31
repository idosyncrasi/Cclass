#ifndef point.h
#define point.h

typedef struct point;

point origin;

void printPoint(point pnt, char* name);

bool equalTo(point pnt1, point pnt2);

int getPointError(point res);

#endif