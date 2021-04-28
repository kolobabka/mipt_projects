#include "proc.h"
//..............................................................................
//..............................................................................
char* Asm (char** commands, size_t amount)
{
  assert (commands);
  size_t counter = 0;
  size_t check = 0;
  int push_counter = 0;
  char* bytecode = NULL;
  char* start_bytecode = NULL;

  bytecode = (char*) calloc (2 * amount * 8, sizeof (char));
  assert (bytecode);

  start_bytecode = bytecode;

  while (counter < amount)
  {
    check = Recognize_Command (&(commands[counter]), &bytecode, &push_counter);
    if (check != 0)
      return NULL;
    counter++;
  }

  return start_bytecode;
}
//..............................................................................
//..............................................................................
void File_Read_Func (char* buffer, size_t size, char* const text_name)
{
  assert (buffer);
  assert (text_name);
  assert (size);

  FILE* text = fopen (text_name, "r");

  if (text == NULL)
  {
    perror ("File open error:");
    return;
  }

  int reader = fread (buffer, sizeof(char), size, text);
  ferror(text);

  fclose(text);
}
//..............................................................................
//..............................................................................
size_t Count_Strings (char* buffer, size_t size)
{
  assert (buffer);
  assert (size);

  size_t count = 0, flag = 0;

  for (size_t num_count = 0; num_count < size; num_count++)
  {
    if (num_count == size - 1 && (buffer[num_count] == '\n') && flag == 0)
      break;
    if ( (buffer[num_count] == '\n' || buffer[num_count] == '\t' || buffer[num_count] == ' ') && flag == 0)
    {
     continue;
    }
    if (buffer[num_count] == '\n')
    {
      count++;
      flag = 0;
      continue;
    }
    flag ++;
  }

  return count;
}
//..............................................................................
//..............................................................................
void Str_Sep (char* buffer, size_t size, char** strings, size_t num_str)
{
  assert (strings);
  assert (buffer);
  assert (size);
  assert (num_str);

  size_t buf_count = 0, move_ptr = 0, flag_2 = 0;

  for (size_t num_count = 0; num_count < num_str; num_count++)
  {
    move_ptr = 0;
    for (buf_count; buf_count < size; buf_count++)
    {
      if ((buffer[buf_count] == '\n' || buffer[buf_count] == '\t') && flag_2 == 0)
      {
        buf_count += 1;
        num_count -= 1;
        break;
      }
      if (buffer[buf_count] == '\n')
      {
        buffer[buf_count] = '\0';
        strings[num_count] = &(buffer[buf_count]) - move_ptr;
        buf_count += 1;
        flag_2 = 0;
        break;
      }
      flag_2 ++;
      move_ptr ++;
    }
  }
}
//..............................................................................
//..............................................................................
size_t Size_Text (char* const text_name)
{

  assert (text_name);

  struct stat size;
  stat (text_name, &size);

  return size.st_size;
}
//..............................................................................
//..............................................................................
size_t Recognize_Command (char** buf, char** bytecode, int* push_counter)
{
  assert (*buf);
  assert (*bytecode);
  size_t buf_idx = 1;
  size_t check = 0;

  Skip_Trash (buf);
//..............................................................................
//..............................................................................
  if (!(strncmp (*buf, "PUSH ", push_len + 1)))
  {
    printf("\t\t\t***MY V PUSHE***\n");
    **bytecode = 1;
    *bytecode = *bytecode + 1;
    *buf = *buf + push_len;

    while ( !(isdigit(**buf)) && **buf != '\0')
      SINTAX;

    if (**buf == '\0')
    {
      printf("\t\t\t***PUSH WITHOUT NUM***\n");
      return WRONG_PUSH;
    }

    double num = 0;
    sscanf (*buf, "%lg", &num);
    char* transformNum = (char*)(&num);
    for (size_t byte_idx = 0; byte_idx < sizeof (double); byte_idx++)
      *(*bytecode + byte_idx) = transformNum[byte_idx];

    while (isdigit(**buf))
      *buf = *buf + 1;

    while (**buf != '\0')
      SINTAX;

    *bytecode = *bytecode + sizeof (double);
    (*push_counter)++;
    return 0;
  }
  if ((!(strncmp (*buf, "POP\0", pop_len + 1))) || (!(strncmp (*buf, "POP ", pop_len + 1))) || (!(strncmp (*buf, "POP\t", pop_len + 1))))
  {
    if (!(*push_counter))
      return WRONG_PUSH;

    printf("\t\t\t***MY V POPE***\n");
    **bytecode = 2;
    *bytecode = *bytecode + 1;
    *buf = *buf + pop_len;

    while (**buf != '\0')
      SINTAX;
    (*push_counter)--;
    return 0;
  }
  if (!(strncmp (*buf, "ADD ", add_len + 1)) || !(strncmp (*buf, "ADD\0", add_len + 1)) || !(strncmp (*buf, "ADD\t", add_len + 1)))
  {
    if (!(*push_counter))
      return LOW_STACK;
    printf("\t\t\t***MY V ADU***\n");
    **bytecode = 3;
    *bytecode = *bytecode + 1;
    *buf = *buf + add_len;

    while (**buf != '\0')
      SINTAX;
    return 0;
  }
  if (!(strncmp (*buf, "SUB", sub_len)))
  {
    if (!(*push_counter))
      return LOW_STACK;
    printf("\t\t\t***MY V SUBWAYE***\n");
    **bytecode = 4;
    *bytecode = *bytecode + 1;
    *buf = *buf + sub_len;

    while (**buf != '\0')
      SINTAX;
    return 0;
  }
  if (!(strncmp (*buf, "MUL", mul_len)))
  {
    if (!(*push_counter))
      return LOW_STACK;
    printf("\t\t\t***MY V MULANE***\n");
    **bytecode = 5;
    *bytecode = *bytecode + 1;
    *buf = *buf + mul_len;

    while (**buf != '\0')
      SINTAX;
    return 0;
  }
  if (!(strncmp (*buf, "DIV", div_len)))
  {
    if (*push_counter < 2)
      return LOW_STACK;
    printf("\t\t\t***MY V DIVANE***\n");
    **bytecode = 6;
    *bytecode = *bytecode + 1;
    *buf = *buf + div_len;
    return 0;
  }
  if (!(strncmp (*buf, "SQRT", sqrt_len)))
  {
    printf("\t\t\t***MY V KORNE NE PRAVY***\n");
    **bytecode = 7;
    *bytecode = *bytecode + 1;
    *buf = *buf + sqrt_len;

    while (**buf != '\0')
      SINTAX;
    return 0;
  }
  if (!(strncmp (*buf, "SIN", sin_len)))
  {
    printf("\t\t\t***TOTAL SIN***\n");
    **bytecode = 8;
    *bytecode = *bytecode + 1;
    *buf = *buf + sin_len;

    while (**buf != '\0')
      SINTAX;
    return 0;
  }
  if (!(strncmp (*buf, "COS", cos_len)))
  {
    printf("\t\t\t***COSI PISUN***\n");
    **bytecode = 9;
    *bytecode = *bytecode + 1;
    *buf = *buf + cos_len;
    return 0;
  }
  if (!(strncmp (*buf, "IN", in_len)))
  {
    printf("\t\t\t***INOMARKA***\n");
    **bytecode = 10;
    *bytecode = *bytecode + 1;
    *buf = *buf + in_len;
    return 0;
  }
  if (!(strncmp (*buf, "OUT", out_len)))
  {
    **bytecode = 10;
    printf("\t\t\t***OUTIST***\n");
    *bytecode = *bytecode + 1;
    *buf = *buf + out_len;
    return 0;
  }
  if (!(strncmp (*buf, "END", end_len)))
  {
    printf("\t\t\t***THE END***\n");
    **bytecode = 10;
    *bytecode = *bytecode + 1;
    *buf = *buf + end_len;
    return 0;
  }

  printf("\t\t\t***WRONG SINTAKSIS TVOY DIVIZIY***\n");

  return WRONG_COMMAND;

}
//..............................................................................
//..............................................................................
size_t Check_Sintax (char** buf)
{
  assert (*buf);
  if (isalpha(**buf) || ispunct(**buf))
  {
    printf("\t\t\t***WRONG SINTAKSIS TVOY DIVIZIY***\n");
    printf("\t\t\t***[%s]***\n", *buf);
    return 777;
  }
  if (isdigit(**buf))
    return 0;

  *buf = *buf + 1;

  return 0;
}
//..............................................................................
//..............................................................................
void Skip_Trash (char** buf)
{
  assert (*buf);
  while ((isspace (**buf)))
    *buf = *buf + 1;
}
//..............................................................................
//..............................................................................
