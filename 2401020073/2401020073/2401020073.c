#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mahasiswa.h" 

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Penggunaan: %s <filedata.csv>\n", argv[0]);
        return 1;
    }

    if (!loadData(argv[1])) {
        fprintf(stderr, "Gagal memuat data dari file %s.\n", argv[1]);
        return 1;
    }

    char line[MAX_LINE];
    char cmd[MAX_LINE], field[MAX_LINE], value[MAX_LINE];

    while (1) {
        printf("Your command: ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, "berhenti") == 0) {
            break;
        }

        cmd[0] = '\0'; field[0] = '\0'; value[0] = '\0';
        
        int count = sscanf(line, "%s %s %99[^\n]", cmd, field, value);

        if (count == 3 && strcmp(cmd, "cari") == 0) {
            if (strcmp(field, "NIM") == 0 || strcmp(field, "NAMA") == 0) {
                performSearch(field, value);
            } else {
                printSyntaxError();
            }
        } else {
            printSyntaxError();
        }
    }
    
    freeData(); 
    
    return 0;
}