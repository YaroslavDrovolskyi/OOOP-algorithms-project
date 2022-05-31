#pragma once
#include <vector>
#include "ConstraintMatrix.h"
#include "SimplexMethodTable.h"


class SimplexMethod {
private:
	ConstraintMatrix<double> matrix;
	std::vector<double> beta;
	std::vector<double> coefs;
	std::vector<double> basis_vars; // indexes of basis vars
	std::vector<double> delta;
	std::vector<double> theta;

	std::vector<SimplexMethodTable> steps;

	SimplexMethodSolution solution;

	void calcDelta();
	void calcTheta(std::size_t col_index);
	void findBasis(); // fill basis_vars
	bool isNoSolutions();


	double getMinIndex(const std::vector<double>& v);
	double getMaxIndex(const std::vector<double>& v);
	double getMin(const std::vector<double>& v);
	double getMax(const std::vector<double>& v);

	void makeResult(bool is_solution_exist);
	std::vector<double> makeSolution();
	double scalarProduct(const std::vector<double>& v1, const std::vector<double>& v2);

public:
	SimplexMethod(const std::vector<double>& coefs, const ConstraintMatrix<double>& matrix, const std::vector<double>& beta);
	void run();
	SimplexMethodSolution getSolution() const;

};



