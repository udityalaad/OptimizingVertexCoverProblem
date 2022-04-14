#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>

#include "edge.hpp"
#include "processes.hpp"


// Function to Parse the input line
void lineParsing (const std::string &line, std::string &cmd, int &noVert, std::vector<Edge> &edges, std::vector<std::string> &endPoints) {
    cmd = "";
    noVert = 0;
    edges.clear();
    endPoints.clear();

    std::string tempLineCheck = line;
    tempLineCheck.erase(std::remove(tempLineCheck.begin(), tempLineCheck.end(), ' '), tempLineCheck.end());       // Remove every occurence of ' ' in tempLineCheck
    // if nothing was read, return
    if (tempLineCheck.size() == 0) {
        return;
    }

    std::vector<std::string> args = splitString(line, " ");

    /* Process args */
    cmd = args.at(0);
    if (cmd == "V") {
        noVert = std::__cxx11::stoi(args.at(1));

        return;

    } else if (cmd == "E") {
        std::string edgeStr = args.at(1);

        // If no/zero edges have been provide inside curly braces
        if (edgeStr.length() == 2  &&  edgeStr.at(0) == '{'  && edgeStr.at(1) == '}') {
            return;
        }

        edgeStr = edgeStr.erase(0, 2);                      // Remove first 2 characters
        edgeStr = edgeStr.erase(edgeStr.length() - 2, 2);   // Remove last 2 characters
        
        std::vector<std::string> edgeStrArray = splitString(edgeStr, ">,<");

        // Create 'edges' - array (vector)
        for (int i = 0; i < ((int) edgeStrArray.size()); i++) {
            std::vector<std::string> edgeVert = splitString(edgeStrArray[i], ",");

            edges.push_back(Edge(edgeVert.at(0), edgeVert.at(1)));
        }

        return;

    } else if (cmd == "s") {
        if (!(args.size() < 3)) {
            endPoints.push_back(args[1]);
            endPoints.push_back(args[2]);

            return;
        }
    }

    std::string errorMessage = "Failed to read the input";
    throw errorMessage;
}




// Function to Split String on given delimiter
std::vector<std::string> splitString (std::string line, std::string delimiter) {
    std::vector<std::string> args;

    int pos = 0;
    int i = 0;
    std::string token;

    // Assign args
    for (i = 0;   (pos = line.find(delimiter))  !=  ((int) std::string::npos);  i++) {
        token = line.substr(0, pos);
        line.erase(0, pos + delimiter.length());
        args.push_back(token);
    }
    args.push_back(line);

    return args;
}

