#include "stack.h"
//..............................................................................
//..............................................................................
stack* Stk_Construct ()
{
  stack* stk = (stack*) calloc (1, sizeof (stack));
  assert (stk);

  stk->buf = (TYPE*) calloc (START_CAP, sizeof (TYPE));
  assert (stk->buf);

  stk->sz = 0;
  stk->capacity = START_CAP;

  for (size_t counter = 0; counter < stk->capacity; counter++)
    stk->buf[counter] = POISON;

  return stk;
}
//..............................................................................
//..............................................................................
size_t Stk_Dump (const stack* stk)
{
  size_t check = 0;
  size_t print_count = 0;
  if (check = Check_Stk (stk))
    return check;

  printf ("Stack [%p]\n", stk);
  printf ("\t{\n");
  printf ("\t Size     = %d\n", stk->sz);
  printf ("\t Capacity = %zu\n", stk->capacity);
  printf ("\t buf [%p]\n", stk->buf);
  printf ("\t  {\n");

  while (stk->buf[print_count] != POISON)
  {
    printf ("\t   *[%zu]: %d\n", print_count + 1, stk->buf[print_count]);
    print_count++;
  }

  while (print_count < stk->capacity)
  {
    printf ("\t    [%zu]: %x\n", print_count + 1, stk->buf[print_count]);
    print_count++;
  }
  printf ("\t  }\n");
  printf ("\t}\n");

  return NO_ERROR;
}
//..............................................................................
//..............................................................................
size_t Stk_Push (stack* stk, TYPE elem)
{
  size_t check = 0;
  if (check = Check_Stk (stk))
    return check;

  if (stk->sz * 2 > stk->capacity)
    ReCalloc (stk);

  stk->buf[stk->sz] = elem;
  stk->sz++;

  if (check = Check_Stk (stk))
    return check;

  return NO_ERROR;
}
size_t Stk_Pop (stack* stk)
{
  size_t check = 0;
  if (check = Check_Stk (stk))
    return check;

  if (stk->sz <= 0)
    return ZERO_SIZE;

  if (stk->sz * 4 < stk->capacity && stk->sz > 20)
    ReCalloc (stk);

  (stk->sz)--;
  stk->buf[(stk->sz)] = POISON;

  if (check = Check_Stk (stk))
    return check;

  return NO_ERROR;
}
//..............................................................................
//..............................................................................
void Stk_Destruct (stack* stk)
{
  free (stk->buf);
}
//..............................................................................
//..............................................................................
size_t ReCalloc (stack* stk)
{
  size_t old_cap = stk->capacity;
  TYPE* tmp_buf = nullptr;

  if (stk->sz * 2 > stk->capacity)
  {
    stk->capacity *= 2;

    tmp_buf = (TYPE*) realloc (stk->buf, (stk->capacity)*sizeof(TYPE)); // not so good
    assert (stk);
    stk->buf = tmp_buf;

    for (old_cap; old_cap < stk->capacity; old_cap++)
      stk->buf[old_cap] = POISON;
  }
  else
  {
    stk->capacity /= 2;

    stk->buf = (TYPE*) realloc (stk->buf, (stk->capacity)*sizeof(TYPE));
    assert (stk);
  }

  return NO_ERROR;
}
//..............................................................................
//..............................................................................
size_t Stk_OK (size_t error, size_t line, const char* func)
{
  switch (error)
  {
    case NULL_STACK:
      printf("\t\t\t***NULL_STACK ON %zu LINE AND IN %s FUNCTION***\n", line, func);
      return NULL_STACK;

    case NULL_BUFFER:
      printf("\t\t\t***NULL_BUFFER ON %zu LINE AND IN %s FUNCTION***\n", line, func);
      return NULL_BUFFER;

    case ZERO_SIZE:
      printf("\t\t\t***WRONG_SIZE ON [%zu] LINE AND IN [%s] FUNCTION***\n", line, func);
      return ZERO_SIZE;

    case SZ_OVERFLOW:
      printf("\t\t\t***SIZE MORE THAN CAPACITY ON %zu LINE AND IN %s FUNCTION***\n", line, func);
      return SZ_OVERFLOW;
  }
  return NO_ERROR;
}
//..............................................................................
//..............................................................................
size_t Check_Stk (const stack* stk)
{
  if (!stk)
    return NULL_STACK;

  if (!(stk->buf))
    return NULL_BUFFER;

  return NO_ERROR;
}
//..............................................................................
//..............................................................................
