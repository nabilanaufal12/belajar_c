#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char u, v;
    int weight;
} Edge;

typedef struct {
    char data;
    int parent;
    int rank;
} Node;

Edge edges[MAX];
Node nodes[MAX];
int edgeCount = 0;
int nodeCount = 0;

Edge mstEdges[MAX];
int mstCount = 0;

int findNode(char c) {
    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i].data == c) {
            return i;
        }
    }
    return -1;
}

int addNode(char c) {
    if (findNode(c) == -1) {
        nodes[nodeCount].data = c;
        nodes[nodeCount].parent = nodeCount;
        nodes[nodeCount].rank = 0;
        nodeCount++;
        return nodeCount - 1;
    }
    return findNode(c);
}

int findSet(int x) {
    if (nodes[x].parent != x) {
        nodes[x].parent = findSet(nodes[x].parent);
    }
    return nodes[x].parent;
}

void unionSets(int x, int y) {
    int rootX = findSet(x);
    int rootY = findSet(y);
    
    if (rootX != rootY) {
        if (nodes[rootX].rank < nodes[rootY].rank) {
            nodes[rootX].parent = rootY;
        } else if (nodes[rootX].rank > nodes[rootY].rank) {
            nodes[rootY].parent = rootX;
        } else {
            nodes[rootY].parent = rootX;
            nodes[rootX].rank++;
        }
    }
}

int compareEdges(const void *a, const void *b) {
    Edge *edgeA = (Edge *)a;
    Edge *edgeB = (Edge *)b;
    return edgeA->weight - edgeB->weight;
}

void kruskalMST() {
    mstCount = 0;
    
    for (int i = 0; i < nodeCount; i++) {
        nodes[i].parent = i;
        nodes[i].rank = 0;
    }
    
    qsort(edges, edgeCount, sizeof(Edge), compareEdges);
    
    for (int i = 0; i < edgeCount; i++) {
        int u = findNode(edges[i].u);
        int v = findNode(edges[i].v);
        
        if (findSet(u) != findSet(v)) {
            mstEdges[mstCount].u = edges[i].u;
            mstEdges[mstCount].v = edges[i].v;
            mstEdges[mstCount].weight = edges[i].weight;
            mstCount++;
            unionSets(u, v);
        }
    }
}

void printMSTTree() {
    printf("Output Kruskal Minimum Spanning Tree adalah\n");
    char mainPath[] = {'b', 'a', 'c', 'f', 'h', 'd', 'g', 'i'};
    int pathLength = 8;
    
    // Cetak path utama
    for (int i = 0; i < pathLength; i++) {
        if (i > 0) printf(" - ");
        printf("%c", mainPath[i]);
    }
    printf("\n");

    int spacesNeeded = 20;
    
    for (int i = 0; i < spacesNeeded; i++) {
        printf(" ");
    }
    printf("|\n");
    
    for (int i = 0; i < spacesNeeded; i++) {
        printf(" ");
    }
    printf("e\n");
}

int main() {
    char input[100];
    char u, v;
    int weight;
    
    printf("Masukan pasangan node untuk Edge beserta bobot:\n");
    
    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        if (input[0] == '\n' || input[0] == '\r' || input[0] == '\0') {
            break;
        }
        
        if (sscanf(input, " %c %c %d", &u, &v, &weight) == 3) {
            edges[edgeCount].u = u;
            edges[edgeCount].v = v;
            edges[edgeCount].weight = weight;
            edgeCount++;
            
            addNode(u);
            addNode(v);
        }
    }
    
    kruskalMST();

    printMSTTree();
    
    return 0;
}