#pragma once
#include <utility>
//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0
typedef std::pair<std::pair<int, int>, TElem>Triple;
//info.first.first === line
//info.first.second==column
struct Node {
	Triple info;
	int next;
	int prev;
};
class Matrix {

private:
	int lines, columns;
	int first_empty;
	int size;//current occupied
	int capacity;
	int head, tail;
	Node* dllnode;
	void resize();
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	//returns the position of element elem from the Matrix
	std::pair <int, int> positionOf(TElem elem)const;

};
