#pragma once
//..............................................................................
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//..............................................................................
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
typedef int TYPE; // data_t
//..............................................................................
const size_t START_CAP = 20;
const TYPE POISON = 0xBADDEAD;
//..............................................................................
struct stack {
  TYPE* buf;
  int sz;
  size_t capacity;
};
//..............................................................................
size_t ReCalloc (stack* stk);
size_t Stk_Dump (const stack* stk);
stack* Stk_Construct ();
size_t Stk_Push (stack* stk, TYPE elem);
size_t Stk_Pop (stack* stk);
void Stk_Destruct (stack* stk);
size_t Stk_OK (size_t error, size_t line, const char* func);
size_t Check_Stk (const stack* stk);
//..............................................................................

#define STK_OK if(Stk_OK(error,__LINE__,__FUNCTION__)) return 0
