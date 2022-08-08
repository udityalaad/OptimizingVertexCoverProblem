#pragma once

#include <string>
#include <vector>
#include <set>


// CLASS AND FUNCTION DECLARATIONS GO HERE



/* ******************************************************************************** */
//                              Other - Common Functions
/* ******************************************************************************** */
// Function to covert vertexCover to a comma-separated string-format.
std::string vertexCover_toString_commaSeparated (std::vector<int> vertexCover);
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//                          Vertex Cover - Common Functions
/* ******************************************************************************** */
// Function to remove edges incident to a particular vertex from 'uncoveredEdges'-vector
std::vector<Edge> removeIncidentEdges (int vertex, std::vector<Edge> uncoveredEdges);
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//                  Vertex Cover - Using Approximate Algorithm 1
/* ******************************************************************************** */
// Function to compare 'noUncoveredEdges' (second value in pair); and then 'vertex' (first value in pair)
// Used to sort vector in decreasing order of 'noUncoveredEdges', and then in increasing order of 'vertex' (where 'noUncoveredEdges' are equal)
bool compareNoUncoveredEdgesDecreasing_andThen_vertexIncreasing (std::pair<int, int> &element1, std::pair<int, int> &element2);

// Function to find vertex with max. noIncidentUncoveredEdges
int findVertexWithMaxIncidentUncoveredEdges (int noVertices, std::vector<Edge> uncoveredEdges);

// Function to find Vertex Cover - Using Approximate Algorithm 1
std::vector<int> approxVC_1 (Graph g);
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//                      Vertex Cover - Using Approximate Algorithm 2
/* ******************************************************************************** */
// Function to find Vertex Cover - Using Approximate Algorithm 2
std::vector<int> approxVC_2 (Graph g);
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//              Vertex Cover - Using Optimized CNF-SAT SOLVER
/* ******************************************************************************** */
// Function to check whether an 'Integer-Vector' contains the given 'Element'
bool intVectorContains (std::vector<int> vec, int elem);

// Function to find vertices with no edges at all
std::vector<int> verticesWithNoEdge (Graph g);

// Function to find vertices with atleast 1 edge
std::vector<int> verticesWithEdge (Graph g);

// Function to find no. of Edges connected to the given vertex
int noEdgesConnectedToVertex (Graph g, int v);

// Function to find the redundant-vertices (Vertices that are not required in vertex-cover) in Pendant Edges (of the Graph).
// and Sure-vertices (Vertices that have to be present in the vertex-cover) of Pendant Edges (of the Graph).
void findRedundantAndSureVerticesInPendantEdges (Graph g, std::vector<int> &redundantVerticesInPendantEdges, std::set<int> &sureVerticesInPendantEdges);


// Function to check whether the given 'k' produces a SATISFIABLE VertexCover - (Optimized)
bool optimized_cnfSATSolver (Graph g, int sizeVertexCover, std::vector<int> &vertexCover, std::string &clauses_string, std::unique_ptr<Minisat::Solver> &solver, std::vector<int> &verNoEdge, std::vector<int> &redundantVerticesInPendantEdges, std::vector<int> &sureVerticesInPendantEdges);

// Function to find vertexCover using cnfSATSolver - (Optimized)
std::vector<int> optimized_vertexCoverUsingCnfSATSolver (Graph g, std::unique_ptr<Minisat::Solver> &solver, bool &interrupted);
/* ******************************************************************************** */
/* ******************************************************************************** */