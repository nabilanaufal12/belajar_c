#include <stdio.h>
#include <string.h>

int main() {
  FILE *filePointer;
  char dataToBeRead[50]; // Buffer untuk menampung data yang dibaca

  // Buka file TestFile.txt dalam mode "r" (baca)
  filePointer = fopen("TestFile.txt", "r");

  // Cek jika file gagal dibuka
  if (filePointer == NULL) {
    printf("TestFile.txt gagal dibuka.\n");
  } else {
    printf("File dibuka dan mulai membaca isi file.\n");
    
    // Loop untuk membaca file baris per baris
    while (fgets(dataToBeRead, 50, filePointer) != NULL) {
      // Cetak baris yang baru saja dibaca ke layar
      printf("%s", dataToBeRead);
    }
    
    // Tutup file
    fclose(filePointer);
    
    printf("\nBerhasil membaca TestFile.txt\n");
    printf("File ditutup.\n");
  }
  
  return 0;
}
