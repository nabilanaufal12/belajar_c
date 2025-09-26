#include <stdio.h>
#include <stdlib.h> // Untuk exit()

int main(int argc, char **argv) {
  // Deklarasi pointer ke FILE
  FILE* fptr;

  // Membuka file yang namanya ada di argumen ke-1
  // dalam mode "r" (read / baca)
  fptr = fopen(argv[1], "r");

  // Jika file tidak berhasil dibuka (misalnya karena tidak ada),
  // fptr akan bernilai NULL
  if (fptr == NULL) {
    printf("Gagal baca file. Program berhenti dengan kode 5.\n");
    exit(5); // Keluar dari program
  }

  // Jangan lupa tutup file jika sudah tidak diperlukan
  fclose(fptr);
  
  // Program berhenti dengan kode 0 (sukses)
  return 0;
}
