#pragma once
#include "domain.h"
#include <cstdlib>
//size -----length
		//capacity-----capacity
		//start----initial_capacity
template <class TElem>
class DynamicArray {
private:
	TElem* elements;
	int size;
	int capacity;
	int start;

	/// <summary>
	/// Resizes the dynamic arrray correspongdly
	/// </summary>
	void Resize() {
		TElem* temp;
		this->capacity = this->capacity * 2;
		temp = new TElem[this->capacity];
		for (int i = 0; i < this->size; i++) {
			temp[i] = this->elements[i];
		}
		delete[] this->elements;
		this->elements = temp;
	}

	/// <summary>
	/// Removes everything on the dynamic arrray
	/// </summary>
	void Clear() {
		this->size = 0;
		TElem* temp;
		this->capacity= this->start;
		temp = new TElem[this->capacity];
		for (int i = 0; i < this->size; i++)
			temp[i] = this->elements[i];
		delete[] this->elements;
		this->elements = temp;
	}

public:
	DynamicArray() {}
	/// <summary>
	/// initialiazes the dynamic array with start values
	/// </summary>
	/// <param name="capacity"></param>
	DynamicArray(int capacity)
	{
		this->capacity = capacity;
		this->size = 0;
		this->start = capacity;
		this->elements = new TElem[capacity];
	}
	/// <summary>
	/// destructor
	/// </summary>
	~DynamicArray() {
		delete[]this->elements;
	}
	void Add(const TElem& element){
		
		if (this->size == this->capacity)
			Resize();
		this->elements[this->size++] = element;
	}
	/// <summary>
	/// deltes an telem from the a certain position by shifting
	/// </summary>
	/// <param name="pos"></param>
	void Delete(int pos) {
		if (this->size == 1)
			Clear();
		else {
			for (int i = pos; i < this->size - 1; i++)
				this->elements[i] = this->elements[i + 1];

			this->size--;
		}
	}
	/// <summary>
	/// updates in certain position a set telem
	/// </summary>
	/// <param name="element"></param>
	/// <param name="pos"></param>
	void Update(const TElem& element, int pos) {
		this->elements[pos] = element;
	}
	/// <summary>
	/// returns the size of dynamic array
	/// </summary>
	/// <returns></returns>
	int get_size_da() {
		return this->size;
	}
	/// <summary>
	/// override of [] operator
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	TElem& operator [] (int pos) {
		return this->elements[pos];
	}
	/// <summary>
	/// overides the equal operator
	/// </summary>
	/// <param name="arr"></param>
	/// <returns></returns>
	DynamicArray& operator=(const DynamicArray& arr) {
		if (this == &arr)
			return *this;
		if (arr.capacity == 0)
			Clear();
		this->capacity = arr.capacity / 2;
		Resize();
		memcpy(this->elements, arr.elements, sizeof(TElem) * arr.capacity);
		return *this;
	}
};