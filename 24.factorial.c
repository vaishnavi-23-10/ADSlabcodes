#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int stack[MAX_SIZE];
int top = -1;

int isFull() {
    return top == MAX_SIZE - 1;
}

int isEmpty() {
    return top == -1;
}

void push(int value) {
    if (!isFull()) {
        stack[++top] = value;
    } else {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
}

int pop() {
    if (!isEmpty()) {
        return stack[top--];
    } else {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }
}

void fibonacciUsingStack(int n) {
    int i, term1 = 0, term2 = 1;

    for (i = 0; i < n; ++i) {
        printf("%d ", term1);
        push(term1);
        int nextTerm = term1 + term2;
        term1 = term2;
        term2 = nextTerm;
    }

    printf("\n");
}

int factorial(int n) {
    push(n);

    int result = 1;

    while (!isEmpty()) {
        int topValue = pop();
        result *= topValue;

        if (topValue > 1) {
            push(topValue - 1);
        }
    }

    return result;
}

int main() {
    int choice, num;

    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Calculate Fibonacci series\n");
        printf("2. Calculate Factorial\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of terms for the Fibonacci series: ");
                scanf("%d", &num);
                if (num <= 0) {
                    printf("Number of terms should be greater than 0.\n");
                } else {
                    printf("Fibonacci series using stack: ");
                    fibonacciUsingStack(num);
                }
                break;
            case 2:
                printf("Enter a number to calculate its factorial: ");
                scanf("%d", &num);
                if (num < 0) {
                    printf("Factorial is not defined for negative numbers.\n");
                } else {
                    int result = factorial(num);
                    printf("Factorial of %d is: %d\n", num, result);
                }
                break;
            case 3:
                printf("Exiting...\n");
                exit(EXIT_SUCCESS);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
