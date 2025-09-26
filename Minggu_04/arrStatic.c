#include <stdio.h>
#include <stdlib.h>

#define UKURAN_MAX 5

int main(int argc, char *argv[]) {
  int nilai[UKURAN_MAX];
  int jumlah_input;
  
  if (argc < 2) {
    printf("gunakan: %s <nilai1> <nilai2> ...\n", argv[0]);
    return 1;
  }
  
  jumlah_input = (argc - 1 < UKURAN_MAX) ? (argc - 1) : UKURAN_MAX;
  
  for (int i = 0; i < jumlah_input; i++) {
    nilai[i] = atoi(argv[i + 1]);
  }
  
  // mengambil dan mencetak nilai dari array
  printf("nilai-nilai yang dimasukkan:\n");
  for (int i = 0; i < jumlah_input; i++) {
    printf("nilai[%d]: %d\n", i, nilai[i]);
  }

  return 0;
}
