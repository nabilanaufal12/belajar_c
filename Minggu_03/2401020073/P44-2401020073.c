#include <stdio.h>
#include <stdlib.h>

void ite2401020073(int n) {
  for (int i = 0; i < n; i++) {
    char huruf_besar = 'A' + i;
    char huruf_kecil = 'a' + i;
    
    for (int j = 0; j < n; j++) {
      if (j < i + 1) {
        printf("%c", huruf_besar);
      } else {
        printf("%c", huruf_kecil);
      }
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("harus dengan format %s <n>\n", argv[0]);
    return 1;
  }
  
  int n = atoi(argv[1]);
  
  ite2401020073(n);
  
  return 0;
}
