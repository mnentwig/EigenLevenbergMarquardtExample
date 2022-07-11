// The code in this file goes into an object file separate from the LM solver, enabling faster compilation cycles

#include <Eigen/Dense>
#include "solver.h"
#include <iostream>

template <typename TScalar>
struct lmUserOFun : public lmFunUserTemplate<TScalar> {
   public:
    lmUserOFun() : lmFunUserTemplate<TScalar>(/*nIn*/ 2, /*nOut*/ 2) {}

    int eval(const Eigen::VectorXd &z, Eigen::VectorXd &fvec) const {
        double x = z(0);
        double y = z(1);
        // objFun = sum(fvec(i)^2)
        fvec(0) = x + 2 * y - 7;
        fvec(1) = 2 * x + y - 5;
        return 0;
    }
};

int main() {
    lmUserOFun<double> ofun;

    Eigen::VectorXd z(2) ;
    z << 0, 0;

    solver(&ofun, z);
    std::cout << "result: " << z.transpose() << std::endl;
    return 0;
}