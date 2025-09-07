#include "MatrixIterator.h"

	/*
	BC: theta(1)
	WC: theta(n)
	AC: O(n)
	*/
MatrixIterator::MatrixIterator(const Matrix& matrix) : matrix(matrix), pos(0) {
	while (pos < matrix.size && matrix.tripl[pos].second == NULL_TELEM) {
		++pos;
	}
}

	/*
	BC: theta(1)
	WC: theta(1)
	AC: theta(1)
	*/
bool MatrixIterator::valid() const {
	return pos < matrix.size;
}

	/*
	BC: theta(1)
	WC: theta(1)
	AC: theta(1)
	*/
TElem MatrixIterator::getCurrent() {
	if (!valid()) {
		throw std::exception();
	}
	return matrix.tripl[pos].second;
}

	/*
	BC: theta(1)
	WC: theta(n)
	AC: O(n)
	*/
void MatrixIterator::next() {
	do {
		++pos;
	} while (pos < matrix.size && matrix.tripl[pos].second == NULL_TELEM);
}