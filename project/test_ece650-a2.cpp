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





TEST_CASE ("Line Parsing - Success") {
    std::string line;
    std::vector<Edge> tempEdges;

    std::string opCmd = "";
    int opNoVert = 0;
    std::vector<Edge> opEdges;
    std::vector<std::string> opEndPoints;
    std::string opErrorMessage = "";


    // ---------------------------------------------------
    // ------------------- Example 1 ---------------------
    // ---------------------------------------------------
    line = "V 15";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "V");
    CHECK(opNoVert == 15);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.size() == 0);


    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    tempEdges.clear();
    tempEdges.push_back(Edge("2" ,"6"));
    tempEdges.push_back(Edge("2", "8"));
    tempEdges.push_back(Edge("2", "5"));
    tempEdges.push_back(Edge("6", "5"));
    tempEdges.push_back(Edge("5", "8"));
    tempEdges.push_back(Edge("6", "10"));
    tempEdges.push_back(Edge("10", "8"));
    CHECK(opCmd == "E");
    CHECK(opNoVert == 0);
    CHECK(edgeVectorEquals(opEdges, tempEdges));
    CHECK(opEndPoints.size() == 0);
    
    
    line = "s 2 10";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "2");
    CHECK(opEndPoints.at(1) == "10");
    

    line = "s 10 2";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "10");
    CHECK(opEndPoints.at(1) == "2");
    // ---------------------------------------------------
	// ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Example 2 ---------------------
    // ---------------------------------------------------
    line = "V 5";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "V");
    CHECK(opNoVert == 5);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.size() == 0);

    line = "E {<1,3>,<3,2>,<3,4>,<4,5>,<5,2>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    tempEdges.clear();
    tempEdges.push_back(Edge("1" ,"3"));
    tempEdges.push_back(Edge("3", "2"));
    tempEdges.push_back(Edge("3", "4"));
    tempEdges.push_back(Edge("4", "5"));
    tempEdges.push_back(Edge("5", "2"));
    CHECK(opCmd == "E");
    CHECK(opNoVert == 0);
    CHECK(edgeVectorEquals(opEdges, tempEdges));
    CHECK(opEndPoints.size() == 0);
    
    line = "s 5 1";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "5");
    CHECK(opEndPoints.at(1) == "1");

    line = "s 1 5";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "1");
    CHECK(opEndPoints.at(1) == "5");
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 3 ---------------------
    // ---------------------------------------------------
    line = "V 10";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "V");
    CHECK(opNoVert == 10);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.size() == 0);

    line = "E {<2,1>,<1,3>,<4,1>,<1,6>,<6,5>,<7,6>,<6,8>,<9,6>,<6,10>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
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
    CHECK(opCmd == "E");
    CHECK(opNoVert == 0);
    CHECK(edgeVectorEquals(opEdges, tempEdges));
    CHECK(opEndPoints.size() == 0);
    
    line = "s 10 1";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "10");
    CHECK(opEndPoints.at(1) == "1");

    line = "s 5 10";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "5");
    CHECK(opEndPoints.at(1) == "10");

    line = "s 7 10";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "7");
    CHECK(opEndPoints.at(1) == "10");

    line = "s 7 4";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "7");
    CHECK(opEndPoints.at(1) == "4");

    line = "s 4 7";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "4");
    CHECK(opEndPoints.at(1) == "7");
    // ---------------------------------------------------
	// ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Example 4 ---------------------
    // ---------------------------------------------------
    line = "V 14";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "V");
    CHECK(opNoVert == 14);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.size() == 0);

    line = "E {<2,1>,<1,3>,<1,4>,<3,5>,<3,6>,<7,4>,<4,10>,<10,8>,<8,12>,<12,9>,<9,14>,<14,10>,<8,11>,<11,12>,<12,14>,<14,13>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
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
    CHECK(opCmd == "E");
    CHECK(opNoVert == 0);
    CHECK(edgeVectorEquals(opEdges, tempEdges));
    CHECK(opEndPoints.size() == 0);
    
    line = "s 1 13";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "1");
    CHECK(opEndPoints.at(1) == "13");

    line = "s 5 11";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "5");
    CHECK(opEndPoints.at(1) == "11");

    line = "s 6 12";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "6");
    CHECK(opEndPoints.at(1) == "12");
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 5 ---------------------
    // ---------------------------------------------------
    line = "V 7";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "V");
    CHECK(opNoVert == 7);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.size() == 0);

    line = "E {<1,2>,<1,3>,<2,4>,<4,5>,<3,4>,<4,6>,<5,7>,<6,7>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    tempEdges.clear();
    tempEdges.push_back(Edge("1" ,"2"));
    tempEdges.push_back(Edge("1", "3"));
    tempEdges.push_back(Edge("2", "4"));
    tempEdges.push_back(Edge("4", "5"));
    tempEdges.push_back(Edge("3", "4"));
    tempEdges.push_back(Edge("4", "6"));
    tempEdges.push_back(Edge("5", "7"));
    tempEdges.push_back(Edge("6", "7"));
    CHECK(opCmd == "E");
    CHECK(opNoVert == 0);
    CHECK(edgeVectorEquals(opEdges, tempEdges));
    CHECK(opEndPoints.size() == 0);
    
    line = "s 1 7";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "1");
    CHECK(opEndPoints.at(1) == "7");

    line = "s 6 3";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "6");
    CHECK(opEndPoints.at(1) == "3");

    line = "s 6 1";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "6");
    CHECK(opEndPoints.at(1) == "1");
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 6 ---------------------
    // ---------------------------------------------------
    line = "V 14";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "V");
    CHECK(opNoVert == 14);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.size() == 0);

    line = "E {<2,8>,<8,1>,<1,6>,<6,3>,<4,1>,<1,5>,<5,6>,<6,7>,<9,8>,<8,10>,<3,11>,<11,12>,<13,11>,<11,14>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
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
    CHECK(opCmd == "E");
    CHECK(opNoVert == 0);
    CHECK(edgeVectorEquals(opEdges, tempEdges));
    CHECK(opEndPoints.size() == 0);
    
    line = "s 5 13";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "5");
    CHECK(opEndPoints.at(1) == "13");

    line = "s 14 4";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "14");
    CHECK(opEndPoints.at(1) == "4");
    

    line = "s 2 14";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "2");
    CHECK(opEndPoints.at(1) == "14");
    

    line = "s 3 7";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "3");
    CHECK(opEndPoints.at(1) == "7");
    

    line = "s 7 2";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "7");
    CHECK(opEndPoints.at(1) == "2");
    
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 7 ---------------------
    // ---------------------------------------------------
    line = "V 11";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "V");
    CHECK(opNoVert == 11);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.size() == 0);
    

    line = "E {<1,5>,<5,2>,<3,10>,<10,1>,<1,4>,<6,5>,<2,7>,<7,8>,<4,7>,<7,9>,<10,11>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
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
    CHECK(opCmd == "E");
    CHECK(opNoVert == 0);
    CHECK(edgeVectorEquals(opEdges, tempEdges));
    CHECK(opEndPoints.size() == 0);
    
    
    line = "s 4 11";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "4");
    CHECK(opEndPoints.at(1) == "11");
    

    line = "s 9 3";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "9");
    CHECK(opEndPoints.at(1) == "3");
    

    line = "s 5 10";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "5");
    CHECK(opEndPoints.at(1) == "10");
    

    line = "s 7 10";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "7");
    CHECK(opEndPoints.at(1) == "10");
    
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 8 ---------------------
    //  Graph with unconnected edges = 2 Parts
    // ---------------------------------------------------
    line = "V 12";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "V");
    CHECK(opNoVert == 12);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.size() == 0);

    line = "E {<1,2>,<1,3>,<2,4>,<4,5>,<3,4>,<4,6>,<5,7>,<6,7>,<12,10>,<10,11>,<9,8>,<9,11>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
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
    CHECK(opCmd == "E");
    CHECK(opNoVert == 0);
    CHECK(edgeVectorEquals(opEdges, tempEdges));
    CHECK(opEndPoints.size() == 0);
    
    // Shortest Paths in Part 1
    line = "s 1 7";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "1");
    CHECK(opEndPoints.at(1) == "7");

    line = "s 6 3";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "6");
    CHECK(opEndPoints.at(1) == "3");

    line = "s 6 1";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "6");
    CHECK(opEndPoints.at(1) == "1");


    // Shortest Paths in Part 2
    line = "s 12 9";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "12");
    CHECK(opEndPoints.at(1) == "9");

    line = "s 8 11";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "8");
    CHECK(opEndPoints.at(1) == "11");
    
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Example 9 ---------------------
    //  Graph with unconnected edges = 4 Parts
    // ---------------------------------------------------
    line = "V 26";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "V");
    CHECK(opNoVert == 26);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.size() == 0);

    line = "E {<13,14>,<4,2>,<20,19>,<16,15>,<5,4>,<6,7>,<8,7>,<5,7>,<5,6>,<18,19>,<3,4>,<2,5>,<25,24>,<13,15>,<14,12>,<12,13>,<1,5>,<11,14>,<20,18>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
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
    CHECK(opCmd == "E");
    CHECK(opNoVert == 0);
    CHECK(edgeVectorEquals(opEdges, tempEdges));
    CHECK(opEndPoints.size() == 0);
    
    // Shortest Paths in Part 1
    line = "s 1 3";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "1");
    CHECK(opEndPoints.at(1) == "3");

    line = "s 8 2";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "8");
    CHECK(opEndPoints.at(1) == "2");

    line = "s 2 1";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "2");
    CHECK(opEndPoints.at(1) == "1");


    // Shortest Paths in Part 2
    line = "s 15 12";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "15");
    CHECK(opEndPoints.at(1) == "12");

    line = "s 11 16";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "11");
    CHECK(opEndPoints.at(1) == "16");


    // Shortest Paths in Part 3
    line = "s 20 18";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "20");
    CHECK(opEndPoints.at(1) == "18");

    line = "s 19 20";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "19");
    CHECK(opEndPoints.at(1) == "20");


    // Shortest Paths in Part 4
    line = "s 24 25";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "24");
    CHECK(opEndPoints.at(1) == "25");

    line = "s 25 24";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(opCmd == "s");
    CHECK(opNoVert == 0);
    CHECK(opEdges.size() == 0);
    CHECK(opEndPoints.at(0) == "25");
    CHECK(opEndPoints.at(1) == "24");
    
    // ---------------------------------------------------
	// ---------------------------------------------------

}




