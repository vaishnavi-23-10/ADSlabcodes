#include <stdio.h>
#include <stdlib.h>

#define INF 999

struct graph
{
    int vertex;
    int weight;
    struct graph *next;
};

int parent[100];

void insert_list(int n, int v1, int v2, struct graph A[])
{
    struct graph *temp = (struct graph *)malloc(sizeof(struct graph));
    temp->vertex = v1;
    temp->weight = 0;
    temp->next = A[v2].next;
    A[v2].next = temp;

    struct graph *temp2 = (struct graph *)malloc(sizeof(struct graph));
    temp2->vertex = v2;
    temp2->weight = 0;
    temp2->next = A[v1].next;
    A[v1].next = temp2;
}

int find_parent(int i)
{
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void change_parent(int i, int j)
{
    int x, r;
    x = find_parent(i);
    r = find_parent(j);
    parent[x] = r;
}

void Kruskals(struct graph A[], int n)
{
    int a, b, cost = 0, min = INF, i, j, ne = 0;

    for (i = 0; i < n; i++)
        parent[i] = i;

    while (ne < n - 1)
    {
        min = INF;

        for (i = 0; i < n; i++)
        {
            struct graph *temp = &A[i];
            struct graph *p = temp->next;

            while (p != NULL)
            {
                if (find_parent(i) != find_parent(p->vertex) && p->weight < min)
                {
                    min = p->weight;
                    a = p->vertex;
                    b = i;
                }
                p = p->next;
            }
        }

        change_parent(a, b);

        struct graph *temp = &A[b];
        struct graph *p = temp->next;
        while (p->vertex != a)
            p = p->next;
        p->weight = INF;

        cost += min;
        ne++;
    }

    printf("The cost of the MST is: %d", cost);
}

int main()
{
    struct graph A[100];
    int V, v1, v2, decision, weight;

    printf("Enter the no. of vertices: ");
    scanf("%d", &V);

    for (int i = 0; i < V; i++)
    {
        A[i].vertex = i;
        A[i].weight = 0;
        A[i].next = NULL;
    }

    do
    {
        printf("Enter 1 to add an edge, or 0 to finish: ");
        scanf("%d", &decision);
        if (decision == 1)
        {
            printf("Enter the vertices for the edge: ");
            scanf("%d %d", &v1, &v2);
            printf("Enter the weight: ");
            scanf("%d", &weight);
            insert_list(V, v1, v2, A);
            A[v1].next->weight = weight;
            A[v2].next->weight = weight;
        }
    } while (decision == 1);

    Kruskals(A, V);
    return 0;
}
