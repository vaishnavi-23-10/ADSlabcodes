#include <stdio.h>
#include <stdbool.h>

#define MAX 100

// Queue for BFS
int queue[MAX];
int front = -1, rear = -1;

// Stack for DFS
int stack[MAX];
int top = -1;

// Function to enqueue a vertex in the queue for BFS
void enqueue(int vertex) {
    if (rear == MAX - 1) {
        printf("Queue is full.\n");
    } else {
        if (front == -1) {
            front = 0;
        }
        rear++;
        queue[rear] = vertex;
    }
}

// Function to dequeue a vertex from the queue for BFS
int dequeue() {
    int vertex;
    if (front == -1) {
        printf("Queue is empty.\n");
        return -1;
    } else {
        vertex = queue[front];
        front++;
        if (front > rear) {
            front = rear = -1;
        }
        return vertex;
    }
}

// Function to push a vertex onto the stack for DFS
void push(int vertex) {
    if (top == MAX - 1) {
        printf("Stack overflow.\n");
    } else {
        top++;
        stack[top] = vertex;
    }
}

// Function to pop a vertex from the stack for DFS
int pop() {
    int vertex;
    if (top == -1) {
        printf("Stack underflow.\n");
        return -1;
    } else {
        vertex = stack[top];
        top--;
        return vertex;
    }
}

// Function to perform BFS traversal
void bfs(int adjacencyMatrix[MAX][MAX], int vertices, int startVertex) {
    bool visited[MAX] = { false };
    printf("BFS Traversal starting from vertex %d: ", startVertex);

    visited[startVertex] = true;
    enqueue(startVertex);

    while (front != -1) {
        int currentVertex = dequeue();
        printf("%d ", currentVertex);

        for (int i = 0; i < vertices; i++) {
            if (adjacencyMatrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                enqueue(i);
            }
        }
    }
    printf("\n");
}

// Function to perform DFS traversal
void dfs(int adjacencyMatrix[MAX][MAX], int vertices, int startVertex, int visited[MAX]) {
    push(startVertex);

    printf("DFS Traversal starting from vertex %d: ", startVertex);

    while (top != -1) {
        int currentVertex = pop();

        if (visited[currentVertex] == 0) {
            printf("%d ", currentVertex);
            visited[currentVertex] = 1;
        }

        for (int i = vertices - 1; i >= 0; i--) {
            if (adjacencyMatrix[currentVertex][i] == 1 && visited[i] == 0) {
                push(i);
            }
        }
    }
    printf("\n");
}

int main() {
    int vertices, startVertex;
    int adjacencyMatrix[MAX][MAX];
    int visited[MAX] = {0};

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &adjacencyMatrix[i][j]);
        }
    }

    printf("Enter the start vertex: ");
    scanf("%d", &startVertex);

    bfs(adjacencyMatrix, vertices, startVertex);
    // Reset visited array for DFS
    for (int i = 0; i < MAX; i++) {
        visited[i] = 0;
    }
    dfs(adjacencyMatrix, vertices, startVertex, visited);

    return 0;
}