// Not really required, since Prof said that input will be perfectly formed
TEST_CASE ("Line Parsing - Failure") {
    std::string line;
    std::vector<Edge> tempEdges;

    std::string opCmd = "";
    int opNoVert = 0;
    std::vector<Edge> opEdges;
    std::vector<std::string> opEndPoints;
    std::string opErrorMessage = "";

    
    line = "V";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "V ";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "V a";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "V1";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "Va";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));
    

    line = "E";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "E ";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "E {<}";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));
    
    line = "E {<>}";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "E {<1>}";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "E{<1,2>}";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "E {<1,2>,<>}";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "E {<1,2>,<1}";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "E 12";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "E1";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "Eb";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));
    


    line = "s";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "s 1";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));

    line = "s11 1";
    CHECK(checkIfExceptionRaisedInLineParsing(line, opCmd, opNoVert, opEdges, opEndPoints));
}









TEST_CASE ("'Create Graph' + 'Generate Shortest Path' - Success") {
    Graph g;
    Graph tempGraph;

    std::string line;
    std::vector<Edge> tempEdges;

    std::string opCmd = "";
    int opNoVert = 0;
    std::vector<Edge> opEdges;
    std::vector<std::string> opEndPoints;
    std::string opErrorMessage = "";


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

    
    line = "s 2 10";
    CHECK(g.generateShortestPath("2", "10") == "2-6-10");

    line = "s 10 2";
    CHECK(g.generateShortestPath("10", "2") == "10-6-2");

    // Shortest Path to Itself (For a vertex that has an edge to one or more verticies)
    line = "s 2 2";
    CHECK(g.generateShortestPath("2", "2") == "2");

    // Shortest Path to Itself (For a vertex that has no edge to any other vertex)
    line = "s 11 11";
    CHECK(g.generateShortestPath("11", "11") == "11");
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
    
    line = "s 5 1";
    CHECK(g.generateShortestPath("5", "1") == "5-4-3-1");

    line = "s 1 5";
    CHECK(g.generateShortestPath("1", "5") == "1-3-2-5");
    
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
    
    line = "s 10 1";
    CHECK(g.generateShortestPath("10", "1") == "10-6-1");

    line = "s 5 10";
    CHECK(g.generateShortestPath("5", "10") == "5-6-10");

    line = "s 7 10";
    CHECK(g.generateShortestPath("7", "10") == "7-6-10");

    line = "s 7 4";
    CHECK(g.generateShortestPath("7", "4") == "7-6-1-4");

    line = "s 4 7";
    CHECK(g.generateShortestPath("4", "7") == "4-1-6-7");
    
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
    
    line = "s 1 13";
    CHECK(g.generateShortestPath("1", "13") == "1-4-10-14-13");
    
    line = "s 5 11";
    CHECK(g.generateShortestPath("5", "11") == "5-3-1-4-10-8-11");
    
    line = "s 6 12";
    CHECK(g.generateShortestPath("6", "12") == "6-3-1-4-10-8-12");
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
    
    line = "s 1 7";
    CHECK(g.generateShortestPath("1", "7") == "1-2-4-5-7");

    line = "s 6 3";
    CHECK(g.generateShortestPath("6", "3") == "6-4-3");

    line = "s 6 1";
    CHECK(g.generateShortestPath("6", "1") == "6-4-2-1");
    
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
    
    line = "s 5 13";
    CHECK(g.generateShortestPath("5", "13") == "5-6-3-11-13");

    line = "s 14 4";
    CHECK(g.generateShortestPath("14", "4") == "14-11-3-6-1-4");

    line = "s 2 14";
    CHECK(g.generateShortestPath("2", "14") == "2-8-1-6-3-11-14");

    line = "s 3 7";
    CHECK(g.generateShortestPath("3", "7") == "3-6-7");

    line = "s 7 2";
    CHECK(g.generateShortestPath("7", "2") == "7-6-1-8-2");
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
    
    line = "s 4 11";
    CHECK(g.generateShortestPath("4", "11") == "4-1-10-11");

    line = "s 9 3";
    CHECK(g.generateShortestPath("9", "3") == "9-7-4-1-10-3");

    line = "s 5 10";
    CHECK(g.generateShortestPath("5", "10") == "5-1-10");

    line = "s 7 10";
    CHECK(g.generateShortestPath("7", "10") == "7-4-1-10");
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
    
    // Shortest Paths in Part 1
    line = "s 1 7";
    CHECK(g.generateShortestPath("1", "7") == "1-2-4-5-7");

    line = "s 6 3";
    CHECK(g.generateShortestPath("6", "3") == "6-4-3");

    line = "s 6 1";
    CHECK(g.generateShortestPath("6", "1") == "6-4-2-1");


    // Shortest Paths in Part 2
    line = "s 12 9";
    CHECK(g.generateShortestPath("12", "9") == "12-10-11-9");

    line = "s 8 11";
    CHECK(g.generateShortestPath("8", "11") == "8-9-11");
    
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
    
    // Shortest Paths in Part 1
    line = "s 1 3";
    CHECK(g.generateShortestPath("1", "3") == "1-5-4-3");

    line = "s 8 2";
    CHECK(g.generateShortestPath("8", "2") == "8-7-5-2");

    line = "s 2 1";
    CHECK(g.generateShortestPath("2", "1") == "2-5-1");


    // Shortest Paths in Part 2
    line = "s 15 12";
    CHECK(g.generateShortestPath("15", "12") == "15-13-12");

    line = "s 11 16";
    CHECK(g.generateShortestPath("11", "16") == "11-14-13-15-16");


    // Shortest Paths in Part 3
    line = "s 20 18";
    CHECK(g.generateShortestPath("20", "18") == "20-18");

    line = "s 19 20";
    CHECK(g.generateShortestPath("19", "20") == "19-20");


    // Shortest Paths in Part 4
    line = "s 24 25";
    CHECK(g.generateShortestPath("24", "25") == "24-25");

    line = "s 25 24";
    CHECK(g.generateShortestPath("25", "24") == "25-24");
    
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

    
    line = "s 2 2";
    CHECK(g.generateShortestPath("2", "2") == "2");

    line = "s 3 3";
    CHECK(g.generateShortestPath("3", "3") == "3");

    line = "s 2 6";
    CHECK(g.generateShortestPath("2", "6") == "2-6");

    line = "s 6 2";
    CHECK(g.generateShortestPath("6", "2") == "6-2");
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

    
    line = "s 2 2";
    CHECK(g.generateShortestPath("2", "2") == "2");

    line = "s 3 3";
    CHECK(g.generateShortestPath("3", "3") == "3");
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
    

    line = "s 1 2";
    CHECK(g.generateShortestPath("1", "2") == "1-2");

    line = "s 2 1";
    CHECK(g.generateShortestPath("2", "1") == "2-1");

    line = "s 2 2";
    CHECK(g.generateShortestPath("2", "2") == "2");
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
    

    line = "s 1 1";
    CHECK(g.generateShortestPath("1", "1") == "1");
    // ---------------------------------------------------
	// ---------------------------------------------------
}




