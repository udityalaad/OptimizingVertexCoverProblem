#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <pthread.h>
#include <cmath>
#include <tuple>

#include "prj_performance.hpp"





/* ******************************************************************************** */
//                  Functions to find 'Performance' parameters
/* ******************************************************************************** */
// Function to 'Approximation Ratio' for different methods of finding 'Vertex-Cover'
// computed_k = Size of computed vertex-cover
// optimal_k = Size of minimum (optimal) vertex-cover
double findApproximationRatio (int computed_k, int optimal_k) {
    double result =  (double) ((double) computed_k) / ((double) optimal_k);
    return result;
}
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//  Functions - to perform Mathematical Operations on 'Performance Parameters'
/* ******************************************************************************** */
// Function to get only the positive values inside the given vector
std::vector<double> positivesInVector (std::vector<double> input) {
    std::vector<double> result;

    for (int i = 0; i < ((int) input.size()); i++) {
        if (input.at(i) >= 0) {
            result.push_back(input.at(i));
        }
    }
    
    return result;
}


// Function to find 'MEAN' of a vector of values
double mean (std::vector<double> input) {
    // Consider only Valid-values (positive-values) 
    std::vector<double> values = positivesInVector(input);

    if (((int) values.size()) == 0) {
        return -1;
    }

    double sum = 0;
    for (int i = 0; i < ((int) values.size()); i++) {
        sum += values.at(i);
    }

    double result = (double) (sum / values.size());

    return result;
}


// Function to find 'STANDARD DEVIATION' of a vector of values
double standardDeviation (std::vector<double> input) {
    // Consider only Valid-values (positive-values) 
    std::vector<double> values = positivesInVector(input);

    if (((int) values.size()) == 0) {
        return -1;
    }

    double m = mean(values);

    double sum = 0;
    for (int i = 0; i < ((int) values.size()); i++) {
        sum += pow((values.at(i) - m), 2);
    }

    double result = (double) sqrt((double) sum / values.size());

    return result;
}


// Function to find 'MEAN' & 'STANDARD DEVIATION' of performanceParameters(cpuTime / approximationRatio), corresponding to each 'v' (noVertices)
std::vector<std::tuple<int, double, double>> v_mean_sD_values (std::vector<std::pair<int, std::vector<double>>> v_performanceParameter) {
    std::vector<std::tuple<int, double, double>> result;
    
    for (int i = 0; i < ((int) v_performanceParameter.size()); i++) {
        int v = v_performanceParameter.at(i).first;
        std::vector<double> pp = v_performanceParameter.at(i).second;

        
        result.push_back(std::make_tuple(v, mean(pp), standardDeviation(pp)));
    }

    return result;
}
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//          Functions for accumulating/collecting 'Performance parameters'
/* ******************************************************************************** */
// Function to append a 'performanceParameter' value corresponding to the given 'v' (noVertices)
void appendPerformanceParameterForVertex (std::vector<std::pair<int, std::vector<double>>> &v_performanceParameter, int v, double performanceParameter) {
    bool recordExists = false;

    // Append corresponding to 'v' (noVertices), if a record for 'v' already exists
    for (int i = 0; i < ((int) v_performanceParameter.size()); i++) {
        if (v_performanceParameter.at(i).first == v) {
            v_performanceParameter.at(i).second.push_back(performanceParameter);
            recordExists = true;
            break;
        }
    }

    // Create a new record corresponding to 'v'(noVertices), if a record for 'v' does not exist
    if (!recordExists) {
        std::vector<double> pp;
        pp.push_back(performanceParameter);

        v_performanceParameter.push_back(std::make_pair(v, pp));
    }
}
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
// Functions to transform 'Performance Parameters' to a User/Graph - Readable Format
/* ******************************************************************************** */
// Function to return performanceParameters in string format
std::string string_performanceParameters (std::string details, std::vector<std::pair<int, std::vector<double>>> v_performanceParameter) {
    std::string result = details + " : ";

    for (int i = 0; i < ((int) v_performanceParameter.size()); i++) {
        int v = v_performanceParameter.at(i).first;
        std::vector<double> pp = v_performanceParameter.at(i).second;

        result += "\n\tV = " + std::to_string(v) + " :";
        for (int j = 0; j < ((int) pp.size()); j++) {
            result += " " + std::to_string(pp.at(j));
        }
    }

    return result;
}


// Function to return cpuRunningTime(s) & approximationRatio(s) - for all executions corresponding to each 'noVertices' (v)
std::string string_accumulatedPerformanceParameters (vertexWise_performanceParameters_struct pp) {
    // Variables holding cpuRunningTime(s) for all executions corresponding to each 'noVertices' (v)
    std::string final_pp_string = "\n" + string_performanceParameters("CPU Running Time - CNF-SAT-VC", pp.v_cpuRT_cnfSatVC);
    final_pp_string += "\n" + string_performanceParameters("CPU Running Time - APPROX-VC-1", pp.v_cpuRT_approxVC_1);
    final_pp_string += "\n" + string_performanceParameters("CPU Running Time - APPROX-VC-2", pp.v_cpuRT_approxVC_2);

    // Variables holding approximationRatio(s) for all executions corresponding to each 'noVertices' (v)
    final_pp_string += "\n" + string_performanceParameters("Approximation Ratio - CNF-SAT-VC", pp.v_AR_cnfSatVC);
    final_pp_string += "\n" + string_performanceParameters("Approximation Ratio - APPROX-VC-1", pp.v_AR_approxVC_1);
    final_pp_string += "\n" + string_performanceParameters("Approximation Ratio - APPROX-VC-2", pp.v_AR_approxVC_2);

    return final_pp_string;
}


