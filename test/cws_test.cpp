#include <string>
#include <gmock/gmock.h>

#include "algorithms/SavingsHeuristic.h"
#include "utils/IO.h"
#include "config/constants.h"
#include "config/results.h"

using ::testing::Contains;
using ::testing::AllOf;
using ::testing::Property;

TEST(CWSTest, a_n32_k5) {
    std::string file_path = DATA_DIR + "A-n32-k5.txt";

    InputCVRP inputCVRP = IO::fileToInputCVRP(file_path);

    SavingsHeuristic csw;

    OutputCVRP outputCVRP = *csw.execute(&inputCVRP);

    ASSERT_EQ(outputCVRP.getCantidadDeCamiones(), a_n32_k5_result[0][0]);

    ASSERT_TRUE(outputCVRP.getCostoSolucion() <
                a_n32_k5_result[a_n32_k5_result.size() - 1][0] *
                ((double) CVRP_OPTIMIZATION_TRESHOLD_PERCENTAGE / (double) 100 + 1));

    for (int i = 1; i <= outputCVRP.getCantidadDeCamiones(); i++) {
        for (int j = 0; j < a_n32_k5_result[i].size(); j++) {
            ASSERT_EQ(outputCVRP.getCaminos()[i - 1][j], a_n32_k5_result[i][j])
                                        << "Failed with { i: " << i << ", j: " << j << " } | output: 0"
                                        << outputCVRP.getCaminos()[i - 1][j] << " - a_n32: " << a_n32_k5_result[i][j]
                                        << endl;
        }
    }
}

TEST(CWSTest, set_a_32) {
    std::string file_path = DATA_DIR + "set-a-32.txt";

    InputCVRP inputCVRP = IO::fileToInputCVRP(file_path);

    SavingsHeuristic csw;

    OutputCVRP outputCVRP = *csw.execute(&inputCVRP);

    ASSERT_EQ(outputCVRP.getCantidadDeCamiones(), 5);

    ASSERT_TRUE(outputCVRP.getCostoSolucion() <
                784 *
                ((double) CVRP_OPTIMIZATION_TRESHOLD_PERCENTAGE / (double) 100 + 1));
}

TEST(CWSTest, X_n502_k39) {
    std::string file_path = DATA_DIR + "X-n502-k39.txt";

    InputCVRP inputCVRP = IO::fileToInputCVRP(file_path);

    SavingsHeuristic csw;

    OutputCVRP outputCVRP = *csw.execute(&inputCVRP);

    ASSERT_EQ(outputCVRP.getCantidadDeCamiones(), 39);

    ASSERT_TRUE(outputCVRP.getCostoSolucion() <
                69230 * ((double) CVRP_OPTIMIZATION_TRESHOLD_PERCENTAGE / (double) 100 + 1));
}