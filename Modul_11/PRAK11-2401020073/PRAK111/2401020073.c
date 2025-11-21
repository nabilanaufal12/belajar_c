#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk menyimpan data Edge (Garis)
struct Edge {
    char src, dest;
    int weight;
};

// Struktur untuk representasi subset (Union-Find)
struct Subset {
    int parent;
    int rank;
};

// Fungsi komparasi untuk qsort (mengurutkan berdasarkan bobot)
int compareEdges(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight - b1->weight;
}

// Fungsi Find (mencari parent dari suatu node)
int find(struct Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Fungsi Union (menggabungkan dua himpunan)
void Union(struct Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int main() {
    struct Edge edges[100]; 
    int edgeCount = 0;
    char inputLine[100];
    char u, v;
    int w;

    printf("Masukan pasangan node untuk Edge beserta bobot:\n");
    
    // Loop input
    while (1) {
        if (fgets(inputLine, sizeof(inputLine), stdin) == NULL || inputLine[0] == '\n') {
            break;
        }
        if (sscanf(inputLine, " %c %c %d", &u, &v, &w) == 3) {
            edges[edgeCount].src = u;
            edges[edgeCount].dest = v;
            edges[edgeCount].weight = w;
            edgeCount++;
        }
    }

    // Sorting
    qsort(edges, edgeCount, sizeof(edges[0]), compareEdges);

    struct Subset* subsets = (struct Subset*)malloc(26 * sizeof(struct Subset));
    for (int i = 0; i < 26; ++i) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    printf("Output Kruskal Minimum Spanning Tree adalah\n");
    
    int e = 0; 
    int i = 0; 
    int totalWeight = 0; // Variabel untuk hitung total

    while (e < 26 - 1 && i < edgeCount) {
        struct Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src - 'a');
        int y = find(subsets, next_edge.dest - 'a');

        if (x != y) {
            printf("%c-%c ", next_edge.src, next_edge.dest); // Print Edge
            totalWeight += next_edge.weight; // Tambahkan bobot
            Union(subsets, x, y);
            e++;
        }
    }
    printf("\n");
    
    // Tambahan: Tampilkan Total Bobot untuk validasi
    printf("Total Bobot MST: %d\n", totalWeight);

    return 0;
}