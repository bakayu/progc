#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *createNode(int data, Node *next) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->next = next;
    return node;
}

void printLL(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

Node *reverseLL(Node *head, Node *prev) {
    if (head == NULL) {
        return prev;
    }
    Node *next = head->next;
    head->next = prev;
    prev = head;

    return reverseLL(next, prev);
}

int main(void) {
    Node *head = createNode(
        1, createNode(2, createNode(3, createNode(4, createNode(5, NULL)))));

    printf("before:\n");
    printLL(head);

    Node *newHead = reverseLL(head, NULL);
    printf("after:\n");
    printLL(newHead);

    return 0;
}
