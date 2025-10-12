#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void countingSort(int array[], int size) {
    if (size == 0) return;

    // Buat array output seukuran data asli
    int* output = (int*) malloc(size * sizeof(int));
    if (output == NULL) {
        printf("Gagal alokasi memori untuk output!\n");
        return;
    }

    // Cari elemen dengan nilai terbesar dalam array
    int max = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    // Buat array 'count' seukuran nilai maksimum
    // PENTING: Menggunakan malloc agar tidak terjadi stack overflow jika max sangat besar
    int* count = (int*) malloc((max + 1) * sizeof(int));
    if (count == NULL) {
        printf("Gagal alokasi memori untuk count!\n");
        free(output);
        return;
    }
    
    // Inisialisasi semua elemen count menjadi 0
    for(int i = 0; i <= max; i++) {
        count[i] = 0;
    }

    // Simpan hitungan (frekuensi) dari setiap elemen
    for (int i = 0; i < size; i++) {
        count[array[i]]++;
    }

    // Ubah 'count' menjadi 'cumulative count'
    for (int i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }

    // Bangun array output dari belakang agar stabil
    for (int i = size - 1; i >= 0; i--) {
        output[count[array[i]] - 1] = array[i];
        count[array[i]]--;
    }

    // Salin array output yang sudah terurut ke array asli
    for (int i = 0; i < size; i++) {
        array[i] = output[i];
    }
    
    // Bebaskan memori yang dialokasikan di dalam fungsi ini
    free(output);
    free(count);
}

// Fungsi untuk menampilkan isi array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Cara pakai: %s <namafile.csv>\n", argv[0]);
        return 1;
    }

    FILE *fptr;
    char *filename = argv[1];
    int number, count = 0;
    
    fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Error: Tidak bisa membuka file %s\n", filename);
        return 1;
    }
    while (fscanf(fptr, "%d", &number) == 1) {
        count++;
    }
    fclose(fptr);

    int* data = (int*) malloc(count * sizeof(int));
    if (data == NULL) {
        printf("Gagal mengalokasikan memori!\n");
        return 1;
    }

    fptr = fopen(filename, "r");
    int i = 0;
    while (fscanf(fptr, "%d", &data[i]) == 1) {
        i++;
    }
    fclose(fptr);

    printf("Original Array (10 elemen pertama): ");
    printArray(data, (count < 10) ? count : 10);

    // Panggil fungsi sorting
    countingSort(data, count);

    printf("Sorted Array (10 elemen pertama): ");
    printArray(data, (count < 10) ? count : 10);
    
    free(data);

    return 0;
}
