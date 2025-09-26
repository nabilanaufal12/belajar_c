#include <stdio.h>
#include <string.h>

struct Mahasiswa {
  char nim[20];
  char nama[50];
};

int main() {
  struct Mahasiswa daftar_mahasiswa[100];
  int jumlah_data = 0;
  char jawaban;
  
  printf("Array Statis.\n");
  
  do {
    printf("\nMasukkan NIM: ");
    scanf("%19s", daftar_mahasiswa[jumlah_data].nim);
    
    printf("Masukkan Nama: ");
    while (getchar() != '\n'); 
    scanf("%49[^\n]", daftar_mahasiswa[jumlah_data].nama);

    jumlah_data++;

    printf("\nMasih ada Data? [Y/T]: ");
    scanf(" %c", &jawaban);

    if (jumlah_data >= 100) {
      printf("\nKapasitas data sudah penuh (100).\n");
      break;
    }

  } while (jawaban == 'Y' || jawaban == 'y');

  printf("\nNIM\t\tNAMA\n");
  printf("==========================\n");

  for (int i = 0; i < jumlah_data; i++) {
    printf("%s\t%s\n", daftar_mahasiswa[i].nim, daftar_mahasiswa[i].nama);
  }

  return 0;
}

