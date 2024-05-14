#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in an Inorder Threaded Binary Tree
typedef struct Node {
    int data;
    struct Node *left, *right;
    int lthread; // True if left pointer is a thread
    int rthread; // True if right pointer is a thread
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    newNode->lthread = newNode->rthread = 1; // Initial threads
    return newNode;
}

// Insert a new node in the Inorder Threaded Binary Tree
Node* insert(Node* root, int data) {
    Node* newNode = createNode(data);
    if (root == NULL)
        return newNode;

    Node* parent = NULL;
    Node* current = root;

    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            if (current->lthread == 0)
                current = current->left;
            else
                break;
        } else {
            if (current->rthread == 0)
                current = current->right;
            else
                break;
        }
    }

    if (data < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->lthread = 0;
        parent->left = newNode;
    } else {
        newNode->left = parent;
        newNode->right = parent->right;
        parent->rthread = 0;
        parent->right = newNode;
    }

    return root;
}

// Function to find the inorder successor of a given node
Node* inorderSuccessor(Node* ptr) {
    if (ptr->rthread == 1)
        return ptr->right;

    ptr = ptr->right;
    while (ptr->lthread == 0)
        ptr = ptr->left;

    return ptr;
}

// Function to traverse the threaded binary tree in inorder
void inorderTraversal(Node* root) {
    if (root == NULL)
        return;

    // Go to the leftmost node
    Node* current = root;
    while (current->lthread == 0)
        current = current->left;

    while (current != NULL) {
        printf("%d ", current->data);
        current = inorderSuccessor(current);
    }
}

// Main function
int main() {
    Node* root = NULL;
    int choice, data;

    do {
        printf("1. Insert\n");
        printf("2. Inorder Traversal\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                root = insert(root, data);
                break;
            case 2:
                printf("Inorder traversal of the Inorder Threaded Binary Tree:\n");
                inorderTraversal(root);
                printf("\n");
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);

    return 0;
}
