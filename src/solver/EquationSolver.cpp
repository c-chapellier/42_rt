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

    if(d == 0) {
        solutions.push_back(0);
        std::list<double> tmp = solveQuadraticEquation(a, b, c);
        for(auto const s : tmp) {
            bool alreadyIn = false;
            for(auto const s_prime : solutions) {
                if (s_prime == s)
                    alreadyIn = true;
            }
            if(alreadyIn == false) {
                solutions.push_back(s);
            }
        }
    } else {
        double delta0 = pow(b, 2) - (3 *a * c);
        double delta1 = (2 * pow(b, 3)) - (9 * a * b * c) + (27 * pow(a, 2) * d);
        double delta = (pow(delta1, 2) - (4 * pow(delta0, 3))) / (27 * pow(a, 2));
        double C = pow(sqrt(pow(delta1, 2) - (4 * pow(delta0, 3)) + delta1) / 2.0, 1.0 / 3.0);
        double u = (-1 + sqrt(-3)) / 2.0;
        for (int n = 1; n < 4; ++n) {
            double s = -(b + (pow(u, n) * C) + (delta0 / (pow(u, n) * C))) / (3 * a);
            bool alreadyIn = false;
            for(auto const s_prime : solutions) {
                if (s_prime == s)
                    alreadyIn = true;
            }
            if(alreadyIn == false) {
                solutions.push_back(s);
            }
        }
    }

    return solutions;
}

// https://en.wikipedia.org/wiki/Quartic_equation#The_general_case,_along_Ferrari's_lines
std::list<double> EquationSolver::solveQuarticEquation(double a, double b, double c, double d, double e)
{
    if (a == 0)
        return solveCubicEquation(b, c, d, e);

    std::list<double> solutions;

    // double alpha = ((-3 * pow(b, 2)) / (8 * pow(a, 2))) + (c / a);
    // double beta = (pow(b, 3) / (8 * pow(a, 3))) - ((b * c) / (2 * pow(a, 2))) + (d / a);
    // double gama = ((-3 * pow(b, 4)) / (256 * pow(a, 4))) + ((c * pow(b, 2)) / (16 * pow(a, 3))) - ((b * d) / (4 * pow(a, 2))) + (e / a);
    // // u⁴ + αu² + βu + γ = 0
    // double P = -(pow(alpha, 2) / 12) - gama;
    // double Q = -(pow(alpha, 3) / 108) + ((alpha * gama) / 3) - (pow(beta, 2) / 8);
    // double R1 = -(Q / 2.0) + sqrt((pow(Q, 2) / 4) + (pow(P, 3) / 27));
    // double R2 = -(Q / 2.0) - sqrt((pow(Q, 2) / 4) + (pow(P, 3) / 27));
    // double U1 = pow(R1, 1.0 / 3.0);
    // double U2 = pow(R2, 1.0 / 3.0);

    return solutions;
}