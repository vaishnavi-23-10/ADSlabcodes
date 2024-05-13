#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

struct Node* newNode(int key) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

// Function to print the level order traversal of the AVL tree
void printLevelOrder(struct Node *root) {
    if (root == NULL)
        return;

    // Create an empty queue for level order traversal
    struct Node **queue = (struct Node **)malloc(sizeof(struct Node *) * 1000);
    int front = -1, rear = -1;

    // Enqueue the root
    queue[++rear] = root;
    queue[++rear] = NULL; // Mark the end of the first level

    while (front < rear) {
        struct Node *temp = queue[++front];

        if (temp != NULL) {
            printf("%d ", temp->key);

            // Enqueue left child
            if (temp->left != NULL)
                queue[++rear] = temp->left;

            // Enqueue right child
            if (temp->right != NULL)
                queue[++rear] = temp->right;
        } else {
            // Move to the next level
            if (front < rear) {
                printf("\n");
                queue[++rear] = NULL; // Mark the end of the next level
            }
        }
    }

    free(queue);
}

int main() {
    struct Node *root = NULL;
    int choice, key;

    while (1) {
        printf("1. Insert\n");
        printf("2. Display Level Order Traversal\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Level order traversal of the AVL tree is:\n");
                printLevelOrder(root);
                printf("\n");
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
