#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
    int isMaxHeap; // 1: maxHeap; 0: minHeap
} Heap;

Heap *createHeap(int isMaxHeap) {
    Heap *h = (Heap *)malloc(sizeof(Heap));
    h->capacity = 4;
    h->data = (int *)malloc(sizeof(int) * h->capacity);
    h->size = 0;
    h->isMaxHeap = isMaxHeap;
    return h;
}

int compare(Heap *h, int a, int b) {
    if (h->isMaxHeap)
        return a > b;
    else
        return a < b;
}

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void siftUp(Heap *h, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (compare(h, h->data[i], h->data[parent])) {
            swap(&h->data[i], &h->data[parent]);
            i = parent;
        } else
            break;
    }
}

void siftDown(Heap *h, int i) {
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int top = i;

        if (left < h->size && compare(h, h->data[left], h->data[top]))
            top = left;
        if (right < h->size && compare(h, h->data[right], h->data[top]))
            top = right;

        if (top == i)
            break;
        swap(&h->data[i], &h->data[top]);
        i = top;
    }
}

void push(Heap *h, int val) {
    // grow if full
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->data = (int *)realloc(h->data, sizeof(int) * h->capacity);
    }
    h->data[h->size] = val;
    siftUp(h, h->size);
    h->size++;
}

int pop(Heap *h) {
    int top = h->data[0];
    h->size--;
    h->data[0] = h->data[h->size];
    siftDown(h, 0);
    return top;
}

int peek(Heap *h) { return h->data[0]; }

void insert(Heap *maxHeap, Heap *minHeap, int num) {
    push(maxHeap, num);
    push(minHeap, pop(maxHeap));

    if (minHeap->size > maxHeap->size) {
        push(maxHeap, pop(minHeap));
    }
}

float getMedian(Heap *maxHeap, Heap *minHeap) {
    if (maxHeap->size > minHeap->size) {
        return (float)peek(maxHeap);
    }
    return (peek(maxHeap) + peek(minHeap)) / 2.0f;
}

int main(void) {
    Heap *maxHeap = createHeap(1);
    Heap *minHeap = createHeap(0);

    int stream[] = {5, 15, 1, 3, 8, 7, 9, 10, 20};
    int n = sizeof(stream) / sizeof(stream[0]);

    for (int i = 0; i < n; i++) {
        insert(maxHeap, minHeap, stream[i]);
        printf("Inserted %d, median = %.2f\n", stream[i],
               getMedian(maxHeap, minHeap));
    }

    free(maxHeap->data);
    free(maxHeap);
    free(minHeap->data);
    free(minHeap);

    return 0;
}
