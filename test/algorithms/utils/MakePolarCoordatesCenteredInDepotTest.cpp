//
// Created by Christian nahuel Rivera on 12/12/19.
//

#include <gmock/gmock.h>
#include <cmath>
#include <entities/core/Dot.h>
#include <algorithms/utils/MakePolarCoordenatesCenteredInDepot.h>

using ::testing::Contains;
using ::testing::AllOf;
using ::testing::Property;

double pi = MakePolarCoordenatesCenteredInDepot::pi();

TEST(MakePolarCoordenatesCenteredInDepotTest, test1_xAndYArePositive){
    auto dots = std::vector<Dot>();
    dots.emplace_back(Dot(5,6,0));
    dots.emplace_back(Dot(8,10,0));
    dots.emplace_back(Dot(9,7,0));


    std::vector<StationCoordinate> *actualCoordinates = MakePolarCoordenatesCenteredInDepot::execute(&dots);


    ASSERT_EQ(3,actualCoordinates->size());
    ASSERT_EQ(StationCoordinate(0,0,0), actualCoordinates->at(0));

    double radius1 = std::sqrt( std::pow(8-5,2) + std::pow(10-6,2));
    double angle1 = std::atan2(10-6 ,8-5) * MakePolarCoordenatesCenteredInDepot::toDegress();
    ASSERT_EQ(StationCoordinate(radius1,angle1,1), actualCoordinates->at(1));

    double radius2 = std::sqrt( std::pow(9-5,2) + std::pow(7-6,2));
    double angle2 = std::atan2(7-6 ,9-5) * MakePolarCoordenatesCenteredInDepot::toDegress();
    ASSERT_EQ(StationCoordinate(radius2,angle2,2), actualCoordinates->at(2));
}

TEST(MakePolarCoordenatesCenteredInDepotTest, test2_xIsNegativeAndYIsnt){
    auto dots = std::vector<Dot>();
    dots.emplace_back(Dot(5,6,0));
    dots.emplace_back(Dot(2,8,0));
    dots.emplace_back(Dot(1,7,0));


    std::vector<StationCoordinate> *actualCoordinates = MakePolarCoordenatesCenteredInDepot::execute(&dots);


    ASSERT_EQ(3,actualCoordinates->size());
    ASSERT_EQ(StationCoordinate(0,0,0), actualCoordinates->at(0));

    double radius1 = std::sqrt( std::pow(2-5,2) + std::pow(8-6,2));
    double angle1 = std::atan2(8-6 ,2-5) * MakePolarCoordenatesCenteredInDepot::toDegress();
    ASSERT_EQ(StationCoordinate(radius1,angle1,1), actualCoordinates->at(1));

    double radius2 = std::sqrt( std::pow(1-5,2) + std::pow(7-6,2));
    double angle2 = std::atan2(7-6 ,1-5) * MakePolarCoordenatesCenteredInDepot::toDegress();
    ASSERT_EQ(StationCoordinate(radius2,angle2,2), actualCoordinates->at(2));
}

TEST(MakePolarCoordenatesCenteredInDepotTest, test3_xAndYAreNegative){
    auto dots = std::vector<Dot>();
    dots.emplace_back(Dot(5,6,0));
    dots.emplace_back(Dot(1,4,0));
    dots.emplace_back(Dot(3,2,0));


    std::vector<StationCoordinate> *actualCoordinates = MakePolarCoordenatesCenteredInDepot::execute(&dots);


    ASSERT_EQ(3,actualCoordinates->size());
    ASSERT_EQ(StationCoordinate(0,0,0), actualCoordinates->at(0));

    double radius1 = std::sqrt( std::pow(1-5,2) + std::pow(4-6,2));
    double angle1 = std::atan2(4-6 ,1-5) * MakePolarCoordenatesCenteredInDepot::toDegress() +360.0;
    ASSERT_EQ(StationCoordinate(radius1,angle1,1), actualCoordinates->at(1));

    double radius2 = std::sqrt( std::pow(3-5,2) + std::pow(2-6,2));
    double angle2 = std::atan2(2-6 ,3-5) * MakePolarCoordenatesCenteredInDepot::toDegress() + 360.0;
    ASSERT_EQ(StationCoordinate(radius2,angle2,2), actualCoordinates->at(2));
}

