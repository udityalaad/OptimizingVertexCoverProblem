/**
 * An example unit test using doctest. See documentation at
 * https://github.com/onqtam/doctest/blob/master/doc/markdown/tutorial.md
 */
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cstring>
#include <vector>
#include <iostream>

#include "a2_source_files/edge.hpp"
#include "a2_source_files/graph.hpp"
#include "a2_source_files/processes.hpp"

#include "a4_source_files/a4_processes.hpp"
#include "prj_source_files/prj_processes.hpp"
#include "prj_source_files/prj_performance.hpp"



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




TEST_CASE ("'Create Graph' + 'approxVC_1' + 'approxVC_2' - Success") {
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
    
    std::vector<int> vertexCover_returned;
    std::vector<int> vertexCover_cnfSATSolver;


    std::vector<int> verNoEdge;
    std::vector<int> redundantVerticesInPendantEdges;
    std::vector<int> sureVerticesInPendantEdges;


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

    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {2, 5, 10}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {2, 5, 6, 8}));
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

    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {3, 5}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 3, 4, 5}));
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

    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 6}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2, 5, 6}));
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

    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 3, 4, 8, 10, 12, 14}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2, 3, 4, 5, 7, 8, 9, 10, 12, 13, 14}));
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

    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 4, 7}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2, 4, 5, 6, 7}));
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

    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 6, 8, 11}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2, 3, 6, 8, 11}));
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

    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 5, 7, 10}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2, 3, 5, 7, 10}));
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

    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 4, 7, 9, 10}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2, 4, 5, 6, 7, 8, 9, 10, 12}));
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
    
    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {4, 5, 7, 13, 14, 15, 18, 19, 24}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2, 4, 5, 6, 7, 13, 14, 15, 16, 19, 20, 24, 25}));
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

    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {2}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {2, 6}));
    // ---------------------------------------------------
	// ---------------------------------------------------


    // // ---------------------------------------------------
    // // ------------------- Example 11 ---------------------
    // //  Graph with no edges
    // // ---------------------------------------------------
    // line = "V 5";
    // lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    // g.setNoVertices(opNoVert);
    // CHECK(g.getNoVertices() == opNoVert);
    // CHECK(g.getEdges().size() == 0);

    // line = "E {}";
    // lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    // g.setEdges(opEdges);
    // CHECK(edgeVectorEquals(g.getEdges(), opEdges));
    // CHECK(g.getEdges().size() == 0);

    // // Graph to check against
    // tempEdges.clear();
    // tempGraph = Graph();
    // tempGraph.setNoVertices(5);
    // tempGraph.setEdges(tempEdges);

    // CHECK(g.equals(tempGraph));
    // CHECK(g.toString() == "V 5\nE {}");

    // // Test approxVC_1
    // vertexCover_returned = approxVC_1(g);
    // CHECK(intVectorEquals(vertexCover_returned, {}));

    // // Test approxVC_2
    // vertexCover_returned = approxVC_2(g);
    // CHECK(intVectorEquals(vertexCover_returned, {}));
    // // ---------------------------------------------------
	// // ---------------------------------------------------



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
    
    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {1}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2}));
    // ---------------------------------------------------
	// ---------------------------------------------------



    // // ---------------------------------------------------
    // // ------------------- Example 13 ---------------------
    // //  Graph with only 1 vertex
    // // ---------------------------------------------------
    // line = "V 1";
    // lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    // g.setNoVertices(opNoVert);
    // CHECK(g.getNoVertices() == opNoVert);
    // CHECK(g.getEdges().size() == 0);

    // line = "E {}";
    // lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    // g.setEdges(opEdges);
    // CHECK(edgeVectorEquals(g.getEdges(), opEdges));

    // // Graph to check against
    // tempEdges.clear();
    // tempGraph = Graph();
    // tempGraph.setNoVertices(1);
    // tempGraph.setEdges(tempEdges);

    // CHECK(g.equals(tempGraph));
    // CHECK(g.toString() == "V 1\nE {}");

    // // Test approxVC_1
    // vertexCover_returned = approxVC_1(g);
    // CHECK(intVectorEquals(vertexCover_returned, {}));

    // // Test approxVC_2
    // vertexCover_returned = approxVC_2(g);
    // CHECK(intVectorEquals(vertexCover_returned, {}));
    // // ---------------------------------------------------
	// // ---------------------------------------------------



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

    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {1}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2}));
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

    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2}));
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

    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {4, 5}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2, 4, 5}));
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

    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 3}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2, 3, 4}));
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

    // Test approxVC_1
    vertexCover_returned = approxVC_1(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 3, 5, 7, 9}));

    // Test approxVC_2
    vertexCover_returned = approxVC_2(g);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}));
    // ---------------------------------------------------
	// ---------------------------------------------------
}








