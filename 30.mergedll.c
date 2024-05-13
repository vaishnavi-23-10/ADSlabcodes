#include <stdio.h>
#include <stdlib.h>

// Define a Node structure for the doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Function to create a new Node with given data
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a new Node at the end of the doubly linked list
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
        newNode->prev = temp;
    }
}

// Function to merge two sorted doubly linked lists
struct Node* mergeSortedLists(struct Node* list1, struct Node* list2) {
    struct Node* mergedList = NULL;
    struct Node* temp;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data < list2->data) {
            insertAtEnd(&mergedList, list1->data);
            list1 = list1->next;
        } else {
            insertAtEnd(&mergedList, list2->data);
            list2 = list2->next;
        }
    }

    // If there are remaining nodes in list1 or list2
    while (list1 != NULL) {
        insertAtEnd(&mergedList, list1->data);
        list1 = list1->next;
    }

    while (list2 != NULL) {
        insertAtEnd(&mergedList, list2->data);
        list2 = list2->next;
    }

    return mergedList;
}

// Function to print the doubly linked list
void printList(struct Node* head) {
    while (head != NULL) {
        printf("%d <-> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    struct Node* mergedList = NULL;
    int n, data;

    // Input for the first sorted list
    printf("Enter the number of elements for the first sorted list: ");
    scanf("%d", &n);
    printf("Enter the elements for the first sorted list:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &data);
        insertAtEnd(&list1, data);
    }

    // Input for the second sorted list
    printf("Enter the number of elements for the second sorted list: ");
    scanf("%d", &n);
    printf("Enter the elements for the second sorted list:\n");
    for (int i = 0; i < n; ++i) {
        scanf("%d", &data);
        insertAtEnd(&list2, data);
    }

    // Merge the sorted lists
    mergedList = mergeSortedLists(list1, list2);

    // Print the merged list
    printf("Merged Sorted List: ");
    printList(mergedList);

    return 0;
}
