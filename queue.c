// Customer service queue
#include <stdio.h>
#include <stdlib.h>

#define MAX 5  // Maximum size of the queue

// Queue structure
struct Queue {
    int items[MAX];
    int front;
    int rear;
};

// Initialize the queue
void initQueue(struct Queue* q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is full
int isFull(struct Queue* q) {
    if (q->rear == MAX - 1) {
        return 1;
    }
    return 0;
}

// Check if the queue is empty
int isEmpty(struct Queue* q) {
    if (q->front == -1) {
        return 1;
    }
    return 0;
}

// Add an element to the queue (enqueue)
void enqueue(struct Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full! Cannot add more customers.\n");
        return;
    } else {
        if (q->front == -1) {
            q->front = 0;
        }
        q->rear++;
        q->items[q->rear] = value;
        printf("Customer %d entered the queue.\n", value);
    }
}

// Remove an element from the queue (dequeue)
int dequeue(struct Queue* q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty! No customers to attend.\n");
        return -1;
    } else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;  // Reset the queue when it's empty
        }
        printf("Customer %d was attended and removed from the queue.\n", item);
        return item;
    }
}

// Display the queue
void display(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
    } else {
        printf("Queue: ");
        for (int i = q->front; i <= q->rear; i++) {
            printf("%d ", q->items[i]);
        }
        printf("\n");
    }
}

// Practical case: Simulating a customer service queue
int main() {
    struct Queue q;
    initQueue(&q);

    // Simulating customers entering the queue
    enqueue(&q, 101);  // Customer 101 enters the queue
    enqueue(&q, 102);  // Customer 102 enters the queue
    enqueue(&q, 103);  // Customer 103 enters the queue

    display(&q);  // Display the queue

    // Simulating customer service
    dequeue(&q);  // Customer 101 is attended
    display(&q);  // Display the queue after service

    enqueue(&q, 104);  // Customer 104 enters the queue
    enqueue(&q, 105);  // Customer 105 enters the queue

    display(&q);  // Display the updated queue

    dequeue(&q);  // Customer 102 is attended
    dequeue(&q);  // Customer 103 is attended

    display(&q);  // Display the final queue

    return 0;
}
