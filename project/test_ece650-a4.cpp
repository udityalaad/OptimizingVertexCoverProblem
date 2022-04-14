/**
 * An example unit test using doctest. See documentation at
 * https://github.com/onqtam/doctest/blob/master/doc/markdown/tutorial.md
 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cstring>
#include <vector>
#include <iostream>


// defined std::unique_ptr
#include <memory>
//defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"


#include "a2_source_files/edge.hpp"
#include "a2_source_files/graph.hpp"
#include "a2_source_files/processes.hpp"

#include "a4_source_files/a4_processes.hpp"



bool checkIfExceptionRaisedInLineParsing (const std::string &line, std::string &cmd, int &noVert, std::vector<Edge> &edges, std::vector<std::string> &endPoints) {
    bool result = false;

    try {
        lineParsing(line, cmd, noVert, edges, endPoints);
    } catch (std::string  e) {
        result = true;
    } catch (const std::exception &e) {
        result = true;
    }

    return result;
}

bool checkIfExceptionRaisedInGraphSetNoVertices (Graph &g, int v) {
    bool result = false;

    try {
        g.setNoVertices(v);
    } catch (std::string  e) {
        result = true;
    } catch (const std::exception &e) {
        result = true;
    }

    return result;
}


bool checkIfExceptionRaisedInGraphSetEdges (Graph &g, std::vector<Edge> edges) {
    bool result = false;

    try {
        g.setEdges(edges);
    } catch (std::string  e) {
        result = true;
    } catch (const std::exception &e) {
        result = true;
    }

    return result;
}


bool checkIfExceptionRaisedInGenerateShortestPath (Graph g, std::string src, std::string dest) {
    bool result = false;

    try {
        g.generateShortestPath(src, dest);
    } catch (std::string  e) {
        result = true;
    } catch (const std::exception &e) {
        result = true;
    }

    return result;
}




TEST_CASE ("'Create Graph' + 'vertexCoverUsingCnfSATSolver' - Success + Failure") {
    Graph g;
    Graph tempGraph;

    std::string line;
    std::vector<Edge> tempEdges;

    std::string opCmd = "";
    int opNoVert = 0;
    std::vector<Edge> opEdges;
    std::vector<std::string> opEndPoints;
    std::string opErrorMessage = "";

    std::string vc_string = "";
    std::string clauses_string = "";
    int k = 0;
    
    std::vector<int> vertexCover_returned;
    std::vector<int> vertexCover_cnfSATSolver;

    std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());
    bool cnfSAT_interrupted = false;

    // ---------------------------------------------------
    // ------------------- Example 1 ---------------------
    // ---------------------------------------------------
    line = "V 15";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("2", "6"));
    tempEdges.push_back(Edge("2", "8"));
    tempEdges.push_back(Edge("2", "5"));
    tempEdges.push_back(Edge("6", "5"));
    tempEdges.push_back(Edge("5", "8"));
    tempEdges.push_back(Edge("6", "10"));
    tempEdges.push_back(Edge("10", "8"));
    tempGraph = Graph();
    tempGraph.setNoVertices(15);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 15\nE {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}");

    // Test -1 -  (k = 1) - Failure
    k = 1;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {2, 6, 8}));

    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
	// ---------------------------------------------------
    // ---------------------------------------------------

    
    // ---------------------------------------------------
    // ------------------- Example 2 ---------------------
    // ---------------------------------------------------
    line = "V 5";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,3>,<3,2>,<3,4>,<4,5>,<5,2>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1" ,"3"));
    tempEdges.push_back(Edge("3", "2"));
    tempEdges.push_back(Edge("3", "4"));
    tempEdges.push_back(Edge("4", "5"));
    tempEdges.push_back(Edge("5", "2"));
    tempGraph = Graph();
    tempGraph.setNoVertices(5);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 5\nE {<1,3>,<3,2>,<3,4>,<4,5>,<5,2>}");

    // Test -1 -  (k = 1) - Failure
    k = 1;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {3, 5}));
    
    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 3 ---------------------
    // ---------------------------------------------------
    line = "V 10";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<2,1>,<1,3>,<4,1>,<1,6>,<6,5>,<7,6>,<6,8>,<9,6>,<6,10>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("2" ,"1"));
    tempEdges.push_back(Edge("1", "3"));
    tempEdges.push_back(Edge("4", "1"));
    tempEdges.push_back(Edge("1", "6"));
    tempEdges.push_back(Edge("6", "5"));
    tempEdges.push_back(Edge("7", "6"));
    tempEdges.push_back(Edge("6", "8"));
    tempEdges.push_back(Edge("9", "6"));
    tempEdges.push_back(Edge("6", "10"));
    tempGraph = Graph();
    tempGraph.setNoVertices(10);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 10\nE {<2,1>,<1,3>,<4,1>,<1,6>,<6,5>,<7,6>,<6,8>,<9,6>,<6,10>}");

    // Test -1 -  (k = 1) - Failure
    k = 1;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 6}));
    
    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Example 4 ---------------------
    // ---------------------------------------------------
    line = "V 14";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<2,1>,<1,3>,<1,4>,<3,5>,<3,6>,<7,4>,<4,10>,<10,8>,<8,12>,<12,9>,<9,14>,<14,10>,<8,11>,<11,12>,<12,14>,<14,13>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("2" ,"1"));
    tempEdges.push_back(Edge("1", "3"));
    tempEdges.push_back(Edge("1", "4"));
    tempEdges.push_back(Edge("3", "5"));
    tempEdges.push_back(Edge("3", "6"));
    tempEdges.push_back(Edge("7", "4"));
    tempEdges.push_back(Edge("4", "10"));
    tempEdges.push_back(Edge("10", "8"));
    tempEdges.push_back(Edge("8", "12"));
    tempEdges.push_back(Edge("12", "9"));
    tempEdges.push_back(Edge("9", "14"));
    tempEdges.push_back(Edge("14", "10"));
    tempEdges.push_back(Edge("8", "11"));
    tempEdges.push_back(Edge("11", "12"));
    tempEdges.push_back(Edge("12", "14"));
    tempEdges.push_back(Edge("14", "13"));
    tempGraph = Graph();
    tempGraph.setNoVertices(14);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 14\nE {<2,1>,<1,3>,<1,4>,<3,5>,<3,6>,<7,4>,<4,10>,<10,8>,<8,12>,<12,9>,<9,14>,<14,10>,<8,11>,<11,12>,<12,14>,<14,13>}");

    // Test -1 -  (k = 1) - Failure
    k = 1;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -3 -  (k = 3) - Failure
    k = 3;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -4 -  (k = 4) - Failure
    k = 4;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 3, 4, 8, 12, 14}));
    
    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 5 ---------------------
    // ---------------------------------------------------
    line = "V 7";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,2>,<1,3>,<2,4>,<4,5>,<3,4>,<4,6>,<5,7>,<6,7>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1" ,"2"));
    tempEdges.push_back(Edge("1", "3"));
    tempEdges.push_back(Edge("2", "4"));
    tempEdges.push_back(Edge("4", "5"));
    tempEdges.push_back(Edge("3", "4"));
    tempEdges.push_back(Edge("4", "6"));
    tempEdges.push_back(Edge("5", "7"));
    tempEdges.push_back(Edge("6", "7"));
    tempGraph = Graph();
    tempGraph.setNoVertices(7);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 7\nE {<1,2>,<1,3>,<2,4>,<4,5>,<3,4>,<4,6>,<5,7>,<6,7>}");

    // Test -1 -  (k = 1) - Failure
    k = 1;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 4, 7}));
    
    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 6 ---------------------
    // ---------------------------------------------------
    line = "V 14";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<2,8>,<8,1>,<1,6>,<6,3>,<4,1>,<1,5>,<5,6>,<6,7>,<9,8>,<8,10>,<3,11>,<11,12>,<13,11>,<11,14>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("2" ,"8"));
    tempEdges.push_back(Edge("8", "1"));
    tempEdges.push_back(Edge("1", "6"));
    tempEdges.push_back(Edge("6", "3"));
    tempEdges.push_back(Edge("4", "1"));
    tempEdges.push_back(Edge("1", "5"));
    tempEdges.push_back(Edge("5", "6"));
    tempEdges.push_back(Edge("6", "7"));
    tempEdges.push_back(Edge("9", "8"));
    tempEdges.push_back(Edge("8", "10"));
    tempEdges.push_back(Edge("3", "11"));
    tempEdges.push_back(Edge("11", "12"));
    tempEdges.push_back(Edge("13", "11"));
    tempEdges.push_back(Edge("11", "14"));
    tempGraph = Graph();
    tempGraph.setNoVertices(14);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 14\nE {<2,8>,<8,1>,<1,6>,<6,3>,<4,1>,<1,5>,<5,6>,<6,7>,<9,8>,<8,10>,<3,11>,<11,12>,<13,11>,<11,14>}");

    // Test -1 -  (k = 1) - Failure
    k = 1;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 6, 8, 11}));
    
    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 7 ---------------------
    // ---------------------------------------------------
    line = "V 11";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,5>,<5,2>,<3,10>,<10,1>,<1,4>,<6,5>,<2,7>,<7,8>,<4,7>,<7,9>,<10,11>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1" ,"5"));
    tempEdges.push_back(Edge("5", "2"));
    tempEdges.push_back(Edge("3", "10"));
    tempEdges.push_back(Edge("10", "1"));
    tempEdges.push_back(Edge("1", "4"));
    tempEdges.push_back(Edge("6", "5"));
    tempEdges.push_back(Edge("2", "7"));
    tempEdges.push_back(Edge("7", "8"));
    tempEdges.push_back(Edge("4", "7"));
    tempEdges.push_back(Edge("7", "9"));
    tempEdges.push_back(Edge("10", "11"));
    tempGraph = Graph();
    tempGraph.setNoVertices(11);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 11\nE {<1,5>,<5,2>,<3,10>,<10,1>,<1,4>,<6,5>,<2,7>,<7,8>,<4,7>,<7,9>,<10,11>}");

    // Test -1 -  (k = 1) - Failure
    k = 1;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 5, 7, 10}));
    
    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 8 ---------------------
    //  Graph with unconnected edges = 2 Parts
    // ---------------------------------------------------
    line = "V 12";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,2>,<1,3>,<2,4>,<4,5>,<3,4>,<4,6>,<5,7>,<6,7>,<12,10>,<10,11>,<9,8>,<9,11>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1" ,"2"));
    tempEdges.push_back(Edge("1", "3"));
    tempEdges.push_back(Edge("2", "4"));
    tempEdges.push_back(Edge("4", "5"));
    tempEdges.push_back(Edge("3", "4"));
    tempEdges.push_back(Edge("4", "6"));
    tempEdges.push_back(Edge("5", "7"));
    tempEdges.push_back(Edge("6", "7"));
    tempEdges.push_back(Edge("12", "10"));
    tempEdges.push_back(Edge("10", "11"));
    tempEdges.push_back(Edge("9", "8"));
    tempEdges.push_back(Edge("9", "11"));
    tempEdges.push_back(Edge("10", "8"));
    tempGraph = Graph();
    tempGraph.setNoVertices(12);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 12\nE {<1,2>,<1,3>,<2,4>,<4,5>,<3,4>,<4,6>,<5,7>,<6,7>,<12,10>,<10,11>,<9,8>,<9,11>,<10,8>}");


    // Test -1 -  (k = 1) - Failure
    k = 1;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -3 -  (k = 3) - Failure
    k = 3;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test 0 - Success
    // k = 5;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 4, 7, 9, 10}));
    
    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Example 9 ---------------------
    //  Graph with unconnected edges = 4 Parts
    // ---------------------------------------------------
    line = "V 26";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<13,14>,<4,2>,<20,19>,<16,15>,<5,4>,<6,7>,<8,7>,<5,7>,<5,6>,<18,19>,<3,4>,<2,5>,<25,24>,<13,15>,<14,12>,<12,13>,<1,5>,<11,14>,<20,18>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("13" ,"14"));
    tempEdges.push_back(Edge("4", "2"));
    tempEdges.push_back(Edge("20", "19"));
    tempEdges.push_back(Edge("16", "15"));
    tempEdges.push_back(Edge("5", "4"));
    tempEdges.push_back(Edge("6", "7"));
    tempEdges.push_back(Edge("8", "7"));
    tempEdges.push_back(Edge("5", "7"));
    tempEdges.push_back(Edge("5", "6"));
    tempEdges.push_back(Edge("18", "19"));
    tempEdges.push_back(Edge("3", "4"));
    tempEdges.push_back(Edge("2", "5"));
    tempEdges.push_back(Edge("25", "24"));
    tempEdges.push_back(Edge("13", "15"));
    tempEdges.push_back(Edge("14", "12"));
    tempEdges.push_back(Edge("12", "13"));
    tempEdges.push_back(Edge("1", "5"));
    tempEdges.push_back(Edge("11", "14"));
    tempEdges.push_back(Edge("20", "18"));
    tempGraph = Graph();
    tempGraph.setNoVertices(26);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 26\nE {<13,14>,<4,2>,<20,19>,<16,15>,<5,4>,<6,7>,<8,7>,<5,7>,<5,6>,<18,19>,<3,4>,<2,5>,<25,24>,<13,15>,<14,12>,<12,13>,<1,5>,<11,14>,<20,18>}");
    
    
    // Test -1 -  (k = 1) - Failure
    k = 1;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -3 -  (k = 3) - Failure
    k = 3;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -4 -  (k = 4) - Failure
    k = 4;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -5 -  (k = 5) - Failure
    k = 5;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -6 -  (k = 6) - Failure
    k = 6;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test 0 - Success
    // clauses_string = "";
    // vertexCover_cnfSATSolver.clear();
    // vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    // CHECK(intVectorEquals(vertexCover_returned, {4, 5, 7, 12, 14, 15, 19, 20, 25}));
    // k = vertexCover_returned.size();
    // CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    // CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 10 ---------------------
    //  Graph with only 1 edge
    // ---------------------------------------------------
    line = "V 7";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<2,6>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("2", "6"));
    tempGraph = Graph();
    tempGraph.setNoVertices(7);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 7\nE {<2,6>}");

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {2}));
    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    // ---------------------------------------------------
	// ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Example 11 ---------------------
    //  Graph with no edges
    // ---------------------------------------------------
    line = "V 5";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));
    CHECK(g.getEdges().size() == 0);

    // Graph to check against
    tempEdges.clear();
    tempGraph = Graph();
    tempGraph.setNoVertices(5);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 5\nE {}");

    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {}));
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 12 ---------------------
    //  Graph with only 2 vertices
    // ---------------------------------------------------
    line = "V 2";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,2>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1", "2"));
    tempGraph = Graph();
    tempGraph.setNoVertices(2);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 2\nE {<1,2>}");
    

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {2}));
    
    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 13 ---------------------
    //  Graph with only 1 vertex
    // ---------------------------------------------------
    line = "V 1";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempGraph = Graph();
    tempGraph.setNoVertices(1);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 1\nE {}");

    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {}));
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 14 ---------------------
    // ---------------------------------------------------
    line = "V 3";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,2>,<1,3>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1", "2"));
    tempEdges.push_back(Edge("1", "3"));
    tempGraph = Graph();
    tempGraph.setNoVertices(3);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 3\nE {<1,2>,<1,3>}");

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1}));
    
    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------

    
    // ---------------------------------------------------
    // ------------------- Example 15 ---------------------
    // ---------------------------------------------------
    line = "V 3";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,2>,<1,3>,<2,3>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1" ,"2"));
    tempEdges.push_back(Edge("1", "3"));
    tempEdges.push_back(Edge("2", "3"));
    tempGraph = Graph();
    tempGraph.setNoVertices(3);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 3\nE {<1,2>,<1,3>,<2,3>}");

    // Test -1 -  (k = 1) - Failure
    k = 1;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2}));
    
    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 16 ---------------------
    // ---------------------------------------------------
    line = "V 5";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,4>,<1,5>,<2,4>,<2,5>,<3,4>,<4,5>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1" ,"4"));
    tempEdges.push_back(Edge("1", "5"));
    tempEdges.push_back(Edge("2", "4"));
    tempEdges.push_back(Edge("2", "5"));
    tempEdges.push_back(Edge("3", "4"));
    tempEdges.push_back(Edge("4", "5"));
    tempGraph = Graph();
    tempGraph.setNoVertices(5);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 5\nE {<1,4>,<1,5>,<2,4>,<2,5>,<3,4>,<4,5>}");

    // Test -1 -  (k = 1) - Failure
    k = 1;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {4, 5}));
    
    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Example 17 ---------------------
    // ---------------------------------------------------
    line = "V 5";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,2>,<3,4>,<3,5>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1" ,"2"));
    tempEdges.push_back(Edge("3", "4"));
    tempEdges.push_back(Edge("3", "5"));
    tempGraph = Graph();
    tempGraph.setNoVertices(5);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 5\nE {<1,2>,<3,4>,<3,5>}");

    // Test -1 -  (k = 1) - Failure
    k = 1;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 3}));
    
    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 18 ---------------------
    // ---------------------------------------------------
    line = "V 10";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,2>,<4,3>,<5,6>,<8,7>,<9,10>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1" ,"2"));
    tempEdges.push_back(Edge("4", "3"));
    tempEdges.push_back(Edge("5", "6"));
    tempEdges.push_back(Edge("8", "7"));
    tempEdges.push_back(Edge("9", "10"));
    tempGraph = Graph();
    tempGraph.setNoVertices(10);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 10\nE {<1,2>,<4,3>,<5,6>,<8,7>,<9,10>}");


    // Test -1 -  (k = 1) - Failure
    k = 1;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -3 -  (k = 3) - Failure
    k = 3;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));

    // Test -4 - (k = 4) - Failure
    k = 4;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));


    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 3, 5, 7, 9}));

    k = vertexCover_returned.size();
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------
}






TEST_CASE ("'Create Graph' + 'Check CNF Satisfiability' - Success + Failure") {
    Graph g;
    Graph tempGraph;

    std::string line;
    std::vector<Edge> tempEdges;

    std::string opCmd = "";
    int opNoVert = 0;
    std::vector<Edge> opEdges;
    std::vector<std::string> opEndPoints;
    std::string opErrorMessage = "";

    
    std::string vc_string = "";
    std::string clauses_string = "";
    int k = 0;


    std::vector<int> vertexCover_returned;
    std::vector<int> vertexCover_cnfSATSolver;


    std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());


    // ---------------------------------------------------
    // ------------------- Example 1 ---------------------
    // ---------------------------------------------------
    line = "V 3";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,2>,<1,3>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1", "2"));
    tempEdges.push_back(Edge("1", "3"));
    tempGraph = Graph();
    tempGraph.setNoVertices(3);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 3\nE {<1,2>,<1,3>}");

    // Test 1 - (k = 1) - Success
    k = 1;
    clauses_string = "";
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(clauses_string == "1 2 3 0\n-1 -2 0\n-1 -3 0\n-2 -3 0\n2 1 0\n3 1 0\n");

    // Test 2 - (k = 2) - Success
    k = 2;
    clauses_string = "";
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(clauses_string == "1 3 5 0\n2 4 6 0\n-1 -2 0\n-3 -4 0\n-5 -6 0\n-1 -3 0\n-1 -5 0\n-3 -5 0\n-2 -4 0\n-2 -6 0\n-4 -6 0\n3 1 4 2 0\n5 1 6 2 0\n");
    // ---------------------------------------------------
	// ---------------------------------------------------

    
    // ---------------------------------------------------
    // ------------------- Example 2 ---------------------
    // ---------------------------------------------------
    line = "V 3";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,2>,<1,3>,<2,3>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1" ,"2"));
    tempEdges.push_back(Edge("1", "3"));
    tempEdges.push_back(Edge("2", "3"));
    tempGraph = Graph();
    tempGraph.setNoVertices(3);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 3\nE {<1,2>,<1,3>,<2,3>}");
    
    // Test 1 - (k = 2) - Success
    k = 2;
    clauses_string = "";
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(clauses_string == "1 3 5 0\n2 4 6 0\n-1 -2 0\n-3 -4 0\n-5 -6 0\n-1 -3 0\n-1 -5 0\n-3 -5 0\n-2 -4 0\n-2 -6 0\n-4 -6 0\n3 1 4 2 0\n5 1 6 2 0\n5 3 6 4 0\n");
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 3 ---------------------
    // ---------------------------------------------------
    line = "V 5";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,4>,<1,5>,<2,4>,<2,5>,<3,4>,<4,5>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1" ,"4"));
    tempEdges.push_back(Edge("1", "5"));
    tempEdges.push_back(Edge("2", "4"));
    tempEdges.push_back(Edge("2", "5"));
    tempEdges.push_back(Edge("3", "4"));
    tempEdges.push_back(Edge("4", "5"));
    tempGraph = Graph();
    tempGraph.setNoVertices(5);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 5\nE {<1,4>,<1,5>,<2,4>,<2,5>,<3,4>,<4,5>}");
    
    // Test 1 - (k = 3) - Success
    k = 3;
    clauses_string = "";
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(clauses_string == "1 4 7 10 13 0\n2 5 8 11 14 0\n3 6 9 12 15 0\n-1 -2 0\n-1 -3 0\n-2 -3 0\n-4 -5 0\n-4 -6 0\n-5 -6 0\n-7 -8 0\n-7 -9 0\n-8 -9 0\n-10 -11 0\n-10 -12 0\n-11 -12 0\n-13 -14 0\n-13 -15 0\n-14 -15 0\n-1 -4 0\n-1 -7 0\n-1 -10 0\n-1 -13 0\n-4 -7 0\n-4 -10 0\n-4 -13 0\n-7 -10 0\n-7 -13 0\n-10 -13 0\n-2 -5 0\n-2 -8 0\n-2 -11 0\n-2 -14 0\n-5 -8 0\n-5 -11 0\n-5 -14 0\n-8 -11 0\n-8 -14 0\n-11 -14 0\n-3 -6 0\n-3 -9 0\n-3 -12 0\n-3 -15 0\n-6 -9 0\n-6 -12 0\n-6 -15 0\n-9 -12 0\n-9 -15 0\n-12 -15 0\n10 1 11 2 12 3 0\n13 1 14 2 15 3 0\n10 4 11 5 12 6 0\n13 4 14 5 15 6 0\n10 7 11 8 12 9 0\n13 10 14 11 15 12 0\n");

    // Test 2 - (k = 4) - Success
    k = 4;
    clauses_string = "";
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(clauses_string == "1 5 9 13 17 0\n2 6 10 14 18 0\n3 7 11 15 19 0\n4 8 12 16 20 0\n-1 -2 0\n-1 -3 0\n-1 -4 0\n-2 -3 0\n-2 -4 0\n-3 -4 0\n-5 -6 0\n-5 -7 0\n-5 -8 0\n-6 -7 0\n-6 -8 0\n-7 -8 0\n-9 -10 0\n-9 -11 0\n-9 -12 0\n-10 -11 0\n-10 -12 0\n-11 -12 0\n-13 -14 0\n-13 -15 0\n-13 -16 0\n-14 -15 0\n-14 -16 0\n-15 -16 0\n-17 -18 0\n-17 -19 0\n-17 -20 0\n-18 -19 0\n-18 -20 0\n-19 -20 0\n-1 -5 0\n-1 -9 0\n-1 -13 0\n-1 -17 0\n-5 -9 0\n-5 -13 0\n-5 -17 0\n-9 -13 0\n-9 -17 0\n-13 -17 0\n-2 -6 0\n-2 -10 0\n-2 -14 0\n-2 -18 0\n-6 -10 0\n-6 -14 0\n-6 -18 0\n-10 -14 0\n-10 -18 0\n-14 -18 0\n-3 -7 0\n-3 -11 0\n-3 -15 0\n-3 -19 0\n-7 -11 0\n-7 -15 0\n-7 -19 0\n-11 -15 0\n-11 -19 0\n-15 -19 0\n-4 -8 0\n-4 -12 0\n-4 -16 0\n-4 -20 0\n-8 -12 0\n-8 -16 0\n-8 -20 0\n-12 -16 0\n-12 -20 0\n-16 -20 0\n13 1 14 2 15 3 16 4 0\n17 1 18 2 19 3 20 4 0\n13 5 14 6 15 7 16 8 0\n17 5 18 6 19 7 20 8 0\n13 9 14 10 15 11 16 12 0\n17 13 18 14 19 15 20 16 0\n");
    // ---------------------------------------------------
	// ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Example 4 ---------------------
    // ---------------------------------------------------
    line = "V 5";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,2>,<3,4>,<3,5>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1" ,"2"));
    tempEdges.push_back(Edge("3", "4"));
    tempEdges.push_back(Edge("3", "5"));
    tempGraph = Graph();
    tempGraph.setNoVertices(5);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 5\nE {<1,2>,<3,4>,<3,5>}");
    
    // Test 1 - (k = 2) - Success
    k = 2;
    clauses_string = "";
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(clauses_string == "1 3 5 7 9 0\n2 4 6 8 10 0\n-1 -2 0\n-3 -4 0\n-5 -6 0\n-7 -8 0\n-9 -10 0\n-1 -3 0\n-1 -5 0\n-1 -7 0\n-1 -9 0\n-3 -5 0\n-3 -7 0\n-3 -9 0\n-5 -7 0\n-5 -9 0\n-7 -9 0\n-2 -4 0\n-2 -6 0\n-2 -8 0\n-2 -10 0\n-4 -6 0\n-4 -8 0\n-4 -10 0\n-6 -8 0\n-6 -10 0\n-8 -10 0\n3 1 4 2 0\n7 5 8 6 0\n9 5 10 6 0\n");
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 5 ---------------------
    // ---------------------------------------------------
    line = "V 10";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);

    line = "E {<1,2>,<4,3>,<5,6>,<8,7>,<9,10>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setEdges(opEdges);
    CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // Graph to check against
    tempEdges.clear();
    tempEdges.push_back(Edge("1" ,"2"));
    tempEdges.push_back(Edge("4", "3"));
    tempEdges.push_back(Edge("5", "6"));
    tempEdges.push_back(Edge("8", "7"));
    tempEdges.push_back(Edge("9", "10"));
    tempGraph = Graph();
    tempGraph.setNoVertices(10);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 10\nE {<1,2>,<4,3>,<5,6>,<8,7>,<9,10>}");

    // Test -4 - (k = 4) - Failure
    k = 4;
    clauses_string = "";
    CHECK(!cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(clauses_string == "1 5 9 13 17 21 25 29 33 37 0\n2 6 10 14 18 22 26 30 34 38 0\n3 7 11 15 19 23 27 31 35 39 0\n4 8 12 16 20 24 28 32 36 40 0\n-1 -2 0\n-1 -3 0\n-1 -4 0\n-2 -3 0\n-2 -4 0\n-3 -4 0\n-5 -6 0\n-5 -7 0\n-5 -8 0\n-6 -7 0\n-6 -8 0\n-7 -8 0\n-9 -10 0\n-9 -11 0\n-9 -12 0\n-10 -11 0\n-10 -12 0\n-11 -12 0\n-13 -14 0\n-13 -15 0\n-13 -16 0\n-14 -15 0\n-14 -16 0\n-15 -16 0\n-17 -18 0\n-17 -19 0\n-17 -20 0\n-18 -19 0\n-18 -20 0\n-19 -20 0\n-21 -22 0\n-21 -23 0\n-21 -24 0\n-22 -23 0\n-22 -24 0\n-23 -24 0\n-25 -26 0\n-25 -27 0\n-25 -28 0\n-26 -27 0\n-26 -28 0\n-27 -28 0\n-29 -30 0\n-29 -31 0\n-29 -32 0\n-30 -31 0\n-30 -32 0\n-31 -32 0\n-33 -34 0\n-33 -35 0\n-33 -36 0\n-34 -35 0\n-34 -36 0\n-35 -36 0\n-37 -38 0\n-37 -39 0\n-37 -40 0\n-38 -39 0\n-38 -40 0\n-39 -40 0\n-1 -5 0\n-1 -9 0\n-1 -13 0\n-1 -17 0\n-1 -21 0\n-1 -25 0\n-1 -29 0\n-1 -33 0\n-1 -37 0\n-5 -9 0\n-5 -13 0\n-5 -17 0\n-5 -21 0\n-5 -25 0\n-5 -29 0\n-5 -33 0\n-5 -37 0\n-9 -13 0\n-9 -17 0\n-9 -21 0\n-9 -25 0\n-9 -29 0\n-9 -33 0\n-9 -37 0\n-13 -17 0\n-13 -21 0\n-13 -25 0\n-13 -29 0\n-13 -33 0\n-13 -37 0\n-17 -21 0\n-17 -25 0\n-17 -29 0\n-17 -33 0\n-17 -37 0\n-21 -25 0\n-21 -29 0\n-21 -33 0\n-21 -37 0\n-25 -29 0\n-25 -33 0\n-25 -37 0\n-29 -33 0\n-29 -37 0\n-33 -37 0\n-2 -6 0\n-2 -10 0\n-2 -14 0\n-2 -18 0\n-2 -22 0\n-2 -26 0\n-2 -30 0\n-2 -34 0\n-2 -38 0\n-6 -10 0\n-6 -14 0\n-6 -18 0\n-6 -22 0\n-6 -26 0\n-6 -30 0\n-6 -34 0\n-6 -38 0\n-10 -14 0\n-10 -18 0\n-10 -22 0\n-10 -26 0\n-10 -30 0\n-10 -34 0\n-10 -38 0\n-14 -18 0\n-14 -22 0\n-14 -26 0\n-14 -30 0\n-14 -34 0\n-14 -38 0\n-18 -22 0\n-18 -26 0\n-18 -30 0\n-18 -34 0\n-18 -38 0\n-22 -26 0\n-22 -30 0\n-22 -34 0\n-22 -38 0\n-26 -30 0\n-26 -34 0\n-26 -38 0\n-30 -34 0\n-30 -38 0\n-34 -38 0\n-3 -7 0\n-3 -11 0\n-3 -15 0\n-3 -19 0\n-3 -23 0\n-3 -27 0\n-3 -31 0\n-3 -35 0\n-3 -39 0\n-7 -11 0\n-7 -15 0\n-7 -19 0\n-7 -23 0\n-7 -27 0\n-7 -31 0\n-7 -35 0\n-7 -39 0\n-11 -15 0\n-11 -19 0\n-11 -23 0\n-11 -27 0\n-11 -31 0\n-11 -35 0\n-11 -39 0\n-15 -19 0\n-15 -23 0\n-15 -27 0\n-15 -31 0\n-15 -35 0\n-15 -39 0\n-19 -23 0\n-19 -27 0\n-19 -31 0\n-19 -35 0\n-19 -39 0\n-23 -27 0\n-23 -31 0\n-23 -35 0\n-23 -39 0\n-27 -31 0\n-27 -35 0\n-27 -39 0\n-31 -35 0\n-31 -39 0\n-35 -39 0\n-4 -8 0\n-4 -12 0\n-4 -16 0\n-4 -20 0\n-4 -24 0\n-4 -28 0\n-4 -32 0\n-4 -36 0\n-4 -40 0\n-8 -12 0\n-8 -16 0\n-8 -20 0\n-8 -24 0\n-8 -28 0\n-8 -32 0\n-8 -36 0\n-8 -40 0\n-12 -16 0\n-12 -20 0\n-12 -24 0\n-12 -28 0\n-12 -32 0\n-12 -36 0\n-12 -40 0\n-16 -20 0\n-16 -24 0\n-16 -28 0\n-16 -32 0\n-16 -36 0\n-16 -40 0\n-20 -24 0\n-20 -28 0\n-20 -32 0\n-20 -36 0\n-20 -40 0\n-24 -28 0\n-24 -32 0\n-24 -36 0\n-24 -40 0\n-28 -32 0\n-28 -36 0\n-28 -40 0\n-32 -36 0\n-32 -40 0\n-36 -40 0\n5 1 6 2 7 3 8 4 0\n9 13 10 14 11 15 12 16 0\n21 17 22 18 23 19 24 20 0\n25 29 26 30 27 31 28 32 0\n37 33 38 34 39 35 40 36 0\n");


    // Test 2 - (k = 5) - Success
    k = 5;
    clauses_string = "";
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(clauses_string == "1 6 11 16 21 26 31 36 41 46 0\n2 7 12 17 22 27 32 37 42 47 0\n3 8 13 18 23 28 33 38 43 48 0\n4 9 14 19 24 29 34 39 44 49 0\n5 10 15 20 25 30 35 40 45 50 0\n-1 -2 0\n-1 -3 0\n-1 -4 0\n-1 -5 0\n-2 -3 0\n-2 -4 0\n-2 -5 0\n-3 -4 0\n-3 -5 0\n-4 -5 0\n-6 -7 0\n-6 -8 0\n-6 -9 0\n-6 -10 0\n-7 -8 0\n-7 -9 0\n-7 -10 0\n-8 -9 0\n-8 -10 0\n-9 -10 0\n-11 -12 0\n-11 -13 0\n-11 -14 0\n-11 -15 0\n-12 -13 0\n-12 -14 0\n-12 -15 0\n-13 -14 0\n-13 -15 0\n-14 -15 0\n-16 -17 0\n-16 -18 0\n-16 -19 0\n-16 -20 0\n-17 -18 0\n-17 -19 0\n-17 -20 0\n-18 -19 0\n-18 -20 0\n-19 -20 0\n-21 -22 0\n-21 -23 0\n-21 -24 0\n-21 -25 0\n-22 -23 0\n-22 -24 0\n-22 -25 0\n-23 -24 0\n-23 -25 0\n-24 -25 0\n-26 -27 0\n-26 -28 0\n-26 -29 0\n-26 -30 0\n-27 -28 0\n-27 -29 0\n-27 -30 0\n-28 -29 0\n-28 -30 0\n-29 -30 0\n-31 -32 0\n-31 -33 0\n-31 -34 0\n-31 -35 0\n-32 -33 0\n-32 -34 0\n-32 -35 0\n-33 -34 0\n-33 -35 0\n-34 -35 0\n-36 -37 0\n-36 -38 0\n-36 -39 0\n-36 -40 0\n-37 -38 0\n-37 -39 0\n-37 -40 0\n-38 -39 0\n-38 -40 0\n-39 -40 0\n-41 -42 0\n-41 -43 0\n-41 -44 0\n-41 -45 0\n-42 -43 0\n-42 -44 0\n-42 -45 0\n-43 -44 0\n-43 -45 0\n-44 -45 0\n-46 -47 0\n-46 -48 0\n-46 -49 0\n-46 -50 0\n-47 -48 0\n-47 -49 0\n-47 -50 0\n-48 -49 0\n-48 -50 0\n-49 -50 0\n-1 -6 0\n-1 -11 0\n-1 -16 0\n-1 -21 0\n-1 -26 0\n-1 -31 0\n-1 -36 0\n-1 -41 0\n-1 -46 0\n-6 -11 0\n-6 -16 0\n-6 -21 0\n-6 -26 0\n-6 -31 0\n-6 -36 0\n-6 -41 0\n-6 -46 0\n-11 -16 0\n-11 -21 0\n-11 -26 0\n-11 -31 0\n-11 -36 0\n-11 -41 0\n-11 -46 0\n-16 -21 0\n-16 -26 0\n-16 -31 0\n-16 -36 0\n-16 -41 0\n-16 -46 0\n-21 -26 0\n-21 -31 0\n-21 -36 0\n-21 -41 0\n-21 -46 0\n-26 -31 0\n-26 -36 0\n-26 -41 0\n-26 -46 0\n-31 -36 0\n-31 -41 0\n-31 -46 0\n-36 -41 0\n-36 -46 0\n-41 -46 0\n-2 -7 0\n-2 -12 0\n-2 -17 0\n-2 -22 0\n-2 -27 0\n-2 -32 0\n-2 -37 0\n-2 -42 0\n-2 -47 0\n-7 -12 0\n-7 -17 0\n-7 -22 0\n-7 -27 0\n-7 -32 0\n-7 -37 0\n-7 -42 0\n-7 -47 0\n-12 -17 0\n-12 -22 0\n-12 -27 0\n-12 -32 0\n-12 -37 0\n-12 -42 0\n-12 -47 0\n-17 -22 0\n-17 -27 0\n-17 -32 0\n-17 -37 0\n-17 -42 0\n-17 -47 0\n-22 -27 0\n-22 -32 0\n-22 -37 0\n-22 -42 0\n-22 -47 0\n-27 -32 0\n-27 -37 0\n-27 -42 0\n-27 -47 0\n-32 -37 0\n-32 -42 0\n-32 -47 0\n-37 -42 0\n-37 -47 0\n-42 -47 0\n-3 -8 0\n-3 -13 0\n-3 -18 0\n-3 -23 0\n-3 -28 0\n-3 -33 0\n-3 -38 0\n-3 -43 0\n-3 -48 0\n-8 -13 0\n-8 -18 0\n-8 -23 0\n-8 -28 0\n-8 -33 0\n-8 -38 0\n-8 -43 0\n-8 -48 0\n-13 -18 0\n-13 -23 0\n-13 -28 0\n-13 -33 0\n-13 -38 0\n-13 -43 0\n-13 -48 0\n-18 -23 0\n-18 -28 0\n-18 -33 0\n-18 -38 0\n-18 -43 0\n-18 -48 0\n-23 -28 0\n-23 -33 0\n-23 -38 0\n-23 -43 0\n-23 -48 0\n-28 -33 0\n-28 -38 0\n-28 -43 0\n-28 -48 0\n-33 -38 0\n-33 -43 0\n-33 -48 0\n-38 -43 0\n-38 -48 0\n-43 -48 0\n-4 -9 0\n-4 -14 0\n-4 -19 0\n-4 -24 0\n-4 -29 0\n-4 -34 0\n-4 -39 0\n-4 -44 0\n-4 -49 0\n-9 -14 0\n-9 -19 0\n-9 -24 0\n-9 -29 0\n-9 -34 0\n-9 -39 0\n-9 -44 0\n-9 -49 0\n-14 -19 0\n-14 -24 0\n-14 -29 0\n-14 -34 0\n-14 -39 0\n-14 -44 0\n-14 -49 0\n-19 -24 0\n-19 -29 0\n-19 -34 0\n-19 -39 0\n-19 -44 0\n-19 -49 0\n-24 -29 0\n-24 -34 0\n-24 -39 0\n-24 -44 0\n-24 -49 0\n-29 -34 0\n-29 -39 0\n-29 -44 0\n-29 -49 0\n-34 -39 0\n-34 -44 0\n-34 -49 0\n-39 -44 0\n-39 -49 0\n-44 -49 0\n-5 -10 0\n-5 -15 0\n-5 -20 0\n-5 -25 0\n-5 -30 0\n-5 -35 0\n-5 -40 0\n-5 -45 0\n-5 -50 0\n-10 -15 0\n-10 -20 0\n-10 -25 0\n-10 -30 0\n-10 -35 0\n-10 -40 0\n-10 -45 0\n-10 -50 0\n-15 -20 0\n-15 -25 0\n-15 -30 0\n-15 -35 0\n-15 -40 0\n-15 -45 0\n-15 -50 0\n-20 -25 0\n-20 -30 0\n-20 -35 0\n-20 -40 0\n-20 -45 0\n-20 -50 0\n-25 -30 0\n-25 -35 0\n-25 -40 0\n-25 -45 0\n-25 -50 0\n-30 -35 0\n-30 -40 0\n-30 -45 0\n-30 -50 0\n-35 -40 0\n-35 -45 0\n-35 -50 0\n-40 -45 0\n-40 -50 0\n-45 -50 0\n6 1 7 2 8 3 9 4 10 5 0\n11 16 12 17 13 18 14 19 15 20 0\n26 21 27 22 28 23 29 24 30 25 0\n31 36 32 37 33 38 34 39 35 40 0\n46 41 47 42 48 43 49 44 50 45 0\n");


    // Test 3 - (k = 7) - Success
    k = 7;
    clauses_string = "";
    CHECK(cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver));
    CHECK(clauses_string == "1 8 15 22 29 36 43 50 57 64 0\n2 9 16 23 30 37 44 51 58 65 0\n3 10 17 24 31 38 45 52 59 66 0\n4 11 18 25 32 39 46 53 60 67 0\n5 12 19 26 33 40 47 54 61 68 0\n6 13 20 27 34 41 48 55 62 69 0\n7 14 21 28 35 42 49 56 63 70 0\n-1 -2 0\n-1 -3 0\n-1 -4 0\n-1 -5 0\n-1 -6 0\n-1 -7 0\n-2 -3 0\n-2 -4 0\n-2 -5 0\n-2 -6 0\n-2 -7 0\n-3 -4 0\n-3 -5 0\n-3 -6 0\n-3 -7 0\n-4 -5 0\n-4 -6 0\n-4 -7 0\n-5 -6 0\n-5 -7 0\n-6 -7 0\n-8 -9 0\n-8 -10 0\n-8 -11 0\n-8 -12 0\n-8 -13 0\n-8 -14 0\n-9 -10 0\n-9 -11 0\n-9 -12 0\n-9 -13 0\n-9 -14 0\n-10 -11 0\n-10 -12 0\n-10 -13 0\n-10 -14 0\n-11 -12 0\n-11 -13 0\n-11 -14 0\n-12 -13 0\n-12 -14 0\n-13 -14 0\n-15 -16 0\n-15 -17 0\n-15 -18 0\n-15 -19 0\n-15 -20 0\n-15 -21 0\n-16 -17 0\n-16 -18 0\n-16 -19 0\n-16 -20 0\n-16 -21 0\n-17 -18 0\n-17 -19 0\n-17 -20 0\n-17 -21 0\n-18 -19 0\n-18 -20 0\n-18 -21 0\n-19 -20 0\n-19 -21 0\n-20 -21 0\n-22 -23 0\n-22 -24 0\n-22 -25 0\n-22 -26 0\n-22 -27 0\n-22 -28 0\n-23 -24 0\n-23 -25 0\n-23 -26 0\n-23 -27 0\n-23 -28 0\n-24 -25 0\n-24 -26 0\n-24 -27 0\n-24 -28 0\n-25 -26 0\n-25 -27 0\n-25 -28 0\n-26 -27 0\n-26 -28 0\n-27 -28 0\n-29 -30 0\n-29 -31 0\n-29 -32 0\n-29 -33 0\n-29 -34 0\n-29 -35 0\n-30 -31 0\n-30 -32 0\n-30 -33 0\n-30 -34 0\n-30 -35 0\n-31 -32 0\n-31 -33 0\n-31 -34 0\n-31 -35 0\n-32 -33 0\n-32 -34 0\n-32 -35 0\n-33 -34 0\n-33 -35 0\n-34 -35 0\n-36 -37 0\n-36 -38 0\n-36 -39 0\n-36 -40 0\n-36 -41 0\n-36 -42 0\n-37 -38 0\n-37 -39 0\n-37 -40 0\n-37 -41 0\n-37 -42 0\n-38 -39 0\n-38 -40 0\n-38 -41 0\n-38 -42 0\n-39 -40 0\n-39 -41 0\n-39 -42 0\n-40 -41 0\n-40 -42 0\n-41 -42 0\n-43 -44 0\n-43 -45 0\n-43 -46 0\n-43 -47 0\n-43 -48 0\n-43 -49 0\n-44 -45 0\n-44 -46 0\n-44 -47 0\n-44 -48 0\n-44 -49 0\n-45 -46 0\n-45 -47 0\n-45 -48 0\n-45 -49 0\n-46 -47 0\n-46 -48 0\n-46 -49 0\n-47 -48 0\n-47 -49 0\n-48 -49 0\n-50 -51 0\n-50 -52 0\n-50 -53 0\n-50 -54 0\n-50 -55 0\n-50 -56 0\n-51 -52 0\n-51 -53 0\n-51 -54 0\n-51 -55 0\n-51 -56 0\n-52 -53 0\n-52 -54 0\n-52 -55 0\n-52 -56 0\n-53 -54 0\n-53 -55 0\n-53 -56 0\n-54 -55 0\n-54 -56 0\n-55 -56 0\n-57 -58 0\n-57 -59 0\n-57 -60 0\n-57 -61 0\n-57 -62 0\n-57 -63 0\n-58 -59 0\n-58 -60 0\n-58 -61 0\n-58 -62 0\n-58 -63 0\n-59 -60 0\n-59 -61 0\n-59 -62 0\n-59 -63 0\n-60 -61 0\n-60 -62 0\n-60 -63 0\n-61 -62 0\n-61 -63 0\n-62 -63 0\n-64 -65 0\n-64 -66 0\n-64 -67 0\n-64 -68 0\n-64 -69 0\n-64 -70 0\n-65 -66 0\n-65 -67 0\n-65 -68 0\n-65 -69 0\n-65 -70 0\n-66 -67 0\n-66 -68 0\n-66 -69 0\n-66 -70 0\n-67 -68 0\n-67 -69 0\n-67 -70 0\n-68 -69 0\n-68 -70 0\n-69 -70 0\n-1 -8 0\n-1 -15 0\n-1 -22 0\n-1 -29 0\n-1 -36 0\n-1 -43 0\n-1 -50 0\n-1 -57 0\n-1 -64 0\n-8 -15 0\n-8 -22 0\n-8 -29 0\n-8 -36 0\n-8 -43 0\n-8 -50 0\n-8 -57 0\n-8 -64 0\n-15 -22 0\n-15 -29 0\n-15 -36 0\n-15 -43 0\n-15 -50 0\n-15 -57 0\n-15 -64 0\n-22 -29 0\n-22 -36 0\n-22 -43 0\n-22 -50 0\n-22 -57 0\n-22 -64 0\n-29 -36 0\n-29 -43 0\n-29 -50 0\n-29 -57 0\n-29 -64 0\n-36 -43 0\n-36 -50 0\n-36 -57 0\n-36 -64 0\n-43 -50 0\n-43 -57 0\n-43 -64 0\n-50 -57 0\n-50 -64 0\n-57 -64 0\n-2 -9 0\n-2 -16 0\n-2 -23 0\n-2 -30 0\n-2 -37 0\n-2 -44 0\n-2 -51 0\n-2 -58 0\n-2 -65 0\n-9 -16 0\n-9 -23 0\n-9 -30 0\n-9 -37 0\n-9 -44 0\n-9 -51 0\n-9 -58 0\n-9 -65 0\n-16 -23 0\n-16 -30 0\n-16 -37 0\n-16 -44 0\n-16 -51 0\n-16 -58 0\n-16 -65 0\n-23 -30 0\n-23 -37 0\n-23 -44 0\n-23 -51 0\n-23 -58 0\n-23 -65 0\n-30 -37 0\n-30 -44 0\n-30 -51 0\n-30 -58 0\n-30 -65 0\n-37 -44 0\n-37 -51 0\n-37 -58 0\n-37 -65 0\n-44 -51 0\n-44 -58 0\n-44 -65 0\n-51 -58 0\n-51 -65 0\n-58 -65 0\n-3 -10 0\n-3 -17 0\n-3 -24 0\n-3 -31 0\n-3 -38 0\n-3 -45 0\n-3 -52 0\n-3 -59 0\n-3 -66 0\n-10 -17 0\n-10 -24 0\n-10 -31 0\n-10 -38 0\n-10 -45 0\n-10 -52 0\n-10 -59 0\n-10 -66 0\n-17 -24 0\n-17 -31 0\n-17 -38 0\n-17 -45 0\n-17 -52 0\n-17 -59 0\n-17 -66 0\n-24 -31 0\n-24 -38 0\n-24 -45 0\n-24 -52 0\n-24 -59 0\n-24 -66 0\n-31 -38 0\n-31 -45 0\n-31 -52 0\n-31 -59 0\n-31 -66 0\n-38 -45 0\n-38 -52 0\n-38 -59 0\n-38 -66 0\n-45 -52 0\n-45 -59 0\n-45 -66 0\n-52 -59 0\n-52 -66 0\n-59 -66 0\n-4 -11 0\n-4 -18 0\n-4 -25 0\n-4 -32 0\n-4 -39 0\n-4 -46 0\n-4 -53 0\n-4 -60 0\n-4 -67 0\n-11 -18 0\n-11 -25 0\n-11 -32 0\n-11 -39 0\n-11 -46 0\n-11 -53 0\n-11 -60 0\n-11 -67 0\n-18 -25 0\n-18 -32 0\n-18 -39 0\n-18 -46 0\n-18 -53 0\n-18 -60 0\n-18 -67 0\n-25 -32 0\n-25 -39 0\n-25 -46 0\n-25 -53 0\n-25 -60 0\n-25 -67 0\n-32 -39 0\n-32 -46 0\n-32 -53 0\n-32 -60 0\n-32 -67 0\n-39 -46 0\n-39 -53 0\n-39 -60 0\n-39 -67 0\n-46 -53 0\n-46 -60 0\n-46 -67 0\n-53 -60 0\n-53 -67 0\n-60 -67 0\n-5 -12 0\n-5 -19 0\n-5 -26 0\n-5 -33 0\n-5 -40 0\n-5 -47 0\n-5 -54 0\n-5 -61 0\n-5 -68 0\n-12 -19 0\n-12 -26 0\n-12 -33 0\n-12 -40 0\n-12 -47 0\n-12 -54 0\n-12 -61 0\n-12 -68 0\n-19 -26 0\n-19 -33 0\n-19 -40 0\n-19 -47 0\n-19 -54 0\n-19 -61 0\n-19 -68 0\n-26 -33 0\n-26 -40 0\n-26 -47 0\n-26 -54 0\n-26 -61 0\n-26 -68 0\n-33 -40 0\n-33 -47 0\n-33 -54 0\n-33 -61 0\n-33 -68 0\n-40 -47 0\n-40 -54 0\n-40 -61 0\n-40 -68 0\n-47 -54 0\n-47 -61 0\n-47 -68 0\n-54 -61 0\n-54 -68 0\n-61 -68 0\n-6 -13 0\n-6 -20 0\n-6 -27 0\n-6 -34 0\n-6 -41 0\n-6 -48 0\n-6 -55 0\n-6 -62 0\n-6 -69 0\n-13 -20 0\n-13 -27 0\n-13 -34 0\n-13 -41 0\n-13 -48 0\n-13 -55 0\n-13 -62 0\n-13 -69 0\n-20 -27 0\n-20 -34 0\n-20 -41 0\n-20 -48 0\n-20 -55 0\n-20 -62 0\n-20 -69 0\n-27 -34 0\n-27 -41 0\n-27 -48 0\n-27 -55 0\n-27 -62 0\n-27 -69 0\n-34 -41 0\n-34 -48 0\n-34 -55 0\n-34 -62 0\n-34 -69 0\n-41 -48 0\n-41 -55 0\n-41 -62 0\n-41 -69 0\n-48 -55 0\n-48 -62 0\n-48 -69 0\n-55 -62 0\n-55 -69 0\n-62 -69 0\n-7 -14 0\n-7 -21 0\n-7 -28 0\n-7 -35 0\n-7 -42 0\n-7 -49 0\n-7 -56 0\n-7 -63 0\n-7 -70 0\n-14 -21 0\n-14 -28 0\n-14 -35 0\n-14 -42 0\n-14 -49 0\n-14 -56 0\n-14 -63 0\n-14 -70 0\n-21 -28 0\n-21 -35 0\n-21 -42 0\n-21 -49 0\n-21 -56 0\n-21 -63 0\n-21 -70 0\n-28 -35 0\n-28 -42 0\n-28 -49 0\n-28 -56 0\n-28 -63 0\n-28 -70 0\n-35 -42 0\n-35 -49 0\n-35 -56 0\n-35 -63 0\n-35 -70 0\n-42 -49 0\n-42 -56 0\n-42 -63 0\n-42 -70 0\n-49 -56 0\n-49 -63 0\n-49 -70 0\n-56 -63 0\n-56 -70 0\n-63 -70 0\n8 1 9 2 10 3 11 4 12 5 13 6 14 7 0\n15 22 16 23 17 24 18 25 19 26 20 27 21 28 0\n36 29 37 30 38 31 39 32 40 33 41 34 42 35 0\n43 50 44 51 45 52 46 53 47 54 48 55 49 56 0\n64 57 65 58 66 59 67 60 68 61 69 62 70 63 0\n");
    // ---------------------------------------------------
	// ---------------------------------------------------
}



