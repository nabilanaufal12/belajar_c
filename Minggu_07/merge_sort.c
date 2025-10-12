  #include <stdio.h>
  #include <stdlib.h>

  // Fungsi untuk menggabungkan dua subarray yang sudah terurut
  void merge(int arr[], int left, int mid, int right) {
      int i, j, k;
      int n1 = mid - left + 1;
      int n2 = right - mid;

      // Buat array sementara untuk menampung bagian kiri dan kanan
      int L[n1], R[n2];

      // Salin data ke array sementara
      for (i = 0; i < n1; i++)
          L[i] = arr[left + i];
      for (j = 0; j < n2; j++)
          R[j] = arr[mid + 1 + j];

      // Proses penggabungan kembali ke array utama (arr)
      i = 0; // Indeks awal subarray kiri
      j = 0; // Indeks awal subarray kanan
      k = left; // Indeks awal subarray yang digabungkan

      while (i < n1 && j < n2) {
          if (L[i] <= R[j]) {
              arr[k] = L[i];
              i++;
          } else {
              arr[k] = R[j];
              j++;
          }
          k++;
      }

      // Salin sisa elemen dari L[], jika ada
      while (i < n1) {
          arr[k] = L[i];
          i++;
          k++;
      }

      // Salin sisa elemen dari R[], jika ada
      while (j < n2) {
          arr[k] = R[j];
          j++;
          k++;
      }
  }

  // Fungsi utama Merge Sort yang rekursif
  void mergeSort(int arr[], int left, int right) {
      if (left < right) {
          // Cari titik tengah untuk menghindari overflow
          int mid = left + (right - left) / 2;

          // Panggil mergeSort untuk bagian kiri
          mergeSort(arr, left, mid);
          // Panggil mergeSort untuk bagian kanan
          mergeSort(arr, mid + 1, right); // Perbaikan dari 'mid - 1' di modul

          // Gabungkan kedua bagian yang sudah terurut
          merge(arr, left, mid, right);
      }
  }

  // Fungsi untuk menampilkan isi array
  void printArray(int arr[], int n) {
      for (int i = 0; i < n; i++) {
          printf("%d ", arr[i]);
      }
      printf("\n");
  }

  int main(int argc, char *argv[]) {
      // Cek apakah argumen file CSV diberikan
      if (argc < 2) {
          printf("Cara pakai: %s <namafile.csv>\n", argv[0]);
          return 1;
      }

      FILE *fptr;
      char *filename = argv[1];
      int number, count = 0;
      
      // Buka file untuk MENGHITUNG jumlah data
      fptr = fopen(filename, "r");
      if (fptr == NULL) {
          printf("Error: Tidak bisa membuka file %s\n", filename);
          return 1;
      }
      while (fscanf(fptr, "%d", &number) == 1) {
          count++;
      }
      fclose(fptr);

      // Alokasi memori dinamis dengan ukuran yang pas
      int* data = (int*) malloc(count * sizeof(int));
      if (data == NULL) {
          printf("Gagal mengalokasikan memori!\n");
          return 1;
      }

      // Buka file lagi untuk MEMBACA data ke dalam array
      fptr = fopen(filename, "r");
      int i = 0;
      while (fscanf(fptr, "%d", &data[i]) == 1) {
          i++;
      }
      fclose(fptr);

      printf("Original Array (10 elemen pertama): ");
      printArray(data, (count < 10) ? count : 10);

      // Panggil fungsi sorting
      mergeSort(data, 0, count - 1); // Merge sort butuh indeks awal dan akhir

      printf("Sorted Array (10 elemen pertama): ");
      printArray(data, (count < 10) ? count : 10);
      
      // Wajib bebaskan memori yang sudah dipesan
      free(data);

      return 0;
  }
