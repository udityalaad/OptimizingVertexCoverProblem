#pragma once

#include <string>
#include <vector>


// CLASS AND FUNCTION DECLARATIONS GO HERE


/* ******************************************************************************** */
//                              Data Structures
/* ******************************************************************************** */
// // Data structure - used to - store vertexWise performanceParameters - for each vertexCover algorithm (& for each parameter)
typedef struct vertexWise_performanceParameters_struct {
    // Variables holding cpuRunningTime(s) for all executions corresponding to a particular 'noVertices' (v)
    std::vector<std::pair<int, std::vector<double>>> v_cpuRT_cnfSatVC;
    std::vector<std::pair<int, std::vector<double>>> v_cpuRT_approxVC_1;
    std::vector<std::pair<int, std::vector<double>>> v_cpuRT_approxVC_2;

    // Variables holding approximationRatio(s) for all executions corresponding to a particular 'noVertices' (v)
    std::vector<std::pair<int, std::vector<double>>> v_AR_cnfSatVC;
    std::vector<std::pair<int, std::vector<double>>> v_AR_approxVC_1;
    std::vector<std::pair<int, std::vector<double>>> v_AR_approxVC_2;
} vertexWise_performanceParameters_struct;
/* ******************************************************************************** */
/* ******************************************************************************** */


/* ******************************************************************************** */
//                  Functions to find 'Performance' parameters
/* ******************************************************************************** */
// Function to 'Approximation Ratio' for different methods of finding 'Vertex-Cover'
// computed_k = Size of computed vertex-cover
// optimal_k = Size of minimum (optimal) vertex-cover
double findApproximationRatio (int computed_k, int optimal_k);
/* ******************************************************************************** */
/* ******************************************************************************** */


/* ******************************************************************************** */
//  Functions - to perform Mathematical Operations on 'Performance Parameters'
/* ******************************************************************************** */
// Function to get only the positive values inside the given vector
std::vector<double> positivesInVector (std::vector<double> input);

// Function to find 'MEAN' of a vector of values
double mean (std::vector<double> input);

// Function to find 'STANDARD DEVIATION' of a vector of values
double standardDeviation (std::vector<double> input);

// Function to find 'MEAN' & 'STANDARD DEVIATION' of performanceParameters(cpuTime / approximationRatio), corresponding to each 'v' (noVertices)
std::vector<std::tuple<int, double, double>> v_mean_sD_values (std::vector<std::pair<int, std::vector<double>>> v_performanceParameter);
/* ******************************************************************************** */
/* ******************************************************************************** */


/* ******************************************************************************** */
//          Functions for accumulating/collecting 'Performance parameters'
/* ******************************************************************************** */
// Function to append a 'performanceParameter' value corresponding to the given 'v' (noVertices)
void appendPerformanceParameterForVertex (std::vector<std::pair<int, std::vector<double>>> &v_performanceParameter, int v, double performanceParameter);
/* ******************************************************************************** */
/* ******************************************************************************** */


/* ******************************************************************************** */
// Functions to transform 'Performance Parameters' to a User/Graph - Readable Format
/* ******************************************************************************** */
// Function to return performanceParameters in string format
std::string string_performanceParameters (std::string details, std::vector<std::pair<int, std::vector<double>>> v_performanceParameter);

// Function to return cpuRunningTime(s) & approximationRatio(s) - for all executions corresponding to each 'noVertices' (v)
std::string string_accumulatedPerformanceParameters (vertexWise_performanceParameters_struct pp);

// Function to return 'mean' & 'standardDeviation' associated with each vertex in string format (v, mean, standardDeviation)
// This will be input for the Graph (to be used in Project Report)
std::string string_mean_sd (vertexWise_performanceParameters_struct pp);
/* ******************************************************************************** */
/* ******************************************************************************** */