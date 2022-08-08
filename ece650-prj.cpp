// Compile with c++ ece650-a2cpp -std=c++11 -o ece650-a2
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <pthread.h>
#include <cmath>
#include <signal.h>

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

#include "prj_source_files/prj_processes.hpp"
#include "prj_source_files/prj_performance.hpp"



/* ******************************************************************************** */
//                              Data Structures
/* ******************************************************************************** */
// Data structure - used to - create arguments and/or data for vertexCover-specific thread functions
typedef struct graph_vc_struct {
    Graph g;
    std::vector<int> vc;
    double cpuTime;
    std::unique_ptr<Minisat::Solver> solver;
    bool interrupt;
} graph_vc_struct_t;
/* ******************************************************************************** */
/* ******************************************************************************** */



/* ******************************************************************************** */
//                      CPU-Time Specific Functions
/* ******************************************************************************** */
// Function to extract cpuTime from clockId
double cpuTime_using_clockId (clockid_t cid) {
    struct timespec ts;

    if (clock_gettime(cid, &ts) == -1) {
        std::string errorMessage = "Failed to execute 'pthread_getcpuclockid()'";
        std::cerr << "Error: " << errorMessage<< std::endl;
        exit(0);
    }

    double result = (double) ((intmax_t) ts.tv_sec);
    result +=  (double) (ts.tv_nsec) / (1000000 * 1000);

    return result;
}


// Function to find current-cpuTime of a particular thread using threadId
double findCurrentThreadCpuTime (pthread_t tid) {
    clockid_t cid;

    // Note the current clockId of given thread    
    if (pthread_getcpuclockid(tid, &cid) != 0) {
        std::string errorMessage = "Failed to execute 'pthread_getcpuclockid()'";
        std::cerr << "Error: " << errorMessage<< std::endl;
        exit(0);
    }

    return cpuTime_using_clockId(cid);
}
/* ******************************************************************************** */
/* ******************************************************************************** */



/* ******************************************************************************** */
//                      Thread-Specific Functions
/* ******************************************************************************** */
// Functions to be run by threads
void *handle_vertexCoverUsingCnfSATSolver (void *data) {
    graph_vc_struct_t *ds = (graph_vc_struct_t *)(data);
    
    // ++++++++++++++++++++
    double startCpuTime = findCurrentThreadCpuTime(pthread_self());

    // Find Vertex Cover
    std::vector<int> result = optimized_vertexCoverUsingCnfSATSolver(ds->g, ds->solver, ds->interrupt);

    double endtCpuTime = findCurrentThreadCpuTime(pthread_self());
    // ++++++++++++++++++++

    ds->vc = result;
    ds->cpuTime = endtCpuTime - startCpuTime;   // Find cpuTime required to find Vertex-Cover

    return nullptr;
}


void *handle_approxVC_1 (void *data) {
    graph_vc_struct_t *ds = (graph_vc_struct_t *)(data);

    // ++++++++++++++++++++
    double startCpuTime = findCurrentThreadCpuTime(pthread_self());

    // Find Vertex Cover
    std::vector<int> result = approxVC_1(ds->g);

    double endtCpuTime = findCurrentThreadCpuTime(pthread_self());
    // ++++++++++++++++++++

    ds->vc = result;
    ds->cpuTime = endtCpuTime - startCpuTime;   // Find cpuTime required to find Vertex-Cover
    
    return nullptr;
}


void *handle_approxVC_2 (void *data) {
    graph_vc_struct_t *ds = (graph_vc_struct_t *)(data);

    // ++++++++++++++++++++
    double startCpuTime = findCurrentThreadCpuTime(pthread_self());

    // Find Vertex Cover
    std::vector<int> result = approxVC_2(ds->g);

    double endtCpuTime = findCurrentThreadCpuTime(pthread_self());
    // ++++++++++++++++++++

    ds->vc = result;
    ds->cpuTime = endtCpuTime - startCpuTime;   // Find cpuTime required to find Vertex-Cover

    return nullptr;
}
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//                         Thread Implementation
/* ******************************************************************************** */
// Function to create & initialize timespec variable (with addedTime)
struct timespec createAndInitializeTimeSpecWithAddedTime (int timeToAdd) {
    clockid_t current_thread_cid;
    // Note the current clockId of given thread
    if (pthread_getcpuclockid(pthread_self(), &current_thread_cid) != 0) {
        std::string errorMessage = "Failed to execute 'pthread_getcpuclockid()'";
        std::cerr << "Error: " << errorMessage<< std::endl;
        exit(0);
    }

