#include <stdlib.h>
#include <string.h>

#include "rpn.h"
#include "operator_stack.h"

const char* _operators = "+-*/^";

typedef struct _Expression {
  char * string;
  int size;
  int pos;
} Expression;

void expression_init(Expression* expression) {
  expression->size = 5;
  expression->pos = 0;
  expression->string = malloc(sizeof(char) * expression->size);
};

void expression_delete(Expression* expression) {
  free(expression->string);
};

void expression_addChar(Expression* expression, char newChar) {
  if (expression->pos == expression->size-1) {
    int newSize = expression->size*2;
    char* oldString = expression->string;
    expression->string = malloc(sizeof(char) * newSize);
    memcpy(expression->string, oldString, expression->size);
    free(oldString);
    expression->size = newSize;
  }

  expression->string[expression->pos] = newChar;
  expression->string[expression->pos+1] = '\0';

  expression->pos++;
};

char* expression_toString(Expression* expression) {
  char* returnString;

  int stringSize = 1;
  for (int i = 0; expression->string[i] != '\0'; ++i) {
    ++stringSize;
  }

  returnString = malloc(sizeof(char) * stringSize);
  memcpy(returnString, expression->string, stringSize);

  return returnString;
}

int isOperator(char character) {
  if (character != '\0' && strchr(_operators, character) != NULL) {
    return 1;
  }
  else {
    return 0;
  }
};

char* infix_to_postfix(char* infixString) {
  OperatorStack operatorStack;
  operatorStack_initStack(&operatorStack);
  Expression postfixExpression;
  expression_init(&postfixExpression);

  if (infixString == NULL) {
    return NULL;
  }

  char currentCharacter;
  for (currentCharacter = *infixString; currentCharacter != '\0'; infixString++, currentCharacter = *infixString) {
    if (isOperator(currentCharacter)) {
      char lastOperator = operatorStack_peek(&operatorStack);

      if (lastOperator == currentCharacter) {
        operatorStack_pop(&operatorStack);
        expression_addChar(&postfixExpression, lastOperator);
      }

      operatorStack_push(&operatorStack, currentCharacter);
    }
    else {
      expression_addChar(&postfixExpression, currentCharacter);
    }
  };

  char poppedOperator;
  while((poppedOperator = operatorStack_pop(&operatorStack)) != '\0') {
    expression_addChar(&postfixExpression, poppedOperator);
  }

  char* returnString = expression_toString(&postfixExpression);
  expression_delete(&postfixExpression);

  return returnString;
}