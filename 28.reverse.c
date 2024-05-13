#include <stdio.h>
#include <stdlib.h>

// Define a Node structure for the linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new Node with given data
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new Node at the end of the list
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Function to reverse the linked list iteratively
void reverseList(struct Node** head) {
    struct Node *prev = NULL, *current = *head, *next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head = prev;
}

// Function to print the linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int n, data;

    // Take user input for the linked list
    printf("Enter the number of elements in the list: ");
    scanf("%d", &n);

    printf("Enter the elements of the list:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &data);
        insertAtEnd(&head, data);
    }

    // Print the original linked list
    printf("Original Linked List: ");
    printList(head);

    // Reverse the linked list
    reverseList(&head);

    // Print the reversed linked list
    printf("Reversed Linked List: ");
    printList(head);

    return 0;
}