    struct timespec current_thread_ts;
    if (clock_gettime(CLOCK_REALTIME, &current_thread_ts) == -1) {
        std::string errorMessage = "Failed to execute 'pthread_getcpuclockid()'";
        std::cerr << "Error: " << errorMessage<< std::endl;
        exit(0);
    }

    current_thread_ts.tv_sec += timeToAdd;

    return current_thread_ts;
}


// Function to run multiple threads - in order to find vertex-cover using different methods
// And print the results
std::string findAndPrintVertexCover (Graph graph, vertexWise_performanceParameters_struct &pp) {
    // Maximum time allowed (in Seconds) - for an instance of CNF-SOLVER to run
    const double MAX_ALLOWED_TIME = 10;  // in Seconds
    
    // Create pthread_t's
    pthread_t t_handle_vertexCoverUsingCnfSATSolver;
    pthread_t t_handle_approxVC_1;
    pthread_t t_handle_approxVC_2;

    
    /* -------- Step 1 - Create arguments and/or data for each thread function -------- */
    graph_vc_struct_t ds_vertexCoverUsingCnfSATSolver = {.g = graph};
    ds_vertexCoverUsingCnfSATSolver.solver.reset(new Minisat::Solver());
    ds_vertexCoverUsingCnfSATSolver.interrupt = false;

    graph_vc_struct_t ds_approxVC_1 = {.g = graph};
    graph_vc_struct_t ds_approxVC_2 = {.g = graph};


    /* -------- Step 2 - Create threads for each method of finding Veretx Cover -------- */
    pthread_create(&t_handle_vertexCoverUsingCnfSATSolver, nullptr, handle_vertexCoverUsingCnfSATSolver, (void *) &ds_vertexCoverUsingCnfSATSolver);    
    pthread_create(&t_handle_approxVC_1, nullptr, handle_approxVC_1, (void *) &ds_approxVC_1);
    pthread_create(&t_handle_approxVC_2, nullptr, handle_approxVC_2, (void *) &ds_approxVC_2);


    /* -------- Step 3 - Wait for all threads to end (& interrupt CNF-SAT-Solver on timeout) -------- */
    struct timespec current_thread_ts = createAndInitializeTimeSpecWithAddedTime(MAX_ALLOWED_TIME);
    int timeout = pthread_timedjoin_np(t_handle_vertexCoverUsingCnfSATSolver, nullptr, &current_thread_ts);

    if (timeout == 110) {
        ds_vertexCoverUsingCnfSATSolver.interrupt = true;
        ds_vertexCoverUsingCnfSATSolver.solver->interrupt();
        pthread_join(t_handle_vertexCoverUsingCnfSATSolver, nullptr);

    } else if (timeout != 0) {
        std::string errorMessage = "Failed to execute 'pthread_timedjoin_np()'";
        std::cerr << "Error: " << errorMessage<< std::endl;
        exit(0);
    }

    pthread_join(t_handle_approxVC_1, nullptr);
    pthread_join(t_handle_approxVC_2, nullptr);

    
    /* -------- Step 4 - Print Vertex Covers -------- */
    std::string result;
    if (timeout != 110) {
        result = "CNF-SAT-VC: " + vertexCover_toString_commaSeparated(ds_vertexCoverUsingCnfSATSolver.vc); //std::to_string(ds_vertexCoverUsingCnfSATSolver.vc.size());
    } else {
        result = "CNF-SAT-VC: timeout";
        // ds_vertexCoverUsingCnfSATSolver.cpuTime = MAX_ALLOWED_TIME;
    }
    result += "\nAPPROX-VC-1: " + vertexCover_toString_commaSeparated(ds_approxVC_1.vc);
    result += "\nAPPROX-VC-2: " + vertexCover_toString_commaSeparated(ds_approxVC_2.vc);


    /* -------- Step 5 - Collect Parameters (To be used for generating Graph) -------- */
    if (timeout != 110) {
        // CPU Time(s)
        appendPerformanceParameterForVertex(pp.v_cpuRT_cnfSatVC, graph.getNoVertices(), ds_vertexCoverUsingCnfSATSolver.cpuTime);
        appendPerformanceParameterForVertex(pp.v_cpuRT_approxVC_1, graph.getNoVertices(), ds_approxVC_1.cpuTime);
        appendPerformanceParameterForVertex(pp.v_cpuRT_approxVC_2, graph.getNoVertices(), ds_approxVC_2.cpuTime);

        // Approximation Ratio(s)
        appendPerformanceParameterForVertex(pp.v_AR_cnfSatVC, graph.getNoVertices(), findApproximationRatio((int) ds_vertexCoverUsingCnfSATSolver.vc.size(), (int) ds_vertexCoverUsingCnfSATSolver.vc.size()));
        appendPerformanceParameterForVertex(pp.v_AR_approxVC_1, graph.getNoVertices(), findApproximationRatio((int) ds_approxVC_1.vc.size(), (int) ds_vertexCoverUsingCnfSATSolver.vc.size()));
        appendPerformanceParameterForVertex(pp.v_AR_approxVC_2, graph.getNoVertices(), findApproximationRatio((int) ds_approxVC_2.vc.size(), (int) ds_vertexCoverUsingCnfSATSolver.vc.size()));

    } else {
        // CPU Time(s)
        appendPerformanceParameterForVertex(pp.v_cpuRT_cnfSatVC, graph.getNoVertices(), MAX_ALLOWED_TIME);
        appendPerformanceParameterForVertex(pp.v_cpuRT_approxVC_1, graph.getNoVertices(), ds_approxVC_1.cpuTime);
        appendPerformanceParameterForVertex(pp.v_cpuRT_approxVC_2, graph.getNoVertices(), ds_approxVC_2.cpuTime);

        // Approximation Ratio(s)
        appendPerformanceParameterForVertex(pp.v_AR_cnfSatVC, graph.getNoVertices(), -1);
        appendPerformanceParameterForVertex(pp.v_AR_approxVC_1, graph.getNoVertices(), -1);
        appendPerformanceParameterForVertex(pp.v_AR_approxVC_2, graph.getNoVertices(), -1);
    }

    return result;
}
/* ******************************************************************************** */
/* ******************************************************************************** */




