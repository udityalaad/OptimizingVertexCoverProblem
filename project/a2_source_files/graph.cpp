#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>

#include "edge.hpp"
#include "graph.hpp"



/* ******************************************************************************** */
//              Graph
/* ******************************************************************************** */
Graph :: Graph () {
    noVertices = 0;
}


int Graph :: getNoVertices() {
    return noVertices;
}


void Graph :: setNoVertices(int v) {
    if (v < 1) {
        // Make noVertices = 0 and 'edges = empty', when an error occurs in 'V' command
        noVertices = 0;
        edges.clear();

        std::string errorMessage = "'No. of Vertices' should be greater than or equal to 1";
        throw errorMessage;
    }

    noVertices = v;

    // Make edges of the graph empty when new value is given for noVertices
    edges.clear();
}



std::vector<Edge> Graph :: getEdges()  {
    return edges;
}



void Graph :: setEdges(std::vector<Edge> newEdges)  {
    for (int i = 0; i < ((int) newEdges.size()); i++) {
        Edge e = newEdges.at(i);

        // Checking whether source and destination are same vertices
        if (e.getSrc() == e.getDest()) {
            noVertices = 0;
            edges.clear();

            std::string errorMessage = "Source and destination should be different for an edge.";
            throw errorMessage;
        }

        // Checking whether source and destination are valid vertices
        if (std::__cxx11::stoi(e.getSrc()) < 1   ||   std::__cxx11::stoi(e.getSrc()) > noVertices) {
            // Make noVertices = 0 and 'edges = empty', when an error occurs in 'E' command
            noVertices = 0;
            edges.clear();

            std::string errorMessage = "Vertex " + e.getSrc() + " does not exist.";
            throw errorMessage;

        } else if (std::__cxx11::stoi(e.getDest()) < 1   ||   std::__cxx11::stoi(e.getDest()) > noVertices) {
            // Make noVertices = 0 and 'edges = empty', when an error occurs in 'E' command
            noVertices = 0;
            edges.clear();

            std::string errorMessage = "Vertex " + e.getDest() + " does not exist.";
            throw errorMessage;
        }
    }

    edges = newEdges;
}



std::string Graph :: toString() {
    std::string result = "";

    result += "V " + std::to_string(noVertices);

    if (!edges.empty()) {
        result += "\nE {";
        for (int i = 0; i < ((int) edges.size()); i++) {
            result += edges.at(i).toString();

            if (i != ((int) edges.size()) -1) {
                result += ",";
            }
        }
        result += "}";

    } else {
        result += "\nE {";
        result += "}";
    }

    return result;
}



bool Graph :: equals (Graph g2) {
    // Check noVertices
    if (noVertices != g2.getNoVertices()) {
        return false;
    }

    // Check edges
    return edgeVectorEquals(edges, g2.getEdges());
}



// Function to find shortest path between two vertices
std::string Graph :: generateShortestPath (std::string src, std::string dest) {
    // Checking whether source and destination are valid vertices
    if (std::__cxx11::stoi(src) < 1   ||   std::__cxx11::stoi(src) > noVertices) {
        std::string errorMessage = "Vertex " + src + " does not exist.";
        throw errorMessage;

    } else if (std::__cxx11::stoi(dest) < 1   ||   std::__cxx11::stoi(dest) > noVertices) {
        std::string errorMessage = "Vertex " + dest + " does not exist.";
        throw errorMessage;
    }

    // Get Shortest Path using BFS
    std::string result = shortestPathUsingBFS(*this, src, dest);
    
    if (result == "null") {
        std::string errorMessage = "No path exists between the given vertices.";
        throw errorMessage;
    }

    return result;
}



// Function to check if 2 'Edge Vectors' are equal
bool edgeVectorEquals (std::vector<Edge> edges1, std::vector<Edge> edges2) {
    if (edges1.size() != edges2.size()) {
        return false;
    }

    for (int i =0; i < ((int) edges1.size()); i++) {
        if (!edges1.at(i).equals(edges2.at(i))) {
            return false;
        }
    }

    return true;
}
/* ******************************************************************************** */






/* ******************************************************************************** */
//          Shortest Path using - Breadth First Search (BFS)
/* ******************************************************************************** */
std::string shortestPathUsingBFS (Graph g, std::string src, std::string dest) {
    std::string result = "null";

    // Dynamic Queue - to store shortest path to each vertex
    std::vector<std::vector<std::string>> queue;

    // Variable containing all the edges
    std::vector<Edge> currEdges = g.getEdges();
    

    // Add source as the 1st element to Queue
    std::vector<std::string> newShortestPath;
    newShortestPath.push_back(src);
    queue.push_back(newShortestPath);

    if (src == dest) {
        return shortestPathToString(queue.back());
    }

    // Traverse Graph in BFS fashion
    for (int queueIndex = 0; queueIndex < ((int) queue.size()); queueIndex++) {
        for (int edgeIndex = 0; edgeIndex < ((int) currEdges.size()); edgeIndex++) {
            std::string edgeSrc = currEdges.at(edgeIndex).getSrc();
            std::string edgeDest = currEdges.at(edgeIndex).getDest();

            std::vector<std::string> currQueue = queue.at(queueIndex);

            // If current Vertex is a dest of current edge, then interchange src and dest
            // We are considering both - Since it is an undirected graph
            if (edgeDest == currQueue.back()) {
                std::string temp = edgeSrc;
                edgeSrc = edgeDest;
                edgeDest = temp;
            }

            if (edgeSrc == currQueue.back()  &&  !queueContains(queue, edgeDest)) {
                newShortestPath = currQueue;
                newShortestPath.push_back(edgeDest);

                queue.push_back(newShortestPath);

                if (edgeDest == dest) {
                    result = shortestPathToString(queue.back());
                    return result;
                }
            }
        }
    }

    return result;
}



// Function to check if Queue already contains the vertex (i.e. if BFS has already visited it)
bool queueContains (std::vector<std::vector<std::string>> queue, std::string vertex) {
    for (int i = 0; i < ((int) queue.size()); i++) {
        if (queue.at(i).back() == vertex) {
            return true;
        }
    }

    return false;
}



// Function to convert shortest path (vector array) to string
std::string shortestPathToString(std::vector<std::string> sP) {
    std::string result = "";

    if (sP.empty()) {
        return "null";
    }

    for (int i = 0; i < ((int) sP.size()); i++) {
        if (i != 0) {
            result += "-";
        }

        result += sP.at(i);
    }
    
    return result;
}
/* ******************************************************************************** */
