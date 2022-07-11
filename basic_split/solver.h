#include <Eigen/Dense>

/** #include from user code and overload with custom objective function. Ppassed as object to lmFunOuter.
 * Purpose is to break the inheritance chain, allowing independent compilation of the complex LM code */
template <typename TScalar>
class lmFunUserTemplate {
   public:
    lmFunUserTemplate(int nInputs, int nValues) : nInputs(nInputs), nValues(nValues){};
    virtual int eval(const Eigen::VectorXd& z, Eigen::VectorXd& fvec) const = 0;
    int inputs() const { return nInputs; }
    int values() const { return nValues; }

    int nInputs;
    int nValues;
    //    friend lmFunOuter<TScalar>;
};

void solver(lmFunUserTemplate<double>* ofun, Eigen::VectorXd& z);