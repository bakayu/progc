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

Node *intersect_ll(Node *ll1, Node *ll2) {
    Node *dummy = createNode(0, NULL);
    Node *curr0 = dummy;

    Node *curr1 = ll1;
    Node *curr2 = ll2;
    while (curr1 != NULL && curr2 != NULL) {
        if (curr1->data == curr2->data) {
            Node *newNode = createNode(curr1->data, NULL);
            curr0->next = newNode;
            curr0 = curr0->next;

            curr1 = curr1->next;
            curr2 = curr2->next;
        } else if (curr1->data > curr2->data) {
            curr2 = curr2->next;
        } else {
            curr1 = curr1->next;
        }
    }

    return dummy->next;
}

int main(void) {
    Node *ll1 = createNode(
        1, createNode(2, createNode(2, createNode(3, createNode(4, NULL)))));
    Node *ll2 =
        createNode(2, createNode(2, createNode(2, createNode(4, NULL))));

    printf("ll1: ");
    printLL(ll1);
    printf("ll2: ");
    printLL(ll2);

    Node *res = intersect_ll(ll1, ll2);
    printf("res: ");
    printLL(res);

    return 0;
}
