#ifndef MAHASISWA_H
#define MAHASISWA_H

#define MAX_NIM 20
#define MAX_NAMA 100
#define MAX_LINE 256

typedef struct Node {
    char nim[MAX_NIM];
    char nama[MAX_NAMA];
    char nim_lower[MAX_NIM];
    char nama_lower[MAX_NAMA];

    struct Node* next;
} Node;

int loadData(const char* filename);
void printSyntaxError();
void performSearch(const char* field, const char* value);
void freeData();

#endif