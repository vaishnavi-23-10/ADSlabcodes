#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a student
struct Student {
    char student_name[50];
    int student_roll_no;
    int total_marks;
};

// Function to perform insertion sort and count swaps
int insertionSort(struct Student arr[], int n) {
    int i, j, swaps = 0;
    struct Student key;

    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position
        while (j >= 0 && arr[j].student_roll_no > key.student_roll_no) {
            arr[j + 1] = arr[j];
            j = j - 1;
            swaps++;
        }
        arr[j + 1] = key;
    }

    return swaps;
}

// Function to merge two subarrays of arr[]
void merge(struct Student arr[], int l, int m, int r, int *swaps) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    struct Student L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i].student_roll_no <= R[j].student_roll_no) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
            *swaps = *swaps + (m - (l + i) + 1); // Counting swaps
        }
        k++;
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Recursive function to perform merge sort and count swaps
void mergeSort(struct Student arr[], int l, int r, int *swaps) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m, swaps);
        mergeSort(arr, m + 1, r, swaps);

        // Merge the sorted halves
        merge(arr, l, m, r, swaps);
    }
}

// Function to print the array of students
void printArray(struct Student arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("Name: %s, Roll No: %d, Total Marks: %d\n", arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
}

int main() {
    int n, i, swaps_insertion = 0, swaps_merge = 0;

    printf("Enter the number of students: ");
    scanf("%d", &n);

    struct Student *students_insertion = (struct Student *)malloc(n * sizeof(struct Student));
    struct Student *students_merge = (struct Student *)malloc(n * sizeof(struct Student));

    printf("Enter student details (Name, Roll No, Total Marks):\n");
    for (i = 0; i < n; i++) {
        scanf("%s %d %d", students_insertion[i].student_name, &students_insertion[i].student_roll_no, &students_insertion[i].total_marks);
        strcpy(students_merge[i].student_name, students_insertion[i].student_name);
        students_merge[i].student_roll_no = students_insertion[i].student_roll_no;
        students_merge[i].total_marks = students_insertion[i].total_marks;
    }

    // Perform insertion sort
    swaps_insertion = insertionSort(students_insertion, n);

    // Perform merge sort
    mergeSort(students_merge, 0, n - 1, &swaps_merge);

    printf("\nSorted array using Insertion Sort (Swaps: %d):\n", swaps_insertion);
    printArray(students_insertion, n);

    printf("\nSorted array using Merge Sort (Swaps: %d):\n", swaps_merge);
    printArray(students_merge, n);

    free(students_insertion);
    free(students_merge);

    return 0;
}
