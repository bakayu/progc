/*
Evaluation of Postfix expressions

The Postfix notation is used to represent algebraic expressions. The expressions
written in postfix form are evaluated faster compared to infix notation as
parenthesis are not required in postfix.

For example: 3 1 * + 9 - is a postfix expression where parenthesis are not
required to change the order of evaluation of expressions. The order of
evaluation for expressions with operator is governed by the position of the
operator in the expression.

Here, the order of evaluation is: *, +, -

(3 * 1) + 2) - 9 is the equivalent infix expression and the value of the
expression is: -4

Constraints: 0 < Length of expression < 50 Operands are numeric Operators are:
"+" for addition, "-" for subtraction, "*" for multiplication, "/" for division
and

Every token in the expression is separated by a space.

Sample Input 2 3 1 * + 9 -

Sample Output -4
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} Stack;

Stack *createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->capacity = 4;
    stack->data = (int *)malloc(sizeof(int) * stack->capacity);
    stack->size = 0;
    return stack;
}

bool is_empty(Stack *stack) { return stack->size == 0; }

void push_to_stack(Stack *stack, int val) {
    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        stack->data =
            (int *)realloc(stack->data, sizeof(int) * stack->capacity);
    }

    stack->data[stack->size] = val;
    stack->size++;
}

// NOTE: Caller is responsible for underflow check,
// Calling on empty stack will result in undefined behaviour.
int peek(Stack *stack) { return stack->data[stack->size - 1]; }

// NOTE: Caller is responsible for underflow check,
// Calling on empty stack will result in undefined behaviour.
int pop_from_stack(Stack *stack) {
    int top = peek(stack);
    stack->size--;
    return top;
}

void cleanup(Stack *stack) {
    free(stack->data);
    free(stack);
}

int evaluate_postfix_exp(const char *postfix_exp) {
    Stack *stack = createStack();

    char buffer[64];
    strncpy(buffer, postfix_exp, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char *token = strtok(buffer, " ");
    while (token != NULL) {
        bool is_operator = token[1] == '\0' && !isdigit((unsigned char)token[0]);

        if (is_operator) {
            int num2 = pop_from_stack(stack);
            int num1 = pop_from_stack(stack);
            int val;
            switch (token[0]) {
            case '+':
                val = num1 + num2;
                break;
            case '-':
                val = num1 - num2;
                break;
            case '*':
                val = num1 * num2;
                break;
            case '/':
                // NOTE: simply returning `-1` in case of divide by 0
                if (num2 == 0) {
                    cleanup(stack);
                    return -1;
                }
                val = num1 / num2;
                break;
            default:
                val = 0;
                break;
            }
            push_to_stack(stack, val);
        } else {
            push_to_stack(stack, atoi(token));
        }

        token = strtok(NULL, " ");
    }

    int result = pop_from_stack(stack);
    cleanup(stack);
    printf("%d\n", result);
    return result;
}

int main(void) {
    const char *test_case_1 = "2 3 1 * + 9 -";
    const char *test_case_2 = "4 6 +";
    const char *test_case_3 = "5 1 2 + 4 * + 3 -";

    printf("test case 1: %s\n",
           evaluate_postfix_exp(test_case_1) == -4 ? "PASS" : "FAIL");
    printf("test case 2: %s\n",
           evaluate_postfix_exp(test_case_2) == 10 ? "PASS" : "FAIL");
    printf("test case 3: %s\n",
           evaluate_postfix_exp(test_case_3) == 14 ? "PASS" : "FAIL");

    return 0;
}
