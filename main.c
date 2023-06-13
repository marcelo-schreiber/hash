#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

int main(void)
{
  int table_1[M], table_2[M];

  initialize_hash_table(table_1);
  initialize_hash_table(table_2);

  int key = 0;
  char op = ' ';

  while (scanf("%c %d\n", &op, &key) != EOF)
  {
    if (op == 'i')
      insert(key, table_1, table_2);
    else if (op == 'r')
      remove_item(key, table_1, table_2);
    else
      printf("Invalid operation %c\n", op);
  }

  print_table(table_1, table_2);

  return 0;
}