#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int *nilai;
  int jumlah_input;
  
  if (argc < 2) {
   printf("gunakan: %s <nilai1> <nilai2> ...\n", argv[0]);
   return 1;
  }
  
  jumlah_input = argc - 1;
  
  nilai = (int *)malloc(jumlah_input * sizeof(int));
  
  if (nilai == NULL) {
    printf("gagal mengalokasikan memori.\n");
    return 1;
  }
  
  for (int i = 0; i < jumlah_input; i++) {
    nilai[i] = atoi(argv[i + 1]);
  }
  
  printf("nilai-nilai yang dimasukkan:\n");
  for (int i = 0; i < jumlah_input; i++) {
    printf("nilai[%d]: %d\n", i, nilai[i]);
  }
  
  free(nilai);
  nilai = NULL;

  return 0;
}
