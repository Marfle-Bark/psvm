#ifndef _MAIN_C
#define _MAIN_C

#include <stdio.h>
#include <stdbool.h>
#include "main.h"

int ip = 0;           //instruction pointer
int sp = -1;          //stack pointer
DWORD stack[256];     //256-int stack
bool running = true;  //"is the VM running?"
bool debug = false;   //enable debug statements

char* getInstruction(int instr) {
  switch(instr) {
    case PUSH:  return "PUSH";
    case POP:   return "POP";
    case ADD:   return "ADD";
    case SUB:   return "SUB";
    case MUL:   return "MUL";
    case DIV:   return "DIV";
    case PEEK:  return "PEEK";
    case HALT:  return "HALT";
    default:    return "ERROR";
    }
}

void dumpStack() {
  printf("***Stack trace:\n");
  while(sp > -1)
    printf("%i: %i\n", sp--, (int)stack[sp]);
  printf("\n");
}

//evaluate instruction
void eval(DWORD code[]) {
  int instr = (int)code[ip];
  if(debug) printf("*Evaluating instruction %s...\n", getInstruction(instr));

  switch(instr) {

    case PUSH: {
      stack[++sp] = code[++ip];
      if(debug) printf("**Pushed %i onto the stack.\n", (int)stack[sp]);
      break;
    }

    case ADD: {
      int left = stack[sp--];
      int right = stack[sp--];
      stack[++sp] = left + right;
      if(debug) printf("**Added %i and %i and pushed %i.\n", left, right, (int)stack[sp]);
      break;
    }

    case SUB: {
      int left = stack[sp--];
      int right = stack[sp--];
      stack[++sp] = left - right;
      if(debug) printf("**Subtracted %i and %i and pushed %i.\n", left, right, (int)stack[sp]);
      break;
    }

    case MUL: {
      int left = stack[sp--];
      int right = stack[sp--];
      stack[++sp] = left * right;
      if(debug) printf("**Multiplied %i and %i and pushed %i.\n", left, right, (int)stack[sp]);
      break;
    }

    case DIV: {
      int left = stack[sp--];
      int right = stack[sp--];
      stack[++sp] = left / right;
      if(debug) printf("**Divided %i bright %i and pushed %i.\n", left, right, (int)stack[sp]);
      break;
    }

    case POP: {
      if(debug) printf("**Popped %i.\n", (int)stack[sp--]);
      break;
    }

    case PEEK: {
      if(debug) printf("**Peeked %i.\n", (int)stack[sp]);
      break;
    }

    case HALT: {
      running = false;
      if(debug) printf("**Halting.\n");
      break;
    }

  }
  ip++; //increment IP at end of eval()
}

void run(DWORD program[], bool enableDebug) {
  debug = enableDebug;

  printf("\n\n***Launching PSVM...\n\n\n");
  
  int cycles = 0;
  while (running) {
    if(debug) printf("\nBegin cycle %i\n", ++cycles);
    eval(program);
  }

  printf("\n\n***Closing PSVM...\n");
  printf("***VM ran for %i cycles.\n", cycles);
  dumpStack();
}

void testVM() {
  
  
  // DWORD test[] = {
  //   PUSH, 1,
  //   PUSH, 2,
  //   PUSH, 2,
  //   ADD,
  //   PEEK,
  //   PUSH, 4,
  //   ADD,
  //   SUB,
  //   PUSH, 2,
  //   PUSH, 7,
  //   PUSH, 9,
  //   MUL,
  //   DIV,
  //   HALT
  // };

  printf("\nPSVM is running in Test Mode!\n");

  FILE* testfile = fopen("test.psc", "r");
  
  int count = (int) getc(testfile);

  //burn blank bytes before code starts
  int subdivisions = sizeof(DWORD) / sizeof(char);
  subdivisions--;
  int i;
  for(i = 0; i < subdivisions; i++) {
  }
  
  printf("Count = %i.", count);
  DWORD test[count];

  fread(test, sizeof(DWORD), count, testfile);

  run(test, true);
}

int main() {
  testCompiler();
  testVM();

  return 0;
}

#endif
