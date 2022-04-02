#pragma once
//..............................................................................
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
//..............................................................................
#define POISON NAN
//..............................................................................
enum TypeError { // TypeError::NO_ERROR

    NO_ERROR = 0,
    NULL_STACK,
    NULL_BUFFER,
    ZERO_SIZE,
    SZ_OVERFLOW,
    CANARIES_ERROR,
    HASH_ERROR

};
//..............................................................................
typedef double TYPE; // data_t
//..............................................................................
static const size_t START_CAP = 4;
//const TYPE POISON = nan; //0xBADDEAD;
static const unsigned long long CANARY = 0xBEDDEADBEDDEAD;

//..............................................................................
typedef struct stack {
  unsigned long long stk_left_canary;
  void* buf;
  int sz;
  size_t capacity;
  unsigned long long HashSum;
  unsigned long long stk_right_canary;
}stack;
//..............................................................................
void Stack_Start ();
size_t ReCalloc (stack* stk);
size_t Stk_Dump (stack* stk);
stack* Stk_Construct ();
size_t Stk_Push (stack* stk, TYPE elem);
size_t Stk_Pop (stack* stk);
void Stk_Destruct (stack* stk);
size_t Stk_OK (size_t error, size_t line, const char* func);
size_t Check_Stk (stack* stk);
unsigned long long ROR (unsigned long long elem);
unsigned long long Hash (stack* stk);
//..............................................................................

#define STK_OK if(Stk_OK(error,__LINE__,__FUNCTION__)) return 0
