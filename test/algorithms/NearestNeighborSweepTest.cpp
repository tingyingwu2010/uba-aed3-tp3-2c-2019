//
// Created by Christian nahuel Rivera on 15/12/19.
//

#include <gmock/gmock.h>
#include <entities/entrypoint/InputCVRP.h>
#include <utils/IO.h>
#include <entities/entrypoint/OutputCVRP.h>
#include <algorithms/utils/ValidateOutputCvrp.h>
#include <algorithms/NearestNeighborSweep.h>


using ::testing::Contains;
using ::testing::AllOf;
using ::testing::Property;


TEST(NearestNeighborSweepTest, test1){
    NearestNeighborSweep csw;
    InputCVRP inputCVRP = IO::fileToInputCVRP("../test/data/input/A-n32-k5.txt");


    OutputCVRP outputCVRP = *csw.execute(&inputCVRP);


    ASSERT_TRUE(ValidateOutputCvrp::validate(&outputCVRP, &inputCVRP));
}

TEST(NearestNeighborSweepTest, test2){
    NearestNeighborSweep csw;
    InputCVRP inputCVRP = IO::fileToInputCVRP("../test/data/input/set-a-32.txt");


    OutputCVRP outputCVRP = *csw.execute(&inputCVRP);


    ASSERT_TRUE(ValidateOutputCvrp::validate(&outputCVRP, &inputCVRP));
}

TEST(NearestNeighborSweepTest, test3){
    NearestNeighborSweep csw;
    InputCVRP inputCVRP = IO::fileToInputCVRP("../test/data/input/X-n502-k39.txt");


    OutputCVRP outputCVRP = *csw.execute(&inputCVRP);


    ASSERT_TRUE(ValidateOutputCvrp::validate(&outputCVRP, &inputCVRP));
}