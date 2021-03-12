#include "stack.h"
//..............................................................................
//..............................................................................
int main ()
{
  stack* stk = NULL;
  size_t error = 0;

  stk = Stk_Construct ();
  assert (stk && "Lack of memory!!! Attention!");

  for (TYPE i = 0; i < 1488; i++)
  {
    error = Stk_Push (stk, i);
    STK_OK;
  }

  for (TYPE i = 0; i < 1400; i++)
  {
    error = Stk_Pop (stk);
    STK_OK;
  }

  error = Stk_Dump (stk);
  STK_OK;

  Stk_Destruct (stk);

  printf("\t\t\t***VSE OK***\n");
  free (stk);
  return 0;
}
//..............................................................................
//..............................................................................
