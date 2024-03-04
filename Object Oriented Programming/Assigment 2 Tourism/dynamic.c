#pragma once
#include "dynamic.h"
#include <stdlib.h>

DynamicArray* createDA(int capacity)
{
	DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
	//space to be alloc
	if (arr == NULL)
		return NULL;
	arr->max_len = capacity;
	arr->count = 0;

	arr->data = (TElem*)malloc(capacity * sizeof(TElem));
	if (arr->data == NULL)
		return NULL;
	return arr;
}

void destroy(DynamicArray* array)
{
	if (array == NULL)
		return;
	free(array->data);
	array->data = NULL;
	free(array);

}

void resize(DynamicArray* array)
{
	array->data = (TElem*)(realloc(array, sizeof(TElem) * array->max_len * 2));
	array->max_len = array->max_len * 2;
}

void add_TElem(DynamicArray* array, TElem telem)
{
	if (array == NULL)
		return;
	if (array->data == NULL)
		return;
	//resize if we need;
	if (array->max_len == array->count)
		resize(array);
	array->data[array->count] = telem;
	array->count++;
}

void delete_TElem(DynamicArray* array, int pos)
{
	for (int i = pos; i <= array->count - 1; i++)
		array->data[i] = array->data[i + 1];
	array->count--;
}

void update_TElem(DynamicArray* array, TElem telem, int pos)
{
	array->data[pos] = telem;
}
