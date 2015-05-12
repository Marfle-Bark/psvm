#ifndef _COMP_C
#define _COMP_C

#include <stdio.h>
#include "main.h"

typedef enum {
  INTEGER,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE
} NodeTypes;

typedef struct Node {
  int type; //from NodeTypes
  int value;
  struct Node* x;    //operand x
  struct Node* y;    //operand y
} Node;

Node NodeBuilder(int type, int value, Node* x, Node* y) {
  Node o;
  o.type = type;
  if (o.type != INTEGER) o.value = value;
  else o.value = 0;
  o.x = x;
  o.y = y;
  return o;
}

int main() {
  // test();

  //simple arithmetic tests
  char* sample1 = "2 + 2";
  char* sample2 = "5 - 1";
  char* sample3 = "3 * 4";
  char* sample4 = "6 / 3";



  return 0;
}

#endif
