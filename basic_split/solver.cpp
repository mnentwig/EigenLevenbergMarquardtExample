#include "solver.h"

#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>  // Eigen::LevenbergMarquardt
#include <unsupported/Eigen/NumericalDiff>          // Eigen::NumericalDiff

/** boilerplate template for LM optimization.
 * Fields are expected by Eigen::LevenbergMarquardt and / or Eigen::NumDiff */
template <typename TScalar>
struct lmFunOuter {
    typedef TScalar Scalar;
    enum {
        InputsAtCompileTime = Eigen::Dynamic,  // note, fixed size is not supported in Eigen::LM 3.4.0
        ValuesAtCompileTime = Eigen::Dynamic
    };

    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> InputType;
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> ValueType;
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> JacobianType;

    lmFunOuter(lmFunUserTemplate<TScalar> *glmf) : glmf(glmf) {}
    int inputs() const { return this->glmf->nInputs; }
    int values() const { return this->glmf->nValues; }

   public:
    lmFunUserTemplate<TScalar> *glmf;
    int operator()(const Eigen::VectorXd &z, Eigen::VectorXd &fvec) const {
        return this->glmf->eval(z, fvec);
    }
};

struct lmFunOuter_diff : Eigen::NumericalDiff<lmFunOuter<double>> {
    lmFunOuter_diff(lmFunOuter<double> &lmfo) : NumericalDiff(lmfo){};
};

void solver(lmFunUserTemplate<double> *ofun, Eigen::VectorXd &z) {
    lmFunOuter<double> lmfo(ofun);
    lmFunOuter_diff fdf(lmfo);
    Eigen::LevenbergMarquardt<lmFunOuter_diff> lm(fdf);
    lm.parameters.maxfev = 1000;
    lm.parameters.xtol = 1.0e-10;

    lm.minimize(z);
}