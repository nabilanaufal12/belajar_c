#include <stdio.h>
#include <stdlib.h>

void rec2401020073(int n, int i) {
  if (i >= n) return;
  
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
  
  rec2401020073(n, i + 1);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("untuk linux harus dengan format %s <n>\n", argv[0]);
    return 1;
  }
  
  int n = atoi(argv[1]);
  
  rec2401020073(n, 0);
  
  return 0;
}
