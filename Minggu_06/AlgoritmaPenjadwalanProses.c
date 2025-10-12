#include <stdio.h>      // Library standar untuk input-output (printf, scanf)

// ======================
// Struktur data untuk menyimpan informasi proses
// ======================
struct Process {
    int pid;                // ID proses (misal P1, P2, dst.)
    int arrival;            // Waktu kedatangan (Arrival Time)
    int burst;              // Lama eksekusi proses (Burst Time)
    int remaining;          // Sisa waktu eksekusi (digunakan di algoritma Round Robin)
    int start_time;         // Waktu mulai dijalankan oleh CPU
    int completion_time;    // Waktu proses selesai dieksekusi
    int turnaround_time;    // Total waktu dari datang sampai selesai (CT - AT)
    int waiting_time;       // Waktu menunggu di ready queue (TAT - BT)
    int response_time;      // Waktu dari datang sampai pertama kali dijalankan (ST - AT)
    int has_started;        // Penanda apakah proses sudah mulai dijalankan (0 = belum, 1 = sudah)
};

// ======================
// Struktur data untuk Gantt Chart (log urutan eksekusi)
// ======================
struct GanttLog {
    int pid;        // ID proses
    int end_time;   // Waktu proses ini selesai eksekusi (akhir segmen Gantt Chart)
};

// ======================
// Fungsi untuk algoritma FCFS (First Come, First Served)
// ======================
void fcfs() {
    printf("\nFirst-Come, First-Served (FCFS)\n");

    int n;
    printf("Masukkan jumlah proses: ");
    scanf("%d", &n);    // Input jumlah proses dari user

    struct Process processes[n];  // Array untuk menyimpan semua proses
    struct GanttLog gantt[n];     // Array untuk menyimpan urutan Gantt Chart

    // ======================
    // Input data tiap proses
    // ======================
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1; // Set ID proses dimulai dari 1
        printf("Masukkan waktu kedatangan proses P%d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival);
        printf("Masukkan waktu burst proses P%d: ", processes[i].pid);
        scanf("%d", &processes[i].burst);
    }

    // ======================
    // Mengurutkan proses berdasarkan waktu kedatangan (arrival time)
    // ======================
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival > processes[j + 1].arrival) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // ======================
    // Variabel untuk perhitungan waktu total dan rata-rata
    // ======================
    int current_time = 0;                      // Menyimpan waktu CPU saat ini
    float total_waiting = 0, total_turnaround = 0, total_response = 0;

    // ======================
    // Proses tiap proses secara berurutan
    // ======================
    for (int i = 0; i < n; i++) {
        // Jika CPU idle dan belum ada proses datang, loncat ke waktu kedatangan proses berikutnya
        if (current_time < processes[i].arrival) {
            current_time = processes[i].arrival;
        }

        // Waktu mulai proses (ketika CPU mulai mengeksekusi)
        processes[i].start_time = current_time;

        // Hitung response time = waktu mulai - waktu datang
        processes[i].response_time = processes[i].start_time - processes[i].arrival;

        // Hitung completion time = waktu sekarang + burst
        processes[i].completion_time = current_time + processes[i].burst;

        // Hitung turnaround time = selesai - datang
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival;

        // Hitung waiting time = turnaround - burst
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst;

        // Tambahkan ke total untuk rata-rata
        total_waiting += processes[i].waiting_time;
        total_turnaround += processes[i].turnaround_time;
        total_response += processes[i].response_time;

        // Simpan ke Gantt Chart (urutan eksekusi)
        gantt[i].pid = processes[i].pid;
        gantt[i].end_time = processes[i].completion_time;

        // Update waktu CPU saat ini
        current_time = processes[i].completion_time;
    }

    // ======================
    // Menampilkan Gantt Chart FCFS
    // ======================
    printf("\nGANTT CHART\n");
    int last_time = 0;
    for(int i = 0; i < n; i++) { printf("| P%d\t", gantt[i].pid); }
    printf("|\n");
    for(int i = 0; i < n; i++) { printf("%d\t", last_time); last_time = gantt[i].end_time; }
    printf("%d\n", last_time);

    // ======================
    // Menampilkan hasil per proses
    // ======================
    printf("\nPROSES\t| AT\t| BT\t| ST\t| CT\t| TAT\t| WT\t| RT\n");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t| %d\t| %d\t| %d\t| %d\t| %d\t| %d\t| %d\n",
               processes[i].pid, processes[i].arrival, processes[i].burst,
               processes[i].start_time, processes[i].completion_time,
               processes[i].turnaround_time, processes[i].waiting_time,
               processes[i].response_time);
    }

    // ======================
    // Menampilkan rata-rata hasil
    // ======================
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);
    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Response Time: %.2f\n", total_response / n);
}

