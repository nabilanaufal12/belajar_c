#include <stdio.h>
#include <stdlib.h>

// Mendefinisikan sebuah struktur data
struct threeNum {
  int n1, n2, n3;
};

int main() {
  int n;
  struct threeNum num;
  FILE *fptr;

  // Buka file dalam mode "wb" (write binary / tulis biner)
  if ((fptr = fopen("AyoTebakAdaDimana.bin", "wb")) == NULL) {
    printf("Error! Gagal buka file");
    exit(1);
  }

  // Loop untuk menulis 4 set data struct ke file
  for (n = 1; n < 5; ++n) {
    // Isi nilai ke dalam struct
    num.n1 = n;
    num.n2 = 5 * n;
    num.n3 = 5 * n + 1;
    
    // Tulis satu blok 'struct threeNum' ke file
    fwrite(&num, sizeof(struct threeNum), 1, fptr);
  }
  
  // Tutup file
  fclose(fptr);
  
  printf("File biner berhasil ditulis.\n");

  return 0;
}
