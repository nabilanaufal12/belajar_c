#include <stdio.h>

// --- Deklarasi Fungsi (Function Prototypes) ---
// Ini adalah praktik yang baik, memberitahu compiler fungsi apa saja yang ada.
int faktorial_iterasi(int n);
int faktorial_rekursif(int n);


// --- Fungsi Utama (Program Dimulai Dari Sini) ---
int main() {
    // Angka yang ingin kita hitung faktorialnya.
    // Coba ganti-ganti nilainya (misal: 4, 5, 7) untuk bereksperimen.
    int angka = 5;

    printf("Menghitung faktorial dari %d\n\n", angka);

    // --- Memanggil Fungsi Iterasi ---
    int hasil_iterasi = faktorial_iterasi(angka);
    printf("Hasil dengan cara Iterasi (loop): %d\n", hasil_iterasi);

    // --- Memanggil Fungsi Rekursif ---
    int hasil_rekursif = faktorial_rekursif(angka);
    printf("Hasil dengan cara Rekursif: %d\n", hasil_rekursif);

    return 0; // Program selesai dengan sukses
}


/**
 * Menghitung faktorial menggunakan pendekatan Iterasi (for loop).
 * Logikanya lurus ke depan, menghitung dari 1 sampai n.
 */
int faktorial_iterasi(int n) {
    int hasil = 1; // Mulai dari 1 karena perkalian
    
    // Loop dari 1 sampai n
    for (int i = 1; i <= n; i++) {
        hasil = hasil * i;
    }
    
    return hasil;
}


/**
 * Menghitung faktorial menggunakan pendekatan Rekursif.
 * Fungsi ini memanggil dirinya sendiri dengan nilai yang lebih kecil.
 */
int faktorial_rekursif(int n) {
    // BASE CASE: Kondisi berhenti.
    // Jika n adalah 1 atau 0, faktorialnya adalah 1.
    // Ini mencegah fungsi memanggil dirinya sendiri tanpa henti.
    if (n <= 1) {
        return 1;
    }
    // RECURSIVE STEP: Langkah rekursif.
    // Fungsi memanggil dirinya sendiri dengan masalah yang lebih kecil (n - 1).
    else {
        return n * faktorial_rekursif(n - 1);
    }
}
