#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Mahasiswa {
    char nim[20];
    char nama[50];
};

int main() {
    struct Mahasiswa *daftar_mahasiswa = NULL;
    int jumlah_data = 0;
    char jawaban;
    
    printf("Array Dinamis.\n");
    
    do {
        struct Mahasiswa *temp = realloc(daftar_mahasiswa, (jumlah_data + 1) * sizeof(struct Mahasiswa));
        if (temp == NULL) {
            printf("Gagal alokasi memori!\n");
            free(daftar_mahasiswa);
            return 1;
        }
        daftar_mahasiswa = temp;

        printf("\nMasukkan NIM : ");
        scanf("%19s", daftar_mahasiswa[jumlah_data].nim);

        printf("Masukkan Nama: ");
        while (getchar() != '\n'); 
        scanf("%49[^\n]", daftar_mahasiswa[jumlah_data].nama);

        jumlah_data++;

        printf("\nMasih ada Data? [Y/T]: ");
        scanf(" %c", &jawaban);

    } while (jawaban == 'Y' || jawaban == 'y');

    printf("%-15s %-20s\n", "NIM", "NAMA");
    printf("======================================\n");

    for (int i = 0; i < jumlah_data; i++) {
        printf("%-15s %-20s\n", daftar_mahasiswa[i].nim, daftar_mahasiswa[i].nama);
    }

    free(daftar_mahasiswa);

    return 0;
}
