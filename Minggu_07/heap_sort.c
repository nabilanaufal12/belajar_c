#include <stdio.h>
#include <stdlib.h>

// Fungsi untuk menukar dua elemen. Ini akan membantu merapikan kode.
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fungsi rekursif heapify
void heapify(int arr[], int n, int i) {
    int largest = i;       // Inisialisasi elemen terbesar sebagai root
    int left = 2 * i + 1;  // anak kiri
    int right = 2 * i + 2; // anak kanan

    // Cek jika anak kiri lebih besar dari root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // Cek jika anak kanan lebih besar dari yang terbesar sejauh ini
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Jika elemen terbesar bukan lagi root, tukar posisi dan heapify ulang
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// Fungsi utama Heap Sort (logika dari modul)
void heapSort(int arr[], int n) {
    // Bangun Max-Heap dari array input
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Ekstrak elemen satu per satu dari heap
    for (int i = n - 1; i > 0; i--) {
        // Pindahkan root (elemen terbesar) ke akhir array
        swap(&arr[0], &arr[i]);
        
        // Panggil heapify pada heap yang ukurannya sudah berkurang
        heapify(arr, i, 0);
    }
}

// Fungsi untuk menampilkan isi array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]); // Ditambah spasi agar rapi
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
    heapSort(data, count);

    printf("Sorted Array (10 elemen pertama): ");
    printArray(data, (count < 10) ? count : 10);
    
    // Wajib bebaskan memori yang sudah dipesan
    free(data);

    return 0;
}
