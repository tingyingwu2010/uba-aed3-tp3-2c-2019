#include <string>
#include <gmock/gmock.h>

#include "entities/entrypoint/OutputCVRP.h"

using ::testing::Contains;
using ::testing::AllOf;
using ::testing::Property;

TEST(OutputCVRPTest, SetBasicProperties) {
    auto *output = new OutputCVRP(std::vector<std::vector<int>>(), std::vector<int>());

    output->setCostoSolucion(123);
    output->setCantidadDeCamiones(3);

    std::vector<std::vector<int>> list;
    list.push_back(std::vector<int>({1, 5, 4, 1}));
    list.push_back(std::vector<int>({1, 2, 3, 1}));
    list.push_back(std::vector<int>({1, 6, 8, 7, 9}));

    output->setCaminos(list);

    ASSERT_EQ(output->getCantidadDeCamiones(), 3) << "CantidadDeCamiones differs";
    ASSERT_EQ(output->getCostoSolucion(), 123) << "CostoSolucion differs";

    for (int i = 0; i < list.size(); i++) {
        for (int j = 0; j < list[i].size(); j++) {
            ASSERT_EQ(output->getCaminos()[i][j], list[i][j])
                                        << "Caminos list differs {i: " << i << ", j: " << j << "} :: "
                                        << output->getCaminos()[i][j] << "_vs_" << list[i][j];
        }
    }
}
