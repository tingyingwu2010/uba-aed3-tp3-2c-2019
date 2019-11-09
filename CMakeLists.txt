cmake_minimum_required(VERSION 3.12)
project(tp3_heuristicas_cvrp)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/entities/entrypoint/InputCVRP.cpp src/entities/entrypoint/InputCVRP.h src/algorithms/SavingsEuristic.cpp src/algorithms/SavingsEuristic.h src/entities/entrypoint/OutputCVRP.cpp src/entities/entrypoint/OutputCVRP.h src/algorithms/CVRPEuristic.h src/entities/core/Dot.h src/entities/core/Dot.cpp)
add_executable(test-32 src/executables/output_example.cpp)
add_executable(savings-main src/executables/savings-main.cpp ${SOURCE_FILES})