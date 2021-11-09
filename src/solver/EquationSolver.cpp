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
// https://stackoverflow.com/questions/43559140/having-trouble-solving-cubic-equations-in-java
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
        b /= a;
        c /= a;
        d /= a;

        // double p = (b / 3) - (pow(a, 21) / 9);
        // double q = (pow(a, 3) / 27) - ((a * b) / 6) + (c / 2);
        // double D = pow(p, 3) + (p * q);

        double disc, q, r, dum1, s, t, term1, r13;
        q = (3.0 * c - (pow(b, 2))) / 9.0;
        r = -(27.0 * d) + b * (9.0 * c - 2.0 * (pow(b, 2)));
        r /= 54.0;
        disc = pow(q, 3) + pow(r, 2);

        term1 = (b / 3.0);

        if (disc > 0) { // one root real, two are complex
            s = r + sqrt(disc);
            s = ((s < 0) ? pow(-s, (1.0 / 3.0)) : pow(s, (1.0 / 3.0)));
            t = r - sqrt(disc);
            t = ((t < 0) ? - pow(-t, (1.0 / 3.0)) : pow(t, (1.0 / 3.0)));
            solutions.push_back(-term1 + s + t);
        } else if (disc == 0) { // All roots real, at least two are equal.
            r13 = ((r < 0) ? - pow(-r, (1.0 / 3.0)) : pow(r, (1.0/  3.0)));
            solutions.push_back(-term1 + 2.0 * r13);
            solutions.push_back(-(r13 + term1));
        } else { // all roots are real and unequal (to get here, q < 0)
            q = -q;
            dum1 = pow(q, 3);
            dum1 = acos(r / sqrt(dum1));
            r13 = 2.0 * sqrt(q);
            solutions.push_back(-term1 + r13 * cos(dum1 / 3.0));
            solutions.push_back(-term1 + r13 * cos((dum1 + 2.0 * M_PI) / 3.0));
            solutions.push_back(-term1 + r13 * cos((dum1 + 4.0 * M_PI) / 3.0));
        }
    }

    return solutions;
}

// https://en.wikipedia.org/wiki/Quartic_equation#The_general_case,_along_Ferrari's_lines
std::list<double> EquationSolver::solveQuarticEquation(double a, double b, double c, double d, double e)
{
    //std::cout << a << " " << b << " " << c << " " << d << " " << e << std::endl;
    if (a == 0) {
        // equation:
        // bx³ + cx² + dx + e = 0
        return solveCubicEquation(b, c, d, e);
    }

    std::list<double> solutions;

    if(e == 0) {
        // equation:
        // ax⁴ + bx³ + cx² + dx = 0
        solutions.push_back(0);
        std::list<double> tmp = solveCubicEquation(a, b, c, d);
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
    } else if(b == 0 && c == 0 && d == 0) {
        // equation:
        // ax⁴ + e = 0
        double r = -d / a;
        if(r > 0) {
            solutions.push_back(pow(r, 1.0 / 4.0));
            solutions.push_back(-pow(r, 1.0 / 4.0));
        }
    } else if(b == 0 && d == 0) {
        // equation:
        // ax⁴ + cx² + e = 0
        std::list<double> tmp = solveQuadraticEquation(a, c, e);
        for(double s : tmp) {
            if (s == 0) {
                solutions.push_back(sqrt(0));
            } else if (s >= 0) {
                solutions.push_back(sqrt(s));
                solutions.push_back(-sqrt(s));
            }
        }
    } else {
        // equation:
        // ax⁴ + bx³ + cx² + dx + e= 0
        // on pose:
        // x = y - (b / 4a)
        double p = (c / a) -
                    ((3 * pow(b, 2)) / (8 * pow(a, 2)));
        double q = (d / a) - 
                    ((b * c) / (2 * pow(a, 2))) +
                    (pow(b, 3) / (8 * pow(a, 3)));
        double r = (e / a) -
                    (b * d) / (4 * pow(a, 2)) +
                    (c * pow(b, 2)) / (16 * pow(a, 3)) -
                    (3 * pow(b, 4)) / (256 * pow(a, 4));

        // equation resultante:
        // z⁴ + pz² + qz + r = 0

        if (q == 0) {
            // equation bicare:
            // z⁴ + pz² + r = 0
            std::list<double> tmp = solveQuadraticEquation(1, p, r);
            for(double s : tmp) {
                if (s == 0) {
                    solutions.push_back(sqrt(0) - (b / (4 * a)));
                } else if (s >= 0) {
                    solutions.push_back(sqrt(s) - (b / (4 * a)));
                    solutions.push_back(-sqrt(s) - (b / (4 * a)));
                }
            }
        } else {
            // equation resultante:
            // z⁴ + pz² + qz + r = 0
            // Descartes's method
            std::list<double> tmp = solveCubicEquation(1, 2 * p, pow(p, 2) - (4 * r), -pow(q, 2));

            double D_A = 0;
            for (double s : tmp) {
                if(D_A == INFINITY || (D_A < 0 && s > 0) || (s > 0 && D_A > s)) {
                    D_A = s;
                    //break;
                }
            }
            if (D_A > 0) {
                double D_a = sqrt(D_A);
                //double D_a_prime = -a;
                double D_c = (p + pow(D_a, 2) + (q / D_a)) / 2;
                double D_b = (p + pow(D_a, 2) - (q / D_a)) / 2;

                std::list<double> tmp1 = solveQuadraticEquation(1, D_a, D_b);
                std::list<double> tmp2 = solveQuadraticEquation(1, -D_a, D_c);

                for (double s: tmp1) {
                    //s = s - (b / 4 * a);
                    bool alreadyIn = false;
                    // for(auto const s_prime : solutions) {
                    //     if (s_prime == s)
                    //         alreadyIn = true;
                    // }
                    if(alreadyIn == false) {
                        solutions.push_back(s);
                    }
                }
                for (double s: tmp2) {
                    //s = s - (b / 4 * a);
                    bool alreadyIn = false;
                    // for(auto const s_prime : solutions) {
                    //     if (s_prime == s)
                    //         alreadyIn = true;
                    // }
                    if(alreadyIn == false) {
                        solutions.push_back(s);
                    }
                }
            }
            
            /*
            std::list<double> tmp = solveCubicEquation(8, -4 * p, -8 * r, (4 * r * p) - pow(q, 2));

            double phi = INFINITY;
            for (double ss : tmp) {
                if(phi == INFINITY || (phi < 0 && ss > 0) || (ss > 0 && phi > ss)) {
                    phi = ss;
                }
            }

            if (phi == INFINITY)
                return solutions;

            double a0 = (2 * phi) - p;
            double b0 = -q / (2 * a0);

            std::list<double> tmp1 = solveQuadraticEquation(1, a0, phi + b0);
            std::list<double> tmp2 = solveQuadraticEquation(1, -a0, phi - b0);

            for (double s: tmp1) {
                s = s - (b / 4 * a);
                bool alreadyIn = false;
                for(auto const s_prime : solutions) {
                    if (s_prime == s)
                        alreadyIn = true;
                }
                if(alreadyIn == false) {
                    solutions.push_back(s);
                }
            }
            for (double s: tmp2) {
                s = s - (b / 4 * a);
                bool alreadyIn = false;
                for(auto const s_prime : solutions) {
                    if (s_prime == s)
                        alreadyIn = true;
                }
                if(alreadyIn == false) {
                    solutions.push_back(s);
                }
            }*/
        }
    }
    // if(solutions.size())
    //     std::cout << solutions.size() << std::endl;
    return solutions;
}