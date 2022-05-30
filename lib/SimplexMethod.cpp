#include <limits>
#include <stdexcept>
#include "SimplexMethod.h"



void SimplexMethod::run() {
	findBasis();
	if (getMax(basis_vars) == std::numeric_limits<double>::infinity()) { // no exact basis
		throw std::runtime_error("Input constraint matrix doesn't contain identity submatrix");
		// there we can apply M-method or something else to find start basis
	}
	if (getMin(basis_vars) < 0) { // some beta[i] < 0, so it is not canonical task
		throw std::runtime_error("Task is not canonical: exist beta[i] < 0");
		// there we can apply dual simplex-method
	}
	while (true) {
		calcDelta();
		if (getMin(delta) >= 0) { // we found optimal solution
//			makeResult(); // 
			return;
		}
		if (isNoSolutions()) {
			// resull make result
			return;
		}
		std::size_t min_j = getMinIndex(delta);
		calcTheta(min_j);
		std::size_t min_i = getMinIndex(theta);

		// captureState(); // 
		basis_vars[min_i] = min_j; // change basis
		matrix.makeJordanGaussElimination(min_i, min_j, &beta);

	}
}


void SimplexMethod::calcDelta() {
	for (std::size_t j = 0; j < matrix.nCols(); j++) {
		double scalar_product = 0;
		for (std::size_t i = 0; i < matrix.nRows(); i++) {
			scalar_product += coefs[basis_vars[i]] * matrix.item(i, j);
		}
		delta[j] = coefs[j] - scalar_product;
	}
}


void SimplexMethod::calcTheta(std::size_t col_index) {
	for (std::size_t i = 0; i < matrix.nRows(); i++) {
		if (matrix.item(i, col_index) > 0) {
			theta[i] = beta[i] / matrix.item(i, col_index);
		}
		else {
			theta[i] = std::numeric_limits<double>::infinity();
		}
	}
}

double SimplexMethod::getMinIndex(const std::vector<double>& v) {
	std::size_t min_i = 0;
	for (std::size_t i = 1; i < v.size(); i++) {
		if (v[i] < v[min_i]) {
			min_i = i;
		}
	}

	return min_i;
}

double SimplexMethod::getMaxIndex(const std::vector<double>& v) {
	std::size_t max_i = 0;
	for (std::size_t i = 1; i < v.size(); i++) {
		if (v[i] > v[max_i]) {
			max_i = i;
		}
	}

	return max_i;
}


double SimplexMethod::getMin(const std::vector<double>& v) {
	std::size_t min_i = getMinIndex(v);

	return v[min_i];
}

double SimplexMethod::getMax(const std::vector<double>& v) {
	std::size_t max_i = getMaxIndex(v);
	
	return v[max_i];
}


void SimplexMethod::findBasis() {
	this->basis_vars.resize(matrix.nRows(), std::numeric_limits<double>::infinity());
	for (std::size_t i = 0; i < matrix.nRows(); i++) {
		for (std::size_t j = 0; j < matrix.nCols(); j++) {
			if (matrix.isUnitVector(j, i)) { // j-th vector is unit vector with 1 on i-th position
				basis_vars[i] = j;
			}
		}
	}
}

bool SimplexMethod::isNoSolutions() {
	for (std::size_t j = 0; j < delta.size(); j++) {
		if (delta[j] < 0) {
			if (getMax(matrix.getCol(j)) <= 0) {
				return true;
			}
		}
	}

	return false;
}