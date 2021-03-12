#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//..............................................................................
enum {
  THATSCOCK,
};
//..............................................................................
#define POISON -666
#define NO_ERRORS 0
#define JOPA 1
#define START_CAP 5
//..............................................................................
typedef struct stack {
  int* buf;
  size_t sz;
  size_t capacity;
} stack_t;
//..............................................................................
typedef struct stack_inform {
  size_t ret_val;
  size_t total_sz;
  int top;
} inform;
//..............................................................................
void ReCalloc (stack_t* stk);
void Stk_Dump (stack_t* stk, inform* stk_inf);
void Stk_Construct (stack* stk, size_t cap);
void Stk_Push (stack_t* stk, int elem, inform* stk_inf);
void Stk_Pop (stack_t* stk, inform* stk_inf);
void Stk_Destruct (stack_t* stk);
//..............................................................................
int main ()
{
  stack_t stk = {NULL, 0, 0};
  Stk_Construct (&stk, START_CAP);
  inform stk_inf = {0, 0, 0};
  int value = 10;

  for (int mult_push = 0; mult_push < 20; mult_push++)
  {
    if (stk_inf.total_sz >= (3 * stk.capacity / 4))
    {
      printf("total_sz = %ld\ncapacity = %ld\n", stk_inf.total_sz, stk.capacity);
      ReCalloc (&stk);
    }


    value++;
  }
  Stk_Push (&stk, value, &stk_inf);

  for (int counter = 0; counter < 10; counter++)
    Stk_Pop (&stk, &stk_inf);


  Stk_Dump (&stk, &stk_inf);

  Stk_Destruct (&stk);

}
//..............................................................................
void Stk_Construct (stack_t* stk, size_t cap)
 {
  assert (cap);

  stk->buf = (int*) calloc (cap, sizeof (int));
  assert (stk->buf != NULL);

  stk->sz = 0;
  stk->capacity = cap;
 }
//..............................................................................
void Stk_Push (stack_t* stk, int elem, inform* stk_inf)
{
  assert (stk != NULL);
  assert (stk_inf != NULL);

  for (int mult_push = 0; mult_push < 20; mult_push++)
  {
    if (stk_inf->total_sz >= (3 * stk->capacity / 4))
    {
      printf("total_sz = %ld\ncapacity = %ld\n", stk_inf->total_sz, stk->capacity);
      ReCalloc (stk);
    }

  stk->buf[stk->sz] = elem;
  stk->sz++;
  elem++;
  stk_inf->total_sz = stk->sz;
  }
}
//..............................................................................
void Stk_Pop (stack_t* stk, inform* stk_inf)
{
  assert (stk);
  assert (stk_inf);


  (stk->sz)--;
  int tmp = stk->buf[(stk->sz)];
  stk->buf[(stk->sz)] = POISON;

  stk_inf->ret_val = tmp;
}
//..............................................................................
void Stk_Destruct (stack_t* stk)
{
  assert (stk != NULL);
  free (stk->buf);
}
//..............................................................................
void Stk_Dump (stack_t* stk, inform* stk_inf)
{
  assert (stk != NULL);
  assert (stk_inf != NULL);

  printf ("Stack [%p]\n", stk);
  printf ("\t{\n");
  printf ("\t Size     = %ld\n", stk->sz);
  printf ("\t Capacity = %ld\n", stk->capacity);
  printf ("\t buf [%p]\n", stk->buf);
  printf ("\t  {\n");
  int print_count = 0;
  while (stk->buf[print_count] != POISON)
  {
    printf ("\t   *[%d]: %d\n", print_count, stk->buf[print_count]);
    print_count++;
  }
  while (print_count < stk_inf->total_sz)
  {
    printf ("\t    [%d]: %d\n", print_count, stk->buf[print_count]);
    print_count++;
  }
  printf ("\t  }\n");
  printf ("\t}\n");
}
//..............................................................................
void ReCalloc (stack_t* stk)
{
  size_t old_cap = stk->capacity;
  TYPE* tmp_buf = NULL;

  stk->capacity *= 2;

  tmp_buf = (TYPE*) realloc (stk->buf, 4*(stk->capacity)*sizeof(TYPE));
  assert (stk);
  stk->buf = tmp_buf;

  for (old_cap; old_cap < stk->capacity; old_cap++)
    stk->buf[old_cap] = 0;
}
//..............................................................................
