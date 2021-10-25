#include "EquationSolver.hpp"

std::list<double> EquationSolver::solveEquation(double a, double b)
{
    std::list<double> solutions;
    if(a == 0){

    } else {
        solutions.push_back(-b / a);
    }
    return solutions;
}
std::list<double> EquationSolver::solveQuadraticEquation(double a, double b, double c)
{
    if (a == 0)
        return solveEquation(b, c);

    std::list<double> solutions;
    double delta = pow(b, 2) - (4 * a * c);
    if (delta < 0) {

    } else if(delta == 0) {
        solutions.push_back(-b / (2 * a));
    } else {
        solutions.push_back((-b + sqrt(delta)) / (2 * a));
        solutions.push_back((-b - sqrt(delta)) / (2 * a));
    }
    return solutions;
}
// https://fr.wikipedia.org/wiki/%C3%89quation_cubique#M%C3%A9thode_de_Lagrange
std::list<double> EquationSolver::solveCubicEquation(double a, double b, double c, double d)
{
    if (a == 0)
        return solveQuadraticEquation(b, c, d);

    std::list<double> solutions;

    return solutions;
}
std::list<double> EquationSolver::solveQuarticEquation(double a, double b, double c, double d, double e)
{
    if (a == 0)
        return solveCubicEquation(b, c, d, e);

    std::list<double> solutions;

    return solutions;
}