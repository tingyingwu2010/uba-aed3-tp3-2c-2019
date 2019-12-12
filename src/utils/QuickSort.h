#pragma once

#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <signal.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>
#include <vector>
#include <math.h>
#include <cstring>

#include "algorithms/SavingsHeuristic.h"

using namespace std;

class QuickSort {
public:

    QuickSort()= default;

    ~QuickSort()= default;

    static void Sort(SavingsHeuristic::Saving *input, long p, long r);
};
