// compile with
// g++ -static -Ieigen-3.4.0 basic_LM_example.cpp
// with eigen-3.4.0 in same
// ~16s compile time
#include <iostream>
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization> // Eigen::LevenbergMarquardt
#include <unsupported/Eigen/NumericalDiff> // Eigen::NumericalDiff

/** boilerplate template for LM optimization.
 * Fields are expected by Eigen::LevenbergMarquardt and / or Eigen::NumDiff */
template <typename TScalar>
struct LM_functor_boilerplate {
    typedef TScalar Scalar;
    enum {
        InputsAtCompileTime = Eigen::Dynamic,  // note, fixed size is not supported in Eigen::LM 3.4.0
        ValuesAtCompileTime = Eigen::Dynamic
    };

    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> InputType;
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, 1> ValueType;
    typedef Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic> JacobianType;

    int m_numInputs, m_numValues;
    LM_functor_boilerplate(int numInputs, int numValues) : m_numInputs(numInputs), m_numValues(numValues) {}
    int inputs() const { return m_numInputs; }
    int values() const { return m_numValues; }
};

struct myFunctor : LM_functor_boilerplate<double> {
    myFunctor() : LM_functor_boilerplate<double>(2, 2) {}

    int operator()(const Eigen::VectorXd &z, Eigen::VectorXd &fvec) const {
        double x = z(0);
        double y = z(1);
        // objFun = sum(fvec(i)^2)
        fvec(0) = x + 2 * y - 7;
        fvec(1) = 2 * x + y - 5;
        return 0;
    }
};

int main() {
    struct myFunctor_numDiff : Eigen::NumericalDiff<myFunctor> {};
    Eigen::VectorXd z(2);
    z << 0, 0;

    myFunctor_numDiff fdf;
    Eigen::LevenbergMarquardt<myFunctor_numDiff> lm(fdf);
    lm.parameters.maxfev = 1000;
    lm.parameters.xtol = 1.0e-10;

    int ret = lm.minimize(z);
    std::cout << "iterations: " << lm.iter << std::endl;
    std::cout << "status: " << ret << std::endl;
    std::cout << "result: " << z.transpose() << std::endl;
    return 0;
}