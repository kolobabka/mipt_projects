#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>

//-----------------------------------------------------------------------------

void file_write_func (char** strings, size_t num_str, char* const output);
int char_cmp_up (const void *first, const void *second );
int char_cmp_low (const void *first, const void *second );
void str_sep (char* buffer, size_t size, char** strings, size_t num_str);
int count_strings (char* buffer, size_t size);
void file_read_func (char* buffer, size_t size, char* const text_name);
int size_of_text (char* const text_name);

//-----------------------------------------------------------------------------

int main()
{
  char** strings = NULL;
  char* buffer = NULL;
  size_t size = 0, num_str = 0;
  char* const text_name = "text.md";
  char* const output = "output.md";
  char* const output_iverse = "output_iverse.md";

  size = size_of_text(text_name);
  assert (size);

  buffer = (char*) calloc(size, sizeof(char));
  assert (buffer);

  file_read_func (buffer, size, text_name);
  num_str = count_strings(buffer, size);
  assert (num_str);

  strings = (char**) calloc (num_str, sizeof(char*));
  assert (strings);

  str_sep (buffer, size, strings, num_str);

  qsort (strings, num_str, sizeof (char*), char_cmp_low);

  file_write_func (strings, num_str, output);

  qsort (strings, num_str, sizeof (char*), char_cmp_up);

  file_write_func (strings, num_str, output_iverse);

  free (buffer);
  free (strings);

  return 0;
}

//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------

int char_cmp_low (const void *first, const void *second )
{
  assert (first);
  assert (second);

  char **str1 = (char**) first;
  char **str2 = (char**) second;

  size_t char_count_1 = 0;
  size_t char_count_2 = 0;

  while (str1[0][char_count_1] != '\0' && str2[0][char_count_2] != '\0')
  {
    while (ispunct (str1[0][char_count_1]) || isdigit (str1[0][char_count_1]) || isspace (str1[0][char_count_1]))
      char_count_1++;

    while (ispunct (str2[0][char_count_2]) || isdigit (str2[0][char_count_2]) || isspace (str2[0][char_count_2]))
      char_count_2++;

    while (tolower(str1[0][char_count_1]) == tolower(str2[0][char_count_2]) )
    {
      char_count_1++;
      char_count_2++;
    }
    break;
  }

  return (tolower(str1[0][char_count_1]) - tolower(str2[0][char_count_2]));
}

//-----------------------------------------------------------------------------

int char_cmp_up (const void *first, const void *second )
{
  assert (first);
  assert (second);

  char **str1 = (char**) first;
  char **str2 = (char**) second;

  size_t char_count_1 = strlen (str1[0]) - 1;
  size_t char_count_2 = strlen (str2[0]) - 1;

  while (char_count_1 > 0 && char_count_2 > 0)
  {
    while (ispunct (str1[0][char_count_1]) || isdigit (str1[0][char_count_1]) || isspace (str1[0][char_count_1]))
      char_count_1--;

    while (ispunct (str2[0][char_count_2]) || isdigit (str2[0][char_count_2]) || isspace (str2[0][char_count_2]))
      char_count_2--;

    while (tolower(str1[0][char_count_1]) == tolower(str2[0][char_count_2]) )
    {
      char_count_1--;
      char_count_2--;
    }
    break;
  }

  return (tolower(str1[0][char_count_1]) - tolower(str2[0][char_count_2]));
}

void file_write_func (char** strings, size_t num_str, char* const output)
{
  assert (strings);
  assert (output);
  assert (num_str);

  FILE* text = fopen(output, "w");
  assert(text);

  for (int count_str = 0; count_str < num_str; count_str++)
  {
    fwrite (strings[count_str], sizeof (char), strlen (strings[count_str]), text);
    fwrite ("\n", sizeof (char), 1, text);
  }

  fclose(text);
}
