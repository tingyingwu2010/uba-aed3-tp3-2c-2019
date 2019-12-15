
cmake_minimum_required(VERSION 3.10)

project(tp3_heuristicas_cvrp)

# ==== Platform dependent options ====
if(APPLE)
    # Support for APPLE
    set(EXTERNAL_LIB_DIR ${CMAKE_SOURCE_DIR}/lib/platform/darwin)
else()
    # Support 64 bit linux
    set(EXTERNAL_LIB_DIR ${CMAKE_SOURCE_DIR}/lib/platform/linux64)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

# ======= Compilation options ========
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# ========== Main variables ==========
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(MAIN_CWS ${SRC_DIR}/executables/savings_main.cpp)
set(MAIN_GREEDY ${SRC_DIR}/executables/goloso_main.cpp)
set(MAIN_CLUSTER ${SRC_DIR}/executables/cluster_main.cpp)
set(MAIN_CLUSTER_ALTERNATIVE ${SRC_DIR}/executables/cluster_alternative_main.cpp)
set(MAIN_SA ${SRC_DIR}/executables/sa_main.cpp)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(DATA_DIR ${CMAKE_SOURCE_DIR}/test/data/input)
set(EXTERNAL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

# ======= Include directories ========
include_directories(${SRC_DIR})
include_directories(${EXTERNAL_INCLUDE_DIR})

# ========= Link directories =========
link_directories(${EXTERNAL_LIB_DIR})

# =========== Executables ============
# ===== SOURCES =====
file(GLOB_RECURSE SOURCE_FILES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.h ${SRC_DIR}/*.hpp)
list(REMOVE_ITEM SOURCE_FILES ${MAIN_CWS})
list(REMOVE_ITEM SOURCE_FILES ${MAIN_GREEDY})
list(REMOVE_ITEM SOURCE_FILES ${MAIN_CLUSTER})
list(REMOVE_ITEM SOURCE_FILES ${MAIN_CLUSTER_ALTERNATIVE})
list(REMOVE_ITEM SOURCE_FILES ${MAIN_SA})

add_library(cvrp_src ${SOURCE_FILES})

target_link_libraries(cvrp_src LINK_PUBLIC)

# ====== MAIN =======
include(GoogleTest)
add_executable(cvrp_cws ${MAIN_CWS})
add_executable(cvrp_greedy ${MAIN_GREEDY})
add_executable(cvrp_cluster ${MAIN_CLUSTER})
add_executable(cvrp_cluster_alternative ${MAIN_CLUSTER_ALTERNATIVE})
add_executable(cvrp_sa ${MAIN_SA})
target_link_libraries(cvrp_cws LINK_PUBLIC cvrp_src)
target_link_libraries(cvrp_greedy LINK_PUBLIC cvrp_src)
target_link_libraries(cvrp_cluster LINK_PUBLIC cvrp_src)
target_link_libraries(cvrp_cluster_alternative LINK_PUBLIC cvrp_src)
target_link_libraries(cvrp_sa LINK_PUBLIC cvrp_src)

# ====== TESTS ======
enable_testing()

file(GLOB_RECURSE TEST_FILES ${TEST_DIR}/*.cpp ${TEST_DIR}/*.h ${TEST_DIR}/*.hpp ${TEST_DIR}/*.txt)

add_executable(cvrp_test ${TEST_FILES})

target_include_directories(cvrp_test PUBLIC ${TEST_DIR})
target_link_libraries(cvrp_test LINK_PUBLIC cvrp_src gtest gmock)


gtest_discover_tests(cvrp_test)

