#include <stdio.h>
#include <stdlib.h>

// Struct harus sama persis dengan yang digunakan untuk menulis
struct threeNum {
  int n1, n2, n3;
};

int main() {
  int n;
  struct threeNum num;
  FILE *fptr;

  // Buka file dalam mode "rb" (read binary / baca biner)
  if ((fptr = fopen("AyoTebakAdaDimana.bin", "rb")) == NULL) {
    printf("Error! Gagal buka file");
    exit(1);
  }

  printf("Membaca file biner:\n");
  
  // Loop untuk membaca 4 set data struct dari file
  for (n = 1; n < 5; ++n) {
    // Baca satu blok 'struct threeNum' dari file ke variabel num
    fread(&num, sizeof(struct threeNum), 1, fptr);
    
    // Cetak isi struct yang sudah dibaca
    printf("n1: %d\tn2: %d\tn3: %d\n", num.n1, num.n2, num.n3);
  }

  // Tutup file
  fclose(fptr);

  return 0;
}
