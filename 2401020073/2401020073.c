#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_NIM 30
#define MAX_NAMA 150
#define INITIAL_CAPACITY 100
#define MAX_CMD_LINE 512

typedef struct {
    char nim[MAX_NIM];
    char nama[MAX_NAMA];
    char nim_lower[MAX_NIM];  
    char nama_lower[MAX_NAMA];
} Mahasiswa;

Mahasiswa *data = NULL;
size_t totalData = 0;
size_t capacity = 0;

void to_lowercase(const char* input, char* output);
void trim_newline(char* str);
int loadData(const char* filename);
void performSearch(const char* field, const char* value);
void printSyntaxError();

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Command error. You need data file as arguments\n");
        return 0;
    }

    if (!loadData(argv[1])) {
        fprintf(stderr, "Error: Gagal membaca file %s\n", argv[1]);
        return 1;
    }

    char line[MAX_CMD_LINE];
    char cmd[50], field[50], value[256];

    while (1) {
        printf("Your command: ");
        
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        
        trim_newline(line);

        if (strlen(line) == 0) continue;

        if (strcmp(line, "berhenti") == 0) {
            break; 
        }

        cmd[0] = '\0'; field[0] = '\0'; value[0] = '\0';

        int args = sscanf(line, "%s %s %255[^\n]", cmd, field, value);

        if (args == 3 && strcmp(cmd, "cari") == 0) {
            if (strcmp(field, "NIM") == 0 || strcmp(field, "NAMA") == 0) {
                performSearch(field, value);
            } else {
                printSyntaxError();
            }
        } else {
            printSyntaxError();
        }
    }

    free(data);
    return 0;
}

void to_lowercase(const char* input, char* output) {
    int i = 0;
    while (input[i]) {
        output[i] = tolower((unsigned char)input[i]);
        i++;
    }
    output[i] = '\0';
}

void trim_newline(char* str) {
    size_t len = strlen(str);
    while (len > 0 && (str[len - 1] == '\n' || str[len - 1] == '\r')) {
        str[len - 1] = '\0';
        len--;
    }
}

int loadData(const char* filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;

    capacity = INITIAL_CAPACITY;
    data = (Mahasiswa*) malloc(capacity * sizeof(Mahasiswa));
    if (!data) {
        perror("Gagal alokasi memori");
        fclose(fp);
        return 0;
    }

    char buffer[1024];
    
    while (fgets(buffer, sizeof(buffer), fp)) {
        trim_newline(buffer);

        char *comma_pos = strchr(buffer, ',');
        if (comma_pos != NULL) {
            *comma_pos = '\0';
            char *nim_str = buffer;
            char *nama_str = comma_pos + 1;

            if (totalData >= capacity) {
                capacity *= 2;
                Mahasiswa *temp = (Mahasiswa*) realloc(data, capacity * sizeof(Mahasiswa));
                if (!temp) {
                    perror("Gagal realloc memori");
                    free(data);
                    fclose(fp);
                    return 0;
                }
                data = temp;
            }

            strncpy(data[totalData].nim, nim_str, MAX_NIM - 1);
            data[totalData].nim[MAX_NIM - 1] = '\0';
            
            strncpy(data[totalData].nama, nama_str, MAX_NAMA - 1);
            data[totalData].nama[MAX_NAMA - 1] = '\0';

            to_lowercase(data[totalData].nim, data[totalData].nim_lower);
            to_lowercase(data[totalData].nama, data[totalData].nama_lower);

            totalData++;
        }
    }

    fclose(fp);
    return 1;
}

void printSyntaxError() {
    printf("Syntax error. Should only\n");
    printf("cari xxx yyy\n");
    printf("Where xxx is NIM or NAMA, and yyy is the search value\n");
}

void performSearch(const char* field, const char* value) {
    clock_t start = clock();
    
    char value_lower[MAX_NAMA];
    to_lowercase(value, value_lower);

    int found = 0;
    printf("Result:\n");

    for (size_t i = 0; i < totalData; i++) {
        char *target = NULL;
        
        if (strcmp(field, "NIM") == 0) {
            target = data[i].nim_lower;
        } else {
            target = data[i].nama_lower;
        }

        if (strstr(target, value_lower) != NULL) {
            printf("%s\n", data[i].nim);
            printf("%s\n", data[i].nama);
            found++;
        }
    }

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Total time %.3f seconds\n", time_taken);
}