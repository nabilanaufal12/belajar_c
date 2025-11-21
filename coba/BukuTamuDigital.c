#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// definisi struktur data (linked list)
typedef struct Node {
    char nik[20];
    char nama[50];
    char tujuan[100];
    char tanggal[20];
    char jam[10];
    struct Node *next;
} Tamu;

// pointer global
Tamu *head = NULL;
Tamu *tail = NULL;
int jumlahData = 0;

// fungsi utilitas
// mengambil waktu saat ini dari sistem komputer
void ambilWaktuSistem(char *bufferTanggal, char *bufferJam) {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    strftime(bufferTanggal, 20, "%d-%m-%Y", timeinfo);  // DD-MM-YYYY
    strftime(bufferJam, 10, "%H:%M:%S", timeinfo);      // HH:MM:SS
}

// core function (fungsi utama)
// menambah data baru ke akhir linked list (insert last)
void inputData(char *nik, char *nama, char *tujuan) {
    Tamu *baru = (Tamu*) malloc(sizeof(Tamu));
    
    if (baru == NULL) {
        printf("Error: Memori penuh!\n");
        return;
    }

    // copy data ke node baru
    strcpy(baru->nik, nik);
    strcpy(baru->nama, nama);
    strcpy(baru->tujuan, tujuan);
    ambilWaktuSistem(baru->tanggal, baru->jam);
    baru->next = NULL;

    // menyambungkan ke rantai linked list
    if (head == NULL) {
        head = baru;
        tail = baru;
    } else {
        tail->next = baru;
        tail = baru;
    }
    jumlahData++;
}

// menampilkan menu inputan user
void menuInput() {
    char nik[20], nama[50], tujuan[100];
    printf("\nINPUT DATA TAMU");
    printf("\n------------------------------\n");
    printf("Masukkan NIK    : ");
    scanf(" %[^\n]", nik);
    printf("Masukkan Nama   : ");
    scanf(" %[^\n]", nama);
    printf("Masukkan Tujuan : ");
    scanf(" %[^\n]", tujuan);

    inputData(nik, nama, tujuan);
    printf("Data berhasil disimpan!\n");
}

// menampilkan seluruh data (traversal)
void tampilkanSemua() {
    if (head == NULL) {
        printf("\nBuku tamu kosong.\n");
        return;
    }

    Tamu *bantu = head;
    printf("\n%-15s %-25s %-15s %-10s\n", "NIK", "NAMA", "TANGGAL", "JAM");
    printf("------------------------------------------------------------------\n");
    
    int count = 0;
    while (bantu != NULL) {
        // batasi tampilan 20 data saja agar layar tidak penuh
        if (count < 20) {
            printf("%-15s %-25s %-15s %-10s\n", 
                   bantu->nik, bantu->nama, bantu->tanggal, bantu->jam);
        }
        bantu = bantu->next;
        count++;
    }
    if (count > 20) printf("... (Total %d data tersimpan. Sebagian disembunyikan) ...\n", count);
}

// pencarian data (partial search)
void cariBerdasarkanNama() {
    if (head == NULL) {
        printf("\nData kosong.\n");
        return;
    }

    char keyword[50];
    int ditemukan = 0;
    printf("\nMasukkan Nama yang dicari: ");
    scanf(" %[^\n]", keyword);

    printf("\nHASIL PENCARIAN");
    printf("\n------------------------------\n");
    
    Tamu *bantu = head;
    while (bantu != NULL) {
        // strstr mengecek apakah keyword ada di dalam nama
        if (strstr(bantu->nama, keyword) != NULL) {
            printf("* %s (NIK: %s) -> Tujuan: %s [%s %s]\n", 
                   bantu->nama, bantu->nik, bantu->tujuan, bantu->tanggal, bantu->jam);
            ditemukan = 1;
        }
        bantu = bantu->next;
    }

    if (!ditemukan) printf("Data tidak ditemukan.\n");
}

