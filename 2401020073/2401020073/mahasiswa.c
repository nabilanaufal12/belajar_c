#include "mahasiswa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

static Node *head = NULL; 

static void to_lowercase(const char* input, char* output) {
    int i = 0;
    while (input[i]) {
        output[i] = tolower(input[i]);
        i++;
    }
    output[i] = '\0';
}

int loadData(const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Gagal membuka file");
        return 0;
    }

    char line_buffer[MAX_LINE];
    int dataCount = 0;
    Node* tail = NULL;

    while (fgets(line_buffer, sizeof(line_buffer), fp)) {
        line_buffer[strcspn(line_buffer, "\n")] = 0;

        char* nim = strtok(line_buffer, ",");
        char* nama = strtok(NULL, "\n"); 

        if (nim && nama) {
            Node* newNode = (Node*) malloc(sizeof(Node));
            if (newNode == NULL) {
                fprintf(stderr, "Error: Gagal alokasi memori (malloc)!\n");
                return 0;
            }

            strncpy(newNode->nim, nim, MAX_NIM - 1);
            newNode->nim[MAX_NIM - 1] = '\0';
            
            strncpy(newNode->nama, nama, MAX_NAMA - 1);
            newNode->nama[MAX_NAMA - 1] = '\0';

            to_lowercase(newNode->nim, newNode->nim_lower);
            to_lowercase(newNode->nama, newNode->nama_lower);

            newNode->next = NULL;

            if (head == NULL) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            dataCount++;
        }
    }
    
    fclose(fp);
    printf("Berhasil memuat %d data.\n", dataCount);
    return 1;
}

void printSyntaxError() {
    printf("Syntax error. Should only\n");
    printf("cari xxx yyy\n");
    printf("Where xxx is NIM or NAMA, and yyy is the search value\n");
}

void performSearch(const char* field, const char* value) {
    clock_t start = clock();

    int foundCount = 0;
    char value_lower[MAX_NAMA]; 
    to_lowercase(value, value_lower);

    printf("Result:\n");

    Node* current = head; 
    while (current != NULL) {
        
        char* data_to_search = NULL;

        if (strcmp(field, "NIM") == 0) {
            data_to_search = current->nim_lower;
        } else {
            data_to_search = current->nama_lower;
        }

        if (strstr(data_to_search, value_lower) != NULL) {
            printf("%s\n%s\n", current->nim, current->nama);
            foundCount++;
        }

        current = current->next;
    }

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    if (foundCount == 0) {
        printf("No data found.\n");
    }
    printf("Total time %.3f seconds\n", time_spent);
}

void freeData() {
    Node* current = head;
    Node* temp = NULL;
    
    printf("\nMembersihkan memori...\n");
    
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}