// Function to return 'mean' & 'standardDeviation' associated with each vertex in string format (v, mean, standardDeviation)
// This will be input for the Graph (to be used in Project Report)
std::string string_mean_sd (vertexWise_performanceParameters_struct pp) {
    std::vector<std::tuple<int, double, double>> vMS_cpuRT_cnfSatVC = v_mean_sD_values(pp.v_cpuRT_cnfSatVC);
    std::vector<std::tuple<int, double, double>> vMS_cpuRT_approxVC_1 = v_mean_sD_values(pp.v_cpuRT_approxVC_1);
    std::vector<std::tuple<int, double, double>> vMS_cpuRT_approxVC_2 = v_mean_sD_values(pp.v_cpuRT_approxVC_2);

    std::vector<std::tuple<int, double, double>> vMS_aR_cnfSatVC = v_mean_sD_values(pp.v_AR_cnfSatVC);
    std::vector<std::tuple<int, double, double>> vMS_aR_approxVC_1 = v_mean_sD_values(pp.v_AR_approxVC_1);
    std::vector<std::tuple<int, double, double>> vMS_aR_approxVC_2 = v_mean_sD_values(pp.v_AR_approxVC_2);


    // CPU Run-Time (Mean + Standard Deviation)
    std::string result = std::string("v")
                            + std::string("\tcpu_cnf_Mean\tcpu_cnf_SD") + std::string("\tcpu_vc1_Mean\tcpu_vc1_SD") + std::string("\tcpu_vc2_Mean\tcpu_vc2_SD");
    for (int i = 0; i < ((int) vMS_cpuRT_cnfSatVC.size()); i++) {
        int v = std::get<0>(vMS_cpuRT_cnfSatVC.at(i));
        std::string cpu_cnf_Mean = std::to_string(std::get<1>(vMS_cpuRT_cnfSatVC.at(i)));
        std::string cpu_cnf_SD = std::to_string(std::get<2>(vMS_cpuRT_cnfSatVC.at(i)));

        std::string cpu_vc1_Mean = std::to_string(std::get<1>(vMS_cpuRT_approxVC_1.at(i)));
        std::string cpu_vc1_SD = std::to_string(std::get<2>(vMS_cpuRT_approxVC_1.at(i)));

        std::string cpu_vc2_Mean = std::to_string(std::get<1>(vMS_cpuRT_approxVC_2.at(i)));
        std::string cpu_vc2_SD = std::to_string(std::get<2>(vMS_cpuRT_approxVC_2.at(i)));

        result += "\n" + std::to_string(v)
                    + "\t" + cpu_cnf_Mean + "\t\t" + cpu_cnf_SD + "\t" + cpu_vc1_Mean + "\t" + cpu_vc1_SD + "\t" + cpu_vc2_Mean + "\t" + cpu_vc2_SD;
    }


    // Approximation Ratio (Mean + Standard Deviation)
    result += "\n\n" + std::string("v")
                            + std::string("\tar_cnf_Mean\tar_cnf_SD") + std::string("\tar_vc1_Mean\tar_vc1_SD") + std::string("\tar_vc2_Mean\tar_vc2_SD\t");
    for (int i = 0; i < ((int) vMS_cpuRT_cnfSatVC.size()); i++) {
        int v = std::get<0>(vMS_cpuRT_cnfSatVC.at(i));
        std::string ar_cnf_Mean = std::to_string(std::get<1>(vMS_aR_cnfSatVC.at(i)));
        std::string ar_cnf_SD = std::to_string(std::get<2>(vMS_aR_cnfSatVC.at(i)));

        std::string ar_vc1_Mean = std::to_string(std::get<1>(vMS_aR_approxVC_1.at(i)));
        std::string ar_vc1_SD = std::to_string(std::get<2>(vMS_aR_approxVC_1.at(i)));

        std::string ar_vc2_Mean = std::to_string(std::get<1>(vMS_aR_approxVC_2.at(i)));
        std::string ar_vc2_SD = std::to_string(std::get<2>(vMS_aR_approxVC_2.at(i)));

        if (std::stod(ar_cnf_Mean) != -1) {
            result += "\n" + std::to_string(v)
                    + "\t" + ar_cnf_Mean + "\t" + ar_cnf_SD + "\t" + ar_vc1_Mean + "\t" + ar_vc1_SD + "\t" + ar_vc2_Mean + "\t" + ar_vc2_SD;
        }
    }

    return result;
}
/* ******************************************************************************** */
/* ******************************************************************************** */




