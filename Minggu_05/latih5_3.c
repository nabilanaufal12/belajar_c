#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int num;
  FILE *fptr;

  // Buka (atau buat) file dalam mode tulis
  fptr = fopen(argv[1], "w");

  // Cek jika file gagal dibuka
  if (fptr == NULL) {
    printf("Gagal buka file %s!\n", argv[1]);
    exit(1);
  }

  // Minta input dari user
  printf("Masukin 1 angka: ");
  scanf("%d", &num);

  // Tulis angka yang diinput ke dalam file
  fprintf(fptr, "%d", num);

  // Tutup file
  fclose(fptr);
  
  printf("Angka %d berhasil ditulis ke %s\n", num, argv[1]);

  return 0;
}
