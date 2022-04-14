#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <set>
#include <map>
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

#include "../a4_source_files/a4_processes.hpp"

#include "prj_processes.hpp"




/* ******************************************************************************** */
//                              Other - Common Functions
/* ******************************************************************************** */
// Function to covert vertexCover to a comma-separated string-format.
std::string vertexCover_toString_commaSeparated (std::vector<int> vertexCover) {
    std::string vc_string = "";

    for (int i = 0; i < ((int) vertexCover.size()); i++) {
        if (i != 0) {
            vc_string = vc_string + ",";
        }

        vc_string = vc_string + std::to_string(vertexCover.at(i));
    }

    return vc_string;
}
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//                          Vertex Cover - Common Functions
/* ******************************************************************************** */
// Function to remove edges incident to a particular vertex from 'uncoveredEdges'-vector
std::vector<Edge> removeIncidentEdges (int vertex, std::vector<Edge> uncoveredEdges) {
    int i = 0;
    while (i < ((int) uncoveredEdges.size())) {
        if (std::stoi(uncoveredEdges.at(i).getSrc()) == vertex  ||  std::stoi(uncoveredEdges.at(i).getDest()) == vertex) {
            uncoveredEdges.erase(uncoveredEdges.begin() + i);
        } else {
            i++;
        }
    }

    return uncoveredEdges;
}
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//                  Vertex Cover - Using Approximate Algorithm 1
/* ******************************************************************************** */
// Function to compare 'noUncoveredEdges' (second value in pair); and then 'vertex' (first value in pair)
// Used to sort vector in decreasing order of 'noUncoveredEdges', and then in increasing order of 'vertex' (where 'noUncoveredEdges' are equal)
bool compareNoUncoveredEdgesDecreasing_andThen_vertexIncreasing (std::pair<int, int> &element1, std::pair<int, int> &element2) {
    if (element1.second == element2.second) {
        return element1.first < element2.first;
    }

    return element1.second > element2.second;
}


// Function to find vertex with max. noIncidentUncoveredEdges
int findVertexWithMaxIncidentUncoveredEdges (int noVertices, std::vector<Edge> uncoveredEdges) {
    // If no of vertices <= 0; then return 0 - indicating invalid/unsuccessful
    if (noVertices <= 0) {
        return 0;
    }

    // Create and initialise vector of pairs in the form '<vertex, noUncoveredEdges>' with noVertices as '0' (initially)
    std::vector<std::pair<int,int>> vertexEdgeFreq;
    for (int i = 0; i < noVertices; i++) {
        vertexEdgeFreq.push_back(std::pair<int, int>(i + 1, 0));
    }

    // Find noIncidentUncoveredEdges for all vertices
    for (int i = 0; i < ((int) uncoveredEdges.size()); i++) {
        int src = std::stoi(uncoveredEdges.at(i).getSrc());
        int dest =  std::stoi(uncoveredEdges.at(i).getDest());

        vertexEdgeFreq.at(src - 1).second++;
        vertexEdgeFreq.at(dest - 1).second++;
    }

    // Sort 'vertexEdgeFreq' in decreasing order of 'noUncoveredEdges', and then in increasing order of 'vertex' (where 'noUncoveredEdges' are equal)
    std::sort(vertexEdgeFreq.begin(), vertexEdgeFreq.end(), compareNoUncoveredEdgesDecreasing_andThen_vertexIncreasing);
        
    return vertexEdgeFreq.at(0).first;
}


