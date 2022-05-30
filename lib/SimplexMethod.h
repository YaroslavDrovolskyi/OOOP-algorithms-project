#pragma once
#include <vector>
#include "ConstraintMatrix.h"


class SimplexMethod {
private:
	ConstraintMatrix<double> matrix;
	std::vector<double> beta;
	std::vector<double> coefs;
	std::vector<double> basis_vars; // indexes of basis vars
	std::vector<double> delta;
	std::vector<double> theta;

	void calcDelta();
	void calcTheta(std::size_t col_index);
	void findBasis(); // fill basis_vars
	bool isNoSolutions();


	double getMinIndex(const std::vector<double>& v);
	double getMaxIndex(const std::vector<double>& v);
	double getMin(const std::vector<double>& v);
	double getMax(const std::vector<double>& v);

	
public:
	void run();


};



