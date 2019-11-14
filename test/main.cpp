#include <gmock/gmock.h>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

int main(int argc, char** argv) {

  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

