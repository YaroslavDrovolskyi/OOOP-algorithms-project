#pragma once
#include "ConstraintMatrix.h"
class SimplexMethodTable {
	ConstraintMatrix<double> matrix;
	std::vector<double> beta;
	std::vector<double> basis_vars; // indexes of basis vars

	std::vector<double> delta;
	std::vector<double> theta;

	SimplexMethodTable(const ConstraintMatrix<double>& matrix, const std::vector<double>& beta,
		const std::vector<double>& basis_vars, const std::vector<double>& delta, const std::vector<double>& theta);


	// need to add getters

};


class SimplexMethodSolution {
	std::vector<double> coefs;
	std::vector<SimplexMethodTable> steps;
	std::vector<double> solution; // solution[i] - is value of i-th variable
	double func_value;

	SimplexMethodSolution(const std::vector<double>& coefs, const std::vector<SimplexMethodTable>& steps,
		const std::vector<double>& solution, double func_value);
};

