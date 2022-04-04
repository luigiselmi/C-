#include <stdio.h>

struct point makepoint(int x, int y);
struct rect makerect(struct point p1, struct point p2);
int inside_rect(struct point p, struct rect r);

struct point {
  int x;
  int y;
};
struct rect {
  struct point upleft;
  struct point btright;
};
/* Shows the usage of data structures using the struct keyword */
int main() {
 struct point location = makepoint(10, 20);
 printf("Location x = %d, y = %d\n", location.x, location.y);

 struct point p1, p2;
 p1 = makepoint(10, 20);
 p2 = makepoint(30, 0);

 // nested structure
 struct rect box = makerect(p1, p2);
 printf("Box coordinates: upperleft point = (%d, %d), bottom right point = (%d, %d)\n", box.upleft.x, box.upleft.y, box.btright.x, box.btright.y);
 struct point p3 = makepoint(20, 10);
 int inside = inside_rect(p3, box);
 printf("Is point p inside the box ? %s\n", inside ? "True" : "False");

 // pointer to a structure
 struct point *pp;
 pp = &p3;
 printf("Location x = %d, y = %d\n", (*pp).x, (*pp).y);
 printf("Location x = %d, y = %d\n", pp->x, pp->y); // direct access from the pointer to the struct element
}
/* Creates a structure of type point from two integer coordinates */
struct point makepoint(int x, int y) {
  struct point temp;
  temp.x = x;
  temp.y = y;
  return temp;
}
struct rect makerect(struct point p1, struct point p2) {
  struct rect temp;
  temp.upleft = p1;
  temp.btright = p2;
  return temp;
}
/* Returns 1 if p is inside r, 0 otherwise */
int inside_rect(struct point p, struct rect r) {
  int conditionx = p.x >= r.upleft.x && p.x < r.btright.x;
  int conditiony = p.y <= r.upleft.y && p.y > r.btright.y;
  int condition = conditionx && conditiony;
  return condition;
}
