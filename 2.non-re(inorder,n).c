#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define MAX_STACK_SIZE 100

struct Stack {
    struct TreeNode* items[MAX_STACK_SIZE];
    int top;
};

struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insertNode(struct TreeNode** root) {
    int value;
    char choice;
    printf("Enter the value of the node: ");
    scanf("%d", &value);
    struct TreeNode* newNode = createNode(value);
    if (*root == NULL) {
        *root = newNode;
    } else {
        struct TreeNode* current = *root;
        struct TreeNode* parent = NULL;
        while (current != NULL) {
            parent = current;
            printf("Insert %d as left or right child of %d (l/r): ", value, current->val);
            scanf(" %c", &choice);
            if (choice == 'l') {
                current = current->left;
            } else if (choice == 'r') {
                current = current->right;
            } else {
                printf("Invalid choice. Please enter 'l' or 'r'.\n");
                continue;
            }
        }
        if (choice == 'l') {
            parent->left = newNode;
        } else if (choice == 'r') {
            parent->right = newNode;
        }
    }
}

void initializeStack(struct Stack* stack) {
    stack->top = -1;
}

void push(struct Stack* stack, struct TreeNode* node) {
    if (stack->top == MAX_STACK_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack->items[++stack->top] = node;
}

struct TreeNode* pop(struct Stack* stack) {
    if (stack->top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack->items[stack->top--];
}

void inorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;
    struct Stack stack;
    initializeStack(&stack);
    struct TreeNode* current = root;
    while (current != NULL || stack.top != -1) {
        while (current != NULL) {
            push(&stack, current);
            current = current->left;
        }
        current = pop(&stack);
        printf("%d ", current->val);
        current = current->right;
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}

void printLevel(struct TreeNode* root, int level) {
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->val);
    else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

void printLevelOrder(struct TreeNode* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printf("Level %d: ", i);
        printLevel(root, i);
        printf("\n");
    }
}

int countNodesOnLongestPath(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int main() {
    struct TreeNode* root = NULL;
    char choice;
    do {
        insertNode(&root);
        printf("Do you want to insert another node? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y');

    printf("\nInorder Traversal: ");
    inorderTraversal(root);

    printf("\n\nNumber of nodes on longest path: %d\n", countNodesOnLongestPath(root));

    printf("\nTree Level-wise:\n");
    printLevelOrder(root);

    printf("\nHeight of the tree: %d\n", height(root));

    return 0;
}
