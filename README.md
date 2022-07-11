# EigenLevenbergMarquardtExample
A cleaned up code sample for Eigen 3.4.0's "Levenberg-Marquardt" nonlinear optimization. 

There are two versions:
* simple
* compile time optimized

Note: use -O1 with Eigen for faster compile time, compared to default -O0

### basic_LM_example

* Template functor class provides fields expected by LM and num. diff
* specific objective function derives from above
* numerical differentiation derives from above

Notes: 
* Apparently, Eigen::LevenbergMarquardt does not support fixed size input at the moment (results in type mismatch for Jacobian).
* LM optimizes the squared sum of objective function values

### basic_split
Puts LM solver into object file, avoiding full recompilation when e.g. the objective function changes
With -O1 (fastest compile time!), minimum compile cycle is ~2.8 s (all in one file: 8.6 s)
