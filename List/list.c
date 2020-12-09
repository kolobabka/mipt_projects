#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//..............................................................................
//..............................................................................

struct list_t {
  int data;
  struct list_t* next;
  struct list_t* prev;
};

//..............................................................................
//..............................................................................

void Run_to_end (struct list_t** start);
void Run_to_begin (struct list_t** start);
int Deleter (struct list_t** start);
int Print_List(struct list_t** start);
int List_Maker (struct list_t** start, FILE* f);
int Inverse_List (struct list_t** start);


//..............................................................................
//..............................................................................

int main (int argc, char** argv)
{
  int check = 666;
  FILE* f;
  struct list_t* start = NULL;
  start = (struct list_t*) calloc (1, sizeof(struct list_t));
  assert (start != NULL);

  if (argc < 2)
  {
    printf("Usage: <%sfile-to-open\n", argv[0]);
    return -1;
  }

  f = fopen (argv[1], "r");

  if (f == NULL)
  {
    perror ("File open error:");
    return -2;
  }

  check = List_Maker (&start, f);
  assert (check == 0);
  check = Print_List (&start);
  Inverse_List (&start);
  assert (check == 0);
  check = Print_List (&start);
  assert (check == 0);
  check = Deleter (&start);
  assert (check == 0);

}

//..............................................................................
//..............................................................................

int List_Maker (struct list_t** start, FILE* f)
{
  int len_list = 0, check = 0;
  struct list_t* tmp_point = NULL;
  assert (start != NULL);
  fscanf (f,"%d", &len_list);

  for (int counter = 1; counter <= len_list; counter++)
  {
    check = fscanf (f, "%d", &((*start)->data));
    assert (check == 1);
    tmp_point = *start;
    if (counter == len_list)
      break;
    (*start)->next = (struct list_t*) calloc (1, sizeof(struct list_t));
    assert ((*start)->next != NULL);

    *start = (*start)->next;
    (*start)->prev = tmp_point;
  }
  (*start)->next = NULL;

  return 0;
}

//..............................................................................
//..............................................................................

int Print_List (struct list_t** start)
{
  assert (*start != NULL);
  printf("\nPrint list:\n\n");

  Run_to_begin (start);

  while (1)
  {
    printf("%d\n", (*start)->data);
    if ((*start)->next == NULL)
      break;
    *start = (*start)->next;
  }

  printf("\nPrint inversed list:\n\n");

  while (1)
  {
    printf("%d\n", (*start)->data);
    if ((*start)->prev == NULL)
      break;
    *start = (*start)->prev;
  }
  return 0;
}

//..............................................................................
//..............................................................................

int Inverse_List (struct list_t** start)
{
  assert (start != NULL);
  struct list_t* tmp =  NULL;

  Run_to_end (start);

  while (1)
  {
    tmp = (*start)->next;
    (*start)->next = (*start)->prev;
    (*start)->prev = tmp;
    if ((*start)->next == NULL)
      break;
    *start = (*start)->next;
  }
  Run_to_begin (start);

  return 0;
}

//..............................................................................
//..............................................................................

int Deleter (struct list_t** start)
{
  Run_to_end (start);

  while (1)
  {
    if ((*start)->prev == NULL)
      break;
    free ((*start) ->next);
    *start = (*start)->prev;
  }
  free (*start);
  return 0;
}

//..............................................................................
//..............................................................................

void Run_to_begin (struct list_t** start)
{
  while (1)
  {
    if ((*start)->prev == NULL)
      break;
    *start = (*start)->prev;
  }
}

//..............................................................................
//..............................................................................

void Run_to_end (struct list_t** start)
{
  while (1)
  {
    if ((*start)->next == NULL)
      break;
    *start = (*start)->next;
  }
}
