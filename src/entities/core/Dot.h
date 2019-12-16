#pragma once

#include <iostream>

class Dot {
 public:
  int x;
  int y;
  int expectedCapacity;

  Dot(int x, int y, int capacity = 0);
  bool operator==(const Dot &rhs) const {
    return (x == rhs.x) && (y == rhs.y) && (expectedCapacity == rhs.expectedCapacity);
  }
  friend std::ostream &operator<<(std::ostream &os, const Dot &dot);

  friend class Route;
  friend class CVRP;
  friend class SavingsEuristic;
};