// Function to find Vertex Cover - Using Approximate Algorithm 1
std::vector<int> approxVC_1 (Graph g)  {
    std::vector<Edge> uncoveredEdges = g.getEdges();
    std::vector<int> vertexCover;

    // Find Vertex Cover
    while (((int) uncoveredEdges.size()) != 0) {
        // Vertex with max. uncovered Edges 
        int vMax = findVertexWithMaxIncidentUncoveredEdges(g.getNoVertices(), uncoveredEdges);
        
        // Cover vMax
        vertexCover.push_back(vMax);                                // Add 'vMax' to 'vertexCover'
        uncoveredEdges = removeIncidentEdges(vMax, uncoveredEdges); // Remove uncoveredEdges incident to 'vMax'
    }

    // Sort vertexCover
    std::sort(vertexCover.begin(), vertexCover.end());

    return vertexCover;
}
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//                      Vertex Cover - Using Approximate Algorithm 2
/* ******************************************************************************** */
// Function to find Vertex Cover - Using Approximate Algorithm 2
std::vector<int> approxVC_2 (Graph g) {
    std::vector<Edge> uncoveredEdges = g.getEdges();
    std::vector<int> vertexCover;

    // Find Vertex Cover
    while ((int) uncoveredEdges.size() != 0) {
        int src = std::stoi(uncoveredEdges.at(0).getSrc());
        int dest = std::stoi(uncoveredEdges.at(0).getDest());

        // Cover 'src'
        vertexCover.push_back(src);                                 // Add 'src' to 'vertexCover'
        uncoveredEdges = removeIncidentEdges(src, uncoveredEdges);  // Remove uncoveredEdges incident to 'src'

        // Cover 'dest'
        vertexCover.push_back(dest);                                // Add 'dest' to 'vertexCover'
        uncoveredEdges = removeIncidentEdges(dest, uncoveredEdges); // Remove uncoveredEdges incident to 'dest'
    }

    // Sort vertexCover
    std::sort(vertexCover.begin(), vertexCover.end());

    return vertexCover;
}
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//              Vertex Cover - Using Optimized CNF-SAT SOLVER
/* ******************************************************************************** */
// Function to check whether an 'Integer-Vector' contains the given 'Element'
bool intVectorContains (std::vector<int> vec, int elem) {
    for (int i = 0; i < ((int) vec.size()); i++) {
        if (vec.at(i) == elem) {
            return true;
        }
    }

    return false;
}


// Function to find vertices with no edges at all
std::vector<int> verticesWithNoEdge (Graph g) {
    std::vector<int> result;

    std::vector<int> vE = verticesWithEdge(g);

    for (int i = 0; i < g.getNoVertices(); i++) {
        if (!intVectorContains(vE, i + 1)) {
            result.push_back(i + 1);
        }
    }

    return result;
}


// Function to find vertices with atleast 1 edge
std::vector<int> verticesWithEdge (Graph g) {
    std::vector<Edge> edges = g.getEdges();
    std::vector<int> result;

    for (int i = 0; i < ((int) edges.size()); i++) {
        if (!intVectorContains(result, std::stoi(edges.at(i).getSrc()))) {
            result.push_back(std::stoi(edges.at(i).getSrc()));
        }

        if (!intVectorContains(result, std::stoi(edges.at(i).getDest()))) {
            result.push_back(std::stoi(edges.at(i).getDest()));
        }
    }

    return result;
}


// Function to find no. of Edges connected to the given vertex
int noEdgesConnectedToVertex (Graph g, int v) {
    std::vector<Edge> edges = g.getEdges();
    int result = 0;

    for (int i = 0; i < ((int) edges.size()); i++) {
        int src = std::stoi(edges.at(i).getSrc());
        int dest = std::stoi(edges.at(i).getDest());

        if (src == v  ||  dest == v) {
            result++;
        }
    }

    return result;
}


// Function to find the redundant-vertices (Vertices that are not required in vertex-cover) in Pendant Edges (of the Graph).
// and Sure-vertices (Vertices that have to be present in the vertex-cover) of Pendant Edges (of the Graph).
void findRedundantAndSureVerticesInPendantEdges (Graph g, std::vector<int> &redundantVerticesInPendantEdges, std::set<int> &sureVerticesInPendantEdges) {
    std::vector<Edge> edges = g.getEdges();

    for (int x = 0; x < ((int) edges.size()); x++) {        
        int src = std::stoi(edges.at(x).getSrc());
        int dest = std::stoi(edges.at(x).getDest());

        int nE_src = noEdgesConnectedToVertex(g, src);
        int nE_dest = noEdgesConnectedToVertex(g, dest);
        if (std::min(nE_src, nE_dest) == 1) {       // If currentEdge is leaf/pendant edges
            if (nE_src == 1) {
                redundantVerticesInPendantEdges.push_back(src);
                sureVerticesInPendantEdges.insert(dest);
            } else {
                redundantVerticesInPendantEdges.push_back(dest);
                sureVerticesInPendantEdges.insert(src);
            }

            
        }
    }
}



