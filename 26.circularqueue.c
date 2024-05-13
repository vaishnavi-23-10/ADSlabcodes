#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

// Structure to represent the circular queue
struct CircularQueue {
    int data[MAX_SIZE];
    int front, rear;
};

// Function to initialize the circular queue
void initialize(struct CircularQueue *queue) {
    queue->front = queue->rear = -1;
}

// Function to check if the queue is full
int isFull(struct CircularQueue *queue) {
    return (queue->front == 0 && queue->rear == MAX_SIZE - 1) || (queue->rear == (queue->front - 1) % (MAX_SIZE - 1));
}

// Function to check if the queue is empty
int isEmpty(struct CircularQueue *queue) {
    return queue->front == -1;
}

// Function to enqueue at the rear of the queue
void enqueueRear(struct CircularQueue *queue, int value) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
    } else {
        if (isEmpty(queue)) {
            queue->front = queue->rear = 0;
        } else {
            queue->rear = (queue->rear + 1) % MAX_SIZE;
        }
        queue->data[queue->rear] = value;
        printf("Enqueued %d at the rear.\n", value);
    }
}

// Function to enqueue at the front of the queue
void enqueueFront(struct CircularQueue *queue, int value) {
    if (isFull(queue)) {
        printf("Queue is full. Cannot enqueue.\n");
    } else {
        if (isEmpty(queue)) {
            queue->front = queue->rear = 0;
        } else {
            queue->front = (queue->front - 1 + MAX_SIZE) % MAX_SIZE;
        }
        queue->data[queue->front] = value;
        printf("Enqueued %d at the front.\n", value);
    }
}

// Function to dequeue from the front of the queue
int dequeueFront(struct CircularQueue *queue) {
    int value;
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    } else {
        value = queue->data[queue->front];
        if (queue->front == queue->rear) {
            // If the queue has only one element
            initialize(queue);
        } else {
            queue->front = (queue->front + 1) % MAX_SIZE;
        }
        printf("Dequeued %d from the front.\n", value);
        return value;
    }
}

// Function to dequeue from the rear of the queue
int dequeueRear(struct CircularQueue *queue) {
    int value;
    if (isEmpty(queue)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1;
    } else {
        value = queue->data[queue->rear];
        if (queue->front == queue->rear) {
            // If the queue has only one element
            initialize(queue);
        } else {
            queue->rear = (queue->rear - 1 + MAX_SIZE) % MAX_SIZE;
        }
        printf("Dequeued %d from the rear.\n", value);
        return value;
    }
}

// Function to display the elements of the queue
void display(struct CircularQueue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
    } else {
        printf("Queue elements: ");
        int i = queue->front;
        do {
            printf("%d ", queue->data[i]);
            i = (i + 1) % MAX_SIZE;
        } while (i != (queue->rear + 1) % MAX_SIZE);
        printf("\n");
    }
}

int main() {
    struct CircularQueue queue;
    initialize(&queue);

    int choice, value;

    do {
        printf("\n----- Menu -----\n");
        printf("1. Enqueue at Front\n");
        printf("2. Enqueue at Rear\n");
        printf("3. Dequeue from Front\n");
        printf("4. Dequeue from Rear\n");
        printf("5. Display\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue at front: ");
                scanf("%d", &value);
                enqueueFront(&queue, value);
                break;
            case 2:
                printf("Enter value to enqueue at rear: ");
                scanf("%d", &value);
                enqueueRear(&queue, value);
                break;
            case 3:
                dequeueFront(&queue);
                break;
            case 4:
                dequeueRear(&queue);
                break;
            case 5:
                display(&queue);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}
