cmake_minimum_required(VERSION 3.12)
project(tp3_heuristicas_cvrp)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/entities/entrypoint/InputCVRP.cpp src/entities/entrypoint/InputCVRP.h src/algorithms/SavingsEuristic.cpp src/algorithms/SavingsEuristic.h src/entities/entrypoint/OutputCVRP.cpp src/entities/entrypoint/OutputCVRP.h src/algorithms/CVRPEuristic.h src/entities/core/Dot.h src/entities/core/Dot.cpp src/utils/io.hpp src/entities/core/AdyacencyMatrixGraph.h src/entities/core/AdyacencyMatrixGraph.cpp src/entities/core/Graph.h src/utils/util.hpp)
add_executable(test-32 src/executables/output_example.cpp)
add_executable(savings-main src/executables/savings-main.cpp ${SOURCE_FILES})
add_executable(goloso-main src/executables/goloso-main.cpp ${SOURCE_FILES})