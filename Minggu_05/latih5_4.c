#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int num;
  FILE *fptr;

  // Buka file dalam mode "r" (read / baca)
  if ((fptr = fopen(argv[1], "r")) == NULL) {
    printf("Error! Gagal buka file %s\n", argv[1]);
    exit(1);
  }

  // Baca satu integer dari file dan simpan ke variabel 'num'
  fscanf(fptr, "%d", &num);

  // Tampilkan hasil baca ke layar
  printf("Hasil baca file:\n%d\n", num);
  
  // Tutup file
  fclose(fptr);

  return 0;
}
