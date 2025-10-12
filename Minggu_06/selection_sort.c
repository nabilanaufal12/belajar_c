#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int arr[], int idxA, int idxB) {
    int temp = arr[idxA];
    arr[idxA] = arr[idxB];
    arr[idxB] = temp;
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(arr, min_idx, i);
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
    selectionSort(data, jumlah);
    akhir = clock();

    penggunaan_waktu_cpu = ((double) (akhir - mulai)) / CLOCKS_PER_SEC;

    printf("algoritma: selection sort\n");
    printf("jumlah data: %d\n", jumlah);
    printf("waktu eksekusi: %f detik\n", penggunaan_waktu_cpu);

    free(data);
    
    return 0;
}
