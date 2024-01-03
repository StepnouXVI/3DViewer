#ifndef _VECTOR_H
#define _VECTOR_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
  void *data;
  size_t size_of_data;

  size_t size;
  size_t capacity;
} Vector;

#define create_vector(type) init_vector_(sizeof(type));
Vector *init_vector_(size_t size_of_data);

void push_back(Vector *vector, void *data);
void *get_by_index(Vector *vector, size_t index);
void clear(Vector *vector);

#endif  // _VECTOR_H