TEST_CASE ("'Create Graph' + 'Generate Shortest Path' - Success + Failure") {
    Graph g;
    Graph tempGraph;

    std::string line;
    std::vector<Edge> tempEdges;

    std::string opCmd = "";
    int opNoVert = 0;
    std::vector<Edge> opEdges;
    std::vector<std::string> opEndPoints;

    // int prevNoVert;
    // std::vector<Edge> prevEdges;


    // ---------------------------------------------------
    // ------------------- Success ---------------------
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

    
    line = "s 2 10";
    CHECK(g.generateShortestPath("2", "10") == "2-6-10");

    line = "s 10 2";
    CHECK(g.generateShortestPath("10", "2") == "10-6-2");
    // ---------------------------------------------------
	// ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Failure ---------------------
    // ---------------------------------------------------
    // Setting Negative no. of Vertices
    line = "V -1";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetNoVertices(g, opNoVert));
    CHECK(g.getNoVertices() == 0); 
    CHECK(g.getEdges().size() == 0);


    // Setting no. of Vertices to zero(0)
    line = "V 0";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetNoVertices(g, opNoVert));
    CHECK(g.getNoVertices() == 0);
    CHECK(g.getEdges().size() == 0);


    // Adding Edge with same src and dest <6,6>
    line = "V 15";
    g.setNoVertices(15);
    CHECK(g.getNoVertices() == 15);
    
    line = "E {<2,6>,<2,13>,<2,5>,<6,6>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetEdges(g, opEdges));
    CHECK(g.getNoVertices() == 0);
    CHECK(g.getEdges().size() == 0);


    // Adding Edge with same src and dest <2,2>
    line = "V 15";
    g.setNoVertices(15);
    CHECK(g.getNoVertices() == 15);
    
    line = "E {<2,6>,<2,2>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetEdges(g, opEdges));
    CHECK(g.getNoVertices() == 0);
    CHECK(g.getEdges().size() == 0);




    // Adding Edge with vertex that does not exist
    line = "V 15";
    g.setNoVertices(15);
    CHECK(g.getNoVertices() == 15);
    
    line = "E {<2,6>,<2,21>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetEdges(g, opEdges));
    CHECK(g.getNoVertices() == 0);
    CHECK(g.getEdges().size() == 0);

    
    // Adding Edge with vertex that does not exist
    line = "V 15";
    g.setNoVertices(15);
    CHECK(g.getNoVertices() == 15);
    
    line = "E {<2,6>,<18,2>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetEdges(g, opEdges));
    CHECK(g.getNoVertices() == 0);
    CHECK(g.getEdges().size() == 0);


    // Adding Edge with vertex that does not exist
    line = "V 15";
    g.setNoVertices(15);
    CHECK(g.getNoVertices() == 15);
    
    line = "E {<2,6>,<2,16>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetEdges(g, opEdges));
    CHECK(g.getNoVertices() == 0);
    CHECK(g.getEdges().size() == 0);


    // Adding Edge with vertex '0'
    line = "V 15";
    g.setNoVertices(15);
    CHECK(g.getNoVertices() == 15);
    
    line = "E {<2,6>,<2,0>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetEdges(g, opEdges));
    CHECK(g.getNoVertices() == 0);
    CHECK(g.getEdges().size() == 0);


    // Adding Edge with vertex '-1' (Negative)
    line = "V 15";
    g.setNoVertices(15);
    CHECK(g.getNoVertices() == 15);
    
    line = "E {<2,6>,<2,-1>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetEdges(g, opEdges));
    CHECK(g.getNoVertices() == 0);
    CHECK(g.getEdges().size() == 0);


    // Adding Edge with vertex '-12' (Negative)
    line = "V 15";
    g.setNoVertices(15);
    CHECK(g.getNoVertices() == 15);
    
    line = "E {<2,6>,<2,-12>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetEdges(g, opEdges));
    CHECK(g.getNoVertices() == 0);
    CHECK(g.getEdges().size() == 0);




    // Adding Edge with vertex that does not exist
    line = "V 15";
    g.setNoVertices(15);
    CHECK(g.getNoVertices() == 15);
    
    line = "E {<2,6>,<22,6>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetEdges(g, opEdges));
    CHECK(g.getNoVertices() == 0);
    CHECK(g.getEdges().size() == 0);


    // Adding Edge with vertex that does not exist
    line = "V 15";
    g.setNoVertices(15);
    CHECK(g.getNoVertices() == 15);
    
    line = "E {<2,6>,<16,6>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetEdges(g, opEdges));
    CHECK(g.getNoVertices() == 0);
    CHECK(g.getEdges().size() == 0);


    // Adding Edge with vertex '0'
    line = "V 15";
    g.setNoVertices(15);
    CHECK(g.getNoVertices() == 15);
    
    line = "E {<2,6>,<0,6>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetEdges(g, opEdges));
    CHECK(g.getNoVertices() == 0);
    CHECK(g.getEdges().size() == 0);


    // Adding Edge with vertex '-1' (Negative)
    line = "V 15";
    g.setNoVertices(15);
    CHECK(g.getNoVertices() == 15);
    
    line = "E {<2,6>,<-1,6>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetEdges(g, opEdges));
    CHECK(g.getNoVertices() == 0);
    CHECK(g.getEdges().size() == 0);


    // Adding Edge with vertex '-1' (Negative)
    line = "V 15";
    g.setNoVertices(15);
    CHECK(g.getNoVertices() == 15);

    line = "E {<2,6>,<-4,6>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    CHECK(checkIfExceptionRaisedInGraphSetEdges(g, opEdges));
    CHECK(g.getNoVertices() == 0);
    CHECK(g.getEdges().size() == 0);
    // ---------------------------------------------------
	// ---------------------------------------------------




    // ---------------------------------------------------
    // ------------------- Success ---------------------
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

    
    line = "s 2 10";
    CHECK(g.generateShortestPath("2", "10") == "2-6-10");

    line = "s 10 2";
    CHECK(g.generateShortestPath("10", "2") == "10-6-2");
    // ---------------------------------------------------
	// ---------------------------------------------------




    // ---------------------------------------------------
    // ------------------- Failure ---------------------
    // ---------------------------------------------------
    
    // Generate shortest path from a vertex that does not exist
    line = "s 19 10";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "19", "10"));
    
    // Generate shortest path from a vertex that does not exist
    line = "s 16 10";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "16", "10"));

    // Generate shortest path from a vertex that does not exist
    line = "s 0 10";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "0", "10"));

    // Generate shortest path from a vertex that does not exist
    line = "s -1 10";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "-1", "10"));

    // Generate shortest path from a vertex that does not exist
    line = "s -6 10";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "-6", "10"));



    // Generate shortest path to a vertex that does not exist
    line = "s 2 17";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "2", "17"));

    // Generate shortest path to a vertex that does not exist
    line = "s 2 16";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "2", "16"));

    // Generate shortest path to a vertex that does not exist
    line = "s 2 0";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "2", "0"));

    // Generate shortest path to a vertex that does not exist
    line = "s 2 -1";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "2", "-1"));

    // Generate shortest path to a vertex that does not exist
    line = "s s 2 -10";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "2", "-10"));


    // Generate shortest path from a vertex which has no edge to any other vertex
    // OR (Not sure) Generate shortest path between vertices that have no path
    line = "s 7 2";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "7", "2"));

    // Generate shortest path to a vertex which has no edge to any other vertex
    // OR (Not sure) Generate shortest path between vertices that have no path
    line = "s 2 11";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "2", "11"));

    // Generate shortest path to & from vertices which have no edge to any other vertex
    // OR (Not sure) Generate shortest path between vertices that have no path
    line = "s 7 11";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "7", "11"));
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Success ---------------------
    // ---------------------------------------------------
    line = "s 2 10";
    CHECK(g.generateShortestPath("2", "10") == "2-6-10");

    line = "s 10 2";
    CHECK(g.generateShortestPath("10", "2") == "10-6-2");



    line = "V 15";
    lineParsing(line, opCmd, opNoVert, opEdges, opEndPoints);
    g.setNoVertices(opNoVert);
    CHECK(g.getNoVertices() == opNoVert);
    CHECK(g.getEdges().size() == 0);
    
    line = "E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>,<7,1>}";
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
    tempEdges.push_back(Edge("7", "1"));
    tempGraph = Graph();
    tempGraph.setNoVertices(15);
    tempGraph.setEdges(tempEdges);

    CHECK(g.equals(tempGraph));
    CHECK(g.toString() == "V 15\nE {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>,<7,1>}");


    line = "s 2 10";
    CHECK(g.generateShortestPath("2", "10") == "2-6-10");

    line = "s 10 2";
    CHECK(g.generateShortestPath("10", "2") == "10-6-2");
    // ---------------------------------------------------
	// ---------------------------------------------------



    // ---------------------------------------------------
    // ------------------- Failure ---------------------
    // ---------------------------------------------------
    // Generate shortest path between vertices that have no path
    line = "s 2 7";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "2", "7"));

    // Generate shortest path between vertices that have no path
    line = "s 7 2";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "7", "2"));
    // ---------------------------------------------------
	// ---------------------------------------------------


    

    // ---------------------------------------------------
    // ------------------- Example 9 (Success) ---------------------
    //  Graph with unconnected edges = 4 Parts
    // ---------------------------------------------------
    line = "s 2 10";
    CHECK(g.generateShortestPath("2", "10") == "2-6-10");

    line = "s 10 2";
    CHECK(g.generateShortestPath("10", "2") == "10-6-2");


    
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
    
    // Shortest Paths in Part 1
    line = "s 1 3";
    CHECK(g.generateShortestPath("1", "3") == "1-5-4-3");

    line = "s 8 2";
    CHECK(g.generateShortestPath("8", "2") == "8-7-5-2");

    line = "s 2 1";
    CHECK(g.generateShortestPath("2", "1") == "2-5-1");


    // Shortest Paths in Part 2
    line = "s 15 12";
    CHECK(g.generateShortestPath("15", "12") == "15-13-12");

    line = "s 11 16";
    CHECK(g.generateShortestPath("11", "16") == "11-14-13-15-16");


    // Shortest Paths in Part 3
    line = "s 20 18";
    CHECK(g.generateShortestPath("20", "18") == "20-18");

    line = "s 19 20";
    CHECK(g.generateShortestPath("19", "20") == "19-20");


    // Shortest Paths in Part 4
    line = "s 24 25";
    CHECK(g.generateShortestPath("24", "25") == "24-25");

    line = "s 25 24";
    CHECK(g.generateShortestPath("25", "24") == "25-24");
    
    // ---------------------------------------------------
	// ---------------------------------------------------

    


    // ---------------------------------------------------
    // ------------------- Failure ---------------------
    // ---------------------------------------------------
    // Generate shortest path between vertices that have no path
    line = "s 1 14";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "1", "14"));

    // Generate shortest path between vertices that have no path
    line = "s 24 5";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "24", "5"));

    // Generate shortest path between vertices that have no path
    line = "s 5 24";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "5", "24"));

    // Generate shortest path between vertices that have no path
    line = "s 18 2";
    CHECK(checkIfExceptionRaisedInGenerateShortestPath(g, "18", "2"));
    // ---------------------------------------------------
	// ---------------------------------------------------


    // ---------------------------------------------------
    // ------------------- Success ---------------------
    // ---------------------------------------------------
    // Shortest Paths in Part 1
    line = "s 1 3";
    CHECK(g.generateShortestPath("1", "3") == "1-5-4-3");

    line = "s 8 2";
    CHECK(g.generateShortestPath("8", "2") == "8-7-5-2");

    line = "s 2 1";
    CHECK(g.generateShortestPath("2", "1") == "2-5-1");
    // ---------------------------------------------------
    // ---------------------------------------------------




    // ---------------------------------------------------
    // ------------------- Example 2 (Success) ---------------------
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
    
    line = "s 5 1";
    CHECK(g.generateShortestPath("5", "1") == "5-4-3-1");

    line = "s 1 5";
    CHECK(g.generateShortestPath("1", "5") == "1-3-2-5");
    
    // ---------------------------------------------------
	// ---------------------------------------------------
}