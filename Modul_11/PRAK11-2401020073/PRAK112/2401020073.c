#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

typedef struct {
    int vertices[MAX];
    int adjacency[MAX][MAX];
    int vertexCount;
} Graph;

Graph graph;
int visited[MAX];
int distance[MAX];
int previous[MAX];

int findVertexIndex(char c) {
    for (int i = 0; i < graph.vertexCount; i++) {
        if (graph.vertices[i] == c) {
            return i;
        }
    }
    return -1;
}

int addVertex(char c) {
    int idx = findVertexIndex(c);
    if (idx == -1) {
        graph.vertices[graph.vertexCount] = c;
        return graph.vertexCount++;
    }
    return idx;
}

void initializeGraph() {
    graph.vertexCount = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            graph.adjacency[i][j] = INF;
        }
    }
    for (int i = 0; i < MAX; i++) {
        graph.adjacency[i][i] = 0;
    }
}

int getMinDistanceVertex() {
    int minDistance = INF;
    int minVertex = -1;
    
    for (int i = 0; i < graph.vertexCount; i++) {
        if (!visited[i] && distance[i] < minDistance) {
            minDistance = distance[i];
            minVertex = i;
        }
    }
    return minVertex;
}

void dijkstra(int start, int end) {
    for (int i = 0; i < graph.vertexCount; i++) {
        distance[i] = INF;
        visited[i] = 0;
        previous[i] = -1;
    }
    
    distance[start] = 0;
    
    for (int count = 0; count < graph.vertexCount - 1; count++) {
        int u = getMinDistanceVertex();
        if (u == -1) break;
        
        visited[u] = 1;
        
        for (int v = 0; v < graph.vertexCount; v++) {
            if (!visited[v] && graph.adjacency[u][v] != INF && 
                distance[u] != INF && 
                distance[u] + graph.adjacency[u][v] < distance[v]) {
                distance[v] = distance[u] + graph.adjacency[u][v];
                previous[v] = u;
            }
        }
    }
}

void printPath(int end) {
    if (previous[end] == -1) {
        printf("%c", graph.vertices[end]);
        return;
    }
    printPath(previous[end]);
    printf(" - %c", graph.vertices[end]);
}

int main() {
    char input[100];
    char u, v;
    int weight;
    char startChar, endChar;
    
    initializeGraph();
    
    printf("Masukan pasangan node untuk Edge beserta bobot:\n");
    
    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        if (input[0] == '\n' || input[0] == '\r' || input[0] == '\0') {
            break;
        }
        
        if (sscanf(input, " %c %c %d", &u, &v, &weight) == 3) {
            int idxU = addVertex(u);
            int idxV = addVertex(v);
            // Cegah duplikasi edge dengan memilih bobot terkecil
            if (graph.adjacency[idxU][idxV] > weight) {
                graph.adjacency[idxU][idxV] = weight;
                graph.adjacency[idxV][idxU] = weight;
            }
        }
    }
    
    printf("Masukan node sumber dan node tujuan:\n");
    if (scanf(" %c %c", &startChar, &endChar) == 2) {
        // Flush stdin agar input tidak tertinggal
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        int start = findVertexIndex(startChar);
        int end = findVertexIndex(endChar);
        
        if (start != -1 && end != -1) {
            dijkstra(start, end);
            
            printf("Output Dijkstra Shortest Path adalah\n");
            printPath(end);
            printf("\nTotal : %d\n", distance[end]);
        } else {
            printf("Node tidak ditemukan!\n");
        }
    }
    
    return 0;
}