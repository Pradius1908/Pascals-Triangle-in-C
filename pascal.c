#include <stdio.h>
#include <stdlib.h>

#define MAX 50

/* ---------- STACK IMPLEMENTATION ---------- */

struct Stack {
    int data[MAX];
    int top;
};

void initStack(struct Stack* s) {
    s->top = -1;
}

void push(struct Stack* s, int value) {
    s->data[++s->top] = value;
}

int pop(struct Stack* s) {
    return s->data[s->top--];
}

/* ---------- TREE NODE ---------- */

struct TreeNode {
    int data;
    struct TreeNode* left_parent;
    struct TreeNode* right_parent;
};

struct TreeNode* createNode() {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = 0;
    node->left_parent = NULL;
    node->right_parent = NULL;
    return node;
}

/* ---------- MAIN ---------- */

int main() {
    int n;
    printf("Enter number of rows: ");
    scanf("%d", &n);

    struct TreeNode* levels[MAX][MAX];

    /* Root */
    levels[0][0] = createNode();
    levels[0][0]->data = 1;

    /* Generate Pascal's Triangle using TREE + STACK */
    for (int i = 1; i < n; i++) {
        struct Stack s;
        initStack(&s);

        /* Push computed values into stack first */
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                push(&s, 1);
            } else {
                int val = levels[i-1][j-1]->data + levels[i-1][j]->data;
                push(&s, val);
            }
        }

        /* Pop from stack and assign to tree nodes */
        for (int j = i; j >= 0; j--) {
            levels[i][j] = createNode();
            levels[i][j]->data = pop(&s);

            if (j != 0 && j != i) {
                levels[i][j]->left_parent  = levels[i-1][j-1];
                levels[i][j]->right_parent = levels[i-1][j];
            }
        }
    }

    /* ---------- DISPLAY PASCAL'S TRIANGLE ---------- */

    printf("\nPascal's Triangle:\n\n");
    for (int i = 0; i < n; i++) {
        for (int s = 0; s < n - i - 1; s++)
            printf("  ");

        for (int j = 0; j <= i; j++)
            printf("%d   ", levels[i][j]->data);

        printf("\n");
    }

    /* ---------- BINOMIAL EXPANSION ---------- */

    printf("\nBinomial Expansion (x + y)^n:\n");
    for (int i = 0; i < n; i++) {
        printf("(x + y)^%d = ", i);
        for (int j = 0; j <= i; j++) {
            printf("%d*x^%d*y^%d", levels[i][j]->data, i-j, j);
            if (j != i) printf(" + ");
        }
        printf("\n");
    }

    /* ---------- FIBONACCI SERIES (Shallow Diagonals) ---------- */

    printf("\nFibonacci Series from Pascal's Triangle:\n");
    int fib[MAX] = {1, 1};

    for (int i = 2; i < n; i++)
        fib[i] = fib[i-1] + fib[i-2];

    for (int i = 0; i < n; i++)
        printf("%d ", fib[i]);

    printf("\n");

    /* ---------- POWERS OF 11 ---------- */

    printf("\nPowers of 11:\n");
    for (int i = 0; i < n && i < 6; i++) {
        long long num = 0;
        for (int j = 0; j <= i; j++)
            num = num * 10 + levels[i][j]->data;

        printf("11^%d = %lld\n", i, num);
    }

    /* ---------- FREE MEMORY ---------- */

    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
            free(levels[i][j]);

    return 0;
}
