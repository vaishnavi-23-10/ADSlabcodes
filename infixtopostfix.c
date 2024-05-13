//infix to postfix conversion
//coeff exponent
//powers should be in the decreasing order

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

// Function to return precedence of operators
static int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

// Function to convert infix expression to postfix
void infixToPostfix(char* infix, char* postfix) {
    int i = 0, j = 0;
    int len = strlen(infix);
    int top = -1;
    char stack[MAX_LEN];

    while (i < len) {
        char c = infix[i];
        if (c == '(') {
            stack[++top] = c;
            i++;
        } else if (c == ')') {
            while (top > -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            if (top == -1) {
                printf("Invalid expression: Mismatched parentheses\n");
                return;
            }
            top--; // Pop the opening parenthesis
            i++;
        } else if (isdigit(c) || isalpha(c)) {
            postfix[j++] = c;
            i++;
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            while (top > -1 && prec(c) <= prec(stack[top])) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = c;
            i++;
        } else {
            printf("Invalid character: %c\n", c);
            return;
        }
    }

    while (top > -1) {
        if (stack[top] == '(') {
            printf("Invalid expression: Mismatched parentheses\n");
            return;
        }
        postfix[j++] = stack[top--];
    }

    postfix[j] = '\0';
}

int main() {
    char infix[MAX_LEN];
    char postfix[MAX_LEN];
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("The postfix expression is: %s\n", postfix);
    return 0;
}
