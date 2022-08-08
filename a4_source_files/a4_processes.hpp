#pragma once

#include <string>
#include <vector>


// defined std::unique_ptr
#include <memory>
//defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"


// CLASS AND FUNCTION DECLARATIONS GO HERE


/* ******************************************************************************** */
//                              Other Common Functions
/* ******************************************************************************** */
// Function to covert vertexCover to a string format.
std::string vertexCover_toString (std::vector<int> vertexCover);

// Function to check if two integer-vectors are equal.
bool intVectorEquals (std::vector<int> v1, std::vector<int> v2);
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//                      Vertex Cover - Using CNF-SAT Solver
/* ******************************************************************************** */
// Function to find ArrayIndex equivalent of a MatrixIndex
int convertMatrixIndex_to_ArrayIndex (int currRow, int currCol, int noRow, int noCol);

// Function to extract MatrixRow from an ArrayIndex
int extractMatrixRow_from_ArrayIndex (int index, int noRow, int noCol);

// Function to check whether the given 'k' produces a SATISFIABLE VertexCover
bool cnfSATSolver (Graph g, int sizeVertexCover, std::vector<int> &vertexCover, std::string &clauses_string, std::unique_ptr<Minisat::Solver> &solver);

// Function to find vertexCover using cnfSATSolver
std::vector<int> vertexCoverUsingCnfSATSolver (Graph g, std::unique_ptr<Minisat::Solver> &solver, bool &interrupted);
/* ******************************************************************************** */
/* ******************************************************************************** */



