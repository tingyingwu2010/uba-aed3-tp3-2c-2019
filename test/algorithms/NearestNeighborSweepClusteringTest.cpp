//
// Created by Christian nahuel Rivera on 14/12/19.
//

#include <gmock/gmock.h>
#include <entities/core/VertexCoordinate.h>
#include <cmath>
#include <algorithms/NearestNeighborSweepClustering.h>
#include <algorithms/utils/MakePolarCoordenatesCenteredInDepot.h>

using ::testing::Contains;
using ::testing::AllOf;
using ::testing::Property;

TEST(NearestNeighborSweepClusteringTest, test1_primerCuadrante_1cluster){
    auto dots = std::vector<Dot>();
    dots.emplace_back(Dot(5,6,0));
    dots.emplace_back(Dot(8,10,5));
    dots.emplace_back(Dot(9,7,4));

    auto stations = std::vector<StationCoordinate>();
    stations.emplace_back(StationCoordinate(0,0,0));

    double radius1 = std::sqrt( std::pow(8-5,2) + std::pow(10-6,2));
    double angle1 = std::atan2(10-6 ,8-5);
    stations.emplace_back(StationCoordinate(radius1,angle1,1));

    double radius2 = std::sqrt( std::pow(9-5,2) + std::pow(7-6,2));
    double angle2 = std::atan2(7-6 ,9-5);
    stations.emplace_back(StationCoordinate(radius2,angle2,2));


    std::vector<std::vector<int>> *actualClusters = NearestNeighborSweepClustering::execute(&stations, &dots, 10);


    auto expectedClusters = std::vector<std::vector<int>>();
    auto cluster = std::vector<int>();
    cluster.emplace_back(2);
    cluster.emplace_back(1);
    expectedClusters.emplace_back(cluster);
    ASSERT_EQ(expectedClusters, *actualClusters);
}

TEST(NearestNeighborSweepClusteringTest, test2_primerCuadrante_2clusters){
    auto dots = std::vector<Dot>();
    dots.emplace_back(Dot(5,6,0));
    dots.emplace_back(Dot(8,10,5));
    dots.emplace_back(Dot(9,7,4));

    auto stations = std::vector<StationCoordinate>();
    stations.emplace_back(StationCoordinate(0,0,0));

    double radius1 = std::sqrt( std::pow(8-5,2) + std::pow(10-6,2));
    double angle1 = std::atan2(10-6 ,8-5);
    stations.emplace_back(StationCoordinate(radius1,angle1,1));

    double radius2 = std::sqrt( std::pow(9-5,2) + std::pow(7-6,2));
    double angle2 = std::atan2(7-6 ,9-5);
    stations.emplace_back(StationCoordinate(radius2,angle2,2));


    std::vector<std::vector<int>> *actualClusters = NearestNeighborSweepClustering::execute(&stations, &dots, 5);


    auto expectedClusters = std::vector<std::vector<int>>();

    auto cluster = std::vector<int>();
    cluster.emplace_back(2);
    expectedClusters.emplace_back(cluster);

    auto cluster2 = std::vector<int>();
    cluster2.emplace_back(1);
    expectedClusters.emplace_back(cluster2);

    ASSERT_EQ(expectedClusters, *actualClusters);
}

TEST(NearestNeighborSweepClusteringTest, test3_mismoAngulo_3clusters){
    auto dots = std::vector<Dot>();
    dots.emplace_back(Dot(5,6,0));
    dots.emplace_back(Dot(2,8,9)); //1
    dots.emplace_back(Dot(5,2,10)); //2
    dots.emplace_back(Dot(1,4,5)); //3
    dots.emplace_back(Dot(5,4,10));//4
    dots.emplace_back(Dot(9,3,5)); //5
    dots.emplace_back(Dot(8,10,5)); //6

    auto stations = std::vector<StationCoordinate>();
    stations.emplace_back(StationCoordinate(0,0,0));

    double radius1 = std::sqrt( std::pow(8-5,2) + std::pow(10-6,2));
    double angle1 = std::atan2(10-6 ,8-5) * MakePolarCoordenatesCenteredInDepot::toDegress();
    stations.emplace_back(StationCoordinate(radius1,angle1,6));

    double radius2 = std::sqrt( std::pow(2-5,2) + std::pow(8-6,2));
    double angle2 = std::atan2(8-6 ,2-5) * MakePolarCoordenatesCenteredInDepot::toDegress();
    stations.emplace_back(StationCoordinate(radius2,angle2,1));

    double radius3 = std::sqrt( std::pow(1-5,2) + std::pow(4-6,2));
    double angle3 = 360.0 + std::atan2(4-6 ,1-5)* MakePolarCoordenatesCenteredInDepot::toDegress();
    stations.emplace_back(StationCoordinate(radius3,angle3,3));

    double radius4 = std::sqrt( std::pow(5-5,2) + std::pow(4-6,2));
    double angle4 = 360.0 + std::atan2(4-6,5-5) * MakePolarCoordenatesCenteredInDepot::toDegress();
    stations.emplace_back(StationCoordinate(radius4,angle4,4));

    double radius5 = std::sqrt( std::pow(5-5,2) + std::pow(2-6,2));
    double angle5 = 360.0 + std::atan2(2-6,5-5) * MakePolarCoordenatesCenteredInDepot::toDegress();
    stations.emplace_back(StationCoordinate(radius5,angle5,2));

    double radius6 = std::sqrt( std::pow(9-5,2) + std::pow(3-6,2));
    double angle6 = 360.0 + std::atan2(3-6 ,9-5) * MakePolarCoordenatesCenteredInDepot::toDegress();
    stations.emplace_back(StationCoordinate(radius6,angle6,5));


    std::vector<std::vector<int>> *actualClusters = NearestNeighborSweepClustering::execute(&stations, &dots, 15);


    auto expectedClusters = std::vector<std::vector<int>>();

    auto cluster = std::vector<int>();
    cluster.emplace_back(6);
    cluster.emplace_back(1);
    expectedClusters.emplace_back(cluster);

    auto cluster2 = std::vector<int>();
    cluster2.emplace_back(3);
    cluster2.emplace_back(4);
    expectedClusters.emplace_back(cluster2);

    auto cluster3 = std::vector<int>();
    cluster3.emplace_back(2);
    cluster3.emplace_back(5);
    expectedClusters.emplace_back(cluster3);

    ASSERT_EQ(expectedClusters, *actualClusters);
}