/* ******************************************************************************** */
//                              Main Method
/* ******************************************************************************** */
int main(int argc, char** argv) {
    // Test code. Replaced with your code
    
    Graph graph = Graph();

    // Variable holding all the required vertexWise - performanceParameters
    vertexWise_performanceParameters_struct pp;

    // read from stdin until EOF
    while (!std::cin.eof()) {        
        try {
            // read a line of input until EOL and store in a string
            std::string line;
            std::getline(std::cin, line);

            std::string cmd = "";
            int noVert = 0;
            std::vector<Edge> edges;
            std::vector<std::string> endPoints;

            lineParsing(line, cmd, noVert, edges, endPoints);
            if (cmd == "V") {
                graph.setNoVertices(noVert);

            } else if (cmd == "E") {
                graph.setEdges(edges);

                std::string string_VCs = findAndPrintVertexCover(graph, pp);
                std::cout << string_VCs << std::endl;

            } else if (cmd == "s") {
                std::string shorestPathResult = graph.generateShortestPath (endPoints.at(0), endPoints.at(1));
                std::cout << shorestPathResult << std::endl;
            }

        } catch (std::string exc) {
            std::cerr << "Error: " << exc << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // // For Graph (Report)
    // std::cout << string_accumulatedPerformanceParameters(pp) << std::endl;
    // std::cout << string_mean_sd(pp) << std::endl;

    return 0;
}
/* ******************************************************************************** */
/* ******************************************************************************** */