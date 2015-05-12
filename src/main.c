#include <stdio.h>
#include <stdbool.h>

//program instructions
typedef enum {
  PUSH,  //PUSH X: Push DWORD X onto the stack.
  POP,  //POP: Pop top DWORD off the stack.
  ADD,  //ADD: Pop top two DWORDs off of the stack, add them, push result.
  SUB,  //SUB: Pop top two DWORDS off the stack, subtract them, push result.
  MUL, //MUL: Pop two DWORDS off the stack, multiply them, push result.
  DIV,  //DIV: Pop two DWORDS off the stack, divide them, push result.
  PEEK, //PEEK: Peek top DWORD off the stack and print.
  HALT   //HALT: End program execution.
} InstructionSet;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;

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
      int x = stack[sp--];
      int y = stack[sp--];
      stack[++sp] = x + y;
      if(debug) printf("**Added %i and %i and pushed %i.\n", x, y, (int)stack[sp]);
      break;
    }

    case SUB: {
      int x = stack[sp--];
      int y = stack[sp--];
      stack[++sp] = x - y;
      if(debug) printf("**Subtracted %i and %i and pushed %i.\n", x, y, (int)stack[sp]);
      break;
    }

    case MUL: {
      int x = stack[sp--];
      int y = stack[sp--];
      stack[++sp] = x * y;
      if(debug) printf("**Multiplied %i and %i and pushed %i.\n", x, y, (int)stack[sp]);
      break;
    }

    case DIV: {
      int x = stack[sp--];
      int y = stack[sp--];
      stack[++sp] = x / y;
      if(debug) printf("**Divided %i by %i and pushed %i.\n", x, y, (int)stack[sp]);
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
    cycles++;
    if(debug) printf("\nBegin cycle %i\n", cycles);
    eval(program);
  }

  printf("\n\n***Closing PSVM...\n");
  printf("***VM ran for %i cycles.\n", cycles);
  dumpStack();
}

int main() {
  DWORD test[] = {
    PUSH, 1,
    PUSH, 2,
    PUSH, 2,
    ADD,
    PEEK,
    PUSH, 4,
    ADD,
    SUB,
    PUSH, 2,
    PUSH, 7,
    PUSH, 9,
    MUL,
    DIV,
    HALT
  };

  run(test, true);

  return 0;
}
