cmake_minimum_required(VERSION 2.8.12)
project(ece650-a4)

find_package (Threads)

if (EXISTS "${CMAKE_SOURCE_DIR}/minisat")
  add_subdirectory(minisat)
else()
  message (FATAL_ERROR "MiniSat not found. Use `git clone https://github.com/agurfinkel/minisat` to check it out.")
endif()


## ECE650 Specific configuration start here
## Project specific configurations go here

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

# expose minisat header files
include_directories(${CMAKE_SOURCE_DIR}/minisat)

option(WITH_ASAN "Enabled AddressSanitizer to detect memory faults" OFF)
if(WITH_ASAN)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined" )
endif()


# create the main executable
## add additional .cpp files if needed
add_executable(ece650-prj ece650-prj.cpp prj_source_files/prj_processes.cpp prj_source_files/prj_performance.cpp a4_source_files/a4_processes.cpp a2_source_files/processes.cpp a2_source_files/graph.cpp a2_source_files/edge.cpp )

# link MiniSAT libraries
target_link_libraries(ece650-prj minisat-lib-static)
target_link_libraries(ece650-prj ${CMAKE_THREAD_LIBS_INIT})

# create the executable for tests
add_executable(tests_ece650-a2 test_ece650-a2.cpp a2_source_files/processes.cpp a2_source_files/graph.cpp a2_source_files/edge.cpp )
add_executable(tests_ece650-a4 test_ece650-a4.cpp a4_source_files/a4_processes.cpp a2_source_files/processes.cpp a2_source_files/graph.cpp a2_source_files/edge.cpp )
add_executable(tests_ece650-prj test_ece650-prj.cpp prj_source_files/prj_processes.cpp prj_source_files/prj_performance.cpp a4_source_files/a4_processes.cpp a2_source_files/processes.cpp a2_source_files/graph.cpp a2_source_files/edge.cpp )
add_executable(test test.cpp)

# link MiniSAT libraries
target_link_libraries(tests_ece650-a2 minisat-lib-static)
target_link_libraries(tests_ece650-a4 minisat-lib-static)
target_link_libraries(tests_ece650-prj minisat-lib-static)
target_link_libraries(test minisat-lib-static)

