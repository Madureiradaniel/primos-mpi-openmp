#include <stdio.h>
#include <stdlib.h>


void sub(int a, int b, int c) {

 b = a + b;

 c = a - c;

}


void main() {

 int x;

 scanf("%i", &x);


 int y;

 scanf("%i", &y);


 sub(x + y, x, y);


 printf("%d e %d", x, y);

}