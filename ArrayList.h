#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#ifndef ALDEF
#define ALDEF
#endif // ALDEF

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef union {
     int Int;
     size_t Size_t;
     char Char;
     float Float;
     double Double;
} Type;

typedef struct {
     Type *data;
     size_t size;
     size_t capacity;
} Array;

#define crash assert (a->data != NULL && "Buy more RAM lol")
#define cast (void*)

ALDEF void ArrayInit (Array *a, size_t bytes); // Must use ArrayFree
ALDEF void ArrayAdd (Array *a, Type element);
ALDEF void ArrayClear (Array *a); // Must use ArrayFree
ALDEF Array ArrayClone (Array *a); // Must use ArrayFree
ALDEF Type ArrayGet (Array *a, size_t index);
ALDEF bool ArrayIsEmpty (Array *a);
ALDEF void ArrayRemove (Array *a, size_t index);
ALDEF void ArraySet (Array *a, size_t index, Type element);
ALDEF size_t ArraySize (Array *a);
ALDEF void ArrayFree (Array *a);

void ArrayInit (Array *a, size_t bytes) {
     a->data = malloc (sizeof(Type) * bytes);
     crash;
     a->size = 0;
     a->capacity = bytes;
}

void ArrayAdd (Array *a, Type element) {
     if (a->size == a->capacity) {
          a->capacity *= 2;
          a->data = realloc (a->data, a->capacity * sizeof(Type));
          crash;
     }
     a->data[a->size++] = element;
}

void ArrayClear (Array *a) {
     free (a->data);
     a->data = malloc (sizeof(Type) * a->size);
     a->size = 0;
}

// FIXME: Float and Double elements not getting cloned
Array ArrayClone (Array *a) {
     Array b = {0};
     b.data = malloc (sizeof(Type) * a->size);
     b.capacity = a->capacity;
     for (size_t i = 0; i < a->size; ++i) {
          if (a->data[i].Int != 0) {
               b.data[b.size++].Int = a->data[i].Int;
          }
          if (a->data[i].Size_t != 0) {
               b.data[b.size++].Size_t = a->data[i].Size_t;
          }
          if (a->data[i].Char != 0) {
               b.data[b.size++].Char = a->data[i].Char;
          }
          if (a->data[i].Float != 0.0f) {
               b.data[b.size++].Float = a->data[i].Float;
          }
          if (a->data[i].Double != 0.0) {
               b.data[b.size++].Double = a->data[i].Double;
          }
     }
     return b;
}

Type ArrayGet (Array *a, size_t index) {
     return a->data[index];
}

bool ArrayIsEmpty (Array *a) {
     return a->size == 0;
}

void ArrayRemove (Array *a, size_t index) {
     for (size_t i = index; i < a->size; ++i) {
          a->data[i] = a->data[i+1];
     }
     a->size--;
}

void ArraySet (Array *a, size_t index, Type element) {
     a->data[index] = element;
}

size_t ArraySize (Array *a) {
     return a->size;
}

void ArrayFree (Array *a) {
     free (a->data);
     a->data = NULL;
     a->size = 0;
     a->capacity = 0;
}

#endif // ARRAYLIST_H_
