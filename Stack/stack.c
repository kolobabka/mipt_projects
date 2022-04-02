#include "stack.h"
//..............................................................................
//..............................................................................
void Command_Recognizer (stack* stk, char command[])
{

}
//..............................................................................
//..............................................................................
void Stack_Start ()
{
  stack* stk = NULL;
  size_t error = 0;
  char command[32] = {};
  printf ("\t\tHello! I'm a week, but really ambitious Stack_Man for\n"
          "\t\ttrue boys. There is still no any helpers, but my owner\n"
          "\t\tcan help you by himself:)\n");

  printf ("Enter your command:");
  while ( (strcmp (command, "stop")) != 0)
  {
    scanf ("%s", command);
    Command_Recognizer (stk, command);
  }
  
  free (stk);
}
//..............................................................................
//..............................................................................
stack* Stk_Construct ()
{
  stack* stk = (stack*) calloc (1, sizeof (stack));
  assert (stk);

  stk->capacity = START_CAP;
  stk->stk_left_canary = CANARY;
  stk->stk_right_canary = CANARY;

  stk->buf = (void*) calloc (START_CAP * sizeof(TYPE) + 2 * sizeof (CANARY), sizeof (char));
  assert (stk->buf);

  *((unsigned long*)(stk->buf)) = CANARY;
  stk->buf = ((unsigned long*)(stk->buf) + 1);
  *(unsigned long*)((TYPE*)(stk->buf) + (stk->capacity)) = CANARY;

  stk->sz = 0;

  for (size_t counter = 0; counter < stk->capacity; counter++)
    ((TYPE*) stk->buf)[counter] = POISON;

  stk->HashSum = Hash(stk);
  return stk;
}
//..............................................................................
//..............................................................................
size_t Stk_Dump (stack* stk)
{
  size_t error = 0;
  size_t print_count = 0;
  if (error = Check_Stk (stk))
  {
    STK_OK;
    return error;
  }

  printf ("Stack [%p]\n", stk);
  printf ("\t{\n");
  printf ("\t Size     = %d\n", stk->sz);
  printf ("\t Capacity = %zu\n", stk->capacity);
  printf ("\t buf [%p]\n", stk->buf);
  printf ("\t LEFT_CANARY = %llX\n", ((unsigned long long*) stk->buf)[-1]);
  printf ("\t RIGHT_CANARY = %llX\n", *(unsigned long long*)((TYPE*)stk->buf + stk->capacity));
  printf ("\t  {\n");

  while ( ((TYPE*) stk->buf)[print_count] != ((TYPE*) stk->buf)[print_count])
  {
    printf ("\t   *[%zu]: %lf\n", print_count, ((TYPE*) stk->buf)[print_count]);
    print_count++;
  }

  while (print_count < stk->capacity)
  {
    printf ("\t    [%zu]: %lf\n", print_count, ((TYPE*) stk->buf)[print_count]);
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
  if (stk->sz + 1 == stk->capacity)
    ReCalloc (stk);

  ((TYPE*) stk->buf)[stk->sz] = elem;
  stk->sz++;

  stk->HashSum = Hash(stk);

  if (check = Check_Stk (stk))
    return check;

  return NO_ERROR;
}
//..............................................................................
//..............................................................................
size_t Stk_Pop (stack* stk)
{
  size_t check = 0;
  if (check = Check_Stk (stk))
    return check;

  if (stk->sz <= 0)
    return ZERO_SIZE;

  if (stk->sz * 2 < stk->capacity && stk->sz > 20)
    ReCalloc (stk);

  (stk->sz)--;
  ((TYPE*) stk->buf)[stk->sz] = POISON;

  stk->HashSum = Hash(stk);

  if (check = Check_Stk (stk))
    return check;

  return NO_ERROR;
}
//..............................................................................
//..............................................................................
void Stk_Destruct (stack* stk)
{
  free ((unsigned long*)(stk->buf) - 1);
}
//..............................................................................
//..............................................................................
size_t ReCalloc (stack* stk)
{
  printf("jepa\n");
  size_t old_cap = stk->capacity;
  void* tmp_buf = NULL;

  if (stk->sz * 2 > stk->capacity)
  {
    stk->capacity *= 2;

    tmp_buf = (void*) realloc ((unsigned long*)(stk->buf) - 1, stk->capacity * sizeof(TYPE) + 2 * sizeof (CANARY));
    assert (tmp_buf);
    stk->buf = (unsigned long*)(tmp_buf) + 1;
    ((unsigned long long*) stk->buf)[stk->capacity*sizeof(TYPE)/sizeof(CANARY)] = CANARY;

    for (old_cap; old_cap < stk->capacity; old_cap++)
    {
      ((TYPE*) stk->buf)[old_cap] = POISON;
        printf("pisya\n");
    }
  }
  else
  {
    stk->capacity /= 2;

    stk->buf = (TYPE*) realloc ((unsigned long*)(stk->buf) - 1, stk->capacity * sizeof(TYPE) + 2 * sizeof (CANARY));
    stk->buf = (unsigned long*)(stk->buf) + 1;
    assert (stk);
    ((unsigned long long*) stk->buf)[stk->capacity*sizeof(TYPE)/sizeof(CANARY)] = CANARY;
  }
  //printf("zdes zakonchil???\n");
  stk->HashSum = Hash(stk);
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

    case HASH_ERROR:
      printf("\t\t\t***HASH WAS CHANGED ON %zu LINE AND IN %s FUNCTION***\n", line, func);
      return HASH_ERROR;

    case CANARIES_ERROR:
      printf("\t\t\t***CANARIES OF STACK WERE DAMAGED ON %zu LINE AND IN %s FUNCTION***\n", line, func);
      return CANARIES_ERROR;
  }
  return NO_ERROR;
}
//..............................................................................
//..............................................................................
size_t Check_Stk (stack* stk)
{
  if (!stk)
    return NULL_STACK;

  if (!(stk->buf))
    return NULL_BUFFER;

  if (stk->stk_left_canary != CANARY)
    return CANARIES_ERROR;

  if (stk->stk_right_canary != CANARY)
    return CANARIES_ERROR;

  if (stk->HashSum != Hash (stk))
  {
    return HASH_ERROR;
  }

  return NO_ERROR;
}
//..............................................................................
unsigned long long Hash (stack* stk)
{
    char * bait_stack_eqvivalent = (char *) stk;

    unsigned long long old_hash = stk->HashSum;
    stk->HashSum = 0;

    unsigned long long new_hash = 0;

    for (int i = 0; i < sizeof (*stk); i++)
    {
        new_hash = ROR (new_hash) + bait_stack_eqvivalent[i];
    }

    char * inception_of_data = (char *) stk->buf - sizeof (CANARY);
    for (size_t i = 0; i < stk->capacity * sizeof (TYPE) + 2 * sizeof (CANARY); i++)
    {
        new_hash = ROR (new_hash) + inception_of_data[i];
    }

    stk->HashSum = old_hash;

    //printf ("%llx %llx \n", old_hash, new_hash);
    return new_hash;
}

unsigned long long ROR (unsigned long long elem)
{
  return (elem >> 1 | elem << 63);
}
//..............................................................................
