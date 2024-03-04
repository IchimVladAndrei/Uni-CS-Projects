#pragma once
#include "domain.h"
typedef Offer TElem;

typedef struct {
	TElem* data;
	int count, max_len;
}DynamicArray;

/// <summary>
/// This function creates a dynamic array
///  </summary>
/// <param name="capacity">nr of elements in the DA</param>
/// <returns>the DA</returns>
DynamicArray* createDA(int capacity);
/// <summary>
/// This function destroys DA
/// </summary>
/// <param name="array">The array to be destroyed </param>
void destroy(DynamicArray* array);
/// <summary>
/// This function adds the TElem to the DA
/// </summary>
/// <param name="array">From what array</param>
/// <param name="telem"></param>
void add_TElem(DynamicArray* array, TElem telem);

/// <summary>
/// This function removes an TElem from DA
/// </summary>
/// <param name="array">From what array</param>
/// <param name="pos">at what position is the TElem</param>
void delete_TElem(DynamicArray* array, int pos);

/// <summary>///This function updates an TElem from DA
///</summary>/// <param name="array">From what array</param>/// <param name="TElem"></param>/// <param name="pos">at what position is the TElem</param>
void update_TElem(DynamicArray* array, TElem telem, int pos);