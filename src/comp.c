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
  struct Node* left;    //left operand
  struct Node* right;    //right operand
} Node;

Node NodeBuilder(int type, int value, Node* left, Node* right) {
  Node o;
  o.type = type;
  if (o.type == INTEGER) o.value = value;
  else o.value = 0;
  o.left = left;
  o.right = right;
  return o;
}

DWORD* parse(char* code) {
  
}

void compile(char* code, char* outfile) {
  
  printf("Beginning compilation.\n");

  //setup filename
  char* start = "../bin/";  //beginning of filename
  char* filename = malloc(strlen(start) + strlen(outfile) + 2);  //allocate enough space for filename
  strcpy(filename, start);
  strcat(filename, outfile);

  FILE* out = fopen(filename, "w"); //open file for writing

  printf("File opened.\n");

  DWORD program[1024];  //program can be up to 1024 * 32 bits = 4kB

  //program = parse(code);
  
  DWORD test[] = {PUSH, 2, PUSH, 2, ADD, HALT}; //TEST PROGRAM
  int count = 6;  //TEST LENGTH

  putc((char)count, out);
  int subdivisions = sizeof(DWORD) / sizeof(char);
  subdivisions--;
  int i;
  for(i = 0; i < subdivisions; i++) {
    putc((char)0, out);
  }

  // copy program length and code/data into program buffer
  memcpy(program, test, count * sizeof(DWORD));

  printf("Memory copied.\n");

  fwrite(program, sizeof(DWORD), count, out); //write out to file

  printf("File written.\n");

  fclose(out);  //close file gracefully

  printf("File closed.\n");
}

void testCompiler() {
  printf("Running testCompiler().\n");
  
  //simple arithmetic tests
  char* sample = "2 + 2\n3-1\n4* 3  \n 9/ 3  "; //deliberate awful formatting
  char* outfile = "test.psc";

  printf("char*s created.\n");
  
  compile(sample, outfile);
  printf("Compilation completed.\n");
}

// int main() {
//   printf("Literally the first thing that's happened.\n");
//   testCompiler();

//   return 0;
// }

#endif
