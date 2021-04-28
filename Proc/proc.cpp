#include <proc.h>

void file_read_func (char* buffer, size_t size, char* const text_name)
{
  assert (buffer);
  assert (text_name);
  assert (size);

  FILE* text = fopen(text_name, "r");
  assert(text);

  int reader = fread (buffer, sizeof(char), size, text);
  ferror(text);

  fclose(text);
}

//-----------------------------------------------------------------------------

int count_strings (char* buffer, size_t size)
{
  assert (buffer);
  assert (size);

  size_t count = 0, flag = 0;

  for (size_t num_count = 0; num_count < size; num_count++)
  {
    if (num_count == size - 1 && (buffer[num_count] == '\n') && flag == 0)
      break;
    if ( (buffer[num_count] == '\n' || buffer[num_count] == '\t' || buffer[num_count] == ' ' || isdigit (buffer[num_count]) || ispunct (buffer[num_count])) && flag == 0)
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

//-----------------------------------------------------------------------------

void str_sep (char* buffer, size_t size, char** strings, size_t num_str)
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
      if ((buffer[buf_count] == '\n' || buffer[buf_count] == '\t' || buffer[buf_count] == ' ' || isdigit (buffer[buf_count]) || ispunct (buffer[buf_count]))  && flag_2 == 0)
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

//-----------------------------------------------------------------------------

int size_of_text (char* const text_name)
{
  assert (text_name);

  struct stat size;
  stat (text_name, &size);

  return size.st_size;
}
