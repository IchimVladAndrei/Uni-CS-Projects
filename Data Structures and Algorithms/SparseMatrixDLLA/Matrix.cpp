#include "Matrix.h"
#include <exception>
using namespace std;

//BC=WC=AC= theta(capacity)
void Matrix::resize()
{

	Node* temp = new Node[this->capacity * 2];
	for (int i = 0; i < this->capacity; i++)
		temp[i] = this->dllnode[i];

	for (int i = this->capacity; i < this->capacity * 2 - 1; i++)
	{
		temp[i].prev = i - 1;
		temp[i].next = i + 1;
		temp[i].info.second = NULL_TELEM;

	}

	temp[this->capacity * 2 - 1].next = -1;
	this->dllnode = temp;
	this->first_empty = this->capacity;
	this->capacity = this->capacity * 2;


}
//BC=WC=AC=theta(capacity)
Matrix::Matrix(int nrLines, int nrCols) {

	this->capacity = 10;
	this->columns = nrCols;
	this->lines = nrLines;
	this->head = this->tail = -1;
	this->size = 0;
	this->dllnode = new Node[this->capacity];
	this->first_empty = 0;
	this->dllnode[first_empty].prev = -1;
	this->dllnode[first_empty].next = 1;
	this->dllnode[first_empty].info.second = NULL_TELEM;
	int i;
	for (i = 1; i < this->capacity - 1; i++) {
		this->dllnode[i].prev = i - 1;
		this->dllnode[i].next = i + 1;
		this->dllnode[i].info.second = NULL_TELEM;
	}

	this->dllnode[this->capacity - 1].prev = i - 1;
	this->dllnode[this->capacity - 1].next = -1;
	this->dllnode[this->capacity - 1].info.second = NULL_TELEM;
}
//BC=theta(1)=when the element searched is on the first row and first column
//WC=theta(size)=when the element searched is not found 
//Overall=O(size)
TElem Matrix::element(int i, int j) const {
	if (i<0 || j<0 || i>this->lines || j>this->columns)
		throw exception();
	int current = this->head;
	while (current != -1 && this->dllnode[current].info.first.first < i)
		current = this->dllnode[current].next;

	if (this->dllnode[current].info.first.first == i)
		while (current != -1 && this->dllnode[current].info.first.first == i && this->dllnode[current].info.first.second < j)
			current = this->dllnode[current].next;
	if (current != -1 && this->dllnode[current].info.first.first == i && this->dllnode[current].info.first.second == j)
		return this->dllnode[current].info.second;
	return NULL_TELEM;
}
//BC=theta(1)=when telem is !=null and we add the node on a smaller pos than i   
//WC=theta(size)=when we modify any other node
//Overall=O(size)
TElem Matrix::modify(int i, int j, TElem e) {
	if (i<0 || j<0 || i>this->lines || j>this->columns)
		throw exception();

	TElem temp = this->element(i, j);

	if (temp != NULL_TELEM && e != NULL_TELEM) {
		Triple nou;
		nou.first.first = i;
		nou.first.second = j;
		nou.second = e;

		int current = this->head;
		int pos = 0;
		while (current != -1 && pos < this->size) {
			if (this->dllnode[current].info.first.first > i)
				break;
			if (this->dllnode[current].info.first.first == i) {
				if (this->dllnode[current].info.first.second >= j)
					break;
			}
			current = this->dllnode[current].next;
			pos++;
		}
		this->dllnode[current].info = nou;
	}
	else if (temp != NULL_TELEM && e == NULL_TELEM) {
		int current = this->head;
		int pos = 0;
		while (current != -1 && pos < this->size) {
			if (this->dllnode[current].info.first.first > i)
				break;
			if (this->dllnode[current].info.first.first == i) {
				if (this->dllnode[current].info.first.second >= j)
					break;
			}
			current = this->dllnode[current].next;
			pos++;
		}

		if (current != -1) {
			if (current == this->head)
			{
				if (this->head == this->tail)
				{
					this->head = -1;
					this->tail = -1;
				}
				else {
					this->head = this->dllnode[this->head].next;
					this->dllnode[this->head].prev = -1;

				}
			}
			else
			{
				if (current == this->tail)
				{
					this->tail = this->dllnode[current].prev;
					this->dllnode[this->tail].next = -1;
				}
				else {
					this->dllnode[this->dllnode[current].next].prev = this->dllnode[current].prev;
					this->dllnode[this->dllnode[current].prev].next = this->dllnode[current].next;
				}
			}
		}

		this->dllnode[current].next = this->first_empty;
		this->dllnode[this->first_empty].prev = current;
		this->first_empty = current;
		this->size--;


	}
	else if (temp == NULL_TELEM && e != NULL_TELEM) {
		int current = this->head;
		int pos = 0;
		while (current != -1 && pos < this->size) {
			if (this->dllnode[current].info.first.first > i)
				break;
			if (this->dllnode[current].info.first.first == i) {
				if (this->dllnode[current].info.first.second >= j)
					break;
			}
			current = this->dllnode[current].next;
			pos++;
		}
		if (this->first_empty == -1)
			this->resize();
		int nnod = this->first_empty;
		this->first_empty = this->dllnode[this->first_empty].next;
		this->dllnode[nnod].next = -1;
		this->dllnode[nnod].prev = -1;

		Triple nou;
		nou.first.first = i;
		nou.first.second = j;
		nou.second = e;
		this->dllnode[nnod].info = nou;
		if (this->head == -1)
		{
			this->head = nnod;
			this->tail = nnod;

		}
		else if (current == this->head)
		{
			//before head
			this->dllnode[nnod].next = this->head;
			this->dllnode[nnod].prev = nnod;
			this->head = nnod;
		}
		else if (current == -1) {
			//after tail
			this->dllnode[nnod].prev = this->tail;
			this->dllnode[this->tail].next = nnod;
			this->tail = nnod;
		}
		else {
			//middle
			this->dllnode[nnod].next = current;
			this->dllnode[nnod].prev = this->dllnode[current].prev;
			this->dllnode[this->dllnode[current].prev].next = nnod;
			this->dllnode[current].prev = nnod;

		}
		this->size++;

	}

	return temp;
}

//BC=theta(1)=when the elem is the first node,
//WC=theta(size)= when the elem is not found
pair<int, int> Matrix::positionOf(TElem elem) const
{
	int current = this->head;
	while (current != -1) {
		if (this->dllnode[current].info.second == elem)
			return make_pair(dllnode[current].info.first.first, dllnode[current].info.first.second);
		current = this->dllnode[current].next;
	}
	return make_pair(-1, -1);
}

//BC=WC=AC= theta(1)
int Matrix::nrLines() const {

	return this->lines;
}

//BC=WC=AC= theta(1)
int Matrix::nrColumns() const {

	return this->columns;
}
