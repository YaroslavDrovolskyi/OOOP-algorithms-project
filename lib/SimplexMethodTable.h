#pragma once
#include "ConstraintMatrix.h"
#include <string>
class SimplexMethodTable {
	ConstraintMatrix<double> matrix;
	std::vector<double> beta;
	std::vector<double> basis_vars; // indexes of basis vars

	std::vector<double> delta;
	std::vector<double> theta;

	bool is_last_step;
	std::size_t lead_i;
	std::size_t lead_j;

public:
	SimplexMethodTable(const ConstraintMatrix<double>& matrix, const std::vector<double>& beta,
		const std::vector<double>& basis_vars, const std::vector<double>& delta, const std::vector<double>& theta, 
		std::size_t lead_i, std::size_t lead_j);

	SimplexMethodTable(const ConstraintMatrix<double>& matrix, const std::vector<double>& beta,
		const std::vector<double>& basis_vars, const std::vector<double>& delta);


	// need to add getters

};


class SimplexMethodSolution {
	std::vector<double> coefs;
	std::vector<SimplexMethodTable> steps;
	std::vector<double> solution; // solution[i] - is value of i-th variable
	double func_value;
	std::string result_str; // is is some comments, for example if no suolutions, we can write it there
	bool is_solution;


	SimplexMethodSolution(const std::vector<double>& coefs, const std::vector<SimplexMethodTable>& steps,
		const std::vector<double>& solution, double func_value, const std::string& result_str);

	SimplexMethodSolution(const std::vector<double>& coefs, const std::vector<SimplexMethodTable>& steps, const std::string& result_str);

public:

	SimplexMethodSolution();
	void setCoefs(const std::vector<double>& coefs);
	void setSteps(const std::vector<SimplexMethodTable>& steps);
	void setSolution(const std::vector<double>& solution);
	void setFuncValue(double func_value);
	void setResultStr(const std::string& result_str);
	void setIsSolution(bool is_solution);

};

