//
// Created by Christian nahuel Rivera on 11/12/19.
//

#include <gmock/gmock.h>
#include <entities/entrypoint/InputCVRP.h>
#include <utils/IO.h>
#include <algorithms/GreedyHeuristic.h>
#include <algorithms/utils/ValidateOutputCvrp.h>
#include <string>

using ::testing::Contains;
using ::testing::AllOf;
using ::testing::Property;

TEST(GreedyHeuristicTest, test1){
    GreedyHeuristic csw;
    InputCVRP inputCVRP = IO::fileToInputCVRP("../test/data/input/A-n32-k5.txt");


    OutputCVRP outputCVRP = *csw.execute(&inputCVRP);


    ASSERT_TRUE(ValidateOutputCvrp::validate(&outputCVRP, &inputCVRP));
}

TEST(GreedyHeuristicTest, test2){
    GreedyHeuristic csw;
    InputCVRP inputCVRP = IO::fileToInputCVRP("../test/data/input/set-a-32.txt");


    OutputCVRP outputCVRP = *csw.execute(&inputCVRP);


    ASSERT_TRUE(ValidateOutputCvrp::validate(&outputCVRP, &inputCVRP));
}

TEST(GreedyHeuristicTest, test3){
    GreedyHeuristic csw;
    InputCVRP inputCVRP = IO::fileToInputCVRP("../test/data/input/X-n502-k39.txt");


    OutputCVRP outputCVRP = *csw.execute(&inputCVRP);


    ASSERT_TRUE(ValidateOutputCvrp::validate(&outputCVRP, &inputCVRP));
}