#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char student_name[50];
    int student_roll_no;
    int total_marks;
};

// Function to swap two students
void swap(struct Student *a, struct Student *b) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform Heapify operation in Heap Sort
void heapify(struct Student arr[], int n, int i, int *swapCount) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].student_roll_no > arr[largest].student_roll_no)
        largest = left;

    if (right < n && arr[right].student_roll_no > arr[largest].student_roll_no)
        largest = right;

    if (largest != i) {
        (*swapCount)++;
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest, swapCount);
    }
}

// Function to perform Heap Sort
void heapSort(struct Student arr[], int n, int *swapCount) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, swapCount);

    for (int i = n - 1; i >= 0; i--) {
        (*swapCount)++;
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0, swapCount);
    }
}

// Function to display the array of students
void displayStudents(struct Student arr[], int n) {
    printf("Student Details:\n");
    printf("%-20s%-15s%-15s\n", "Student Name", "Roll Number", "Total Marks");
    for (int i = 0; i < n; i++) {
        printf("%-20s%-15d%-15d\n", arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
    }
}

int main() {
    int n;
    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct Student *students = (struct Student *)malloc(n * sizeof(struct Student));

    // Input details of students
    for (int i = 0; i < n; i++) {
        printf("Enter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].student_name);
        printf("Roll Number: ");
        scanf("%d", &students[i].student_roll_no);
        printf("Total Marks: ");
        scanf("%d", &students[i].total_marks);
    }

    int swapCountHeap = 0;

    struct Student *studentsHeap = (struct Student *)malloc(n * sizeof(struct Student));

    memcpy(studentsHeap, students, n * sizeof(struct Student));

    // Perform Heap Sort
    heapSort(studentsHeap, n, &swapCountHeap);


    // Display sorted arrays and swap counts
    printf("\nHeap Sort:\n");
    displayStudents(studentsHeap, n);
    printf("Number of swaps: %d\n", swapCountHeap);

    // Free allocated memory
    free(students);
    free(studentsHeap);

    return 0;
}
