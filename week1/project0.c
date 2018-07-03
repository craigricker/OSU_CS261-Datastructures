#include <stdio.h>
#include <math.h>

float herons(float a, float b, float c) {
   float area;
   float s;
   s = (a+b+c)/2;
   area = sqrt(s *(s-a)*(s-b)*(s-c));
   return area;
}

int main(int argc, const char * argv[]) {
   // insert code here...
   float area = herons(4,13,15);
   printf("The area is %.5f!\n", area);
   return 0;
}

