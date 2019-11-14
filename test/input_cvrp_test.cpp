#include <string>
#include <gmock/gmock.h>

#include "entities/entrypoint/InputCVRP.h"

using ::testing::Contains;
using ::testing::AllOf;
using ::testing::Property;

TEST(InputCVRPTest, SetBasicProperties) {
    auto *input = new InputCVRP();
    input->setVertex(1);
    input->setCapacity(30);

    std::vector<Dot> dots;
    dots.push_back(Dot(2, 2, 5));
    dots.push_back(Dot(3, 5, 7));
    dots.push_back(Dot(2, 1, 3));

    input->setVertexCordenates(dots);

    ASSERT_EQ(input->getVertex(), 1);
    ASSERT_EQ(input->getCapacity(), 30);

    for (int i = 0; i < dots.size(); i++) {
        ASSERT_EQ(input->getVertexCordenates()[i], dots[i]);
    }
}
