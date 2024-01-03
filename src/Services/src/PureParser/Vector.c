#include <Services/PureParser/Vector.h>
#include <string.h>

Vector *init_vector_(size_t size_of_data) {
  Vector *vector = (Vector *)malloc(sizeof(Vector));

  vector->size = 0;
  vector->capacity = 100;
  vector->size_of_data = size_of_data;
  vector->data = malloc(size_of_data * vector->capacity);

  return vector;
}

void push_back(Vector *vector, void *data) {
  if (vector->size == vector->capacity) {
    vector->capacity *= 2;
    vector->data =
        realloc(vector->data, vector->capacity * vector->size_of_data);
  }
  memcpy((vector->data + vector->size * vector->size_of_data), data,
         vector->size_of_data);
  free(data);
  vector->size++;
}

void *get_by_index(Vector *vector, size_t index) {
  return (vector->data + index * vector->size_of_data);
}

void clear(Vector *vector) {
  free(vector->data);
  free(vector);
}