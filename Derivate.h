
#pragma once

#include "Algebra_node.h"
#include "Shunting_yard.h"
#include "Enumerate.h"
#include <ratio>
#include <algorithm>


Algebra_Node* DerivateFunction(Algebra_Node* root);
Algebra_Node* DerivateFunction(Algebra_Node* root, Debug_concept& W);
double Numerical_Differentiation(Algebra_Tree& treeExpr, double t, double h, QString x);
