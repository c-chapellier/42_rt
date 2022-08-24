#pragma once

#include    <math.h>

#define     EQN_EPS     1e-9
#define	    IsZero(x)	((x) > -EQN_EPS && (x) < EQN_EPS)

class EquationSolver
{
private:

public:
    static int Quadric(double c[ 3 ], double s[ 2 ]);

    static int QuadraticSphere(double c[ 3 ], double s[ 2 ]);
    static int Cubic(double c[ 4 ], double s[ 3 ]);
    static int Quartic(double c[ 5 ], double s[ 3 ]);
};
