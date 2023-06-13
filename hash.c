#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "hash.h"

#define SIGN_COMPARISION(a, b) a > b ? 1 : -1

int h_1(int key)
{
  return key % M;
}

int h_2(int key)
{
  return floor(M * (key * 0.9 - floor(key * 0.9)));
}

void initialize_hash_table(int table[])
{
  for (size_t i = 0; i < M; i++)
    table[i] = AVALIABLE;
}

void insert(int key, int t1[], int t2[])
{
  int primary_hash_pos = h_1(key);

  if (t1[primary_hash_pos] == key) // if key is already on table 1
    return;

  if (t1[primary_hash_pos] == REMOVED || t1[primary_hash_pos] == AVALIABLE) // if key is not on table 1
    t1[primary_hash_pos] = key;
  else // if key is not on table 1 and position is occupied
  {
    int collision_pos = h_2(t1[primary_hash_pos]);
    t2[collision_pos] = t1[primary_hash_pos];
    t1[primary_hash_pos] = key;
  }
}

// function to compare keys for sort
int comp_func(const void *a, const void *b)
{
  char *a_copy = strdup(*(char **)a); // don't modify original string
  char *b_copy = strdup(*(char **)b);

  int a_key = atoi(strtok(a_copy, ",")); // get first field
  int b_key = atoi(strtok(b_copy, ","));

  free(a_copy);
  free(b_copy);

  return SIGN_COMPARISION(a_key, b_key);
}

void print_table(int t1[], int t2[])
{
  int result_count = 0;

  char **formatted_entries = malloc(sizeof(char *) * M);
  memset(formatted_entries, 0, sizeof(char *) * M);

  if (formatted_entries == NULL)
  {
    printf("Error allocating memory");
    exit(1);
  }

  for (int i = 0; i < M; i++)
  {
    if ((t1[i] == AVALIABLE || t1[i] == REMOVED) && (t2[i] == AVALIABLE || t2[i] == REMOVED))
      continue;

    char *formatted_entry = malloc(sizeof(char) * MAX_BUFFER_PER_LINE);

    if (formatted_entry == NULL)
    {
      printf("Error allocating memory");
      exit(1);
    }

    if (t1[i] != AVALIABLE && t1[i] != REMOVED)
      snprintf(formatted_entry, MAX_BUFFER_PER_LINE, "%d,T1,%d", t1[i], i);
    else
      snprintf(formatted_entry, MAX_BUFFER_PER_LINE, "%d,T2,%d", t2[i], i);

    formatted_entries[result_count++] = formatted_entry;
  }

  // sort by first field
  qsort(formatted_entries, result_count, sizeof(char *), comp_func);

  for (int i = 0; i < result_count; i++)
  {
    printf("%s\n", formatted_entries[i]);
    free(formatted_entries[i]);
  }

  free(formatted_entries);
}

void remove_item(int key, int t1[], int t2[])
{
  int t1_pos = h_1(key);
  int t2_pos = h_2(key);

  if (t1[t1_pos] == key)
    t1[t1_pos] = REMOVED;
  else if (t2[t2_pos] == key)
    t2[t2_pos] = REMOVED;
}

int find(int key, int t1[], int t2[])
{
  int primary_hash_pos = h_1(key);
  int secondary_hash_pos = h_2(key);

  if (t1[primary_hash_pos] == AVALIABLE)
    return AVALIABLE;

  if (t1[primary_hash_pos] == key)
    return primary_hash_pos;

  if (t2[secondary_hash_pos] == key)
    return secondary_hash_pos;

  return AVALIABLE;
}