// fungsi manajemen file CSV
void simpanKeCSV() {
    FILE *file = fopen("data_tamu.csv", "w");
    if (file == NULL) {
        printf("Error: Gagal menyimpan file!\n");
        return;
    }

    // header CSV
    fprintf(file, "NIK,Nama,Tujuan,Tanggal,Jam\n");

    Tamu *bantu = head;
    while (bantu != NULL) {
        fprintf(file, "%s,%s,%s,%s,%s\n", 
                bantu->nik, bantu->nama, bantu->tujuan, bantu->tanggal, bantu->jam);
        bantu = bantu->next;
    }

    fclose(file);
    printf("Data berhasil diexport ke 'data_tamu.csv'!\n");
}

void bacaDariCSV() {
    FILE *file = fopen("data_tamu.csv", "r");
    if (file == NULL) return; // file tidak ada, abaikan

    char buffer[1024]; // buffer diperbesar untuk keamanan
    char nik[20], nama[50], tujuan[100];

    // lewati baris header
    fgets(buffer, sizeof(buffer), file);

    // baca baris per baris
    while (fgets(buffer, sizeof(buffer), file)) {
        // parsing CSV
        char *token = strtok(buffer, ",");
        if(token != NULL) strcpy(nik, token);
        
        token = strtok(NULL, ",");
        if(token != NULL) strcpy(nama, token);

        token = strtok(NULL, ",");
        if(token != NULL) {
            strcpy(tujuan, token);
            // bersihkan newline di akhir string tujuan jika ada
            tujuan[strcspn(tujuan, "\n")] = 0;
        }

        inputData(nik, nama, tujuan); 
    }

    fclose(file);
    printf("Data lama berhasil dimuat dari file CSV.\n");
}

// fungsi benchmark untuk analisis performa
void hapusSemua() {
    Tamu *bantu = head;
    while (head != NULL) {
        bantu = head;
        head = head->next;
        free(bantu);
    }
    tail = NULL;
    jumlahData = 0;
}

void generateDummyData(int jumlah) {
    hapusSemua(); // reset dulu agar bersih
    printf("Sedang membuat %d data dummy... ", jumlah);
    
    char tempNama[50];
    for (int i = 0; i < jumlah; i++) {
        sprintf(tempNama, "Pengunjung %d", i);
        inputData("12345", tempNama, "Uji Coba");
    }
    printf("Selesai!\n");
}

void jalankanBenchmark() {
    clock_t start, end;
    double cpu_time_used;
    char keyword[] = "Pengunjung 999999"; // worst case (data tidak ada/di akhir)
    
    printf("Memulai pengukuran waktu pencarian...\n");
    start = clock();

    // loop pencarian dilakukan berulang agar terdeteksi CPU
    int pengulangan = 1000; 
    int dummyHit = 0;
    
    for(int k=0; k<pengulangan; k++) {
        Tamu *bantu = head;
        while (bantu != NULL) {
            if (strstr(bantu->nama, keyword) != NULL) {
                dummyHit++;
            }
            bantu = bantu->next;
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nHASIL BENCHMARK (LINKED LIST)");
    printf("\n==============================\n");
    printf("Jumlah Node     : %d\n", jumlahData);
    printf("Waktu Eksekusi  : %f detik (1000x loop)\n", cpu_time_used);
    printf("Kesimpulan      : O(N) - Linear Time Complexity.\n");
}

// main program
int main() {
    int pilihan, n;

    // load data otomatis saat program jalan
    bacaDariCSV(); 

    do {
        printf("\nBUKU TAMU DIGITAL (CBM CASE 1)");
        printf("\n==============================\n");
        printf("1. Input Data Tamu\n");
        printf("2. Tampilkan Semua Data\n");
        printf("3. Cari Data (Partial Search)\n");
        printf("4. Simpan ke CSV (Export)\n");
        printf("5. Benchmark Grafik\n");
        printf("6. Keluar & Simpan Otomatis\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch(pilihan) {
            case 1: menuInput(); break;
            case 2: tampilkanSemua(); break;
            case 3: cariBerdasarkanNama(); break;
            case 4: simpanKeCSV(); break;
            case 5: 
                printf("Masukkan jumlah data dummy: "); 
                scanf("%d", &n);
                generateDummyData(n);
                jalankanBenchmark();
                break;
            case 6: 
                simpanKeCSV(); // autosave
                hapusSemua(); 
                printf("Program Selesai.\n");
                break;
            default: printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 6);
    return 0;
}