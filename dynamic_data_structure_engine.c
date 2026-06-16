#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
    int size;
} Stack;

// Initialize stack controls safely
void init_stack(Stack *stack) {
    stack->top = NULL;
    stack->size = 0;
}

// Check if memory elements are empty
bool is_empty(const Stack *stack) {
    return stack->top == NULL;
}

// Push data item to top of structural workflow
void push(Stack *stack, int val) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("System Alert: Failed stack overflow safety allocation!\n");
        exit(1);
    }
    new_node->value = val;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
    printf("Pushed: %d onto stack (Size: %d)\n", val, stack->size);
}

// Remove item elements from structure top safely
int pop(Stack *stack, bool *success) {
    if (is_empty(stack)) {
        if (success != NULL) *success = false;
        printf("Error: Attempted stack underflow pop extraction.\n");
        return -1;
    }

    Node *temp = stack->top;
    int popped_val = temp->value;
    stack->top = temp->next;
    free(temp);
    stack->size--;

    if (success != NULL) *success = true;
    return popped_val;
}

// Safely view top stack component without manipulation
int peek(const Stack *stack, bool *success) {
    if (is_empty(stack)) {
        if (success != NULL) *success = false;
        return -1;
    }
    if (success != NULL) *success = true;
    return stack->top->value;
}

// Render dynamic mapping view of stack sequence lines
void display_stack(const Stack *stack) {
    printf("\n--- Current Stack Configuration ---\n");
    if (is_empty(stack)) {
        printf("[Empty Stack Node Stack]\n");
        return;
    }
    Node *current = stack->top;
    while (current != NULL) {
        printf(" | %3d |\n", current->value);
        printf(" -------\n");
        current = current->next;
    }
    printf("   NULL\n");
}

// Fully purge allocations across memory structures
void clear_stack(Stack *stack) {
    Node *current = stack->top;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    stack->top = NULL;
    stack->size = 0;
}

int main(void) {
    Stack tracking_stack;
    init_stack(&tracking_stack);
    bool access_state = false;

    printf("--- Executing Structural Appends ---\n");
    push(&tracking_stack, 15);
    push(&tracking_stack, 30);
    push(&tracking_stack, 45);

    display_stack(&tracking_stack);

    printf("\n--- Executing Peak Check Verification ---\n");
    int peak_val = peek(&tracking_stack, &access_state);
    if (access_state) {
        printf("Top element preview data: %d\n", peak_val);
    }

    printf("\n--- Executing Structural Extractions ---\n");
    int item1 = pop(&tracking_stack, &access_state);
    if (access_state) printf("Popped Target element: %d\n", item1);

    int item2 = pop(&tracking_stack, &access_state);
    if (access_state) printf("Popped Target element: %d\n", item2);

    display_stack(&tracking_stack);

    printf("\n--- Handling Safety Extraction Failures ---\n");
    pop(&tracking_stack, &access_state); // Emptying remaining node element
    pop(&tracking_stack, &access_state); // Triggers logic underflow protection condition

    clear_stack(&tracking_stack);
    printf("\n[System Log]: Pointer allocations released back to OS.\n");
    return 0;
}

