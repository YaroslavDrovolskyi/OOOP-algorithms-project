#pragma once

#include <vector>


template<typename T>
class ConstraintMatrix {
private:
	std::vector<std::vector<T>> matrix;
	std::size_t rows;
	std::size_t cols;
	

public:
	ConstraintMatrix(std::size_t rows, std::size_t cols);
	void appendRow(const std::vector<T>& new_row);
	void appendCol(const std::vector<T>& new_col);
	std::size_t nRows() const;
	std::size_t nCols() const;
	std::vector<T> getCol(std::size_t index) const;
	T& item(std::size_t i, std::size_t j);
	void makeJordanGaussElimination(std::size_t lead_i, std::size_t lead_j, std::vector<T>* beta = nullptr);
	void print() const;
	bool isUnitVector(std::size_t col_index, std::size_t index_of_1) const;
};