// Function to check whether the given 'k' produces a SATISFIABLE VertexCover - (Optimized)
bool optimized_cnfSATSolver (Graph g, int sizeVertexCover, std::vector<int> &vertexCover, std::string &clauses_string, std::unique_ptr<Minisat::Solver> &solver, std::vector<int> &verNoEdge, std::vector<int> &redundantVerticesInPendantEdges, std::vector<int> &sureVerticesInPendantEdges) {
    // Finding Sets for Pre-conditions
    if (sizeVertexCover == 1) {
        verNoEdge.clear();
        redundantVerticesInPendantEdges.clear();
        sureVerticesInPendantEdges.clear();

        verNoEdge = verticesWithNoEdge(g);

        std::set<int> temp_sureVerticesInPendantEdges;
        findRedundantAndSureVerticesInPendantEdges(g, redundantVerticesInPendantEdges, temp_sureVerticesInPendantEdges);
        std::copy(temp_sureVerticesInPendantEdges.begin(), temp_sureVerticesInPendantEdges.end(), std::back_inserter(sureVerticesInPendantEdges));
    }



    /* -------- Var declaration and initialization -------- */
    // allocate on the heap so that we can reset later if needed
    // std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());

    // Reset solver for next iteration
    solver.reset(new Minisat::Solver());
    
    // No. of vertices in the Graph
    int n = g.getNoVertices();

    // Uncovered Edges in the Graph
    std::vector<Edge> uncoveredEdges = g.getEdges();
    
    // No. of vertices in vertexCover
    int k = sizeVertexCover;

    // Minimum required Size of Vertex Cover (Based on SureVerticesInPendantEdges[])
    int min_vc_size = ((int) sureVerticesInPendantEdges.size());
    
    // Literals in matrix form [ size = (n - |R|) * k]
    std::vector<std::vector<Minisat::Lit>> literals;
    for (int i = 0; i < n; i++) {       // initialize literals
        std::vector<Minisat::Lit> row;

        if (std::find(verNoEdge.begin(), verNoEdge.end(), i + 1) == verNoEdge.end()   &&   std::find(redundantVerticesInPendantEdges.begin(), redundantVerticesInPendantEdges.end(), i + 1) == redundantVerticesInPendantEdges.end()) {
            for (int j = 0; j < k; j++) {
                row.push_back(Minisat::mkLit(solver->newVar()));
            }
        }

        literals.push_back(row);
    }

    // Return UNSATISFIABLE, if proposed 'k' is less then the size of 'set of verticies (which have to be there in the vertex cover)'
    if (k < ((int) sureVerticesInPendantEdges.size())) {
        return false;

    } else {
        /* -------- Clauses -------- */

        // All Mandatory Vertices (in Set A) must be included in the Vertex Cover.
        for (int i = 0; i < ((int) sureVerticesInPendantEdges.size()); i++) {
            solver->addClause(literals.at(sureVerticesInPendantEdges.at(i) - 1).at(i));

            for (int x = 0; x < n; x++) {
                if (x != (sureVerticesInPendantEdges.at(i) - 1)  &&  (((int)literals.at(x).size()) != 0)) {
                    solver->addClause(~literals.at(x).at(i));
                }
            }

            for (int y = 0; y < k; y++) {
                if (y != i) {
                    solver->addClause(~literals.at(sureVerticesInPendantEdges.at(i) - 1).at(y));
                }
            }

            uncoveredEdges = removeIncidentEdges(sureVerticesInPendantEdges.at(i), uncoveredEdges);
        }


        // ----- At least one eligible vertex is the ith vertex in the remaining spaces of Vertex Cover. -----
        for (int i = min_vc_size; i < k; i++) {
            Minisat::vec<Minisat::Lit> clauseLiterals;

            for (int v = 0; v < n; v++) {
                if (((int)literals.at(v).size()) != 0  &&  std::find(sureVerticesInPendantEdges.begin(), sureVerticesInPendantEdges.end(), v + 1) == sureVerticesInPendantEdges.end()) {
                    clauseLiterals.push(literals.at(v).at(i));
                    
                    clauses_string += std::to_string(convertMatrixIndex_to_ArrayIndex(v, i, n, k) + 1) + " ";
                }
            }

            solver->addClause(clauseLiterals);
            clauses_string += "0\n";
        }

        // ----- No one (eligible) vertex can appear twice in the remaining spaces of Vertex Cover. -----
        for (int m = 0; m < n; m++) {
            if (((int)literals.at(m).size()) == 0  ||  std::find(sureVerticesInPendantEdges.begin(), sureVerticesInPendantEdges.end(), m + 1) != sureVerticesInPendantEdges.end()) {
                continue;
            }

            for (int p = min_vc_size; p < k; p++) {
                for (int q = p + 1; q < k; q++) {
                    solver->addClause(~literals.at(m).at(p), ~literals.at(m).at(q));
                    
                    clauses_string += std::to_string(-convertMatrixIndex_to_ArrayIndex(m, p, n, k) - 1) + " "
                                        + std::to_string(-convertMatrixIndex_to_ArrayIndex(m, q, n, k) - 1) + " "
                                        + "0\n";
                }
            }
        }


        // ----- No more than one eligible vertex appears in the mth position of the remaining spaces of Vertex Cover. -----
        for (int m = min_vc_size; m < k; m++) {
            for (int p = 0; p < n; p++) {
                if (((int)literals.at(p).size()) == 0   ||  std::find(sureVerticesInPendantEdges.begin(), sureVerticesInPendantEdges.end(), p + 1) != sureVerticesInPendantEdges.end()) {
                    continue;
                }

                for (int q = p + 1; q < n; q++) {
                    if (((int)literals.at(q).size()) == 0  ||  std::find(sureVerticesInPendantEdges.begin(), sureVerticesInPendantEdges.end(), q + 1) != sureVerticesInPendantEdges.end()) {
                        continue;
                    }

                    solver->addClause(~literals.at(p).at(m), ~literals.at(q).at(m));

                    clauses_string += std::to_string(-convertMatrixIndex_to_ArrayIndex(p, m, n, k) - 1) + " "
                                        + std::to_string(-convertMatrixIndex_to_ArrayIndex(q, m, n, k) - 1) + " "
                                        + "0\n";
                }
            }
        }
        
        // ----- Every Uncovered-Edge is incident to at least one vertex in the vertex cover. -----
        for (int x = 0; x < ((int) uncoveredEdges.size()); x++) {
            Minisat::vec<Minisat::Lit> clauseLiterals;

            int src = std::stoi(uncoveredEdges.at(x).getSrc());
            int dest = std::stoi(uncoveredEdges.at(x).getDest());
            
            if (((int)literals.at(src - 1).size()) != 0) {
                for (int j = min_vc_size; j < k; j++) {
                    clauseLiterals.push(literals.at(src - 1).at(j));
                    clauses_string += std::to_string(convertMatrixIndex_to_ArrayIndex(src - 1, j, n, k) + 1) + " ";
                }
            }

            if (((int)literals.at(dest - 1).size()) != 0) {
                for (int j = min_vc_size; j < k; j++) {
                    clauseLiterals.push(literals.at(dest - 1).at(j));
                    clauses_string += std::to_string(convertMatrixIndex_to_ArrayIndex(dest - 1, j, n, k) + 1) + " ";
                }
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
}


// Function to find vertexCover using cnfSATSolver - (Optimized)
std::vector<int> optimized_vertexCoverUsingCnfSATSolver (Graph g, std::unique_ptr<Minisat::Solver> &solver, bool &interrupted) {
    std::vector<int> vertexCover;
    std::string clauses_string;

    // Verticies with noEdges
    std::vector<int> verNoEdge;

    // Redundant-vertices (Vertices not required in the vertex-cover) of Pendant Edges
    std::vector<int> redundantVerticesInPendantEdges;

    // Sure-vertices (Vertices that have to be present in the vertex-cover) of Pendant Edges
    std::vector<int> sureVerticesInPendantEdges;


    if ((int) g.getEdges().size() != 0) {
        for (int i = 1; i <= g.getNoVertices(); i++) {
            bool satisfiable = optimized_cnfSATSolver(g, i, vertexCover, clauses_string, solver, verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges);
            
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