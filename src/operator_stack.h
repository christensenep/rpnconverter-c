#ifndef OPERATOR_STACK_H
#define OPERATOR_STACK_H

typedef struct _Node {
  struct _Node* next;
  char operator;
} Node;

typedef struct _OperatorStack {
  Node* top;
} OperatorStack;

void operatorStack_initStack(OperatorStack*);
void operatorStack_push(OperatorStack*, char);
char operatorStack_pop(OperatorStack*);
char operatorStack_peek(OperatorStack*);

#endif /* OPERATOR_STACK_H */