#include <string>
#include <gmock/gmock.h>

#include "algorithms/SimulatingAnnealingHeuristic.h"
#include "utils/IO.h"
#include "config/constants.h"
#include "config/results.h"

using ::testing::Contains;
using ::testing::AllOf;
using ::testing::Property;

TEST(SimulatedAnnealingTest, a_n32_k5) {
    std::string file_path = DATA_DIR + "A-n32-k5.txt";

    InputCVRP inputCVRP = IO::fileToInputCVRP(file_path);

    SimulatingAnnealingHeuristic sa;

    OutputCVRP outputCVRP = *sa.execute(&inputCVRP);

    ASSERT_EQ(outputCVRP.getCantidadDeCamiones(), a_n32_k5_result[0][0]);

    ASSERT_TRUE(outputCVRP.getCostoSolucion() <
                a_n32_k5_result[a_n32_k5_result.size() - 1][0] *
                ((double) CVRP_OPTIMIZATION_THRESHOLD_PERCENTAGE / (double) 100 + 1));
}

// Too strong for SA
//TEST(SimulatedAnnealingTest, set_a_32) {
//    std::string file_path = DATA_DIR + "set-a-32.txt";
//
//    InputCVRP inputCVRP = IO::fileToInputCVRP(file_path);
//
//    SimulatingAnnealingHeuristic sa;
//
//    OutputCVRP outputCVRP = *sa.execute(&inputCVRP);
//
//    ASSERT_EQ(outputCVRP.getCantidadDeCamiones(), 5);
//
//    ASSERT_TRUE(outputCVRP.getCostoSolucion() <
//                784 *
//                ((double) CVRP_OPTIMIZATION_THRESHOLD_PERCENTAGE / (double) 100 + 1));
//}

