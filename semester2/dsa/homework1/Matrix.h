#pragma once

#include <iostream>
#include <utility>
using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

typedef std::pair<std::pair<int, int>, TElem>Triple;
#define NULL_TRIPLE {{-1,-1}, NULL_TELEM}

class MatrixIterator;

class Matrix {
	friend class MatrixIterator;
private:
	int numberLines, numberColums;
	Triple* tripl;
	int capacity, size;
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

	pair<int, int> findPositon(TElem e) const;
	MatrixIterator iterator() const;
	int numberOfZero(int line) const;
	int numberOfNonZeroElems() const;
	~Matrix();

};

