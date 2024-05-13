#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
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

int height(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

struct TreeNode* mirrorImage(struct TreeNode* root) {
    if (root == NULL)
        return NULL;

    struct TreeNode* leftMirror = mirrorImage(root->left);
    struct TreeNode* rightMirror = mirrorImage(root->right);

    root->left = rightMirror;
    root->right = leftMirror;

    return root;
}

int main() {
    struct TreeNode* root = NULL;
    char choice;
    do {
        insertNode(&root);
        printf("Do you want to insert another node? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y');

    printf("\nTree Level-wise:\n");
    printLevelOrder(root);

    printf("\nHeight of the tree: %d\n", height(root));

    struct TreeNode* mirrorRoot = mirrorImage(root);
    printf("\nMirror Image of the Tree Level-wise:\n");
    printLevelOrder(mirrorRoot);

    return 0;
}
