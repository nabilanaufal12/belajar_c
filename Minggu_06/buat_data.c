#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void membuatFileData(const char* namafile, int jumlah) {
  FILE *fptr;
  
  fptr = fopen(namafile, "w");
  if (fptr == NULL) {
    printf("error mmebuka file %s!\n", namafile);
    return;
  }
  
  printf("membuat file %s dengan %d data...\n", namafile, jumlah);
  
  for (int i = 0; i < jumlah; i++) {
    int nomorRandom = (rand() % 999991) + 10;
    fprintf(fptr, "%d\n", nomorRandom);
  }
  
  fclose(fptr);
  printf("file %s berhasil dibuat.\n", namafile);
}

int main() {
  srand(time(NULL));
  
  membuatFileData("data100.csv", 100);
  membuatFileData("data1000.csv", 1000);
  membuatFileData("data10000.csv", 10000);
  
  return 0;
}
