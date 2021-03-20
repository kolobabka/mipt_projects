#pragma once
//..............................................................................
//..............................................................................
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
//..............................................................................
//..............................................................................
enum Errors {
  LOW_STACK = 666,
  WRONG_POP = 228,
  WRONG_COMMAND = 1488,
  WRONG_PUSH = 777
};
//..............................................................................
//..............................................................................
enum Commands {
  PUSH,
  POP ,
  ADD ,
  SUB ,
  MUL ,
  DIV ,
  SQRT,
  SIN ,
  COS ,
  IN  ,
  OUT ,
  END ,
};
//..............................................................................
//..............................................................................
const size_t push_len =  strlen ("PUSH");
const size_t pop_len  =  strlen ("POP");
const size_t add_len  =  strlen ("ADD");
const size_t sub_len  =  strlen ("SUB");
const size_t mul_len  =  strlen ("MUL");
const size_t div_len  =  strlen ("DIV");
const size_t sqrt_len =  strlen ("SQRT");
const size_t sin_len  =  strlen ("SIN");
const size_t cos_len  =  strlen ("COS");
const size_t in_len   =  strlen ("IN");
const size_t out_len  =  strlen ("OUT");
const size_t end_len  =  strlen ("END");
//..............................................................................
//..............................................................................
void Str_Sep (char* buffer, size_t size, char** strings, size_t num_str);
void File_Read_Func (char* buffer, size_t size, char* const text_name);
size_t Count_Strings (char* buffer, size_t size);
size_t Size_Text (char* const text_name);
char* Asm (char** commands, size_t amount);
size_t Recognize_Command (char** buf, char** bytecode, int* push_counter);
size_t Check_Sintax (char** buf);
void Skip_Trash (char** buf);
//..............................................................................
//..............................................................................
#define SINTAX if (Check_Sintax (buf)) return 42
//..............................................................................
//..............................................................................
