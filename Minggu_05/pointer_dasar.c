#include <stdio.h>

int a;
int *b;

int main(int argc, char** argv) {
  a = 10;
  b = &a;
  *b = 2; 

  printf("a= %d\n", a); 
  
  return 0;
}
