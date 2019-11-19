//
// Created by Christian nahuel Rivera on 9/11/19.
//
#include "Dot.h"

Dot::Dot(int x, int y, int capacity) {
  this->x = x;
  this->y = y;
  this->expectedCapacity = capacity;
}

std::ostream &operator<<(std::ostream &os, const Dot &dot) {
  os << "(x: " << dot.x << ", y: " << dot.y << ", d: " << dot.expectedCapacity << ")";
  return os;
}
