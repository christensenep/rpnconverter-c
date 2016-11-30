#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "operator_stack.h"

void operatorStack_initStack(OperatorStack stack) {
  stack.top = NULL;
  printf("blah");
};

void operatorStack_push(OperatorStack stack, char operator) {
  Node* newNode;
  newNode = (Node*) malloc(sizeof(Node));
  newNode->operator = operator;
  newNode->next = stack.top;
  stack.top = newNode;
};

char operatorStack_pop(OperatorStack stack) {
  Node* poppedNode = stack.top;
  if (poppedNode == NULL) {
    return '\0';
  }

  char poppedOperator = poppedNode->operator;
  stack.top = poppedNode->next;
  free(poppedNode);
  return poppedOperator;
};