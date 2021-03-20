#include "proc.h"

int main (int argc, char** argv)
{
  char** commands = NULL;
  char* buffer = NULL;
  size_t size = 0, num_str = 0;
  FILE* in = NULL;
  char* bytecode = NULL;

  size = Size_Text (argv[1]);
  assert (size);

  buffer = (char*) calloc(size, sizeof(char));
  assert (buffer);

  File_Read_Func (buffer, size, argv[1]);
  num_str = Count_Strings (buffer, size);
  assert (num_str);

  commands = (char**) calloc (num_str, sizeof(char*));
  assert (commands);

  Str_Sep (buffer, size, commands, num_str);

  bytecode = Asm (commands, num_str);
  if (!bytecode)
  {
    printf("NAM PIZDEC\n");
    return -666;
  }

  for (int i = 0; i < 2 * num_str * 8; i++)
    printf("%d", bytecode[i]);
  printf("\n");

  free (bytecode);
  free (buffer);
  free (commands);


}
