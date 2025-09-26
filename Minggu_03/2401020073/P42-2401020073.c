#include <stdio.h>
#include <stdlib.h>

void cetakSegitiga(int tinggi) {
  printf("Hello, World!\n");
  
  for (int i = 0; i < tinggi; i++) {
    for (int spasi = 0; spasi < tinggi - i - 1; spasi++) printf(" ");
    for (int j = 0; j < 2 * i + 1; j++) printf("o");
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("harus dengan format %s <tinggi>\n", argv[0]);
    return 1;
  }
  
  int tinggi = atoi(argv[1]);
  
  cetakSegitiga(tinggi);
  
  return 0;
}

