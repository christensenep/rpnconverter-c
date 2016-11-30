#include <stdlib.h>

#include "rpn.h"
#include "operator_stack.h"

char* infix_to_postfix(char* infixString) {
  OperatorStack operatorStack;
  operatorStack_initStack(operatorStack);
  char** postfixString = malloc(sizeof(char) * 500);
  char* currentPostfixStringPos = *postfixString;

  if (infixString == NULL) {
    return NULL;
  }

  char currentCharacter;
  for (currentCharacter = *infixString; currentCharacter != '\0'; infixString++) {
    if (currentCharacter == '+') {
      operatorStack_push(operatorStack, currentCharacter);
    }
    else {
      *currentPostfixStringPos = currentCharacter;
      currentPostfixStringPos++;
    }
  };

  char poppedOperator;
  while((poppedOperator = operatorStack_pop(operatorStack)) != '\0') {
    *currentPostfixStringPos = currentCharacter;
    currentPostfixStringPos++;
  }
  return *postfixString;
}