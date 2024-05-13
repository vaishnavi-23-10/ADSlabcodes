#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INFINITY 99  // Your chosen representation for infinity

// Function to find the vertex with the minimum key value
int findMinKeyVertex(int key[], bool mstSet[], int n) {
    int minKey = __INT_MAX__, minIndex;

    for (int v = 0; v < n; v++) {
        if (!mstSet[v] && key[v] < minKey) {
            minKey = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

// Function to print the MST
void printMST(int parent[], int graph[MAX_VERTICES][MAX_VERTICES], int n) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d: \t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}

void primMST(int graph[MAX_VERTICES][MAX_VERTICES], int n) {
    int parent[MAX_VERTICES];
    int key[MAX_VERTICES];
    bool mstSet[MAX_VERTICES];

    for (int i = 0; i < n; i++) {
        key[i] = INFINITY;  // Using your chosen infinity value
        mstSet[i] = false;
    }
    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = findMinKeyVertex(key, mstSet, n);   // Pick the minimum key vertex

        mstSet[u] = true;   // Include the picked vertex in MST

        // Update key values and parent index of the adjacent vertices of the picked vertex
        for (int v = 0; v < n; v++) {
            if (graph[u][v]!= 0 && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    // Print the constructed MST
    printMST(parent, graph, n);
}

int main() {
    int n;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    int graph[MAX_VERTICES][MAX_VERTICES];
    printf("Enter the adjacency matrix with distance:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
    primMST(graph, n);
    return 0;
}
