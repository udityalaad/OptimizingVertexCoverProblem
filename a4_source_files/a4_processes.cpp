#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>

// defined std::unique_ptr
#include <memory>
//defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"


#include "../a2_source_files/edge.hpp"
#include "../a2_source_files/graph.hpp"

#include "a4_processes.hpp"




/* ******************************************************************************** */
//                              Other Common Functions
/* ******************************************************************************** */
// Function to covert vertexCover to a string format.
std::string vertexCover_toString (std::vector<int> vertexCover) {
    std::string vc_string = "";

    for (int i = 0; i < ((int) vertexCover.size()); i++) {
        if (i != 0) {
            vc_string = vc_string + " ";
        }

        vc_string = vc_string + std::to_string(vertexCover.at(i));
    }

    return vc_string;
}


// Function to check if two integer-vectors are equal.
bool intVectorEquals (std::vector<int> v1, std::vector<int> v2) {
    if (v1.size() != v2.size()) {
        return false;
    }

    for (int i = 0; i < ((int) v1.size()); i++) {
        if (v1.at(i) != v2.at(i)) {
            return false;
        }
    }

    return true;
}
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//                      Vertex Cover - Using CNF-SAT Solver
/* ******************************************************************************** */
// Function to find ArrayIndex equivalent of a MatrixIndex
int convertMatrixIndex_to_ArrayIndex (int currRow, int currCol, int noRow, int noCol) {
    return currCol + (currRow * noCol);
}


// Function to extract MatrixRow from an ArrayIndex
int extractMatrixRow_from_ArrayIndex (int index, int noRow, int noCol) {
    return (index - (index/noRow)) / noCol;
}


// Function to check whether the given 'k' produces a SATISFIABLE VertexCover
bool cnfSATSolver (Graph g, int sizeVertexCover, std::vector<int> &vertexCover, std::string &clauses_string, std::unique_ptr<Minisat::Solver> &solver) {
    /* -------- Var declaration and initialization -------- */
    // allocate on the heap so that we can reset later if needed
    // std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());

    // Reset solver for next iteration
    solver.reset(new Minisat::Solver());
    
    // No. of vertices in the Graph
    int n = g.getNoVertices();
    
    // No. of vertices in vertexCover
    int k = sizeVertexCover;
    
    // Literals in matrix form
    std::vector<std::vector<Minisat::Lit>> literals;
    for (int i = 0; i < n; i++) {       // initialize literals
        std::vector<Minisat::Lit> row;

        for (int j = 0; j < k; j++) {
            row.push_back(Minisat::mkLit(solver->newVar()));
        }

        literals.push_back(row);
    }


    /* -------- Clauses -------- */
    // At least one vertex = vertexCover[i], for each value till 'k'
    // ----- At least one vertex is the ith vertex in the vertex cover -----
    for (int i = 0; i < k; i++) {
        Minisat::vec<Minisat::Lit> clauseLiterals;

        for (int v = 0; v < n; v++) {
            clauseLiterals.push(literals.at(v).at(i));

            clauses_string += std::to_string(convertMatrixIndex_to_ArrayIndex(v, i, n, k) + 1) + " ";
        }

        solver->addClause(clauseLiterals);
        clauses_string += "0\n";
    }

    // vertexCover[j] contains unique values
    // ----- No one vertex can appear twice in a vertex cover. -----
    // ----- In other words, it is not the case that vertex m appears both in positions p and q of the vertex cover. -----
    for (int m = 0; m < n; m++) {
        for (int p = 0; p < k; p++) {
            for (int q = p + 1; q < k; q++) {
                solver->addClause(~literals.at(m).at(p), ~literals.at(m).at(q));
                
                clauses_string += std::to_string(-convertMatrixIndex_to_ArrayIndex(m, p, n, k) - 1) + " "
                                    + std::to_string(-convertMatrixIndex_to_ArrayIndex(m, q, n, k) - 1) + " "
                                    + "0\n";
            }
        }
    }

    // Each vertexCover[m] contains only one vertex
    // ----- No more than one vertex appears in the mth position of the vertex cover -----
    for (int m = 0; m < k; m++) {
        for (int p = 0; p < n; p++) {
            for (int q = p + 1; q < n; q++) {
                solver->addClause(~literals.at(p).at(m), ~literals.at(q).at(m));

                clauses_string += std::to_string(-convertMatrixIndex_to_ArrayIndex(p, m, n, k) - 1) + " "
                                    + std::to_string(-convertMatrixIndex_to_ArrayIndex(q, m, n, k) - 1) + " "
                                    + "0\n";
            }
        }
    }

    // VertexCover[] contains either 'src' and/or 'dest' of each Edge
    // ----- Every edge is incident to at least one vertex in the vertex cover. -----
    std::vector<Edge> edges = g.getEdges();
    for (int x = 0; x < ((int) edges.size()); x++) {
        Minisat::vec<Minisat::Lit> clauseLiterals;

        int src = std::stoi(edges.at(x).getSrc());
        int dest = std::stoi(edges.at(x).getDest());

        for (int j = 0; j < k; j++) {
            clauseLiterals.push(literals.at(src - 1).at(j));
            clauseLiterals.push(literals.at(dest - 1).at(j));

            clauses_string += std::to_string(convertMatrixIndex_to_ArrayIndex(dest - 1, j, n, k) + 1) + " "
                                + std::to_string(convertMatrixIndex_to_ArrayIndex(src - 1, j, n, k) + 1) + " ";
        }

        solver->addClause(clauseLiterals);

        clauses_string += "0\n";
    }


    /* --------- Function Wrap-up -------- */
    bool SATISFIABILITY = solver->solve();

    if (SATISFIABILITY) {
        for (int i = 0; i < ((int) literals.size()); i++) {
            for (int j = 0; j < ((int) literals.at(i).size()); j++) {
                if (Minisat::toInt(solver->modelValue(literals.at(i).at(j))) == 0) {
                    vertexCover.push_back(i + 1);
                }
            }
        }
    }

    // solver.reset(new Minisat::Solver());

    return SATISFIABILITY;
}


// Function to find vertexCover using cnfSATSolver
std::vector<int> vertexCoverUsingCnfSATSolver (Graph g, std::unique_ptr<Minisat::Solver> &solver, bool &interrupted) {
    std::vector<int> vertexCover;
    std::string clauses_string;

    if ((int) g.getEdges().size() != 0) {
        for (int i = 1; i <= g.getNoVertices(); i++) {
            bool satisfiable = cnfSATSolver(g, i, vertexCover, clauses_string, solver);
            
            if (satisfiable  ||  interrupted) {
                if (interrupted) {
                    vertexCover.clear();
                }

                break;
            }
        }
    }
    
    // Sort vertexCover
    std::sort(vertexCover.begin(), vertexCover.end());
    
    return vertexCover;
}
/* ******************************************************************************** */
/* ******************************************************************************** */



