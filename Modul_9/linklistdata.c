#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "helper.h"
#include "linklistdata.h"

penduduk *start, *current, *startEntry, *currentEntry ;

penduduk *createNewLink() {
    penduduk *newNode = (penduduk*) malloc(sizeof(penduduk));
    if (newNode == NULL) {
        printf("Gagal alokasi memori untuk node baru!\n");
        return NULL;
    }
    
    newNode->nama = (char*) malloc(101 * sizeof(char)); 
    if (newNode->nama == NULL) {
        printf("Gagal alokasi memori untuk nama!\n");
        free(newNode); // bebaskan node yang gagal dibuat
        return NULL;
    }
    
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void addNewEntry(penduduk *newEntry) {
    if (startEntry == NULL) {
        // jika ini adalah data baru pertama
        startEntry = newEntry;
        currentEntry = newEntry;
    } else {
        // tambahkan ke akhir list data baru
        currentEntry->next = newEntry;
        newEntry->prev = currentEntry;
        currentEntry = newEntry;
    }
}

void flushNewEntry(FILE *f) {
    if (startEntry == NULL) {
        // tidak ada data baru untuk ditulis
        return;
    }
    
    penduduk *temp = startEntry;
    
    // pindahkan pointer file ke akhir untuk 'append'
    fseek(f, 0, SEEK_END);
    
    while (temp != NULL) {
        // tulis data ke file dalam format CSV
        fprintf(f, "%d;%s;%c\n", temp->nik, temp->nama, temp->gender);
        
        // pindahkan data dari list 'startEntry' ke list 'start' (main)
        if (start == NULL) {
            start = temp;
            current = temp;
        } else {
            current->next = temp;
            temp->prev = current;
            current = temp;
        }
        
        penduduk *next = temp->next;
        startEntry = next; // pindahkan head list data baru
        temp = next;
    }
    
    // reset list data baru
    startEntry = NULL;
    currentEntry = NULL;
}

void loadData(FILE *f) {
    start = NULL;
    current = NULL;
    penduduk *tempNode;
    
    // pindahkan pointer file ke awal
    rewind(f);

    while (1) {
        tempNode = createNewLink();
        if (tempNode == NULL) break;

        // gunakan format robust dari Experimen 4 
        int result = fscanf(f, "%d;%100[^;];%c\n", &tempNode->nik, tempNode->nama, &tempNode->gender);
        
        if (result != 3) {
            // jika gagal membaca atau sudah di akhir file
            free(tempNode->nama); // free alokasi yang tidak terpakai
            free(tempNode);
            break;
        }
        
        // tambahkan node ke list 'start'
        if (start == NULL) {
            start = tempNode;
            current = tempNode;
        } else {
            current->next = tempNode;
            tempNode->prev = current;
            current = tempNode;
        }
    }
}

// ada beberapa perbaikan di fungsi cari, karena program sebelumnya tidak berjalan sesuai harapan
int cari() {
    char keywd[10], nilai[100], *found = NULL;
    printf("Masukan keyword (NIK/NAMA/GENDER) spasi nilai_yang_dicari. Contoh NIK 2010\n");
    scanf("%s %[^\n]", keywd, nilai); // perbaikan scanf untuk nilai dengan spasi
    fflush(stdin);
    int countFound = 0;
    penduduk *tmp;
    if (start == NULL) {
        printf("Error data missing\n");
        return 1;
    }
    tmp = start;
    do {
        if (strcmp(keywd, "NIK") == 0) {
            char nik_str[20];
            sprintf(nik_str, "%d", tmp->nik); // konversi NIK int ke string
            found = strstr(nik_str, nilai);
        } else if (strcmp(keywd, "NAMA") == 0) {
            found = strstr(tmp->nama, nilai);
        } else if (strcmp(keywd, "GENDER") == 0) {
            // perlu perbandingan char, bukan strstr
            if (nilai[0] == tmp->gender) {
                found = nilai; // set found jika cocok
            } else {
                found = NULL;
            }
        } else {
            printf("\nKEYWORD ga dikenal.\nKeyword hanya NIK atau NAMA atau GENDER saja\n\a");
            break;
        }
        if (found) {
            countFound++;
            printf("\n");
            printf("NIK\t:%d\n", tmp->nik);
            printf("Nama\t:%s\n", tmp->nama);
            printf("Gender\t:%c\n", tmp->gender);
            printf("\n");
        }
    } while ((tmp = tmp->next) != NULL);
    printf("%d data ditemukan.\n", countFound);
    return lanjut(); // lanjut() dari helper.h
}