TEST(MakePolarCoordenatesCenteredInDepotTest, test4_xIsPositiveAndYNegative){
    auto dots = std::vector<Dot>();
    dots.emplace_back(Dot(5,6,0));
    dots.emplace_back(Dot(8,3,0));
    dots.emplace_back(Dot(9,3,0));


    std::vector<StationCoordinate> *actualCoordinates = MakePolarCoordenatesCenteredInDepot::execute(&dots);


    ASSERT_EQ(3,actualCoordinates->size());
    ASSERT_EQ(StationCoordinate(0,0,0), actualCoordinates->at(0));

    double radius1 = std::sqrt( std::pow(8-5,2) + std::pow(3-6,2));
    double angle1 = std::atan2(3-6 ,8-5) * MakePolarCoordenatesCenteredInDepot::toDegress() + 360.0;
    ASSERT_EQ(StationCoordinate(radius1,angle1,1), actualCoordinates->at(1));

    double radius2 = std::sqrt( std::pow(9-5,2) + std::pow(3-6,2));
    double angle2 = std::atan2(3-6 ,9-5)  * MakePolarCoordenatesCenteredInDepot::toDegress() + 360.0;
    ASSERT_EQ(StationCoordinate(radius2,angle2,2), actualCoordinates->at(2));
}

TEST(MakePolarCoordenatesCenteredInDepotTest, test5_xIspositiveAndYisZero){
    auto dots = std::vector<Dot>();
    dots.emplace_back(Dot(5,6,0));
    dots.emplace_back(Dot(10,6,0));


    std::vector<StationCoordinate> *actualCoordinates = MakePolarCoordenatesCenteredInDepot::execute(&dots);


    ASSERT_EQ(2,actualCoordinates->size());
    ASSERT_EQ(StationCoordinate(0,0,0), actualCoordinates->at(0));

    double radius1 = std::sqrt( std::pow(10-5,2) + std::pow(6-6,2));
    double angle1 = std::atan2(6-6 ,10-5) * MakePolarCoordenatesCenteredInDepot::toDegress();
    ASSERT_EQ(StationCoordinate(radius1,angle1,1), actualCoordinates->at(1));
}

TEST(MakePolarCoordenatesCenteredInDepotTest, test6_xIsZeroAndYpositive){
    auto dots = std::vector<Dot>();
    dots.emplace_back(Dot(5,6,0));
    dots.emplace_back(Dot(5,11,0));


    std::vector<StationCoordinate> *actualCoordinates = MakePolarCoordenatesCenteredInDepot::execute(&dots);


    ASSERT_EQ(2,actualCoordinates->size());
    ASSERT_EQ(StationCoordinate(0,0,0), actualCoordinates->at(0));

    double radius1 = std::sqrt( std::pow(5-5,2) + std::pow(11-6,2));
    double angle1 = std::atan2(11-6,5-5)  * MakePolarCoordenatesCenteredInDepot::toDegress();
    ASSERT_EQ(StationCoordinate(radius1,angle1,1), actualCoordinates->at(1));
}

TEST(MakePolarCoordenatesCenteredInDepotTest, test7_xIsNegativeAndYisZero){
    auto dots = std::vector<Dot>();
    dots.emplace_back(Dot(5,6,0));
    dots.emplace_back(Dot(1,6,0));


    std::vector<StationCoordinate> *actualCoordinates = MakePolarCoordenatesCenteredInDepot::execute(&dots);


    ASSERT_EQ(2,actualCoordinates->size());
    ASSERT_EQ(StationCoordinate(0,0,0), actualCoordinates->at(0));

    double radius1 = std::sqrt( std::pow(1-5,2) + std::pow(6-6,2));
    double angle1 = std::atan2(6-6 ,1-5)  * MakePolarCoordenatesCenteredInDepot::toDegress();
    ASSERT_EQ(StationCoordinate(radius1,angle1,1), actualCoordinates->at(1));
}

TEST(MakePolarCoordenatesCenteredInDepotTest, test8_xIsZeroAndYisNegative){
    auto dots = std::vector<Dot>();
    dots.emplace_back(Dot(5,6,0));
    dots.emplace_back(Dot(5,4,0));


    std::vector<StationCoordinate> *actualCoordinates = MakePolarCoordenatesCenteredInDepot::execute(&dots);


    ASSERT_EQ(2,actualCoordinates->size());
    ASSERT_EQ(StationCoordinate(0,0,0), actualCoordinates->at(0));

    double radius1 = std::sqrt( std::pow(5-5,2) + std::pow(4-6,2));
    double angle1 = std::atan2(4-6,5-5)  * MakePolarCoordenatesCenteredInDepot::toDegress() +360.0;
    ASSERT_EQ(StationCoordinate(radius1,angle1,1), actualCoordinates->at(1));
}