// ======================
// Fungsi untuk algoritma Round Robin (Queue-Based)
// ======================
void round_robin() {
    printf("\nRound Robin (Queue-Based)\n");

    int n, quantum;
    printf("Masukkan jumlah proses: ");
    scanf("%d", &n);

    struct Process processes[n];
    struct GanttLog gantt[200];     // Karena Round Robin bisa punya banyak segmen di Gantt chart
    int gantt_count = 0;

    // Input data proses
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Masukkan waktu kedatangan proses P%d: ", processes[i].pid);
        scanf("%d", &processes[i].arrival);
        printf("Masukkan waktu burst proses P%d: ", processes[i].pid);
        scanf("%d", &processes[i].burst);
        processes[i].remaining = processes[i].burst; // Inisialisasi sisa waktu
        processes[i].has_started = 0;               // Belum pernah dijalankan
        processes[i].start_time = -1;               // Belum mulai
    }

    // Input quantum
    printf("Masukkan quantum time: ");
    scanf("%d", &quantum);

    // Urutkan berdasarkan waktu kedatangan
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival > processes[j + 1].arrival) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    // Inisialisasi variabel RR
    int current_time = 0;
    int completed = 0;
    int queue[200];             // Queue untuk proses
    int front = 0, rear = 0;    // Penanda depan & belakang antrian
    int in_queue[n];            // Cek apakah proses sudah di antrian
    for (int i = 0; i < n; i++) in_queue[i] = 0;

    float total_waiting = 0, total_turnaround = 0, total_response = 0;

    // Masukkan proses pertama
    queue[rear++] = 0;
    in_queue[0] = 1;
    current_time = processes[0].arrival;

    // ======================
    // Proses utama Round Robin
    // ======================
    while (completed < n) {
        // Jika queue kosong, tambahkan proses berikutnya yang datang
        if (front == rear) {
            for (int i = 0; i < n; i++) {
                if (processes[i].remaining > 0) {
                    current_time = processes[i].arrival;
                    queue[rear++] = i;
                    in_queue[i] = 1;
                    break;
                }
            }
        }

        int idx = queue[front++];  // Ambil proses dari depan queue

        // Jika proses baru pertama kali dijalankan
        if (processes[idx].has_started == 0) {
            processes[idx].response_time = current_time - processes[idx].arrival;
            processes[idx].start_time = current_time;
            processes[idx].has_started = 1;
        }

        // Tentukan waktu eksekusi (quantum atau sisa burst)
        int time_slice = (processes[idx].remaining > quantum) ? quantum : processes[idx].remaining;
        current_time += time_slice;
        processes[idx].remaining -= time_slice;

        // Catat ke Gantt chart
        gantt[gantt_count].pid = processes[idx].pid;
        gantt[gantt_count].end_time = current_time;
        gantt_count++;

        // Tambahkan proses lain yang sudah datang
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= current_time && processes[i].remaining > 0 && in_queue[i] == 0) {
                queue[rear++] = i;
                in_queue[i] = 1;
            }
        }

        // Jika proses belum selesai, masukkan lagi ke belakang queue
        if (processes[idx].remaining > 0) {
            queue[rear++] = idx;
        } else {
            // Jika selesai, hitung waktunya
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst;

            total_waiting += processes[idx].waiting_time;
            total_turnaround += processes[idx].turnaround_time;
            total_response += processes[idx].response_time;
            completed++;
        }
    }

    // ======================
    // Menampilkan hasil Round Robin
    // ======================
    printf("\nGANTT CHART\n");
    int last_time = 0;
    for (int i = 0; i < gantt_count; i++) printf("| P%d\t", gantt[i].pid);
    printf("|\n");
    for (int i = 0; i < gantt_count; i++) { printf("%d\t", last_time); last_time = gantt[i].end_time; }
    printf("%d\n", last_time);

    // Menampilkan tabel hasil
    printf("\nPROSES\t| AT\t| BT\t| Q\t| ST\t| CT\t| TAT\t| WT\t| RT\n");
    printf("---------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t| %d\t| %d\t| %d\t| %d\t| %d\t| %d\t| %d\t| %d\n",
               processes[i].pid,
               processes[i].arrival,
               processes[i].burst,
               quantum,
               processes[i].start_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time,
               processes[i].response_time);
    }

    // Menampilkan rata-rata hasil
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);
    printf("Average Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Response Time: %.2f\n", total_response / n);
}

// ======================
// Fungsi utama (Main Menu)
// ======================
int main() {
    int choice;
    do {
        // Menu pilihan
        printf("\nSIMULASI ALGORITMA PENJADWALAN\n");
        printf("1. First-Come, First-Served (FCFS)\n");
        printf("2. Round Robin\n");
        printf("3. Keluar\n");
        printf("Pilihan Anda (1-3): ");
        scanf("%d", &choice);

        // Menjalankan pilihan user
        switch (choice) {
            case 1:
                fcfs(); // Jalankan algoritma FCFS
                break;
            case 2:
                round_robin(); // Jalankan algoritma Round Robin
                break;
            case 3:
                printf("Program selesai. Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid! Silakan coba lagi.\n");
        }
    } while (choice != 3); // Ulangi selama belum pilih keluar

    return 0;
}

