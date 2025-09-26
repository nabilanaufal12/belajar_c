#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  // Deklarasi variabel pointer ke FILE
  FILE *fptr;

  // Membuka file dalam mode "w" (write / tulis)
  fptr = fopen(argv[1], "w");

  // jika file gagal dibuka/dibuat
  if (fptr == NULL) {
    printf("Gagal buka file. Program berhenti dengan kode 5.\n");
    exit(5); // Keluar dari program
  } 
  // selain itu berarti berhasil
  else {
    printf("File berhasil dibuka.\n");
  }

  // jangan lupa tutup file kalau sudah tidak diperlukan.
  fclose(fptr);
  
  // program berhenti dengan kode 0 alias sukses tanpa masalah
  return 0;
}
