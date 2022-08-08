#pragma once

#include <string>
#include <vector>


// CLASS AND FUNCTION DECLARATIONS GO HERE

/* ******************************************************************************** */
//              Graph
/* ******************************************************************************** */
class Graph {
    int noVertices;
    std::vector<Edge> edges;

    public:
        Graph();

        int getNoVertices();
        void setNoVertices(int n);

        std::vector<Edge> getEdges();
        void setEdges(std::vector<Edge> newEdges);

        std::string toString();
        bool equals (Graph g2);

        // Function to find shortest path between two vertices
        std::string generateShortestPath (std::string src, std::string dest);
};


// Function to check if 2 'Edge Vectors' are equal
bool edgeVectorEquals (std::vector<Edge> edges1, std::vector<Edge> edges2);
/* ******************************************************************************** */




/* ******************************************************************************** */
//          Shortest Path using - Breadth First Search (BFS)
/* ******************************************************************************** */
std::string shortestPathUsingBFS (Graph g, std::string src, std::string dest);

// Function to check if Queue already contains the vertex (i.e. if BFS has already visited it)
bool queueContains (std::vector<std::vector<std::string>> queue, std::string vertex);

// Function to convert shortest path (vector array) to string
std::string shortestPathToString(std::vector<std::string> sP);
/* ******************************************************************************** */
