#include <stdio.h>

int a;
int *b;
int **c;

int main(int argc, char** argv) {
  a = 10;
  b = &a;
  c = &b;
  
  **c = 1000;
  
  printf("a= %d\n", a);
  
  return 0;
}
