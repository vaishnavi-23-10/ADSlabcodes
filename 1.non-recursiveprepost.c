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

void preorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;
    struct Stack stack;
    initializeStack(&stack);
    push(&stack, root);
    while (stack.top != -1) {
        struct TreeNode* node = pop(&stack);
        printf("%d ", node->val);
        if (node->right != NULL)
            push(&stack, node->right);
        if (node->left != NULL)
            push(&stack, node->left);
    }
}

void postorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;
    struct Stack stack1, stack2;
    initializeStack(&stack1);
    initializeStack(&stack2);
    push(&stack1, root);
    while (stack1.top != -1) {
        struct TreeNode* node = pop(&stack1);
        push(&stack2, node);
        if (node->left != NULL)
            push(&stack1, node->left);
        if (node->right != NULL)
            push(&stack1, node->right);
    }
    while (stack2.top != -1) {
        struct TreeNode* node = pop(&stack2);
        printf("%d ", node->val);
    }
}

int countNodes(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    return max(height(root->left), height(root->right));
}

int main() {
    struct TreeNode* root = NULL;
    char choice;
    do {
        insertNode(&root);
        printf("Do you want to insert another node? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y');

    printf("\nPreorder Traversal: ");
    preorderTraversal(root);
    printf("\nPostorder Traversal: ");
    postorderTraversal(root);

    printf("\nNumber of nodes in the tree: %d\n", countNodes(root));
    printf("Height of the tree: %d\n", height(root));

    return 0;
}
