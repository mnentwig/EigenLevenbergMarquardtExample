# EigenLevenbergMarquardtExample
A cleaned up code sample for Eigen 3.4.0's "Levenberg-Marquardt" nonlinear optimization

* Template functor class provides fields expected by LM and num. diff
* specific objective function derives from above
* numerical differentiation derives from above

Notes: 
* Apparently, Eigen::LevenbergMarquardt does not support fixed size input at the moment (results in type mismatch for Jacobian).
* LM optimizes the squared sum of objective function values