#ifndef _MAIN_H
#define _MAIN_H
#include <stdbool.h>
//program instructions
typedef enum {
  HALT,  //HALT: End program execution.
  PUSH,  //PUSH X: Push DWORD X onto the stack.
  POP,   //POP: Pop top DWORD off the stack.
  ADD,   //ADD: Pop top two DWORDs off of the stack, add them, push result.
  SUB,   //SUB: Pop top two DWORDS off the stack, subtract them, push result.
  MUL,   //MUL: Pop two DWORDS off the stack, multiply them, push result.
  DIV,   //DIV: Pop two DWORDS off the stack, divide them, push result.
  PEEK,  //PEEK: Peek top DWORD off the stack and print.
} InstructionSet;

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned long long QWORD; //this typedef looks ugly af

void run(DWORD[], bool);
void test(void);
#endif