TEST_CASE ("'mean', 'standardDeviation' - Success") {
    std::vector<double> input;

    // ---------------------------------------------------
    // -------------- All Positive Input -----------------
    // ---------------------------------------------------
    // Test Case 1
    input.clear();
    input.push_back(3);
    input.push_back(3.2);
    input.push_back(5.21);
    input.push_back(8.22);
    input.push_back(1);
    input.push_back(22);

    CHECK(std::to_string(mean(input)) == std::to_string(7.105));
    CHECK(std::to_string(standardDeviation(input)) == std::to_string(7.0245563324));


    // Test Case 2
    input.clear();
    input.push_back(2);
    input.push_back(1);
    input.push_back(5);
    input.push_back(5);
    input.push_back(2);
    input.push_back(12);

    CHECK(std::to_string(mean(input)) == std::to_string(4.5));
    CHECK(std::to_string(standardDeviation(input)) == std::to_string(3.6855573979));


    // Test Case 3
    input.clear();
    input.push_back(14.0328);
    input.push_back(3.2123);
    input.push_back(24.221);
    input.push_back(8.22);
    input.push_back(122);
    input.push_back(23.123121);

    CHECK(std::to_string(mean(input)) == std::to_string(32.4682035));
    CHECK(std::to_string(standardDeviation(input)) == std::to_string(40.7329450646));


    // Test Case 4
    input.clear();
    input.push_back(0.2781);
    input.push_back(283.274);
    input.push_back(882.183278);
    input.push_back(27362);
    input.push_back(654.22);

    CHECK(std::to_string(mean(input)) == std::to_string(5836.3910756));
    CHECK(std::to_string(standardDeviation(input)) == std::to_string(10767.0630670028));



    // ---------------------------------------------------
    // -------------- Positive + Negative Input -----------------
    // ---------------------------------------------------
    // Test Case 1
    input.clear();
    input.push_back(3);
    input.push_back(3.2);
    input.push_back(-5);
    input.push_back(5.21);
    input.push_back(-29.21);
    input.push_back(8.22);
    input.push_back(-2);
    input.push_back(1);
    input.push_back(22);
    input.push_back(-12.2221);

    CHECK(std::to_string(mean(input)) == std::to_string(7.105));
    CHECK(std::to_string(standardDeviation(input)) == std::to_string(7.0245563324));


    // Test Case 2
    input.clear();
    input.push_back(2);
    input.push_back(1);
    input.push_back(-29.21);
    input.push_back(-2);
    input.push_back(5);
    input.push_back(5);
    input.push_back(-12.2221);
    input.push_back(2);
    input.push_back(12);
    input.push_back(-5);

    CHECK(std::to_string(mean(input)) == std::to_string(4.5));
    CHECK(std::to_string(standardDeviation(input)) == std::to_string(3.6855573979));


    // Test Case 3
    input.clear();
    input.push_back(-29.21);
    input.push_back(14.0328);
    input.push_back(3.2123);
    input.push_back(-12.2221);
    input.push_back(24.221);
    input.push_back(-2);
    input.push_back(8.22);
    input.push_back(122);
    input.push_back(-5);
    input.push_back(23.123121);

    CHECK(std::to_string(mean(input)) == std::to_string(32.4682035));
    CHECK(std::to_string(standardDeviation(input)) == std::to_string(40.7329450646));


    // Test Case 4
    input.clear();
    input.push_back(-29.21);
    input.push_back(-29.21);
    input.push_back(0.2781);
    input.push_back(283.274);
    input.push_back(882.183278);
    input.push_back(27362);
    input.push_back(-12.2221);
    input.push_back(-5);
    input.push_back(654.22);
    input.push_back(-2);

    CHECK(std::to_string(mean(input)) == std::to_string(5836.3910756));
    CHECK(std::to_string(standardDeviation(input)) == std::to_string(10767.0630670028));


    // ---------------------------------------------------
    // -------------- All Negative Input -----------------
    // ---------------------------------------------------
    // Test Case 1
    input.clear();
    input.push_back(-3);
    input.push_back(-3.2);
    input.push_back(-5.21);
    input.push_back(-8.22);
    input.push_back(-1);
    input.push_back(-22);

    CHECK(std::to_string(mean(input)) == std::to_string(-1.000000));
    CHECK(std::to_string(standardDeviation(input)) == std::to_string(-1.000000));


    // Test Case 2
    input.clear();
    input.push_back(-2);
    input.push_back(-1);
    input.push_back(-5);
    input.push_back(-5);
    input.push_back(-2);
    input.push_back(-12);

    CHECK(std::to_string(mean(input)) == std::to_string(-1.000000));
    CHECK(std::to_string(standardDeviation(input)) == std::to_string(-1.000000));


    // Test Case 3
    input.clear();
    input.push_back(-14.0328);
    input.push_back(-3.2123);
    input.push_back(-24.221);
    input.push_back(-8.22);
    input.push_back(-122);
    input.push_back(-23.123121);

    CHECK(std::to_string(mean(input)) == std::to_string(-1.000000));
    CHECK(std::to_string(standardDeviation(input)) == std::to_string(-1.000000));


    // Test Case 4
    input.clear();
    input.push_back(-0.2781);
    input.push_back(-283.274);
    input.push_back(-882.183278);
    input.push_back(-27362);
    input.push_back(-654.22);

    CHECK(std::to_string(mean(input)) == std::to_string(-1.000000));
    CHECK(std::to_string(standardDeviation(input)) == std::to_string(-1.000000));



    // ---------------------------------------------------
    // ------------------- Empty Input -------------------
    // ---------------------------------------------------
    // Test Case 1
    input.clear();
    
    CHECK(std::to_string(mean(input)) == std::to_string(-1.000000));
    CHECK(std::to_string(standardDeviation(input)) == std::to_string(-1.000000));
}










