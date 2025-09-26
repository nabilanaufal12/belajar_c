#include <stdio.h>
#include <stdlib.h>

void cetakSegitigaTerbalik(int tinggi) {
  printf("Hello, World!\n");
  
  for (int i = 0; i < tinggi; i++) {
    for(int spasi = 0; spasi < i; spasi++) printf(" ");
    printf("o");
    if (i < tinggi - 1) {
      for (int j = 0; j < 2 * (tinggi - i - 1) - 1; j++) printf("-");
      printf("o");
    }
    printf("\n");
  }
}

int main (int argc, char *argv[]) {
  if (argc != 2) {
    printf("harus dengan format %s <tinggi>\n", argv[0]);
    return 1;
  }
  
  int tinggi = atoi(argv[1]);
  
  cetakSegitigaTerbalik(tinggi);
  
  return 0;
}
