/* Singly linked list
github.com/tozaicevas */
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void push_front(Node**, int);               /* push entry at the front of list in O(1) time */
void push_back(Node**, int);                /* push entry at the end of list in O(n) time */
Node* pop_front(Node**);                    /* returns first value of the list */
Node* pop_back(Node**);                     /* returns last value of the list */
void insert(Node**, int, int);              /* insert entry by index [1, n] */
void delete_by_index(Node**, int);          /* delete entry by index [1, n] */
void print_list(Node*);                     /* prints all elements in the list */
void free_list(Node**);                     /* free memory and dissolve the list */

int main(void) {
    Node *HEAD = NULL;
    int n;                                  /* number of elements in single linked list */
    int i, data_tmp;

    /* read number of elements */
    printf("Number of elements: ");
    scanf("%d", &n);
    /* read elements and put them into list */
    for (i=0; i<n; i++) {
        printf("%d: ", i+1);
        scanf("%d", &data_tmp);
        push_back(&HEAD, data_tmp);
    }
    /* print the list */
    print_list(HEAD);
    /* do stuff */

    /* destroy the list by freeing allocated memory */
    free_list(&HEAD);
    return 0;
}

void push_front(Node **HEAD, int data) {
    Node *new = malloc(sizeof(Node));
    new->data = data;
    new->next = *HEAD;
    *HEAD = new;
}

void push_back(Node **HEAD, int data)
{
    while (*HEAD)
        HEAD = &(*HEAD)->next;
    *HEAD = malloc(sizeof(**HEAD));         
    (*HEAD)->data = data;
    (*HEAD)->next = NULL;
}

Node* pop_front(Node **HEAD) {
    Node *tmp = *HEAD;
    if (*HEAD == NULL)
        return NULL;
    *HEAD = (*HEAD)->next;
    return tmp;
}

Node* pop_back(Node **HEAD) {
    Node *tmp = NULL;
    if (*HEAD == NULL)
        return NULL;
    while ((*HEAD)->next)
        HEAD = &(*HEAD)->next;
    tmp = *HEAD;
    *HEAD = NULL;
    return tmp;
}

void insert(Node **HEAD, int index, int data) {
    Node *new = NULL;
    int i=0;
    while (*HEAD && i != index-1) {
        HEAD = &(*HEAD)->next;
        i++;
    }
    if (*HEAD == NULL) {
        printf("Index out of range\n");
        return;
    }
    new = malloc(sizeof(Node));
    new->data = data;
    new->next = *HEAD;
    *HEAD = new;
}

void delete_by_index(Node **HEAD, int index) {
    Node* tmp = NULL;
    int i=0;
    while (*HEAD && i != index-1) {
        HEAD = &(*HEAD)->next;
        i++;
    }
    if (*HEAD == NULL) {
        printf("Index out of range\n");
        return;
    }
    tmp = *HEAD;                         
    *HEAD = (*HEAD)->next;
    free(tmp);                               
}

void print_list(Node *HEAD) {
    while (HEAD) {
        printf("%d\n", HEAD->data);
        HEAD = HEAD->next;
    }
}

void free_list(Node **HEAD) {
    Node *tmp = NULL;
    while (*HEAD) {
        tmp = *HEAD;
        *HEAD = (*HEAD)->next;
        free(tmp);
    }
}