TEST_CASE ("'Create Graph' + 'optimized_vertexCoverUsingCnfSATSolver' - Success + Failure") {
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

    std::vector<int> verNoEdge;
    std::vector<int> redundantVerticesInPendantEdges;
    std::vector<int> sureVerticesInPendantEdges;

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
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {2, 6, 8}));

    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {3, 5}));
    
    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 6}));
    
    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -3 -  (k = 3) - Failure
    k = 3;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -4 -  (k = 4) - Failure
    k = 4;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 3, 4, 8, 12, 14}));
    
    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 4, 7}));
    
    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 6, 8, 11}));
    
    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {4, 5, 7, 10}));
    
    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -3 -  (k = 3) - Failure
    k = 3;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test 0 - Success
    // k = 5;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 4, 7, 9, 10}));
    
    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -3 -  (k = 3) - Failure
    k = 3;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -4 -  (k = 4) - Failure
    k = 4;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -5 -  (k = 5) - Failure
    k = 5;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -6 -  (k = 6) - Failure
    k = 6;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test 0 - Success
    // clauses_string = "";
    // vertexCover_cnfSATSolver.clear();
    // vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    // CHECK(intVectorEquals(vertexCover_returned, {4, 5, 7, 12, 14, 15, 19, 20, 25}));
    // k = vertexCover_returned.size();
    // CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {6}));
    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
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
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {2}));
    
    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
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
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1}));
    
    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {1, 2}));
    
    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {4, 5}));
    
    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {2, 3}));
    
    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
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
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -2 -  (k = 2) - Failure
    k = 2;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -3 -  (k = 3) - Failure
    k = 3;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));

    // Test -4 - (k = 4) - Failure
    k = 4;
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    CHECK(!optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));


    // Test 0 - Success
    clauses_string = "";
    vertexCover_cnfSATSolver.clear();
    vertexCover_returned = optimized_vertexCoverUsingCnfSATSolver(g, solver, cnfSAT_interrupted);
    CHECK(intVectorEquals(vertexCover_returned, {2, 3, 6, 7, 10}));

    k = vertexCover_returned.size();
    CHECK(optimized_cnfSATSolver(g, k, vertexCover_cnfSATSolver, clauses_string, solver,verNoEdge, redundantVerticesInPendantEdges, sureVerticesInPendantEdges));
    CHECK(intVectorEquals(vertexCover_returned, vertexCover_cnfSATSolver));
    // ---------------------------------------------------
	// ---------------------------------------------------
}