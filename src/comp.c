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

void removewhitespace(const char* rawcode, char* purecode) {
  printf("Removing whitespace.\n");
  char* pos = rawcode;  //where we are in the code to be parsed
  int right, left;

  while(*pos != '\n') { //end on end of line for this test
    switch((int)pos) {  //kinda dirty cast hack
      printf("%i\n", (int) pos);
      case ' ':
      pos++;  //ignore spaces
      break;

      default:
        *purecode++ = *pos++; //just copy anything else we see
        break;
    }
  }
}

void parse(char* code, DWORD* program) {
  printf("Beginning parsing.\n");
  DWORD* buffer[1024];  //compiled code buffer: 1024 * 32b = 4kB
  int count = 0;        //number of compiled instructions

  char purecode[1024 * 16];  //uncompiled code buffer: 1024 * 16kB * 8b = 256kB
  removewhitespace(code, purecode);
  printf("%s\n", purecode);

  count = 6;  //TEST COUNT
  DWORD test[] = {PUSH, 2, PUSH, 2, ADD, HALT}; //TEST PROGRAM
  
  copyToFile(program, test, count);
  printf("Finished parsing.\n");
}

void copyToFile(DWORD* program, DWORD* test, int count) {
  printf("Copying memory.\n");
  program[0] = count; //pack count into first position
  memcpy(program, test, 6 * sizeof(DWORD));
}

//insert one char into output file
void insertchar(const char input, FILE* file) {
  putc(input, file);
  int subdivisions = sizeof(DWORD) / sizeof(char);
  subdivisions--;
  int i;
  for(i = 0; i < subdivisions; i++) {
    putc((char)0, file);
  }
}

//concatenates directory and filename into one string, or any two strings
char* catstr(char* dir, char* file) {
  //allocate enough space for full filename
  char* fullname = malloc(strlen(dir) + strlen(file) + 2);
  strcpy(fullname, dir);
  strcat(fullname, file);
  return fullname;
}

void compile(char* code, char* outfile) {
  
  printf("Beginning compilation.\n");

  //setup output file
  char* filename = catstr("../bin/", outfile);
  FILE* out = fopen(filename, "w"); //open file for writing
  printf("File opened.\n");
  
  DWORD* program = malloc(sizeof(DWORD) * 1024);
  parse(code, program);

  int count = 6;  //TEST LENGTH
  insertchar((char)count, out);

  fwrite(program, sizeof(DWORD), count, out); //write out to file
  printf("File written.\n");

  fclose(out);  //close file gracefully
  printf("File closed.\n");

  free(program);
  printf("Memory freed.\n");
}

void testCompiler() {
  printf("Running testCompiler().\n");
  
  //ALL code MUST end in newline

  //simple arithmetic tests
  char* sample0 = "2 + 2 \n";
  char* sample1 = "2+2\n2-2\n2*2\n2/2";
  char* sample2 = "2 + 2\n3-1\n4* 3  \n 9/ 3  "; //deliberate awful formatting
  
  compile(sample0, "test.psc");
  printf("Compilation completed.\n");
}

// int main() {
//   printf("Literally the first thing that's happened.\n");
//   testCompiler();

//   return 0;
// }

#endif
