#include<stdio.h>

void fungsiv1(int *p){
  *p = 10;
}

void fungsiv2(int p){
  p = 15;
}

int main(){
  int a = 5;
  printf("int a = 5; \t====> a = %d\n", a);

  fungsiv1(&a);
  printf("fungsiv1(&a); \t====> a = %d\n", a);

  fungsiv2(a);
  printf("fungsiv2(a); \t====> a = %d\n", a);

  int *b;
  b = &a;
  *b = 100;
  printf("*b = 100; \t====> a = %d\n", a);

  fungsiv1(b);
  printf("fungsiv1(b); \t====> a = %d\n", a);
  
  return 0;
}
