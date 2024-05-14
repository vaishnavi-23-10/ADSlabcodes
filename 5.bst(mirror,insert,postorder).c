#include <stdio.h>
#include <stdlib.h>

// Structure for a node of the binary search tree
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Structure for a stack used in postorder traversal
struct Stack {
    struct Node** array;
    int top;
    int capacity;
};

// Function to create a new node with the given key
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to create a new stack
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (struct Node**)malloc(stack->capacity * sizeof(struct Node*));
    return stack;
}

// Function to check if the stack is full
int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

// Function to push a node onto the stack
void push(struct Stack* stack, struct Node* node) {
    if (isFull(stack))
        return;
    stack->array[++stack->top] = node;
}

// Function to pop a node from the stack
struct Node* pop(struct Stack* stack) {
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

// Function to get the top node of the stack
struct Node* top(struct Stack* stack) {
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top];
}

// Function to insert a key into the BST
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return newNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

// Function to create the mirror image of a binary tree
void mirror(struct Node* root) {
    if (root == NULL)
        return;
    struct Stack* stack = createStack(100);
    push(stack, root);
    while (!isEmpty(stack)) {
        struct Node* current = pop(stack);
        struct Node* temp = current->left;
        current->left = current->right;
        current->right = temp;
        if (current->left != NULL)
            push(stack, current->left);
        if (current->right != NULL)
            push(stack, current->right);
    }
}

// Function to find a key in the BST
struct Node* find(struct Node* root, int key) {
    while (root != NULL) {
        if (key == root->key)
            return root;
        else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

// Function to perform postorder traversal of a binary search tree
void postOrderTraversal(struct Node* root) {
    if (root == NULL)
        return;
    struct Stack* stack = createStack(100);
    do {
        while (root) {
            if (root->right)
                push(stack, root->right);
            push(stack, root);
            root = root->left;
        }
        root = pop(stack);
        if (root->right && top(stack) == root->right) {
            pop(stack);
            push(stack, root);
            root = root->right;
        } else {
            printf("%d ", root->key);
            root = NULL;
        }
    } while (!isEmpty(stack));
}

// Function to display the menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Insert\n");
    printf("2. Mirror Image\n");
    printf("3. Find\n");
    printf("4. Postorder Traversal (non-recursive)\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

// Main function
int main() {
    struct Node* root = NULL;
    int choice, key;
    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Creating mirror image...\n");
                mirror(root);
                printf("Mirror image created.\n");
                break;
            case 3:
                printf("Enter key to find: ");
                scanf("%d", &key);
                if (find(root, key))
                    printf("Key %d found in the tree.\n", key);
                else
                    printf("Key %d not found in the tree.\n", key);
                break;
            case 4:
                printf("Postorder traversal (non-recursive):\n");
                postOrderTraversal(root);
                printf("\n");
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}
