//
// Created by Christian nahuel Rivera on 11/12/19.
//

#include <gmock/gmock.h>
#include <algorithms/utils/ValidateOutputCvrp.h>

using ::testing::Contains;
using ::testing::AllOf;
using ::testing::Property;

TEST(ValidateOutputCvrpTest, allDotsInOnlyOnePath_test1){
    ValidateOutputCvrp validate = ValidateOutputCvrp();

    auto path1 = std::vector<int>();
    path1.push_back(0);
    path1.push_back(1);
    path1.push_back(2);
    path1.push_back(0);

    auto path2 = std::vector<int>();
    path2.push_back(0);
    path2.push_back(3);
    path2.push_back(4);
    path2.push_back(0);

    auto paths = new std::vector<std::vector<int>>();
    paths->push_back(path1);
    paths->push_back(path2);


    ASSERT_TRUE(validate.allDotsInOnlyOnePath(*paths, 5));
}

TEST(ValidateOutputCvrpTest, allDotsInOnlyOnePath_test2){
    ValidateOutputCvrp validate = ValidateOutputCvrp();

    auto path1 = std::vector<int>();
    path1.push_back(0);
    path1.push_back(1);
    path1.push_back(2);
    path1.push_back(0);

    auto path2 = std::vector<int>();
    path2.push_back(0);
    path2.push_back(3);
    path2.push_back(1);
    path2.push_back(0);

    auto paths = new std::vector<std::vector<int>>();
    paths->push_back(path1);
    paths->push_back(path2);


    ASSERT_FALSE(validate.allDotsInOnlyOnePath(*paths, 5));
}

TEST(ValidateOutputCvrpTest, allPathsBeginAndEndInDepot_test1){
    ValidateOutputCvrp validate = ValidateOutputCvrp();

    auto path1 = std::vector<int>();
    path1.push_back(0);
    path1.push_back(1);

    auto path2 = std::vector<int>();
    path2.push_back(0);
    path2.push_back(3);
    path2.push_back(4);
    path2.push_back(0);

    auto paths = new std::vector<std::vector<int>>();
    paths->push_back(path1);
    paths->push_back(path2);


    ASSERT_FALSE(validate.allPathsBeginAndEndInDepot(*paths));
}

TEST(ValidateOutputCvrpTest, allPathsBeginAndEndInDepot_test2){
    ValidateOutputCvrp validate = ValidateOutputCvrp();

    auto path1 = std::vector<int>();
    path1.push_back(0);
    path1.push_back(1);
    path1.push_back(2);

    auto path2 = std::vector<int>();
    path2.push_back(0);
    path2.push_back(3);
    path2.push_back(4);
    path2.push_back(5);

    auto paths = new std::vector<std::vector<int>>();
    paths->push_back(path1);
    paths->push_back(path2);


    ASSERT_FALSE(validate.allPathsBeginAndEndInDepot(*paths));
}

TEST(ValidateOutputCvrpTest, allPathsBeginAndEndInDepot_test3){
    ValidateOutputCvrp validate = ValidateOutputCvrp();

    auto path1 = std::vector<int>();
    path1.push_back(0);
    path1.push_back(1);
    path1.push_back(2);
    path1.push_back(0);

    auto path2 = std::vector<int>();
    path2.push_back(0);
    path2.push_back(3);
    path2.push_back(4);
    path2.push_back(0);

    auto paths = new std::vector<std::vector<int>>();
    paths->push_back(path1);
    paths->push_back(path2);


    ASSERT_TRUE(validate.allPathsBeginAndEndInDepot(*paths));
}

TEST(ValidateOutputCvrpTest, anyPathWeightIsBiggerThanCapacity_test1){
    ValidateOutputCvrp validate = ValidateOutputCvrp();

    auto dots = std::vector<Dot>();
    dots.push_back(Dot(1,1,0));
    dots.push_back(Dot(1,1,5));
    dots.push_back(Dot(1,1,3));
    dots.push_back(Dot(1,1,7));
    dots.push_back(Dot(1,1,8));

    auto path1 = std::vector<int>();
    path1.push_back(0);
    path1.push_back(1);
    path1.push_back(2);
    path1.push_back(0);

    auto path2 = std::vector<int>();
    path2.push_back(0);
    path2.push_back(3);
    path2.push_back(4);
    path2.push_back(0);

    auto paths = new std::vector<std::vector<int>>();
    paths->push_back(path1);
    paths->push_back(path2);


    ASSERT_FALSE(validate.anyPathWeightIsBiggerThanCapacity(*paths,dots, 10));
}

TEST(ValidateOutputCvrpTest, anyPathWeightIsBiggerThanCapacity_test2){
    ValidateOutputCvrp validate = ValidateOutputCvrp();

    auto dots = std::vector<Dot>();
    dots.push_back(Dot(1,1,0));
    dots.push_back(Dot(1,1,5));
    dots.push_back(Dot(1,1,3));
    dots.push_back(Dot(1,1,7));
    dots.push_back(Dot(1,1,2));

    auto path1 = std::vector<int>();
    path1.push_back(0);
    path1.push_back(1);
    path1.push_back(2);
    path1.push_back(0);

    auto path2 = std::vector<int>();
    path2.push_back(0);
    path2.push_back(3);
    path2.push_back(4);
    path2.push_back(0);

    auto paths = new std::vector<std::vector<int>>();
    paths->push_back(path1);
    paths->push_back(path2);


    ASSERT_TRUE(validate.anyPathWeightIsBiggerThanCapacity(*paths,dots, 10));
}

TEST(ValidateOutputCvrpTest, validate_test1){
    ValidateOutputCvrp validate = ValidateOutputCvrp();

    auto dots = std::vector<Dot>();
    dots.push_back(Dot(1,1,0));
    dots.push_back(Dot(1,1,5));
    dots.push_back(Dot(1,1,3));
    dots.push_back(Dot(1,1,7));
    dots.push_back(Dot(1,1,2));

    auto path1 = std::vector<int>();
    path1.push_back(0);
    path1.push_back(1);
    path1.push_back(2);
    path1.push_back(0);

    auto path2 = std::vector<int>();
    path2.push_back(0);
    path2.push_back(3);
    path2.push_back(4);
    path2.push_back(0);

    auto paths = new std::vector<std::vector<int>>();
    paths->push_back(path1);
    paths->push_back(path2);

    auto input = new InputCVRP();
    input->setVertexCordenates(dots);
    input->setCapacity(10);

    auto output = new OutputCVRP(std::vector<std::vector<int>>(), std::vector<int>());
    output->setCaminos(*paths);


    ASSERT_TRUE(validate.validate(output,input));
}