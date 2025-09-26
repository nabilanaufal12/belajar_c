#include <stdio.h>
#include <stdlib.h> // Diperlukan untuk malloc() dan free()

int main() {

    // --- 1. ARRAY STATIS ---
    // Ukuran HARUS sudah diketahui saat menulis kode.
    // Memori dialokasikan di Stack.
    printf("--- Array Statis ---\n");
    int nilai_statis[5]; // Ukuran 5 sudah dipesan pasti.
    
    // Mengisi dan menampilkan array statis
    printf("Mengisi 5 data ke array statis...\n");
    for (int i = 0; i < 5; i++) {
        nilai_statis[i] = (i + 1) * 10; // Mengisi dengan nilai 10, 20, 30, ...
        printf("nilai_statis[%d] = %d\n", i, nilai_statis[i]);
    }
    printf("\n");


    // --- 2. ARRAY DINAMIS ---
    // Ukuran bisa ditentukan saat program berjalan.
    // Memori dialokasikan di Heap.
    printf("--- Array Dinamis ---\n");
    int jumlah_data;
    int* nilai_dinamis; // Siapkan sebuah pointer, bukan array biasa.

    printf("Mau berapa banyak data yang disimpan? ");
    scanf("%d", &jumlah_data);

    // Pesan memori (malloc) sebanyak yang user minta
    nilai_dinamis = (int*) malloc(jumlah_data * sizeof(int));

    // PENTING: Selalu cek apakah malloc berhasil.
    // Jika memori habis, malloc akan mengembalikan NULL.
    if (nilai_dinamis == NULL) {
        printf("Gagal mengalokasikan memori!\n");
        return 1; // Keluar dari program dengan kode error
    }

    // Mengisi dan menampilkan array dinamis
    printf("Mengisi %d data ke array dinamis...\n", jumlah_data);
    for (int i = 0; i < jumlah_data; i++) {
        nilai_dinamis[i] = (i + 1) * 100; // Mengisi dengan 100, 200, 300, ...
        printf("nilai_dinamis[%d] = %d\n", i, nilai_dinamis[i]);
    }
    
    // PENTING: "Check-out" atau kembalikan memori yang sudah dipinjam.
    free(nilai_dinamis);
    printf("\nMemori dinamis sudah dikembalikan (free).\n");

    return 0;
}
