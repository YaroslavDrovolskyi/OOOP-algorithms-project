#include "SimplexMethodTable.h"
#include <utility>



SimplexMethodTable::SimplexMethodTable(const ConstraintMatrix<double>& matrix, const std::vector<double>& beta,
	const std::vector<double>& basis_vars, const std::vector<double>& delta, const std::vector<double>& theta, std::size_t lead_i, std::size_t lead_j) :
	matrix(matrix), beta(beta), basis_vars(basis_vars), delta(delta), theta(theta), lead_i(lead_i), lead_j(lead_j), is_last_step(false)
{

}


SimplexMethodTable::SimplexMethodTable(const ConstraintMatrix<double>& matrix, const std::vector<double>& beta,
	const std::vector<double>& basis_vars, const std::vector<double>& delta) :
	matrix(matrix), beta(beta), basis_vars(basis_vars), delta(delta), is_last_step(true), lead_i(0), lead_j(0)

{


}


ConstraintMatrix<double> SimplexMethodTable::getConstraintMatrix() const{
    return this->matrix;
}
std::vector<double> SimplexMethodTable::getBeta() const{
    return this->beta;
}
std::vector<double> SimplexMethodTable::getBasisVars() const{
    return this->basis_vars;
}
std::vector<double> SimplexMethodTable::getDelta() const{
    return this->delta;
}

bool SimplexMethodTable::isLastStep() const{
    return this->is_last_step;
}
std::vector<double> SimplexMethodTable::getTheta() const{
    return this->theta;
}
std::pair<std::size_t, std::size_t> SimplexMethodTable::getLeadItem() const{
    return std::make_pair(lead_i, lead_j);
}



SimplexMethodSolution::SimplexMethodSolution(const std::vector<double>& coefs, const std::vector<SimplexMethodTable>& steps, const std::string& result_str) :
	coefs(coefs), steps(steps), result_str(result_str), is_solution(false)
{

}


SimplexMethodSolution::SimplexMethodSolution(const std::vector<double>& coefs, const std::vector<SimplexMethodTable>& steps,
	const std::vector<double>& solution, double func_value, const std::string& result_str) :
	coefs(coefs), steps(steps), solution(solution), func_value(func_value), result_str(result_str), is_solution(true)
{

}

SimplexMethodSolution::SimplexMethodSolution() : is_solution(false), func_value(0)
{

}

void SimplexMethodSolution::setCoefs(const std::vector<double>& coefs) {
	this->coefs = coefs;
}
void SimplexMethodSolution::setSteps(const std::vector<SimplexMethodTable>& steps) {
	this->steps = steps;
}
void SimplexMethodSolution::setSolution(const std::vector<double>& solution) {
	this->solution = solution;
}
void SimplexMethodSolution::setFuncValue(double func_value) {
	this->func_value = func_value;
}
void SimplexMethodSolution::setResultStr(const std::string& result_str) {
	this->result_str = result_str;
}
void SimplexMethodSolution::setIsSolution(bool is_solution) {
	this->is_solution = is_solution;
}


std::vector<double> SimplexMethodSolution::getCoefs() const{
    return this->coefs;
}
std::vector<SimplexMethodTable> SimplexMethodSolution::getSteps() const{
    return this->steps;
}
std::string SimplexMethodSolution::getResultStr() const{
    return this->result_str;
}

bool SimplexMethodSolution::isSolutionExist() const{
    return this->is_solution;
}
std::vector<double> SimplexMethodSolution::getSolution() const{
    return this->solution;
}
double SimplexMethodSolution::getFuncValue() const{
    return this->func_value;
}
