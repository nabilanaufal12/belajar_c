#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int arr[], int n) {
  int i, kunci, j;
  for (i = 1; i < n; i++) {
   kunci = arr[i];
   j = i - 1;
   
   while (j >= 0 && arr[j] > kunci) {
    arr[j + 1] = arr[j];
    j = j - 1;
   }
   arr[j + 1] = kunci;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("format: %s <namafile.csv>\n", argv[0]);
    return 1;
  }
  
  FILE *fptr;
  char *namafile = argv[1];
  int nomor, jumlah = 0;
  
  fptr = fopen(namafile, "r");
  if (fptr == NULL) {
    printf("error: tidak bisa membuka file %s\n", namafile);
    return 1;
  }
  while (fscanf(fptr, "%d", &nomor) == 1) {
    jumlah++;
  }
  fclose(fptr);
  
  int* data = (int*) malloc(jumlah * sizeof(int));
  fptr = fopen(namafile, "r");
  int i = 0;
  while (fscanf(fptr, "%d", &data[i]) == 1) {
    i++;
  }
  fclose(fptr);
  
  clock_t mulai, akhir;
  double penggunaan_waktu_cpu;

  mulai = clock();
  insertionSort(data, jumlah);
  akhir = clock();

  penggunaan_waktu_cpu = ((double) (akhir - mulai)) / CLOCKS_PER_SEC;

  printf("algoritma: insertion sort\n");
  printf("jumlah data: %d\n", jumlah);
  printf("waktu eksekusi: %f detik\n", penggunaan_waktu_cpu);
  
  free(data);
  
  return 0;
}
