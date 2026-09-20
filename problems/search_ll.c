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

// 1 -> true, 0 -> false
int is_same(Node *ll1, Node *ll2) {
    Node *curr1 = ll1;
    Node *curr2 = ll2;

    while (curr1 != NULL && curr2 != NULL) {
        if (curr1->data != curr2->data)
            return 0;

        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    return curr1 == NULL ? 1 : 0;
}

// 1 -> Yes, 0 -> No
int searchLL(Node *ll1, Node *ll2) {
    if (ll1 == NULL)
        return 1;

    Node *curr1 = ll1;
    Node *curr2 = ll2;
    while (curr2 != NULL) {
        if (curr1->data == curr2->data) {
            if (is_same(curr1, curr2)) {
                return 1;
            }
        }

        curr2 = curr2->next;
    }

    return 0;
}

int main(void) {
    Node *ll1 = createNode(10, createNode(20, NULL));
    Node *ll2 = createNode(5, createNode(10, createNode(20, NULL)));

    printf("ll1: ");
    printLL(ll1);
    printf("ll2: ");
    printLL(ll2);

    int res = searchLL(ll1, ll2);
    printf("%s\n", res == 1 ? "YES" : "NO");

    return 0;
}
