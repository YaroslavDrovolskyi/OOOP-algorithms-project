#include "SimplexMethodTable.h"



SimplexMethodTable::SimplexMethodTable(const ConstraintMatrix<double>& matrix, const std::vector<double>& beta,
	const std::vector<double>& basis_vars, const std::vector<double>& delta, const std::vector<double>& theta) :
	matrix(matrix), beta(beta), basis_vars(basis_vars), delta(delta), theta(theta)
{

}


SimplexMethodSolution::SimplexMethodSolution(const std::vector<double>& coefs, const std::vector<SimplexMethodTable>& steps,
	const std::vector<double>& solution, double func_value) :
	coefs(coefs), steps(steps), solution(solution), func_value(func_value)
{

}