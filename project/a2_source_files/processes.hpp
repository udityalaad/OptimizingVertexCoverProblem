#pragma once

#include <string>
#include <vector>


// CLASS AND FUNCTION DECLARATIONS GO HERE


// Function to Parse the input line
void lineParsing (const std::string &line, std::string &cmd, int &noVert, std::vector<Edge> &edges, std::vector<std::string> &endPoints);

// Function to Split String on given delimiter
std::vector<std::string> splitString (std::string line, std::string delimiter);
