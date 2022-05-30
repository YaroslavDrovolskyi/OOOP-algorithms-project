#include "ConstraintMatrix.h"
#include <cassert>
#include <iostream>
#include <exception>

template<typename T>
ConstraintMatrix<T>::ConstraintMatrix(std::size_t rows, std::size_t cols) :
	rows(rows), cols(cols)

{


}

template<typename T>
void ConstraintMatrix<T>::appendRow(const std::vector<T>& new_row) {
	if (this->cols != 0) {
		assert(new_row.size() == this->cols);
	}
	else {
		this->cols = new_row.size();
	}

	matrix.push_back(new_row);

	this->rows++;
}

template<typename T>
void ConstraintMatrix<T>::appendCol(const std::vector<T>& new_col) {
	if (this->rows != 0) {
		assert(new_col.size() == this->rows);
	}
	else {
		this->rows = new_col.size();
		this->matrix.resize(new_col.size());
	}
	

	for (std::size_t i = 0; i < rows; i++) {
		matrix[i].push_back(new_col[i]);
	}

	this->cols++;
}

template<typename T>
std::size_t ConstraintMatrix<T>::nRows() const {
	return this->rows;
}

template<typename T>
std::size_t ConstraintMatrix<T>::nCols() const {
	return this->cols;
}

template<typename T>
T& ConstraintMatrix<T>::item(std::size_t i, std::size_t j) {
	return matrix[i][j];
}

template<typename T>
std::vector<T> ConstraintMatrix<T>::getCol(std::size_t index) const {
	assert(index < nCols());
	std::vector<T> col;

	for (std::size_t i = 0; i < nRows(); i++) {
		col.push_back(matrix[i][index]);
	}

	return col;
}



/**
	\param[in, out] beta is vector-column B in equation system A*X = B

*/
template <typename T>
void ConstraintMatrix<T>::makeJordanGaussElimination(std::size_t lead_i, std::size_t lead_j, std::vector<T>* beta) {
//	assert(lead_i * lead_j > 0); //
	assert(matrix[lead_i][lead_j] != 0);
//	assert(lead_j > 0);

	auto matrix_copy(this->matrix);
	

	for (std::size_t i = 0; i < rows; i++) {
		for (std::size_t j = 0; j < cols; j++) {
			if (i == lead_i) {
				matrix[i][j] = matrix_copy[i][j] / matrix_copy[lead_i][lead_j];
			}
			else {
				matrix[i][j] = matrix_copy[i][j] - (matrix_copy[lead_i][j] * matrix_copy[i][lead_j]) / matrix_copy[lead_i][lead_j];
			}
		}
	}

	if (!beta) {
		return;
	}

	std::vector<T> beta_copy(*beta);
	// make Jourdan-Gaussiann elimination for beta

	for (std::size_t i = 0; i < beta->size(); i++) {
		
		if (i == lead_i) {
			(*beta)[i] = beta_copy[i] / matrix_copy[lead_i][lead_j];
		}
		else {
			(*beta)[i] = beta_copy[i] - (beta_copy[lead_i] * matrix_copy[i][lead_j]) / matrix_copy[lead_i][lead_j];
		}
		
	}
}

template <typename T>
void ConstraintMatrix<T>::print() const {
	for (std::size_t i = 0; i < rows; i++) {
		for (std::size_t j = 0; j < cols; j++) {
			std::cout << matrix[i][j] << "   ";
		}
		std::cout << std::endl;
	}
}



template <typename T>
bool ConstraintMatrix<T>::isUnitVector(std::size_t col_index, std::size_t index_of_1) const {
	if (col_index >= nCols()) {
		throw std::out_of_range("col_index >= number of columns");
	}

	for (std::size_t i = 0; i < nRows(); i++) {
		if (i == index_of_1) {
			if (matrix[i][col_index] != 1) {
				return false;
			}
		}
		else {
			if (matrix[i][col_index] != 0) {
				return false;
			}
		}
	}

	return true;
}
template class ConstraintMatrix<double>;
