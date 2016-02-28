#include <math.h>

typedef struct Point {
  double x;
  double y;
} Point;

double distance(Point *a, Point *b){
  return hypot(a->x - b->x, a->y - b->y);
};
