#include <stdio.h>
#include <math.h>
#include <string.h>

int top = -1, a[100], n;

void push();
void pop();
int isempty();
int isfull();
void dis();

int main()
{
    int choice;
    printf("Enter the size of Stack:");
    scanf("%d", &n);
    printf("\n1.Push the element\n2.Pop the element\n3.Check if Stack is Empty\n4.Check if Stack is Full\n5.Display all elements");

    while (1)
    {
        printf("\n\nEnter the choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            push();
            break;
        case 2:
            pop();
            break;
        case 3:
            if (isempty())
                printf("Stack is Empty\n");
            else
                printf("Stack is not Empty\n");
            break;
        case 4:
            if (isfull())
                printf("Stack is Full\n");
            else
                printf("Stack is not Full\n");
            break;
        case 5:
            dis();
            break;
        }
    }

    return 0;
}

void push()
{
    if (isfull())
        printf("Stack is Full\n");
    else
    {
        int val;
        printf("Enter a value to be loaded in stack:");
        scanf("%d", &val);
        top++;
        a[top] = val;
    }
}

void pop()
{
    if (isempty())
        printf("No element in Stack\n");
    else
    {
        printf("Removed element is:%d\n", a[top]);
        top--;
    }
}

int isempty()
{
    return (top == -1);
}

int isfull()
{
    return (top == n - 1);
}

void dis()
{
    if (isempty())
    {
        printf("Stack is Empty\n");
    }
    else
    {
        for (int i = 0; i <= top; i++)
        {
            printf("%d\n", a[i]);
        }
    }
}
