#include <stdio.h>
#include <string.h>

int main() {
  FILE *filePointer;
  char dataToBeWritten[] = "Belajar Struktur Data itu mudah.";

  // Buka file TestFile.txt dalam mode "w" (tulis)
  filePointer = fopen("TestFile.txt", "w");

  // Cek jika file berhasil dibuka
  if (filePointer == NULL) {
    printf("TestFile.txt gagal dibuka.\n");
  } else {
    printf("File dibuka dan mulai menulis ke file.\n");

    // Hanya tulis jika stringnya tidak kosong
    if (strlen(dataToBeWritten) > 0) {
      // Tulis isi string ke file
      fputs(dataToBeWritten, filePointer);
      // Tulis karakter baris baru ke file
      fputs("\n", filePointer);
    }
    
    // Tutup file
    fclose(filePointer);
    
    printf("Data sukses ditulis ke file TestFile.txt\n");
    printf("File ditutup.\n");
  }

  return 0;
}
