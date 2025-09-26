#include <stdio.h>
#include <stdlib.h>

void cetakKotak(int baris, int kolom) {
  printf("Hello, World!\n");
  
  for (int i = 0; i < baris; i++) {
    for (int j = 0; j < kolom; j++) {
      printf("o");
    }
    printf("\n");
  }
}

int main (int argc, char *argv[]) {
  if (argc != 3 || argc == 1) {
    printf("harus dengan format %s <baris> <kolom>\n", argv[0]);
    return 1;
  }
  
  int baris = atoi(argv[1]);
  int kolom = atoi(argv[2]);
  
  cetakKotak(baris, kolom);
  
  return 0;
}
