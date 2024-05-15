#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Employee structure
struct Employee {
    int emp_id;
    char name[50];
    struct Employee *left;
    struct Employee *right;
};

// Function to create a new employee node
struct Employee* createEmployee(int emp_id, const char *name) {
    struct Employee* newEmployee = (struct Employee*)malloc(sizeof(struct Employee));
    newEmployee->emp_id = emp_id;
    strcpy(newEmployee->name, name);
    newEmployee->left = NULL;
    newEmployee->right = NULL;
    return newEmployee;
}

// Function to insert an employee record into the BST
struct Employee* insert(struct Employee* root, int emp_id, const char *name) {
    if (root == NULL)
        return createEmployee(emp_id, name);

    if (emp_id < root->emp_id)
        root->left = insert(root->left, emp_id, name);
    else if (emp_id > root->emp_id)
        root->right = insert(root->right, emp_id, name);

    return root;
}

// Function to search for an employee record by emp_id
struct Employee* search(struct Employee* root, int emp_id) {
    if (root == NULL || root->emp_id == emp_id)
        return root;

    if (emp_id < root->emp_id)
        return search(root->left, emp_id);
    else
        return search(root->right, emp_id);
}

// Function to perform inorder traversal of the BST (to print the sorted records)
void inorder(struct Employee* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("Emp ID: %d, Name: %s\n", root->emp_id, root->name);
        inorder(root->right);
    }
}

int main() {
    struct Employee* root = NULL;
    int emp_id;
    char name[50];

    // Inserting employee records
    printf("Enter employee details (ID and Name), enter -1 to stop:\n");
    while (1) {
        printf("Enter employee ID (-1 to stop): ");
        scanf("%d", &emp_id);
        if (emp_id == -1)
            break;

        printf("Enter employee name: ");
        scanf(" %[^\n]s", name);

        root = insert(root, emp_id, name);
    }

    printf("\nEmployee records sorted by emp_id (ascending order):\n");
    inorder(root);

    // Searching for an employee record
    int search_id;
    printf("\nEnter employee ID to search: ");
    scanf("%d", &search_id);
    struct Employee* found = search(root, search_id);
    if (found != NULL)
        printf("\nEmployee with emp_id %d found. Name: %s\n", search_id, found->name);
    else
        printf("\nEmployee with emp_id %d not found.\n", search_id);

    return 0;
}
